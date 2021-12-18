#define fill_x_reso_hists_cxx
#include "fill_x_reso_hists.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "utils.c"
#include "histio.c"

void fill_x_reso_hists::Loop( bool fine_binning, bool verbose, int last_event, int first_event, const char* out_file )
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




   TH2F* h_q2_vs_x_gen_no_cuts = 0x0 ;
   TH2F* h_q2_vs_x_obs = 0x0 ;

   if ( fine_binning ) {
      h_q2_vs_x_gen_no_cuts = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_gen_no_cuts" ) ;
      h_q2_vs_x_obs = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs" ) ;
   } else {
      h_q2_vs_x_gen_no_cuts = make_q2_vs_x_h1_binning( "h_q2_vs_x_gen_no_cuts" ) ;
      h_q2_vs_x_obs = make_q2_vs_x_h1_binning( "h_q2_vs_x_obs" ) ;
   }

   char hname[10000] ;
   char htitle[10000] ;

   TH1F* h_x_meas_over_x_gen__gen_binning[10000] ;
   TH1F* h_x_meas_over_x_gen__obs_binning[10000] ;
   TH1F* h_x_meas_minus_x_gen__gen_binning[10000] ;
   TH1F* h_x_meas_minus_x_gen__obs_binning[10000] ;
   for ( int i=0; i<10000; i++ ) h_x_meas_over_x_gen__gen_binning[i] = 0x0 ;
   for ( int i=0; i<10000; i++ ) h_x_meas_over_x_gen__obs_binning[i] = 0x0 ;
   for ( int i=0; i<10000; i++ ) h_x_meas_minus_x_gen__gen_binning[i] = 0x0 ;
   for ( int i=0; i<10000; i++ ) h_x_meas_minus_x_gen__obs_binning[i] = 0x0 ;

   for ( int xbi = 1; xbi <= h_q2_vs_x_gen_no_cuts -> GetNbinsX(); xbi++ ) {

      float x_center =  h_q2_vs_x_gen_no_cuts -> GetXaxis() -> GetBinCenter( xbi ) ;
      float x_low =  h_q2_vs_x_gen_no_cuts -> GetXaxis() -> GetBinLowEdge( xbi ) ;
      float x_high =  h_q2_vs_x_gen_no_cuts -> GetXaxis() -> GetBinLowEdge( xbi+1 ) ;

      for ( int q2bi = 1; q2bi <= h_q2_vs_x_gen_no_cuts -> GetNbinsY(); q2bi++ ) {

         float q2_center =  h_q2_vs_x_gen_no_cuts -> GetYaxis() -> GetBinCenter( q2bi ) ;
         float q2_low =  h_q2_vs_x_gen_no_cuts -> GetYaxis() -> GetBinLowEdge( q2bi ) ;
         float q2_high =  h_q2_vs_x_gen_no_cuts -> GetYaxis() -> GetBinLowEdge( q2bi+1 ) ;

         int gbi = h_q2_vs_x_gen_no_cuts -> FindBin( x_center, q2_center ) ;


        //---

         sprintf( htitle, "x_meas/x_gen gen %3d :  x %3d [%9.5f, %9.5f],  Q2 %3d [%9.1f, %9.1f]",
             gbi, xbi, x_low, x_high,  q2bi, q2_low, q2_high ) ;

         sprintf( hname, "h_x_meas_over_x_gen__gen_binning_gbi%03d", gbi ) ;

         printf( " %s : %s\n", hname, htitle ) ;

         h_x_meas_over_x_gen__gen_binning[gbi] = new TH1F( hname, htitle, 40, 0., 2. ) ;


        //---

         sprintf( htitle, "x_meas/x_gen obs %3d :  x %3d [%9.5f, %9.5f],  Q2 %3d [%9.1f, %9.1f]",
             gbi, xbi, x_low, x_high,  q2bi, q2_low, q2_high ) ;

         sprintf( hname, "h_x_meas_over_x_gen__obs_binning_gbi%03d", gbi ) ;

         printf( " %s : %s\n", hname, htitle ) ;

         h_x_meas_over_x_gen__obs_binning[gbi] = new TH1F( hname, htitle, 40, 0., 2. ) ;


        //---

         sprintf( htitle, "x_meas - x_gen gen %3d :  x %3d [%9.5f, %9.5f],  Q2 %3d [%9.1f, %9.1f]",
             gbi, xbi, x_low, x_high,  q2bi, q2_low, q2_high ) ;

         sprintf( hname, "h_x_meas_minus_x_gen__gen_binning_gbi%03d", gbi ) ;

         printf( " %s : %s\n", hname, htitle ) ;

         h_x_meas_minus_x_gen__gen_binning[gbi] = new TH1F( hname, htitle, 100, -1., 1. ) ;


        //---

         sprintf( htitle, "x_meas - x_gen obs %3d :  x %3d [%9.5f, %9.5f],  Q2 %3d [%9.1f, %9.1f]",
             gbi, xbi, x_low, x_high,  q2bi, q2_low, q2_high ) ;

         sprintf( hname, "h_x_meas_minus_x_gen__obs_binning_gbi%03d", gbi ) ;

         printf( " %s : %s\n", hname, htitle ) ;

         h_x_meas_minus_x_gen__obs_binning[gbi] = new TH1F( hname, htitle, 100, -1., 1. ) ;


      } // q2bi

   } // xbi





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

      int gen_gbi = h_q2_vs_x_gen_no_cuts -> FindBin( from_tlv_gen_x, from_tlv_gen_Q2 ) ;

      float meas_x = dnn_x ;
      float meas_y = dnn_y ;
      float meas_Q2 = dnn_Q2 ;

      //float meas_x = obs_x_eSigma ;
      //float meas_y = obs_y_eSigma ;
      //float meas_Q2 = obs_Q2_eSigma ;

      if (     meas_Q2 >= good_range_q2min && meas_Q2 <= good_range_q2max
            && meas_x  >= good_range_xmin  && meas_x  <= good_range_xmax
            && meas_y  >= good_range_ymin  && meas_y  <= good_range_ymax   ) {

         h_q2_vs_x_obs -> Fill( meas_x, meas_Q2, wgt ) ;

         int obs_gbi = h_q2_vs_x_obs -> FindBin( meas_x, meas_Q2 ) ;

         float x_meas_over_x_gen = -1. ;
         if ( from_tlv_gen_x > 0 ) { x_meas_over_x_gen =  meas_x / from_tlv_gen_x ; }

         if ( gen_gbi > 0 && h_x_meas_over_x_gen__gen_binning[gen_gbi] != 0x0 ) {
            h_x_meas_over_x_gen__gen_binning[gen_gbi] -> Fill( x_meas_over_x_gen, wgt ) ;
            h_x_meas_minus_x_gen__gen_binning[gen_gbi] -> Fill( (meas_x - from_tlv_gen_x), wgt ) ;
         }

         if ( obs_gbi > 0 && h_x_meas_over_x_gen__obs_binning[obs_gbi] != 0x0 ) {
            h_x_meas_over_x_gen__obs_binning[obs_gbi] -> Fill( x_meas_over_x_gen, wgt ) ;
            h_x_meas_minus_x_gen__obs_binning[obs_gbi] -> Fill( (meas_x - from_tlv_gen_x), wgt ) ;
         }

      }




   } // jentry

   printf("\n\n Done. \n\n") ;





   TH2F* h_q2_vs_x_gbi = 0x0 ;

   TH2F* h_q2_vs_x_gen_binning__x_reso_rms  = 0x0 ;
   TH2F* h_q2_vs_x_gen_binning__x_reso_mean = 0x0 ;

   TH2F* h_q2_vs_x_obs_binning__x_reso_rms  = 0x0 ;
   TH2F* h_q2_vs_x_obs_binning__x_reso_mean = 0x0 ;

   TH2F* h_q2_vs_x_gen_binning__x_diff_rms  = 0x0 ;
   TH2F* h_q2_vs_x_gen_binning__x_diff_mean = 0x0 ;

   TH2F* h_q2_vs_x_obs_binning__x_diff_rms  = 0x0 ;
   TH2F* h_q2_vs_x_obs_binning__x_diff_mean = 0x0 ;


   if ( fine_binning ) {

      h_q2_vs_x_gbi = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_gbi" ) ;

      h_q2_vs_x_gen_binning__x_reso_rms  = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_gen_binning__x_reso_rms" ) ;
      h_q2_vs_x_gen_binning__x_reso_mean = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_gen_binning__x_reso_mean" ) ;

      h_q2_vs_x_obs_binning__x_reso_rms  = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_binning__x_reso_rms" ) ;
      h_q2_vs_x_obs_binning__x_reso_mean = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_binning__x_reso_mean" ) ;

      h_q2_vs_x_gen_binning__x_diff_rms  = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_gen_binning__x_diff_rms" ) ;
      h_q2_vs_x_gen_binning__x_diff_mean = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_gen_binning__x_diff_mean" ) ;

      h_q2_vs_x_obs_binning__x_diff_rms  = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_binning__x_diff_rms" ) ;
      h_q2_vs_x_obs_binning__x_diff_mean = make_q2_vs_x_fine_h1_binning( "h_q2_vs_x_obs_binning__x_diff_mean" ) ;

   } else {

      h_q2_vs_x_gbi = make_q2_vs_x_h1_binning( "h_q2_vs_x_gbi" ) ;

      h_q2_vs_x_gen_binning__x_reso_rms  = make_q2_vs_x_h1_binning( "h_q2_vs_x_gen_binning__x_reso_rms" ) ;
      h_q2_vs_x_gen_binning__x_reso_mean = make_q2_vs_x_h1_binning( "h_q2_vs_x_gen_binning__x_reso_mean" ) ;

      h_q2_vs_x_obs_binning__x_reso_rms  = make_q2_vs_x_h1_binning( "h_q2_vs_x_obs_binning__x_reso_rms" ) ;
      h_q2_vs_x_obs_binning__x_reso_mean = make_q2_vs_x_h1_binning( "h_q2_vs_x_obs_binning__x_reso_mean" ) ;

      h_q2_vs_x_gen_binning__x_diff_rms  = make_q2_vs_x_h1_binning( "h_q2_vs_x_gen_binning__x_diff_rms" ) ;
      h_q2_vs_x_gen_binning__x_diff_mean = make_q2_vs_x_h1_binning( "h_q2_vs_x_gen_binning__x_diff_mean" ) ;

      h_q2_vs_x_obs_binning__x_diff_rms  = make_q2_vs_x_h1_binning( "h_q2_vs_x_obs_binning__x_diff_rms" ) ;
      h_q2_vs_x_obs_binning__x_diff_mean = make_q2_vs_x_h1_binning( "h_q2_vs_x_obs_binning__x_diff_mean" ) ;

   }



   for ( int xbi = 1; xbi <= h_q2_vs_x_gen_no_cuts -> GetNbinsX(); xbi++ ) {

      float x_center =  h_q2_vs_x_gen_no_cuts -> GetXaxis() -> GetBinCenter( xbi ) ;
      float x_low =  h_q2_vs_x_gen_no_cuts -> GetXaxis() -> GetBinLowEdge( xbi ) ;
      float x_high =  h_q2_vs_x_gen_no_cuts -> GetXaxis() -> GetBinLowEdge( xbi+1 ) ;

      for ( int q2bi = 1; q2bi <= h_q2_vs_x_gen_no_cuts -> GetNbinsY(); q2bi++ ) {

         float q2_center =  h_q2_vs_x_gen_no_cuts -> GetYaxis() -> GetBinCenter( q2bi ) ;
         float q2_low =  h_q2_vs_x_gen_no_cuts -> GetYaxis() -> GetBinLowEdge( q2bi ) ;
         float q2_high =  h_q2_vs_x_gen_no_cuts -> GetYaxis() -> GetBinLowEdge( q2bi+1 ) ;

         int gbi = h_q2_vs_x_gen_no_cuts -> FindBin( x_center, q2_center ) ;


        //---

         if ( h_x_meas_over_x_gen__gen_binning[gbi] != 0x0 ) {

            float x_rms = h_x_meas_over_x_gen__gen_binning[gbi] -> GetRMS() ;
            float x_mean = h_x_meas_over_x_gen__gen_binning[gbi] -> GetMean() ;

            h_q2_vs_x_gen_binning__x_reso_rms  -> SetBinContent( xbi, q2bi, x_rms ) ;
            h_q2_vs_x_gen_binning__x_reso_mean -> SetBinContent( xbi, q2bi, x_mean ) ;

            printf("  gen %3d :  x %9.5f,  Q2 %9.1f  |  x reso  RMS = %7.4f, mean = %5.3f\n", gbi, x_center, q2_center, x_rms, x_mean ) ;

         }


        //---

         if ( h_x_meas_over_x_gen__obs_binning[gbi] != 0x0 ) {

            float x_rms = h_x_meas_over_x_gen__obs_binning[gbi] -> GetRMS() ;
            float x_mean = h_x_meas_over_x_gen__obs_binning[gbi] -> GetMean() ;

            h_q2_vs_x_obs_binning__x_reso_rms  -> SetBinContent( xbi, q2bi, x_rms ) ;
            h_q2_vs_x_obs_binning__x_reso_mean -> SetBinContent( xbi, q2bi, x_mean ) ;

            printf("  obs %3d :  x %9.5f,  Q2 %9.1f  |  x reso  RMS = %7.4f, mean = %5.3f\n", gbi, x_center, q2_center, x_rms, x_mean ) ;

         }


        //---

         if ( h_x_meas_minus_x_gen__gen_binning[gbi] != 0x0 ) {

            float x_rms = h_x_meas_minus_x_gen__gen_binning[gbi] -> GetRMS() ;
            float x_mean = h_x_meas_minus_x_gen__gen_binning[gbi] -> GetMean() ;

            h_q2_vs_x_gen_binning__x_diff_rms  -> SetBinContent( xbi, q2bi, x_rms ) ;
            h_q2_vs_x_gen_binning__x_diff_mean -> SetBinContent( xbi, q2bi, x_mean ) ;

         }


        //---

         if ( h_x_meas_minus_x_gen__obs_binning[gbi] != 0x0 ) {

            float x_rms = h_x_meas_minus_x_gen__obs_binning[gbi] -> GetRMS() ;
            float x_mean = h_x_meas_minus_x_gen__obs_binning[gbi] -> GetMean() ;

            h_q2_vs_x_obs_binning__x_diff_rms  -> SetBinContent( xbi, q2bi, x_rms ) ;
            h_q2_vs_x_obs_binning__x_diff_mean -> SetBinContent( xbi, q2bi, x_mean ) ;

         }

         h_q2_vs_x_gbi -> SetBinContent( gbi, gbi ) ;

      } // q2bi

   } // xbi

   printf("\n\n") ;


   char save_file[1000] ;
   if ( strlen( out_file ) > 0 ) {
      sprintf( save_file, "%s", out_file ) ;
   } else {
      if ( fine_binning ) {
         sprintf( save_file, "x_reso_hists_fine_binning.root" ) ;
      } else {
         sprintf( save_file, "x_reso_hists.root" ) ;
      }
   }

   saveHist( save_file, "*" ) ;


} // Loop








