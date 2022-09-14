
#include "histio.c"
#include "utils.c"
#include "draw_2d_slices.c"
#include "TExec.h"


//-------

void draw_ru( const char* infile = "ru1-output-method3.root" ) {

                     const char* method_name_a = "DNN" ;
                     const char* method_name_b = "eSigma" ;

      gStyle -> SetPalette( kBird ) ;
      gStyle -> SetPadRightMargin(0.15) ;

      TCanvas* can1 = (TCanvas*) gDirectory -> FindObject( "can1" ) ;
      if ( can1 == 0x0 ) { can1 = new TCanvas( "can1", "", 50, 50, 1500, 1200 ) ; }

      TCanvas* can2 = (TCanvas*) gDirectory -> FindObject( "can2" ) ;
      if ( can2 == 0x0 ) { can2 = new TCanvas( "can2", "", 1550, 50, 800, 1200 ) ; }



      gStyle -> SetOptStat(0) ;

      gDirectory -> Delete( "*" ) ;


      TFile* tf_in = new TFile( infile, "READ" ) ;
      if ( tf_in == 0x0 ) { printf("\n\n *** bad input file: %s\n\n", infile ) ; return ; }


      TH2*  h_in_gen_vs_obs_a = (TH2*) tf_in -> Get( "h_in_gen_vs_obs_a" ) ;
      TH1*  hReco_a = (TH1*) tf_in -> Get( "hReco_a" ) ;
      TH1F* h_1d_gen_val_trimmed_a = (TH1F*) tf_in -> Get( "h_1d_gen_val_trimmed_a" ) ;
      TH2F* h_unfold_cor_mat_trimmed_a = (TH2F*) tf_in -> Get( "h_unfold_cor_mat_trimmed_a" ) ;

      TH2*  h_in_gen_vs_obs_b = (TH2*) tf_in -> Get( "h_in_gen_vs_obs_b" ) ;
      TH1*  hReco_b = (TH1*) tf_in -> Get( "hReco_b" ) ;
      TH1F* h_1d_gen_val_trimmed_b = (TH1F*) tf_in -> Get( "h_1d_gen_val_trimmed_b" ) ;
      TH2F* h_unfold_cor_mat_trimmed_b = (TH2F*) tf_in -> Get( "h_unfold_cor_mat_trimmed_b" ) ;

      TH1F* h_global_correlation_coeff_trimmed_a = (TH1F*) tf_in -> Get( "h_global_correlation_coeff_trimmed_a" ) ;
      TH1F* h_global_correlation_coeff_trimmed_b = (TH1F*) tf_in -> Get( "h_global_correlation_coeff_trimmed_b" ) ;
      TH1F* h_unfolding_result_err_trimmed_a = (TH1F*) tf_in -> Get( "h_unfolding_result_err_trimmed_a" ) ;
      TH1F* h_unfolding_result_err_trimmed_b = (TH1F*) tf_in -> Get( "h_unfolding_result_err_trimmed_b" ) ;

      TH1F* h_unfolding_result_error_ratio = (TH1F*) tf_in -> Get( "h_unfolding_result_error_ratio" ) ;

      TH1F* h_1d_unfolded_val_trimmed_a = (TH1F*) tf_in -> Get( "h_1d_unfolded_val_trimmed_a" ) ;
      TH1F* h_1d_unfolded_val_trimmed_b = (TH1F*) tf_in -> Get( "h_1d_unfolded_val_trimmed_b" ) ;
      TH1F* h_1d_unfolded_val_trimmed_b_copy = (TH1F*) tf_in -> Get( "h_1d_unfolded_val_trimmed_b_copy" ) ;



      TExec* change_hist_palette = new TExec( "change_hist_palette", "Setup2DhistPalette();" );
      TExec* change_cor_palette = new TExec( "change_cor_palette", "SetupCorrelationPalette();" );




      int ci ;

      can1 -> cd() ;
      can1 -> Clear() ;
      can1 -> Divide(4,3) ;

      ci = 1 ;


    //--- main plots for A

      can1 -> cd( ci++ ) ;
      h_in_gen_vs_obs_a -> DrawCopy("colz") ;
      change_hist_palette -> Draw() ;
      h_in_gen_vs_obs_a -> DrawCopy("colz same") ;

      can1 -> cd( ci++ ) ;
      hReco_a -> DrawCopy( "colz" ) ;
      //gPad -> SetLogz(1) ;
      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;

      can1 -> cd( ci++ ) ;
      h_1d_unfolded_val_trimmed_a -> SetMaximum( 1.4 * h_1d_unfolded_val_trimmed_a -> GetMaximum() ) ;
      h_1d_unfolded_val_trimmed_a -> DrawCopy() ;
      h_1d_gen_val_trimmed_a -> SetLineColor(2) ;
      h_1d_gen_val_trimmed_a -> DrawCopy("same hist") ;


      can1 -> cd( ci++ ) ;
      h_unfold_cor_mat_trimmed_a -> SetMinimum(-1.) ;
      h_unfold_cor_mat_trimmed_a -> SetMaximum( 1.) ;
      h_unfold_cor_mat_trimmed_a -> DrawCopy("colz") ;
      change_cor_palette -> Draw() ;
      h_unfold_cor_mat_trimmed_a -> DrawCopy("colz same") ;





    //--- main plots for B

      can1 -> cd( ci++ ) ;
      h_in_gen_vs_obs_b -> DrawCopy("colz") ;
      change_hist_palette -> Draw() ;
      h_in_gen_vs_obs_b -> DrawCopy("colz same") ;

      can1 -> cd( ci++ ) ;
      hReco_b -> DrawCopy( "colz" ) ;
      //gPad -> SetLogz(1) ;
      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;


      can1 -> cd( ci++ ) ;
      h_1d_unfolded_val_trimmed_b -> SetMaximum( 1.4 * h_1d_unfolded_val_trimmed_b -> GetMaximum() ) ;
      h_1d_unfolded_val_trimmed_b -> DrawCopy() ;
      h_1d_gen_val_trimmed_b -> SetLineColor(2) ;
      h_1d_gen_val_trimmed_b -> DrawCopy("same hist") ;


      can1 -> cd( ci++ ) ;
      h_unfold_cor_mat_trimmed_b -> SetMinimum(-1.) ;
      h_unfold_cor_mat_trimmed_b -> SetMaximum( 1.) ;
      h_unfold_cor_mat_trimmed_b -> DrawCopy("colz") ;
      change_cor_palette -> Draw() ;
      h_unfold_cor_mat_trimmed_b -> DrawCopy("colz same") ;






    //--- plots with both superimposed

      can1 -> cd( ci++ ) ;
      h_global_correlation_coeff_trimmed_a -> SetMaximum(1.1) ;
      h_global_correlation_coeff_trimmed_a -> SetLineColor(4) ;
      h_global_correlation_coeff_trimmed_b -> SetLineColor(2) ;
      h_global_correlation_coeff_trimmed_a -> DrawCopy("hist") ;
      h_global_correlation_coeff_trimmed_b -> DrawCopy("same hist") ;
      gPad -> SetGridy(1) ;



      can1 -> cd( ci++ ) ;
      h_unfolding_result_err_trimmed_a -> SetLineColor(4) ;
      h_unfolding_result_err_trimmed_b -> SetLineColor(2) ;
      h_unfolding_result_err_trimmed_b -> DrawCopy("hist") ;
      h_unfolding_result_err_trimmed_a -> DrawCopy("hist same") ;
      gPad -> SetGridy(1) ;


      can1 -> cd( ci++ ) ;
      h_unfolding_result_error_ratio -> SetMaximum( 1.1 ) ;
      h_unfolding_result_error_ratio -> DrawCopy( "hist" ) ;
      gPad -> SetGridy(1) ;


      //////TH1* h_1d_unfolded_val_trimmed_b_copy = (TH1*) h_1d_unfolded_val_trimmed_b->Clone( "h_1d_unfolded_val_trimmed_b_copy") ;
      h_1d_unfolded_val_trimmed_b_copy -> SetLineColor(2) ;

      can1 -> cd( ci++ ) ;
      h_1d_unfolded_val_trimmed_a -> DrawCopy() ;
      h_1d_unfolded_val_trimmed_b_copy -> DrawCopy("same") ;




      can1 -> Update() ;
      can1 -> Draw() ;
      gSystem -> ProcessEvents() ;

      can1 -> SaveAs("mt3-can1.pdf") ;






   //-----------

      gStyle -> SetPadRightMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;


      can2 -> cd() ;
      can2 -> Clear() ;
      can2 -> Divide(2,2) ;

      char htitle_a[100] ;
      char htitle_b[100] ;

      sprintf( htitle_a, "Unfolded, %s", method_name_a ) ;
      sprintf( htitle_b, "Unfolded, %s", method_name_b ) ;

      ci = 1 ;

      can2 -> cd( ci++ ) ;
      draw_2d_slices( hReco_a, 0, htitle_a, 1 ) ;

      can2 -> cd( ci++ ) ;
      draw_2d_slices( hReco_b, 0, htitle_b, 1 ) ;



      can2 -> cd( ci++ ) ;
      draw_2d_slices( hReco_a, 1, htitle_a, 1 ) ;

      can2 -> cd( ci++ ) ;
      draw_2d_slices( hReco_b, 1, htitle_b, 1 ) ;


////  can2 -> SaveAs("mt3-can2.pdf") ;

      printf("\n\n\n") ;






   }












