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
  inline bool IsData() const {return j_IsData;}

private:
  bool j_IsData;
  ClassDef(Event,1)
};

#endif
