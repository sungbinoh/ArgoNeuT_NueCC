#include "canvas_margin.h"
#include "mylib.h"

using namespace std;

void open_file_data(TString dir, TString histname){

  TString input_file_dir = getenv("ArNeuT_WD");
  TString root_file_path =input_file_dir + "/output/hists_data.root";
  if(debug) cout << "[open_file_data] " << root_file_path << endl;
  TFile *current_file = new TFile ((root_file_path)) ;
  gDirectory->cd(dir);
  TH1D * current_hist = (TH1D*)gDirectory -> Get(histname + "_" + dir);
  if(current_hist){
    current_hist -> SetDirectory(0);
    if(debug) cout << "[open_file_data] We have " +  histname + "_" + dir << endl;
  }
  else{
    if(debug) cout << "[open_file_data] We do not have " +  histname + "_" + dir << endl;
  }
  TH1::AddDirectory(kFALSE);

  maphist[histname + dir] = current_hist;

  current_file -> Close();
  delete current_file;
}

void open_file_mc(TString which_vew, TString MC_syst, TString histname){

  TString input_file_dir = getenv("ArNeuT_WD");
  TString root_file_path =input_file_dir + "/output/hists_mc_fit_0p4to0p9_beamflux_SetNanWeightTo1.root";
  TFile *current_file = new TFile ((root_file_path)) ;
  TString dir = which_vew + "_" + MC_syst;
  gDirectory->cd(dir);
  TH1D * current_hist = (TH1D*)gDirectory -> Get(histname + "_" + which_vew + "_" + MC_syst);
  if(current_hist){
    current_hist -> SetDirectory(0);
    if(debug) cout << "[open_file_mc] We have " +  histname + "_" + which_vew + "_" + MC_syst << endl;
  }
  else{
    if(debug) cout << "[open_file_mc] We do not have " +  histname + "_" + which_vew + "_" + MC_syst << endl;
  }
  TH1::AddDirectory(kFALSE);

  maphist[histname + MC_syst] = current_hist;

  current_file -> Close();
  delete current_file;
}

void make_histogram(TString histname, int N_bin, double binx[]){

  TString output_file_dir = getenv("ArNeuT_WD");
  output_file_dir = output_file_dir + "/output/templates/shape_" + histname + ".root";
  if(debug) cout << "[make_histogram] output_file_dir : " << output_file_dir << endl;
  TFile *current_shape = new TFile(output_file_dir,"RECREATE");
  current_shape -> cd();
  maphist[histname + "Data_centralrebin"] = (TH1D*)maphist[histname + "Data_central"] -> Rebin(N_bin - 1, histname + "Data_centralrebin", binx);
  maphist[histname + "Data_centralrebin"] -> SetName("data_obs");
  maphist[histname + "Data_centralrebin"] -> Write();

  for(int i = 0; i < N_MC_category; i++){
    TString this_hist_name = histname + MC_category[i];
    maphist[this_hist_name + "_centralrebin"] = (TH1D*)maphist[this_hist_name + "_central"] -> Rebin(N_bin - 1, this_hist_name + "_centralrebin", binx);
    maphist[this_hist_name + "_centralrebin"] -> SetName(MC_category[i]);
    maphist[this_hist_name + "_centralrebin"] -> Write();
    
    for(int j = 0; j < N_syst_category; j++){
      TString this_hist_name = histname + MC_category[i] + "_" + systematics_category[j];
      TString this_hist_name_Up = histname + MC_category[i] + "_" + systematics_category[j] + "_Up";
      TString this_hist_name_Down = histname + MC_category[i] + "_" + systematics_category[j] + "_Down";

      maphist[this_hist_name_Up + "rebin"] = (TH1D*)maphist[this_hist_name_Up] -> Rebin(N_bin - 1, this_hist_name_Up + "rebin", binx);
      maphist[this_hist_name_Up + "rebin"] -> SetName(MC_category[i] + "_" + systematics_category[j] + "Up");
      maphist[this_hist_name_Up + "rebin"] -> Write();

      maphist[this_hist_name_Down + "rebin"] = (TH1D*)maphist[this_hist_name_Down] -> Rebin(N_bin - 1, this_hist_name_Down + "rebin",binx);
      maphist[this_hist_name_Down + "rebin"] -> SetName(MC_category[i] + "_" + systematics_category[j] + "Down");
      maphist[this_hist_name_Down + "rebin"] -> Write();
    }
  }

  //current_shape
  current_shape -> Close();
}

void Draw_updown_shapes(TString histname){
  
  TCanvas *c = new TCanvas("", "", 600, 800);
  gStyle->SetOptStat(0);
  //c -> SetLogy();
  TString output_file_dir = getenv("ArNeuT_WD");
  output_file_dir = output_file_dir + "/output/plots/updown_plots/";
  for(int i = 0; i < N_MC_category; i++){
    for(int j = 0; j < N_syst_category; j++){
      TString this_hist_name_central = histname + MC_category[i] + "_centralrebin";
      TString this_hist_name_Up = histname+ MC_category[i] + "_" + systematics_category[j] + "_Uprebin";
      TString this_hist_name_Down = histname+ MC_category[i] + "_" + systematics_category[j] + "_Downrebin";

      maphist[this_hist_name_central] -> GetXaxis() -> SetTitle("CVN score (2 view)");
      maphist[this_hist_name_central] -> GetYaxis() -> SetTitle("Events");
      
      double max_central = 0.;
      for(int k = 1; k <= maphist[this_hist_name_central] -> GetNbinsX(); k++){
	double this_content =  maphist[this_hist_name_central] -> GetBinContent(k);
	if(this_content > max_central) max_central = this_content;
      }
      gStyle->SetLineWidth(2);
      maphist[this_hist_name_central] -> GetYaxis() -> SetRangeUser(0., max_central * 2.0);
      maphist[this_hist_name_central] -> SetLineColor(kBlack);
      maphist[this_hist_name_central] -> SetLineWidth(3);
      maphist[this_hist_name_central] -> Draw("hist");

      maphist[this_hist_name_Up] -> SetLineColor(kRed);
      maphist[this_hist_name_Up] -> SetLineStyle(2);
      maphist[this_hist_name_Up] -> SetLineWidth(3);
      maphist[this_hist_name_Up] -> Draw("histsame");

      maphist[this_hist_name_Down] -> SetLineColor(kBlue);
      maphist[this_hist_name_Down] -> SetLineStyle(5);
      maphist[this_hist_name_Down] -> SetLineWidth(3);
      maphist[this_hist_name_Down] -> Draw("histsame");

      TLegend *this_legend = new TLegend(0.12, 0.7, 0.4, 0.89);
      this_legend -> SetLineColor(kWhite);
      this_legend -> AddEntry(maphist[this_hist_name_central], "central", "l");
      this_legend -> AddEntry(maphist[this_hist_name_Up], "Syst. Up", "l");
      this_legend -> AddEntry(maphist[this_hist_name_Down], "Syst. Down", "l");
      this_legend -> Draw("same");

      TLatex MC_latex, Syst_latex;
      MC_latex.SetNDC();
      Syst_latex.SetNDC();
      MC_latex.SetTextSize(0.035);
      Syst_latex.SetTextSize(0.035);
      Syst_latex.DrawLatex(0.10, 0.91, "#font[62]{" + MC_category[i] + "}  #font[42]{#it{#scale[0.8]{" + systematics_names[j] + "}}}");

      c -> SaveAs(output_file_dir + histname + "_" + MC_category[i] + "_" + systematics_category[j] + ".pdf");
    }
  }

}

void Draw_central_Data_vs_mc(TString histname){

  TCanvas *c = new TCanvas("", "", 600, 800);
  //c -> SetLogy();
  TString this_data = histname + "Data_centralrebin";
  maphist[this_data] -> GetXaxis() -> SetTitle("CVN score (2 view)");
  maphist[this_data] -> GetYaxis() -> SetRangeUser(1.0, 140.);
  maphist[this_data] -> GetYaxis() -> SetTitle("Events");
  gStyle->SetOptTitle(0);
  maphist[this_data] -> Draw("ep");

  Int_t colour_array[] = {867, 393, 420, 416, 414, 632};
  THStack *this_stack = new THStack("", "Stacked_" + histname);
  TLegend *this_legend = new TLegend(0.5, 0.7, 0.7, 0.9);
  for(int i = 0; i < N_MC_category; i++){
    TString this_mc = histname + MC_category[i] + "_centralrebin";
    maphist[this_mc] -> SetFillColor(colour_array[i]);
    this_stack -> Add(maphist[this_mc]);
    this_legend -> AddEntry(maphist[this_mc], MC_category[i], "f");
  }
  this_stack -> Draw("histsame");
  maphist[this_data] -> Draw("epsame");
  this_legend -> Draw("same");
  
  TString output_file_dir = getenv("ArNeuT_WD");
  output_file_dir = output_file_dir + "/output/plots/updown_plots/";
  c -> SaveAs(output_file_dir + histname + "_stacked.pdf");


}

void open_files(TString histname,TString which_view){

  maphist.clear();
  map_syst_array.clear();
  mapcanvas.clear();
  map_asym_gr.clear();

  unsigned int N_bin = map_bin_vector[histname].size();
  if(debug) cout << "[open_files] N_bin : " << N_bin << endl;
  double current_bins[100];
  for(unsigned int i_bin = 0; i_bin < N_bin; i_bin++){
    current_bins[i_bin] = map_bin_vector[histname].at(i_bin);
  }

  open_file_data("Data_central", histname);
  for(int i = 0; i < N_syst; i++){
    for(int j = 0; j < N_MC_category; j++){
      TString MC_syst = MC_category[j] + "_" + systematics[i];
      //cout << "MC_syst : " << MC_syst << endl;
      open_file_mc(which_view, MC_syst, histname);
    }
  }

  make_histogram(histname, N_bin, current_bins);
  Draw_updown_shapes(histname);
  Draw_central_Data_vs_mc(histname);
}

void open_binning_file(TString filename, TString which_view){

  cout << "[open_binning_file] start to open binngin file : " << filename << endl;
  TString WORKING_DIR = getenv("ArNeuT_WD");
  TString binning_file_path=WORKING_DIR+"/data/v1/binning/"+filename;
  ifstream data_file;
  data_file.open(binning_file_path);

  char line[500];
  if(data_file.is_open()){
    while(!data_file.eof()){
      data_file.getline(line, 500);
      if(debug) cout << line << endl;
      TString this_line = line;
      if(this_line.Contains("#")) continue;

      TObjArray *tx = this_line.Tokenize("\t");
      int N_line_part = tx -> GetEntries();
      if(N_line_part < 1) continue;
      cout << "[open_binning_file] histname : " << ((TObjString *)(tx->At(0)))->String() << endl;
      cout << "[open_binning_file] binning : " << ((TObjString *)(tx->At(1)))->String() << endl;
      
      // -- saving current histname for mapping : TString && clear the map vector
      TString current_histname = ((TObjString *)(tx->At(0)))->String();
      if(debug) cout << "[open_binning_file] current_histname : " << current_histname << endl;
      map_bin_vector[current_histname].clear();

      // -- making vector<double> for binning
      TString current_binning = ((TObjString *)(tx->At(1)))->String();
      TObjArray *binning_token = current_binning.Tokenize(", ");
      for(int i_bin_part = 0; i_bin_part < binning_token->GetEntries() - 1; i_bin_part++){
        TString current_bin_value = ((TObjString *)(binning_token->At(i_bin_part)))->String();
        if(i_bin_part == 0){
          current_bin_value.Remove(0,1);
        }
        if(debug) cout << current_bin_value << " | " << endl;
        double current_bin_double = current_bin_value.Atof();
        map_bin_vector[current_histname].push_back(current_bin_double);
      }

      open_files(current_histname, which_view);
      map_bin_vector.clear();
    }
  }
  data_file.close();

}

void make_template(){

  open_binning_file("pNueCC2_binning.txt", "TwoView");
}
