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

NueCCAnalyzer::NueCCAnalyzer(){

}

NueCCAnalyzer::~NueCCAnalyzer(){

}

