#include "NueCCAnalyzer.h"

void NueCCAnalyzer::initializeAnalyzer(){

  cout << "[[NueCCAnalyzer::initializeAnalyzer]] Simulator : " << Simulator << endl;
  debug_mode = true;
  debug_mode = false;

}

void NueCCAnalyzer::executeEvent(){
  if(debug_mode) cout << "[[NueCCAnalyzer::executeEvent]] : START" << endl;
}

NueCCAnalyzer::NueCCAnalyzer(){

}

NueCCAnalyzer::~NueCCAnalyzer(){

}

