

#include "fill_h1_rxsec_th2.c"
#include "draw_2d_slice_plots.c"
#include "rxsec_from_mc.c"
#include "rxsec_from_fake_data_no_unfolding.c"
#include "rxsec_from_fake_data_no_unfolding_with_acceptance.c"
#include "rxsec_from_unfolding.c"

void draw_rxsec_slices() {

   TH2F* hp_h1 = fill_h1_rxsec_th2() ;

   //TH2F* hp_mc = 0x0 ;
   //TH2F* hp_mc = rxsec_from_mc() ;
   //TH2F* hp_mc = rxsec_from_fake_data_no_unfolding() ;
   //TH2F* hp_mc = rxsec_from_fake_data_no_unfolding_with_acceptance() ;
   TH2F* hp_mc = rxsec_from_unfolding() ;

   printf("\n\n pointers:  hp_h1 %p   hp_mc %p\n\n", hp_h1, hp_mc ) ;

   printf("  calling draw_2d_slice_plots.\n\n") ;

   hp_mc -> Draw("colz") ;

   draw_2d_slice_plots(hp_h1, hp_mc) ;


}

