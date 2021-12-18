
#include "utils.c"

#include "histio.c"

   void make_fake_data_max_stats(
           bool do_nint = false,
           float scale_factor = 1.,
           int  seed = 12345,
           const char* input_hist_fname = "rapgap-for-q2-vs-y-gen012_obs024-0.05-obs-good.root",
           const char* output_hist_fname = "fake-data-max-stats.root"
        ) {

      gDirectory -> Delete( "h*" ) ;

      TRandom3 tran( seed ) ;

      TFile* tf_in = new TFile( input_hist_fname, "read" ) ;

      TFile* tf_out = new TFile( output_hist_fname, "recreate" ) ;


      TH2F* h_in ;
      TH2F* h_out ;



    //----

      h_in = fget_hist2d( "h_log10_q2_vs_log10_y_obs_dnn_sel", tf_in ) ;

      h_out = (TH2F*) h_in -> Clone( "h_data_log10_q2_vs_log10_y_obs_dnn" ) ;
      h_out -> Reset() ;

      for ( int xbi = 1; xbi <= h_in->GetNbinsX(); xbi ++ ) {
         for ( int ybi = 1; ybi <= h_in->GetNbinsY(); ybi ++ ) {
            float val = scale_factor * ( h_in -> GetBinContent( xbi, ybi ) ) ;
            if ( do_nint ) {
               h_out -> SetBinContent( xbi, ybi, TMath::Nint( val ) ) ;
               h_out -> SetBinError( xbi, ybi, sqrt(TMath::Nint( val )) ) ;
            } else {
               int set_val = tran.Poisson( val ) ;
               h_out -> SetBinContent( xbi, ybi, set_val ) ;
               h_out -> SetBinError( xbi, ybi, sqrt(set_val) ) ;
            }
         } // ybi
      } // xbi

      h_out -> Write() ;



    //----

      h_in = fget_hist2d( "h_log10_q2_vs_log10_y_obs_e_sel", tf_in ) ;

      h_out = (TH2F*) h_in -> Clone( "h_data_log10_q2_vs_log10_y_obs_e" ) ;
      h_out -> Reset() ;

      for ( int xbi = 1; xbi <= h_in->GetNbinsX(); xbi ++ ) {
         for ( int ybi = 1; ybi <= h_in->GetNbinsY(); ybi ++ ) {
            float val = scale_factor * ( h_in -> GetBinContent( xbi, ybi ) ) ;
            if ( do_nint ) {
               h_out -> SetBinContent( xbi, ybi, TMath::Nint( val ) ) ;
               h_out -> SetBinError( xbi, ybi, sqrt(TMath::Nint( val )) ) ;
            } else {
               int set_val = tran.Poisson( val ) ;
               h_out -> SetBinContent( xbi, ybi, set_val ) ;
               h_out -> SetBinError( xbi, ybi, sqrt(set_val) ) ;
            }
         } // ybi
      } // xbi

      h_out -> Write() ;



    //----

      h_in = fget_hist2d( "h_log10_q2_vs_log10_y_obs_isigma_sel", tf_in ) ;

      h_out = (TH2F*) h_in -> Clone( "h_data_log10_q2_vs_log10_y_obs_isigma" ) ;
      h_out -> Reset() ;

      for ( int xbi = 1; xbi <= h_in->GetNbinsX(); xbi ++ ) {
         for ( int ybi = 1; ybi <= h_in->GetNbinsY(); ybi ++ ) {
            float val = scale_factor * ( h_in -> GetBinContent( xbi, ybi ) ) ;
            if ( do_nint ) {
               h_out -> SetBinContent( xbi, ybi, TMath::Nint( val ) ) ;
               h_out -> SetBinError( xbi, ybi, sqrt(TMath::Nint( val )) ) ;
            } else {
               int set_val = tran.Poisson( val ) ;
               h_out -> SetBinContent( xbi, ybi, set_val ) ;
               h_out -> SetBinError( xbi, ybi, sqrt(set_val) ) ;
            }
         } // ybi
      } // xbi

      h_out -> Write() ;



    //----

      h_in = fget_hist2d( "h_log10_q2_vs_log10_y_obs_esigma_sel", tf_in ) ;

      h_out = (TH2F*) h_in -> Clone( "h_data_log10_q2_vs_log10_y_obs_esigma" ) ;
      h_out -> Reset() ;

      for ( int xbi = 1; xbi <= h_in->GetNbinsX(); xbi ++ ) {
         for ( int ybi = 1; ybi <= h_in->GetNbinsY(); ybi ++ ) {
            float val = scale_factor * ( h_in -> GetBinContent( xbi, ybi ) ) ;
            if ( do_nint ) {
               h_out -> SetBinContent( xbi, ybi, TMath::Nint( val ) ) ;
               h_out -> SetBinError( xbi, ybi, sqrt(TMath::Nint( val )) ) ;
            } else {
               int set_val = tran.Poisson( val ) ;
               h_out -> SetBinContent( xbi, ybi, set_val ) ;
               h_out -> SetBinError( xbi, ybi, sqrt(set_val) ) ;
            }
         } // ybi
      } // xbi

      h_out -> Write() ;



    //----

      h_in = fget_hist2d( "h_log10_q2_vs_log10_y_obs_da_sel", tf_in ) ;

      h_out = (TH2F*) h_in -> Clone( "h_data_log10_q2_vs_log10_y_obs_da" ) ;
      h_out -> Reset() ;

      for ( int xbi = 1; xbi <= h_in->GetNbinsX(); xbi ++ ) {
         for ( int ybi = 1; ybi <= h_in->GetNbinsY(); ybi ++ ) {
            float val = scale_factor * ( h_in -> GetBinContent( xbi, ybi ) ) ;
            if ( do_nint ) {
               h_out -> SetBinContent( xbi, ybi, TMath::Nint( val ) ) ;
               h_out -> SetBinError( xbi, ybi, sqrt(TMath::Nint( val )) ) ;
            } else {
               int set_val = tran.Poisson( val ) ;
               h_out -> SetBinContent( xbi, ybi, set_val ) ;
               h_out -> SetBinError( xbi, ybi, sqrt(set_val) ) ;
            }
         } // ybi
      } // xbi

      h_out -> Write() ;



    //----


      h_out -> Write() ;

      tf_out -> Close() ;

      printf("\n\n Created %s\n\n", output_hist_fname ) ;


   }


