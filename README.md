# ArgoNeuT_NueCC

## ArNeuT

It should run well in linux, when PATH for the root is well defined.

### Complie
```
source setup.sh
make
```

### Running
Modifiy run.sh. 
```
m.IsData = true; // true or false
if(m.IsData) m.AddFile("/gv0/Users/suoh/ArgoNeuT/data/standard_reco_hist.root"); // Set your directory for data file
if(!m.IsData) m.AddFile("/gv0/Users/suoh/ArgoNeuT/mc/standard_reco_hist.root"); // Set your directory for mc file
```

To run,
```
source run.sh
```