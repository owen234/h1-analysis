
#include "histio.c"
#include "calc_reduced_xsec_from_q2_vs_x_given_center.c"
#include "fill_h1_rxsec_th2.c"

TH2F* rxsec_from_mc_bcc_given_center( const char* infile = "unfold-hists-h1-binning.root" ) {

   gStyle -> SetOptStat(0) ;

   ///////////gDirectory -> Delete() ;

   //loadHist("unfold-hists-h1-binning.root") ;
   loadHist( infile ) ;
   loadHist( "cbc-output-h1-bin-centers.root" ) ;

   TH2F* h_q2_vs_x_gen_no_cuts = (TH2F*) gDirectory -> FindObject( "h_q2_vs_x_gen_no_cuts" ) ;
   if ( h_q2_vs_x_gen_no_cuts == 0x0 ) {
      gDirectory -> ls() ;
      printf("\n\n *** h_q2_vs_x_gen_no_cuts missing.\n\n") ;
      return 0x0 ;
   }

   TH2F* h_xsec_bcc = (TH2F*) gDirectory -> FindObject( "h_xsec_bcc" ) ;
   if ( h_xsec_bcc == 0x0 ) {
      gDirectory -> ls() ;
      printf("\n\n *** h_xsec_bcc missing.\n\n") ;
      return 0x0 ;
   }

   h_q2_vs_x_gen_no_cuts -> Multiply( h_xsec_bcc ) ;


   TH2F* h_h1_rxsec = fill_h1_rxsec_th2() ;

   TH2F* h_h1_rxsec_stat_error = (TH2F*) gDirectory -> Get( "h_h1_rxsec_stat_error" ) ;
   if ( h_h1_rxsec_stat_error == 0x0 ) { printf("\n\n *** can't find h_h1_rxsec_stat_error.\n\n") ; return 0x0 ; }

   TH2F* h_x_vals = get_hist2d( "h_h1_rxsec_x_val" ) ;
   TH2F* h_q2_vals = get_hist2d( "h_h1_rxsec_q2_val" ) ;

   TH2F* h_rxsec = calc_reduced_xsec_from_q2_vs_x_given_center( h_q2_vs_x_gen_no_cuts, h_x_vals, h_q2_vals  ) ;


   h_rxsec -> Draw("colz") ;
   gPad -> SetLogx(1) ;
   gPad -> SetLogy(1) ;

   return h_rxsec ;


}



