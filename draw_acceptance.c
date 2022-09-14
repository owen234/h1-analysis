
#include "utils.c"

#include "calc_acceptance.c"

void draw_acceptance( const char* infile = "unfold-hists-h1-binning.root" ) {

   gStyle -> SetOptStat(0) ;

   TFile* tf = new TFile( infile, "READ" ) ;
   if ( tf == 0x0 ) { printf("\n\n *** bad input file : %s\n\n", infile ) ; return ; }
   TH2F* h_nc  = (TH2F*) fget_hist2d( "h_q2_vs_x_gen_no_cuts" , tf ) ;
   TH2F* h_sel = (TH2F*) fget_hist2d( "h_q2_vs_x_gen_dnn_sel" , tf ) ;
   TH2* h_acc = calc_acceptance( h_nc, h_sel ) ;

   TCanvas* can = new TCanvas( "can", "", 50, 50, 1800, 800 ) ;
   can -> cd() ;

   gStyle->SetPaintTextFormat("5.3f") ;

   h_acc -> Draw("colz") ;
   gPad -> SetLogx(1) ;
   gPad -> SetLogy(1) ;
   h_acc -> Draw("text same") ;



}




