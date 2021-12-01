#define fill_fake_data3_cxx
#include "fill_fake_data3.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "histio.c"

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldTUnfold.h"

void fill_fake_data3::Loop( int seed, int number_of_events, const char* rur_file_name )
{
   if (fChain == 0) return;






  //-- good ranges should be consistent with fill_hists3.c

   float good_range_log10_xmin = -2.5  ;
   float good_range_log10_xmax = 0.0 ;

   float good_range_log10_ymin = -2.0  ;
   float good_range_log10_ymax = 0.0  ;

   float good_range_log10_q2min = 2.3979400 ; // log10(250) = 2.3979400
   float good_range_log10_q2max = 4 ;







   Long64_t nentries = fChain->GetEntries();

   char hname[100] ;

   gDirectory -> Delete( "h*" ) ;

   printf("\n\n Ntuple has %lld entries\n\n", nentries ) ;


  //--- Take the RooUnfoldResponse object used in the unfolding to define the observed histogram
  //     to ensure consistency.

   TFile* tf_in = new TFile( rur_file_name, "read" ) ;
   if ( tf_in == 0x0 ) { printf("\n\n *** Bad input file for RooUnfoldResponse objects: %s\n\n", rur_file_name ) ; gSystem -> Exit(-1) ; }

   gDirectory -> cd( "Rint:/" ) ;

   tf_in -> ls() ;

   char rur_name_a[100] ;
   RooUnfoldResponse* rur_a ;
   TH1* h_template ;

   sprintf( rur_name_a, "rur_2D_log10_q2_vs_log10_y_dnn" ) ;
   rur_a = (RooUnfoldResponse*) tf_in -> Get( rur_name_a ) ;
   if ( rur_a == 0x0 ) { printf("\n\n *** can't find %s\n\n", rur_name_a ) ; return ; }

   h_template = rur_a -> Hmeasured() ;

   printf("\n\n") ;
   printf("   Template histogram:  %s\n", h_template -> GetName() ) ;
   printf("     x axis:  nbins %2d,  [%9.5f, %9.5f]\n",
     h_template -> GetNbinsX(),
     h_template -> GetXaxis() -> GetBinLowEdge(1), 
     h_template -> GetXaxis() -> GetBinLowEdge( h_template -> GetNbinsX() + 1 ) ) ;
   printf("     y axis:  nbins %2d,  [%9.5f, %9.5f]\n",
     h_template -> GetNbinsY(),
     h_template -> GetYaxis() -> GetBinLowEdge(1), 
     h_template -> GetYaxis() -> GetBinLowEdge( h_template -> GetNbinsX() + 1 ) ) ;
   printf("\n\n") ;


   TString tsname_dnn( h_template -> GetName() ) ;
   tsname_dnn.ReplaceAll( "dummy", "data" ) ;
   tsname_dnn.Append("_dnn") ;
   TH1* h_data_dnn = (TH1*) h_template -> Clone( tsname_dnn.Data() ) ;
   h_data_dnn -> Reset() ;
   h_data_dnn -> SetTitle( tsname_dnn.Data() ) ;

   TString tsname ;

   tsname = tsname_dnn ;
   tsname.ReplaceAll( "dnn", "e" ) ;
   TH1* h_data_e = (TH1*) h_template -> Clone( tsname.Data() ) ;
   h_data_e -> Reset() ;
   h_data_e -> SetTitle( tsname.Data() ) ;

   tsname = tsname_dnn ;
   tsname.ReplaceAll( "dnn", "esigma" ) ;
   TH1* h_data_esigma = (TH1*) h_template -> Clone( tsname.Data() ) ;
   h_data_esigma -> Reset() ;
   h_data_esigma -> SetTitle( tsname.Data() ) ;

   tsname = tsname_dnn ;
   tsname.ReplaceAll( "dnn", "isigma" ) ;
   TH1* h_data_isigma = (TH1*) h_template -> Clone( tsname.Data() ) ;
   h_data_isigma -> Reset() ;
   h_data_isigma -> SetTitle( tsname.Data() ) ;

   tsname = tsname_dnn ;
   tsname.ReplaceAll( "dnn", "da" ) ;
   TH1* h_data_da = (TH1*) h_template -> Clone( tsname.Data() ) ;
   h_data_da -> Reset() ;
   h_data_da -> SetTitle( tsname.Data() ) ;


   TRandom3 tran( seed ) ;


   Long64_t nbytes = 0, nb = 0;

   int n_fill = 0 ;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      int ei = jentry ;

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ( ei%100 == 0 ) {
         printf(" --- Event: %7d / %lld    %6.3f   n_fill = %8d\r", ei, nentries, (1.*ei)/(1.*nentries), n_fill ) ;
         fflush(stdout) ;
      }

      ///////////if ( dnn_Q2 < 240 ) continue ;

      float rn = tran.Uniform(0.7) ;
      if ( rn > wgt ) continue ;


      if ( ei < 50 ) {
         printf("  %3d : dnn  %9.5f, %9.5f  |  e  %9.5f, %9.5f  |  esigma %9.5f, %9.5f  |  isigma %9.5f, %9.5f  |  da  %9.5f, %9.5f |\n",
           ei,
           log10( dnn_y ), log10( dnn_Q2 ),
           log10( obs_y_e ), log10( obs_Q2_e ),
           log10( obs_y_eSigma ), log10( obs_Q2_eSigma ),
           log10( obs_y_ISigma ), log10( obs_Q2_ISigma ),
           log10( obs_y_DA ), log10( obs_Q2_DA ) ) ;
      }





     //----------  DNN

      float log10_dnn_Q2 = log10(dnn_Q2) ;
      float log10_dnn_x = log10(dnn_x) ;
      float log10_dnn_y = log10(dnn_y) ;

      if (     log10_dnn_Q2 >= good_range_log10_q2min && log10_dnn_Q2 <= good_range_log10_q2max
            && log10_dnn_x  >= good_range_log10_xmin  && log10_dnn_x  <= good_range_log10_xmax
            && log10_dnn_y  >= good_range_log10_ymin  && log10_dnn_y  <= good_range_log10_ymax   ) {

         h_data_dnn -> Fill( log10( dnn_y ), log10( dnn_Q2 ) ) ;

      }



     //----------  electron

      float log10_e_Q2 = log10(obs_Q2_e) ;
      float log10_e_x = log10(obs_x_e) ;
      float log10_e_y = log10(obs_y_e) ;

      if (     log10_e_Q2 >= good_range_log10_q2min && log10_e_Q2 <= good_range_log10_q2max
            && log10_e_x  >= good_range_log10_xmin  && log10_e_x  <= good_range_log10_xmax
            && log10_e_y  >= good_range_log10_ymin  && log10_e_y  <= good_range_log10_ymax   ) {

         h_data_e -> Fill( log10( obs_y_e ), log10( obs_Q2_e ) ) ;

      }


     //----------  ISigma

      float log10_isigma_Q2 = log10(obs_Q2_ISigma) ;
      float log10_isigma_x = log10(obs_x_ISigma) ;
      float log10_isigma_y = log10(obs_y_ISigma) ;


      if (     log10_isigma_Q2 >= good_range_log10_q2min && log10_isigma_Q2 <= good_range_log10_q2max
            && log10_isigma_x  >= good_range_log10_xmin  && log10_isigma_x  <= good_range_log10_xmax
            && log10_isigma_y  >= good_range_log10_ymin  && log10_isigma_y  <= good_range_log10_ymax   ) {

         h_data_isigma -> Fill( log10( obs_y_ISigma ), log10( obs_Q2_ISigma ) ) ;

      }




     //----------  eSigma

      float log10_esigma_Q2 = log10(obs_Q2_eSigma) ;
      float log10_esigma_x = log10(obs_x_eSigma) ;
      float log10_esigma_y = log10(obs_y_eSigma) ;

      if (     log10_esigma_Q2 >= good_range_log10_q2min && log10_esigma_Q2 <= good_range_log10_q2max
            && log10_esigma_x  >= good_range_log10_xmin  && log10_esigma_x  <= good_range_log10_xmax
            && log10_esigma_y  >= good_range_log10_ymin  && log10_esigma_y  <= good_range_log10_ymax   ) {

         h_data_esigma -> Fill( log10( obs_y_eSigma ), log10( obs_Q2_eSigma ) ) ;

      }




     //----------  DA

      float log10_da_Q2 = log10(obs_Q2_DA) ;
      float log10_da_x = log10(obs_x_DA) ;
      float log10_da_y = log10(obs_y_DA) ;

      if (     log10_da_Q2 >= good_range_log10_q2min && log10_da_Q2 <= good_range_log10_q2max
            && log10_da_x  >= good_range_log10_xmin  && log10_da_x  <= good_range_log10_xmax
            && log10_da_y  >= good_range_log10_ymin  && log10_da_y  <= good_range_log10_ymax   ) {

         h_data_da -> Fill( log10( obs_y_DA ), log10( obs_Q2_DA ) ) ;

      }




      n_fill ++ ;

      if ( n_fill >= number_of_events ) break ;


   } // jentry

   printf("\n\n") ;

   char fname[1000] ;
   sprintf( fname, "fake-data-hists-seed-%d-obs-good.root", seed ) ;
   saveHist( fname, "*" ) ;

} // Loop















