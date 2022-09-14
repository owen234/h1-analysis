

   void print_th2_table( TH2F* hp ) {

      for ( int q2bi=1; q2bi <= hp -> GetNbinsY(); q2bi ++ ) {

         float q2_bc_val = hp -> GetYaxis() -> GetBinCenter( q2bi ) ;
         float bin_dq2 = hp -> GetYaxis() -> GetBinLowEdge( q2bi+1 ) - hp -> GetYaxis() -> GetBinLowEdge( q2bi ) ;

         printf("\n") ;


         for ( int xbi=1; xbi <= hp -> GetNbinsX(); xbi ++ ) {

            float x_bc_val = hp -> GetXaxis() -> GetBinCenter( xbi ) ;

            float hist_bin_val = hp -> GetBinContent( xbi, q2bi ) ;
            float hist_bin_err = hp -> GetBinError( xbi, q2bi ) ;

            if ( hist_bin_val > 0 ) {
                printf("  %3d, %3d  :  Q2 = %7.1f, x = %6.4f  :  hist_bin_val = %9.2f +/- %9.2f  \n",
                   q2bi, xbi, q2_bc_val, x_bc_val, hist_bin_val,  hist_bin_err ) ;
            }

         } // xbi

      } // q2bi

   } // print_th2_table



