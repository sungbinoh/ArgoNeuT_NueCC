#include "canvas_margin.h"

void Draw_Xsec(){
  setTDRStyle();
  gStyle->SetLineWidth(3);
  double xsec[4] = {0.932, 0.997, 0.948, 1.04};
  double xsec_stat_up[4] = {0.179, 0.190, 0.181, 0.38};
  double xsec_stat_down[4] = {0.168, 0.179, 0.171, 0.38};
  double xsec_syst_up[4] = {0.364, 0.506, 0.277, 0.15};
  double xsec_syst_down[4] = {0.301, 0.348, 0.248, 0.23};
  double xsec_error_up[4] = {0., 0., 0., 0.};
  double xsec_error_down[4] = {0., 0., 0., 0.};
  for(int i = 0; i < 4; i++){
    xsec_error_up[i] = sqrt(pow(xsec_stat_up[i], 2) + pow(xsec_syst_up[i], 2));
    xsec_error_down[i] = sqrt(pow(xsec_stat_down[i], 2) + pow(xsec_syst_down[i], 2));
  }

  double BDT_error_up[4] = {xsec_error_up[3], xsec_error_up[3], xsec_error_up[3], xsec_error_up[3]};
  double BDT_error_down[4] = {xsec_error_down[3], xsec_error_down[3], xsec_error_down[3], xsec_error_down[3]};

  double y[4] = {1., 2., 3., 4.};
  double y_err[4] = {0., 0., 0., 0.};

  double GENIE_xsec = 1.137;

  TCanvas *c = new TCanvas("", "", 600, 800);
  TPad *pad1 = new TPad("", "", 0.25, 0, 0.90, 0.95);
  pad1 -> SetLeftMargin( 0.15 );
  pad1 -> SetRightMargin( 0.03 );
  pad1 -> Draw();
  pad1 -> cd();
  TH1F * pad1_template = new TH1F("", "", 1, 0.4, 1.6);
  TString label[3] = {"Plane0", "Plane1", "Plane2"};
  pad1_template -> GetYaxis() -> SetRangeUser(0., 5.);
  pad1_template -> GetYaxis() -> SetLabelSize(0);
  pad1_template -> GetYaxis() -> SetNdivisions(0000);
  pad1_template -> GetXaxis() -> SetTitle("#sigma_{#nu_{e} + #bar{#nu}_{e}} (10^{-36} cm^{2} / Ar)");
  pad1_template -> GetXaxis() -> CenterTitle(true);
  pad1_template -> GetXaxis() -> SetNdivisions(2105);
  pad1_template -> GetXaxis() -> SetLabelSize(0.05);
  pad1_template -> SetStats(0);
  pad1_template -> Draw();

  TLine *pad1_line = new TLine(GENIE_xsec, 0., GENIE_xsec, 5.);
  pad1_line -> SetLineColor(kRed);
  pad1_line -> Draw("same");

  TGraphAsymmErrors *err_gr = new TGraphAsymmErrors(4, xsec, y, xsec_error_down, xsec_error_up, y_err, y_err);
  err_gr -> SetLineColor(kBlue);
  err_gr -> Draw("ezpsame");
  
  TGraphAsymmErrors *stat_gr = new TGraphAsymmErrors(4, xsec, y, xsec_stat_down, xsec_stat_up, y_err, y_err);
  stat_gr -> SetLineColor(kBlack);
  stat_gr -> SetLineWidth(3);
  //stat_gr -> MarkerColor(kRed);
  stat_gr -> SetMarkerStyle(20);
  stat_gr -> Draw("ezpsame");

  TGraphAsymmErrors *BDT_err_gr = new TGraphAsymmErrors(4, xsec, y, BDT_error_down, BDT_error_up, y_err, y_err);
  BDT_err_gr -> SetLineColor(kRed);
  BDT_err_gr -> SetLineWidth(1);
  BDT_err_gr -> SetLineStyle(7);
  BDT_err_gr -> Draw("epsame");

  TLegend *this_legend = new TLegend(0.2, 0.80, 0.6, 0.94);
  this_legend -> AddEntry(stat_gr, "Stat. Only", "lp");
  this_legend -> AddEntry(err_gr, "Syst. + Stat.", "l");
  this_legend -> AddEntry(BDT_err_gr, "BDT Err.", "l");
  this_legend -> AddEntry(pad1_line, "GENIE X-sec", "l");
  this_legend -> SetFillStyle(1001);
  //this_legend -> SetLineColor(kWhite);
  this_legend -> Draw("same");

  gPad->RedrawAxis();

  c -> cd();
  TLatex latex0, latex1, latex2, latex3, latex4, latex5, latex6;
  double text_size = 0.035;
  latex0.SetNDC();
  latex1.SetNDC();
  latex2.SetNDC();
  latex3.SetNDC();
  latex4.SetNDC();
  latex5.SetNDC();
  latex6.SetNDC();
  latex0.SetTextSize(text_size);
  latex1.SetTextSize(text_size);
  latex2.SetTextSize(text_size);
  latex3.SetTextSize(text_size);  
  latex4.SetTextSize(text_size);
  latex5.SetTextSize(text_size);
  latex6.SetTextSize(text_size);

  latex0.DrawLatex(0.08, 0.74, "Previous BDT");

  latex1.DrawLatex(0.10, 0.60, "No GENIE");
  latex2.DrawLatex(0.05, 0.56, "for Ext. and Signal");

  latex3.DrawLatex(0.10, 0.45, "No GENIE");
  latex4.DrawLatex(0.11, 0.42, "for Ext.");

  latex5.DrawLatex(0.10, 0.29, "GENIE for");
  latex6.DrawLatex(0.12, 0.25, "all MC");

  

  TLatex latex_ArgoNeuT, latex_data_POT;
  latex_ArgoNeuT.SetNDC();
  latex_data_POT.SetNDC();
  latex_ArgoNeuT.SetTextSize(0.035);
  latex_data_POT.SetTextSize(0.035);
  latex_ArgoNeuT.DrawLatex(0.05, 0.91, "#font[62]{ArgoNeuT} #font[42]{#it{#scale[0.8]{Preliminary}}}");
  latex_data_POT.DrawLatex(0.56, 0.91, "RHC 1.25 #times 10^{20} POT");

  TString pdfname;
  TString WORKING_DIR = getenv("ArNeuT_WD");
  WORKING_DIR = WORKING_DIR + "/output/plots/fit/";
  pdfname = WORKING_DIR + "xsec_comparison.pdf";
  c -> SaveAs(pdfname);

}
