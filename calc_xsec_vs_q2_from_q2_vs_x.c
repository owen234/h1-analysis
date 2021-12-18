

   TH1* calc_xsec_vs_q2_from_q2_vs_x( TH2F* hp ) {

      float lumi_val = 136. ;

      if ( hp == 0x0 ) { printf("\n\n *** calc_xsec_vs_q2_from_q2_vs_x : null pointer.\n\n") ; gSystem -> Exit(-1) ; }

      char hname[1000] ;
      sprintf( hname, "%s_projy", hp -> GetName() ) ;
      TH1* h_evts_vs_q2 = (TH1*) hp -> ProjectionY( hname ) ;

      char htitle[1000] ;
      sprintf( htitle, "%s, projection on y axis", hp -> GetTitle() ) ;
      h_evts_vs_q2 -> SetTitle( htitle ) ;

      h_evts_vs_q2 -> Draw() ;
      gPad -> SetLogy(1) ;
      gPad -> SetLogx(1) ;


      sprintf( hname, "%s_xsec_vs_q2", hp -> GetName() ) ;
      TH1* h_xsec_vs_q2 = (TH1*) hp -> ProjectionY( hname ) ;
      sprintf( htitle, "%s, Cross section vs q2", hp -> GetTitle() ) ;
      h_xsec_vs_q2 -> SetTitle( htitle ) ;

      for ( int bi=1; bi<= h_xsec_vs_q2->GetNbinsX(); bi++ ) {

         float bin_width = h_xsec_vs_q2->GetXaxis() -> GetBinLowEdge(bi+1) - h_xsec_vs_q2->GetXaxis() -> GetBinLowEdge(bi) ;

         float nevts_val = h_evts_vs_q2 -> GetBinContent( bi ) ;
         float nevts_err = h_evts_vs_q2 -> GetBinError( bi ) ;

         float xsec_val = nevts_val / ( lumi_val * bin_width ) ;
         float xsec_err = nevts_err / ( lumi_val * bin_width ) ;

         h_xsec_vs_q2 -> SetBinContent( bi , xsec_val ) ;
         h_xsec_vs_q2 -> SetBinError( bi , xsec_err ) ;

      }

      h_xsec_vs_q2 -> Draw() ;

      return 0x0 ;


   }



