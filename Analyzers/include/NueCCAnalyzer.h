#ifndef NueCCAnalyzer_h
#define NueCCAnalyzer_h

#include "AnalyzerCore.h"

class NueCCAnalyzer : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEvent();

  //=====================
  //== Fiducial Volumes
  //=====================
  FiducialVolume FV_TPC;
  FiducialVolume FV1;
  FiducialVolume FV2;
  FiducialVolume FV_vtx;

  //=========
  //== Cuts
  //=========
  int volume_index;
  int cut_nhits = 50;
  double cut_nearestz = 0.5;
  double cut_pNueCC = 0.99;
  double cut_pNueCC2 = 0.99;

  //=========================== 
  //== Event Variables
  //=========================== 
  double data_pot;
  double mc_pot;

  //==========================
  //== Additional functions
  //==========================
  TString Get_suffix(int nu_PDG);
  void Get_vtx_position_and_which_interaction();
  int Select_best_vtx(std::vector<TVector3> vtr_vtx, std::vector<int> vtr_int_interaction);
  bool Is_Better_vtx(TVector3 vtx1, int vtx1_interaction, TVector3 vtx2, int vtx2_interaction);
  bool Is_closer_to_center(TVector3 vtx1, TVector3 vtx2);

  //==========================
  //== Additional variables
  //==========================
  TVector3 best_vtx_position;
  TString str_interaction;

  NueCCAnalyzer();
  ~NueCCAnalyzer();

};

#endif
