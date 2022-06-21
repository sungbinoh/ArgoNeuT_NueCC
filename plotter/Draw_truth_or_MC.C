#include "canvas_margin.h"
#include "mylib.h"
#include <sstream>

using namespace std;

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

void open_file_mc_interaction(TString dir, TString histname){

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

void open_file_mc_source(TString dir, TString histname){

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

  if(External_NueCC_cryo) External_NumuCC_cryo -> Add(External_NueCC_cryo);
  if(External_NC_cryo) External_NumuCC_cryo -> Add(External_NC_cryo);

  if(External_NueCC_Minerva) External_NumuCC_Minerva -> Add(External_NueCC_Minerva);
  if(External_NC_Minerva) External_NumuCC_Minerva -> Add(External_NC_Minerva);

  if(External_NueCC_Dirt) External_NumuCC_Dirt -> Add(External_NueCC_Dirt);
  if(External_NC_Dirt) External_NumuCC_Dirt -> Add(External_NC_Dirt);

  if(External_NumuCC_cryo) External_NumuCC_cryo -> SetDirectory(0);
  if(External_NumuCC_Minerva) External_NumuCC_Minerva -> SetDirectory(0);
  if(External_NumuCC_Dirt) External_NumuCC_Dirt -> SetDirectory(0);
  if(NC) NC -> SetDirectory(0);
  if(NueCC) NueCC -> SetDirectory(0);
  if(NumuCC) NumuCC -> SetDirectory(0);
  TH1::AddDirectory(kFALSE);

  maphist["External_cryo" +  histname] = External_NumuCC_cryo;
  maphist["External_Minerva" +  histname] = External_NumuCC_Minerva;
  maphist["External_Dirt" +  histname] = External_NumuCC_Dirt;
  maphist["NC" +  histname] = NC;
  maphist["NueCC" +  histname] = NueCC;
  maphist["NumuCC" +  histname] = NumuCC;

  current_file -> Close();
  delete current_file;

}

void Draw_External_shape(TString histname, double xmin, double xmax, double rebin){

  TString title_y = "Events/bin";
  TString nameofhistogram = histname;
  TString canvas = nameofhistogram;
  TString pad1 = nameofhistogram;
  TString pad2 = nameofhistogram;
  TString hstack = nameofhistogram;
  TString legend = nameofhistogram;
  TString line = nameofhistogram;
  canvas.Insert(0, "c_Draw_External_shape");
  pad1.Insert(0, "pad1_Draw_External_shape");
  pad2.Insert(0, "pad2_Draw_External_shape");
  hstack.Insert(0, "hs_Draw_External_shape");
  legend.Insert(0, "legend_Draw_External_shape");
  line.Insert(0, "l_Draw_External_shape");

  mapcanvas[canvas] = new TCanvas(canvas,"",800,800);
  canvas_margin(mapcanvas[canvas]);
  gStyle -> SetOptStat(1111);

  mappad[pad1] = new TPad("", "", 0, 0, 1, 1);
  mappad[pad1] -> SetTopMargin( 0.07 );
  mappad[pad1] -> SetLeftMargin( 0.15 );
  mappad[pad1] -> SetRightMargin( 0.03 );
  mappad[pad1] -> Draw();
  mappad[pad1] -> cd();
  mappad[pad1] -> SetLogx();
  //mappad[pad1] -> SetLogy();

  const int N_mc_strings = 3;
  const int N_pNueCC_strings = 3;

  TString mc_strings[N_mc_strings] = {"External_NueCC", "External_NC", "External_NumuCC"};
  TString pNueCC_strings[N_pNueCC_strings] = {"pNueCC_above_0p7", "pNueCC_0p4_to_0p7", "pNueCC_bellow_0p4"};

  open_file_mc("", histname + "_pNueCC_bellow_0p4");
  open_file_mc("", histname + "_pNueCC_0p4_to_0p7");
  open_file_mc("", histname + "_pNueCC_above_0p7");
  for(int i = 0; i < N_mc_strings; i++){
    for(int j = 0; j < N_pNueCC_strings; j++){
      maphist["Draw_External_shape" + mc_strings[i] + nameofhistogram + pNueCC_strings[j]] =
	(TH1D*)maphist[mc_strings[i] + nameofhistogram + "_" + pNueCC_strings[j]] -> Clone();
    }
    maphist["Draw_External_shape" + mc_strings[i] + nameofhistogram] = (TH1D*)maphist[mc_strings[i] + nameofhistogram] -> Clone();
  }

  for(int i = 1; i < N_mc_strings; i++){
    for(int j = 0; j < N_pNueCC_strings; j++){
      maphist["Draw_External_shape" + mc_strings[0] + nameofhistogram + pNueCC_strings[j]]
	-> Add(maphist["Draw_External_shape" + mc_strings[i] + nameofhistogram + pNueCC_strings[j]]);
    }
  }

  maplegend[legend] = new TLegend(0.60, 0.70, 0.95, 0.90);
  maplegend[legend] -> SetFillColor(kWhite);
  maplegend[legend] -> SetLineColor(kWhite);
  maplegend[legend] -> SetBorderSize(1);
  maplegend[legend] -> SetFillStyle(1001);
  maplegend[legend] -> SetShadowColor(0);
  maplegend[legend] -> SetEntrySeparation(0.3);


  // == Normalize shape
  Int_t colour_array[] = {867, 393, 632, 416, 414, 420};
  for(int j = 0; j < N_pNueCC_strings; j++){
    double current_norm = maphist["Draw_External_shape" + mc_strings[0] + nameofhistogram + pNueCC_strings[j]] -> Integral();
    TString current_hist_name = "Draw_External_shape" + mc_strings[0] + nameofhistogram + pNueCC_strings[j];
    maphist[current_hist_name] -> Rebin(rebin);
    maphist[current_hist_name] -> Scale(1./current_norm);
    maphist[current_hist_name + "error"] = (TH1D*)maphist[current_hist_name]-> Clone();
    maphist[current_hist_name] -> SetLineColor(colour_array[j]);
    maphist[current_hist_name] -> SetLineWidth(2);
    maphist[current_hist_name + "error"] -> SetFillColor(colour_array[j]);
    maphist[current_hist_name + "error"] -> SetFillStyle(3013);
    maphist[current_hist_name + "error"] -> SetMarkerSize(0);
    maphist[current_hist_name + "error"] -> SetLineWidth(0);
    maplegend[legend] -> AddEntry(maphist["Draw_External_shape" + mc_strings[0] + nameofhistogram + pNueCC_strings[j]], pNueCC_strings[j], "l");
  }

  double max_y = maphist["Draw_External_shape" + mc_strings[0] + nameofhistogram + pNueCC_strings[0]] -> GetMaximum();;
  TH1D *pad1_template = new TH1D("", "", 1, xmin, xmax);
  gStyle->SetOptTitle(0);
  gStyle->SetLineWidth(3);
  pad1_template -> SetStats(0);
  pad1_template -> GetXaxis() -> SetTitle(nameofhistogram);
  pad1_template -> GetXaxis() -> SetLabelSize(0.03);
  pad1_template -> GetXaxis() -> SetTitleSize(0.05);
  pad1_template -> GetYaxis() -> SetLabelSize(0.03);
  pad1_template -> GetYaxis() -> SetTitleSize(0.07);
  pad1_template -> GetYaxis() -> SetTitleOffset(1.02);
  pad1_template -> GetXaxis() -> SetTitle(nameofhistogram + " (cm)");
  pad1_template -> GetYaxis() -> SetTitle("A.U.");
  pad1_template -> GetYaxis() -> SetRangeUser(0., max_y * 1.5);
  pad1_template -> Draw("hist");

  for(int j = 0; j < N_pNueCC_strings; j++){
    TString current_hist_name ="Draw_External_shape" + mc_strings[0] + nameofhistogram + pNueCC_strings[j];
    maphist[current_hist_name] -> Draw("histsame");
    maphist[current_hist_name + "error"] -> Draw("e2same");
  }
  maplegend[legend] -> Draw("same");
  gPad->RedrawAxis();
  mapcanvas[canvas] -> cd();
  TLatex latex_ArgoNeuT, latex_data_POT;
  latex_ArgoNeuT.SetNDC();
  latex_data_POT.SetNDC();
  latex_ArgoNeuT.SetTextSize(0.035);
  latex_data_POT.SetTextSize(0.035);
  latex_ArgoNeuT.DrawLatex(0.15, 0.96, "#font[62]{ArgoNeuT} #font[42]{#it{#scale[0.8]{Preliminary}}}");
  latex_data_POT.DrawLatex(0.65, 0.96, "RHC 1.25 #times 10^{20} POT");

  TString pdfname;
  TString WORKING_DIR = getenv("ArNeuT_WD");
  pdfname = WORKING_DIR + "/output/plots/" + nameofhistogram + "_External_shapes.pdf";
  mapcanvas[canvas] -> SaveAs(pdfname);

}

void Draw_External_overlap(TString histname, double xmin, double xmax, double rebin){

  TString title_y = "Events/bin";
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
  mappad[pad1] = new TPad("", "", 0, 0, 1, 1);
  mappad[pad1] -> SetTopMargin( 0.07 );
  mappad[pad1] -> SetLeftMargin( 0.15 );
  mappad[pad1] -> SetRightMargin( 0.03 );
  mappad[pad1] -> Draw();
  mappad[pad1] -> cd();
  mappad[pad1] -> SetLogx();
  mappad[pad1] -> SetLogy();

  // == Define histograms into maps
  const int N_mc_strings = 3;
  const int N_pNueCC_strings = 3;
 //TString mc_strings[N_mc_strings] = {"NC", "NumuCC", "External", "NueCC"};
  //TString mc_strings[N_mc_strings] = {"NC", "NumuCC", "NueCC", "External_NC", "External_NueCC", "External_NumuCC"};
  TString mc_strings[N_mc_strings] = {"External_NueCC", "External_NC", "External_NumuCC"};
  TString pNueCC_strings[N_pNueCC_strings] = {"pNueCC_above_0p7", "pNueCC_0p4_to_0p7", "pNueCC_bellow_0p4"};

  open_file_mc("", histname + "_pNueCC_bellow_0p4");
  open_file_mc("", histname + "_pNueCC_0p4_to_0p7");
  open_file_mc("", histname + "_pNueCC_above_0p7");
  for(int i = 0; i < N_mc_strings; i++){
    for(int j = 0; j < N_pNueCC_strings; j++){
      maphist["Draw_External_overlap" + mc_strings[i] + nameofhistogram + pNueCC_strings[j]] = (TH1D*)maphist[mc_strings[i] + nameofhistogram + "_" + pNueCC_strings[j]] -> Clone();
    }
    maphist["Draw_External_overlap" + mc_strings[i] + nameofhistogram] = (TH1D*)maphist[mc_strings[i] + nameofhistogram] -> Clone();
  }

  // == Sum mc strings
  for(int i = 1; i < N_mc_strings; i++){
    for(int j = 0; j < N_pNueCC_strings; j++){
      maphist["Draw_External_overlap" + mc_strings[0] + nameofhistogram + pNueCC_strings[j]] -> Add(maphist["Draw_External_overlap" + mc_strings[i] + nameofhistogram + pNueCC_strings[j]]);
    }
  }

  // == Define legend
  maplegend[legend] = new TLegend(0.60, 0.70, 0.95, 0.90);
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
  Int_t colour_array[] = {867, 393, 632, 416, 414, 420};


  // == Rebin, set color, stack, and add to legend MC histograms
  for(int j = 0; j < N_pNueCC_strings; j++){
    if(maphist["Draw_External_overlap" + mc_strings[0] + nameofhistogram + pNueCC_strings[j]]){
      if(debug) cout << "[Draw_External_overlap] Draw_External_overlap" +  mc_strings[0] + nameofhistogram + pNueCC_strings[j] << endl;
      maphist["Draw_External_overlap" + mc_strings[0] + nameofhistogram + pNueCC_strings[j]] -> Rebin(rebin);
      maphist["Draw_External_overlap" + mc_strings[0] + nameofhistogram + pNueCC_strings[j]] -> SetLineColor(colour_array[j]);
      maphist["Draw_External_overlap" + mc_strings[0] + nameofhistogram + pNueCC_strings[j]] -> SetFillColor(colour_array[j]);
      maphstack[hstack] -> Add(maphist["Draw_External_overlap" + mc_strings[0] + nameofhistogram + pNueCC_strings[j]]);
      maplegend[legend]->AddEntry(maphist["Draw_External_overlap" + mc_strings[0] + nameofhistogram + pNueCC_strings[j]], pNueCC_strings[j], "f");
    }
  }

  // == mc sum
  TH1D * mc_sum = (TH1D*)maphist["Draw_External_overlap" + mc_strings[0] + nameofhistogram + + pNueCC_strings[0]] -> Clone();
  for(int j = 1; j < N_pNueCC_strings; j++){
    mc_sum -> Add(maphist["Draw_External_overlap" + mc_strings[0] + nameofhistogram + + pNueCC_strings[j]]);
  }
  double sum_max = mc_sum -> GetMaximum();

  // == Set a template for Pad 1
  TH1D *pad1_template = new TH1D("", "", 1, xmin, xmax);
  gStyle->SetOptTitle(0);
  gStyle->SetLineWidth(3);
  pad1_template -> SetStats(0);
  pad1_template -> GetXaxis() -> SetTitle(nameofhistogram);
  pad1_template -> GetXaxis() -> SetLabelSize(0.03);
  pad1_template -> GetXaxis() -> SetTitleSize(0.05);
  pad1_template -> GetYaxis() -> SetLabelSize(0.03);
  pad1_template -> GetYaxis() -> SetTitleSize(0.07);
  pad1_template -> GetYaxis() -> SetTitleOffset(1.02);
  pad1_template -> GetXaxis() -> SetTitle(nameofhistogram + " (cm)");
  pad1_template -> GetYaxis() -> SetTitle("Events");
  pad1_template -> GetYaxis() -> SetRangeUser(0.1, sum_max * 100.);
  pad1_template -> Draw("hist");


  // == Draw
  maphstack[hstack] -> Draw("histsame");
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
  pdfname = WORKING_DIR + "/output/plots/" + nameofhistogram + "_External_only.pdf";
  mapcanvas[canvas] -> SaveAs(pdfname);
  
}

void Draw_normalized_shape_interaction(TString histname, double xmin, double xmax, double rebin){

  TString title_y = "Events/bin";
  TString nameofhistogram = histname + "Draw_normalized_shape";;
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

  mappad[pad1] = new TPad("", "", 0, 0, 1, 1);
  mappad[pad1] -> SetTopMargin( 0.07 );
  mappad[pad1] -> SetLeftMargin( 0.15 );
  mappad[pad1] -> SetRightMargin( 0.03 );
  mappad[pad1] -> Draw();
  mappad[pad1] -> cd();
  mappad[pad1] -> SetLogy();

  TH1D *pad1_template = new TH1D("", "", 1, xmin, xmax);
  gStyle->SetOptTitle(0);
  gStyle->SetLineWidth(3);
  pad1_template -> SetStats(0);
  pad1_template -> GetXaxis() -> SetTitle("pNueCC");
  pad1_template -> GetXaxis() -> SetLabelSize(0.03);
  pad1_template -> GetXaxis() -> SetTitleSize(0.03);
  pad1_template -> GetYaxis() -> SetLabelSize(0.05);
  pad1_template -> GetYaxis() -> SetTitleSize(0.07);
  pad1_template -> GetYaxis() -> SetTitleOffset(1.02);
  pad1_template -> GetYaxis() -> SetTitle("A.U.");
  
  maplegend[legend] = new TLegend(0.40, 0.50, 0.80, 0.90);
  maplegend[legend] -> SetFillColor(kWhite);
  maplegend[legend] -> SetLineColor(kWhite);
  maplegend[legend] -> SetBorderSize(1);
  maplegend[legend] -> SetFillStyle(1001);
  maplegend[legend] -> SetShadowColor(0);
  maplegend[legend] -> SetEntrySeparation(0.3);

  double max_y = 0.;
  const int N_mc_strings = 6;
  TString mc_strings[N_mc_strings] = {"NC", "NumuCC", "NueCC", "External_NC", "External_NueCC", "External_NumuCC"};
  Int_t colour_array[] = {867, 393, 632, 416, 414, 420};
  for(int i = 0; i < N_mc_strings; i++){
    TString current_histname = "make_histogram" + mc_strings[i] + histname;
    if(maphist[mc_strings[i] + histname]){
      maphist[current_histname] = (TH1D*)maphist[mc_strings[i] + histname] -> Clone();
      maphist[current_histname] -> Rebin(rebin);
      maphist[current_histname] -> SetName(mc_strings[i]);
      maphist[current_histname] -> SetLineColor(colour_array[i]);
      maphist[current_histname] -> SetLineWidth(2.);
      maphist[current_histname] -> Scale(1. / maphist[current_histname] -> Integral() );
      double current_max_y = maphist[current_histname] -> GetMaximum();
      if(current_max_y > max_y) max_y = current_max_y;

      maphist[current_histname + "error"] = (TH1D*)maphist[current_histname]-> Clone();
      maphist[current_histname + "error"] -> SetFillColor(colour_array[i]);
      maphist[current_histname + "error"] -> SetFillStyle(3013);
      maphist[current_histname + "error"] -> SetMarkerSize(0);
      maphist[current_histname + "error"] -> SetLineWidth(0);
    }
  }
  pad1_template -> GetYaxis() -> SetRangeUser(0.,max_y);
  pad1_template -> GetYaxis() -> SetRangeUser(0.001, max_y * 10.); // == logy
  pad1_template -> Draw("hist");

  for(int i = 0; i < N_mc_strings; i++){
    TString current_histname = "make_histogram" + mc_strings[i] + histname;
    maphist[current_histname] -> Draw("histsame");
    maphist[current_histname + "error"] -> Draw("e2same");
    maplegend[legend] -> AddEntry(maphist[current_histname], mc_strings[i], "l");
  }

  maplegend[legend] -> Draw("same");
  mapcanvas[canvas] -> cd();
  TLatex latex_ArgoNeuT, latex_data_POT;
  latex_ArgoNeuT.SetNDC();
  latex_data_POT.SetNDC();
  latex_ArgoNeuT.SetTextSize(0.035);
  latex_data_POT.SetTextSize(0.035);
  latex_ArgoNeuT.DrawLatex(0.15, 0.96, "#font[62]{ArgoNeuT} #font[42]{#it{#scale[0.8]{Preliminary}}}");
  latex_data_POT.DrawLatex(0.65, 0.96, "RHC 1.25 #times 10^{20} POT");

  TString pdfname;
  TString WORKING_DIR = getenv("ArNeuT_WD");
  pdfname = WORKING_DIR + "/output/plots/" + nameofhistogram + "_norm_shape_interaction.pdf";
  mapcanvas[canvas] -> SaveAs(pdfname);

}

void Draw_normalized_shape_source(TString histname, double xmin, double xmax, double rebin){

  TString nameofhistogram = histname + "Draw_normalized_source";
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

  mappad[pad1] = new TPad("", "", 0, 0, 1, 1);
  mappad[pad1] -> SetTopMargin( 0.07 );
  mappad[pad1] -> SetLeftMargin( 0.15 );
  mappad[pad1] -> SetRightMargin( 0.03 );
  mappad[pad1] -> Draw();
  mappad[pad1] -> cd();
  //mappad[pad1] -> SetLogy();

  TH1D *pad1_template = new TH1D("", "", 1, xmin, xmax);
  gStyle->SetOptTitle(0);
  gStyle->SetLineWidth(3);
  pad1_template -> SetStats(0);
  pad1_template -> GetXaxis() -> SetTitle("pNueCC");
  pad1_template -> GetXaxis() -> SetLabelSize(0.03);
  pad1_template -> GetXaxis() -> SetTitleSize(0.03);
  pad1_template -> GetYaxis() -> SetLabelSize(0.05);
  pad1_template -> GetYaxis() -> SetTitleSize(0.07);
  pad1_template -> GetYaxis() -> SetTitleOffset(1.02);
  pad1_template -> GetYaxis() -> SetTitle("A.U.");

  maplegend[legend] = new TLegend(0.40, 0.50, 0.80, 0.90);
  maplegend[legend] -> SetFillColor(kWhite);
  maplegend[legend] -> SetLineColor(kWhite);
  maplegend[legend] -> SetBorderSize(1);
  maplegend[legend] -> SetFillStyle(1001);
  maplegend[legend] -> SetShadowColor(0);
  maplegend[legend] -> SetEntrySeparation(0.3);

  double max_y = 0.;
  const int N_mc_strings = 6;
  TString mc_strings[N_mc_strings] = {"NC", "NumuCC", "NueCC", "External_cryo", "External_Minerva", "External_Dirt"};
  Int_t colour_array[] = {867, 393, 632, 416, 414, 420};
  for(int i = 0; i < N_mc_strings; i++){
    TString current_histname = "make_histogram" + mc_strings[i] + histname;
    if(maphist[mc_strings[i] + histname]){
      maphist[current_histname] = (TH1D*)maphist[mc_strings[i] + histname] -> Clone();
      maphist[current_histname] -> Rebin(rebin);
      maphist[current_histname] -> SetName(mc_strings[i]);
      maphist[current_histname] -> SetLineColor(colour_array[i]);
      maphist[current_histname] -> SetLineWidth(2.);
      maphist[current_histname] -> Scale(1. / maphist[current_histname] -> Integral() );
      double current_max_y = maphist[current_histname] -> GetMaximum();
      if(current_max_y > max_y) max_y = current_max_y;

      maphist[current_histname + "error"] = (TH1D*)maphist[current_histname]-> Clone();
      maphist[current_histname + "error"] -> SetFillColor(colour_array[i]);
      maphist[current_histname + "error"] -> SetFillStyle(3013);
      maphist[current_histname + "error"] -> SetMarkerSize(0);
      maphist[current_histname + "error"] -> SetLineWidth(0);
    }
  }

  //pad1_template -> GetYaxis() -> SetRangeUser(0.,max_y);
  pad1_template -> GetYaxis() -> SetRangeUser(0.001, max_y * 10.); // == logy
  //pad1_template -> GetYaxis() -> SetRangeUser(0.001, 0.01);
  pad1_template -> Draw("hist");

  for(int i = 0; i < N_mc_strings; i++){
    TString current_histname = "make_histogram" + mc_strings[i] + histname;
    maphist[current_histname] -> Draw("histsame");
    if(i!=5)maphist[current_histname + "error"] -> Draw("e2same");
    maplegend[legend] -> AddEntry(maphist[current_histname], mc_strings[i], "l");
  }

  //maplegend[legend] -> Draw("same");
  mapcanvas[canvas] -> cd();
  TLatex latex_ArgoNeuT, latex_data_POT;
  latex_ArgoNeuT.SetNDC();
  latex_data_POT.SetNDC();
  latex_ArgoNeuT.SetTextSize(0.035);
  latex_data_POT.SetTextSize(0.035);
  latex_ArgoNeuT.DrawLatex(0.15, 0.96, "#font[62]{ArgoNeuT} #font[42]{#it{#scale[0.8]{Preliminary}}}");
  latex_data_POT.DrawLatex(0.65, 0.96, "RHC 1.25 #times 10^{20} POT");

  TString pdfname;
  TString WORKING_DIR = getenv("ArNeuT_WD");
  pdfname = WORKING_DIR + "/output/plots/" + nameofhistogram + "_norm_shape_source.pdf";
  mapcanvas[canvas] -> SaveAs(pdfname);


}

void submit_stack_plot(TString histname, double xmin, double xmax, double rebin){

  open_file_mc("", histname);
  open_file_mc("", histname);

  //Draw_stacked_plot(histname, xmin, xmax, rebin);

}

void submit_external_overlap(TString histname, double xmin, double xmax, double rebin){

  open_file_mc("", histname);
  open_file_mc("", histname + "_pNueCC_bellow_0p4");
  open_file_mc("", histname + "_pNueCC_0p4_to_0p7");
  open_file_mc("", histname + "_pNueCC_above_0p7");

  Draw_External_overlap(histname, xmin, xmax, rebin);
  Draw_External_shape(histname, xmin, xmax, rebin);

}

void submit_normalized_shapes_interaction(TString histname, double xmin, double xmax, double rebin){
  open_file_mc_interaction("", histname);
  Draw_normalized_shape_interaction(histname, xmin, xmax, rebin);
}

void submit_normalized_shapes_source(TString histname, double xmin, double xmax, double rebin){
  open_file_mc_source("", histname);
  Draw_normalized_shape_source(histname, xmin, xmax, rebin);
}

void Draw_truth_or_MC(){
  setTDRStyle();

  // == Draw_plot(histname, xmin, xmax, rebin)
  //submit_external_overlap("distance_vtx_truth", 10., 3000., 50);
  //submit_external_overlap("distance_vtx_truth_SR", 10., 3000., 50);
  
  //pNueCC_vtx
  submit_normalized_shapes_interaction("pNueCC_vtx", 0., 1., 10);
  submit_normalized_shapes_source("pNueCC_vtx", 0., 1., 5);

}
