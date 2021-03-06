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
  FV_TPC.SetFV(1., 46., -19., 19., 2., 76.); // == Active Volume 
  FV1.SetFV(3., 44., -16., 16., 6., 70.); // == Fiducial volume (the same volume with the previous analysis)
  FV2.SetFV(2.5, 46., -19.5, 19.5, 2.5, 76.); // == Volume for Nearestz cut
  FV3.SetFV(-3., 50., -23., 23., 10., 80.); // == Volume for Minos veto.

  //=========
  //== Cuts
  //=========
  cut_nhits = 25;
  //cut_nearestz = 0.5; // == default cut by Wanwei
  //cut_nearestz_bellow = 10.;
  //cut_nearestz_upper = 80.;
  if (volume_index == 0) {
    //cut_nearestz_bellow = 0.5; // == Cut for the active volume
    //2.5 <=Nearest z <= 76
    //2.5 <=Nearest x(z) <= 46
    //-19.5 <=Nearest y(z) <= 19.5
  }
  else if (volume_index == 1) {
    //cut_nearestz_bellow = 2.5; // = Cut for the fiducial volume
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
  int nhits_0 = 0;
  int nhits_1 = 0;
  for(int i = 0; i < this_StandardRecoNtuple.no_hits; i++){
    if(this_StandardRecoNtuple.hit_plane[i] == 0) {
      nhits_0++;
    }
    else if(this_StandardRecoNtuple.hit_plane[i] == 1) {
      nhits_1++;
    }
  }
  isPassNhits = IsPassNhits(nhits_0, nhits_1);

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
  
  TVector3 nearestz_vec(this_StandardRecoNtuple.nearestz[0], this_StandardRecoNtuple.nearestz[1], this_StandardRecoNtuple.nearestz[2]);
  isPassNearestz = FV2.InFV(nearestz_vec);
  /*
  if(this_StandardRecoNtuple.nearestz[0] > cut_nearestz_X_bellow && this_StandardRecoNtuple.nearestz[0] < cut_nearestz_X_upper
     && this_StandardRecoNtuple.nearestz[1] > cut_nearestz_Y_bellow && this_StandardRecoNtuple.nearestz[1] < cut_nearestz_Y_upper
     &&this_StandardRecoNtuple.nearestz[2] > cut_nearestz_Z_bellow && this_StandardRecoNtuple.nearestz[2] < cut_nearestz_Z_upper){
    isPassNearestz = true;
  }
  */
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
  bool is_cryo = false;
  if(!IsData){
    Get_vtx_position_and_which_interaction();
    suffix = str_interaction;
    // == External?
    //cout << "best_vtx_position = (" << best_vtx_position.X() << ", " << best_vtx_position.Y() << ", " << best_vtx_position.Z() << ")" <<endl;
    bool isInside = FV_TPC.InFV(best_vtx_position);
    if(!isInside){
      suffix = "External_" + suffix;
      TVector3 active_volume_center(23.5, 0., 45.);
      double this_distance = (best_vtx_position - active_volume_center).Mag();
      is_cryo = (this_distance < 100.);
      if(is_cryo) suffix = suffix + "_Cryo";
      else suffix = suffix + "_NotCryo";
    }
  }

  //===================
  //==== Event weight
  //===================
  double weight = 1.;
  double beamflux_weight = 1.;
  double beamflux_weight_Up = 1.;
  double beamflux_weight_Down = 1.;
  double pot_weight = 1.;
  if(!IsData){
    pot_weight = data_pot / mc_pot;

    beamflux_weight = mcCorr->BeamFlux_SF(this_StandardRecoNtuple.nuPDG_truth, this_StandardRecoNtuple.enu_truth, 0);
    beamflux_weight_Up = mcCorr->BeamFlux_SF(this_StandardRecoNtuple.nuPDG_truth, this_StandardRecoNtuple.enu_truth, 1);
    beamflux_weight_Down = mcCorr->BeamFlux_SF(this_StandardRecoNtuple.nuPDG_truth, this_StandardRecoNtuple.enu_truth, -1);

    // == External background scaling
    ext_reweight_1view = 1.;
    ext_reweight_2view = 1.;
    if(suffix.Contains("External") && !is_cryo){
      // == p0, p1 in [0.7, 0.9]
      /*
      double p0_1view = 6.216;
      double p1_1view = -4.754;
      double p0_2view = 10.366;
      double p1_2view = -7.668;
      // == p0, p1 in [0.4, 0.9]
      double p0_1view = 3.895;
      double p1_1view = -1.928;
      double p0_2view = 7.171;
      double p1_2view = -3.840;
      */
      // == p0, p1 in [0.45, 0.9] for Not Cryo
      double p0_1view = 3.194;
      double p1_1view = -2.274;
      double p0_2view = 5.602;
      double p1_2view = -3.294;

      ext_reweight_1view = mcCorr->External_bkg_corr("pNueCC", pNueCC);
      ext_reweight_2view = mcCorr->External_bkg_corr("pNueCC2", pNueCC2);
      /*
      cout << "[NueCCAnalyzer::executeEvent] [" << this_StandardRecoNtuple.run << ":" << this_StandardRecoNtuple.event << "]" << endl;
      cout << "[NueCCAnalyzer::executeEvent] pNueCC : " << pNueCC << ", ExtCorr : " << ext_reweight_1view << endl;
      cout << "[NueCCAnalyzer::executeEvent] pNueCC2 : "<< pNueCC2 << ", ExtCorr : " << ext_reweight_2view << endl;
      */
      if(pNueCC > 0.45){
	ext_reweight_1view = p0_1view + p1_1view * pNueCC;
      }
      if(pNueCC2 > 0.45){
	ext_reweight_2view = p0_2view + p1_2view * pNueCC2;
      }

      // == fit parameters for otherfunctions
      /*
      // 1. [0] * x * exp([1] * x) + [2] * exp([3] * x)/x + [4] for pNueCC2
      double p0_1 = 1.91162e+02;
      double p1_1 = -7.32827;;
      double p2_1 = -2.78591e-01 ;
      double p3_1 = -2.15808e+02;
      double p4_1 = 3.16400;
      double ext_reweight_1_2view = p0_1 * pNueCC2 * exp(p1_1*pNueCC2) + p2_1 * exp(p3_1 * pNueCC2) / pNueCC2 + p4_1;
      if(ext_reweight_1_2view < 0.) ext_reweight_1_2view = 0.;
      // 2. [0] * x * exp([1] * x) + [2] * exp([3] * x)/x + [4] /x + [5]
      double p0_2 = -8.90125e+03;
      double p1_2 = -2.42296e+02;
      double p2_2 = -3.86198e-01;
      double p3_2 = -1.16362e+01;
      double p4_2 = 4.35563e-01;
      double p5_2 = 1.96238e+0;
      double ext_reweight_2_1view = p0_2 * pNueCC * exp(p1_2 * pNueCC) + p2_2 * exp(p3_2 * pNueCC) / pNueCC + p4_2 / pNueCC + p5_2;
      if(ext_reweight_2_1view < 0.) ext_reweight_2_1view = 0.;
      ext_reweight_2view = ext_reweight_1_2view;
      ext_reweight_1view = ext_reweight_2_1view;
      */
    }
  }
  weight *= pot_weight;

  if(IsData){
    Plot(suffix + "_central", 1.);
    Plot_others(suffix + "_central", 1.);
  }
  else{

    // == Central MC
    //cout << "pNueCC : " << pNueCC << ", weight : " << pot_weight << ", 1view weight : " << weight * ext_reweight_1view * beamflux_weight << endl;
    //cout << "pNueCC2 : " << pNueCC2 << ", weight : " << pot_weight << ", 1view weight : " << weight * ext_reweight_2view * beamflux_weight << endl;
    Plot("OneView_" + suffix + "_central", weight * ext_reweight_1view * beamflux_weight);
    Plot("TwoView_" + suffix + "_central", weight * ext_reweight_2view * beamflux_weight);
    Plot("OneView_" + suffix + "_central_NoExtReweight", weight * beamflux_weight);
    Plot("TwoView_" + suffix + "_central_NoExtReweight", weight * beamflux_weight);
    Plot_others("OneView_" + suffix + "_central", weight * beamflux_weight);
    Plot_others("TwoView_" + suffix + "_central", weight * beamflux_weight);


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

      if(isnan(weight_Up)) weight_Up = 1.;
      if(isnan(weight_Down)) weight_Down = 1.;

      
      if(this_syst_str.Contains("MaCOHpi") || this_syst_str.Contains("R0COHpi") ){
	if(isnan(weight_Up) | isnan(weight_Down)){
	  cout << "[run:event] = [" << this_StandardRecoNtuple.run << ", " << this_StandardRecoNtuple.event << "] this_syst_str : " << this_syst_str << ", Up : " << weight_Up << ", Down : " << weight_Down << endl;
	  
	}
      }

      /*
      Plot("OneView_" + suffix + "_" + syst_Up, weight * ext_reweight_1view * beamflux_weight * weight_Up );
      Plot("OneView_" + suffix + "_" + syst_Down, weight * ext_reweight_1view * beamflux_weight * weight_Down );
      Plot("TwoView_" + suffix + "_" + syst_Up, weight * ext_reweight_2view * beamflux_weight * weight_Up );
      Plot("TwoView_" + suffix + "_" + syst_Down, weight * ext_reweight_2view * beamflux_weight * weight_Down );
      */
    } 

    // == Beam flux reweight error
    /*
    Plot("OneView_" + suffix + "_beamflux_Up", weight * ext_reweight_1view * beamflux_weight_Up);
    Plot("OneView_" + suffix + "_beamflux_Down", weight * ext_reweight_1view * beamflux_weight_Down);
    Plot("TwoView_" + suffix + "_beamflux_Up", weight * ext_reweight_2view * beamflux_weight_Up);
    Plot("TwoView_" + suffix + "_beamflux_Down", weight * ext_reweight_2view * beamflux_weight_Down);
    */

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
  // 5 - nnhits + antiminos + nearestz + vertex + pNuecc > 0.994 / pNuecc2 > 0.991
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
	  if(pNueCC2 > 0.991) JSFillHist(suffix, "Cutflow_" + suffix, 6.5, weight, 10, 0., 10.);
	  JSFillHist(suffix, "pNueCC_vtx_" + suffix, pNueCC, weight, 1000, 0., 1.);
	  JSFillHist(suffix, "pNueCC2_vtx_" + suffix, pNueCC2, weight, 1000, 0., 1.);
	  JSFillHist(suffix, "pNueCC_vs_pNueCC2_vtx_" + suffix, pNueCC, pNueCC2, weight, 50, 0., 1., 50, 0., 1.);
	}
      }
    }
  }
}

void NueCCAnalyzer::Plot_others(TString suffix, double weight){
  if(isPassNhits){
    if(isPassAntiMINOS){
      JSFillHist(suffix, "NearestZ_X_" + suffix, this_StandardRecoNtuple.nearestz[0], weight, 50, 0., 50.);
      JSFillHist(suffix, "NearestZ_Y_" + suffix, this_StandardRecoNtuple.nearestz[1], weight, 40, -20., 20.);
      JSFillHist(suffix, "NearestZ_Z_" + suffix, this_StandardRecoNtuple.nearestz[2], weight, 80, 0., 80.);

      // == Verify if linear fit is availiable for external backgrounds
      if(!IsData){
	//best_vtx_position
	TVector3 active_volume_center(23.5, 0., 45.);
	double this_distance = (best_vtx_position - active_volume_center).Mag();
	bool is_cryo = (this_distance < 100.);
	if(this_distance < 100.) is_cryo = 0.5;
	if(is_cryo){
	  JSFillHist(suffix, "pNueCC_isCryo_" + suffix, pNueCC, weight,50, 0.,1.);
          JSFillHist(suffix, "pNueCC2_isCryo_" + suffix, pNueCC2, weight, 50, 0.,1.);
	}
	else{
	  JSFillHist(suffix, "pNueCC_isnotCryo_" + suffix, pNueCC, weight, 50, 0., 1.);
	  JSFillHist(suffix, "pNueCC2_isnotCryo_" + suffix, pNueCC2, weight, 50, 0.,1.);
	}
      }

      if(isPassVertex){
      }
    }
  }

}

bool NueCCAnalyzer::IsPassNhits(int nhits_0, int nhits_1){

  bool this_decision = false;
  double ratio = (nhits_1 + 0.) / (nhits_0 + 0.);
  if(nhits_0 >= cut_nhits && nhits_1 >= cut_nhits && ratio > cut_nhits_ratio_bellow && ratio < cut_nhits_ratio_upper){
    this_decision = true;
  }

  return this_decision;
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

