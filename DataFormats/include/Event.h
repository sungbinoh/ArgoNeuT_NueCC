#ifndef Event_h
#define Event_h

#include "TString.h"
#include "TObject.h"
#include <iostream>

using namespace std;

class Event : public TObject {
public:

  Event();
  ~Event();

  void SetSimulator(TString sim);
  inline TString Simulator() const {return j_Simulator;}

private:
  TString j_Simulator;

  ClassDef(Event,1)
};

#endif
