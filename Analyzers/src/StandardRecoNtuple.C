#define StandardRecoNtuple_cxx
#include "StandardRecoNtuple.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

StandardRecoNtuple::StandardRecoNtuple(){
  IsData = true;
}

StandardRecoNtuple::~StandardRecoNtuple(){
}

void StandardRecoNtuple::Init_StandardReco(TChain *ch)
{

   ch->SetMakeClass(0);
   // Set object pointer
   nuPDG_truth_multiple = 0;
   ccnc_truth_multiple = 0;
   enu_truth_multiple = 0;
   nuvtxx_truth_multiple = 0;
   nuvtxy_truth_multiple = 0;
   nuvtxz_truth_multiple = 0;
   nu_dcosx_truth_multiple = 0;
   nu_dcosy_truth_multiple = 0;
   nu_dcosz_truth_multiple = 0;
   lep_mom_truth_multiple = 0;
   lep_dcosx_truth_multiple = 0;
   lep_dcosy_truth_multiple = 0;
   lep_dcosz_truth_multiple = 0;
   evtwgt_funcname = 0;
   evtwgt_nweight = 0;
   evtwgt_weight = 0;
 
   // Set branch addresses and branch pointers
 
   ch->SetBranchAddress("run", &run, &b_run);
   ch->SetBranchAddress("subrun", &subrun, &b_subrun);
   ch->SetBranchAddress("event", &event, &b_event);
   ch->SetBranchAddress("pot", &pot, &b_pot);
   ch->SetBranchAddress("vtxx_reco", &vtxx_reco, &b_vtxx_reco);
   ch->SetBranchAddress("vtxy_reco", &vtxy_reco, &b_vtxy_reco);
   ch->SetBranchAddress("vtxz_reco", &vtxz_reco, &b_vtxz_reco);
   ch->SetBranchAddress("ntracks_reco", &ntracks_reco, &b_ntracks_reco);
   ch->SetBranchAddress("nvertextracks_reco", &nvertextracks_reco, &b_nvertextracks_reco);
   ch->SetBranchAddress("ntrackendonboundary_reco", &ntrackendonboundary_reco, &b_ntrackendonboundary_reco);
   ch->SetBranchAddress("nearestz", nearestz, &b_nearestz);
   ch->SetBranchAddress("trackstart_x_reco", &trackstart_x_reco, &b_trackstart_x_reco);
   ch->SetBranchAddress("trackstart_y_reco", &trackstart_y_reco, &b_trackstart_y_reco);
   ch->SetBranchAddress("trackstart_z_reco", &trackstart_z_reco, &b_trackstart_z_reco);
   ch->SetBranchAddress("trackexit_x_reco", &trackexit_x_reco, &b_trackexit_x_reco);
   ch->SetBranchAddress("trackexit_y_reco", &trackexit_y_reco, &b_trackexit_y_reco);
   ch->SetBranchAddress("trackexit_z_reco", &trackexit_z_reco, &b_trackexit_z_reco);
   ch->SetBranchAddress("trackstart_dcosx_reco", &trackstart_dcosx_reco, &b_trackstart_dcosx_reco);
   ch->SetBranchAddress("trackstart_dcosy_reco", &trackstart_dcosy_reco, &b_trackstart_dcosy_reco);
   ch->SetBranchAddress("trackstart_dcosz_reco", &trackstart_dcosz_reco, &b_trackstart_dcosz_reco);
   ch->SetBranchAddress("trackexit_dcosx_reco", &trackexit_dcosx_reco, &b_trackexit_dcosx_reco);
   ch->SetBranchAddress("trackexit_dcosy_reco", &trackexit_dcosy_reco, &b_trackexit_dcosy_reco);
   ch->SetBranchAddress("trackexit_dcosz_reco", &trackexit_dcosz_reco, &b_trackexit_dcosz_reco);
   ch->SetBranchAddress("enu_reco", &enu_reco, &b_enu_reco);
   ch->SetBranchAddress("nvertices", &nvertices, &b_nvertices);
   ch->SetBranchAddress("vtx_x", vtx_x, &b_vtx_x);
   ch->SetBranchAddress("vtx_y", vtx_y, &b_vtx_y);
   ch->SetBranchAddress("vtx_z", vtx_z, &b_vtx_z);
   ch->SetBranchAddress("trkvtxx", trkvtxx, &b_trkvtxx);
   ch->SetBranchAddress("trkvtxy", trkvtxy, &b_trkvtxy);
   ch->SetBranchAddress("trkvtxz", trkvtxz, &b_trkvtxz);
   ch->SetBranchAddress("trkendx", trkendx, &b_trkendx);
   ch->SetBranchAddress("trkendy", trkendy, &b_trkendy);
   ch->SetBranchAddress("trkendz", trkendz, &b_trkendz);
   ch->SetBranchAddress("trkstartdcosx", trkstartdcosx, &b_trkstartdcosx);
   ch->SetBranchAddress("trkstartdcosy", trkstartdcosy, &b_trkstartdcosy);
   ch->SetBranchAddress("trkstartdcosz", trkstartdcosz, &b_trkstartdcosz);
   ch->SetBranchAddress("trkenddcosx", trkenddcosx, &b_trkenddcosx);
   ch->SetBranchAddress("trkenddcosy", trkenddcosy, &b_trkenddcosy);
   ch->SetBranchAddress("trkenddcosz", trkenddcosz, &b_trkenddcosz);
   ch->SetBranchAddress("trkke", trkke, &b_trkke);
   ch->SetBranchAddress("nshws", &nshws, &b_nshws);
   ch->SetBranchAddress("shwdcosx", &shwdcosx, &b_shwdcosx);
   ch->SetBranchAddress("shwdcosy", &shwdcosy, &b_shwdcosy);
   ch->SetBranchAddress("shwdcosz", &shwdcosz, &b_shwdcosz);
   ch->SetBranchAddress("shwstartx", &shwstartx, &b_shwstartx);
   ch->SetBranchAddress("shwstarty", &shwstarty, &b_shwstarty);
   ch->SetBranchAddress("shwstartz", &shwstartz, &b_shwstartz);
   ch->SetBranchAddress("nmatched_reco", &nmatched_reco, &b_nmatched_reco);
   ch->SetBranchAddress("trk_mom_minos", &trk_mom_minos, &b_trk_mom_minos);
   ch->SetBranchAddress("trk_charge_minos", &trk_charge_minos, &b_trk_charge_minos);
   ch->SetBranchAddress("trk_dcosx_minos", &trk_dcosx_minos, &b_trk_dcosx_minos);
   ch->SetBranchAddress("trk_dcosy_minos", &trk_dcosy_minos, &b_trk_dcosy_minos);
   ch->SetBranchAddress("trk_dcosz_minos", &trk_dcosz_minos, &b_trk_dcosz_minos);
   ch->SetBranchAddress("trk_vtxx_minos", &trk_vtxx_minos, &b_trk_vtxx_minos);
   ch->SetBranchAddress("trk_vtxy_minos", &trk_vtxy_minos, &b_trk_vtxy_minos);
   ch->SetBranchAddress("trk_vtxz_minos", &trk_vtxz_minos, &b_trk_vtxz_minos);
   ch->SetBranchAddress("trk_index_minos", &trk_index_minos, &b_trk_index_minos);
   ch->SetBranchAddress("minostrk_index_minos", &minostrk_index_minos, &b_minostrk_index_minos);
   ch->SetBranchAddress("trkcontained_minos", &trkcontained_minos, &b_trkcontained_minos);
   ch->SetBranchAddress("rdiff_minos", &rdiff_minos, &b_rdiff_minos);
   ch->SetBranchAddress("xdiff_minos", &xdiff_minos, &b_xdiff_minos);
   ch->SetBranchAddress("ydiff_minos", &ydiff_minos, &b_ydiff_minos);
   ch->SetBranchAddress("thetadiff_minos", &thetadiff_minos, &b_thetadiff_minos);
   ch->SetBranchAddress("muon_Kin_Eng_reco", &muon_Kin_Eng_reco, &b_muon_Kin_Eng_reco);
   ch->SetBranchAddress("ntracks_minos", &ntracks_minos, &b_ntracks_minos);
   ch->SetBranchAddress("trk_vtxx_all_minos", trk_vtxx_all_minos, &b_trk_vtxx_all_minos);
   ch->SetBranchAddress("trk_vtxy_all_minos", trk_vtxy_all_minos, &b_trk_vtxy_all_minos);
   ch->SetBranchAddress("trk_vtxz_all_minos", trk_vtxz_all_minos, &b_trk_vtxz_all_minos);
   ch->SetBranchAddress("trk_dcosx_all_minos", trk_dcosx_all_minos, &b_trk_dcosx_all_minos);
   ch->SetBranchAddress("trk_dcosy_all_minos", trk_dcosy_all_minos, &b_trk_dcosy_all_minos);
   ch->SetBranchAddress("trk_dcosz_all_minos", trk_dcosz_all_minos, &b_trk_dcosz_all_minos);
   ch->SetBranchAddress("trk_e_minos", trk_e_minos, &b_trk_e_minos);
   ch->SetBranchAddress("shw_e_minos", shw_e_minos, &b_shw_e_minos);
   ch->SetBranchAddress("trk_mom_all_minos", trk_mom_all_minos, &b_trk_mom_all_minos);
   ch->SetBranchAddress("trk_contained_minos", trk_contained_minos, &b_trk_contained_minos);
   ch->SetBranchAddress("trk_xpred_minos", trk_xpred_minos, &b_trk_xpred_minos);
   ch->SetBranchAddress("trk_ypred_minos", trk_ypred_minos, &b_trk_ypred_minos);
   if(!IsData){
     ch->SetBranchAddress("nuPDG_truth", &nuPDG_truth, &b_nuPDG_truth);
     ch->SetBranchAddress("ccnc_truth", &ccnc_truth, &b_ccnc_truth);
     ch->SetBranchAddress("enu_truth", &enu_truth, &b_enu_truth);
     ch->SetBranchAddress("nuvtxx_truth", &nuvtxx_truth, &b_nuvtxx_truth);
     ch->SetBranchAddress("nuvtxy_truth", &nuvtxy_truth, &b_nuvtxy_truth);
     ch->SetBranchAddress("nuvtxz_truth", &nuvtxz_truth, &b_nuvtxz_truth);
     ch->SetBranchAddress("nu_dcosx_truth", &nu_dcosx_truth, &b_nu_dcosx_truth);
     ch->SetBranchAddress("nu_dcosy_truth", &nu_dcosy_truth, &b_nu_dcosy_truth);
     ch->SetBranchAddress("nu_dcosz_truth", &nu_dcosz_truth, &b_nu_dcosz_truth);
     ch->SetBranchAddress("lep_mom_truth", &lep_mom_truth, &b_lep_mom_truth);
     ch->SetBranchAddress("lep_dcosx_truth", &lep_dcosx_truth, &b_lep_dcosx_truth);
     ch->SetBranchAddress("lep_dcosy_truth", &lep_dcosy_truth, &b_lep_dcosy_truth);
     ch->SetBranchAddress("lep_dcosz_truth", &lep_dcosz_truth, &b_lep_dcosz_truth);
     ch->SetBranchAddress("mcevts_truth", &mcevts_truth, &b_mcevts_truth);
     ch->SetBranchAddress("nuPDG_truth_multiple", &nuPDG_truth_multiple, &b_nuPDG_truth_multiple);
     ch->SetBranchAddress("ccnc_truth_multiple", &ccnc_truth_multiple, &b_ccnc_truth_multiple);
     ch->SetBranchAddress("enu_truth_multiple", &enu_truth_multiple, &b_enu_truth_multiple);
     ch->SetBranchAddress("nuvtxx_truth_multiple", &nuvtxx_truth_multiple, &b_nuvtxx_truth_multiple);
     ch->SetBranchAddress("nuvtxy_truth_multiple", &nuvtxy_truth_multiple, &b_nuvtxy_truth_multiple);
     ch->SetBranchAddress("nuvtxz_truth_multiple", &nuvtxz_truth_multiple, &b_nuvtxz_truth_multiple);
     ch->SetBranchAddress("nu_dcosx_truth_multiple", &nu_dcosx_truth_multiple, &b_nu_dcosx_truth_multiple);
     ch->SetBranchAddress("nu_dcosy_truth_multiple", &nu_dcosy_truth_multiple, &b_nu_dcosy_truth_multiple);
     ch->SetBranchAddress("nu_dcosz_truth_multiple", &nu_dcosz_truth_multiple, &b_nu_dcosz_truth_multiple);
     ch->SetBranchAddress("lep_mom_truth_multiple", &lep_mom_truth_multiple, &b_lep_mom_truth_multiple);
     ch->SetBranchAddress("lep_dcosx_truth_multiple", &lep_dcosx_truth_multiple, &b_lep_dcosx_truth_multiple);
     ch->SetBranchAddress("lep_dcosy_truth_multiple", &lep_dcosy_truth_multiple, &b_lep_dcosy_truth_multiple);
     ch->SetBranchAddress("lep_dcosz_truth_multiple", &lep_dcosz_truth_multiple, &b_lep_dcosz_truth_multiple);
     ch->SetBranchAddress("evtwgt_funcname", &evtwgt_funcname, &b_evtwgt_funcname);
     ch->SetBranchAddress("evtwgt_nweight", &evtwgt_nweight, &b_evtwgt_nweight);
     ch->SetBranchAddress("evtwgt_weight", &evtwgt_weight, &b_evtwgt_weight);
     ch->SetBranchAddress("evtwgt_nfunc", &evtwgt_nfunc, &b_evtwgt_nfunc);
   }
   ch->SetBranchAddress("no_hits", &no_hits, &b_no_hits);
   ch->SetBranchAddress("hit_plane", hit_plane, &b_hit_plane);
   ch->SetBranchAddress("no_clusters", &no_clusters, &b_no_clusters);
   ch->SetBranchAddress("clusters_planeNo", clusters_planeNo, &b_clusters_planeNo);
   ch->SetBranchAddress("pNumuCC", &pNumuCC, &b_pNumuCC);
   ch->SetBranchAddress("pNueCC", &pNueCC, &b_pNueCC);
   ch->SetBranchAddress("pNC", &pNC, &b_pNC);
   ch->SetBranchAddress("pNumuCC2", &pNumuCC2, &b_pNumuCC2);
   ch->SetBranchAddress("pNueCC2", &pNueCC2, &b_pNueCC2);
   ch->SetBranchAddress("pNC2", &pNC2, &b_pNC2);
}
