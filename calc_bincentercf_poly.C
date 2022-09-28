
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "TFile.h"
#include "TH2F.h"
#include "TH2Poly.h"


#include "H1QCDFunc/H1QCDFunc.h"
using namespace std;

float s = 4 * 27.6 * 920. ;

bool save_bin_th2s(true) ;

bool use_h1_bin_centers(true) ;
//bool use_h1_bin_centers(false) ;

float calc_bin_ave( float x_low, float x_high, float q2_low, float q2_high, H1QCDFunc* qcdfunc, bool do_rxsec = false, int bi=0 ) ;

int
main(int argc, char* argv[])
{

   gDirectory -> pwd() ;
   printf("gDirectory -> GetPath() : %s\n", gDirectory -> GetPath() ) ;

   char binning_file[1000] ;
   if ( argc > 1 ) {
      sprintf( binning_file, "%s", argv[1] ) ;
   } else {
      sprintf( binning_file, "h1-q2-vs-x-binning.root" ) ;
   }
   printf("\n\n Opening binning file: %s\n\n", binning_file ) ;

   TFile* tf = new TFile( binning_file, "read" ) ;
   if ( tf == 0x0 ) { printf("\n\n *** Bad input binning file.  %s\n\n", binning_file ) ; return -1 ; }
   if ( ! tf -> IsOpen() ) { printf("\n\n *** Bad input binning file.  %s\n\n", binning_file ) ; return -1 ; }

   char hname[1000] ;

   sprintf( hname, "h_poly_h1_q2_vs_x_binning" ) ;
   //sprintf( hname, "h_poly_h1_rxsec" ) ;
   TH2Poly* hp = (TH2Poly*) tf -> Get( hname ) ;
   if ( hp == 0x0 ) { printf("\n\n *** can't find TH2Poly with name %s in %s\n\n", hname, binning_file ) ; return -1 ; }


   gDirectory -> cd( "root:/" ) ;

   int nb = hp -> GetNumberOfBins() ;

   TList* tl_bins = hp -> GetBins() ;




   printf("   input hist %s :  nb = %d\n", hname, nb ) ;

   double x_bin_centers[9000] ;
   double q2_bin_centers[9000] ;

   TH2Poly* h_h1_x_val(0x0) ;
   TH2Poly* h_h1_q2_val(0x0) ;
   TH2Poly* h_h1_gbi(0x0) ;
   if ( use_h1_bin_centers ) {
      printf("\n\n Extracting H1 bin centers from input histograms.\n\n") ;
      h_h1_x_val  = (TH2Poly*) tf -> Get( "h_poly_h1_rxsec_x_val" ) ;
      if ( h_h1_x_val == 0x0 ) { printf("\n\n *** can't find TH2Poly with name h_poly_h1_rxsec_x_val in  %s\n\n", binning_file ) ; return -1 ; }
      h_h1_q2_val = (TH2Poly*) tf -> Get( "h_poly_h1_rxsec_q2_val" ) ;
      if ( h_h1_q2_val == 0x0 ) { printf("\n\n *** can't find TH2Poly with name h_poly_h1_rxsec_q2_val in  %s\n\n", binning_file ) ; return -1 ; }
      h_h1_gbi = (TH2Poly*) tf -> Get( "h_poly_h1_gbi" ) ;
      if ( h_h1_gbi == 0x0 ) { printf("\n\n *** can't find TH2Poly with name h_poly_h1_gbi in  %s\n\n", binning_file ) ; return -1 ; }
      for ( int i=1; i<=nb; i++ ) { x_bin_centers[i] = 0. ; }
      for ( int i=1; i<=nb; i++ ) { q2_bin_centers[i] = 0. ; }
      for ( int bi=1; bi<=nb; bi++ ) {
         float xval = h_h1_x_val -> GetBinContent( bi ) ;
         if ( xval > 0 && x_bin_centers[bi] == 0 ) x_bin_centers[bi] = xval ;
         float q2val = h_h1_q2_val -> GetBinContent( bi ) ;
         if ( q2val > 0 && q2_bin_centers[bi] == 0 ) q2_bin_centers[bi] = q2val ;
         printf("  i=%2d, xval = %.5f q2val = %12.5f\n", bi, xval, q2val ) ;
      } // bi
   } else {
      printf("\n\n Calculating geometric bin centers.\n\n") ; fflush(stdout) ;
      for ( int bi=1; bi<=nb; bi++ ) {
         TH2PolyBin* thpb = (TH2PolyBin*) tl_bins -> At( bi-1 ) ; //**** note the different index convention!
         float xval = 0.5*( thpb->GetXMax() + thpb->GetXMin() ) ;
         float q2val = 0.5*( thpb->GetYMax() + thpb->GetYMin() ) ;
         printf("  %3d : x = %9.5f  Q2 = %7.1f\n", bi, xval, q2val ) ;
         x_bin_centers[bi] = xval ;
         q2_bin_centers[bi] = q2val ;
      } // bi
   }

   printf("\n\n Collecting bin edges.\n\n") ; fflush(stdout) ;
   double x_bin_edge_low[9000] ;
   double x_bin_edge_high[9000] ;
   double q2_bin_edge_low[9000] ;
   double q2_bin_edge_high[9000] ;
   for ( int bi=1; bi<=nb; bi++ ) {
      TH2PolyBin* thpb = (TH2PolyBin*) tl_bins -> At( bi-1 ) ; //**** note the different index convention!
      x_bin_edge_low[bi] = thpb->GetXMin() ;
      x_bin_edge_high[bi] = thpb->GetXMax() ;
      q2_bin_edge_low[bi] = thpb->GetYMin() ;
      q2_bin_edge_high[bi] = thpb->GetYMax() ;
   } // bi

   printf("\n\n") ;
   for ( int bi=1; bi<=nb; bi ++ ) {
      printf("   bin %3d :  x %9.5f to %9.5f,  center %9.5f     q2 %9.1f to %9.1f,  center %9.1f\n",
        bi, x_bin_edge_low[bi], x_bin_edge_high[bi], x_bin_centers[bi],
            q2_bin_edge_low[bi], q2_bin_edge_high[bi], q2_bin_centers[bi] ) ;
   }
   printf("\n\n") ;



   TH2Poly* h_xsec = (TH2Poly*) hp -> Clone( "h_xsec" ) ;
   h_xsec -> Reset("") ;
   h_xsec -> SetTitle("Cross section" ) ;

   TH2Poly* h_rxsec = (TH2Poly*) hp -> Clone( "h_rxsec" ) ;
   h_rxsec -> Reset("") ;
   h_rxsec -> SetTitle("Reduced cross section" ) ;

   TH2Poly* h_xsec_ave = (TH2Poly*) hp -> Clone( "h_xsec_ave" ) ;
   h_xsec_ave -> Reset("") ;
   h_xsec_ave -> SetTitle("Cross section average in bin" ) ;

   TH2Poly* h_xsec_ave_times_bin_area = (TH2Poly*) hp -> Clone( "h_xsec_ave_times_bin_area" ) ;
   h_xsec_ave_times_bin_area -> Reset("") ;
   h_xsec_ave_times_bin_area -> SetTitle("Cross section average in bin times the bin area" ) ;

   TH2Poly* h_rxsec_ave = (TH2Poly*) hp -> Clone( "h_rxsec_ave" ) ;
   h_rxsec_ave -> Reset("") ;
   h_rxsec_ave -> SetTitle("Reduced cross section average in bin" ) ;


   TH2Poly* h_xsec_bcc = (TH2Poly*) hp -> Clone( "h_xsec_bcc" ) ;
   h_xsec_bcc -> Reset("") ;
   h_xsec_bcc -> SetTitle("Cross section bin center correction" ) ;

   TH2Poly* h_rxsec_bcc = (TH2Poly*) hp -> Clone( "h_rxsec_bcc" ) ;
   h_rxsec_bcc -> Reset("") ;
   h_rxsec_bcc -> SetTitle("Reduced cross section bin center correction" ) ;




   printf("\n\n Creating instance of H1QCDFunc\n\n") ;

   H1QCDFunc *qcdfunc = new H1QCDFunc() ;

   for ( int bi=1; bi<=nb; bi++ ) {


      float q2 = q2_bin_centers[bi] ;
      float x = x_bin_centers[bi] ;
      if ( q2 <= 0 ) continue ;
      if ( x <= 0 ) continue ;

      float y = q2 / ( s * x ) ;

      float bin_area = ( x_bin_edge_high[bi] - x_bin_edge_low[bi] ) * ( q2_bin_edge_high[bi] - q2_bin_edge_low[bi] ) ;

      h_xsec -> SetBinContent( bi, 0. ) ;
      h_xsec -> SetBinError( bi, 0. ) ;
      h_rxsec -> SetBinContent( bi, 0. ) ;
      h_rxsec -> SetBinError( bi, 0. ) ;

      h_xsec_ave -> SetBinContent( bi, 0. ) ;
      h_xsec_ave -> SetBinError( bi, 0. ) ;
      h_rxsec_ave -> SetBinContent( bi, 0. ) ;
      h_rxsec_ave -> SetBinError( bi, 0. ) ;

      h_xsec_ave_times_bin_area -> SetBinContent( bi, 0. ) ;
      h_xsec_ave_times_bin_area -> SetBinError( bi, 0. ) ;


      h_xsec_bcc -> SetBinContent( bi, 0. ) ;
      h_xsec_bcc -> SetBinError( bi, 0. ) ;
      h_rxsec_bcc -> SetBinContent( bi, 0. ) ;
      h_rxsec_bcc -> SetBinError( bi, 0. ) ;

      if ( y > 1.00 ) continue ;

      float xsec = qcdfunc -> GetNCXSec( x, q2, false ) ;
      float rxsec = qcdfunc -> GetNCXSec( x, q2, true ) ;

      /////////////printf("\n Just before first calc_bin_ave:  x = %9.5f  Q2 = %7.1f\n", x, q2 ) ;
      float xsec_ave = calc_bin_ave( x_bin_edge_low[bi], x_bin_edge_high[bi], q2_bin_edge_low[bi], q2_bin_edge_high[bi], qcdfunc, false, bi ) ;
      float rxsec_ave = calc_bin_ave( x_bin_edge_low[bi], x_bin_edge_high[bi], q2_bin_edge_low[bi], q2_bin_edge_high[bi], qcdfunc, true, bi ) ;



      h_xsec_ave_times_bin_area -> SetBinContent( bi, xsec_ave * bin_area ) ;
      h_xsec_ave_times_bin_area -> SetBinError( bi, xsec_ave * bin_area ) ;


      h_xsec -> SetBinContent( bi, xsec ) ;
      h_rxsec -> SetBinContent( bi, rxsec ) ;

      h_xsec_ave -> SetBinContent( bi, xsec_ave ) ;
      h_rxsec_ave -> SetBinContent( bi, rxsec_ave ) ;

      h_xsec_bcc -> SetBinContent( bi, xsec / xsec_ave ) ;
      h_rxsec_bcc -> SetBinContent( bi, rxsec / rxsec_ave ) ;


      printf(" bin %3d :  x = %8.5f,  Q2 = %8.1f,  y = %8.5f,   rXsec = %8.5f  rXsec_ave = %8.5f  ratio = %8.5f\n", bi, x, q2, y, rxsec, rxsec_ave, rxsec/rxsec_ave ) ;


   } // bi


   printf("\n\n pwd before opening output file:  %s\n", gDirectory -> GetPath() ) ;
   char outfile[1000] ;
   if ( use_h1_bin_centers ) {
      sprintf( outfile, "cbc-poly-output-h1-bin-centers.root" ) ;
   } else {
      sprintf( outfile, "cbc-poly-output.root" ) ;
   }
   TFile* tf_out = new TFile( outfile, "recreate" ) ;
   char outdir[1000] ;
   sprintf( outdir, "%s", gDirectory -> GetPath() ) ;


   printf("\n\n pwd after opening output file:  %s\n", gDirectory -> GetPath() ) ;

   if ( save_bin_th2s ) {
      for ( int gbi=1; gbi<=nb; gbi++ ) {
         char hname[100] ;
         sprintf( hname, "h_bin_%02d", gbi ) ;
         gDirectory -> cd( "root:/" ) ;
         TH2F* hp_bin = (TH2F*) gDirectory -> FindObject( hname ) ;
         if ( hp_bin != 0 ) {
            gDirectory -> cd( outdir ) ;
            hp_bin -> Write() ;
            printf("Writing %s\n", hname ) ;
         }
      } // gbi
   }

   gDirectory -> cd( outdir ) ;
   hp -> Write() ;
   if ( h_h1_x_val != 0x0 ) { h_h1_x_val -> Write() ; }
   if ( h_h1_q2_val != 0x0 ) { h_h1_q2_val -> Write() ; }
   if ( h_h1_gbi != 0x0 ) { h_h1_gbi -> Write() ; }
   h_xsec -> Write() ;
   h_rxsec -> Write() ;
   h_xsec_ave -> Write() ;
   h_rxsec_ave -> Write() ;
   h_xsec_bcc -> Write() ;
   h_rxsec_bcc -> Write() ;
   h_xsec_ave_times_bin_area -> Write() ;


   tf_out -> Close() ;



   printf("\n\n Done.\n\n") ;

   return 0 ;

} // main

//=============================================================================================


float calc_bin_ave( float x_low, float x_high, float q2_low, float q2_high, H1QCDFunc* qcdfunc, bool do_rxsec, int bi ) {

      ///////// printf(" calc_bin_ave:     x range:  %9.5f to %9.5f    Q2 range %7.1f to %7.1f\n", x_low, x_high, q2_low, q2_high ) ;

   int nsteps_x(21) ;
   int nsteps_q2(21) ;

   float x_step_width = (x_high - x_low) / nsteps_x ;
   float q2_step_width = (q2_high - q2_low) / nsteps_q2 ;

   TH2F* hp(0x0) ;
   if ( save_bin_th2s && !do_rxsec ) {
      char hname[100] ;
      sprintf( hname, "h_bin_%02d", bi ) ;
      hp = new TH2F( hname, hname, nsteps_x, x_low, x_high, nsteps_q2, q2_low, q2_high ) ;
   }

   float xsec_sum(0.) ;
   int n_points(0) ;
   for ( int q2i=0; q2i<nsteps_q2; q2i++ ) {
      float q2 = q2_low + (q2i + 0.5) * q2_step_width ;
      for ( int xi=0; xi<nsteps_x; xi++ ) {
         float x = x_low + (xi + 0.5) * x_step_width ;
         float y = q2 / ( s * x ) ;
         if ( y > 1 ) {
            //printf("  ** calc_bin_ave:  y = %8.5f,  x = %8.5f,  Q2 = %7.1f\n", y, x, q2 ) ;
            continue ;
         }
         float this_xsec = qcdfunc -> GetNCXSec( x, q2, do_rxsec ) ;
         xsec_sum += this_xsec ;
         n_points ++ ;
         if ( save_bin_th2s && !do_rxsec ) {
            hp -> SetBinContent( xi+1, q2i+1, this_xsec ) ;
            hp -> SetBinError( xi+1, q2i+1, 0. ) ;
         }
      } // q2i
   } // q2i

   if ( n_points == 0 ) {
      printf(" *** calc_bin_ave: n_points is zero.\n") ;
   }

   if ( n_points == 0 ) return 0 ;
   return xsec_sum / n_points ;

} // calc_bin_integral

//=============================================================================================
















