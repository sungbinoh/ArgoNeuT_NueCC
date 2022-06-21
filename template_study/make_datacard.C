#include "mylib.h"

void open_files(TString histname){
  TString output_file_dir = getenv("ArNeuT_WD");
  output_file_dir = output_file_dir + "/output/templates/";
  ofstream file_shape(output_file_dir + "shape_" + histname + ".txt");
  file_shape << "imax 1" << endl;
  file_shape << "jmax 5" << endl;
  file_shape << "kmax *" << endl;
  file_shape << "---------------" << endl;
  file_shape << "shapes * * /argoneut/app/users/sungbino/limit/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/Templates/shape_" + histname + ".root $PROCESS $PROCESS_$SYSTEMATIC" << endl;
  file_shape << "---------------" << endl;
  file_shape << "bin\tbin1" << endl;
  file_shape << "observation\t-1" << endl;
  file_shape << "------------------------------" << endl;
  file_shape << "bin\tbin1\tbin1\tbin1\tbin1\tbin1\tbin1" << endl;

  file_shape << "process";
  for(int i = 0; i < N_MC_category; i++){
    file_shape << "\t" << MC_category[i];
  }
  file_shape << "\n";

  file_shape << "process\t0\t1\t2\t3\t4\t5" << endl;
  file_shape << "rate\t-1\t-1\t-1\t-1\t-1\t-1" << endl;
  file_shape << "--------------------------------" << endl;

  for(int i = 0; i < N_syst_category; i++){
    TString this_syst = systematics_category[i];
    if(this_syst.Contains("COHpi")) continue;
    file_shape << this_syst << "\tshapeN2\t1\t1\t1\t1\t1\t1" << endl;
  }

  TString MC_category[N_MC_category] = {"NumuCC", "NueCC", "NC", "External_NumuCC", "External_NueCC", "External_NC"};
  for(int i = 0; i < N_MC_category; i++){
    if(MC_category[i].Contains("External")){
      file_shape << "R_" << MC_category[i] << "\t" << "rateParam" << "\t" << "bin1\t" <<  MC_category[i] << "\t" << "1" << endl;
    }
  }

}

void make_datacard(){

  open_files("pNueCC2_vtx");

}
