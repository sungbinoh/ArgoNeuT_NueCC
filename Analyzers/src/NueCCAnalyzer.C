#include "NueCCAnalyzer.h"

void NueCCAnalyzer::initializeAnalyzer(){

  cout << "[[NueCCAnalyzer::initializeAnalyzer]] IsData : " << IsData << endl;
  //debug_mode = true;
  debug_mode = false;

  //===========================
  //== Define Fiducial Volumes
  //===========================
  volume_index = 0;
  FV_TPC.SetFV(0., 47., -20., 20., 0., 90.);
  FV1.SetFV(3., 44., -16., 16., 6., 70.);
  FV2.SetFV(0., 47., -20., 20., 2., 76.);
  FV_vtx = FV_TPC;
  if(volume_index == 0){
    FV_vtx = FV_TPC;
  }
  else if(volume_index == 1){
    FV_vtx = FV1;
  }
  else if(volume_index == 2){
    FV_vtx = FV2;
  }

  //=========
  //== Cuts
  //=========
  cut_nhits = 50;
  cut_nearestz = 0.5;
  if (volume_index == 2) {
    cut_nearestz = 1.;
  }
  else if (volume_index == 1) {
    cut_nearestz = 2.5;
  }
  cut_pNueCC = 0.99;
  cut_pNueCC2 = 0.99;
 
  //===========================
  // == Setup Event Variables
  //===========================
  data_pot = 1.25e20;
  mc_pot = 1.111007228e+20;

}

void NueCCAnalyzer::executeEvent(){
  if(debug_mode) cout << "[[NueCCAnalyzer::executeEvent]] : START" << endl;

  //===================
  //==== Event weight
  //===================
  double weight = 1.;
  if(!IsData){
    weight *= data_pot / mc_pot;
    weight *= mcCorr->BeamFlux_SF(this_StandardRecoNtuple.nuPDG_truth, this_StandardRecoNtuple.enu_truth, 0);
  }

  TString suffix = "data";
  if(!IsData){
    vtr_vtx_position.clear();
    vtr_which_interaction.clear();
    

    suffix = Get_suffix(this_StandardRecoNtuple.nuPDG_truth);
  }
    

  //=============
  //== Booleans
  //=============
  bool isPassNhits = (this_StandardRecoNtuple.no_hits >= cut_nhits);

  bool isPassAntiMINOS = true;
  for (int i = 0; i < this_StandardRecoNtuple.ntracks_minos; ++i) {
    for (int j = 0; j < 10; ++j) {
      TVector2 this_muon(this_StandardRecoNtuple.trk_xpred_minos[i][j], this_StandardRecoNtuple.trk_ypred_minos[i][j]);
      bool this_decision = FV1.InFV_XY(this_muon);
      if(this_decision){
	isPassAntiMINOS = false;
	break;
      }
    }
    if (!isPassAntiMINOS) break;
  }

  bool isPassNearestz = (this_StandardRecoNtuple.nearestz[2] >= cut_nearestz);

  TVector3 vertex(this_StandardRecoNtuple.vtxx_reco, this_StandardRecoNtuple.vtxy_reco, this_StandardRecoNtuple.vtxz_reco);
  bool isPassVertex = FV_TPC.InFV(vertex);

  double pNueCC = this_StandardRecoNtuple.pNueCC;
  double pNueCC2 = this_StandardRecoNtuple.pNueCC2;
  if (pNueCC == -9999) pNueCC = 1.0e-6;
  if (pNueCC == 1.) pNueCC = 1.0 - 1.0e-6;
  bool isPasspNueCC = (pNueCC >= cut_pNueCC);

  if (pNueCC2 == -9999) pNueCC2 = 1.0e-6;
  if (pNueCC2 == 1.) pNueCC2 = 1.0 - 1.0e-6;
  bool isPasspNueCC2 = (pNueCC2 >= cut_pNueCC2);

  //=============
  //== Plot
  //=============
  // event index:
  // 0 - total:
  // 1 - nhits;
  // 2 - nhits + antiminos;
  // 3 - nhits + antiminos + nearestz;
  // 4 - nhits + antiminos + nearestz + vertex;
  FillHist("Cutflow", 0.5, weight, 6, 0., 6.);
  FillHist("pNueCC", pNueCC, weight, 1000, 0., 1.);
  if(isPassNhits){
    FillHist("Cutflow", 1.5, weight, 6, 0., 6.);
    FillHist("pNueCC_nhits", pNueCC, weight, 1000, 0., 1.);
    if(isPassAntiMINOS){
      FillHist("Cutflow", 2.5, weight, 6, 0., 6.);
      FillHist("pNueCC_nhits_antiminos", pNueCC, weight, 1000, 0., 1.);
      if(isPassNearestz){
	FillHist("Cutflow", 3.5, weight, 6, 0., 6.);
	FillHist("pNueCC_nhits_antiminos_nearestz", pNueCC, weight, 1000, 0., 1.);
	if(isPassVertex){
	  FillHist("Cutflow", 4.5, 1., 6, 0., 6.);
	  FillHist("pNueCC_nhits_antiminos_nearestz_vertex", pNueCC, weight, 1000, 0., 1.);
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

  std::vector<TVector3> vtr_vtx_position;
  std::vector<TString> vtr_str_interaction;
  std::vector<int> vtr_int_interaction; // 0 : NumuCC, 1 : NueCC, 2 : NC
  // == First of all, identify interaction category of each neutrino interactions in an event and save vertex position
  int current_mcevts_truth = this_StandardRecoNtuple.mcevts_truth;
  for(int n = 0; n < current_mcevts_truth; n++) {
    if (current_mcevts_truth == 1) {
      // == Save vertex position
      TVector3 this_vtx(this_StandardRecoNtuple.nuvtxx_truth, this_StandardRecoNtuple.nuvtxy_truth, this_StandardRecoNtuple.nuvtxz_truth);
      vtr_vtx_position.push_back(this_vtx);
      
      TString this_interaction = "";
      int int_interaction = 2;      
      // == Save which interaction
      if (this_StandardRecoNtupleccnc_truth == 0) { // == charged current, CC
	if (abs(this_StandardRecoNtuplenuPDG_truth) == 14) {
	  this_interaction = "NumuCC";
	  int_interaction = 0;
	}
	else if (abs(this_StandardRecoNtuplenuPDG_truth) == 12) {
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
      TVector3 this_vtx(this_StandardRecoNtuple.nuvtxx_truth, this_StandardRecoNtuple.nuvtxy_truth, this_StandardRecoNtuple.nuvtxz_truth);
      vtr_vtx_position.push_back(this_vtx);

      TString this_interaction = "";
      int int_interaction = 2;
      if ((*this_StandardRecoNtuple.nuvtxx_truth.ccnc_truth_multiple)[n] == 0) { // == charged current, CC
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

  // == Select the best vertex with priorities bellow when current_mcevts_truth < 4
  // ==== 1. NueCC event
  // ==== 2. Inside the TPC FV (FV_TPC)
  // ==== 3. Closest to the center of ArgoNeuT (23.5, 0, 26)
  // == For event with at least 4 current_mcevts_truth, set vtx position (-9999., -9999., -9999.) - abandon the event
  TVector3 this_vtx_position (-9999., -9999., -9999.);
  TString this_interaction = "";
  if(current_mcevts_truth < 4){
    int i_best_vtx = 0;
    i_best_vtx = Select_best_vtx(vtr_vtx_position, vtr_int_interaction); 
    best_vtx_position = vtr_vtx_position.at(i);
    str_interaction = vtr_str_interaction.at(i);
  }
  best_vtx_position = this_vtx_position;
  str_interaction = this_interaction;

  vtr_vtx_position.clear();
  vtr_str_interaction.clear();
  vtr_int_interaction.clear();

}

int NueCCAnalyzer::Select_best_vtx(std::vector<TVector3> vtr_vtx, std::vector<TString> vtr_int_interaction){

  int i_best_vtx = 0;
  for(unsigned int i = 0; i < vtr_vtx.size(); i++){
    
  }

}

bool Is_Better_vtx(TVector3 vtx1, TString vtx1_interaction, TVector3 vtx2, TString vtx2_interaction){
  

}
//double NueCCAnalyzer::

NueCCAnalyzer::NueCCAnalyzer(){

}

NueCCAnalyzer::~NueCCAnalyzer(){

}

