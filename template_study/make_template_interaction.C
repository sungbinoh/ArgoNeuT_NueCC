#include "canvas_margin.h"
#include "mylib.h"

using namespace std;

void open_file_data(TString dir, TString histname){

  TString input_file_dir = getenv("ArNeuT_WD");
  TString root_file_path =input_file_dir + "/output/hists_data.root";
  TFile *current_file = new TFile ((root_file_path)) ;
  
  TH1D * current_hist = (TH1D*)gDirectory -> Get("Data_" + histname);
  if(current_hist){
    current_hist -> SetDirectory(0);
    if(debug) cout << "[open_file_data] We have " +  histname << endl;
  }
  else{
    if(debug) cout << "[open_file_data] We do not have " +  histname << endl;
  }
  TH1::AddDirectory(kFALSE);

  maphist["Data" + histname] = current_hist;

  current_file -> Close();
  delete current_file;
}

void open_file_mc(TString dir, TString histname){

  TString input_file_dir = getenv("ArNeuT_WD");
  TString root_file_path =input_file_dir + "/output/hists_mc.root";
  TFile *current_file = new TFile ((root_file_path)) ;

  TH1D * External_NC_cryo = (TH1D*)gDirectory -> Get("External_NC_cryo_" + histname);
  TH1D * External_NC_Minerva = (TH1D*)gDirectory -> Get("External_NC_Minerva_" + histname);
  TH1D * External_NC_Dirt = (TH1D*)gDirectory -> Get("External_NC_Dirt_" + histname);
  TH1D * External_NueCC_cryo = (TH1D*)gDirectory -> Get("External_NueCC_cryo_" + histname);
  TH1D * External_NueCC_Minerva = (TH1D*)gDirectory -> Get("External_NueCC_Minerva_" + histname);
  TH1D * External_NueCC_Dirt = (TH1D*)gDirectory -> Get("External_NueCC_Dirt_" + histname);
  TH1D * External_NumuCC_cryo = (TH1D*)gDirectory -> Get("External_NumuCC_cryo_" + histname);
  TH1D * External_NumuCC_Minerva = (TH1D*)gDirectory -> Get("External_NumuCC_Minerva_" + histname);
  TH1D * External_NumuCC_Dirt = (TH1D*)gDirectory -> Get("External_NumuCC_Dirt_" + histname);
  TH1D * NC = (TH1D*)gDirectory -> Get("NC_" + histname);
  TH1D * NueCC = (TH1D*)gDirectory -> Get("NueCC_" + histname);
  TH1D * NumuCC = (TH1D*)gDirectory -> Get("NumuCC_" + histname);

  
  double xmin = External_NumuCC_Minerva -> GetXaxis() -> GetXmin();
  double xmax = External_NumuCC_Minerva -> GetXaxis() -> GetXmax();
  double Nbin = External_NumuCC_Minerva -> GetNbinsX();
  TH1D * External_NC = new TH1D("", "", Nbin, xmin, xmax);
  if(External_NC_Minerva) External_NC -> Add(External_NC_Minerva);
  if(External_NC_cryo) External_NC -> Add(External_NC_cryo);
  if(External_NC_Dirt) External_NC -> Add(External_NC_Dirt);

  TH1D * External_NueCC = new TH1D("", "", Nbin, xmin, xmax);
  if(External_NueCC_Minerva) External_NueCC -> Add(External_NueCC_Minerva);
  if(External_NueCC_cryo) External_NueCC -> Add(External_NueCC_cryo);
  if(External_NueCC_Dirt) External_NueCC -> Add(External_NueCC_Dirt);

  if(External_NumuCC_cryo) External_NumuCC_Minerva -> Add(External_NumuCC_cryo);
  if(External_NumuCC_Dirt) External_NumuCC_Minerva -> Add(External_NumuCC_Dirt);

  if(External_NC) External_NC -> SetDirectory(0);
  if(External_NueCC) External_NueCC -> SetDirectory(0);
  if(External_NumuCC_Dirt) External_NumuCC_Minerva -> SetDirectory(0);
  if(NC) NC -> SetDirectory(0);
  if(NueCC) NueCC -> SetDirectory(0);
  if(NumuCC) NumuCC -> SetDirectory(0);
  TH1::AddDirectory(kFALSE);

  maphist["External_NC" +  histname] = External_NC;
  maphist["External_NueCC" +  histname] = External_NueCC;
  maphist["External_NumuCC" +  histname] = External_NumuCC_Minerva;
  maphist["NC" +  histname] = NC;
  maphist["NueCC" +  histname] = NueCC;
  maphist["NumuCC" +  histname] = NumuCC;

  current_file -> Close();
  delete current_file;
}

void make_histogram(TString histname, double xmin, double xmax, double rebin){
  /*
  TString this_region = "";
  if(histname.Contains("CR1")) this_region = "CR1";
  if(histname.Contains("CR2")) this_region = "CR2";
  if(histname.Contains("SR2")) this_region = "SR2";
  */
  TFile *current_shape = new TFile("./output/templates/shape_" + histname + "_interaction.root","RECREATE");

  const int N_mc_strings = 6;
  TString mc_strings[N_mc_strings] = {"NC", "NumuCC", "NueCC", "External_NC", "External_NueCC", "External_NumuCC"};
  Int_t colour_array[] = {867, 393, 632, 416, 414, 420};

  for(int i = 0; i < N_mc_strings; i++){
    TString current_histname = "make_histogram" + mc_strings[i] + histname;
    if(maphist[mc_strings[i] + histname]){
      maphist[current_histname] = (TH1D*)maphist[mc_strings[i] + histname] -> Clone();
      maphist[current_histname] -> Rebin(rebin);
      maphist[current_histname] -> SetName(mc_strings[i]);
      maphist[current_histname] -> Write();
      maphist[current_histname] -> SetFillColor(colour_array[i]);
    }
  }

  TH1D * data =  (TH1D*)maphist["Data" + histname] -> Clone();
  data -> Rebin(rebin);
  data -> SetName("data_obs");
  data -> Write();

  TCanvas *c = new TCanvas("", "", 800, 600);
  data -> SetStats(0);
  double max = data -> GetMaximum();
  data -> GetYaxis() -> SetRangeUser(0., max * 1.5);
  data -> Draw("ep");

  TLegend *legend = new TLegend(0.7, 0.8, 0.9, 0.9);
  THStack *stack_h = new THStack("", "");
  for(int i = 0; i < N_mc_strings; i++){
    TString current_histname = "make_histogram" + mc_strings[i] + histname;
    if(maphist[current_histname]){
      stack_h -> Add(maphist[current_histname]);
      legend -> AddEntry(maphist[current_histname], mc_strings[i], "f");
    }
  }

  stack_h -> Draw("histsame");
  legend -> Draw("same");
  data -> Draw("epsame");

  c -> SaveAs("./output/plots/template_" + histname + "_interaction.pdf");

  current_shape -> Close();
}

void submit_template(TString histname, double xmin, double xmax, double rebin){

  open_file_data("", histname);
  open_file_mc("", histname);
  make_histogram(histname, xmin, xmax, rebin);

}

void make_template_interaction(){

  submit_template("pNueCC_CR1", 0., 1., 50.);
  submit_template("pNueCC_CR2", 0., 1., 50.);
  submit_template("pNueCC_SR2", 0., 1., 50.);

  submit_template("vtxz_reco_CR1", 0., 90., 100.);
  submit_template("vtxz_reco_CR2", 0., 90., 100.);
  submit_template("vtxz_reco_SR2", 0., 90., 300.);

}
