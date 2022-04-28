#include "Event.h"

ClassImp(Event)

Event::Event(){
  j_IsData = true;
}

Event::~Event(){

}

void Event::SetIsData(bool isdata){
  j_IsData = isdata;
}
