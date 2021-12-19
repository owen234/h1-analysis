#define fill_hists6_cxx
#include "fill_hists6.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "utils.c"
#include "histio.c"
#include "create_opt_hist.C"
#include "create_opt_hist_fine.C"

//
//  This version only uses observable quantities for the selection (no gen stuff).
//
//
//
//  Before doing
//
//    .L fill_hists6.c
//
//  do
//
//   gSystem -> Load( "../RooUnfold/build/libRooUnfold.dylib" ) ;
//
//

//TH2Poly* h_template_fine ;
//TH2Poly* h_template ;

//TH2Poly* make_q2_vs_x_fine_opt_binning( const char* hname ) {
//   printf("  make_q2_vs_x_fine_opt_binning : creating %s\n", hname ) ;
//   printf(" pointer %p\n", h_template_fine ) ; fflush(stdout) ;
//   TH2Poly* hp = (TH2Poly*) h_template_fine -> Clone( hname ) ;
//   printf(" pointer %p\n", hp ) ; fflush(stdout) ;
//   //hp -> SetTitle( hname ) ;
//   //hp -> Reset("ICESM") ;
//   return hp ;
//}

//TH2Poly* make_q2_vs_x_opt_binning( const char* hname ) {
//   printf("  make_q2_vs_x_opt_binning : creating %s\n", hname ) ;
//   printf(" pointer %p\n", h_template ) ; fflush(stdout) ;
//   TH2Poly* hp = (TH2Poly*) h_template -> Clone( hname ) ;
//   printf(" pointer %p\n", hp ) ; fflush(stdout) ;
//   //hp -> SetTitle( hname ) ;
//   //hp -> Reset("ICESM") ;
//   return hp ;
//}

TH2Poly* make_q2_vs_x_fine_opt_binning( const char* hname ) {
   printf("  make_q2_vs_x_fine_opt_binning : creating %s\n", hname ) ;
   TH2Poly* hp = create_opt_hist( hname ) ;
   gDirectory -> Add( hp ) ;
   return hp ;
}

TH2Poly* make_q2_vs_x_opt_binning( const char* hname ) {
   printf("  make_q2_vs_x_opt_binning : creating %s\n", hname ) ;
   TH2Poly* hp = create_opt_hist_fine( hname ) ;
   gDirectory -> Add( hp ) ;
   return hp ;
}

void fill_hists6::Loop( const char* template_hist_file,
                        const char* template_hist_file_fine,
                        bool verbose, int last_event, int first_event, const char* out_file )
{


  //------------
// loadHist( template_hist_file ) ;
// loadHist( template_hist_file_fine, "fine" ) ;
// gDirectory -> ls() ;

// h_template = (TH2Poly*) gDirectory -> FindObject( "h_output_binning" ) ;
// if ( h_template == 0x0 ) { printf("\n\n *** can't find h_output_binning in %s\n\n", template_hist_file ) ; gSystem -> Exit(-1) ; }

// h_template_fine = (TH2Poly*) gDirectory -> FindObject( "h_output_binning_fine" ) ;
// if ( h_template_fine == 0x0 ) { printf("\n\n *** can't find h_output_binning in %s\n\n", template_hist_file_fine ) ; gSystem -> Exit(-1) ; }
  //------------
// loadHist( template_hist_file ) ;
// loadHist( template_hist_file_fine, "fine" ) ;
// TFile* tf_in = new TFile( template_hist_file, "read" ) ;
// TFile* tf_in_fine = new TFile( template_hist_file_fine, "read" ) ;

// h_template = (TH2Poly*) tf_in -> Get( "h_output_binning" ) ;
// if ( h_template == 0x0 ) { printf("\n\n *** can't find h_output_binning in %s\n\n", template_hist_file ) ; tf_in -> ls() ; gSystem -> Exit(-1) ; }

// h_template_fine = (TH2Poly*) tf_in_fine -> Get( "h_output_binning" ) ;
// if ( h_template_fine == 0x0 ) { printf("\n\n *** can't find h_output_binning in %s\n\n", template_hist_file_fine ) ; gSystem -> Exit(-1) ; }
  //------------

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


   TH2Poly* h_q2_vs_x_obs_dnn_sel = make_q2_vs_x_fine_opt_binning( "h_q2_vs_x_obs_dnn_sel" ) ;
   TH2Poly* h_q2_vs_x_obs_e_sel = make_q2_vs_x_fine_opt_binning( "h_q2_vs_x_obs_e_sel" ) ;
   TH2Poly* h_q2_vs_x_obs_esigma_sel = make_q2_vs_x_fine_opt_binning( "h_q2_vs_x_obs_esigma_sel" ) ;
   TH2Poly* h_q2_vs_x_obs_isigma_sel = make_q2_vs_x_fine_opt_binning( "h_q2_vs_x_obs_isigma_sel" ) ;
   TH2Poly* h_q2_vs_x_obs_da_sel = make_q2_vs_x_fine_opt_binning( "h_q2_vs_x_obs_da_sel" ) ;

   TH2Poly* h_q2_vs_x_obs_gen_same_dnn_sel = make_q2_vs_x_fine_opt_binning( "h_q2_vs_x_obs_gen_same_dnn_sel" ) ;
   TH2Poly* h_q2_vs_x_obs_gen_same_e_sel = make_q2_vs_x_fine_opt_binning( "h_q2_vs_x_obs_gen_same_e_sel" ) ;
   TH2Poly* h_q2_vs_x_obs_gen_same_esigma_sel = make_q2_vs_x_fine_opt_binning( "h_q2_vs_x_obs_gen_same_esigma_sel" ) ;
   TH2Poly* h_q2_vs_x_obs_gen_same_isigma_sel = make_q2_vs_x_fine_opt_binning( "h_q2_vs_x_obs_gen_same_isigma_sel" ) ;
   TH2Poly* h_q2_vs_x_obs_gen_same_da_sel = make_q2_vs_x_fine_opt_binning( "h_q2_vs_x_obs_gen_same_da_sel" ) ;



   TH2Poly* h_q2_vs_x_meas_binning_obs_dnn_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_meas_binning_obs_dnn_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_e_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_meas_binning_obs_e_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_esigma_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_meas_binning_obs_esigma_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_isigma_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_meas_binning_obs_isigma_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_da_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_meas_binning_obs_da_sel" ) ;

   TH2Poly* h_q2_vs_x_meas_binning_obs_gen_same_dnn_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_meas_binning_obs_gen_same_dnn_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_gen_same_e_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_meas_binning_obs_gen_same_e_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_gen_same_esigma_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_meas_binning_obs_gen_same_esigma_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_gen_same_isigma_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_meas_binning_obs_gen_same_isigma_sel" ) ;
   TH2Poly* h_q2_vs_x_meas_binning_obs_gen_same_da_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_meas_binning_obs_gen_same_da_sel" ) ;







   TH2Poly* h_q2_vs_x_gen_no_cuts = make_q2_vs_x_opt_binning( "h_q2_vs_x_gen_no_cuts" ) ;

   TH2Poly* h_q2_vs_x_gen_dnn_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_gen_dnn_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_e_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_gen_e_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_esigma_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_gen_esigma_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_isigma_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_gen_isigma_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_da_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_gen_da_sel" ) ;


   TH2Poly* h_q2_vs_x_gen_rec_same_dnn_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_gen_rec_same_dnn_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_rec_same_e_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_gen_rec_same_e_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_rec_same_esigma_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_gen_rec_same_esigma_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_rec_same_isigma_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_gen_rec_same_isigma_sel" ) ;
   TH2Poly* h_q2_vs_x_gen_rec_same_da_sel = make_q2_vs_x_opt_binning( "h_q2_vs_x_gen_rec_same_da_sel" ) ;



   gDirectory -> ls() ;








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
      sprintf( save_file, "unfold-hists-h1-binning6.root" ) ;
   }

   saveHist( save_file, "*" ) ;


} // Loop








