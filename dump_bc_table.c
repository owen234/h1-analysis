

#include "utils.c"


   void dump_bc_table( const char* input_file = "cbc-poly-output-h1-bin-centers.root",
                       const char* output_file = "bin-center-corrections-table.txt" ) {

      TFile* tf_in = new TFile( input_file, "READ" ) ;
      if ( tf_in == 0x0 ) { printf("\n\n *** bad input root file: %s\n\n", input_file ) ; return ; }
      if ( !(tf_in -> IsOpen() ) ) { printf("\n\n *** bad input root file: %s\n\n", input_file ) ; return ; }
      tf_in -> ls() ;

      TH2Poly* h_poly_h1_q2_vs_x_binning = fget_hist2dp( "h_poly_h1_q2_vs_x_binning", tf_in ) ;
      TH2Poly* h_poly_h1_rxsec_q2_val = fget_hist2dp( "h_poly_h1_rxsec_q2_val", tf_in ) ;
      TH2Poly* h_poly_h1_rxsec_x_val = fget_hist2dp( "h_poly_h1_rxsec_x_val", tf_in ) ;
      TH2Poly* h_xsec = fget_hist2dp( "h_xsec", tf_in ) ;
      TH2Poly* h_xsec_ave = fget_hist2dp( "h_xsec_ave", tf_in ) ;
      TH2Poly* h_xsec_bcc = fget_hist2dp( "h_xsec_bcc", tf_in ) ;
      TH2Poly* h_rxsec = fget_hist2dp( "h_rxsec", tf_in ) ;

      TList* tl_bins = h_poly_h1_q2_vs_x_binning -> GetBins() ;
      int nbins = tl_bins -> GetEntries() ;

      FILE* ofp = fopen( output_file, "w" ) ;

      printf("  bin      Q2_l      Q2_h      Q2_c     x_l        x_h        x_c             xsec_c        xsec_ave    BCC_area       RC_sf     rxsec_c      area\n") ;
      fprintf( ofp, "  bin      Q2_l      Q2_h      Q2_c     x_l        x_h        x_c             xsec_c        xsec_ave    BCC_area       RC_sf     rxsec_c      area\n") ;
      for ( int bi=1; bi<=nbins; bi++ ) {

         TH2PolyBin* thpb = (TH2PolyBin*) tl_bins->At(bi) ;

         float xsec_c = h_xsec -> GetBinContent( bi ) ;
         if ( xsec_c <= 0 ) continue ;
         float bin_x_l = thpb->GetXMin() ;
         float bin_x_h = thpb->GetXMax() ;
         float bin_x_c = h_poly_h1_rxsec_x_val -> GetBinContent( bi ) ;
         float bin_q2_l = thpb->GetYMin() ;
         float bin_q2_h = thpb->GetYMax() ;
         float bin_q2_c = h_poly_h1_rxsec_q2_val -> GetBinContent( bi ) ;
         float xsec_ave = h_xsec_ave -> GetBinContent( bi ) ;
         float rxsec_c = h_rxsec -> GetBinContent( bi ) ;
         float rcsf = rxsec_c / xsec_c ;
         float bcca = xsec_c / xsec_ave ;
         float bin_a = (bin_x_h-bin_x_l)*(bin_q2_h-bin_q2_l) ;

         printf("  %3d    %8.2f  %8.2f  %8.2f   %8.7f  %8.7f  %8.7f    %12.6f  %12.6f   %7.5f  %14.6f  %7.5f  %10.4f\n",
           bi,
           bin_q2_l, bin_q2_h, bin_q2_c,
           bin_x_l, bin_x_h, bin_x_c,
           xsec_c,
           xsec_ave,
           bcca,
           rcsf,
           rxsec_c,
           bin_a ) ;

         fprintf( ofp, "  %3d    %8.2f  %8.2f  %8.2f   %8.7f  %8.7f  %8.7f    %12.6f  %12.6f   %7.5f  %14.6f  %7.5f  %10.4f\n",
           bi,
           bin_q2_l, bin_q2_h, bin_q2_c,
           bin_x_l, bin_x_h, bin_x_c,
           xsec_c,
           xsec_ave,
           bcca,
           rcsf,
           rxsec_c,
           bin_a ) ;

      } // bi

      fclose(ofp) ;


   } // dump_bc_table











