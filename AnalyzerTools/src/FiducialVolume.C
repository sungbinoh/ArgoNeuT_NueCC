#include "FiducialVolume.h"

FiducialVolume::FiducialVolume(){

}

void FiducialVolume::TestClass(){
  cout << "[[FiducialVolume::TestClass]] Test " << endl;
}

void FiducialVolume::SetFV(double this_x_low, double this_x_high, double this_y_low, double this_y_high, double this_z_low, double this_z_high){

  x_low = this_x_low;
  x_high = this_x_high;
  y_low = this_y_low;
  y_high = this_y_high;
  z_low = this_z_low;
  z_high = this_z_high;
  
}

bool FiducialVolume::InFV(TVector3 this_position){

  bool this_decision = false;
  if(this_position.X() > X_Low() && this_position.X() < X_High() && this_position.Y() > Y_Low() && this_position.Y() < Y_High()
     && this_position.Z() > Z_Low() && this_position.Z() < Z_High()) this_decision = true;

  return this_decision;
  
}

bool FiducialVolume::InFV_XY(TVector2 this_position){

  bool this_decision = false;
  if(this_position.X() > X_Low() && this_position.X() < X_High() && this_position.Y() > Y_Low() && this_position.Y() < Y_High()) this_decision = true;

  return this_decision;

}

FiducialVolume::~FiducialVolume(){

}
