#define fill_hists5_cxx
#include "fill_hists5.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "utils.c"
#include "histio.c"

//
//  This version only uses observable quantities for the selection (no gen stuff).
//
//
//
//  Before doing
//
//    .L fill_hists5.c
//
//  do
//
//   gSystem -> Load( "../RooUnfold/build/libRooUnfold.dylib" ) ;
//
//

void fill_hists5::Loop( bool verbose, int last_event, int first_event, const char* out_file )
{

   //////float wgt = 1. ; // for athena only

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();

   gDirectory -> Delete( "h*" ) ;

   printf("\n\n Ntuple has %lld entries\n\n", nentries ) ;


   float good_range_xmin = 0.0005 ;
   float good_range_xmax = 1.0 ;

   float good_range_ymin = 0.01  ;
   float good_range_ymax = 1.0  ;

   float good_range_q2min = 250 ;
   float good_range_q2max = 50000 ;





   printf("\n\n") ;


   TH2F* h_q2_vs_x_obs_dnn_sel = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_dnn_sel" ) ;
   TH2F* h_q2_vs_x_obs_e_sel = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_e_sel" ) ;
   TH2F* h_q2_vs_x_obs_esigma_sel = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_esigma_sel" ) ;
   TH2F* h_q2_vs_x_obs_isigma_sel = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_isigma_sel" ) ;
   TH2F* h_q2_vs_x_obs_da_sel = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_da_sel" ) ;

   TH2F* h_q2_vs_x_obs_gen_same_dnn_sel = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_gen_same_dnn_sel" ) ;
   TH2F* h_q2_vs_x_obs_gen_same_e_sel = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_gen_same_e_sel" ) ;
   TH2F* h_q2_vs_x_obs_gen_same_esigma_sel = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_gen_same_esigma_sel" ) ;
   TH2F* h_q2_vs_x_obs_gen_same_isigma_sel = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_gen_same_isigma_sel" ) ;
   TH2F* h_q2_vs_x_obs_gen_same_da_sel = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_gen_same_da_sel" ) ;



   TH2Poly* h_q2_vs_x_meas_binning_obs_dnn_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_meas_binning_obs_dnn_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_e_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_meas_binning_obs_e_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_esigma_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_meas_binning_obs_esigma_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_isigma_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_meas_binning_obs_isigma_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_da_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_meas_binning_obs_da_sel" ) ;

   TH2Poly* h_q2_vs_x_meas_binning_obs_gen_same_dnn_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_meas_binning_obs_gen_same_dnn_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_gen_same_e_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_meas_binning_obs_gen_same_e_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_gen_same_esigma_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_meas_binning_obs_gen_same_esigma_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_gen_same_isigma_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_meas_binning_obs_gen_same_isigma_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_gen_same_da_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_meas_binning_obs_gen_same_da_sel" ) ;







   TH2Poly* h_q2_vs_x_gen_no_cuts = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_gen_no_cuts" ) ;

   TH2Poly* h_q2_vs_x_gen_dnn_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_gen_dnn_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_e_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_gen_e_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_esigma_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_gen_esigma_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_isigma_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_gen_isigma_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_da_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_gen_da_sel" ) ;


   TH2Poly* h_q2_vs_x_gen_rec_same_dnn_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_gen_rec_same_dnn_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_rec_same_e_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_gen_rec_same_e_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_rec_same_esigma_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_gen_rec_same_esigma_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_rec_same_isigma_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_gen_rec_same_isigma_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_rec_same_da_sel = make_q2_vs_x_h1_binning_poly( "h_q2_vs_x_gen_rec_same_da_sel" ) ;








   TH2Poly* h_dummy_q2_vs_x_gen = make_q2_vs_x_h1_binning_poly( "h_dummy_q2_vs_x_gen" ) ;
   TH2F* h_dummy_q2_vs_x_obs = make_q2_vs_x_fine_h1_binning( "h_dummy_q2_vs_x_obs" ) ;



   RooUnfoldResponse* rur_2D_q2_vs_x_dnn = new RooUnfoldResponse( h_dummy_q2_vs_x_obs, h_dummy_q2_vs_x_gen, "rur_2D_q2_vs_x_dnn", "rur_2D_q2_vs_x_dnn" ) ;
   RooUnfoldResponse* rur_2D_q2_vs_x_e = new RooUnfoldResponse( h_dummy_q2_vs_x_obs, h_dummy_q2_vs_x_gen, "rur_2D_q2_vs_x_e", "rur_2D_q2_vs_x_e" ) ;
   RooUnfoldResponse* rur_2D_q2_vs_x_esigma = new RooUnfoldResponse( h_dummy_q2_vs_x_obs, h_dummy_q2_vs_x_gen, "rur_2D_q2_vs_x_esigma", "rur_2D_q2_vs_x_esigma" ) ;
   RooUnfoldResponse* rur_2D_q2_vs_x_isigma = new RooUnfoldResponse( h_dummy_q2_vs_x_obs, h_dummy_q2_vs_x_gen, "rur_2D_q2_vs_x_isigma", "rur_2D_q2_vs_x_isigma" ) ;
   RooUnfoldResponse* rur_2D_q2_vs_x_da = new RooUnfoldResponse( h_dummy_q2_vs_x_obs, h_dummy_q2_vs_x_gen, "rur_2D_q2_vs_x_da", "rur_2D_q2_vs_x_da" ) ;



   h_q2_vs_x_obs_dnn_sel    -> SetXTitle( "Obs x, dnn" ) ;
   h_q2_vs_x_obs_e_sel      -> SetXTitle( "Obs x, e" ) ;
   h_q2_vs_x_obs_esigma_sel -> SetXTitle( "Obs x, esigma" ) ;
   h_q2_vs_x_obs_isigma_sel -> SetXTitle( "Obs x, isigma" ) ;
   h_q2_vs_x_obs_da_sel     -> SetXTitle( "Obs x, da" ) ;

   h_q2_vs_x_obs_dnn_sel    -> SetYTitle( "Obs Q2, dnn" ) ;
   h_q2_vs_x_obs_e_sel      -> SetYTitle( "Obs Q2, e" ) ;
   h_q2_vs_x_obs_esigma_sel -> SetYTitle( "Obs Q2, esigma" ) ;
   h_q2_vs_x_obs_isigma_sel -> SetYTitle( "Obs Q2, isigma" ) ;
   h_q2_vs_x_obs_da_sel     -> SetYTitle( "Obs Q2, da" ) ;

   h_q2_vs_x_gen_no_cuts    -> SetXTitle( "Gen x" ) ;
   h_q2_vs_x_gen_dnn_sel    -> SetXTitle( "Gen x" ) ;
   h_q2_vs_x_gen_e_sel      -> SetXTitle( "Gen x" ) ;
   h_q2_vs_x_gen_esigma_sel -> SetXTitle( "Gen x" ) ;
   h_q2_vs_x_gen_isigma_sel -> SetXTitle( "Gen x" ) ;
   h_q2_vs_x_gen_da_sel     -> SetXTitle( "Gen x" ) ;

   h_q2_vs_x_gen_no_cuts    -> SetYTitle( "Gen Q2" ) ;
   h_q2_vs_x_gen_dnn_sel    -> SetYTitle( "Gen Q2" ) ;
   h_q2_vs_x_gen_e_sel      -> SetYTitle( "Gen Q2" ) ;
   h_q2_vs_x_gen_esigma_sel -> SetYTitle( "Gen Q2" ) ;
   h_q2_vs_x_gen_isigma_sel -> SetYTitle( "Gen Q2" ) ;
   h_q2_vs_x_gen_da_sel     -> SetYTitle( "Gen Q2" ) ;


   if ( last_event > 0 ) {
      nentries = last_event ;
   }

   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry=first_event; jentry<nentries;jentry++) {

      int ei = jentry ;

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ( !verbose && ei%100 == 0 ) {
         printf(" --- Event: %7d / %lld    %6.3f\r", ei, nentries, (1.*ei)/(1.*nentries) ) ;
         fflush(stdout) ;
      }


      h_q2_vs_x_gen_no_cuts -> Fill( from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;


      int meas_binning_gen_gbi = h_q2_vs_x_gen_dnn_sel -> FindBin( from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;
      int fine_binning_gen_gbi = h_q2_vs_x_obs_dnn_sel -> FindBin( from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;

      if ( ! pass_evt_sel ) continue ;


     //----------  DNN

      if (     dnn_Q2 >= good_range_q2min && dnn_Q2 <= good_range_q2max
            && dnn_x  >= good_range_xmin  && dnn_x  <= good_range_xmax
            && dnn_y  >= good_range_ymin  && dnn_y  <= good_range_ymax   ) {

         int meas_binning_obs_gbi = h_q2_vs_x_meas_binning_obs_dnn_sel -> FindBin( dnn_x, dnn_Q2, wgt ) ;
         int fine_binning_obs_gbi = h_q2_vs_x_obs_dnn_sel -> FindBin( dnn_x, dnn_Q2, wgt ) ;

         h_q2_vs_x_obs_dnn_sel -> Fill( dnn_x, dnn_Q2, wgt ) ;
         h_q2_vs_x_meas_binning_obs_dnn_sel -> Fill( dnn_x, dnn_Q2, wgt ) ;
         h_q2_vs_x_gen_dnn_sel -> Fill( from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;
         rur_2D_q2_vs_x_dnn -> Fill( dnn_x, dnn_Q2, from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;

         if ( meas_binning_gen_gbi == meas_binning_obs_gbi ) {
            h_q2_vs_x_meas_binning_obs_gen_same_dnn_sel -> Fill( dnn_x, dnn_Q2, wgt ) ;
            h_q2_vs_x_gen_rec_same_dnn_sel -> Fill( from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;
         }
         if ( fine_binning_gen_gbi == fine_binning_obs_gbi ) {
            h_q2_vs_x_obs_gen_same_dnn_sel -> Fill( dnn_x, dnn_Q2, wgt ) ;
         }

      }




     //----------  electron


      if (     obs_Q2_e >= good_range_q2min && obs_Q2_e <= good_range_q2max
            && obs_x_e  >= good_range_xmin  && obs_x_e  <= good_range_xmax
            && obs_y_e  >= good_range_ymin  && obs_y_e  <= good_range_ymax   ) {

         int meas_binning_obs_gbi = h_q2_vs_x_meas_binning_obs_dnn_sel -> FindBin( obs_x_e, obs_Q2_e, wgt ) ;
         int fine_binning_obs_gbi = h_q2_vs_x_obs_dnn_sel -> FindBin( obs_x_e, obs_Q2_e, wgt ) ;

         h_q2_vs_x_obs_e_sel -> Fill( obs_x_e, obs_Q2_e, wgt ) ;
         h_q2_vs_x_meas_binning_obs_e_sel -> Fill( obs_x_e, obs_Q2_e, wgt ) ;
         h_q2_vs_x_gen_e_sel -> Fill( from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;
         rur_2D_q2_vs_x_e -> Fill( obs_x_e, obs_Q2_e, from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;

         if ( meas_binning_gen_gbi == meas_binning_obs_gbi ) {
            h_q2_vs_x_meas_binning_obs_gen_same_e_sel -> Fill( obs_x_e, obs_Q2_e, wgt ) ;
            h_q2_vs_x_gen_rec_same_e_sel -> Fill( from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;
         }
         if ( fine_binning_gen_gbi == fine_binning_obs_gbi ) {
            h_q2_vs_x_obs_gen_same_e_sel -> Fill( obs_x_e, obs_Q2_e, wgt ) ;
         }

      }





     //----------  ISigma

      if (     obs_Q2_ISigma >= good_range_q2min && obs_Q2_ISigma <= good_range_q2max
            && obs_x_ISigma  >= good_range_xmin  && obs_x_ISigma  <= good_range_xmax
            && obs_y_ISigma  >= good_range_ymin  && obs_y_ISigma  <= good_range_ymax   ) {

         int meas_binning_obs_gbi = h_q2_vs_x_meas_binning_obs_dnn_sel -> FindBin( obs_x_ISigma, obs_Q2_ISigma, wgt ) ;
         int fine_binning_obs_gbi = h_q2_vs_x_obs_dnn_sel -> FindBin( obs_x_ISigma, obs_Q2_ISigma, wgt ) ;

         h_q2_vs_x_obs_isigma_sel -> Fill( obs_x_ISigma, obs_Q2_ISigma, wgt ) ;
         h_q2_vs_x_meas_binning_obs_isigma_sel -> Fill( obs_x_ISigma, obs_Q2_ISigma, wgt ) ;
         h_q2_vs_x_gen_isigma_sel -> Fill( from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;
         rur_2D_q2_vs_x_isigma -> Fill( obs_x_ISigma, obs_Q2_ISigma, from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;

         if ( meas_binning_gen_gbi == meas_binning_obs_gbi ) {
            h_q2_vs_x_meas_binning_obs_gen_same_isigma_sel -> Fill( obs_x_ISigma, obs_Q2_ISigma, wgt ) ;
            h_q2_vs_x_gen_rec_same_isigma_sel -> Fill( from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;
         }
         if ( fine_binning_gen_gbi == fine_binning_obs_gbi ) {
            h_q2_vs_x_obs_gen_same_isigma_sel -> Fill( obs_x_ISigma, obs_Q2_ISigma, wgt ) ;
         }

      }






     //----------  eSigma

      if (     obs_Q2_eSigma >= good_range_q2min && obs_Q2_eSigma <= good_range_q2max
            && obs_x_eSigma  >= good_range_xmin  && obs_x_eSigma  <= good_range_xmax
            && obs_y_eSigma  >= good_range_ymin  && obs_y_eSigma  <= good_range_ymax   ) {

         int meas_binning_obs_gbi = h_q2_vs_x_meas_binning_obs_dnn_sel -> FindBin( obs_x_eSigma, obs_Q2_eSigma, wgt ) ;
         int fine_binning_obs_gbi = h_q2_vs_x_obs_dnn_sel -> FindBin( obs_x_eSigma, obs_Q2_eSigma, wgt ) ;

         h_q2_vs_x_obs_esigma_sel -> Fill( obs_x_eSigma, obs_Q2_eSigma, wgt ) ;
         h_q2_vs_x_meas_binning_obs_esigma_sel -> Fill( obs_x_eSigma, obs_Q2_eSigma, wgt ) ;
         h_q2_vs_x_gen_esigma_sel -> Fill( from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;
         rur_2D_q2_vs_x_esigma -> Fill( obs_x_eSigma, obs_Q2_eSigma, from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;

         if ( meas_binning_gen_gbi == meas_binning_obs_gbi ) {
            h_q2_vs_x_meas_binning_obs_gen_same_esigma_sel -> Fill( obs_x_eSigma, obs_Q2_eSigma, wgt ) ;
            h_q2_vs_x_gen_rec_same_esigma_sel -> Fill( from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;
         }
         if ( fine_binning_gen_gbi == fine_binning_obs_gbi ) {
            h_q2_vs_x_obs_gen_same_esigma_sel -> Fill( obs_x_eSigma, obs_Q2_eSigma, wgt ) ;
         }

      }





     //----------  DA

      if (     obs_Q2_DA >= good_range_q2min && obs_Q2_DA <= good_range_q2max
            && obs_x_DA  >= good_range_xmin  && obs_x_DA  <= good_range_xmax
            && obs_y_DA  >= good_range_ymin  && obs_y_DA  <= good_range_ymax   ) {

         int meas_binning_obs_gbi = h_q2_vs_x_meas_binning_obs_dnn_sel -> FindBin( obs_x_DA, obs_Q2_DA, wgt ) ;
         int fine_binning_obs_gbi = h_q2_vs_x_obs_dnn_sel -> FindBin( obs_x_DA, obs_Q2_DA, wgt ) ;

         h_q2_vs_x_obs_da_sel -> Fill( obs_x_DA, obs_Q2_DA, wgt ) ;
         h_q2_vs_x_gen_da_sel -> Fill( from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;
         rur_2D_q2_vs_x_da -> Fill( obs_x_DA, obs_Q2_DA, from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;

         if ( meas_binning_gen_gbi == meas_binning_obs_gbi ) {
            h_q2_vs_x_meas_binning_obs_gen_same_da_sel -> Fill( obs_x_DA, obs_Q2_DA, wgt ) ;
            h_q2_vs_x_gen_rec_same_da_sel -> Fill( from_tlv_gen_x, from_tlv_gen_Q2, wgt ) ;
         }
         if ( fine_binning_gen_gbi == fine_binning_obs_gbi ) {
            h_q2_vs_x_obs_gen_same_da_sel -> Fill( obs_x_DA, obs_Q2_DA, wgt ) ;
         }

      }




     //----------



   } // jentry

   printf("\n\n Done. \n\n") ;

   gDirectory -> ls() ;

   char save_file[1000] ;
   if ( strlen( out_file ) > 0 ) {
      sprintf( save_file, "%s", out_file ) ;
   } else {
      sprintf( save_file, "unfold-hists-h1-binning-v5.root" ) ;
   }

   saveHist( save_file, "*" ) ;

   TFile tf( save_file, "update" ) ;

   tf.WriteTObject( rur_2D_q2_vs_x_dnn, rur_2D_q2_vs_x_dnn->GetName() ) ;
   tf.WriteTObject( rur_2D_q2_vs_x_e, rur_2D_q2_vs_x_e->GetName() ) ;
   tf.WriteTObject( rur_2D_q2_vs_x_esigma, rur_2D_q2_vs_x_esigma->GetName() ) ;
   tf.WriteTObject( rur_2D_q2_vs_x_isigma, rur_2D_q2_vs_x_isigma->GetName() ) ;
   tf.WriteTObject( rur_2D_q2_vs_x_da, rur_2D_q2_vs_x_da->GetName() ) ;

   tf.Close() ;

} // Loop








