#ifndef FiducialVolume_h
#define FiducialVolume_h

#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "TVector3.h"

class FiducialVolume{

  double x_low(0.) x_high(0.), y_low(0.), y_high(0.), z_low(0.), z_high(0.);
  
public:

  FiducialVolume();
  ~FiducialVolume();

  void SetFV(double this_x_low, double this_x_high, double this_y_low, double this_y_high, double this_z_low, double this_z_high);
  bool InFV(double this_x, TVector3 this_position);
  inline double X_Low() const { return x_low; }
  inline double X_High() const { return x_high; }
  inline double Y_Low() const { return y_low; }
  inline double Y_High() const { return y_high; }
  inline double Z_Low() const { return z_low; }
  inline double Z_High() const { return z_high; }
  
  void TestClass();
  
};

#endif
