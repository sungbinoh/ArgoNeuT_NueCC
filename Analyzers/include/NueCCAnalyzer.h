#ifndef NueCCAnalyzer_h
#define NueCCAnalyzer_h

#include "AnalyzerCore.h"

class NueCCAnalyzer : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEvent();
  void Plot(TString suffix, double weight);
  void Plot_others(TString suffix, double weight);

  //=====================
  //== Fiducial Volumes
  //=====================
  FiducialVolume FV_TPC;
  FiducialVolume FV1;
  FiducialVolume FV2;
  FiducialVolume FV3;
  FiducialVolume FV_vtx;

  //=========
  //== Cuts
  //=========
  bool label_energy_deposition = false;
  bool label_Wanwei = false;
  int volume_index;
  int cut_nhits = 25;
  double cut_nhits_ratio_bellow= 0.3;
  double cut_nhits_ratio_upper = 2.0;
  double cut_nearestz_Z_bellow = 2.5;
  double cut_nearestz_Z_upper = 76.;
  double cut_nearestz_X_bellow = 2.5;
  double cut_nearestz_X_upper = 46;
  double cut_nearestz_Y_bellow = -19.5;
  double cut_nearestz_Y_upper = 19.5;

  double cut_pNueCC = 0.99;
  double cut_pNueCC2 = 0.99;
  double pNueCC  = 0;
  double pNueCC2 = 0;
  bool isPassNhits = false;
  bool isPassAntiMINOS = true;
  bool isPassNearestz = false;
  bool isPassVertex = false;

  //=========================== 
  //== Event Variables
  //=========================== 
  double data_pot;
  double mc_pot;
  double ext_reweight_1view = 1.;
  double ext_reweight_2view = 1.;

  //==========================
  //== Additional functions
  //==========================
  bool IsPassNhits(int nhits_0, int nhits_1);
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
  int best_neutrino_number;

  NueCCAnalyzer();
  ~NueCCAnalyzer();

};

#endif
