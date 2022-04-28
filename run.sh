root -l -b<<EOF
  cout << "Call Analyzer Class" << endl;
  NueCCAnalyzer m;
  cout << "Setting event variables" << endl;
  m.IsData = false;
  m.WhichTree = "New" // -- Possible options : Default, New
  //m.WhichTree = "Default"
  m.SetTreeName();
  m.MaxEvent = 10000;
  if(m.IsData && m.WhichTree == "Default") m.AddFile("/gv0/Users/suoh/ArgoNeuT/data/standard_reco_hist.root");
  if(!m.IsData && m.WhichTree == "Default") m.AddFile("/gv0/Users/suoh/ArgoNeuT/mc/standard_reco_hist.root"); 
  if(m.IsData && m.WhichTree == "New") m.AddFile("/gv0/Users/suoh/ArgoNeuT/data/new_standard_reco_hist.root");
  if(!m.IsData && m.WhichTree == "New") m.AddFile("/gv0/Users/suoh/ArgoNeuT/mc/new_standard_reco_hist.root");
  m.SetOutfilePath("hists.root");
  m.Init();
  cout << "Running" << endl;
  m.initializeAnalyzer();
  m.initializeAnalyzerTools();
  m.SwitchToTempDir();
  m.Loop();

  m.WriteHist();

EOF
