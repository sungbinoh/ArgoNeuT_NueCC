root -l -b<<EOF
cout << "Call Analyzer Class" << endl;
  NueCCAnalyzer m;
  cout << "Setting event variables" << endl;
  m.SetTreeName();
  m.AddFile("/gv0/Users/suoh/ArgoNeuT/data/standard_reco_hist.root");
  m.SetOutfilePath("hists.root");
  m.Init();
  cout << "Running" << endl;
  m.initializeAnalyzer();
  m.initializeAnalyzerTools();
  m.SwitchToTempDir();
  m.Loop();

  m.WriteHist();

EOF
