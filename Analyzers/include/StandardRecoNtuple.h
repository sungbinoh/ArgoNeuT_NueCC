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


void ana::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   nuPDG_truth_multiple = 0;
   ccnc_truth_multiple = 0;
   mode_truth_multiple = 0;
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
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("subrun", &subrun, &b_subrun);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("evttime", &evttime, &b_evttime);
   fChain->SetBranchAddress("beamtime", &beamtime, &b_beamtime);
   fChain->SetBranchAddress("pot", &pot, &b_pot);
   fChain->SetBranchAddress("isdata", &isdata, &b_isdata);
   fChain->SetBranchAddress("taulife", &taulife, &b_taulife);
   fChain->SetBranchAddress("vtxx_reco", &vtxx_reco, &b_vtxx_reco);
   fChain->SetBranchAddress("vtxy_reco", &vtxy_reco, &b_vtxy_reco);
   fChain->SetBranchAddress("vtxz_reco", &vtxz_reco, &b_vtxz_reco);
   fChain->SetBranchAddress("nclusu_reco", &nclusu_reco, &b_nclusu_reco);
   fChain->SetBranchAddress("nclusv_reco", &nclusv_reco, &b_nclusv_reco);
   fChain->SetBranchAddress("nclusw_reco", &nclusw_reco, &b_nclusw_reco);
   fChain->SetBranchAddress("ntracks_reco", &ntracks_reco, &b_ntracks_reco);
   fChain->SetBranchAddress("nvertextracks_reco", &nvertextracks_reco, &b_nvertextracks_reco);
   fChain->SetBranchAddress("nvertexclustersu_reco", &nvertexclustersu_reco, &b_nvertexclustersu_reco);
   fChain->SetBranchAddress("nvertexclustersv_reco", &nvertexclustersv_reco, &b_nvertexclustersv_reco);
   fChain->SetBranchAddress("nvertexclustersw_reco", &nvertexclustersw_reco, &b_nvertexclustersw_reco);
   fChain->SetBranchAddress("ntrackendonboundary_reco", &ntrackendonboundary_reco, &b_ntrackendonboundary_reco);
   fChain->SetBranchAddress("nearestx", nearestx, &b_nearestx);
   fChain->SetBranchAddress("nearesty", nearesty, &b_nearesty);
   fChain->SetBranchAddress("nearestz", nearestz, &b_nearestz);
   fChain->SetBranchAddress("trackstart_dcosx_reco", &trackstart_dcosx_reco, &b_trackstart_dcosx_reco);
   fChain->SetBranchAddress("trackstart_dcosy_reco", &trackstart_dcosy_reco, &b_trackstart_dcosy_reco);
   fChain->SetBranchAddress("trackstart_dcosz_reco", &trackstart_dcosz_reco, &b_trackstart_dcosz_reco);
   fChain->SetBranchAddress("trackexit_dcosx_reco", &trackexit_dcosx_reco, &b_trackexit_dcosx_reco);
   fChain->SetBranchAddress("trackexit_dcosy_reco", &trackexit_dcosy_reco, &b_trackexit_dcosy_reco);
   fChain->SetBranchAddress("trackexit_dcosz_reco", &trackexit_dcosz_reco, &b_trackexit_dcosz_reco);
   fChain->SetBranchAddress("trackstart_x_reco", &trackstart_x_reco, &b_trackstart_x_reco);
   fChain->SetBranchAddress("trackstart_y_reco", &trackstart_y_reco, &b_trackstart_y_reco);
   fChain->SetBranchAddress("trackstart_z_reco", &trackstart_z_reco, &b_trackstart_z_reco);
   fChain->SetBranchAddress("trackexit_x_reco", &trackexit_x_reco, &b_trackexit_x_reco);
   fChain->SetBranchAddress("trackexit_y_reco", &trackexit_y_reco, &b_trackexit_y_reco);
   fChain->SetBranchAddress("trackexit_z_reco", &trackexit_z_reco, &b_trackexit_z_reco);
   fChain->SetBranchAddress("enu_reco", &enu_reco, &b_enu_reco);
   fChain->SetBranchAddress("nclupertrack_reco", &nclupertrack_reco, &b_nclupertrack_reco);
   fChain->SetBranchAddress("trkvtxx", trkvtxx, &b_trkvtxx);
   fChain->SetBranchAddress("trkvtxy", trkvtxy, &b_trkvtxy);
   fChain->SetBranchAddress("trkvtxz", trkvtxz, &b_trkvtxz);
   fChain->SetBranchAddress("trkendx", trkendx, &b_trkendx);
   fChain->SetBranchAddress("trkendy", trkendy, &b_trkendy);
   fChain->SetBranchAddress("trkendz", trkendz, &b_trkendz);
   fChain->SetBranchAddress("trkstartdcosx", trkstartdcosx, &b_trkstartdcosx);
   fChain->SetBranchAddress("trkstartdcosy", trkstartdcosy, &b_trkstartdcosy);
   fChain->SetBranchAddress("trkstartdcosz", trkstartdcosz, &b_trkstartdcosz);
   fChain->SetBranchAddress("trkenddcosx", trkenddcosx, &b_trkenddcosx);
   fChain->SetBranchAddress("trkenddcosy", trkenddcosy, &b_trkenddcosy);
   fChain->SetBranchAddress("trkenddcosz", trkenddcosz, &b_trkenddcosz);
   fChain->SetBranchAddress("trkke", trkke, &b_trkke);
   fChain->SetBranchAddress("trkrange", trkrange, &b_trkrange);
   fChain->SetBranchAddress("trkpitchc", trkpitchc, &b_trkpitchc);
   fChain->SetBranchAddress("nmaxtrkhits", nmaxtrkhits, &b_nmaxtrkhits);
   fChain->SetBranchAddress("ntrkhits", ntrkhits, &b_ntrkhits);
   fChain->SetBranchAddress("trkdedx", trkdedx, &b_trkdedx);
   fChain->SetBranchAddress("trkdqdx", trkdqdx, &b_trkdqdx);
   fChain->SetBranchAddress("trkresrg", trkresrg, &b_trkresrg);
   fChain->SetBranchAddress("trkhitindexc", trkhitindexc, &b_trkhitindexc);
   fChain->SetBranchAddress("trkpid", trkpid, &b_trkpid);
   fChain->SetBranchAddress("trkpidndf", trkpidndf, &b_trkpidndf);
   fChain->SetBranchAddress("trkpidchi2", trkpidchi2, &b_trkpidchi2);
   fChain->SetBranchAddress("trkpida", trkpida, &b_trkpida);
   fChain->SetBranchAddress("trkmissinge", trkmissinge, &b_trkmissinge);
   fChain->SetBranchAddress("trkmissingeavg", trkmissingeavg, &b_trkmissingeavg);
   fChain->SetBranchAddress("trktruepdgu", trktruepdgu, &b_trktruepdgu);
   fChain->SetBranchAddress("trktrueeffu", trktrueeffu, &b_trktrueeffu);
   fChain->SetBranchAddress("trktruepuru", trktruepuru, &b_trktruepuru);
   fChain->SetBranchAddress("trktruepdgv", trktruepdgv, &b_trktruepdgv);
   fChain->SetBranchAddress("trktrueeffv", trktrueeffv, &b_trktrueeffv);
   fChain->SetBranchAddress("trktruepurv", trktruepurv, &b_trktruepurv);
   fChain->SetBranchAddress("trkg4Id", trkg4Id, &b_trkg4Id);
   fChain->SetBranchAddress("nshws", &nshws, &b_nshws);
   fChain->SetBranchAddress("shwid", &shwid, &b_shwid);
   fChain->SetBranchAddress("shwdcosx", &shwdcosx, &b_shwdcosx);
   fChain->SetBranchAddress("shwdcosy", &shwdcosy, &b_shwdcosy);
   fChain->SetBranchAddress("shwdcosz", &shwdcosz, &b_shwdcosz);
   fChain->SetBranchAddress("shwstartx", &shwstartx, &b_shwstartx);
   fChain->SetBranchAddress("shwstarty", &shwstarty, &b_shwstarty);
   fChain->SetBranchAddress("shwstartz", &shwstartz, &b_shwstartz);
   fChain->SetBranchAddress("shwenergy", &shwenergy, &b_shwenergy);
   fChain->SetBranchAddress("shwdedx", &shwdedx, &b_shwdedx);
   fChain->SetBranchAddress("shwbestplane", &shwbestplane, &b_shwbestplane);
   fChain->SetBranchAddress("shwg4id", &shwg4id, &b_shwg4id);
   fChain->SetBranchAddress("nmatched_reco", &nmatched_reco, &b_nmatched_reco);
   fChain->SetBranchAddress("trk_mom_minos", &trk_mom_minos, &b_trk_mom_minos);
   fChain->SetBranchAddress("trk_charge_minos", &trk_charge_minos, &b_trk_charge_minos);
   fChain->SetBranchAddress("trk_dcosx_minos", &trk_dcosx_minos, &b_trk_dcosx_minos);
   fChain->SetBranchAddress("trk_dcosy_minos", &trk_dcosy_minos, &b_trk_dcosy_minos);
   fChain->SetBranchAddress("trk_dcosz_minos", &trk_dcosz_minos, &b_trk_dcosz_minos);
   fChain->SetBranchAddress("trk_vtxx_minos", &trk_vtxx_minos, &b_trk_vtxx_minos);
   fChain->SetBranchAddress("trk_vtxy_minos", &trk_vtxy_minos, &b_trk_vtxy_minos);
   fChain->SetBranchAddress("trk_vtxz_minos", &trk_vtxz_minos, &b_trk_vtxz_minos);
   fChain->SetBranchAddress("trk_index_minos", &trk_index_minos, &b_trk_index_minos);
   fChain->SetBranchAddress("minostrk_index_minos", &minostrk_index_minos, &b_minostrk_index_minos);
   fChain->SetBranchAddress("mc_index_minos", &mc_index_minos, &b_mc_index_minos);
   fChain->SetBranchAddress("mc_pdg_minos", &mc_pdg_minos, &b_mc_pdg_minos);
   fChain->SetBranchAddress("mc_px_minos", &mc_px_minos, &b_mc_px_minos);
   fChain->SetBranchAddress("mc_py_minos", &mc_py_minos, &b_mc_py_minos);
   fChain->SetBranchAddress("mc_pz_minos", &mc_pz_minos, &b_mc_pz_minos);
   fChain->SetBranchAddress("mc_ene_minos", &mc_ene_minos, &b_mc_ene_minos);
   fChain->SetBranchAddress("mc_mass_minos", &mc_mass_minos, &b_mc_mass_minos);
   fChain->SetBranchAddress("mc_vtxx_minos", &mc_vtxx_minos, &b_mc_vtxx_minos);
   fChain->SetBranchAddress("mc_vtxy_minos", &mc_vtxy_minos, &b_mc_vtxy_minos);
   fChain->SetBranchAddress("mc_vtxz_minos", &mc_vtxz_minos, &b_mc_vtxz_minos);
   fChain->SetBranchAddress("trkcontained_minos", &trkcontained_minos, &b_trkcontained_minos);
   fChain->SetBranchAddress("test_charge_minos", &test_charge_minos, &b_test_charge_minos);
   fChain->SetBranchAddress("rdiff_minos", &rdiff_minos, &b_rdiff_minos);
   fChain->SetBranchAddress("xdiff_minos", &xdiff_minos, &b_xdiff_minos);
   fChain->SetBranchAddress("ydiff_minos", &ydiff_minos, &b_ydiff_minos);
   fChain->SetBranchAddress("thetadiff_minos", &thetadiff_minos, &b_thetadiff_minos);
   fChain->SetBranchAddress("ntracks_minos", &ntracks_minos, &b_ntracks_minos);
   fChain->SetBranchAddress("trk_vtxx_all_minos", trk_vtxx_all_minos, &b_trk_vtxx_all_minos);
   fChain->SetBranchAddress("trk_vtxy_all_minos", trk_vtxy_all_minos, &b_trk_vtxy_all_minos);
   fChain->SetBranchAddress("trk_vtxz_all_minos", trk_vtxz_all_minos, &b_trk_vtxz_all_minos);
   fChain->SetBranchAddress("trk_dcosx_all_minos", trk_dcosx_all_minos, &b_trk_dcosx_all_minos);
   fChain->SetBranchAddress("trk_dcosy_all_minos", trk_dcosy_all_minos, &b_trk_dcosy_all_minos);
   fChain->SetBranchAddress("trk_dcosz_all_minos", trk_dcosz_all_minos, &b_trk_dcosz_all_minos);
   fChain->SetBranchAddress("trk_chi2_minos", trk_chi2_minos, &b_trk_chi2_minos);
   fChain->SetBranchAddress("trk_qp_minos", trk_qp_minos, &b_trk_qp_minos);
   fChain->SetBranchAddress("trk_eqp_minos", trk_eqp_minos, &b_trk_eqp_minos);
   fChain->SetBranchAddress("trk_erange_minos", trk_erange_minos, &b_trk_erange_minos);
   fChain->SetBranchAddress("trk_e_minos", trk_e_minos, &b_trk_e_minos);
   fChain->SetBranchAddress("shw_e_minos", shw_e_minos, &b_shw_e_minos);
   fChain->SetBranchAddress("trk_mom_all_minos", trk_mom_all_minos, &b_trk_mom_all_minos);
   fChain->SetBranchAddress("trk_contained_minos", trk_contained_minos, &b_trk_contained_minos);
   fChain->SetBranchAddress("trk_xpred_minos", trk_xpred_minos, &b_trk_xpred_minos);
   fChain->SetBranchAddress("trk_ypred_minos", trk_ypred_minos, &b_trk_ypred_minos);
   fChain->SetBranchAddress("parpdg", &parpdg, &b_parpdg);
   fChain->SetBranchAddress("parmom", &parmom, &b_parmom);
   fChain->SetBranchAddress("nuPDG_truth", &nuPDG_truth, &b_nuPDG_truth);
   fChain->SetBranchAddress("ccnc_truth", &ccnc_truth, &b_ccnc_truth);
   fChain->SetBranchAddress("mode_truth", &mode_truth, &b_mode_truth);
   fChain->SetBranchAddress("enu_truth", &enu_truth, &b_enu_truth);
   fChain->SetBranchAddress("Q2_truth", &Q2_truth, &b_Q2_truth);
   fChain->SetBranchAddress("hitnuc_truth", &hitnuc_truth, &b_hitnuc_truth);
   fChain->SetBranchAddress("W_truth", &W_truth, &b_W_truth);
   fChain->SetBranchAddress("nuvtxx_truth", &nuvtxx_truth, &b_nuvtxx_truth);
   fChain->SetBranchAddress("nuvtxy_truth", &nuvtxy_truth, &b_nuvtxy_truth);
   fChain->SetBranchAddress("nuvtxz_truth", &nuvtxz_truth, &b_nuvtxz_truth);
   fChain->SetBranchAddress("nu_dcosx_truth", &nu_dcosx_truth, &b_nu_dcosx_truth);
   fChain->SetBranchAddress("nu_dcosy_truth", &nu_dcosy_truth, &b_nu_dcosy_truth);
   fChain->SetBranchAddress("nu_dcosz_truth", &nu_dcosz_truth, &b_nu_dcosz_truth);
   fChain->SetBranchAddress("lep_mom_truth", &lep_mom_truth, &b_lep_mom_truth);
   fChain->SetBranchAddress("lep_dcosx_truth", &lep_dcosx_truth, &b_lep_dcosx_truth);
   fChain->SetBranchAddress("lep_dcosy_truth", &lep_dcosy_truth, &b_lep_dcosy_truth);
   fChain->SetBranchAddress("lep_dcosz_truth", &lep_dcosz_truth, &b_lep_dcosz_truth);
   fChain->SetBranchAddress("mcevts_truth", &mcevts_truth, &b_mcevts_truth);
   fChain->SetBranchAddress("nuPDG_truth_multiple", &nuPDG_truth_multiple, &b_nuPDG_truth_multiple);
   fChain->SetBranchAddress("ccnc_truth_multiple", &ccnc_truth_multiple, &b_ccnc_truth_multiple);
   fChain->SetBranchAddress("mode_truth_multiple", &mode_truth_multiple, &b_mode_truth_multiple);
   fChain->SetBranchAddress("enu_truth_multiple", &enu_truth_multiple, &b_enu_truth_multiple);
   fChain->SetBranchAddress("nuvtxx_truth_multiple", &nuvtxx_truth_multiple, &b_nuvtxx_truth_multiple);
   fChain->SetBranchAddress("nuvtxy_truth_multiple", &nuvtxy_truth_multiple, &b_nuvtxy_truth_multiple);
   fChain->SetBranchAddress("nuvtxz_truth_multiple", &nuvtxz_truth_multiple, &b_nuvtxz_truth_multiple);
   fChain->SetBranchAddress("nu_dcosx_truth_multiple", &nu_dcosx_truth_multiple, &b_nu_dcosx_truth_multiple);
   fChain->SetBranchAddress("nu_dcosy_truth_multiple", &nu_dcosy_truth_multiple, &b_nu_dcosy_truth_multiple);
   fChain->SetBranchAddress("nu_dcosz_truth_multiple", &nu_dcosz_truth_multiple, &b_nu_dcosz_truth_multiple);
   fChain->SetBranchAddress("lep_mom_truth_multiple", &lep_mom_truth_multiple, &b_lep_mom_truth_multiple);
   fChain->SetBranchAddress("lep_dcosx_truth_multiple", &lep_dcosx_truth_multiple, &b_lep_dcosx_truth_multiple);
   fChain->SetBranchAddress("lep_dcosy_truth_multiple", &lep_dcosy_truth_multiple, &b_lep_dcosy_truth_multiple);
   fChain->SetBranchAddress("lep_dcosz_truth_multiple", &lep_dcosz_truth_multiple, &b_lep_dcosz_truth_multiple);
   fChain->SetBranchAddress("beamwgt", &beamwgt, &b_beamwgt);
   fChain->SetBranchAddress("tpx_flux", &tpx_flux, &b_tpx_flux);
   fChain->SetBranchAddress("tpy_flux", &tpy_flux, &b_tpy_flux);
   fChain->SetBranchAddress("tpz_flux", &tpz_flux, &b_tpz_flux);
   fChain->SetBranchAddress("tptype_flux", &tptype_flux, &b_tptype_flux);
   fChain->SetBranchAddress("nvertices", &nvertices, &b_nvertices);
   fChain->SetBranchAddress("vtx_x", vtx_x, &b_vtx_x);
   fChain->SetBranchAddress("vtx_y", vtx_y, &b_vtx_y);
   fChain->SetBranchAddress("vtx_z", vtx_z, &b_vtx_z);
   fChain->SetBranchAddress("vtx_w0", vtx_w0, &b_vtx_w0);
   fChain->SetBranchAddress("vtx_w1", vtx_w1, &b_vtx_w1);
   fChain->SetBranchAddress("vtx_t0", vtx_t0, &b_vtx_t0);
   fChain->SetBranchAddress("vtx_t1", vtx_t1, &b_vtx_t1);
   fChain->SetBranchAddress("no_dead_wires_muon", &no_dead_wires_muon, &b_no_dead_wires_muon);
   fChain->SetBranchAddress("no_hits", &no_hits, &b_no_hits);
   fChain->SetBranchAddress("hit_plane", hit_plane, &b_hit_plane);
   fChain->SetBranchAddress("hit_wire", hit_wire, &b_hit_wire);
   fChain->SetBranchAddress("hit_channel", hit_channel, &b_hit_channel);
   fChain->SetBranchAddress("hit_peakT", hit_peakT, &b_hit_peakT);
   fChain->SetBranchAddress("hit_peakTcorr", hit_peakTcorr, &b_hit_peakTcorr);
   fChain->SetBranchAddress("hit_charge", hit_charge, &b_hit_charge);
   fChain->SetBranchAddress("hit_ph", hit_ph, &b_hit_ph);
   fChain->SetBranchAddress("hit_trkid", hit_trkid, &b_hit_trkid);
   fChain->SetBranchAddress("hit_etruth", hit_etruth, &b_hit_etruth);
   fChain->SetBranchAddress("hit_rawdQds", hit_rawdQds, &b_hit_rawdQds);
   fChain->SetBranchAddress("hit_dQds", hit_dQds, &b_hit_dQds);
   fChain->SetBranchAddress("hit_dEds", hit_dEds, &b_hit_dEds);
   fChain->SetBranchAddress("hit_ds", hit_ds, &b_hit_ds);
   fChain->SetBranchAddress("hit_resrange", hit_resrange, &b_hit_resrange);
   fChain->SetBranchAddress("hit_x", hit_x, &b_hit_x);
   fChain->SetBranchAddress("hit_y", hit_y, &b_hit_y);
   fChain->SetBranchAddress("hit_z", hit_z, &b_hit_z);
   fChain->SetBranchAddress("no_clusters", &no_clusters, &b_no_clusters);
   fChain->SetBranchAddress("clusters_planeNo", clusters_planeNo, &b_clusters_planeNo);
   fChain->SetBranchAddress("Start_pt_w_Cl", Start_pt_w_Cl, &b_Start_pt_w_Cl);
   fChain->SetBranchAddress("Start_pt_t_Cl", Start_pt_t_Cl, &b_Start_pt_t_Cl);
   fChain->SetBranchAddress("End_pt_w_Cl", End_pt_w_Cl, &b_End_pt_w_Cl);
   fChain->SetBranchAddress("End_pt_t_Cl", End_pt_t_Cl, &b_End_pt_t_Cl);
   fChain->SetBranchAddress("fNhitsClust", &fNhitsClust, &b_fNhitsClust);
   fChain->SetBranchAddress("two_trackstart_dcosx_reco", two_trackstart_dcosx_reco, &b_two_trackstart_dcosx_reco);
   fChain->SetBranchAddress("two_trackstart_dcosy_reco", two_trackstart_dcosy_reco, &b_two_trackstart_dcosy_reco);
   fChain->SetBranchAddress("two_trackstart_dcosz_reco", two_trackstart_dcosz_reco, &b_two_trackstart_dcosz_reco);
   fChain->SetBranchAddress("two_trackexit_dcosx_reco", two_trackexit_dcosx_reco, &b_two_trackexit_dcosx_reco);
   fChain->SetBranchAddress("two_trackexit_dcosy_reco", two_trackexit_dcosy_reco, &b_two_trackexit_dcosy_reco);
   fChain->SetBranchAddress("two_trackexit_dcosz_reco", two_trackexit_dcosz_reco, &b_two_trackexit_dcosz_reco);
   fChain->SetBranchAddress("no_primaries", &no_primaries, &b_no_primaries);
   fChain->SetBranchAddress("geant_list_size", &geant_list_size, &b_geant_list_size);
   fChain->SetBranchAddress("pdg", pdg, &b_pdg);
   fChain->SetBranchAddress("Eng", Eng, &b_Eng);
   fChain->SetBranchAddress("Px", Px, &b_Px);
   fChain->SetBranchAddress("Py", Py, &b_Py);
   fChain->SetBranchAddress("Pz", Pz, &b_Pz);
   fChain->SetBranchAddress("StartPointx", StartPointx, &b_StartPointx);
   fChain->SetBranchAddress("StartPointy", StartPointy, &b_StartPointy);
   fChain->SetBranchAddress("StartPointz", StartPointz, &b_StartPointz);
   fChain->SetBranchAddress("EndPointx", EndPointx, &b_EndPointx);
   fChain->SetBranchAddress("EndPointy", EndPointy, &b_EndPointy);
   fChain->SetBranchAddress("EndPointz", EndPointz, &b_EndPointz);
   fChain->SetBranchAddress("NumberDaughters", NumberDaughters, &b_NumberDaughters);
   fChain->SetBranchAddress("Mother", Mother, &b_Mother);
   fChain->SetBranchAddress("TrackId", TrackId, &b_TrackId);
   fChain->SetBranchAddress("process_primary", process_primary, &b_process_primary);
   fChain->SetBranchAddress("orig", orig, &b_orig);
   fChain->SetBranchAddress("Kin_Eng_reco", Kin_Eng_reco, &b_Kin_Eng_reco);
   fChain->SetBranchAddress("muon_Kin_Eng_reco", &muon_Kin_Eng_reco, &b_muon_Kin_Eng_reco);
   fChain->SetBranchAddress("genie_no_primaries", &genie_no_primaries, &b_genie_no_primaries);
   fChain->SetBranchAddress("genie_primaries_pdg", genie_primaries_pdg, &b_genie_primaries_pdg);
   fChain->SetBranchAddress("genie_Eng", genie_Eng, &b_genie_Eng);
   fChain->SetBranchAddress("genie_Px", genie_Px, &b_genie_Px);
   fChain->SetBranchAddress("genie_Py", genie_Py, &b_genie_Py);
   fChain->SetBranchAddress("genie_Pz", genie_Pz, &b_genie_Pz);
   fChain->SetBranchAddress("genie_P", genie_P, &b_genie_P);
   fChain->SetBranchAddress("genie_status_code", genie_status_code, &b_genie_status_code);
   fChain->SetBranchAddress("genie_mass", genie_mass, &b_genie_mass);
   fChain->SetBranchAddress("genie_trackID", genie_trackID, &b_genie_trackID);
   fChain->SetBranchAddress("genie_ND", genie_ND, &b_genie_ND);
   fChain->SetBranchAddress("genie_mother", genie_mother, &b_genie_mother);
   fChain->SetBranchAddress("evtwgt_nfunc", &evtwgt_nfunc, &b_evtwgt_nfunc);
   fChain->SetBranchAddress("evtwgt_funcname", &evtwgt_funcname, &b_evtwgt_funcname);
   fChain->SetBranchAddress("evtwgt_nweight", &evtwgt_nweight, &b_evtwgt_nweight);
   fChain->SetBranchAddress("evtwgt_weight", &evtwgt_weight, &b_evtwgt_weight);
   fChain->SetBranchAddress("pmttime", &pmttime, &b_pmttime);
   fChain->SetBranchAddress("pmt1", pmt1, &b_pmt1);
   fChain->SetBranchAddress("pmt2", pmt2, &b_pmt2);
   fChain->SetBranchAddress("pmt3", pmt3, &b_pmt3);
   fChain->SetBranchAddress("pmt4", pmt4, &b_pmt4);
   fChain->SetBranchAddress("pNumuCC", &pNumuCC, &b_pNumuCC);
   fChain->SetBranchAddress("pNueCC", &pNueCC, &b_pNueCC);
   fChain->SetBranchAddress("pNC", &pNC, &b_pNC);
   fChain->SetBranchAddress("pNumuCC2", &pNumuCC2, &b_pNumuCC2);
   fChain->SetBranchAddress("pNueCC2", &pNueCC2, &b_pNueCC2);
   fChain->SetBranchAddress("pNC2", &pNC2, &b_pNC2);
   Notify();
}

Bool_t ana::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ana::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ana::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ana_cxx
