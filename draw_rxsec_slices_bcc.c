

#include "fill_h1_rxsec_th2.c"
#include "draw_2d_slice_plots.c"
#include "rxsec_from_mc_bcc.c"
#include "rxsec_from_fake_data_no_unfolding.c"
#include "rxsec_from_fake_data_no_unfolding_with_acceptance.c"
#include "rxsec_from_unfolding.c"

void draw_rxsec_slices_bcc( const char* infile = "unfold-hists-h1-binning.root", const char* unfolding_input = "ru1-output-method2-v4b.root", bool do_logx=true  ) {

   gDirectory -> Delete( "h*" ) ;

   TH2F* hp_h1 = fill_h1_rxsec_th2() ;

   //TH2F* hp_mc = 0x0 ;
   TH2F* hp_mc = rxsec_from_mc_bcc( infile ) ;
   //TH2F* hp_mc = rxsec_from_fake_data_no_unfolding( infile ) ;
   //TH2F* hp_mc = rxsec_from_fake_data_no_unfolding_with_acceptance( infile ) ;
   //TH2F* hp_mc = rxsec_from_unfolding( unfolding_input ) ;

   printf("\n\n pointers:  hp_h1 %p   hp_mc %p\n\n", hp_h1, hp_mc ) ;

   printf("  calling draw_2d_slice_plots.\n\n") ;

   hp_mc -> Draw("colz") ;

   draw_2d_slice_plots(hp_h1, hp_mc, do_logx ) ;
   //draw_2d_slice_plots(hp_mc) ;

   gStyle -> SetPadTopMargin(0.10) ;
   gStyle -> SetPadRightMargin(0.12) ;
   gStyle -> SetPadLeftMargin(0.10) ;

   TCanvas* tc = new TCanvas("tc_ratio","",1200,50, 1200, 700 ) ;
   TH2F* hp_ratio = (TH2F*) hp_mc -> Clone( "hp_ratio" ) ;
   hp_ratio -> SetTitle( "MC / H1" ) ;
   hp_ratio -> Divide( hp_h1 ) ;
   hp_ratio -> SetMaximum(1.50) ;
   hp_ratio -> SetMinimum(0.80) ;
   hp_ratio -> Draw("colz") ;
   logxy_on() ;
   set_tf() ;
   hp_ratio -> Draw("text same") ;


}

