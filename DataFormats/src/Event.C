#include "Event.h"

ClassImp(Event)

Event::Event(){
  j_IsData = true;
  j_WhichTree = "";
}

Event::~Event(){

}

void Event::SetIsData(bool isdata){
  j_IsData = isdata;
}

void Event::SetWhichTree(TString whichtree){
  j_WhichTree = whichtree;
}
