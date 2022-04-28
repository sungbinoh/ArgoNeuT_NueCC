#ifndef NueCCAnalyzer_h
#define NueCCAnalyzer_h

#include "AnalyzerCore.h"

class NueCCAnalyzer : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEvent();

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

  NueCCAnalyzer();
  ~NueCCAnalyzer();

};

#endif
