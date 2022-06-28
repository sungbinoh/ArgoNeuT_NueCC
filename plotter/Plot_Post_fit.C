#include "canvas_margin.h"
#include "mylib.h"

void openfile(TString histname, TString which_fit){
  TString WORKING_DIR = getenv("ArNeuT_WD");
  //TString filename = WORKING_DIR + "/output/fits/fitDiagnostics_fit_result.root";
  //TString filename = WORKING_DIR + "/output/fits/fitDiagnostics_fit_result_NoGenieExtSignal.root";
  TString filename = WORKING_DIR + "/output/fits/fitDiagnostics_fit_result_NoGenieExt.root";

  TFile *current_file = new TFile ((filename)) ;
  gDirectory->cd(which_fit);
  gDirectory->cd("bin1");
  
  for(int i = 0; i < N_MC; i++){
    TH1F* this_hist = (TH1F*)gDirectory -> Get(MC_category[i]);
    if(this_hist){
      this_hist -> SetDirectory(0);
    }
    TH1::AddDirectory(kFALSE);
    mapTH1F[histname + MC_category[i] + which_fit] = this_hist;
  }

  TH1F *total = (TH1F*)gDirectory -> Get("total");
  mapTH1F[histname + which_fit + "total"] = total;

  TGraphAsymmErrors * current_data = (TGraphAsymmErrors*) gDirectory -> Get("data");
  map_asym_gr[histname + "data" + which_fit] = current_data;

  current_file -> Close();
  delete current_file;
}

void make_histogram(TString histname, TString which_fit, int N_bin, double binx[]){

  TString nameofhistogram = histname + "_" + which_fit;
  TString pad1 = nameofhistogram;
  TString pad2 = nameofhistogram;
  TString canvas = nameofhistogram;
  TString hstack = nameofhistogram;
  TString legend = nameofhistogram;
  TString func = nameofhistogram;
  TString clone = nameofhistogram;
  TString line = nameofhistogram;
  pad1.Insert(0, "pad1_");
  pad2.Insert(0, "pad2_");
  canvas.Insert(0, "c_");
  hstack.Insert(0, "hs_");
  legend.Insert(0, "legend_");
  func.Insert(0, "ratio_");
  clone.Insert(0, "h3_");
  line.Insert(0, "l_");

  mapcanvas[canvas] = new TCanvas(canvas,"",800,800);
  canvas_margin(mapcanvas[canvas]);
  gStyle -> SetOptStat(1111);

  ////////////////////////////////////
  // == Pad 1
  ////////////////////////////////////
  mappad[pad1] = new TPad("", "", 0, 0.0, 1, 1);
  mappad[pad1] -> SetTopMargin( 0.05 );
  mappad[pad1] -> SetBottomMargin( 0.10 );
  mappad[pad1] -> SetLeftMargin( 0.15 );
  mappad[pad1] -> SetRightMargin( 0.03 );
  mappad[pad1] -> Draw();
  mappad[pad1] -> cd();
  //mappad[pad1] -> SetLogy();

  maplegend[legend] = new TLegend(0.20, 0.60, 0.55, 0.92);

  if(debug) cout << "1" << endl;


  TH1F * pad1_template = new TH1F("", "", N_bin-1, binx);
  gStyle->SetOptTitle(0);
  gStyle->SetLineWidth(2);

  const int N_mc_strings = 6;
  TString mc_strings[N_mc_strings] = {"NC", "NumuCC", "External_NC", "External_NueCC", "External_NumuCC", "NueCC"};
  Int_t colour_array[] = {867, 393, 420, 416, 414, 632};

  maphstack[hstack] = new THStack(hstack, "Stacked_" + nameofhistogram);
  TH1F * bkg_sum = new TH1F("", "", N_bin-1, binx);

  for(int i = 0; i < N_mc_strings; i++){
    TString this_hist_str = histname + mc_strings[i] + which_fit;
    if(mapTH1F[this_hist_str]){
      mapTH1F[this_hist_str + "template"] = new TH1F(this_hist_str + "template", this_hist_str + "template", N_bin-1, binx);
      for(int i_bin = 1; i_bin < N_bin; i_bin++){
        double current_content = mapTH1F[this_hist_str] -> GetBinContent(i_bin);
        double current_error = mapTH1F[this_hist_str] -> GetBinError(i_bin);
        mapTH1F[this_hist_str + "template"]  -> SetBinContent(i_bin, current_content);


        double bkg_sum_content = bkg_sum -> GetBinContent(i_bin);
        double bkg_sum_error = bkg_sum -> GetBinError(i_bin);
        bkg_sum -> SetBinContent(i_bin, bkg_sum_content + current_content);
	bkg_sum -> SetBinError(i_bin, bkg_sum_error + current_error);
      }

      mapTH1F[this_hist_str + "template"] -> SetFillColor(colour_array[i]);
      mapTH1F[this_hist_str + "template"] -> SetLineColor(colour_array[i]);
      maphstack[hstack] -> Add(mapTH1F[this_hist_str + "template"]);
  
      maplegend[legend] -> AddEntry(mapTH1F[this_hist_str + "template"], mc_strings[i], "lf");
    }
  }

  // == Total MC
  TString this_total_str = histname + which_fit + "total";
  mapTH1F[this_total_str + "template"] = new TH1F(this_total_str + "template", this_total_str + "template", N_bin-1, binx);
  for(int i_bin = 1; i_bin < N_bin; i_bin++){
    double current_content = mapTH1F[this_total_str] -> GetBinContent(i_bin);
    double current_error = mapTH1F[this_total_str] -> GetBinError(i_bin);
    mapTH1F[this_total_str + "template"] -> SetBinContent(i_bin, current_content);
    mapTH1F[this_total_str + "template"] -> SetBinError(i_bin, current_error);
  }
  mapTH1F[this_total_str + "template"] -> SetFillColor(kBlack);
  mapTH1F[this_total_str + "template"] -> SetFillStyle(3013);
  mapTH1F[this_total_str + "template"] -> SetMarkerSize(0);
  mapTH1F[this_total_str + "template"] -> SetLineWidth(0);
    
  // == Data
  TH1F * data_hist = new TH1F("", "", N_bin-1, binx);
  double max_data = 0.;
  const int N_points = N_bin - 1;
  double data_y[N_points], data_x[N_points];
  double data_ey_high[N_points], data_ey_low[N_points];
  double data_ex_high[N_points], data_ex_low[N_points];
  for(int i_point = 0; i_point < N_points; i_point++){
    double current_x, current_y;
    double current_ey_high, current_ey_low;
    map_asym_gr[histname + "data" + which_fit] -> GetPoint(i_point, current_x, current_y);
    current_ey_high = map_asym_gr[histname + "data" + which_fit] -> GetErrorYhigh(i_point);
    current_ey_low = map_asym_gr[histname + "data" + which_fit] -> GetErrorYlow(i_point);
    data_y[i_point] = current_y;
    data_ey_high[i_point] = current_ey_high;
    data_ey_low[i_point] = current_ey_low;
    data_hist -> SetBinContent(i_point + 1, current_y);
    if(current_y > max_data) max_data = current_y;
  }
  for(int i_x = 0; i_x < N_points; i_x++){
    double current_ex = (binx[i_x + 1] - binx[i_x]) / 2.0;
    double current_x = binx[i_x] + current_ex;

    data_x[i_x] = current_x;
    data_ex_high[i_x] = current_ex;
    data_ex_low[i_x] =current_ex;
  }

  TGraphAsymmErrors * data_gr = new TGraphAsymmErrors(N_points, data_x, data_y, data_ex_low, data_ex_high, data_ey_low, data_ey_high);

  // == Draw Pad 1
  pad1_template -> Draw("hist");
  pad1_template -> GetYaxis()->SetLabelSize(0.03);
  pad1_template -> GetYaxis()->SetTitleSize(0.07);
  pad1_template -> GetYaxis()->SetTitleOffset(1.02);
  pad1_template -> GetXaxis()->SetLabelSize(0.03);
  pad1_template -> GetXaxis() -> SetTitle("CVN score (2 veiw)");
  pad1_template -> GetYaxis() -> SetRangeUser(0., 200.);
  //pad1_template -> GetYaxis() -> SetRangeUser(0.1, max_data * 1000.); // logy
  pad1_template -> GetYaxis() -> SetTitle("Events");
  pad1_template -> SetStats(0);
  pad1_template -> Draw("histsame");

  maphstack[hstack] -> Draw("histsame");

  bkg_sum -> SetFillColor(kBlack);
  bkg_sum -> SetFillStyle(3013);
  bkg_sum -> SetMarkerSize(0);;
  //bkg_sum -> Draw("e2same");;
  mapTH1F[this_total_str + "template"] -> Draw("e2same");

  maplegend[legend] -> AddEntry(mapTH1F[this_total_str + "template"], "Stat.+syst. uncert.", "f");

  data_gr -> SetMarkerStyle(20);
  data_gr -> SetMarkerColor(kBlack);
  data_gr -> SetMarkerSize(1.3);
  data_gr -> SetLineWidth(2);
  data_gr -> Draw("ezpsame");

  maplegend[legend] -> AddEntry(data_gr, "Observed", "lp");

  maplegend[legend] -> SetFillColor(kWhite);
  maplegend[legend] -> SetLineColor(kWhite);
  maplegend[legend] -> SetBorderSize(1);
  maplegend[legend] -> SetFillStyle(1001);
  maplegend[legend] -> SetShadowColor(0);
  maplegend[legend] -> SetEntrySeparation(0.3);
  maplegend[legend] -> Draw("same");

  gPad->RedrawAxis();

  ////////////////////////////////////
  // == Latex
  ////////////////////////////////////
  mapcanvas[canvas] -> cd();
  TLatex latex_ArgoNeuT, latex_data_POT;
  latex_ArgoNeuT.SetNDC();
  latex_data_POT.SetNDC();
  latex_ArgoNeuT.SetTextSize(0.035);
  latex_data_POT.SetTextSize(0.035);
  latex_ArgoNeuT.DrawLatex(0.15, 0.96, "#font[62]{ArgoNeuT} #font[42]{#it{#scale[0.8]{Preliminary}}}");
  latex_data_POT.DrawLatex(0.65, 0.96, "RHC 1.25 #times 10^{20} POT");

  ////////////////////////////////////
  // == Save as png or pdf
  ////////////////////////////////////
  TString pdfname;
  TString WORKING_DIR = getenv("ArNeuT_WD");
  WORKING_DIR = WORKING_DIR + "/output/plots/fit/";
  pdfname = WORKING_DIR + nameofhistogram + ".pdf";
  mapcanvas[canvas] -> SaveAs(pdfname);

}

void open_files(TString histname){

  mapTH1F.clear();
  map_asym_gr.clear();

  if(debug) cout << "[[draw_histogram]] histname : " << histname << endl;
  unsigned int N_bin = map_bin_vector[histname].size();
  double current_bins[100];
  for(unsigned int i_bin = 0; i_bin < N_bin; i_bin++){
    current_bins[i_bin] = map_bin_vector[histname].at(i_bin);
  }

  openfile(histname, "shapes_prefit");
  openfile(histname, "shapes_fit_s");
  make_histogram(histname, "shapes_prefit", N_bin, current_bins);
  make_histogram(histname, "shapes_fit_s", N_bin, current_bins);

}

void open_binning_file(TString filename){

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

      open_files(current_histname);
      map_bin_vector.clear();
    }
  }
  data_file.close();

}

void Plot_Post_fit(){
  open_binning_file("pNueCC2_binning.txt");
}
