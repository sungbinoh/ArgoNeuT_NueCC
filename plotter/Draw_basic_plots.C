#include "canvas_margin.h"
#include "mylib.h"
#include <sstream>

using namespace std;
bool draw_Data_vs_External = false;

void open_file_data(TString dir, TString histname){

  TString input_file_dir = getenv("ArNeuT_WD");
  TString root_file_path =input_file_dir + "/output/hists_data.root";
  TFile *current_file = new TFile ((root_file_path)) ;
  gDirectory->cd(dir);

  TH1D * current_hist = (TH1D*)gDirectory -> Get(histname + "_" + dir);
  //TH1D * current_hist = (TH1D*)gDirectory -> Get("Data_" + histname);
  if(current_hist){
    current_hist -> SetDirectory(0);
    if(debug) cout << "[open_file_data] We have " +  histname << endl;
  }
  else{
    if(debug) cout << "[open_file_data] We do not have " +  histname << endl;
  }
  TH1::AddDirectory(kFALSE);
  
  //maphist[histname + "_" + dir] = current_hist;
  cout << histname + "_"+ dir << endl;
  maphist[histname + "_" + dir] = current_hist;

  current_file -> Close();
  delete current_file;
}

void open_file_mc(TString which_view, TString dir, TString histname){

  TString input_file_dir = getenv("ArNeuT_WD");
  //TString root_file_path =input_file_dir + "/output/hists_mc.root";
  TString root_file_path =input_file_dir + "/output/hists_mc_fit_0p7to0p9.root";
  TFile *current_file = new TFile ((root_file_path)) ;

  for(int i = 0; i < N_MC; i++){
    TString this_dir_str = which_view+ "_" + MC_category[i] + "_" + dir;
    TString this_hist_str = histname + "_" + which_view + "_" + MC_category[i] + "_" +dir;
    gDirectory->cd(this_dir_str);
    TH1D* this_hist = (TH1D*)gDirectory -> Get(this_hist_str);
    if(this_hist) this_hist -> SetDirectory(0);
    TH1::AddDirectory(kFALSE);
    maphist[this_hist_str] = this_hist;
    cout << "[open_file_mc] this_hist_str : " << this_hist_str << endl;
    gDirectory->cd("../");
  }

  current_file -> Close();
  delete current_file;
}

void Draw_stacked_plot(TString which_view, TString histname, double xmin, double xmax, double rebin){

  TString title_y = "Events/bin";
  //TString nameofhistogram = histname + "_" + dir;
  TString nameofhistogram = histname + "_" + which_view;
  TString canvas = nameofhistogram;
  TString pad1 = nameofhistogram;
  TString pad2 = nameofhistogram;
  TString hstack = nameofhistogram;
  TString legend = nameofhistogram;
  TString line = nameofhistogram;
  canvas.Insert(0, "c_");
  pad1.Insert(0, "pad1_");
  pad2.Insert(0, "pad2_");
  hstack.Insert(0, "hs_");
  legend.Insert(0, "legend_");
  line.Insert(0, "l_");

  mapcanvas[canvas] = new TCanvas(canvas,"",800,800);
  canvas_margin(mapcanvas[canvas]);
  gStyle -> SetOptStat(1111);

  ////////////////////////////////////
  // == Pad 1
  ////////////////////////////////////
  mappad[pad1] = new TPad("", "", 0, 0.25, 1, 1);
  mappad[pad1] -> SetTopMargin( 0.07 );
  mappad[pad1] -> SetBottomMargin( 0.05 );
  mappad[pad1] -> SetLeftMargin( 0.15 );
  mappad[pad1] -> SetRightMargin( 0.03 );
  mappad[pad1] -> Draw();
  mappad[pad1] -> cd();
  //mappad[pad1] -> SetLogy();

  // == Define histograms into maps
  cout << histname + "_Data_central" << endl;
  TH1D * data =  (TH1D*)maphist[histname + "_Data_central"] -> Clone();

  const int N_mc_strings = 6;
  TString mc_strings[N_mc_strings] = {"NC", "NumuCC", "External_NC", "External_NueCC", "External_NumuCC", "NueCC"};
  for(int i = 0; i < N_mc_strings; i++){
    TString this_hist_name = nameofhistogram + "_" + mc_strings[i] + "_central";
    cout << "[Draw_stacked_plot] this_hist_name : " << this_hist_name << endl;
    maphist["Draw_stacked_plot" + which_view + mc_strings[i] + nameofhistogram] = (TH1D*)maphist[this_hist_name] -> Clone();
  }

  // == Rebin data and get y-maximum value
  data -> Rebin(rebin);
  double data_max = data -> GetMaximum();

  // == Set a template for Pad 1
  TH1D *pad1_template = new TH1D("", "", 1, xmin, xmax);
  gStyle->SetOptTitle(0);
  gStyle->SetLineWidth(3);
  pad1_template -> SetStats(0);
  pad1_template -> GetXaxis() -> SetTitle(nameofhistogram);
  pad1_template -> GetXaxis() -> SetLabelSize(0);
  pad1_template -> GetXaxis() -> SetTitleSize(0);
  pad1_template -> GetYaxis() -> SetLabelSize(0.05);
  pad1_template -> GetYaxis() -> SetTitleSize(0.07);
  pad1_template -> GetYaxis() -> SetTitleOffset(1.02);
  pad1_template -> GetYaxis() -> SetTitle("Events");
  //pad1_template -> GetYaxis() -> SetRangeUser(1., data_max * 100.); // == logy
  pad1_template -> GetYaxis() -> SetRangeUser(0., 150.); // == pNueCC [0.9, 1.0]
  pad1_template -> Draw("hist");

  // == Define legend
  maplegend[legend] = new TLegend(0.60, 0.70, 0.97, 0.90);
  maplegend[legend] -> SetFillColor(kWhite);
  maplegend[legend] -> SetLineColor(kWhite);
  maplegend[legend] -> SetBorderSize(1);
  maplegend[legend] -> SetFillStyle(1001);
  maplegend[legend] -> SetShadowColor(0);
  maplegend[legend] -> SetEntrySeparation(0.3);

  // == Define HStack and MC histgram colors
  maphstack[hstack] = new THStack(hstack, "Stacked_" + nameofhistogram);
  //Int_t colour_array[] = {867, 393, 632, 416, 414, 420};
  Int_t colour_array[] = {867, 393, 420, 416, 414, 632};

  // == Rebin, set color, stack, and add to legend MC histograms
  for(int i = 0; i < N_mc_strings; i++){
    TString this_hist_name = "Draw_stacked_plot" + which_view + mc_strings[i] + nameofhistogram;
    if(maphist[this_hist_name]){
      if(debug) cout << "[Draw_stacked_plot] Draw_stacked_plot" +  mc_strings[i] + nameofhistogram << endl;
      maphist[this_hist_name] -> Rebin(rebin);
      maphist[this_hist_name] -> SetLineColor(colour_array[i]);
      maphist[this_hist_name] -> SetFillColor(colour_array[i]);
      maphstack[hstack] -> Add(maphist[this_hist_name]);
      maplegend[legend]->AddEntry(maphist[this_hist_name], mc_strings[i], "f");
    }
  }
  // == Settings for data points
  data -> SetLineColor(kBlack);
  data -> SetMarkerColor(kBlack);
  data -> SetMarkerSize(2);
  data -> SetLineWidth(2);

  maplegend[legend]->AddEntry(data, "Observed", "lp");

  // == Draw
  maphstack[hstack] -> Draw("histsame");
  data -> Draw("epsame");
  maplegend[legend] -> Draw("same");
  gPad->RedrawAxis();

  data -> Draw("epsame");

  ////////////////////////////////////
  // == Pad 2
  ////////////////////////////////////
  if(debug) cout << "[Draw_stacked_plot] Starting Pad 2" << endl;
  mapcanvas[canvas] -> cd();
  mappad[pad2] = new TPad(pad2, "", 0, 0, 1, 0.25);
  mappad[pad2] -> SetTopMargin( 0.05 );
  mappad[pad2] -> SetBottomMargin( 0.4 );
  mappad[pad2] -> SetLeftMargin( 0.15 );
  mappad[pad2] -> SetRightMargin( 0.03 );
  mappad[pad2] -> Draw();
  mappad[pad2] -> cd();

  TString name_x = histname;

  TH1D * pad2_template = new TH1D("", "", 1, xmin, xmax);
  gStyle->SetOptTitle(0);
  gStyle->SetLineWidth(2);
  pad2_template -> Draw("hist");
  pad2_template -> SetTitle("");
  pad2_template -> SetLineColor(kWhite);
  pad2_template -> GetXaxis() -> SetTitle(name_x);
  pad2_template -> GetXaxis() -> SetTitleSize(0.15);
  pad2_template -> GetXaxis() -> SetLabelSize(0.125);
  if(draw_Data_vs_External){
    pad2_template -> GetYaxis() -> SetTitle("#frac{Obs. - non-Ext. MC}{External}");
    pad2_template -> GetYaxis() -> SetTitleSize(0.10);
  }
  else{
    pad2_template -> GetYaxis() -> SetTitle("#frac{Obs.}{Pred.}");
    pad2_template -> GetYaxis() -> SetTitleSize(0.15);
  }  
  pad2_template -> GetYaxis() -> SetTitleOffset(0.4);
  pad2_template -> GetYaxis() -> SetLabelSize(0.09);
  pad2_template -> GetYaxis() -> SetNdivisions(505);
  pad2_template -> GetYaxis() -> SetRangeUser(0.0, 2.0);
  pad2_template -> SetStats(0);
  pad2_template -> Draw("histsame");

  // == Make MC sum and data/mc shape
  TH1D * mc_sum = (TH1D*)maphist["Draw_stacked_plot" + which_view + mc_strings[4] + nameofhistogram] -> Clone();
  TH1D * data_mc_ratio = (TH1D*)data -> Clone();

  if(draw_Data_vs_External){
    for(int i = 0; i < N_mc_strings; i++){
      TString this_hist_name = "Draw_stacked_plot" + which_view + mc_strings[i] + nameofhistogram;
      if(!mc_strings[i].Contains("External")) data_mc_ratio -> Add(maphist[this_hist_name], -1);
    }
    mc_sum -> Add(maphist["Draw_stacked_plot" + which_view + mc_strings[2] + nameofhistogram]);
    mc_sum -> Add(maphist["Draw_stacked_plot" + which_view + mc_strings[3] + nameofhistogram]);
    data_mc_ratio -> Divide(mc_sum);
  }
  else{
    for(int i = 0; i < N_mc_strings; i++){
      TString this_hist_name = "Draw_stacked_plot" + which_view + mc_strings[i] + nameofhistogram;
      if(i != 4) mc_sum -> Add(maphist[this_hist_name]);
    }
    data_mc_ratio -> Divide(mc_sum);
  }

  data_mc_ratio -> Draw("psame");

  maplegend["bottom" + legend] = new TLegend(0.2, 0.85, 0.6, 0.95);
  maplegend["bottom" + legend]->SetBorderSize(0);
  maplegend["bottom" + legend]->SetNColumns(3);
  if(draw_Data_vs_External) maplegend["bottom" + legend]->AddEntry(data_mc_ratio, "(Obs. - non-External MC)/External", "lp");
  else maplegend["bottom" + legend]->AddEntry(data_mc_ratio, "Obs./Pred.", "lp");

  // == Line : ratio = 1
  TLine *pad2_line = new TLine(xmin, 1, xmax, 1);
  pad2_line -> SetLineStyle(1);
  pad2_line -> SetLineColor(kBlue);
  pad2_line -> Draw("same");

  maplegend["bottom" + legend] -> Draw("same");

  gPad->RedrawAxis();

  data_mc_ratio -> Draw("psame");

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
  if(draw_Data_vs_External) pdfname = WORKING_DIR + "/output/plots/" + nameofhistogram + "_Data_vs_External.pdf";
  else pdfname = WORKING_DIR + "/output/plots/" + nameofhistogram + ".pdf";
  mapcanvas[canvas] -> SaveAs(pdfname);
  
}

void submit_stack_plot(TString histname, double xmin, double xmax, double rebin){

  open_file_data("Data_central", histname);
  open_file_mc("OneView", "central", histname);
  open_file_mc("TwoView", "central", histname);

  Draw_stacked_plot("OneView", histname, xmin, xmax, rebin);
  Draw_stacked_plot("TwoView", histname, xmin, xmax, rebin);

}


void Draw_basic_plots(){
  setTDRStyle();

  // == Draw_plot(histname, xmin, xmax, rebin)
  //submit_stack_plot("Cutflow", 0., 10., 1.);
  //submit_stack_plot("pNueCC_vtx", 0., 1.0, 50.);
  //submit_stack_plot("pNueCC2_vtx", 0., 1.0, 50.);
  //submit_stack_plot("pNueCC_vtx", 0.9, 1.0, 10.);
  //submit_stack_plot("pNueCC2_vtx", 0.9, 1.0, 10.);


  /*
  submit_stack_plot("pNueCC", 0., 1.0, 10.);
  submit_stack_plot("pNueCC_nhits", 0., 1.0, 10.);
  submit_stack_plot("pNueCC_nhits_antiminos",0., 1.0, 10.);
  submit_stack_plot("pNueCC_nhits_antiminos_nearestz",0., 1.0, 10.);
  submit_stack_plot("nhits", -10.,500., 10.);
  */
}
