#ifndef NueCCAnalyzer_h
#define NueCCAnalyzer_h

#include "AnalyzerCore.h"

class NueCCAnalyzer : public AnalyzerCore {

public:

  void initializeAnalyzer();
  void executeEvent();

  NueCCAnalyzer();
  ~NueCCAnalyzer();

};

#endif
