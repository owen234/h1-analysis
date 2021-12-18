
   TH2F* calc_reduced_xsec_from_q2_vs_x( TH2F* hp ) {

       float beam_e_e = 27.6 ;
       float beam_p_e = 920.0 ;

       float lumi_ipb = 136. ; // same as in Miguel's jets Xsec paper (desy21-130.pdf).
       float alpha_val = 1./137. ;

       float s_val = 4. * beam_e_e * beam_p_e ;

       float hbar_c_squared = 0.389 * 1e9 ; // see PDG constants table

       if ( hp == 0x0 ) { printf("\n\n *** calc_reduced_xsec_from_q2_vs_x : null pointer.\n\n") ; gSystem -> Exit( -1 ) ; }

       char hname[1000] ;
       sprintf( hname, "%s_reduced_xsec", hp -> GetName() ) ;

       printf("\n\n calc_reduced_xsec_from_q2_vs_x : creating %s\n\n", hname ) ;

       TH2F* hp_rxsec = (TH2F*) hp -> Clone( hname ) ;


       hp_rxsec -> Reset() ;

       for ( int xbi=1; xbi <= hp -> GetNbinsX(); xbi ++ ) {
          float x_bc_val = hp -> GetXaxis() -> GetBinCenter( xbi ) ;
          float bin_dx = hp -> GetXaxis() -> GetBinLowEdge( xbi+1 ) - hp -> GetXaxis() -> GetBinLowEdge( xbi ) ;
          printf("   x bin %2d :  val = %7.4f, dx = %7.4f\n", xbi, x_bc_val, bin_dx ) ;
       }
       for ( int q2bi=1; q2bi <= hp -> GetNbinsY(); q2bi ++ ) {
          float q2_bc_val = hp -> GetYaxis() -> GetBinCenter( q2bi ) ;
          float bin_dq2 = hp -> GetYaxis() -> GetBinLowEdge( q2bi+1 ) - hp -> GetYaxis() -> GetBinLowEdge( q2bi ) ;
          printf("       Q2 bin %2d :  val = %7.2f, dQ2 = %7.2f\n", q2bi, q2_bc_val, bin_dq2 ) ;
       }



       for ( int xbi=1; xbi <= hp -> GetNbinsX(); xbi ++ ) {

          float x_bc_val = hp -> GetXaxis() -> GetBinCenter( xbi ) ;
          float bin_dx = hp -> GetXaxis() -> GetBinLowEdge( xbi+1 ) - hp -> GetXaxis() -> GetBinLowEdge( xbi ) ;
          ///printf("   x bin %2d :  val = %7.4f, dx = %7.4f\n", xbi, x_bc_val, bin_dx ) ;

          for ( int q2bi=1; q2bi <= hp -> GetNbinsY(); q2bi ++ ) {

             float q2_bc_val = hp -> GetYaxis() -> GetBinCenter( q2bi ) ;
             float bin_dq2 = hp -> GetYaxis() -> GetBinLowEdge( q2bi+1 ) - hp -> GetYaxis() -> GetBinLowEdge( q2bi ) ;
             ///printf("       Q2 bin %2d :  val = %7.2f, dQ2 = %7.2f\n", q2bi, q2_bc_val, bin_dq2 ) ;

             float y_val = q2_bc_val / ( x_bc_val * s_val ) ;

             float Yplus_val = 1. + (1. - y_val) * (1. - y_val) ;

             float rc_sf = ( (q2_bc_val * q2_bc_val * x_bc_val) / (Yplus_val * 2. * 3.14159265 * alpha_val * alpha_val * lumi_ipb) ) * ( 1. / ( bin_dx * bin_dq2 ) ) * (1./hbar_c_squared) ;


             float hist_bin_val = hp -> GetBinContent( xbi, q2bi ) ;
             float hist_bin_err = hp -> GetBinError( xbi, q2bi ) ;

             printf("  %3d, %3d  :  Q2 = %7.1f, x = %6.4f  :  hist_bin_val = %9.2f y_val = %9.5f Yplus = %6.4f  rc_sf = %g\n", q2bi, xbi, q2_bc_val, x_bc_val, hist_bin_val, y_val, Yplus_val, rc_sf ) ;

             hp_rxsec -> SetBinContent( xbi, q2bi, rc_sf * hist_bin_val ) ;
             hp_rxsec -> SetBinError( xbi, q2bi, rc_sf * hist_bin_err ) ;

          } // q2bi

       } // xbi

       return hp_rxsec ;

   } // calc_reduced_xsec_from_q2_vs_x



