
#include "histio.c"
#include "calc_reduced_xsec_from_q2_vs_x.c"
#include "fill_h1_rxsec_th2.c"

TH2F* rxsec_from_fake_data_no_unfolding( const char* infile = "unfold-hists-h1-binning.root" ) {

   gStyle -> SetOptStat(0) ;

   /////////////gDirectory -> Delete() ;

   //loadHist("unfold-hists-h1-binning.root") ;
   loadHist( infile ) ;

   TH2F* h_q2_vs_x_gen_no_cuts = (TH2F*) gDirectory -> FindObject( "h_q2_vs_x_gen_no_cuts" ) ;
   if ( h_q2_vs_x_gen_no_cuts == 0x0 ) {
      gDirectory -> ls() ;
      printf("\n\n *** h_q2_vs_x_gen_no_cuts missing.\n\n") ;
      return 0x0 ;
   }

   TH2F* hp = h_q2_vs_x_gen_no_cuts ;

   for ( int q2bi=1; q2bi <= hp -> GetNbinsY(); q2bi ++ ) {
      for ( int xbi=1; xbi <= hp -> GetNbinsX(); xbi ++ ) {
         float val = hp -> GetBinContent( xbi, q2bi ) ;
         float new_err = 0. ;
         if ( val > 0 ) new_err = sqrt(val) ;
         hp -> SetBinError( xbi, q2bi, new_err ) ;
      } // xbi
   } // q2bi



   TH2F* h_h1_rxsec = fill_h1_rxsec_th2() ;

   TH2F* h_h1_rxsec_stat_error = (TH2F*) gDirectory -> Get( "h_h1_rxsec_stat_error" ) ;
   if ( h_h1_rxsec_stat_error == 0x0 ) { printf("\n\n *** can't find h_h1_rxsec_stat_error.\n\n") ; return 0x0 ; }


   TH2F* h_rxsec = calc_reduced_xsec_from_q2_vs_x( h_q2_vs_x_gen_no_cuts, h_h1_rxsec, h_h1_rxsec_stat_error ) ;
   //TH2F* h_rxsec = calc_reduced_xsec_from_q2_vs_x( h_q2_vs_x_gen_no_cuts ) ;


   h_rxsec -> Draw("colz") ;
   gPad -> SetLogx(1) ;
   gPad -> SetLogy(1) ;

   return h_rxsec ;


}



