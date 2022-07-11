#include "MCCorrection.h"

MCCorrection::MCCorrection() :
  IgnoreNoHist(false)
{

  histDir = TDirectoryHelper::GetTempDirectory("MCCorrection");

}

void MCCorrection::ReadHistograms(){

  TString datapath = getenv("DATA_DIR");

  TDirectory* origDir = gDirectory;

  //==== Beam flux
  TString BeamFlux_path = datapath+"/Beamflux/";
  //cout << "[MCCorrection::ReadHistograms] BeamFlux_path  : " << BeamFlux_path << endl;
  string elline;
  ifstream in(BeamFlux_path+"histmap.txt");
  while(getline(in,elline)){
    std::istringstream is( elline );

    TString tstring_elline = elline;
    if(tstring_elline.Contains("#")) continue;
    //cout << "[MCCorrection::ReadHistograms] tstring_elline : " << tstring_elline << endl;
    TString a,b,c,d,e,f;
    is >> a; // Beam,
    is >> b; // SF, Eff
    is >> c; // <NuType>
    is >> d; // <rootfilename>
    is >> e; // <histname>
    is >> f; // Class
    TFile *file = new TFile(BeamFlux_path + d);
    //cout << "BeamFlux_path + d : " << BeamFlux_path + d << endl;
    //cout << "a : " << a << ", b : " << b << ", c : << " << c << ", d : " << d << ", e : " << e << ", f : " << f << endl;

    if(f=="TH1D"){
      histDir->cd();
      map_hist_BeamFlux[a + "_" + b + "_" + c] = (TH1D *)file -> Get(e) -> Clone();
    }
  }

  //==== External Bkg
  TString External_bkg_path = datapath+"/External/";
  ifstream in_External_bkg(External_bkg_path + "histmap.txt");
  while(getline(in_External_bkg,elline)){
    std::istringstream is( elline );

    TString tstring_elline = elline;
    if(tstring_elline.Contains("#")) continue;
    TString a,b,c,d,e,f;
    is >> a; // Ext_Corr
    is >> b; // SF
    is >> c; // pNueCC, pNueCC2
    is >> d; // <rootfilename>
    is >> e; // <histname>
    is >> f; // Class
    TFile *file = new TFile(External_bkg_path + d);
    if(f=="TH1D"){
      histDir->cd();
      map_hist_ExtCorr[a + "_" + b + "_" + c] = (TH1D *) file -> Get(e) -> Clone();
    }
  }

  cout << "[MCCorrection::ReadHistograms] map_hist_BeamFlux :" << endl;
  for(std::map< TString, TH1D* >::iterator it = map_hist_BeamFlux.begin(); it != map_hist_BeamFlux.end(); it++){
    cout << "[MCCorrection::ReadHistograms] key = " << it -> first << endl;
  }
  cout << "[MCCorrection::ReadHistograms] map_hist_ExtCorr :" << endl;
  for(std::map< TString, TH1D* >::iterator it = map_hist_ExtCorr.begin(); it != map_hist_ExtCorr.end(); it++){
    cout << "[MCCorrection::ReadHistograms] key = " << it -> first << endl;
  }

  cout << "[MCCorrection::ReadHistograms] END" << endl;
}

MCCorrection::~MCCorrection(){

}

void MCCorrection::SetIsData(bool b){
  IsData = b;
}

double MCCorrection::BeamFlux_SF(int nu_PID, double nu_E, int sys){

  double value = 1.;
  double error = 0.;
  TString this_nu_type;
  if(nu_PID == 12) this_nu_type = "nue";
  else if(nu_PID == -12) this_nu_type = "anue";
  else if(nu_PID == 14) this_nu_type = "numu";
  else if(nu_PID == -14) this_nu_type = "anumu";

  TH1D *this_hist = map_hist_BeamFlux["Beam_SF_" + this_nu_type];
  if(!this_hist){
    if(IgnoreNoHist) return 1.;
    else{
      cerr << "[MCCorrection::MuonReco_SF] No "<< "Beam_SF_" + this_nu_type << endl;
      exit(EXIT_FAILURE);
    }
  }

  int this_bin = this_hist->FindBin(nu_E);
  value = this_hist->GetBinContent(this_bin);
  error = this_hist->GetBinError(this_bin);

  return value+double(sys)*error;

}

double MCCorrection::External_bkg_corr(TString pNueCC_str, double pNueCC){

  TH1D *this_hist = map_hist_ExtCorr["Ext_Corr_SF_" + pNueCC_str];
  if(!this_hist){
    if(IgnoreNoHist) return 1.;
    else{
      cerr << "[MCCorrection::MuonReco_SF] No "<< "Ext_Corr_SF_" + pNueCC_str << endl;
      exit(EXIT_FAILURE);
    }
  }

  int this_bin = this_hist->FindBin(pNueCC);
  double value = this_hist->GetBinContent(this_bin);

  return value;
}
