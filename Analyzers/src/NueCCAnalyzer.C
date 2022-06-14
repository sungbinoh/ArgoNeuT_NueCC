#include "NueCCAnalyzer.h"

void NueCCAnalyzer::initializeAnalyzer(){

  cout << "[[NueCCAnalyzer::initializeAnalyzer]] IsData : " << IsData << endl;
  //debug_mode = true;
  debug_mode = false;

  //===========================
  // == MC labelling
  //===========================
  label_energy_deposition = false;
  label_Wanwei = true;

  //===========================
  //== Define Fiducial Volumes
  //===========================
  // == volume_index : 0 (active volume), 1 (fiducial volume)
  volume_index = 0;
  FV_TPC.SetFV(0., 47., -20., 20., 0., 90.); // == Active Volume 
  FV1.SetFV(3., 44., -16., 16., 6., 70.); // == Fiducial volume (the same volume with the previous analysis)
  FV2.SetFV(5., 47., -15., 15., 5., 85.); // == Volume for Signal region
  FV3.SetFV(-3., 50., -23., 23., 10., 80.); // == Volume for Minos veto.

  //=========
  //== Cuts
  //=========
  cut_nhits = 50;
  //cut_nearestz = 0.5; // == default cut by Wanwei
  cut_nearestz_bellow = 10.;
  cut_nearestz_upper = 80.;
  if (volume_index == 0) {
    cut_nearestz_bellow = 0.5; // == Cut for the active volume
  }
  else if (volume_index == 1) {
    cut_nearestz_bellow = 2.5; // = Cut for the fiducial volume
  }
  cut_pNueCC = 0.99;
  cut_pNueCC2 = 0.99;
 
  //===========================
  // == Setup Event Variables
  //===========================
  data_pot = 1.25e20;
  mc_pot = 2.58834e+20;

}

void NueCCAnalyzer::executeEvent(){
  if(debug_mode) cout << "[[NueCCAnalyzer::executeEvent]] : START" << endl;
  if(debug_mode) cout << "[[NueCCAnalyzer::executeEvent]] : POT : " << this_StandardRecoNtuple.pot << endl;
 
  //=============
  //== Booleans
  //=============
  isPassNhits = (this_StandardRecoNtuple.no_hits >= cut_nhits);

  isPassAntiMINOS = true;
  for (int i = 0; i < this_StandardRecoNtuple.ntracks_minos; ++i) {
    if(100. * this_StandardRecoNtuple.trk_vtxz_all_minos[i] > 6.) continue;
    for (int j = 0; j < 10; ++j) {
      TVector2 this_muon(this_StandardRecoNtuple.trk_xpred_minos[i][j], this_StandardRecoNtuple.trk_ypred_minos[i][j]);
      bool this_decision = FV3.InFV_XY(this_muon);
      if(this_decision){
	isPassAntiMINOS = false;
	break;
      }
    }
    if (!isPassAntiMINOS) break;
  }
  isPassNearestz = (this_StandardRecoNtuple.nearestz[2] >= cut_nearestz_bellow);
  //bool isPassNearestz = (this_StandardRecoNtuple.nearestz[2] >= cut_nearestz_bellow) && (this_StandardRecoNtuple.nearestz[2] <= cut_nearestz_upper);

  TVector3 vertex(this_StandardRecoNtuple.vtxx_reco, this_StandardRecoNtuple.vtxy_reco, this_StandardRecoNtuple.vtxz_reco);
  bool isPassVertex_TPC = FV_TPC.InFV(vertex);
  bool isPassVertex_FV1 = FV1.InFV(vertex);
  //bool isPassVertex_FV2 = FV2.InFV(vertex);
  isPassVertex = false;
  if(volume_index == 0){
    isPassVertex = true;
  }
  else if(volume_index == 1 && isPassVertex_FV1){
    isPassVertex = true;
  }
  else{
    isPassVertex = false;
  }

  pNueCC = this_StandardRecoNtuple.pNueCC;
  pNueCC2 = this_StandardRecoNtuple.pNueCC2;
  if (pNueCC == -9999) pNueCC = 1.0e-6;
  if (pNueCC >= 1.0 - 1.0e-6) pNueCC = 1.0 - 1.0e-6;
  bool isPasspNueCC = (pNueCC >= cut_pNueCC);

  if (pNueCC2 == -9999) pNueCC2 = 1.0e-6;
  if (pNueCC2 >= 1.0 - 1.0e-6) pNueCC2 = 1.0 - 1.0e-6;
  bool isPasspNueCC2 = (pNueCC2 >= cut_pNueCC2);

  //===============================
  //==== Set suffix for histograms
  //===============================
  TString suffix = "Data";
  if(!IsData){
    Get_vtx_position_and_which_interaction();
    suffix = str_interaction;
    // == External?
    //cout << "best_vtx_position = (" << best_vtx_position.X() << ", " << best_vtx_position.Y() << ", " << best_vtx_position.Z() << ")" <<endl;
    bool isInside = FV_TPC.InFV(best_vtx_position);
    if(!isInside) suffix = "External_" + suffix;
  }

  //===================
  //==== Event weight
  //===================
  double weight = 1.;
  if(!IsData){
    double pot_weight = data_pot / mc_pot;
    //double beamflux_weight = mcCorr->BeamFlux_SF((*this_StandardRecoNtuple.nuPDG_truth_multiple)[best_neutrino_number], (*this_StandardRecoNtuple.enu_truth_multiple)[best_neutrino_number], 0);
    double beamflux_weight = mcCorr->BeamFlux_SF(this_StandardRecoNtuple.nuPDG_truth, this_StandardRecoNtuple.enu_truth, 0);
    
    // == External background scaling
    ext_reweight_1view = 1.;
    ext_reweight_2view = 1.;
    if(suffix.Contains("External")){
      // == p0, p1 in [0.7, 0.9]
      /*
      double p0_1view = 6.216;
      double p1_1view = -4.754;
      double p0_2view = 10.366;
      double p1_2view = -7.668;
      */
      // == p0, p1 in [0.4, 0.9]
      double p0_1view = 3.895;
      double p1_1view = -1.928;
      double p0_2view = 7.171;
      double p1_2view = -3.840;

      // ==  Default ext_reweight values are 1.0
      ext_reweight_1view = p0_1view + p1_1view * pNueCC;
      ext_reweight_2view = p0_2view + p1_2view * pNueCC2;

      //cout << "SB debug, pNueCC : " << pNueCC << ", pNueCC2 : " << pNueCC2 << ", ext_reweight_1view : " << ext_reweight_1view << ", ext_reweight_2view : " << ext_reweight_2view << endl;
    }

    weight *= pot_weight;
    weight *= beamflux_weight;
    //cout << "[Run:Event] = [" << this_StandardRecoNtuple.run << ":" << this_StandardRecoNtuple.event << "] pot_weight : " << pot_weight << ", beamflux_weight  : " << beamflux_weight << ", weight : " << weight << ", suffix : " << suffix << endl;
    //cout << "best_neutrino_number : "  << best_neutrino_number << ", multiple 0 PDG = " << (*this_StandardRecoNtuple.nuPDG_truth_multiple)[0] << ", multiple 0 enu" << (*this_StandardRecoNtuple.enu_truth_multiple)[0] << ", nuPDG_truth = " << this_StandardRecoNtuple.nuPDG_truth << ", enu_truth = " <<  this_StandardRecoNtuple.enu_truth << endl;
  }

  if(IsData){
    Plot(suffix + "_central", 1.);
  }
  else{

    // == Central MC
    Plot("OneView_" + suffix + "_central", weight * ext_reweight_1view);
    Plot("TwoView_" + suffix + "_central", weight * ext_reweight_2view);
    Plot("OneView_" + suffix + "_central_NoExtReweight", weight);
    Plot("TwoView_" + suffix + "_central_NoExtReweight", weight);

    // == For loop for GENIE parameter uncertainties
    unsigned int size_evtwgt_weight = (*this_StandardRecoNtuple.evtwgt_weight).size();
    //cout << "There are  " << size_evtwgt_weight - 1 << " of GENIE error sets" << endl;
    for(unsigned int i = 1; i < (*this_StandardRecoNtuple.evtwgt_funcname).size(); i++){
      TString this_syst_str = (*this_StandardRecoNtuple.evtwgt_funcname)[i];
      //unsigned int size_this_evt_weight =  (*this_StandardRecoNtuple.evtwgt_weight).at(i).size();
      TString syst_Up = this_syst_str + "_Up";
      TString syst_Down =this_syst_str +"_Down";
      double weight_Up =  (*this_StandardRecoNtuple.evtwgt_weight)[i][0];
      double weight_Down =  (*this_StandardRecoNtuple.evtwgt_weight)[i][1];

      Plot("OneView_" + suffix + "_" + syst_Up, weight * ext_reweight_1view * weight_Up );
      Plot("OneView_" + suffix + "_" + syst_Down, weight * ext_reweight_1view * weight_Down );
      Plot("TwoView_" + suffix + "_" + syst_Up, weight * ext_reweight_2view * weight_Up );
      Plot("TwoView_" + suffix + "_" + syst_Down, weight * ext_reweight_2view * weight_Down );

    } 

    // == External Background syst
    // == NONE. Just Normalization error for now...
    
  }
}

void NueCCAnalyzer::Plot(TString suffix, double weight){
  //=============
  //== Plot
  //=============

  // event index:
  // 0 - total:
  // 1 - nhits;
  // 2 - nhits + antiminos;
  // 3 - nhits + antiminos + nearestz;
  // 4 - nhits + antiminos + nearestz + vertex;
  // 5 - nnhits + antiminos + nearestz + vertex + pNuecc > 0.994
  JSFillHist(suffix, "Cutflow_" + suffix, 0.5, weight, 10, 0., 10.);
  JSFillHist(suffix, "pNueCC_" + suffix, pNueCC, weight, 1000, 0., 1.);
  JSFillHist(suffix, "pNueCC2_" + suffix, pNueCC2, weight, 1000, 0., 1.);
  JSFillHist(suffix, "nhits_" + suffix, this_StandardRecoNtuple.no_hits, weight, 500, 0., 500.);

  if(isPassNhits){
    JSFillHist(suffix, "Cutflow_" + suffix, 1.5, weight, 10, 0., 10.);
    JSFillHist(suffix, "pNueCC_nhits_" + suffix, pNueCC, weight, 1000, 0., 1.);
    if(isPassAntiMINOS){
      JSFillHist(suffix, "Cutflow_" + suffix, 2.5, weight, 10, 0., 10.);
      JSFillHist(suffix, "pNueCC_nhits_antiminos_" + suffix, pNueCC, weight, 1000, 0., 1.);
      if(isPassNearestz){
	JSFillHist(suffix, "Cutflow_" + suffix, 3.5, weight, 10, 0., 10.);
	JSFillHist(suffix, "pNueCC_nhits_antiminos_nearestz_" + suffix, pNueCC, weight, 1000, 0., 1.);
	if(isPassVertex){
	  JSFillHist(suffix, "Cutflow_" + suffix, 4.5, weight, 10, 0., 10.);
	  if(pNueCC > 0.994) JSFillHist(suffix, "Cutflow_" + suffix, 5.5, weight, 10, 0., 10.);
	  if(pNueCC2 > 0.994) JSFillHist(suffix, "Cutflow_" + suffix, 6.5, weight, 10, 0., 10.);
	  JSFillHist(suffix, "pNueCC_vtx_" + suffix, pNueCC, weight, 1000, 0., 1.);
	  JSFillHist(suffix, "pNueCC2_vtx_" + suffix, pNueCC2, weight, 1000, 0., 1.);
	}
      }
    }
  }
}

TString NueCCAnalyzer::Get_suffix(int nu_PDG){

  TString current_nu_str = "";
  if(nu_PDG == 12) current_nu_str = "Nue";
  else if(nu_PDG == -12) current_nu_str = "AntiNue";
  else if(nu_PDG == 14) current_nu_str = "Numu";
  else if(nu_PDG == -14) current_nu_str = "AntiNumu";
  

}

void NueCCAnalyzer::Get_vtx_position_and_which_interaction(){

  // == We want to identify interaction category of an event using truth level information

  if(label_energy_deposition){ // == Label an event using energy deposition, use the first truth particle
    TVector3 this_vtx((*this_StandardRecoNtuple.nuvtxx_truth_multiple)[0], (*this_StandardRecoNtuple.nuvtxy_truth_multiple)[0], (*this_StandardRecoNtuple.nuvtxz_truth_multiple)[0]);
    TString this_interaction = "";
    int int_interaction = 2;

    // == Save which interaction
    if ((*this_StandardRecoNtuple.ccnc_truth_multiple)[0] == 0) { // == charged current, CC
      if (abs((*this_StandardRecoNtuple.nuPDG_truth_multiple)[0]) == 14) {
	this_interaction = "NumuCC";
	int_interaction = 0;
      }
      else if (abs((*this_StandardRecoNtuple.nuPDG_truth_multiple)[0]) == 12) {
	this_interaction = "NueCC";
	int_interaction = 1;
      }
    }
    else { // == neutral current, NC                                                                                      
      this_interaction = "NC";
      int_interaction = 2;
    }
    best_vtx_position = this_vtx;
    str_interaction = this_interaction;
    best_neutrino_number = 0;
  }
  else if(label_Wanwei){
    TVector3 this_vtx(this_StandardRecoNtuple.nuvtxx_truth, this_StandardRecoNtuple.nuvtxy_truth, this_StandardRecoNtuple.nuvtxz_truth);
    TString this_interaction = "";
    int int_interaction = 2;
    if (this_StandardRecoNtuple.ccnc_truth == 0) {
      if (abs(this_StandardRecoNtuple.nuPDG_truth) == 14) {
        this_interaction = "NumuCC";
        int_interaction = 0;
      }
      else if (abs(this_StandardRecoNtuple.nuPDG_truth) == 12) {
        this_interaction = "NueCC";
        int_interaction = 1;
      }
    }
    else {
      this_interaction = "NC";
      int_interaction = 2;
    }
    best_vtx_position = this_vtx;
    str_interaction = this_interaction;
    best_neutrino_number = 0;

  }
  else{ // == Label an event using truth level vertex
    // == First of all, identify interaction category of each neutrino interactions in an event and save vertex position
    std::vector<TVector3> vtr_vtx_position;
    std::vector<TString> vtr_str_interaction;
    std::vector<int> vtr_int_interaction; // 0 : NumuCC, 1 : NueCC, 2 : NC
    int current_mcevts_truth = this_StandardRecoNtuple.mcevts_truth;
    for(int n = 0; n < current_mcevts_truth; n++) {
      if (current_mcevts_truth == 1) {
	// == Save vertex position
	TVector3 this_vtx(this_StandardRecoNtuple.nuvtxx_truth, this_StandardRecoNtuple.nuvtxy_truth, this_StandardRecoNtuple.nuvtxz_truth);
	vtr_vtx_position.push_back(this_vtx);
	
	TString this_interaction = "";
	int int_interaction = 2;      
	// == Save which interaction
	if (this_StandardRecoNtuple.ccnc_truth == 0) { // == charged current, CC
	  if (abs(this_StandardRecoNtuple.nuPDG_truth) == 14) {
	    this_interaction = "NumuCC";
	    int_interaction = 0;
	  }
	  else if (abs(this_StandardRecoNtuple.nuPDG_truth) == 12) {
	    this_interaction = "NueCC";
	    int_interaction = 1;
	  }
	}
	else { // == neutral current, NC
	  this_interaction = "NC";
	  int_interaction = 2;
	}
	vtr_str_interaction.push_back(this_interaction);
	vtr_int_interaction.push_back(int_interaction);
      }
    
      else{
	// == Save vertex position
	TVector3 this_vtx((*this_StandardRecoNtuple.nuvtxx_truth_multiple)[n], (*this_StandardRecoNtuple.nuvtxy_truth_multiple)[n], (*this_StandardRecoNtuple.nuvtxz_truth_multiple)[n]);
	vtr_vtx_position.push_back(this_vtx);

	TString this_interaction = "";
	int int_interaction = 2;
	if ((*this_StandardRecoNtuple.ccnc_truth_multiple)[n] == 0) { // == charged current, CC
	  if (abs((*this_StandardRecoNtuple.nuPDG_truth_multiple)[n]) == 14) {
	    this_interaction = "NumuCC";
	    int_interaction = 0;
	  }
	  else if (abs((*this_StandardRecoNtuple.nuPDG_truth_multiple)[n]) == 12) {
	    this_interaction = "NueCC";
	    int_interaction = 1;
	  }
	}
	else { // == neutral current, NC
	  this_interaction = "NC";
	  int_interaction = 2;
	}
	vtr_str_interaction.push_back(this_interaction);
	vtr_int_interaction.push_back(int_interaction);
      }
    }
  
    if(debug_mode){
      for(int i = 0; i < vtr_str_interaction.size(); i++){
	cout << "vtr_str_interaction.at(" << i << ") : " << vtr_str_interaction.at(i) << endl;
      }
    }

    // == Select the best vertex with priorities bellow when current_mcevts_truth < 4
    // ==== 1. NueCC event
    // ==== 2. Inside the TPC FV (FV_TPC)
    // ==== 3. Closest to the center of ArgoNeuT (23.5, 0, 26)
    // == For event with at least 4 current_mcevts_truth, set vtx position (-9999., -9999., -9999.) - abandon the event
    TVector3 this_vtx_position (-9999., -9999., -9999.);
    TString this_interaction = "NC";
    /*
      if(current_mcevts_truth < 4){
      int i_best_vtx = 0;
      i_best_vtx = Select_best_vtx(vtr_vtx_position, vtr_int_interaction); 
      best_vtx_position = vtr_vtx_position.at(i_best_vtx);
      str_interaction = vtr_str_interaction.at(i_best_vtx);
      }
      else{
      best_vtx_position = this_vtx_position;
      str_interaction = this_interaction;
      }
    */
    int i_best_vtx = 0;
    i_best_vtx = Select_best_vtx(vtr_vtx_position, vtr_int_interaction);
    best_vtx_position = vtr_vtx_position.at(i_best_vtx);
    str_interaction = vtr_str_interaction.at(i_best_vtx);
    best_neutrino_number = i_best_vtx;
  
    vtr_vtx_position.clear();
    vtr_str_interaction.clear();
    vtr_int_interaction.clear();

  }
}

int NueCCAnalyzer::Select_best_vtx(std::vector<TVector3> vtr_vtx, std::vector<int> vtr_int_interaction){

  int i_best_vtx = 0;

  unsigned int N_vtr_vtx = vtr_vtx.size();
  if(N_vtr_vtx <= 1) return 0;

  for(unsigned int i = 0; i < vtr_vtx.size() - 1; i++){
    bool current_decision = Is_Better_vtx(vtr_vtx.at(i), vtr_int_interaction.at(i), vtr_vtx.at(i + 1), vtr_int_interaction.at(i + 1));
    if(!current_decision) i_best_vtx = i + 1;
  }

  return i_best_vtx;
  
}

bool NueCCAnalyzer::Is_Better_vtx(TVector3 vtx1, int vtx1_interaction, TVector3 vtx2, int vtx2_interaction){
  // == vtx 1 is better : return true, vtx 2 is better : return false
  // == Select a better vertex
  // ==== 1. NueCC event  (vtx_interaction == 1)
  // ==== 2. Inside the TPC FV (FV_TPC)
  // ==== 3. Closest to the center of ArgoNeuT (23.5, 0, 26)
  bool this_decision = true;
  // == assign false where vtx2 is better than vtx1
  if(vtx1_interaction == 1){
    if(vtx2_interaction == 1){
      if(FV_TPC.InFV(vtx1)){
	if(FV_TPC.InFV(vtx2)){
	  this_decision = Is_closer_to_center(vtx1, vtx2);
	}
      }
      else { // -- !FV_TPC.InFV(vtx1)
	if(FV_TPC.InFV(vtx2)){
	  this_decision = false;
	}
	else this_decision = Is_closer_to_center(vtx1, vtx2);
      }
    }
    else{ // -- !vtx2_interaction == 1
      if(!FV_TPC.InFV(vtx1)){
	if(FV_TPC.InFV(vtx2)) this_decision = false;
	else this_decision = Is_closer_to_center(vtx1, vtx2);
      }
    }
  }
  else{ // -- !vtx1_interaction == 1
    if(vtx2_interaction == 1){
      if(FV_TPC.InFV(vtx2)) this_decision = false;
      else if(!FV_TPC.InFV(vtx1)) this_decision = Is_closer_to_center(vtx1, vtx2);
    }
    else{ // -- !vtx2_interaction == 1
      if(FV_TPC.InFV(vtx1)){
	if(FV_TPC.InFV(vtx2)) this_decision = Is_closer_to_center(vtx1, vtx2);
      }
      else{ // -- !FV_TPC.InFV(vtx1)
	if(FV_TPC.InFV(vtx2)) this_decision = false;
	else this_decision = Is_closer_to_center(vtx1, vtx2);
      }
    }
  }

  return this_decision;
  
}

bool NueCCAnalyzer::Is_closer_to_center(TVector3 vtx1, TVector3 vtx2){
  // == vtx 1 is closer to the center : return true, vtx 2 is closer to the center : return false
  bool this_decision = true;
  TVector3 center(23.5, 0., 26.);
  double distance_1 = (vtx1 - center).Mag();
  double distance_2 = (vtx2 - center).Mag();
  if(distance_1 > distance_2) this_decision = false;

  return this_decision;
}


NueCCAnalyzer::NueCCAnalyzer(){

}

NueCCAnalyzer::~NueCCAnalyzer(){

}

