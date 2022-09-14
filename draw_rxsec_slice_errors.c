

#include "fill_h1_rxsec_th2.c"
#include "draw_2d_slice_error_plots.c"
#include "rxsec_from_mc.c"
#include "rxsec_from_fake_data_no_unfolding.c"
#include "rxsec_from_fake_data_no_unfolding_with_acceptance.c"
#include "rxsec_from_unfolding.c"

void draw_rxsec_slice_errors( const char* unfolding_hist_file = "ru1-output-method2.root" ) {

   fill_h1_rxsec_th2() ;
   TH2F* hp_h1 = (TH2F*) gDirectory -> FindObject( "h_h1_rxsec_stat_error" ) ;
   if ( hp_h1 == 0x0 ) {printf("\n\n *** can't find h_h1_rxsec_stat_error.\n\n") ; return ; }

   //TH2F* hp_mc = 0x0 ;
   //TH2F* hp_mc = rxsec_from_mc() ;
   //TH2F* hp_mc = rxsec_from_fake_data_no_unfolding() ;
   //TH2F* hp_mc = rxsec_from_fake_data_no_unfolding_with_acceptance() ;
   TH2F* hp_mc = rxsec_from_unfolding( unfolding_hist_file ) ;

   printf("\n\n pointers:  hp_h1 %p   hp_mc %p\n\n", hp_h1, hp_mc ) ;

   printf("  calling draw_2d_slice_plots.\n\n") ;

   hp_mc -> Draw("colz") ;

   draw_2d_slice_error_plots(hp_h1, hp_mc) ;


}

