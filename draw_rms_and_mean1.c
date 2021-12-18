
#include "histio.c"

#include "utils.c"

   void draw_rms_and_mean1( float reso_max = 0.30,  const char* infile_esigma = "x_reso_hists-esigma.root", const char* infile_dnn = "x_reso_hists-dnn.root" ) {

      gStyle -> SetOptStat(0) ;

      gStyle -> SetPaintTextFormat("5.3f") ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile_esigma, "esigma", "h_q2*" ) ;
      loadHist( infile_dnn, "dnn", "h_q2*" ) ;

      gDirectory -> ls() ;



      TH2F* h_xreso_esigma = get_hist2d( "h_q2_vs_x_obs_binning__x_reso_rms_esigma" ) ;
      h_xreso_esigma -> SetTitle( "x meas / gen, RMS, eSigma" ) ;
      h_xreso_esigma -> SetXTitle( "meas x" ) ;
      h_xreso_esigma -> SetYTitle( "meas Q^{2} ,  GeV^{2}" ) ;

      h_xreso_esigma -> SetMaximum( 0.30 ) ;



      TH2F* h_xreso_dnn = get_hist2d( "h_q2_vs_x_obs_binning__x_reso_rms_dnn" ) ;
      h_xreso_dnn -> SetTitle( "x meas / gen, RMS, dnn" ) ;
      h_xreso_dnn -> SetXTitle( "meas x" ) ;
      h_xreso_dnn -> SetYTitle( "meas Q^{2} ,  GeV^{2}" ) ;

      h_xreso_dnn -> SetMaximum( 0.30 ) ;



      TH2F* h_xmean_esigma = get_hist2d( "h_q2_vs_x_obs_binning__x_reso_mean_esigma" ) ;
      h_xmean_esigma -> SetTitle( "x meas / gen, mean, eSigma" ) ;
      h_xmean_esigma -> SetXTitle( "meas x" ) ;
      h_xmean_esigma -> SetYTitle( "meas Q^{2} ,  GeV^{2}" ) ;

      h_xmean_esigma -> SetMinimum( 0.50 ) ;
      h_xmean_esigma -> SetMaximum( 1.50 ) ;


      TH2F* h_xmean_dnn = get_hist2d( "h_q2_vs_x_obs_binning__x_reso_mean_dnn" ) ;
      h_xmean_dnn -> SetTitle( "x meas / gen, mean, dnn" ) ;
      h_xmean_dnn -> SetXTitle( "meas x" ) ;
      h_xmean_dnn -> SetYTitle( "meas Q^{2} ,  GeV^{2}" ) ;

      h_xmean_dnn -> SetMinimum( 0.50 ) ;
      h_xmean_dnn -> SetMaximum( 1.50 ) ;








     //---

      TCanvas* can1 = (TCanvas*) gDirectory -> FindObject("can1") ;
      if ( can1 == 0x0 ) { can1 = new TCanvas( "can1", "", 50, 50, 1000, 600 ) ; }

      can1 -> Clear() ;
      can1 -> cd() ;

      h_xreso_esigma -> Draw("colz") ;
      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;
      h_xreso_esigma -> Draw("text same") ;

      can1 -> SaveAs( "plots/x-reso-rms-esigma.png" ) ;



     //---

      TCanvas* can2 = (TCanvas*) gDirectory -> FindObject("can2") ;
      if ( can2 == 0x0 ) { can2 = new TCanvas( "can2", "", 50, 650, 1000, 600 ) ; }

      can2 -> Clear() ;
      can2 -> cd() ;

      h_xmean_esigma -> Draw("colz") ;
      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;
      h_xmean_esigma -> Draw("text same") ;

      can2 -> SaveAs( "plots/x-reso-mean-esigma.png" ) ;



     //---

      TCanvas* can1b = (TCanvas*) gDirectory -> FindObject("can1b") ;
      if ( can1b == 0x0 ) { can1b = new TCanvas( "can1b", "", 1050, 50, 1000, 600 ) ; }

      can1b -> Clear() ;
      can1b -> cd() ;

      h_xreso_dnn -> Draw("colz") ;
      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;
      h_xreso_dnn -> Draw("text same") ;

      can1b -> SaveAs( "plots/x-reso-rms-dnn.png" ) ;


     //---

      TCanvas* can2b = (TCanvas*) gDirectory -> FindObject("can2b") ;
      if ( can2b == 0x0 ) { can2b = new TCanvas( "can2b", "", 1050, 650, 1000, 600 ) ; }

      can2b -> Clear() ;
      can2b -> cd() ;

      h_xmean_dnn -> Draw("colz") ;
      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;
      h_xmean_dnn -> Draw("text same") ;

      can2b -> SaveAs( "plots/x-reso-mean-dnn.png" ) ;






   }


