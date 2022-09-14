
#include "histio.c"
#include "calc_reduced_xsec_from_q2_vs_x.c"
#include "fill_h1_rxsec_th2.c"

TH2F* rxsec_from_unfolding( const char* hist_file = "ru1-output-method2.root") {

   gStyle -> SetOptStat(0) ;

   ////////////gDirectory -> Delete() ;

   loadHist( hist_file ) ;

   TH2F* hReco_ac_a = (TH2F*) gDirectory -> FindObject( "hReco_ac_a" ) ;
   if ( hReco_ac_a == 0x0 ) {
      gDirectory -> ls() ;
      printf("\n\n *** hReco_a missing.\n\n") ;
      return 0x0 ;
   }



   TH2F* h_h1_rxsec = fill_h1_rxsec_th2() ;

   TH2F* h_h1_rxsec_stat_error = (TH2F*) gDirectory -> Get( "h_h1_rxsec_stat_error" ) ;
   if ( h_h1_rxsec_stat_error == 0x0 ) { printf("\n\n *** can't find h_h1_rxsec_stat_error.\n\n") ; return 0x0 ; }


   TH2F* h_rxsec = calc_reduced_xsec_from_q2_vs_x( hReco_ac_a, h_h1_rxsec, h_h1_rxsec_stat_error ) ;


   h_rxsec -> Draw("colz") ;
   gPad -> SetLogx(1) ;
   gPad -> SetLogy(1) ;

   return h_rxsec ;


}



