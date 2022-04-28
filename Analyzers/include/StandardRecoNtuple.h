#ifndef StandardRecoNtuple_h
#define StandardRecoNtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

// Header file for the classes stored in the TTree if any.
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

const Int_t MAX_ntracks_reco = 500;
const Int_t MAX_ntracks_minos = 100;
const Int_t MAX_nvertices = 500;
const Int_t MAX_no_hits = 20000;
const Int_t MAX_no_clusters = 1000;

using namespace std;

class StandardRecoNtuple {
public :

   StandardRecoNtuple();
   virtual ~StandardRecoNtuple();

   virtual void Init_StandardReco(TChain *ch);
   bool IsData;

   // Declaration of leaf types
   Int_t           run;
   Int_t           subrun;
   Int_t           event;
   Double_t        pot;
   Double_t        vtxx_reco;
   Double_t        vtxy_reco;
   Double_t        vtxz_reco;
   Int_t           ntracks_reco;
   Int_t           nvertextracks_reco;
   Int_t           ntrackendonboundary_reco;
   Double_t        nearestz[3];
   Double_t        trackstart_x_reco;
   Double_t        trackstart_y_reco;
   Double_t        trackstart_z_reco;
   Double_t        trackexit_x_reco;
   Double_t        trackexit_y_reco;
   Double_t        trackexit_z_reco;
   Double_t        trackstart_dcosx_reco;
   Double_t        trackstart_dcosy_reco;
   Double_t        trackstart_dcosz_reco;
   Double_t        trackexit_dcosx_reco;
   Double_t        trackexit_dcosy_reco;
   Double_t        trackexit_dcosz_reco;
   Double_t        enu_reco;
   Int_t           nvertices;
   Double_t        vtx_x[MAX_nvertices];   //[nvertices]
   Double_t        vtx_y[MAX_nvertices];   //[nvertices]
   Double_t        vtx_z[MAX_nvertices];   //[nvertices]
   Double_t        trkvtxx[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trkvtxy[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trkvtxz[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trkendx[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trkendy[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trkendz[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trkstartdcosx[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trkstartdcosy[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trkstartdcosz[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trkenddcosx[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trkenddcosy[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trkenddcosz[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trkke[MAX_ntracks_reco][2];   //[ntracks_reco]
   Int_t           nshws;
   Float_t         shwdcosx[1];   //[nshws]
   Float_t         shwdcosy[1];   //[nshws]
   Float_t         shwdcosz[1];   //[nshws]
   Float_t         shwstartx[1];   //[nshws]
   Float_t         shwstarty[1];   //[nshws]
   Float_t         shwstartz[1];   //[nshws]
   Int_t           nmatched_reco;
   Double_t        trk_mom_minos;
   Double_t        trk_charge_minos;
   Double_t        trk_dcosx_minos;
   Double_t        trk_dcosy_minos;
   Double_t        trk_dcosz_minos;
   Double_t        trk_vtxx_minos;
   Double_t        trk_vtxy_minos;
   Double_t        trk_vtxz_minos;
   Int_t           trk_index_minos;
   Int_t           minostrk_index_minos;
   Int_t           trkcontained_minos;
   Double_t        rdiff_minos;
   Double_t        xdiff_minos;
   Double_t        ydiff_minos;
   Double_t        thetadiff_minos;
   Double_t        muon_Kin_Eng_reco;
   Int_t           ntracks_minos;
   Double_t        trk_vtxx_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Double_t        trk_vtxy_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Double_t        trk_vtxz_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Double_t        trk_dcosx_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Double_t        trk_dcosy_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Double_t        trk_dcosz_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Float_t         trk_e_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Float_t         shw_e_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Float_t         trk_mom_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Int_t           trk_contained_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Double_t        trk_xpred_minos[MAX_ntracks_minos][10];   //[ntracks_minos]
   Double_t        trk_ypred_minos[MAX_ntracks_minos][10];   //[ntracks_minos]
   Int_t           nuPDG_truth;
   Int_t           ccnc_truth;
   Double_t        enu_truth;
   Double_t        nuvtxx_truth;
   Double_t        nuvtxy_truth;
   Double_t        nuvtxz_truth;
   Double_t        nu_dcosx_truth;
   Double_t        nu_dcosy_truth;
   Double_t        nu_dcosz_truth;
   Double_t        lep_mom_truth;
   Double_t        lep_dcosx_truth;
   Double_t        lep_dcosy_truth;
   Double_t        lep_dcosz_truth;
   Int_t           mcevts_truth;
   vector<int>     *nuPDG_truth_multiple;
   vector<int>     *ccnc_truth_multiple;
   vector<double>  *enu_truth_multiple;
   vector<double>  *nuvtxx_truth_multiple;
   vector<double>  *nuvtxy_truth_multiple;
   vector<double>  *nuvtxz_truth_multiple;
   vector<double>  *nu_dcosx_truth_multiple;
   vector<double>  *nu_dcosy_truth_multiple;
   vector<double>  *nu_dcosz_truth_multiple;
   vector<double>  *lep_mom_truth_multiple;
   vector<double>  *lep_dcosx_truth_multiple;
   vector<double>  *lep_dcosy_truth_multiple;
   vector<double>  *lep_dcosz_truth_multiple;
   Int_t           no_hits;
   Int_t           hit_plane[MAX_no_hits];   //[no_hits]
   Int_t           no_clusters;
   Int_t           clusters_planeNo[MAX_no_clusters];   //[no_clusters]
   vector<string>  *evtwgt_funcname;
   vector<int>     *evtwgt_nweight;
   vector<vector<double> > *evtwgt_weight;
   Int_t           evtwgt_nfunc;
   Float_t         pNumuCC;
   Float_t         pNueCC;
   Float_t         pNC;
   Float_t         pNumuCC2;
   Float_t         pNueCC2;
   Float_t         pNC2;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_subrun;   //!
   TBranch        *b_event;   //!
   TBranch        *b_pot;   //!
   TBranch        *b_vtxx_reco;   //!
   TBranch        *b_vtxy_reco;   //!
   TBranch        *b_vtxz_reco;   //!
   TBranch        *b_ntracks_reco;   //!
   TBranch        *b_nvertextracks_reco;   //!
   TBranch        *b_ntrackendonboundary_reco;   //!
   TBranch        *b_nearestz;   //!
   TBranch        *b_trackstart_x_reco;   //!
   TBranch        *b_trackstart_y_reco;   //!
   TBranch        *b_trackstart_z_reco;   //!
   TBranch        *b_trackexit_x_reco;   //!
   TBranch        *b_trackexit_y_reco;   //!
   TBranch        *b_trackexit_z_reco;   //!
   TBranch        *b_trackstart_dcosx_reco;   //!
   TBranch        *b_trackstart_dcosy_reco;   //!
   TBranch        *b_trackstart_dcosz_reco;   //!
   TBranch        *b_trackexit_dcosx_reco;   //!
   TBranch        *b_trackexit_dcosy_reco;   //!
   TBranch        *b_trackexit_dcosz_reco;   //!
   TBranch        *b_enu_reco;   //!
   TBranch        *b_nvertices;   //!
   TBranch        *b_vtx_x;   //!
   TBranch        *b_vtx_y;   //!
   TBranch        *b_vtx_z;   //!
   TBranch        *b_trkvtxx;   //!
   TBranch        *b_trkvtxy;   //!
   TBranch        *b_trkvtxz;   //!
   TBranch        *b_trkendx;   //!
   TBranch        *b_trkendy;   //!
   TBranch        *b_trkendz;   //!
   TBranch        *b_trkstartdcosx;   //!
   TBranch        *b_trkstartdcosy;   //!
   TBranch        *b_trkstartdcosz;   //!
   TBranch        *b_trkenddcosx;   //!
   TBranch        *b_trkenddcosy;   //!
   TBranch        *b_trkenddcosz;   //!
   TBranch        *b_trkke;   //!
   TBranch        *b_nshws;   //!
   TBranch        *b_shwdcosx;   //!
   TBranch        *b_shwdcosy;   //!
   TBranch        *b_shwdcosz;   //!
   TBranch        *b_shwstartx;   //!
   TBranch        *b_shwstarty;   //!
   TBranch        *b_shwstartz;   //!
   TBranch        *b_nmatched_reco;   //!
   TBranch        *b_trk_mom_minos;   //!
   TBranch        *b_trk_charge_minos;   //!
   TBranch        *b_trk_dcosx_minos;   //!
   TBranch        *b_trk_dcosy_minos;   //!
   TBranch        *b_trk_dcosz_minos;   //!
   TBranch        *b_trk_vtxx_minos;   //!
   TBranch        *b_trk_vtxy_minos;   //!
   TBranch        *b_trk_vtxz_minos;   //!
   TBranch        *b_trk_index_minos;   //!
   TBranch        *b_minostrk_index_minos;   //!
   TBranch        *b_trkcontained_minos;   //!
   TBranch        *b_rdiff_minos;   //!
   TBranch        *b_xdiff_minos;   //!
   TBranch        *b_ydiff_minos;   //!
   TBranch        *b_thetadiff_minos;   //!
   TBranch        *b_muon_Kin_Eng_reco;   //!
   TBranch        *b_ntracks_minos;   //!
   TBranch        *b_trk_vtxx_all_minos;   //!
   TBranch        *b_trk_vtxy_all_minos;   //!
   TBranch        *b_trk_vtxz_all_minos;   //!
   TBranch        *b_trk_dcosx_all_minos;   //!
   TBranch        *b_trk_dcosy_all_minos;   //!
   TBranch        *b_trk_dcosz_all_minos;   //!
   TBranch        *b_trk_e_minos;   //!
   TBranch        *b_shw_e_minos;   //!
   TBranch        *b_trk_mom_all_minos;   //!
   TBranch        *b_trk_contained_minos;   //!
   TBranch        *b_trk_xpred_minos;   //!
   TBranch        *b_trk_ypred_minos;   //!
   TBranch        *b_nuPDG_truth;   //!
   TBranch        *b_ccnc_truth;   //!
   TBranch        *b_enu_truth;   //!
   TBranch        *b_nuvtxx_truth;   //!
   TBranch        *b_nuvtxy_truth;   //!
   TBranch        *b_nuvtxz_truth;   //!
   TBranch        *b_nu_dcosx_truth;   //!
   TBranch        *b_nu_dcosy_truth;   //!
   TBranch        *b_nu_dcosz_truth;   //!
   TBranch        *b_lep_mom_truth;   //!
   TBranch        *b_lep_dcosx_truth;   //!
   TBranch        *b_lep_dcosy_truth;   //!
   TBranch        *b_lep_dcosz_truth;   //!
   TBranch        *b_mcevts_truth;   //!
   TBranch        *b_nuPDG_truth_multiple;   //!
   TBranch        *b_ccnc_truth_multiple;   //!
   TBranch        *b_enu_truth_multiple;   //!
   TBranch        *b_nuvtxx_truth_multiple;   //!
   TBranch        *b_nuvtxy_truth_multiple;   //!
   TBranch        *b_nuvtxz_truth_multiple;   //!
   TBranch        *b_nu_dcosx_truth_multiple;   //!
   TBranch        *b_nu_dcosy_truth_multiple;   //!
   TBranch        *b_nu_dcosz_truth_multiple;   //!
   TBranch        *b_lep_mom_truth_multiple;   //!
   TBranch        *b_lep_dcosx_truth_multiple;   //!
   TBranch        *b_lep_dcosy_truth_multiple;   //!
   TBranch        *b_lep_dcosz_truth_multiple;   //!
   TBranch        *b_no_hits;   //!
   TBranch        *b_hit_plane;   //!
   TBranch        *b_no_clusters;   //!
   TBranch        *b_clusters_planeNo;   //!
   TBranch        *b_evtwgt_funcname;   //!
   TBranch        *b_evtwgt_nweight;   //!
   TBranch        *b_evtwgt_weight;   //!
   TBranch        *b_evtwgt_nfunc;   //!
   TBranch        *b_pNumuCC;   //!
   TBranch        *b_pNueCC;   //!
   TBranch        *b_pNC;   //!
   TBranch        *b_pNumuCC2;   //!
   TBranch        *b_pNueCC2;   //!
   TBranch        *b_pNC2;   //!

};

#endif
