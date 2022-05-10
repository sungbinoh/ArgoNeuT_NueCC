#include "canvas_margin.h"
#include "mylib.h"
#include <sstream>

using namespace std;
bool draw_Data_vs_External = false;

void open_file_data(TString dir, TString histname){

  TString input_file_dir = getenv("ArNeuT_WD");
  TString root_file_path =input_file_dir + "/output/hists_data.root";
  TFile *current_file = new TFile ((root_file_path)) ;
  //gDirectory->cd(dir);

  //TH1D * current_hist = (TH1D*)gDirectory -> Get(histname + "_" + dir);
  TH1D * current_hist = (TH1D*)gDirectory -> Get("Data_" + histname);
  if(current_hist){
    current_hist -> SetDirectory(0);
    if(debug) cout << "[open_file_data] We have " +  histname << endl;
  }
  else{
    if(debug) cout << "[open_file_data] We do not have " +  histname << endl;
  }
  TH1::AddDirectory(kFALSE);
  
  //maphist[histname + "_" + dir] = current_hist;
  maphist["Data" + histname] = current_hist;

  current_file -> Close();
  delete current_file;
}

void open_file_mc(TString dir, TString histname){

  TString input_file_dir = getenv("ArNeuT_WD");
  TString root_file_path =input_file_dir + "/output/hists_mc.root";
  TFile *current_file = new TFile ((root_file_path)) ;

  TH1D * External_NC = (TH1D*)gDirectory -> Get("External_NC_" + histname);
  TH1D * External_NueCC = (TH1D*)gDirectory -> Get("External_NueCC_" + histname);
  TH1D * External_NumuCC = (TH1D*)gDirectory -> Get("External_NumuCC_" + histname);
  TH1D * NC = (TH1D*)gDirectory -> Get("NC_" + histname);
  TH1D * NueCC = (TH1D*)gDirectory -> Get("NueCC_" + histname);
  TH1D * NumuCC = (TH1D*)gDirectory -> Get("NumuCC_" + histname);

  if(External_NC) External_NC -> SetDirectory(0);
  if(External_NueCC) External_NueCC -> SetDirectory(0);
  if(External_NumuCC) External_NumuCC -> SetDirectory(0);
  if(NC) NC -> SetDirectory(0);
  if(NueCC) NueCC -> SetDirectory(0);
  if(NumuCC) NumuCC -> SetDirectory(0);
  TH1::AddDirectory(kFALSE);

  maphist["External_NC" +  histname] = External_NC;
  maphist["External_NueCC" +  histname] = External_NueCC;
  maphist["External_NumuCC" +  histname] = External_NumuCC;
  maphist["NC" +  histname] = NC;
  maphist["NueCC" +  histname] = NueCC;
  maphist["NumuCC" +  histname] = NumuCC;

  current_file -> Close();
  delete current_file;
}

void Draw_stacked_plot(TString histname, double xmin, double xmax, double rebin){

  TString title_y = "Events/bin";
  //TString nameofhistogram = histname + "_" + dir;
  TString nameofhistogram = histname;
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
  mappad[pad1] -> SetLogy();


  // == Define histograms into maps
  TH1D * data =  (TH1D*)maphist["Data" + histname] -> Clone();

  const int N_mc_strings = 4;
  TString mc_strings[N_mc_strings] = {"NC", "NumuCC", "External", "NueCC"};
  for(int i = 0; i < N_mc_strings; i++){
    if(i != 2) maphist["Draw_stacked_plot" + mc_strings[i] + nameofhistogram] = (TH1D*)maphist[mc_strings[i] + nameofhistogram] -> Clone();
  }
  maphist["Draw_stacked_plotExternal" + nameofhistogram] = (TH1D*)maphist["External_NC" + nameofhistogram] -> Clone();
  maphist["Draw_stacked_plotExternal" + nameofhistogram] -> Add(maphist["External_NueCC"+ nameofhistogram]);
  maphist["Draw_stacked_plotExternal" + nameofhistogram] -> Add(maphist["External_NumuCC"+ nameofhistogram]);

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
  pad1_template -> GetYaxis() -> SetRangeUser(1., data_max * 100.);
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
  //Int_t colour_array[] = {867, 901, 416, 393};
  //Int_t colour_array[] = {867, 393, 416, 901};
  Int_t colour_array[] = {867, 393, 416, 632};


  // == Rebin, set color, stack, and add to legend MC histograms
  for(int i = 0; i < N_mc_strings; i++){
    if(maphist["Draw_stacked_plot" + mc_strings[i] + nameofhistogram]){
      if(debug) cout << "[Draw_stacked_plot] Draw_stacked_plot" +  mc_strings[i] + nameofhistogram << endl;
      maphist["Draw_stacked_plot" + mc_strings[i] + nameofhistogram] -> Rebin(rebin);
      maphist["Draw_stacked_plot" + mc_strings[i] + nameofhistogram] -> SetLineColor(colour_array[i]);
      maphist["Draw_stacked_plot" + mc_strings[i] + nameofhistogram] -> SetFillColor(colour_array[i]);
      maphstack[hstack] -> Add(maphist["Draw_stacked_plot" + mc_strings[i] + nameofhistogram]);
      maplegend[legend]->AddEntry(maphist["Draw_stacked_plot" + mc_strings[i] + nameofhistogram], mc_strings[i], "f");
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
  pad2_template -> GetYaxis() -> SetRangeUser(0.1, 5.0);
  pad2_template -> SetStats(0);
  pad2_template -> Draw("histsame");

  // == Make MC sum and data/mc shape
  TH1D * mc_sum = (TH1D*)maphist["Draw_stacked_plot" + mc_strings[2] + nameofhistogram] -> Clone();
  TH1D * data_mc_ratio = (TH1D*)data -> Clone();

  if(draw_Data_vs_External){
    for(int i = 0; i < N_mc_strings; i++){
      if(i != 2) data_mc_ratio -> Add(maphist["Draw_stacked_plot" + mc_strings[i] + nameofhistogram], -1);
    }
    data_mc_ratio -> Divide(mc_sum);
  }
  else{
    for(int i = 0; i < N_mc_strings; i++){
      if(i != 2) mc_sum -> Add(maphist["Draw_stacked_plot" + mc_strings[i] + nameofhistogram]);
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

  open_file_data("", histname);
  open_file_mc("", histname);
  Draw_stacked_plot(histname, xmin, xmax, rebin);

}


void Draw_basic_plots(){
  setTDRStyle();

  // == Draw_plot(histname, xmin, xmax, rebin)
  submit_stack_plot("Cutflow", 0., 6., 1.);
  submit_stack_plot("pNueCC", 0., 1.0, 10.);
  submit_stack_plot("pNueCC_nhits", 0., 1.0, 10.);
  submit_stack_plot("pNueCC_nhits_antiminos",0., 1.0, 10.);
  submit_stack_plot("pNueCC_nhits_antiminos_nearestz",0., 1.0, 10.);
  submit_stack_plot("pNueCC_nhits_antiminos_nearestz_vertex",0., 1.0, 50.);
  
}
