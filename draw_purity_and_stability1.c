
#include "histio.c"

#include "utils.c"

   void draw_purity_and_stability1( const char* infile = "unfold-hists-h1-binning.root" ) {

      gStyle -> SetOptStat(0) ;

      gStyle -> SetPaintTextFormat("5.3f") ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;

      gDirectory -> ls() ;

    //
    // 1206.7007
    //
    // page 17, 1st paragraph of section 5.5
    // "The purity is defined as the fraction of events generated and reconstructed in a measurement bin
    //  from the total number of events reconstructed in the bin."  So denominator of purity is histogram
    //  of observed.

      TH2F* h_q2_vs_x_meas_binning_obs_esigma_sel = get_hist2d( "h_q2_vs_x_meas_binning_obs_esigma_sel" ) ;
      TH2F* h_q2_vs_x_meas_binning_obs_gen_same_esigma_sel = get_hist2d( "h_q2_vs_x_meas_binning_obs_gen_same_esigma_sel" ) ;

      TH2F* h_purity_esigma = (TH2F*) h_q2_vs_x_meas_binning_obs_gen_same_esigma_sel -> Clone( "h_purity_esigma" ) ;
      h_purity_esigma -> SetTitle( "Purity, eSigma" ) ;
      h_purity_esigma -> SetXTitle( "x" ) ;
      h_purity_esigma -> SetYTitle( "Q^{2} ,  GeV^{2}" ) ;

      h_purity_esigma -> Divide( h_q2_vs_x_meas_binning_obs_esigma_sel ) ;

      h_purity_esigma -> GetXaxis() -> SetLimits( 0.00158, 1 ) ;
      h_purity_esigma -> GetYaxis() -> SetLimits( 177.8, 77285.9 ) ;






      TH2F* h_q2_vs_x_meas_binning_obs_dnn_sel = get_hist2d( "h_q2_vs_x_meas_binning_obs_dnn_sel" ) ;
      TH2F* h_q2_vs_x_meas_binning_obs_gen_same_dnn_sel = get_hist2d( "h_q2_vs_x_meas_binning_obs_gen_same_dnn_sel" ) ;

      TH2F* h_purity_dnn = (TH2F*) h_q2_vs_x_meas_binning_obs_gen_same_dnn_sel -> Clone( "h_purity_dnn" ) ;
      h_purity_dnn -> SetTitle( "Purity, dnn" ) ;
      h_purity_dnn -> SetXTitle( "x" ) ;
      h_purity_dnn -> SetYTitle( "Q^{2} ,  GeV^{2}" ) ;

      h_purity_dnn -> Divide( h_q2_vs_x_meas_binning_obs_dnn_sel ) ;

      h_purity_dnn -> GetXaxis() -> SetLimits( 0.00158, 1 ) ;
      h_purity_dnn -> GetYaxis() -> SetLimits( 177.8, 77285.9 ) ;



    //
    // 1206.7007
    //
    // page 17, 1st paragraph of section 5.5
    // "The stability is the ratio of the number of events generated and reconstructed in a bin to the
    //  number of events generated in that bin."  So the denominator of stability is histogram of generated.

      TH2F* h_q2_vs_x_gen_esigma_sel = get_hist2d( "h_q2_vs_x_gen_esigma_sel" ) ;
      TH2F* h_q2_vs_x_gen_rec_same_esigma_sel = get_hist2d( "h_q2_vs_x_gen_rec_same_esigma_sel" ) ;

      TH2F* h_stability_esigma = (TH2F*) h_q2_vs_x_gen_rec_same_esigma_sel -> Clone( "h_stability_esigma" ) ;
      h_stability_esigma -> SetTitle( "Stability, eSigma" ) ;
      h_stability_esigma -> SetXTitle( "x" ) ;
      h_stability_esigma -> SetYTitle( "Q^{2} ,  GeV^{2}" ) ;

      h_stability_esigma -> Divide( h_q2_vs_x_gen_esigma_sel ) ;

      h_stability_esigma -> GetXaxis() -> SetLimits( 0.00158, 1 ) ;
      h_stability_esigma -> GetYaxis() -> SetLimits( 177.8, 77285.9 ) ;





      TH2F* h_q2_vs_x_gen_dnn_sel = get_hist2d( "h_q2_vs_x_gen_dnn_sel" ) ;
      TH2F* h_q2_vs_x_gen_rec_same_dnn_sel = get_hist2d( "h_q2_vs_x_gen_rec_same_dnn_sel" ) ;

      TH2F* h_stability_dnn = (TH2F*) h_q2_vs_x_gen_rec_same_dnn_sel -> Clone( "h_stability_dnn" ) ;
      h_stability_dnn -> SetTitle( "Stability, dnn" ) ;
      h_stability_dnn -> SetXTitle( "x" ) ;
      h_stability_dnn -> SetYTitle( "Q^{2} ,  GeV^{2}" ) ;

      h_stability_dnn -> Divide( h_q2_vs_x_gen_dnn_sel ) ;

      h_stability_dnn -> GetXaxis() -> SetLimits( 0.00158, 1 ) ;
      h_stability_dnn -> GetYaxis() -> SetLimits( 177.8, 77285.9 ) ;





      TH2F* h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN = (TH2F*) h_q2_vs_x_meas_binning_obs_esigma_sel -> Clone( "h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN" ) ;
      h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN -> SetTitle( "1/sqrt(N), eSigma" ) ;
      h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN -> SetXTitle( "obs x" ) ;
      h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN -> SetYTitle( "obs Q^{2} ,  GeV^{2}" ) ;

      for ( int ci=1; ci<=h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN->GetNcells(); ci++ ) {
         float n_val = h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN -> GetBinContent( ci ) ;
         float one_over_sqrtn = 1. ;
         if ( n_val > 0 ) one_over_sqrtn = 1. / sqrt( n_val ) ;
         h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN -> SetBinContent( ci, one_over_sqrtn ) ;
      }

      h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN -> SetMaximum(1.) ;

      h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN -> GetXaxis() -> SetLimits( 0.00158, 1 ) ;
      h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN -> GetYaxis() -> SetLimits( 177.8, 77285.9 ) ;





      TH2F* h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN = (TH2F*) h_q2_vs_x_meas_binning_obs_dnn_sel -> Clone( "h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN" ) ;
      h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN -> SetTitle( "1/sqrt(N), dnn" ) ;
      h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN -> SetXTitle( "obs x" ) ;
      h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN -> SetYTitle( "obs Q^{2} ,  GeV^{2}" ) ;

      for ( int ci=1; ci<=h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN->GetNcells(); ci++ ) {
         float n_val = h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN -> GetBinContent( ci ) ;
         float one_over_sqrtn = 1. ;
         if ( n_val > 0 ) one_over_sqrtn = 1. / sqrt( n_val ) ;
         h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN -> SetBinContent( ci, one_over_sqrtn ) ;
      }

      h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN -> SetMaximum(1.) ;

      h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN -> GetXaxis() -> SetLimits( 0.00158, 1 ) ;
      h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN -> GetYaxis() -> SetLimits( 177.8, 77285.9 ) ;



     //---

      TCanvas* can1 = (TCanvas*) gDirectory -> FindObject("can1") ;
      if ( can1 == 0x0 ) { can1 = new TCanvas( "can1", "", 50, 50, 2000, 600 ) ; }

      can1 -> Clear() ;
      can1 -> cd() ;

      h_purity_esigma -> SetMaximum(1.) ;
      h_purity_esigma -> Draw("colz") ;
      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;
      h_purity_esigma -> Draw("text same") ;

      can1 -> SaveAs( "plots/purity-esigma.png" ) ;



     //---

      TCanvas* can2 = (TCanvas*) gDirectory -> FindObject("can2") ;
      if ( can2 == 0x0 ) { can2 = new TCanvas( "can2", "", 50, 650, 2000, 600 ) ; }

      can2 -> Clear() ;
      can2 -> cd() ;

      h_stability_esigma -> SetMaximum(1.) ;
      h_stability_esigma -> Draw("colz") ;
      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;
      h_stability_esigma -> Draw("text same") ;

      can2 -> SaveAs( "plots/stability-esigma.png" ) ;

     //---

      TCanvas* can1b = (TCanvas*) gDirectory -> FindObject("can1b") ;
      if ( can1b == 0x0 ) { can1b = new TCanvas( "can1b", "", 1050, 50, 2000, 600 ) ; }

      can1b -> Clear() ;
      can1b -> cd() ;

      h_purity_dnn -> SetMaximum(1.) ;
      h_purity_dnn -> Draw("colz") ;
      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;
      h_purity_dnn -> Draw("text same") ;

      can1b -> SaveAs( "plots/purity-dnn.png" ) ;


     //---

      TCanvas* can2b = (TCanvas*) gDirectory -> FindObject("can2b") ;
      if ( can2b == 0x0 ) { can2b = new TCanvas( "can2b", "", 1050, 650, 2000, 600 ) ; }

      can2b -> Clear() ;
      can2b -> cd() ;

      h_stability_dnn -> SetMaximum(1.) ;
      h_stability_dnn -> Draw("colz") ;
      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;
      h_stability_dnn -> Draw("text same") ;

      can2b -> SaveAs( "plots/stability-dnn.png" ) ;


     //---

      TCanvas* can3 = (TCanvas*) gDirectory -> FindObject("can3") ;
      if ( can3 == 0x0 ) { can3 = new TCanvas( "can3", "", 1150, 150, 2000, 600 ) ; }

      can3 -> Clear() ;
      can3 -> cd() ;

      h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN -> SetMaximum(1.) ;
      h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN -> Draw("colz") ;
      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;
      h_q2_vs_x_meas_binning_obs_esigma_sel_1_over_sqrtN -> Draw("text same") ;

      can3 -> SaveAs( "plots/one-over-sqrtn-esigma.png" ) ;


     //---

      TCanvas* can4 = (TCanvas*) gDirectory -> FindObject("can4") ;
      if ( can4 == 0x0 ) { can4 = new TCanvas( "can4", "", 1150, 150, 2000, 600 ) ; }

      can4 -> Clear() ;
      can4 -> cd() ;

      h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN -> SetMaximum(1.) ;
      h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN -> Draw("colz") ;
      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;
      h_q2_vs_x_meas_binning_obs_dnn_sel_1_over_sqrtN -> Draw("text same") ;

      can4 -> SaveAs( "plots/one-over-sqrtn-dnn.png" ) ;



   }


