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
m.LogEvery = 50000; // cout for every the number of events you choose
m.MaxEvent = 100000; // runs only for the number of events you choose (mainly for debugging, comment out to run all events)
if(m.IsData) m.AddFile("/gv0/Users/suoh/ArgoNeuT/data/new_standard_reco_hist.root"); // Set your directory for data file
if(!m.IsData) m.AddFile("/gv0/Users/suoh/ArgoNeuT/mc/new_standard_reco_hist.root"); // Set your directory for mc file
```

To run,
```
source run.sh
```