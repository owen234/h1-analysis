

   void draw_2d_slice_plots( TH1* hp, TH1* hp2=0x0, bool do_logx=true, bool do_logy = false, const char* htitle = "", const char* can_name = "can_2d_slice_plots" ) {



      printf("\n\n draw_2d_slice_plots:  hp = %p,  hp2 = %p\n\n", hp, hp2) ;  fflush(stdout) ;

      printf("\n\n At beginning of draw_2d_slice_plots for %s.\n\n", hp->GetName() ) ; fflush(stdout) ;


      gStyle -> SetPadRightMargin(0.01) ;
      gStyle -> SetPadLeftMargin(0.17) ;
      gStyle -> SetPadTopMargin(0.05) ;

      char hname[100] ;

      int nbx = hp -> GetNbinsX() ;
      int nby = hp -> GetNbinsY() ;

      int nbx2(0) ;
      if ( hp2 != 0x0 ) nbx2 = hp2 -> GetNbinsX() ;

      printf(" nbx = %d  nbx2 = %d\n", nbx, nbx2 ) ;

      int first_xbin = 1 ;
      int last_xbin = nbx ;

      int first_xbin2 = 1 ;
      int last_xbin2 = nbx2 ;

      int first_ybin = 3 ;
      int last_ybin = nby-1 ;

      int nbins_slice = last_xbin - first_xbin + 1 ;
      int nbins2_slice = last_xbin2 - first_xbin2 + 1 ;


      float hist_max = hp -> GetMaximum() ;
      printf("\n\n Hist max : %9.1f\n\n", hist_max ) ;


      gStyle -> SetLegendTextSize(0.035) ;
      TLegend* legend = new TLegend( 0.20, 0.63, 0.80, 0.87 ) ;

      TCanvas* can = (TCanvas*) gDirectory -> Get( can_name ) ;
      if ( can == 0x0 ) {
         printf("\n\n Creating canvas %s\n\n", can_name ) ;
         can = new TCanvas( can_name, "", 50, 50, 1000, 1300 ) ;
      }
      can -> cd() ;
      can -> Clear() ;
      can -> Divide(4, 4) ;

      TText* tt_label = new TText() ;
      tt_label -> SetTextSize( 0.070 ) ;
      char label_text[1000] ;

      gStyle -> SetOptStat(0) ;



      int cpi = 1 ;

      for ( int ybi = first_ybin; ybi <= last_ybin; ybi ++ ) {

         double x_vals[50] ;
         double x_errs[50] ;
         double rxsec_vals[50] ;
         double rxsec_errs[50] ;

         double x2_vals[50] ;
         double x2_errs[50] ;
         double rxsec2_vals[50] ;
         double rxsec2_errs[50] ;

         int ngp(0) ;
         int ngp2(0) ;


         can -> cd( cpi ) ;

         float q2_val = hp -> GetYaxis() -> GetBinCenter( ybi ) ;

         sprintf( hname, "%s_yb%02d", hp -> GetName(), ybi ) ;
         printf("  Making %s   Q2 = %.0f\n", hname, q2_val ) ;

         TH1F* h1dslice = new TH1F( hname, hname, nbins_slice, hp -> GetXaxis() -> GetXbins() -> GetArray() ) ;
         sprintf( hname, "%s_yb%02d_2", hp -> GetName(), ybi ) ;
         TH1F* h1dslice2 = new TH1F( hname, hname, nbins_slice, hp -> GetXaxis() -> GetXbins() -> GetArray() ) ;

         if ( nbx == nbx2 ) {

            int gpai = 0 ;

            for ( int xbi = first_xbin; xbi <= last_xbin; xbi ++ ) {
               float xaxis_val = hp -> GetXaxis() -> GetBinCenter( xbi ) ;
               int slice_bin = h1dslice -> FindBin( xaxis_val ) ;
               h1dslice -> SetBinContent( slice_bin, hp -> GetBinContent( xbi, ybi ) ) ;
               h1dslice -> SetBinError( slice_bin, hp -> GetBinError( xbi, ybi ) ) ;
               if ( hp -> GetBinContent( xbi, ybi ) > 0 ) {
                  x_vals[gpai] = xaxis_val ;
                  x_errs[gpai] = 0.5 * (hp -> GetXaxis() -> GetBinWidth( xbi ) ) ;
                  x2_vals[gpai] = xaxis_val ;
                  x2_errs[gpai] = 0.5 * (hp -> GetXaxis() -> GetBinWidth( xbi ) ) ;
                  rxsec_vals[gpai] = hp -> GetBinContent( xbi, ybi ) ;
                  rxsec_errs[gpai] = hp -> GetBinError( xbi, ybi ) ;
                  if ( hp2 != 0x0 ) {
                     rxsec2_vals[gpai] = hp2 -> GetBinContent( xbi, ybi ) ;
                     rxsec2_errs[gpai] = hp2 -> GetBinError( xbi, ybi ) ;
                  }
                  gpai ++ ;
               }
               if ( hp2 != 0x0 ) {
                  h1dslice2 -> SetBinContent( slice_bin, hp2 -> GetBinContent( xbi, ybi ) ) ;
                  h1dslice2 -> SetBinError( slice_bin, hp2 -> GetBinError( xbi, ybi ) ) ;
                  rxsec2_vals[gpai] = hp2 -> GetBinContent( xbi, ybi ) ;
                  rxsec2_errs[gpai] = hp2 -> GetBinError( xbi, ybi ) ;
               }
               printf("  xbi %3d, x val %9.5f, bin %2d : %9.3f +/- %5.3f |  ", xbi, xaxis_val, slice_bin, hp -> GetBinContent( xbi, ybi ), hp -> GetBinError( xbi, ybi ) ) ;
               if ( hp2 != 0x0 ) {
                  float err_ratio = 0. ;
                  float err1 = hp -> GetBinError( xbi, ybi ) ;
                  float err2 = hp2 -> GetBinError( xbi, ybi ) ;
                  float val_ratio = 0. ;
                  float val1 = hp -> GetBinContent( xbi, ybi ) ;
                  float val2 = hp2 -> GetBinContent( xbi, ybi ) ;
                  if ( val1 > 0 && val2 > 0 ) val_ratio = val2 / val1 ;
                  printf("  %9.3f +/- %5.3f  |  val ratio:  %6.3f  err ratio:  %6.3f", hp2 -> GetBinContent( xbi, ybi ), hp2 -> GetBinError( xbi, ybi ), val_ratio, err_ratio ) ;
               }
               printf("\n") ;
            } // xbi
            printf("\n") ;

            ngp = gpai ;
            ngp2 = gpai ;

         } else {

            int gpai = 0 ;

            for ( int xbi = first_xbin; xbi <= last_xbin; xbi ++ ) {
               float xaxis_val = hp -> GetXaxis() -> GetBinCenter( xbi ) ;
               int slice_bin = h1dslice -> FindBin( xaxis_val ) ;
               h1dslice -> SetBinContent( slice_bin, hp -> GetBinContent( xbi, ybi ) ) ;
               h1dslice -> SetBinError( slice_bin, hp -> GetBinError( xbi, ybi ) ) ;
               if ( hp -> GetBinContent( xbi, ybi ) > 0 ) {
                  x_vals[gpai] = xaxis_val ;
                  x_errs[gpai] = 0.5 * (hp -> GetXaxis() -> GetBinWidth( xbi ) ) ;
                  rxsec_vals[gpai] = hp -> GetBinContent( xbi, ybi ) ;
                  rxsec_errs[gpai] = hp -> GetBinError( xbi, ybi ) ;
                  gpai ++ ;
               }
               printf(" h1: xbi %3d, x val %9.5f, bin %2d : %9.3f +/- %5.3f |  \n", xbi, xaxis_val, slice_bin, hp -> GetBinContent( xbi, ybi ), hp -> GetBinError( xbi, ybi ) ) ;
            } // xbi
            printf("\n") ;
            ngp = gpai ;

            gpai = 0 ;
            for ( int xbi = first_xbin2; xbi <= last_xbin2; xbi ++ ) {
               float xaxis_val = hp2 -> GetXaxis() -> GetBinCenter( xbi ) ;
               int slice_bin = h1dslice2 -> FindBin( xaxis_val ) ;
               h1dslice2 -> SetBinContent( slice_bin, hp2 -> GetBinContent( xbi, ybi ) ) ;
               h1dslice2 -> SetBinError( slice_bin, hp2 -> GetBinError( xbi, ybi ) ) ;
               if ( hp2 -> GetBinContent( xbi, ybi ) > 0 ) {
                  x2_vals[gpai] = xaxis_val ;
                  x2_errs[gpai] = 0.5 * (hp2 -> GetXaxis() -> GetBinWidth( xbi ) ) ;
                  rxsec2_vals[gpai] = hp2 -> GetBinContent( xbi, ybi ) ;
                  rxsec2_errs[gpai] = hp2 -> GetBinError( xbi, ybi ) ;
                  gpai ++ ;
               }
               printf(" h2: xbi %3d, x val %9.5f, bin %2d : %9.3f +/- %5.3f |  \n", xbi, xaxis_val, slice_bin, hp2 -> GetBinContent( xbi, ybi ), hp2 -> GetBinError( xbi, ybi ) ) ;
            } // xbi
            printf("\n") ;
            ngp2 = gpai ;

         }



         //////h1dslice -> SetLineColor( 11 + ybi ) ;
         h1dslice -> SetLineColor( 1 ) ;
         h1dslice -> SetLineWidth( 2 ) ;
         h1dslice -> SetYTitle( "Reduced Xsec" ) ;
         h1dslice -> SetTitleSize( 0.08, "y" ) ;
         h1dslice -> SetTitleOffset( 1.0, "y" ) ;
         h1dslice -> SetXTitle( "x   " ) ;
         h1dslice -> SetTitleSize( 0.06, "x" ) ;
         h1dslice -> SetTitleOffset( 0.8, "x" ) ;
         h1dslice -> SetMarkerStyle(0) ;
         h1dslice -> SetTitle( htitle ) ;
         h1dslice -> SetLabelSize( 0.070, "x" ) ;
         h1dslice -> SetLabelSize( 0.070, "y" ) ;
         h1dslice -> SetLabelOffset( -0.020, "x" ) ;
         h1dslice -> SetMarkerStyle(25) ;
         h1dslice -> SetMarkerSize(0.5) ;


         h1dslice2 -> SetLineColor( 2 ) ;
         h1dslice2 -> SetLineWidth( 2 ) ;
         h1dslice2 -> SetXTitle( hp -> GetXaxis() -> GetTitle() ) ;
         h1dslice2 -> SetYTitle( "Unfolded events" ) ;
         h1dslice2 -> SetMarkerStyle(0) ;
         h1dslice2 -> SetTitle( htitle ) ;
         h1dslice2 -> SetTitleOffset( 1.4, "y" ) ;
         h1dslice2 -> SetMarkerStyle(20) ;
         h1dslice2 -> SetMarkerSize(0.5) ;
         h1dslice2 -> SetMarkerColor(2) ;


            if ( do_logy ) {
               h1dslice -> SetMaximum( 340.2 * hist_max ) ;
               h1dslice -> SetMinimum( 1. ) ;
            } else {
               if ( do_logx ) {
                  h1dslice -> SetMaximum( 1.5 ) ;
               } else {
                  h1dslice -> SetMaximum( 0.5 ) ;
               }
            }
            ////////////h1dslice -> DrawCopy("p") ;
            h1dslice -> DrawCopy("axis") ;
            TGraphErrors* tge = new TGraphErrors( ngp, x_vals, rxsec_vals, x_errs, rxsec_errs ) ;
            tge -> SetMarkerStyle(25) ;
            tge -> SetMarkerSize(0.5) ;
            tge -> SetLineWidth(2) ;
            tge -> Draw("samepl") ;

            ////////h1dslice -> DrawCopy( "hist l same" ) ;
            if ( hp2 != 0x0 ) {
               //////h1dslice2 -> DrawCopy( "same" ) ;
               //////h1dslice2 -> DrawCopy( "hist l same" ) ;
               TGraphErrors* tge2 = new TGraphErrors( ngp2, x2_vals, rxsec2_vals, x2_errs, rxsec2_errs ) ;
               tge2 -> SetMarkerStyle(20) ;
               tge2 -> SetMarkerSize(0.5) ;
               tge2 -> SetLineColor(2) ;
               tge2 -> SetMarkerColor(2) ;
               tge2 -> SetLineWidth(2) ;
               tge2 -> Draw("samepl") ;
            }
            if ( do_logy ) { gPad -> SetLogy(1) ; }
         if ( do_logx ) { gPad -> SetLogx(1) ; }

///      char label[100] ;
///      float bin_log10q2min = hp -> GetYaxis() -> GetBinLowEdge( ybi ) ;
///      float bin_log10q2max = hp -> GetYaxis() -> GetBinLowEdge( ybi+1 ) ;
///      sprintf( label, "bin %2d : Q2 range [%4.0f, %4.0f]", ybi, pow(10.,bin_log10q2min), pow(10,bin_log10q2max)  ) ;
///      legend -> AddEntry( h1dslice, label ) ;

         sprintf( label_text, "Q2 = %.0f GeV2", q2_val ) ;
         tt_label -> DrawTextNDC( 0.25, 0.85, label_text ) ;

         cpi ++ ;

      } // ybi

      //////////legend -> Draw() ;

      printf("\n\n At end of draw_2d_slices for %s.\n\n", hp->GetName() ) ; fflush(stdout) ;



   }



