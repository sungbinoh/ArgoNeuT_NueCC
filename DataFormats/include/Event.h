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

  void SetIsData(bool isdata);
  void SetWhichTree(TString whichtree);
  inline bool IsData() const {return j_IsData;}

private:
  bool j_IsData;
  TString j_WhichTree;
  ClassDef(Event,1)
};

#endif
