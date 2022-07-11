#ifndef MCCorrection_h
#define MCCorrection_h

#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "TFile.h"
#include "TString.h"
#include "TRegexp.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"

#include "TDirectoryHelper.h"
#include "TRandom3.h"

using namespace std;

class MCCorrection{

public:

  MCCorrection();
  ~MCCorrection();

  TDirectory *histDir;
  void ReadHistograms();

  bool IsData;
  void SetIsData(bool b);

  bool IgnoreNoHist;

  double BeamFlux_SF(int nu_PID, double nu_E, int sys);
  double External_bkg_corr(TString pNueCC_str, double pNueCC);
  std::map< TString, TH1D* > map_hist_BeamFlux;
  std::map< TString, TH1D* > map_hist_ExtCorr;

};

#endif
