root -l -b<<EOF
  cout << "Call Analyzer Class" << endl;
  NueCCAnalyzer m;
  cout << "Setting event variables" << endl;
  m.IsData = false;
  m.SetTreeName();
  m.LogEvery = 50000;
  //m.MaxEvent = 100000;
  if(m.IsData) m.AddFile("/dune/data/users/sungbino/ArgoNeuT/data/new_standard_reco_hist.root");
  if(!m.IsData) m.AddFile("/dune/data/users/sungbino/ArgoNeuT/mc/new_standard_reco_hist.root");
  if(m.IsData) m.SetOutfilePath("./output/hists_data.root");
  if(!m.IsData) m.SetOutfilePath("./output/hists_mc.root");
  m.Init();
  cout << "Running" << endl;
  m.initializeAnalyzer();
  m.initializeAnalyzerTools();
  m.SwitchToTempDir();
  m.Loop();

  m.WriteHist();

EOF

