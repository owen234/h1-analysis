
#include "histio.c"
#include "utils.c"
#include "draw_2d_slices.c"
#include "print_th2_table.c"

#include "TCanvas.h"
#include "TGraph.h"
#include "TPad.h"
#include "TExec.h"

#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldTUnfold.h"
#include "RooUnfoldSvd.h"
#endif

using namespace RooUnfolding ;


//-------

std::set<int> unused_global_bins ;

//-------

void zero_unused_bins( TH1*  hp, RooUnfoldResponse* rur ) {

   if ( unused_global_bins.size() <= 0 ) return ;

   for ( int i=1; i<=hp->GetNbinsX(); i++ ) {
      double x = hp->GetXaxis()->GetBinCenter( i ) ;
      for ( int j=1; j<=hp->GetNbinsY(); j++ ) {
         double y = hp->GetYaxis()->GetBinCenter( j ) ;
         /////int global_bin = rur->FindBin( hp, x, y ) ;
         int global_bin = findBin( hp, x, y ) ;
         if ( unused_global_bins.find( global_bin ) != unused_global_bins.end() ) {
             printf(" zero_unused_bins : zeroing bin  %2d, %2d  (%9.4f, %9.4f) :  content is %9.3f +/- %9.3f\n",
                i, j, hp -> GetXaxis() -> GetBinCenter(i), hp -> GetYaxis() -> GetBinCenter(j),
                hp -> GetBinContent( i, j ), hp -> GetBinError( i, j ) ) ;
             hp -> SetBinContent( i, j, 0. ) ;
             hp -> SetBinError( i, j, 0. ) ;
         }
      } // j
   } // i

}

//-------

TH2F* trim_unused_bins( TH2F* hp, RooUnfoldResponse* rur ) {

   if ( unused_global_bins.size() <= 0 ) {
      TH1* h_gen_source = rur -> Htruth() ;
      for ( int i=1; i<=h_gen_source->GetNbinsX(); i++ ) {
         double x = h_gen_source->GetXaxis()->GetBinCenter( i ) ;
         for ( int j=1; j<=h_gen_source->GetNbinsY(); j++ ) {
            double y = h_gen_source->GetYaxis()->GetBinCenter( j ) ;
            float entries = h_gen_source -> GetBinContent( i, j ) ;
            if ( entries < 1. ) {
               /////int global_bin = rur -> FindBin( (TH1*) h_gen_source, x, y ) ;
               int global_bin = findBin( (TH1*) h_gen_source, x, y ) ;
               printf("  trim_unused_bins:  %2d, %2d  (%9.5f, %9.5f)  removing bin with low entries  %9.4f.  global_bin %3d\n", i, j, x, y, entries, global_bin ) ;
               unused_global_bins.insert( global_bin ) ;
            }
      ///   if ( i == 1 || i == h_gen_source->GetNbinsX() || j == 1 || j == h_gen_source->GetNbinsX() ) {
      ///      int global_bin = rur -> FindBin( (TH1*) h_gen_source, x, y ) ;
      ///      printf("  trim_unused_bins:  %2d, %2d  (%9.5f, %9.5f)  removing edge bin.  global_bin %3d\n", i, j, x, y, global_bin ) ;
      ///      unused_global_bins.insert( global_bin ) ;
      ///   }
            if ( j < 3 || j == h_gen_source->GetNbinsY() ) {
               //////int global_bin = rur -> FindBin( (TH1*) h_gen_source, x, y ) ;
               int global_bin = findBin( (TH1*) h_gen_source, x, y ) ;
               printf("  trim_unused_bins:  %2d, %2d  (%9.5f, %9.5f)  removing edge bin.  global_bin %3d\n", i, j, x, y, global_bin ) ;
               unused_global_bins.insert( global_bin ) ;
            }
            if ( entries <= 0 ) {
               //////int global_bin = rur -> FindBin( (TH1*) h_gen_source, x, y ) ;
               int global_bin = findBin( (TH1*) h_gen_source, x, y ) ;
               printf("  trim_unused_bins:  %2d, %2d  (%9.5f, %9.5f)  global_bin %3d unused.\n", i, j, x, y, global_bin ) ;
               unused_global_bins.insert( global_bin ) ;
            }
         } // j
      } // i
   }

   int nb_input = hp -> GetNbinsX() ;
   int nb_trimmed = nb_input - unused_global_bins.size() ;

   char hname[100] ;
   sprintf( hname, "%s_trimmed", hp -> GetName() ) ;
   TH2F* hpr = new TH2F( hname, hp->GetTitle(), nb_trimmed, -0.5, nb_trimmed-0.5,  nb_trimmed, -0.5, nb_trimmed-0.5 ) ;
   int out_i = 1 ;
   for ( int in_i=1; in_i <= nb_input; in_i++ ) {
      //printf(" trim_unused_bins: in_i %3d\n", in_i ) ;
      ////if ( unused_global_bins.contains( in_i ) ) continue ; // NFG
      if ( unused_global_bins.find( in_i-1 ) != unused_global_bins.end() ) {
         //printf(" trim_unused_bins: skipping in_i %2d\n", in_i ) ;
         continue ;
      }
      int out_j = 1 ;
      for ( int in_j=1; in_j <= nb_input; in_j++ ) {
         //printf(" trim_unused_bins: in_j %3d\n", in_j ) ;
         ////if ( unused_global_bins.contains( in_j ) ) continue ; // NFG
         if ( unused_global_bins.find( in_j-1 ) != unused_global_bins.end() ) {
            //printf(" trim_unused_bins: skipping in_j %2d\n", in_j ) ;
            continue ;
         }
         //printf(" trim_unused_bins: Setting content for %2d, %2d to %9.5f\n", out_i, out_j, hp -> GetBinContent( in_i, in_j ) ) ;
         hpr -> SetBinContent( out_i, out_j, hp -> GetBinContent( in_i, in_j ) ) ;
         hpr -> SetBinError( out_i, out_j, hp -> GetBinError( in_i, in_j ) ) ;
         out_j ++ ;
      } // in_j
      out_i ++ ;
   } // in_i

   return hpr ;

}


//-------

TH1F* trim_unused_bins( TH1F* hp, RooUnfoldResponse* rur ) {

   if ( unused_global_bins.size() <= 0 ) {
      TH1* h_gen_source = rur -> Htruth() ;
      for ( int i=1; i<=h_gen_source->GetNbinsX(); i++ ) {
         double x = h_gen_source->GetXaxis()->GetBinCenter( i ) ;
         for ( int j=1; j<=h_gen_source->GetNbinsX(); j++ ) {
            double y = h_gen_source->GetYaxis()->GetBinCenter( j ) ;
            float entries = h_gen_source -> GetBinContent( i, j ) ;
            if ( entries <= 0 ) {
               /////////int global_bin = rur -> FindBin( (TH1*) h_gen_source, x, y ) ;
               int global_bin = findBin( (TH1*) h_gen_source, x, y ) ;
               printf("  trim_unused_bins:  %2d, %2d  (%9.5f, %9.5f)  global_bin %3d unused.\n", i, j, x, y, global_bin ) ;
               unused_global_bins.insert( global_bin ) ;
            }
         } // j
      } // i
   }

   int nb_input = hp -> GetNbinsX() ;
   int nb_trimmed = nb_input - unused_global_bins.size() ;

   char hname[100] ;
   sprintf( hname, "%s_trimmed", hp -> GetName() ) ;
   TH1F* hpr = new TH1F( hname, hp->GetTitle(), nb_trimmed, -0.5, nb_trimmed-0.5  ) ;
   int out_i = 1 ;
   for ( int in_i=1; in_i <= nb_input; in_i++ ) {
      if ( unused_global_bins.find( in_i-1 ) != unused_global_bins.end() ) {
         continue ;
      }
      hpr -> SetBinContent( out_i, hp -> GetBinContent( in_i ) ) ;
      hpr -> SetBinError( out_i, hp -> GetBinError( in_i ) ) ;
      out_i ++ ;
   } // in_i

   return hpr ;

}

//-------

int main() {
                     const char* method_a = "dnn" ;
                     const char* method_b = "esigma" ;
                     const char* data_input_file = "fake-data-max-stats-h1-binning.root" ;
                     const char* response_input_file = "unfold-hists-h1-binning.root" ;
                     const char* vary_vs_varx_string = "q2_vs_x" ;
                     float svd_kterm = 150. ;
                     int method_index = 3 ;
                     //int n_iter = 1000 ; // this is huge because I hacked RooUnfoldBayes to start with a flat prior.
                     int n_iter = 40 ;

      char rur_name_base[100] ;
      sprintf( rur_name_base, "rur_2D_%s", vary_vs_varx_string ) ;

      char h_data_name_base[100] ;
      sprintf( h_data_name_base, "h_data_%s_obs", vary_vs_varx_string ) ;


      char rur_name_a[100] ;
      char rur_name_b[100] ;
      sprintf( rur_name_a, "%s_%s", rur_name_base, method_a ) ;
      sprintf( rur_name_b, "%s_%s", rur_name_base, method_b ) ;

      char h_data_name_a[100] ;
      char h_data_name_b[100] ;
      sprintf( h_data_name_a, "%s_%s", h_data_name_base, method_a ) ;
      sprintf( h_data_name_b, "%s_%s", h_data_name_base, method_b ) ;

      char method_name_a[100] ;
      char method_name_b[100] ;
      sprintf( method_name_a, "%s", method_a ) ;
      sprintf( method_name_b, "%s", method_b ) ;

      gStyle -> SetPalette( kBird ) ;
      gStyle -> SetPadLeftMargin(0.10) ;
      gStyle -> SetPadRightMargin(0.15) ;

      TCanvas* can1 = (TCanvas*) gDirectory -> FindObject( "can1" ) ;
      if ( can1 == 0x0 ) { can1 = new TCanvas( "can1", "", 50, 50, 1500, 1200 ) ; }

      TCanvas* can2 = (TCanvas*) gDirectory -> FindObject( "can2" ) ;
      if ( can2 == 0x0 ) { can2 = new TCanvas( "can2", "No Acceptance Correction", 1550, 50, 800, 1200 ) ; }

      TCanvas* can3 = (TCanvas*) gDirectory -> FindObject( "can3" ) ;
      if ( can3 == 0x0 ) { can3 = new TCanvas( "can3", "With Acceptance Correction", 1650, 150, 800, 1200 ) ; }

      TCanvas* can4 = (TCanvas*) gDirectory -> FindObject( "can4" ) ;
      if ( can4 == 0x0 ) { can4 = new TCanvas( "can4", "With Acceptance Correction", 1750, 250, 800, 800 ) ; }

      TCanvas* can5 = (TCanvas*) gDirectory -> FindObject( "can5" ) ;
      if ( can5 == 0x0 ) { can5 = new TCanvas( "can5", "Unfolding stat err ratio, A/B", 1150, 350, 1400, 800 ) ; }


      gStyle -> SetOptStat(0) ;

      gDirectory -> Delete( "*" ) ;

      printf("\n\n Response file: %s\n", response_input_file ) ;
      TFile tf_response( response_input_file, "read" ) ;
      tf_response.ls() ;

      printf("\n\n Data hist file: %s\n", data_input_file ) ;
      TFile tf_data( data_input_file, "read" ) ;
      tf_data.ls() ;

      gDirectory -> cd( "Rint:/" ) ;

      char htitle[1000] ;
      char hname[1000] ;





     //--- things needed for acceptance correction

      sprintf( hname, "h_%s_gen_no_cuts", vary_vs_varx_string ) ;
      TH2F* h_2d_gen_no_cuts = (TH2F*) tf_response.Get( hname ) ;
      if ( h_2d_gen_no_cuts == 0x0 ) { printf("\n\n *** can't find %s\n\n", hname ) ; return -1 ; }


      sprintf( hname, "h_%s_gen_%s_sel", vary_vs_varx_string, method_a ) ;
      TH2F* h_2d_gen_a_sel = (TH2F*) tf_response.Get( hname ) ;
      if ( h_2d_gen_a_sel == 0x0 ) { printf("\n\n *** can't find %s\n\n", hname ) ; return  -1; }


      sprintf( hname, "h_%s_gen_%s_sel", vary_vs_varx_string, method_b ) ;
      TH2F* h_2d_gen_b_sel = (TH2F*) tf_response.Get( hname ) ;
      if ( h_2d_gen_b_sel == 0x0 ) { printf("\n\n *** can't find %s\n\n", hname ) ; return -1 ; }


      sprintf( hname, "h_%s_gen_acceptance_correction_%s", vary_vs_varx_string, method_a ) ;
      TH2F* h_2d_gen_acceptance_correction_a = (TH2F*) h_2d_gen_no_cuts -> Clone( hname ) ;
      h_2d_gen_acceptance_correction_a -> Reset() ;
      sprintf( htitle, "Acceptance correction, %s", method_a ) ;
      h_2d_gen_acceptance_correction_a -> SetTitle( htitle ) ;


      sprintf( hname, "h_%s_gen_acceptance_correction_%s", vary_vs_varx_string, method_b ) ;
      TH2F* h_2d_gen_acceptance_correction_b = (TH2F*) h_2d_gen_no_cuts -> Clone( hname ) ;
      h_2d_gen_acceptance_correction_b -> Reset() ;
      sprintf( htitle, "Acceptance correction, %s", method_b ) ;
      h_2d_gen_acceptance_correction_b -> SetTitle( htitle ) ;


      for ( int xbi = 1; xbi <= h_2d_gen_no_cuts -> GetNbinsX(); xbi ++ ) {
         for ( int ybi = 1; ybi <= h_2d_gen_no_cuts -> GetNbinsY(); ybi ++ ) {
            float val_no_cuts = h_2d_gen_no_cuts -> GetBinContent( xbi, ybi ) ;
            float val_a_sel   = h_2d_gen_a_sel -> GetBinContent( xbi, ybi ) ;
            float val_b_sel   = h_2d_gen_b_sel -> GetBinContent( xbi, ybi ) ;
            float ac_a = 1. ;
            float ac_b = 1. ;
            if ( val_a_sel > 0 ) ac_a = val_no_cuts / val_a_sel ;
            if ( val_b_sel > 0 ) ac_b = val_no_cuts / val_b_sel ;
            h_2d_gen_acceptance_correction_a -> SetBinContent( xbi, ybi, ac_a ) ;
            h_2d_gen_acceptance_correction_b -> SetBinContent( xbi, ybi, ac_b ) ;
            h_2d_gen_acceptance_correction_a -> SetBinError( xbi, ybi, 0. ) ;
            h_2d_gen_acceptance_correction_b -> SetBinError( xbi, ybi, 0. ) ;
         } // ybi
      } // xbi









      RooUnfoldResponse* rur_a = (RooUnfoldResponse*) tf_response.Get( rur_name_a ) ;
      if ( rur_a == 0x0 ) { printf("\n\n *** can't find %s\n\n", rur_name_a ) ; return -1 ; }

      RooUnfoldResponse* rur_b = (RooUnfoldResponse*) tf_response.Get( rur_name_b ) ;
      if ( rur_b == 0x0 ) { printf("\n\n *** can't find %s\n\n", rur_name_b ) ; return -1 ; }





      TH2* h_in_gen_vs_obs_a = rur_a -> Hresponse() ;

      TH1* h_obs_source_a = rur_a -> Hmeasured() ;
      TH1* h_gen_source_a = rur_a -> Htruth() ;

      TH1* h_obs_data_a = (TH1*) tf_data.Get( h_data_name_a ) ;
      if ( h_obs_data_a == 0x0 ) { printf("\n\n *** can't find %s\n\n", h_data_name_a ) ; return -1 ; }

      sprintf( htitle, "Response matrix for log10 Q2 vs log10 x, %s", method_name_a ) ;
      h_in_gen_vs_obs_a -> SetName( "h_in_gen_vs_obs_a" ) ;
      h_in_gen_vs_obs_a -> SetTitle( htitle ) ;
      h_in_gen_vs_obs_a -> SetXTitle( "Reconstructed bin number" ) ;
      h_in_gen_vs_obs_a -> SetYTitle( "Gen bin number" ) ;




      TH2* h_in_gen_vs_obs_b = rur_b -> Hresponse() ;

      TH1* h_obs_source_b = rur_b -> Hmeasured() ;
      TH1* h_gen_source_b = rur_b -> Htruth() ;

      TH1* h_obs_data_b = (TH1*) tf_data.Get( h_data_name_b ) ;
      if ( h_obs_data_b == 0x0 ) { printf("\n\n *** can't find %s\n\n", h_data_name_b ) ; return -1 ; }

      sprintf( htitle, "Response matrix for log10 Q2 vs log10 x, %s", method_name_b ) ;
      h_in_gen_vs_obs_b -> SetName( "h_in_gen_vs_obs_b" ) ;
      h_in_gen_vs_obs_b -> SetTitle( htitle ) ;
      h_in_gen_vs_obs_b -> SetXTitle( "Reconstructed bin number" ) ;
      h_in_gen_vs_obs_b -> SetYTitle( "Gen bin number" ) ;





      rur_a -> UseOverflow(false) ;
      rur_b -> UseOverflow(false) ;




      RooUnfold* unfold_a ;
      RooUnfold* unfold_b ;
      if ( method_index == 1 ) {
         unfold_a = new RooUnfoldBayes( rur_a, h_obs_data_a, n_iter ) ;
         unfold_b = new RooUnfoldBayes( rur_b, h_obs_data_b, n_iter ) ;
      } else if ( method_index == 2 ) {
         unfold_a = new RooUnfoldTUnfold( rur_a, h_obs_data_a ) ;
         unfold_b = new RooUnfoldTUnfold( rur_b, h_obs_data_b ) ;
      } else if ( method_index == 3 ) {
         unfold_a = new RooUnfoldSvd( rur_a, h_obs_data_a, svd_kterm ) ;
         unfold_b = new RooUnfoldSvd( rur_b, h_obs_data_b, svd_kterm ) ;

      } else {
         printf("\n\n *** I don't know method_index = %d\n\n", method_index ) ;
         return -1 ;
      }


      /////////////TH1* hReco_a = (TH1*) unfold_a -> Hreco(RooUnfold::kCovariance) ;
      /////////////TH1* hReco_b = (TH1*) unfold_b -> Hreco(RooUnfold::kCovariance) ;

      TH1* hReco_a = (TH1*) unfold_a -> Hunfold() ;
      TH1* hReco_b = (TH1*) unfold_b -> Hunfold() ;

      printf("\n\n\n ========== Unfolding output histogram from method a\n\n") ;
      print_th2_table( (TH2F*) hReco_a ) ;
      printf("\n\n\n ==========================================================\n\n") ;

      TH1* hReco_ac_a = (TH1*) hReco_a -> Clone( "hReco_ac_a" ) ;
      TH1* hReco_ac_b = (TH1*) hReco_b -> Clone( "hReco_ac_b" ) ;

      hReco_ac_a -> Multiply( h_2d_gen_acceptance_correction_a ) ;
      hReco_ac_b -> Multiply( h_2d_gen_acceptance_correction_b ) ;

      sprintf( htitle, "Unfolded, log10 Q2 vs log10 x, %s", method_name_a ) ;
      hReco_a -> SetName( "hReco_a" ) ;
      hReco_a -> SetTitle( htitle ) ;
      hReco_a -> SetXTitle( "Unfolded log10 x" ) ;
      hReco_a -> SetYTitle( "Unfolded log10 Q2" ) ;

      hReco_ac_a -> SetTitle( htitle ) ;
      hReco_ac_a -> SetXTitle( "Unfolded log10 x" ) ;
      hReco_ac_a -> SetYTitle( "Unfolded log10 Q2" ) ;


      sprintf( htitle, "Unfolded, log10 Q2 vs log10 x, %s", method_name_b ) ;
      hReco_b -> SetName( "hReco_b" ) ;
      hReco_b -> SetTitle( htitle ) ;
      hReco_b -> SetXTitle( "Unfolded log10 x" ) ;
      hReco_b -> SetYTitle( "Unfolded log10 Q2" ) ;

      hReco_ac_b -> SetTitle( htitle ) ;
      hReco_ac_b -> SetXTitle( "Unfolded log10 x" ) ;
      hReco_ac_b -> SetYTitle( "Unfolded log10 Q2" ) ;



   ///printf("\n\n Unfolding results for A:\n") ;
   ///unfold_a -> PrintTable( cout ) ;
   ///printf("\n\n") ;

      ////////TMatrixD unfolding_cov_mat_a = unfold_a -> Ereco() ;
      TMatrixD unfolding_cov_mat_a = unfold_a -> Eunfold() ;

      ////////TMatrixD unfolding_inverse_cov_mat_a = unfold_a -> Wreco() ;
      TMatrixD unfolding_inverse_cov_mat_a = unfold_a -> Wunfold() ;

      ////////TVectorD unfolding_err_a = unfold_a -> ErecoV( RooUnfold::kCovariance ) ;
      TVectorD unfolding_err_a = unfold_a -> EunfoldV( RooUnfold::kCovariance ) ;

      ////////TVectorD unfolding_val_a = unfold_a -> Vreco() ;
      TVectorD unfolding_val_a = unfold_a -> Vunfold() ;

      TVectorD gen_val_a( unfolding_val_a.GetNrows() ) ;

      TVectorD acceptance_correction_val_a( unfolding_val_a.GetNrows() ) ;
      TVectorD unfolding_ac_val_a( unfolding_val_a.GetNrows() ) ;
      TVectorD unfolding_ac_err_a( unfolding_val_a.GetNrows() ) ;
      TVectorD gen_ac_val_a( unfolding_val_a.GetNrows() ) ;



   ///printf("\n\n Unfolding results for B:\n") ;
   ///unfold_b -> PrintTable( cout ) ;
   ///printf("\n\n") ;

      //////////TMatrixD unfolding_cov_mat_b = unfold_b -> Ereco() ;
      TMatrixD unfolding_cov_mat_b = unfold_b -> Eunfold() ;

      //////////TMatrixD unfolding_inverse_cov_mat_b = unfold_b -> Wreco() ;
      TMatrixD unfolding_inverse_cov_mat_b = unfold_b -> Wunfold() ;

      //////////TVectorD unfolding_err_b = unfold_b -> ErecoV( RooUnfold::kCovariance ) ;
      TVectorD unfolding_err_b = unfold_b -> EunfoldV( RooUnfold::kCovariance ) ;

      //////////TVectorD unfolding_val_b = unfold_b -> Vreco() ;
      TVectorD unfolding_val_b = unfold_b -> Vunfold() ;

      TVectorD gen_val_b( unfolding_val_b.GetNrows() ) ;

      TVectorD acceptance_correction_val_b( unfolding_val_b.GetNrows() ) ;
      TVectorD unfolding_ac_val_b( unfolding_val_b.GetNrows() ) ;
      TVectorD unfolding_ac_err_b( unfolding_val_b.GetNrows() ) ;
      TVectorD gen_ac_val_b( unfolding_val_b.GetNrows() ) ;








      sprintf( htitle, "Unfolding result error" ) ;
      TH1F* h_unfolding_result_err_a = new TH1F( "h_unfolding_result_err_a", htitle, unfolding_err_a.GetNrows(), -0.5, unfolding_err_a.GetNrows()-0.5 ) ;
      TH1F* h_unfolding_result_err_b = new TH1F( "h_unfolding_result_err_b", htitle, unfolding_err_b.GetNrows(), -0.5, unfolding_err_b.GetNrows()-0.5 ) ;
      for ( int i=0; i<unfolding_err_a.GetNrows(); i++ ) {
         h_unfolding_result_err_a -> SetBinContent( i+1, unfolding_err_a[i] ) ;
         h_unfolding_result_err_b -> SetBinContent( i+1, unfolding_err_b[i] ) ;
      }







      sprintf( htitle, "Unfolding cov. mat.  %s", method_name_a ) ;
      TH2F* h_unfold_cov_mat_a = new TH2F( "h_unfold_cov_mat_a", htitle,
          unfolding_cov_mat_a.GetNcols(), -0.5, unfolding_cov_mat_a.GetNcols()-0.5,
          unfolding_cov_mat_a.GetNcols(), -0.5, unfolding_cov_mat_a.GetNcols()-0.5 ) ;

      sprintf( htitle, "Unfolding cov. mat.  %s", method_name_b ) ;
      TH2F* h_unfold_cov_mat_b = new TH2F( "h_unfold_cov_mat_b", htitle,
          unfolding_cov_mat_b.GetNcols(), -0.5, unfolding_cov_mat_b.GetNcols()-0.5,
          unfolding_cov_mat_b.GetNcols(), -0.5, unfolding_cov_mat_b.GetNcols()-0.5 ) ;




      sprintf( htitle, "Unfolding cor. mat.  %s", method_name_a ) ;
      TH2F* h_unfold_cor_mat_a = new TH2F( "h_unfold_cor_mat_a", htitle,
          unfolding_cov_mat_a.GetNcols(), -0.5, unfolding_cov_mat_a.GetNcols()-0.5,
          unfolding_cov_mat_a.GetNcols(), -0.5, unfolding_cov_mat_a.GetNcols()-0.5 ) ;

      sprintf( htitle, "Unfolding cor. mat.  %s", method_name_b ) ;
      TH2F* h_unfold_cor_mat_b = new TH2F( "h_unfold_cor_mat_b", htitle,
          unfolding_cov_mat_b.GetNcols(), -0.5, unfolding_cov_mat_b.GetNcols()-0.5,
          unfolding_cov_mat_b.GetNcols(), -0.5, unfolding_cov_mat_b.GetNcols()-0.5 ) ;







      TH1F* h_global_correlation_coeff_a = new TH1F( "h_global_correlation_coeff_a", "Global cor. coef.",
         unfolding_cov_mat_a.GetNcols(), -0.5, unfolding_cov_mat_a.GetNcols()-0.5 ) ;

      TH1F* h_global_correlation_coeff_b = new TH1F( "h_global_correlation_coeff_b", "Global cor. coef.",
         unfolding_cov_mat_b.GetNcols(), -0.5, unfolding_cov_mat_b.GetNcols()-0.5 ) ;

      for ( int ri=0; ri<unfolding_cov_mat_a.GetNcols(); ri++ ) {
         int rbi = ri+1 ;
         for ( int ci=0; ci<unfolding_cov_mat_a.GetNcols(); ci++ ) {
            int cbi = ci+1 ;
            h_unfold_cov_mat_a -> SetBinContent( rbi, cbi, unfolding_cov_mat_a[ri][ci] ) ;
            h_unfold_cov_mat_b -> SetBinContent( rbi, cbi, unfolding_cov_mat_b[ri][ci] ) ;

            float rho = 1. ;
            float err_i, err_j ;

            err_i = 1. ;
            err_j = 1. ;
            if ( unfolding_cov_mat_a[ri][ri] > 0 ) err_i = sqrt( unfolding_cov_mat_a[ri][ri] ) ;
            if ( unfolding_cov_mat_a[ci][ci] > 0 ) err_j = sqrt( unfolding_cov_mat_a[ci][ci] ) ;
            if ( err_i > 0 && err_j > 0 ) rho = unfolding_cov_mat_a[ri][ci] / ( err_i * err_j ) ;
            h_unfold_cor_mat_a -> SetBinContent( rbi, cbi, rho ) ;

            err_i = 1. ;
            err_j = 1. ;
            if ( unfolding_cov_mat_b[ri][ri] > 0 ) err_i = sqrt( unfolding_cov_mat_b[ri][ri] ) ;
            if ( unfolding_cov_mat_b[ci][ci] > 0 ) err_j = sqrt( unfolding_cov_mat_b[ci][ci] ) ;
            if ( err_i > 0 && err_j > 0 ) rho = unfolding_cov_mat_b[ri][ci] / ( err_i * err_j ) ;
            h_unfold_cor_mat_b -> SetBinContent( rbi, cbi, rho ) ;

         } // ci

         float global_rho_a = 1. ;
         if ( unfolding_cov_mat_a[ri][ri] != 0 && unfolding_inverse_cov_mat_a[ri][ri] != 0 ) {
            global_rho_a = 0. ;
            float sqrt_arg = 1. - 1. / ( unfolding_cov_mat_a[ri][ri] * unfolding_inverse_cov_mat_a[ri][ri] ) ;
            if ( sqrt_arg > 0 ) global_rho_a = sqrt( sqrt_arg ) ;
         }
         h_global_correlation_coeff_a -> SetBinContent( rbi, global_rho_a ) ;

         float global_rho_b = 1. ;
         if ( unfolding_cov_mat_b[ri][ri] != 0 && unfolding_inverse_cov_mat_b[ri][ri] != 0 ) {
            global_rho_b = 0. ;
            float sqrt_arg = 1. - 1. / ( unfolding_cov_mat_b[ri][ri] * unfolding_inverse_cov_mat_b[ri][ri] ) ;
            if ( sqrt_arg > 0 ) global_rho_b = sqrt( sqrt_arg ) ;
         }
         h_global_correlation_coeff_b -> SetBinContent( rbi, global_rho_b ) ;

      } // ri

      /////h_unfold_cov_mat -> Print("all") ;





      TH1* h_gen_compare_a = (TH1*) h_gen_source_a -> Clone( "h_gen_compare_a" ) ;
      //////h_gen_compare_a -> Scale( ngen /( h_gen_source_a -> Integral() ) ) ;
      h_gen_compare_a -> Scale( ( hReco_a -> Integral() )/( h_gen_source_a -> Integral() ) ) ;

      TH1* h_gen_compare_b = (TH1*) h_gen_source_b -> Clone( "h_gen_compare_b" ) ;
      /////h_gen_compare_b -> Scale( ngen /( h_gen_source_b -> Integral() ) ) ;
      h_gen_compare_b -> Scale( ( hReco_b -> Integral() )/( h_gen_source_b -> Integral() ) ) ;


      {
         int vi = 0 ;
         for ( int ybi = 1; ybi <= h_gen_compare_a -> GetNbinsY(); ybi++ ) {
            for ( int xbi = 1; xbi <= h_gen_compare_a -> GetNbinsX(); xbi++ ) {
               gen_val_a[vi] = h_gen_compare_a -> GetBinContent( xbi, ybi ) ;
               gen_val_b[vi] = h_gen_compare_b -> GetBinContent( xbi, ybi ) ;
               acceptance_correction_val_a[vi] = h_2d_gen_acceptance_correction_a -> GetBinContent( xbi, ybi ) ;
               acceptance_correction_val_b[vi] = h_2d_gen_acceptance_correction_b -> GetBinContent( xbi, ybi ) ;
               unfolding_ac_val_a[vi] = unfolding_val_a[vi] * acceptance_correction_val_a[vi] ;
               unfolding_ac_val_b[vi] = unfolding_val_b[vi] * acceptance_correction_val_b[vi] ;
               unfolding_ac_err_a[vi] = unfolding_err_a[vi] * acceptance_correction_val_a[vi] ;
               unfolding_ac_err_b[vi] = unfolding_err_b[vi] * acceptance_correction_val_b[vi] ;
               gen_ac_val_a[vi] = gen_val_a[vi] * acceptance_correction_val_a[vi] ;
               gen_ac_val_b[vi] = gen_val_b[vi] * acceptance_correction_val_b[vi] ;
               vi ++ ;
            } // xbi
         } // ybi
      }


      printf("\n\n A: Unfolding results:\n") ;
      for ( int i=0; i<unfolding_val_a.GetNrows(); i++ ) {
         if ( unfolding_err_a[i] == 0 ) continue ;
         printf("A: global bin %3d :  gen = %9.3f, unfold =  %9.3f +/- %9.3f, diff = %9.3f,  diff/err = %9.3f  global correlation %9.3f\n",
            i, gen_val_a[i], unfolding_val_a[i], unfolding_err_a[i], (unfolding_val_a[i]-gen_val_a[i]),
            (unfolding_val_a[i]-gen_val_a[i])/unfolding_err_a[i],
            h_global_correlation_coeff_a->GetBinContent( i+1 ) ) ;
      }
      printf("\n\n\n") ;

      printf("\n\n B: Unfolding results:\n") ;
      for ( int i=0; i<unfolding_val_b.GetNrows(); i++ ) {
         if ( unfolding_err_b[i] == 0 ) continue ;
         printf("B: global bin %3d :  gen = %9.3f, unfold =  %9.3f +/- %9.3f, diff = %9.3f,  diff/err = %9.3f  global correlation %9.3f\n",
            i, gen_val_b[i], unfolding_val_b[i], unfolding_err_b[i], (unfolding_val_b[i]-gen_val_b[i]),
            (unfolding_val_b[i]-gen_val_b[i])/unfolding_err_b[i],
            h_global_correlation_coeff_b->GetBinContent( i+1 ) ) ;
      }
      printf("\n\n\n") ;







      sprintf( htitle, "1D view: unfolded  %s", method_name_a ) ;
      TH1F* h_1d_unfolded_val_a = new TH1F( "h_1d_unfolded_val_a", htitle, unfolding_val_a.GetNrows(), -0.5, unfolding_val_a.GetNrows()-0.5 ) ;
      TH1F* h_1d_gen_val_a = new TH1F( "h_1d_gen_val_a", "1D view: gen", unfolding_val_a.GetNrows(), -0.5, unfolding_val_a.GetNrows()-0.5 ) ;
      TH1F* h_1d_unfolded_ac_val_a = new TH1F( "h_1d_unfolded_ac_val_a", htitle, unfolding_ac_val_a.GetNrows(), -0.5, unfolding_ac_val_a.GetNrows()-0.5 ) ;
      TH1F* h_1d_gen_ac_val_a = new TH1F( "h_1d_gen_ac_val_a", "1D view: gen", unfolding_ac_val_a.GetNrows(), -0.5, unfolding_ac_val_a.GetNrows()-0.5 ) ;


      sprintf( htitle, "1D view: unfolded  %s", method_name_b ) ;
      TH1F* h_1d_unfolded_val_b = new TH1F( "h_1d_unfolded_val_b", htitle, unfolding_val_b.GetNrows(), -0.5, unfolding_val_b.GetNrows()-0.5 ) ;
      TH1F* h_1d_gen_val_b = new TH1F( "h_1d_gen_val_b", "1D view: gen", unfolding_val_b.GetNrows(), -0.5, unfolding_val_b.GetNrows()-0.5 ) ;
      TH1F* h_1d_unfolded_ac_val_b = new TH1F( "h_1d_unfolded_ac_val_b", htitle, unfolding_ac_val_b.GetNrows(), -0.5, unfolding_ac_val_b.GetNrows()-0.5 ) ;
      TH1F* h_1d_gen_ac_val_b = new TH1F( "h_1d_gen_ac_val_b", "1D view: gen", unfolding_ac_val_b.GetNrows(), -0.5, unfolding_ac_val_b.GetNrows()-0.5 ) ;




      for ( int i=0; i<unfolding_val_a.GetNrows(); i++ ) {

         h_1d_unfolded_val_a -> SetBinContent( i+1, unfolding_val_a[i] ) ;
         h_1d_unfolded_val_a -> SetBinError( i+1, unfolding_err_a[i] ) ;
         h_1d_gen_val_a -> SetBinContent( i+1, gen_val_a[i] ) ;

         h_1d_unfolded_val_b -> SetBinContent( i+1, unfolding_val_b[i] ) ;
         h_1d_unfolded_val_b -> SetBinError( i+1, unfolding_err_b[i] ) ;
         h_1d_gen_val_b -> SetBinContent( i+1, gen_val_b[i] ) ;

         h_1d_unfolded_ac_val_a -> SetBinContent( i+1, unfolding_ac_val_a[i] ) ;
         h_1d_unfolded_ac_val_a -> SetBinError( i+1, unfolding_ac_err_a[i] ) ;
         h_1d_gen_ac_val_a -> SetBinContent( i+1, gen_ac_val_a[i] ) ;

         h_1d_unfolded_ac_val_b -> SetBinContent( i+1, unfolding_ac_val_b[i] ) ;
         h_1d_unfolded_ac_val_b -> SetBinError( i+1, unfolding_ac_err_b[i] ) ;
         h_1d_gen_ac_val_b -> SetBinContent( i+1, gen_ac_val_b[i] ) ;

      }







      TH2F* h_unfold_cov_mat_trimmed_a = trim_unused_bins( h_unfold_cov_mat_a, rur_a ) ;
      h_unfold_cov_mat_trimmed_a -> SetName( "h_unfold_cov_mat_trimmed_a" ) ;

      TH2F* h_unfold_cor_mat_trimmed_a = trim_unused_bins( h_unfold_cor_mat_a, rur_a ) ;
      h_unfold_cor_mat_trimmed_a -> SetName( "h_unfold_cor_mat_trimmed_a" ) ;

      TH1F* h_global_correlation_coeff_trimmed_a = trim_unused_bins( h_global_correlation_coeff_a, rur_a ) ;
      h_global_correlation_coeff_trimmed_a -> SetName( "h_global_correlation_coeff_trimmed_a" ) ;

      TH1F* h_unfolding_result_err_trimmed_a = trim_unused_bins( h_unfolding_result_err_a, rur_a ) ;
      h_unfolding_result_err_trimmed_a -> SetName( "h_unfolding_result_err_trimmed_a" ) ;

      TH1F* h_1d_unfolded_val_trimmed_a = trim_unused_bins( h_1d_unfolded_val_a, rur_a ) ;
      h_1d_unfolded_val_trimmed_a -> SetName( "h_1d_unfolded_val_trimmed_a" ) ;

      TH1F* h_1d_gen_val_trimmed_a = trim_unused_bins( h_1d_gen_val_a, rur_a ) ;
      h_1d_gen_val_trimmed_a -> SetName( "h_1d_gen_val_trimmed_a" ) ;



      h_1d_gen_val_trimmed_a -> Scale( ( h_1d_unfolded_val_trimmed_a -> Integral() ) / ( h_1d_gen_val_trimmed_a -> Integral() ) ) ;

      TH1F* h_1d_unfolded_ac_val_trimmed_a = trim_unused_bins( h_1d_unfolded_ac_val_a, rur_a ) ;
      TH1F* h_1d_gen_ac_val_trimmed_a = trim_unused_bins( h_1d_gen_ac_val_a, rur_a ) ;
      h_1d_gen_ac_val_trimmed_a -> Scale( ( h_1d_unfolded_ac_val_trimmed_a -> Integral() ) / ( h_1d_gen_ac_val_trimmed_a -> Integral() ) ) ;




      TH2F* h_unfold_cov_mat_trimmed_b = trim_unused_bins( h_unfold_cov_mat_b, rur_b ) ;
      h_unfold_cov_mat_trimmed_b -> SetName( "h_unfold_cov_mat_trimmed_b" ) ;

      TH2F* h_unfold_cor_mat_trimmed_b = trim_unused_bins( h_unfold_cor_mat_b, rur_b ) ;
      h_unfold_cor_mat_trimmed_b -> SetName( "h_unfold_cor_mat_trimmed_b" ) ;

      TH1F* h_global_correlation_coeff_trimmed_b = trim_unused_bins( h_global_correlation_coeff_b, rur_b ) ;
      h_global_correlation_coeff_trimmed_b -> SetName( "h_global_correlation_coeff_trimmed_b" ) ;

      TH1F* h_unfolding_result_err_trimmed_b = trim_unused_bins( h_unfolding_result_err_b, rur_b ) ;
      h_unfolding_result_err_trimmed_b -> SetName( "h_unfolding_result_err_trimmed_b" ) ;

      TH1F* h_1d_unfolded_val_trimmed_b = trim_unused_bins( h_1d_unfolded_val_b, rur_b ) ;
      h_1d_unfolded_val_trimmed_b -> SetName( "h_1d_unfolded_val_trimmed_b" ) ;

      TH1F* h_1d_gen_val_trimmed_b = trim_unused_bins( h_1d_gen_val_b, rur_b ) ;
      h_1d_gen_val_trimmed_b -> SetName( "h_1d_gen_val_trimmed_b" ) ;



      h_1d_gen_val_trimmed_b -> Scale( ( h_1d_unfolded_val_trimmed_b -> Integral() ) / ( h_1d_gen_val_trimmed_b -> Integral() ) ) ;

      TH1F* h_1d_unfolded_ac_val_trimmed_b = trim_unused_bins( h_1d_unfolded_ac_val_b, rur_b ) ;
      TH1F* h_1d_gen_ac_val_trimmed_b = trim_unused_bins( h_1d_gen_ac_val_b, rur_b ) ;
      h_1d_gen_ac_val_trimmed_b -> Scale( ( h_1d_unfolded_ac_val_trimmed_b -> Integral() ) / ( h_1d_gen_ac_val_trimmed_b -> Integral() ) ) ;


      h_1d_unfolded_val_trimmed_a -> SetXTitle( "Global unfolded bin number") ;
      h_1d_unfolded_val_trimmed_b -> SetXTitle( "Global unfolded bin number") ;

      h_1d_unfolded_ac_val_trimmed_a -> SetXTitle( "Global unfolded bin number") ;
      h_1d_unfolded_ac_val_trimmed_b -> SetXTitle( "Global unfolded bin number") ;

      h_unfold_cov_mat_trimmed_a -> SetXTitle( "Global unfolded bin number") ;
      h_unfold_cov_mat_trimmed_a -> SetYTitle( "Global unfolded bin number") ;
      h_unfold_cov_mat_trimmed_b -> SetXTitle( "Global unfolded bin number") ;
      h_unfold_cov_mat_trimmed_b -> SetYTitle( "Global unfolded bin number") ;

      h_unfold_cor_mat_trimmed_a -> SetXTitle( "Global unfolded bin number") ;
      h_unfold_cor_mat_trimmed_a -> SetYTitle( "Global unfolded bin number") ;
      h_unfold_cor_mat_trimmed_b -> SetXTitle( "Global unfolded bin number") ;
      h_unfold_cor_mat_trimmed_b -> SetYTitle( "Global unfolded bin number") ;

      h_global_correlation_coeff_trimmed_a -> SetXTitle( "Global unfolded bin number") ;
      h_global_correlation_coeff_trimmed_b -> SetXTitle( "Global unfolded bin number") ;

      h_unfolding_result_err_trimmed_a -> SetXTitle( "Global unfolded bin number") ;
      h_unfolding_result_err_trimmed_b -> SetXTitle( "Global unfolded bin number") ;



      h_global_correlation_coeff_trimmed_a -> SetLineWidth(2) ;
      h_global_correlation_coeff_trimmed_b -> SetLineWidth(2) ;

      h_unfolding_result_err_trimmed_a -> SetLineWidth(2) ;
      h_unfolding_result_err_trimmed_b -> SetLineWidth(2) ;


      TH1F* h_unfolding_result_error_ratio = (TH1F*) h_unfolding_result_err_trimmed_a -> Clone( "h_unfolding_result_error_ratio" ) ;
      h_unfolding_result_error_ratio -> Divide( h_unfolding_result_err_trimmed_b ) ;
      sprintf( htitle, "Unfolding error ratio %s / %s", method_name_a, method_name_b ) ;
      h_unfolding_result_error_ratio -> SetTitle( htitle ) ;
      h_unfolding_result_error_ratio -> SetYTitle( htitle ) ;
      h_unfolding_result_error_ratio -> SetXTitle( "Global unfolded bin number") ;


      TExec* change_hist_palette = new TExec( "change_hist_palette", "Setup2DhistPalette();" );
      TExec* change_cor_palette = new TExec( "change_cor_palette", "SetupCorrelationPalette();" );


      printf("\n\n\n ========== Unfolding output histogram from method a, just before zero_unused_bins\n\n") ;
      print_th2_table( (TH2F*) hReco_a ) ;
      printf("\n\n\n ==========================================================\n\n") ;


      printf("\n\n Zeroing unused bins for a:\n") ;
      zero_unused_bins( hReco_a, rur_a ) ;
      printf("\n\n Zeroing unused bins for b:\n") ;
      zero_unused_bins( hReco_b, rur_b ) ;
      printf("\n\n") ;


      printf("\n\n\n ========== Unfolding output histogram from method a, just after zero_unused_bins\n\n") ;
      print_th2_table( (TH2F*) hReco_a ) ;
      printf("\n\n\n ==========================================================\n\n") ;










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


      TH1* h_1d_unfolded_val_trimmed_b_copy = (TH1*) h_1d_unfolded_val_trimmed_b->Clone( "h_1d_unfolded_val_trimmed_b_copy") ;
      h_1d_unfolded_val_trimmed_b_copy -> SetLineColor(2) ;

      can1 -> cd( ci++ ) ;
      h_1d_unfolded_val_trimmed_a -> DrawCopy() ;
      h_1d_unfolded_val_trimmed_b_copy -> DrawCopy("same") ;




      can1 -> Update() ;
      can1 -> Draw() ;
      can1 -> SaveAs("run_unfolding1-can1.pdf") ;
      can1 -> SaveAs("run_unfolding1_can1.C") ;
      gSystem -> ProcessEvents() ;








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
      draw_2d_slices( hReco_a, 0, htitle_a ) ;

      can2 -> cd( ci++ ) ;
      draw_2d_slices( hReco_b, 0, htitle_b ) ;



      can2 -> cd( ci++ ) ;
      draw_2d_slices( hReco_a, 1, htitle_a ) ;

      can2 -> cd( ci++ ) ;
      draw_2d_slices( hReco_b, 1, htitle_b ) ;

      can2 -> SaveAs("run_unfolding1-can2.pdf") ;
      can2 -> SaveAs("run_unfolding1_can2.C") ;

   //-----------

      gStyle -> SetPadRightMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;


      can3 -> cd() ;
      can3 -> Clear() ;
      can3 -> Divide(2,2) ;

      sprintf( htitle_a, "Unfolded, %s", method_name_a ) ;
      sprintf( htitle_b, "Unfolded, %s", method_name_b ) ;

      ci = 1 ;

      can3 -> cd( ci++ ) ;
      draw_2d_slices( hReco_ac_a, 0, htitle_a ) ;

      can3 -> cd( ci++ ) ;
      draw_2d_slices( hReco_ac_b, 0, htitle_b ) ;



      can3 -> cd( ci++ ) ;
      draw_2d_slices( hReco_ac_a, 1, htitle_a ) ;

      can3 -> cd( ci++ ) ;
      draw_2d_slices( hReco_ac_b, 1, htitle_b ) ;


      can3 -> SaveAs("run_unfolding1-can3.pdf") ;
      can3 -> SaveAs("run_unfolding1_can3.C") ;




// //-----------


      can4 -> cd() ;
      can4 -> Clear() ;
      can4 -> Divide(2,2) ;

      TH1F* h_1d_unfolded_over_gen_closure_a = (TH1F*) h_1d_unfolded_val_trimmed_a -> Clone( "h_1d_unfolded_over_gen_closure_a" ) ;
      sprintf( htitle, "Unfolded / gen, %s", method_a ) ;
      h_1d_unfolded_over_gen_closure_a -> SetTitle( htitle ) ;
      h_1d_unfolded_over_gen_closure_a -> Divide( h_1d_gen_val_trimmed_a ) ;

      h_1d_unfolded_over_gen_closure_a -> SetMaximum(1.2) ;
      h_1d_unfolded_over_gen_closure_a -> SetMinimum(0.8) ;


      TH1F* h_1d_unfolded_over_gen_closure_b = (TH1F*) h_1d_unfolded_val_trimmed_b -> Clone( "h_1d_unfolded_over_gen_closure_b" ) ;
      sprintf( htitle, "Unfolded / gen, %s", method_b ) ;
      h_1d_unfolded_over_gen_closure_b -> SetTitle( htitle ) ;
      h_1d_unfolded_over_gen_closure_b -> Divide( h_1d_gen_val_trimmed_b ) ;

      h_1d_unfolded_over_gen_closure_b -> SetMaximum(1.2) ;
      h_1d_unfolded_over_gen_closure_b -> SetMinimum(0.8) ;

      gStyle -> SetOptStat("emrou") ;

      sprintf( htitle, "Point pulls, %s", method_a ) ;
      TH1F* h_point_pulls_a = new TH1F( "h_point_pulls_a", htitle, 20, -5., 5. ) ;
      h_point_pulls_a -> SetFillColor(30) ;

      sprintf( htitle, "Point pulls, %s", method_b ) ;
      TH1F* h_point_pulls_b = new TH1F( "h_point_pulls_b", htitle, 20, -5., 5. ) ;
      h_point_pulls_b -> SetFillColor(30) ;

      for ( int bi=1; bi < h_1d_unfolded_over_gen_closure_a->GetNbinsX(); bi++ ) {
         float val = 0. ;
         float err = 1. ;
         float pull ;
         val = h_1d_unfolded_over_gen_closure_a -> GetBinContent( bi ) ;
         err = h_1d_unfolded_over_gen_closure_a -> GetBinError( bi ) ;
         if ( err > 0 ) pull = (val-1.) / err ;
         h_point_pulls_a -> Fill( pull ) ;
         val = h_1d_unfolded_over_gen_closure_b -> GetBinContent( bi ) ;
         err = h_1d_unfolded_over_gen_closure_b -> GetBinError( bi ) ;
         if ( err > 0 ) pull = (val-1.) / err ;
         h_point_pulls_b -> Fill( pull ) ;
      } // bi


      ci = 1 ;


      can4 -> cd( ci++ ) ;
      h_1d_unfolded_over_gen_closure_a -> Draw( "e0" ) ;
      gPad -> SetGridy(1) ;


      can4 -> cd( ci++ ) ;
      h_1d_unfolded_over_gen_closure_b -> Draw( "e0" ) ;
      gPad -> SetGridy(1) ;


      can4 -> cd( ci++ ) ;
      h_point_pulls_a -> Draw() ;

      can4 -> cd( ci++ ) ;
      h_point_pulls_b -> Draw() ;

      can4 -> Update() ; can4 -> Draw() ;

      can4 -> SaveAs("run_unfolding1-can4.pdf") ;
      can4 -> SaveAs("run_unfolding1_can4.C") ;

    //---------------


      can5 -> cd() ;
      can5 -> Clear() ;


      TH1* h_unfold_stat_err_ratio = (TH1*) hReco_a -> Clone( "h_unfold_stat_err_ratio" ) ;
      sprintf( htitle, "Unfolding stat error ratio, %s / %s", method_a, method_b ) ;
      h_unfold_stat_err_ratio -> SetTitle( htitle ) ;

      for ( int ci=1; ci <= hReco_a -> GetNcells(); ci++ ) {
         float err_a = hReco_a -> GetBinError( ci ) ;
         float err_b = hReco_b -> GetBinError( ci ) ;
         float err_ratio = 0. ;
         if ( err_b > 0 && err_a > 0 ) err_ratio = err_a / err_b ;
         h_unfold_stat_err_ratio -> SetBinContent( ci, err_ratio ) ;
      } // ci

      gStyle -> SetOptStat(0) ;

      h_unfold_stat_err_ratio -> SetMaximum(1.) ;

      h_unfold_stat_err_ratio -> DrawCopy("colz") ;
      change_hist_palette -> Draw() ;
      h_unfold_stat_err_ratio -> DrawCopy("colz same") ;

      gStyle->SetPaintTextFormat("5.3f") ;
      h_unfold_stat_err_ratio -> DrawCopy("text same") ;

      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;

      can5 -> Update() ; can5 -> Draw() ;


      can5 -> SaveAs("run_unfolding1-can5.pdf") ;
      can5 -> SaveAs("run_unfolding1_can5.C") ;



      printf("\n\n\n ========== Unfolding output histogram from method a, just before Write\n\n") ;
      print_th2_table( (TH2F*) hReco_a ) ;
      printf("\n\n\n ==========================================================\n\n") ;




    //---------------

      printf("\n\n\n") ;

    //------- Save outputs

      char outfname[1000] ;
      sprintf( outfname, "ru1-output-method%d.root", method_index ) ;
      TFile* tf_out = new TFile( outfname, "RECREATE" ) ;

      h_in_gen_vs_obs_a -> Write() ;
      hReco_a -> Write() ;
      h_1d_gen_val_trimmed_a -> Write() ;
      h_unfold_cor_mat_trimmed_a -> Write() ;

      h_in_gen_vs_obs_b -> Write() ;
      hReco_b -> Write() ;
      h_1d_gen_val_trimmed_b -> Write() ;
      h_1d_unfolded_val_trimmed_b -> Write() ;

      h_global_correlation_coeff_trimmed_a -> Write() ;
      h_global_correlation_coeff_trimmed_b -> Write() ;
      h_unfolding_result_err_trimmed_a -> Write() ;
      h_unfolding_result_err_trimmed_b -> Write() ;

      h_unfolding_result_error_ratio -> Write() ;

      h_1d_unfolded_val_trimmed_b_copy -> Write() ;
      h_1d_unfolded_val_trimmed_a -> Write() ;


      h_unfold_cor_mat_trimmed_b -> Write() ;

      hReco_ac_a -> Write() ;
      hReco_ac_b -> Write() ;


    //---------------

      unused_global_bins.clear() ;

      return 0 ;

   }










