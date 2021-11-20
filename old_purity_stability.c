
   void purity_stability( const char* infile = "/Volumes/Ext_2020_08/dis-reco-work/h1-2021-10-14-v5f/dnn-output-h1-v2-Rapgap.root", const char* treename = "dnnout" ) {

      gStyle -> SetOptStat(0) ;


      TChain ch( treename ) ;
      ch.Add( infile ) ;


      int nevts = ch.GetEntries() ;
      if ( nevts <= 0 ) {
         printf("\n\n *** bad input file: %s, %s\n\n", infile, treename ) ;
         gSystem -> Exit(-1) ;
      }

      printf("\n\n Number of events in tree: %d\n\n", nevts ) ;


      TCanvas* can1 = (TCanvas*) gDirectory -> FindObject( "can1" ) ;
      if ( can1 == 0x0 ) can1 = new TCanvas( "can1", "", 50, 50, 1200, 1200 ) ;
      can1 -> Clear() ;
      can1 -> cd() ;


      int nbins = 40 ;

      float xmin = 1e-5 ;
      float xmax = 1 ;
      float q2min = 1 ;
      float q2max = 1e5 ;

      TH2F* h_all_rec_bins = new TH2F( "h_all_rec_bins", "h_all_rec_bins", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;


      ch.Draw( "log10(dnn_Q2):log10(dnn_x)>>h_all_rec_bins", "wgt*(from_tlv_gen_Q2>200)", "colz") ;

   }

