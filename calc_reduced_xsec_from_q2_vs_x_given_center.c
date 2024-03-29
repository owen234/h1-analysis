#ifndef calc_reduced_xsec_from_q2_vs_x_given_center_c
#define calc_reduced_xsec_from_q2_vs_x_given_center_c

   TH2F* calc_reduced_xsec_from_q2_vs_x_given_center( TH2F* hp, TH2F* hp_x_vals, TH2F* hp_q2_vals  ) {

       float beam_e_e = 27.6 ;
       float beam_p_e = 920.0 ;

       ///float lumi_ipb = 136. ; // same as in Miguel's jets Xsec paper (desy21-130.pdf).
       float lumi_ipb = 140. ;
       float alpha_val = 1./137. ;

       float s_val = 4. * beam_e_e * beam_p_e ;

       float hbar_c_squared = 0.389 * 1e9 ; // see PDG constants table

       if ( hp == 0x0 ) { printf("\n\n *** calc_reduced_xsec_from_q2_vs_x_given_center : null pointer.\n\n") ; gSystem -> Exit( -1 ) ; }
       if ( hp_x_vals == 0x0 ) { printf("\n\n *** calc_reduced_xsec_from_q2_vs_x_given_center : null pointer.\n\n") ; gSystem -> Exit( -1 ) ; }
       if ( hp_q2_vals == 0x0 ) { printf("\n\n *** calc_reduced_xsec_from_q2_vs_x_given_center : null pointer.\n\n") ; gSystem -> Exit( -1 ) ; }

       char hname[1000] ;
       sprintf( hname, "%s_reduced_xsec", hp -> GetName() ) ;

       printf("\n\n calc_reduced_xsec_from_q2_vs_x_given_center : creating %s\n\n", hname ) ;

       TH2F* hp_rxsec = (TH2F*) hp -> Clone( hname ) ;

       TH2F* hp_rcsf = (TH2F*) hp -> Clone( "h_rcsf" ) ;

       float bc_val_x[100] ;
       float bc_val_q2[100] ;

       hp_rxsec -> Reset() ;
       hp_rcsf -> Reset() ;

       for ( int xbi=1; xbi <= hp -> GetNbinsX(); xbi ++ ) {
          float x_given_bc_val = 0. ;
          for ( int q2bi=1; q2bi <= hp -> GetNbinsY(); q2bi++ ) {
             float val = hp_x_vals -> GetBinContent( xbi, q2bi ) ;
             if ( val > 0 ) { x_given_bc_val = val ; break ; }
          }
          float x_literal_bc_val = hp -> GetXaxis() -> GetBinCenter( xbi ) ;
          if ( x_given_bc_val > 0 ) {
             bc_val_x[xbi] = x_given_bc_val ;
          } else {
             bc_val_x[xbi] = x_literal_bc_val ;
          }
          float bin_dx = hp -> GetXaxis() -> GetBinLowEdge( xbi+1 ) - hp -> GetXaxis() -> GetBinLowEdge( xbi ) ;
          printf("   x bin %2d :  literal val = %7.4f, given val = %7.4f, dx = %7.4f\n", xbi, x_literal_bc_val, x_given_bc_val, bin_dx ) ;
       }
       for ( int q2bi=1; q2bi <= hp -> GetNbinsY(); q2bi ++ ) {
          float q2_given_bc_val = 0. ;
          for ( int xbi=1; xbi <= hp -> GetNbinsX(); xbi ++ ) {
             float val = hp_q2_vals -> GetBinContent( xbi, q2bi ) ;
             if ( val > 0 ) { q2_given_bc_val = val ; break ; }
          }
          float q2_literal_bc_val = hp -> GetYaxis() -> GetBinCenter( q2bi ) ;
          if ( q2_given_bc_val > 0 ) {
             bc_val_q2[q2bi] = q2_given_bc_val ;
          } else {
             bc_val_q2[q2bi] = q2_literal_bc_val ;
          }
          float bin_dq2 = hp -> GetYaxis() -> GetBinLowEdge( q2bi+1 ) - hp -> GetYaxis() -> GetBinLowEdge( q2bi ) ;
          printf("       Q2 bin %2d :  literal val = %7.2f, given val = %7.2f, dQ2 = %7.2f\n", q2bi, q2_literal_bc_val, q2_given_bc_val, bin_dq2 ) ;
       }


          for ( int q2bi=1; q2bi <= hp -> GetNbinsY(); q2bi ++ ) {

             float q2_bc_val = bc_val_q2[q2bi] ;
             float bin_dq2 = hp -> GetYaxis() -> GetBinLowEdge( q2bi+1 ) - hp -> GetYaxis() -> GetBinLowEdge( q2bi ) ;
             ///printf("       Q2 bin %2d :  val = %7.2f, dQ2 = %7.2f\n", q2bi, q2_bc_val, bin_dq2 ) ;

             printf("\n") ;


       for ( int xbi=1; xbi <= hp -> GetNbinsX(); xbi ++ ) {

          float x_bc_val = bc_val_x[xbi] ;
          float bin_dx = hp -> GetXaxis() -> GetBinLowEdge( xbi+1 ) - hp -> GetXaxis() -> GetBinLowEdge( xbi ) ;
          ///printf("   x bin %2d :  val = %7.4f, dx = %7.4f\n", xbi, x_bc_val, bin_dx ) ;

             float y_val = q2_bc_val / ( x_bc_val * s_val ) ;

             float Yplus_val = 1e-9 ;
             if ( y_val <= 1 ) Yplus_val = 1. + (1. - y_val) * (1. - y_val) ;

             float rc_sf = 0. ;
             if ( y_val <= 1 ) rc_sf = ( (q2_bc_val * q2_bc_val * x_bc_val) / (Yplus_val * 2. * 3.14159265 * alpha_val * alpha_val * lumi_ipb) ) * ( 1. / ( bin_dx * bin_dq2 ) ) * (1./hbar_c_squared) ;


             float hist_bin_val = hp -> GetBinContent( xbi, q2bi ) ;
             float hist_bin_err = hp -> GetBinError( xbi, q2bi ) ;

             if ( y_val <= 1 ) {
                printf("  %3d, %3d  :  Q2 = %7.1f, x = %6.4f  :  hist_bin_val = %9.2f y_val = %9.5f Yplus = %12.4f  rc_sf = %12.6f   Rxsec = %6.3f +/- %6.3f  ",
                   q2bi, xbi, q2_bc_val, x_bc_val, hist_bin_val, y_val, Yplus_val, rc_sf, rc_sf * hist_bin_val, rc_sf * hist_bin_err ) ;
                printf("\n") ;
             }

             hp_rxsec -> SetBinContent( xbi, q2bi, rc_sf * hist_bin_val ) ;
             hp_rxsec -> SetBinError( xbi, q2bi, rc_sf * hist_bin_err ) ;

             hp_rcsf -> SetBinContent( xbi, q2bi, rc_sf ) ;
             hp_rcsf -> SetBinError( xbi, q2bi, 0. ) ;

          } // q2bi

       } // xbi

       return hp_rxsec ;

   } // calc_reduced_xsec_from_q2_vs_x_given_center

#endif


