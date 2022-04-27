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
const Int_t Max_no_hits = 20000;
const Int_t Max_no_clusters = 1000;
const Int_t Max_geant_list_size = 20000;
const Int_t Max_genie_no_primaries = 500;

using namespace std;

class StandardRecoNtuple {
public :

   StandardRecoNtuple();
   virtual ~ StandardRecoNtuple();

   virtual void Init_StandardReco(TChain *ch);
  
   // Declaration of leaf types
   Int_t           run;
   Int_t           subrun;
   Int_t           event;
   Double_t        evttime;
   Double_t        beamtime;
   Double_t        pot;
   Int_t           isdata;
   Double_t        taulife;
   Double_t        vtxx_reco;
   Double_t        vtxy_reco;
   Double_t        vtxz_reco;
   Int_t           nclusu_reco;
   Int_t           nclusv_reco;
   Int_t           nclusw_reco;
   Int_t           ntracks_reco;
   Int_t           nvertextracks_reco;
   Int_t           nvertexclustersu_reco;
   Int_t           nvertexclustersv_reco;
   Int_t           nvertexclustersw_reco;
   Int_t           ntrackendonboundary_reco;
   Double_t        nearestx[3];
   Double_t        nearesty[3];
   Double_t        nearestz[3];
   Double_t        trackstart_dcosx_reco;
   Double_t        trackstart_dcosy_reco;
   Double_t        trackstart_dcosz_reco;
   Double_t        trackexit_dcosx_reco;
   Double_t        trackexit_dcosy_reco;
   Double_t        trackexit_dcosz_reco;
   Double_t        trackstart_x_reco;
   Double_t        trackstart_y_reco;
   Double_t        trackstart_z_reco;
   Double_t        trackexit_x_reco;
   Double_t        trackexit_y_reco;
   Double_t        trackexit_z_reco;
   Double_t        enu_reco;
   Int_t           nclupertrack_reco;
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
   Double_t        trkrange[MAX_ntracks_reco][2];   //[ntracks_reco]
   Double_t        trkpitchc[MAX_ntracks_reco][2];   //[ntracks_reco]
   Int_t           nmaxtrkhits[2];
   Int_t           ntrkhits[MAX_ntracks_reco][2];   //[ntracks_reco]
   Double_t        trkdedx[MAX_ntracks_reco][2][1000];   //[ntracks_reco]
   Double_t        trkdqdx[MAX_ntracks_reco][2][1000];   //[ntracks_reco]
   Double_t        trkresrg[MAX_ntracks_reco][2][1000];   //[ntracks_reco]
   Int_t           trkhitindexc[MAX_ntracks_reco][2][1000];   //[ntracks_reco]
   Int_t           trkpid[MAX_ntracks_reco][2];   //[ntracks_reco]
   Int_t           trkpidndf[MAX_ntracks_reco][2];   //[ntracks_reco]
   Double_t        trkpidchi2[MAX_ntracks_reco][2];   //[ntracks_reco]
   Double_t        trkpida[MAX_ntracks_reco][2];   //[ntracks_reco]
   Double_t        trkmissinge[MAX_ntracks_reco][2];   //[ntracks_reco]
   Double_t        trkmissingeavg[MAX_ntracks_reco][2];   //[ntracks_reco]
   Int_t           trktruepdgu[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trktrueeffu[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trktruepuru[MAX_ntracks_reco];   //[ntracks_reco]
   Int_t           trktruepdgv[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trktrueeffv[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        trktruepurv[MAX_ntracks_reco];   //[ntracks_reco]
   Int_t           trkg4Id[MAX_ntracks_reco];   //[ntracks_reco]
   Int_t           nshws;
   Int_t           shwid[1];   //[nshws]
   Float_t         shwdcosx[1];   //[nshws]
   Float_t         shwdcosy[1];   //[nshws]
   Float_t         shwdcosz[1];   //[nshws]
   Float_t         shwstartx[1];   //[nshws]
   Float_t         shwstarty[1];   //[nshws]
   Float_t         shwstartz[1];   //[nshws]
   Float_t         shwenergy[1][2];   //[nshws]
   Double_t        shwdedx[1][2];   //[nshws]
   Int_t           shwbestplane[1];   //[nshws]
   Int_t           shwg4id[1];   //[nshws]
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
   Float_t         mc_index_minos;
   Double_t        mc_pdg_minos;
   Double_t        mc_px_minos;
   Double_t        mc_py_minos;
   Double_t        mc_pz_minos;
   Double_t        mc_ene_minos;
   Double_t        mc_mass_minos;
   Double_t        mc_vtxx_minos;
   Double_t        mc_vtxy_minos;
   Double_t        mc_vtxz_minos;
   Int_t           trkcontained_minos;
   Int_t           test_charge_minos;
   Double_t        rdiff_minos;
   Double_t        xdiff_minos;
   Double_t        ydiff_minos;
   Double_t        thetadiff_minos;
   Int_t           ntracks_minos;
   Double_t        trk_vtxx_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Double_t        trk_vtxy_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Double_t        trk_vtxz_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Double_t        trk_dcosx_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Double_t        trk_dcosy_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Double_t        trk_dcosz_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Float_t         trk_chi2_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Float_t         trk_qp_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Float_t         trk_eqp_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Float_t         trk_erange_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Float_t         trk_e_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Float_t         shw_e_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Float_t         trk_mom_all_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Int_t           trk_contained_minos[MAX_ntracks_minos];   //[ntracks_minos]
   Double_t        trk_xpred_minos[MAX_ntracks_minos][10];   //[ntracks_minos]
   Double_t        trk_ypred_minos[MAX_ntracks_minos][10];   //[ntracks_minos]
   Int_t           parpdg;
   Double_t        parmom;
   Int_t           nuPDG_truth;
   Int_t           ccnc_truth;
   Int_t           mode_truth;
   Double_t        enu_truth;
   Double_t        Q2_truth;
   Int_t           hitnuc_truth;
   Double_t        W_truth;
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
   vector<int>     *mode_truth_multiple;
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
   Double_t        beamwgt;
   Double_t        tpx_flux;
   Double_t        tpy_flux;
   Double_t        tpz_flux;
   Int_t           tptype_flux;
   Int_t           nvertices;
   Double_t        vtx_x[MAX_nvertices];   //[nvertices]
   Double_t        vtx_y[MAX_nvertices];   //[nvertices]
   Double_t        vtx_z[MAX_nvertices];   //[nvertices]
   Double_t        vtx_w0[MAX_nvertices];   //[nvertices]
   Double_t        vtx_w1[MAX_nvertices];   //[nvertices]
   Double_t        vtx_t0[MAX_nvertices];   //[nvertices]
   Double_t        vtx_t1[MAX_nvertices];   //[nvertices]
   Int_t           no_dead_wires_muon;
   Int_t           no_hits;
   Int_t           hit_plane[Max_no_hits];   //[no_hits]
   Int_t           hit_wire[Max_no_hits];   //[no_hits]
   Int_t           hit_channel[Max_no_hits];   //[no_hits]
   Double_t        hit_peakT[Max_no_hits];   //[no_hits]
   Double_t        hit_peakTcorr[Max_no_hits];   //[no_hits]
   Double_t        hit_charge[Max_no_hits];   //[no_hits]
   Double_t        hit_ph[Max_no_hits];   //[no_hits]
   Int_t           hit_trkid[Max_no_hits];   //[no_hits]
   Double_t        hit_etruth[Max_no_hits];   //[no_hits]
   Float_t         hit_rawdQds[Max_no_hits];   //[no_hits]
   Float_t         hit_dQds[Max_no_hits];   //[no_hits]
   Float_t         hit_dEds[Max_no_hits];   //[no_hits]
   Float_t         hit_ds[Max_no_hits];   //[no_hits]
   Float_t         hit_resrange[Max_no_hits];   //[no_hits]
   Float_t         hit_x[Max_no_hits];   //[no_hits]
   Float_t         hit_y[Max_no_hits];   //[no_hits]
   Float_t         hit_z[Max_no_hits];   //[no_hits]
   Int_t           no_clusters;
   Int_t           clusters_planeNo[Max_no_clusters];   //[no_clusters]
   Double_t        Start_pt_w_Cl[Max_no_clusters];   //[no_clusters]
   Double_t        Start_pt_t_Cl[Max_no_clusters];   //[no_clusters]
   Double_t        End_pt_w_Cl[Max_no_clusters];   //[no_clusters]
   Double_t        End_pt_t_Cl[Max_no_clusters];   //[no_clusters]
   Int_t           fNhitsClust;
   Double_t        two_trackstart_dcosx_reco[2];
   Double_t        two_trackstart_dcosy_reco[2];
   Double_t        two_trackstart_dcosz_reco[2];
   Double_t        two_trackexit_dcosx_reco[2];
   Double_t        two_trackexit_dcosy_reco[2];
   Double_t        two_trackexit_dcosz_reco[2];
   Int_t           no_primaries;
   Int_t           geant_list_size;
   Int_t           pdg[Max_geant_list_size];   //[geant_list_size]
   Double_t        Eng[Max_geant_list_size];   //[geant_list_size]
   Double_t        Px[Max_geant_list_size];   //[geant_list_size]
   Double_t        Py[Max_geant_list_size];   //[geant_list_size]
   Double_t        Pz[Max_geant_list_size];   //[geant_list_size]
   Double_t        StartPointx[Max_geant_list_size];   //[geant_list_size]
   Double_t        StartPointy[Max_geant_list_size];   //[geant_list_size]
   Double_t        StartPointz[Max_geant_list_size];   //[geant_list_size]
   Double_t        EndPointx[Max_geant_list_size];   //[geant_list_size]
   Double_t        EndPointy[Max_geant_list_size];   //[geant_list_size]
   Double_t        EndPointz[Max_geant_list_size];   //[geant_list_size]
   Int_t           NumberDaughters[Max_geant_list_size];   //[geant_list_size]
   Int_t           Mother[Max_geant_list_size];   //[geant_list_size]
   Int_t           TrackId[Max_geant_list_size];   //[geant_list_size]
   Int_t           process_primary[Max_geant_list_size];   //[geant_list_size]
   Int_t           orig[Max_geant_list_size];   //[geant_list_size]
   Double_t        Kin_Eng_reco[MAX_ntracks_reco];   //[ntracks_reco]
   Double_t        muon_Kin_Eng_reco;
   Int_t           genie_no_primaries;
   Int_t           genie_primaries_pdg[Max_genie_no_primaries];   //[genie_no_primaries]
   Double_t        genie_Eng[Max_genie_no_primaries];   //[genie_no_primaries]
   Double_t        genie_Px[Max_genie_no_primaries];   //[genie_no_primaries]
   Double_t        genie_Py[Max_genie_no_primaries];   //[genie_no_primaries]
   Double_t        genie_Pz[Max_genie_no_primaries];   //[genie_no_primaries]
   Double_t        genie_P[Max_genie_no_primaries];   //[genie_no_primaries]
   Int_t           genie_status_code[Max_genie_no_primaries];   //[genie_no_primaries]
   Double_t        genie_mass[Max_genie_no_primaries];   //[genie_no_primaries]
   Int_t           genie_trackID[Max_genie_no_primaries];   //[genie_no_primaries]
   Int_t           genie_ND[Max_genie_no_primaries];   //[genie_no_primaries]
   Int_t           genie_mother[Max_genie_no_primaries];   //[genie_no_primaries]
   Int_t           evtwgt_nfunc;
   vector<string>  *evtwgt_funcname;
   vector<int>     *evtwgt_nweight;
   vector<vector<double> > *evtwgt_weight;
   Double_t        pmttime;
   Int_t           pmt1[4];
   Int_t           pmt2[4];
   Int_t           pmt3[4];
   Int_t           pmt4[4];
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
   TBranch        *b_evttime;   //!
   TBranch        *b_beamtime;   //!
   TBranch        *b_pot;   //!
   TBranch        *b_isdata;   //!
   TBranch        *b_taulife;   //!
   TBranch        *b_vtxx_reco;   //!
   TBranch        *b_vtxy_reco;   //!
   TBranch        *b_vtxz_reco;   //!
   TBranch        *b_nclusu_reco;   //!
   TBranch        *b_nclusv_reco;   //!
   TBranch        *b_nclusw_reco;   //!
   TBranch        *b_ntracks_reco;   //!
   TBranch        *b_nvertextracks_reco;   //!
   TBranch        *b_nvertexclustersu_reco;   //!
   TBranch        *b_nvertexclustersv_reco;   //!
   TBranch        *b_nvertexclustersw_reco;   //!
   TBranch        *b_ntrackendonboundary_reco;   //!
   TBranch        *b_nearestx;   //!
   TBranch        *b_nearesty;   //!
   TBranch        *b_nearestz;   //!
   TBranch        *b_trackstart_dcosx_reco;   //!
   TBranch        *b_trackstart_dcosy_reco;   //!
   TBranch        *b_trackstart_dcosz_reco;   //!
   TBranch        *b_trackexit_dcosx_reco;   //!
   TBranch        *b_trackexit_dcosy_reco;   //!
   TBranch        *b_trackexit_dcosz_reco;   //!
   TBranch        *b_trackstart_x_reco;   //!
   TBranch        *b_trackstart_y_reco;   //!
   TBranch        *b_trackstart_z_reco;   //!
   TBranch        *b_trackexit_x_reco;   //!
   TBranch        *b_trackexit_y_reco;   //!
   TBranch        *b_trackexit_z_reco;   //!
   TBranch        *b_enu_reco;   //!
   TBranch        *b_nclupertrack_reco;   //!
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
   TBranch        *b_trkrange;   //!
   TBranch        *b_trkpitchc;   //!
   TBranch        *b_nmaxtrkhits;   //!
   TBranch        *b_ntrkhits;   //!
   TBranch        *b_trkdedx;   //!
   TBranch        *b_trkdqdx;   //!
   TBranch        *b_trkresrg;   //!
   TBranch        *b_trkhitindexc;   //!
   TBranch        *b_trkpid;   //!
   TBranch        *b_trkpidndf;   //!
   TBranch        *b_trkpidchi2;   //!
   TBranch        *b_trkpida;   //!
   TBranch        *b_trkmissinge;   //!
   TBranch        *b_trkmissingeavg;   //!
   TBranch        *b_trktruepdgu;   //!
   TBranch        *b_trktrueeffu;   //!
   TBranch        *b_trktruepuru;   //!
   TBranch        *b_trktruepdgv;   //!
   TBranch        *b_trktrueeffv;   //!
   TBranch        *b_trktruepurv;   //!
   TBranch        *b_trkg4Id;   //!
   TBranch        *b_nshws;   //!
   TBranch        *b_shwid;   //!
   TBranch        *b_shwdcosx;   //!
   TBranch        *b_shwdcosy;   //!
   TBranch        *b_shwdcosz;   //!
   TBranch        *b_shwstartx;   //!
   TBranch        *b_shwstarty;   //!
   TBranch        *b_shwstartz;   //!
   TBranch        *b_shwenergy;   //!
   TBranch        *b_shwdedx;   //!
   TBranch        *b_shwbestplane;   //!
   TBranch        *b_shwg4id;   //!
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
   TBranch        *b_mc_index_minos;   //!
   TBranch        *b_mc_pdg_minos;   //!
   TBranch        *b_mc_px_minos;   //!
   TBranch        *b_mc_py_minos;   //!
   TBranch        *b_mc_pz_minos;   //!
   TBranch        *b_mc_ene_minos;   //!
   TBranch        *b_mc_mass_minos;   //!
   TBranch        *b_mc_vtxx_minos;   //!
   TBranch        *b_mc_vtxy_minos;   //!
   TBranch        *b_mc_vtxz_minos;   //!
   TBranch        *b_trkcontained_minos;   //!
   TBranch        *b_test_charge_minos;   //!
   TBranch        *b_rdiff_minos;   //!
   TBranch        *b_xdiff_minos;   //!
   TBranch        *b_ydiff_minos;   //!
   TBranch        *b_thetadiff_minos;   //!
   TBranch        *b_ntracks_minos;   //!
   TBranch        *b_trk_vtxx_all_minos;   //!
   TBranch        *b_trk_vtxy_all_minos;   //!
   TBranch        *b_trk_vtxz_all_minos;   //!
   TBranch        *b_trk_dcosx_all_minos;   //!
   TBranch        *b_trk_dcosy_all_minos;   //!
   TBranch        *b_trk_dcosz_all_minos;   //!
   TBranch        *b_trk_chi2_minos;   //!
   TBranch        *b_trk_qp_minos;   //!
   TBranch        *b_trk_eqp_minos;   //!
   TBranch        *b_trk_erange_minos;   //!
   TBranch        *b_trk_e_minos;   //!
   TBranch        *b_shw_e_minos;   //!
   TBranch        *b_trk_mom_all_minos;   //!
   TBranch        *b_trk_contained_minos;   //!
   TBranch        *b_trk_xpred_minos;   //!
   TBranch        *b_trk_ypred_minos;   //!
   TBranch        *b_parpdg;   //!
   TBranch        *b_parmom;   //!
   TBranch        *b_nuPDG_truth;   //!
   TBranch        *b_ccnc_truth;   //!
   TBranch        *b_mode_truth;   //!
   TBranch        *b_enu_truth;   //!
   TBranch        *b_Q2_truth;   //!
   TBranch        *b_hitnuc_truth;   //!
   TBranch        *b_W_truth;   //!
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
   TBranch        *b_mode_truth_multiple;   //!
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
   TBranch        *b_beamwgt;   //!
   TBranch        *b_tpx_flux;   //!
   TBranch        *b_tpy_flux;   //!
   TBranch        *b_tpz_flux;   //!
   TBranch        *b_tptype_flux;   //!
   TBranch        *b_nvertices;   //!
   TBranch        *b_vtx_x;   //!
   TBranch        *b_vtx_y;   //!
   TBranch        *b_vtx_z;   //!
   TBranch        *b_vtx_w0;   //!
   TBranch        *b_vtx_w1;   //!
   TBranch        *b_vtx_t0;   //!
   TBranch        *b_vtx_t1;   //!
   TBranch        *b_no_dead_wires_muon;   //!
   TBranch        *b_no_hits;   //!
   TBranch        *b_hit_plane;   //!
   TBranch        *b_hit_wire;   //!
   TBranch        *b_hit_channel;   //!
   TBranch        *b_hit_peakT;   //!
   TBranch        *b_hit_peakTcorr;   //!
   TBranch        *b_hit_charge;   //!
   TBranch        *b_hit_ph;   //!
   TBranch        *b_hit_trkid;   //!
   TBranch        *b_hit_etruth;   //!
   TBranch        *b_hit_rawdQds;   //!
   TBranch        *b_hit_dQds;   //!
   TBranch        *b_hit_dEds;   //!
   TBranch        *b_hit_ds;   //!
   TBranch        *b_hit_resrange;   //!
   TBranch        *b_hit_x;   //!
   TBranch        *b_hit_y;   //!
   TBranch        *b_hit_z;   //!
   TBranch        *b_no_clusters;   //!
   TBranch        *b_clusters_planeNo;   //!
   TBranch        *b_Start_pt_w_Cl;   //!
   TBranch        *b_Start_pt_t_Cl;   //!
   TBranch        *b_End_pt_w_Cl;   //!
   TBranch        *b_End_pt_t_Cl;   //!
   TBranch        *b_fNhitsClust;   //!
   TBranch        *b_two_trackstart_dcosx_reco;   //!
   TBranch        *b_two_trackstart_dcosy_reco;   //!
   TBranch        *b_two_trackstart_dcosz_reco;   //!
   TBranch        *b_two_trackexit_dcosx_reco;   //!
   TBranch        *b_two_trackexit_dcosy_reco;   //!
   TBranch        *b_two_trackexit_dcosz_reco;   //!
   TBranch        *b_no_primaries;   //!
   TBranch        *b_geant_list_size;   //!
   TBranch        *b_pdg;   //!
   TBranch        *b_Eng;   //!
   TBranch        *b_Px;   //!
   TBranch        *b_Py;   //!
   TBranch        *b_Pz;   //!
   TBranch        *b_StartPointx;   //!
   TBranch        *b_StartPointy;   //!
   TBranch        *b_StartPointz;   //!
   TBranch        *b_EndPointx;   //!
   TBranch        *b_EndPointy;   //!
   TBranch        *b_EndPointz;   //!
   TBranch        *b_NumberDaughters;   //!
   TBranch        *b_Mother;   //!
   TBranch        *b_TrackId;   //!
   TBranch        *b_process_primary;   //!
   TBranch        *b_orig;   //!
   TBranch        *b_Kin_Eng_reco;   //!
   TBranch        *b_muon_Kin_Eng_reco;   //!
   TBranch        *b_genie_no_primaries;   //!
   TBranch        *b_genie_primaries_pdg;   //!
   TBranch        *b_genie_Eng;   //!
   TBranch        *b_genie_Px;   //!
   TBranch        *b_genie_Py;   //!
   TBranch        *b_genie_Pz;   //!
   TBranch        *b_genie_P;   //!
   TBranch        *b_genie_status_code;   //!
   TBranch        *b_genie_mass;   //!
   TBranch        *b_genie_trackID;   //!
   TBranch        *b_genie_ND;   //!
   TBranch        *b_genie_mother;   //!
   TBranch        *b_evtwgt_nfunc;   //!
   TBranch        *b_evtwgt_funcname;   //!
   TBranch        *b_evtwgt_nweight;   //!
   TBranch        *b_evtwgt_weight;   //!
   TBranch        *b_pmttime;   //!
   TBranch        *b_pmt1;   //!
   TBranch        *b_pmt2;   //!
   TBranch        *b_pmt3;   //!
   TBranch        *b_pmt4;   //!
   TBranch        *b_pNumuCC;   //!
   TBranch        *b_pNueCC;   //!
   TBranch        *b_pNC;   //!
   TBranch        *b_pNumuCC2;   //!
   TBranch        *b_pNueCC2;   //!
   TBranch        *b_pNC2;   //!

};

#endif
