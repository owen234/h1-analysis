

   TH2F* make_th2_error_hist( TH2F* hp ) {
      char hname[1000] ;
      sprintf( hname, "%s_errors", hp -> GetName() ) ;
      printf("\n\n make_th2_error_hist : creating %s\n\n", hname ) ;
      TH2F* rp = (TH2F*) hp -> Clone( hname ) ;
      rp -> Reset() ;
      for ( int xbi=1; xbi <= hp -> GetNbinsX(); xbi ++ ) {
         for ( int ybi=1; ybi <= hp -> GetNbinsY(); ybi ++ ) {
            float err = hp -> GetBinError( xbi, ybi ) ;
            rp -> SetBinContent( xbi, ybi, err ) ;
            rp -> SetBinError( xbi, ybi, 0 ) ;
         } // ybi
      } // xbi
      return rp ;
   }
