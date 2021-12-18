#ifndef utils_c
#define utils_c


   TCanvas* get_canvas( const char* cname, const char* ctitle = "",
                        int px = 50, int py = 50,
                        int w = 900, int h = 900 ) {
       TCanvas* rp = (TCanvas*) gDirectory -> FindObject( cname ) ;
       if ( rp != 0 ) return rp ;
       return new TCanvas( cname, ctitle, px, py, w, h ) ;
   }

   TH1F* get_hist( const char* hname ) {
      TH1F* rp = (TH1F*) gDirectory -> FindObject( hname ) ;
      if ( rp == 0x0 ) { printf("\n\n *** Missing hist %s\n\n", hname ) ; gSystem -> Exit(-1) ; }
      return rp ;
   }

   TH2F* get_hist2d( const char* hname ) {
      TH2F* rp = (TH2F*) gDirectory -> FindObject( hname ) ;
      if ( rp == 0x0 ) { printf("\n\n *** Missing hist %s\n\n", hname ) ; gSystem -> Exit(-1) ; }
      return rp ;
   }

   TH1F* fget_hist( const char* hname, TFile* tfp ) {
      if ( tfp == 0x0 ) { printf("\n\n *** fget_hist : bad file pointer.\n\n") ; gSystem -> Exit(-1) ; }
      TH1F* rp = (TH1F*) tfp -> Get( hname ) ;
      if ( rp == 0x0 ) { printf("\n\n *** Missing hist %s\n\n", hname ) ; gSystem -> Exit(-1) ; }
      return rp ;
   }

   TH2F* fget_hist2d( const char* hname, TFile* tfp ) {
      if ( tfp == 0x0 ) { printf("\n\n *** fget_hist : bad file pointer.\n\n") ; gSystem -> Exit(-1) ; }
      TH2F* rp = (TH2F*) tfp -> Get( hname ) ;
      if ( rp == 0x0 ) { printf("\n\n *** Missing hist %s\n\n", hname ) ; gSystem -> Exit(-1) ; }
      return rp ;
   }

   TGraph* get_graph( const char* gname ) {
      TGraph* rp = (TGraph*) gDirectory -> FindObject( gname ) ;
      if ( rp == 0x0 ) { printf("\n\n *** Missing TGraph %s\n\n", gname ) ; gSystem -> Exit(-1) ; }
      return rp ;
   }

   void grid_on() {
      gPad -> SetGridx(1) ;
      gPad -> SetGridy(1) ;
   }

   void SetupCorrelationPalette() {

      static Bool_t initialized = kFALSE ;
      static Int_t colors[90] ;

      const Int_t Number = 3 ;
      Double_t Length[Number] = {0.,0.5, 1.} ;
      Double_t Red[Number] = {0.,1.,1.} ;
      Double_t Green[Number] = {0.,1.,0.} ;
      Double_t Blue[Number] = {1.,1.,0.} ;

      if ( !initialized ) {
         Int_t fi = TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,90);
         for ( int i=0; i<90; i++ ) colors[i] = fi+i ;
         initialized = kTRUE ;
         return ;
      }
      gStyle -> SetPalette( 90, colors ) ;

   }

   void Setup2DhistPalette() {
      gStyle -> SetPalette( kBird ) ;
   }


   TH2F* make_q2_vs_x_h1_binning( const char* hname ) {

      ///////int nbins_q2 = 17 ;
      ///////int nbins_x = 14 ;

     //--- Literal bin center method
      ////////double q2_bin_low_edge[] = { 175., 225., 275., 325., 475., 525., 775., 825., 1175., 1225., 1775., 2225., 3775., 6225., 9775., 14225., 25775., 34225. } ;
      ////////double x_bin_low_edge[] = { 0.0016, 0.0024, 0.0040, 0.0060, 0.0100, 0.0160, 0.0240, 0.0400, 0.0600, 0.1000, 0.1600, 0.2000, 0.3000, 0.5000, 0.8000 } ;

     //--- Midway between points method
      /////double q2_bin_low_edge[] = { 175., 225., 275., 350., 450., 575., 725., 900., 1100., 1350., 1750., 2500., 4000., 6500., 10000., 16000., 25000., 40000. } ;
      /////double x_bin_low_edge[] = { 0.0016, 0.0026, 0.0041, 0.0065, 0.0105, 0.0165, 0.0260, 0.0410, 0.0650, 0.1050, 0.1550, 0.2150, 0.3250, 0.5250, 0.8000 } ;

      int nbins_q2 = 18 ;
      int nbins_x = 14 ;

     //--- From H1 internal web page:  https://www-h1.desy.de/h1/iww/ipwg/iinc/hiq2/hiq2-binning.html
      double q2_bin_low_edge[] = { 177.8, 223.9, 281.8, 354.8, 446.7, 562.3, 707.9, 891.3, 1122.0, 1412.5, 1778.3, 2238.7, 3548.1, 6000.7, 10000.0, 16680.2, 27777.9, 46334.0, 77285.9 } ;
      double x_bin_low_edge[] = { 0.00158, 0.00251, 0.00398, 0.00631, 0.01000, 0.01585, 0.02512, 0.03981, 0.06310, 0.10000, 0.14501, 0.20893, 0.31623, 0.50119, 1.00000 } ;

      return new TH2F( hname, hname, nbins_x, x_bin_low_edge, nbins_q2, q2_bin_low_edge ) ;

   }


   TH2F* make_q2_vs_x_fine_h1_binning( const char* hname ) {


     //--- My estimates
      ////////int nbins_q2 = 37 ;
      ////////int nbins_x = 33 ;

      ////////double q2_bin_low_edge[] = { 175., 195., 217., 242., 270., 301., 335., 373., 416., 463., 516., 575., 641., 714., 796., 887., 989., 1147., 1331., 1544., 1792., 2079., 2536., 3093., 3773., 4602., 5613., 6847., 8351., 10186., 12424., 15154., 18484., 22545., 27499., 33542., 40912., 50000. } ;
      ////////double x_bin_low_edge[] = { 0.00100, 0.00123, 0.00151, 0.00186, 0.00229, 0.00282, 0.00346, 0.00426, 0.00524, 0.00644, 0.00793, 0.00975, 0.01199, 0.01475, 0.01814, 0.02231, 0.02745, 0.03376, 0.04152, 0.05107, 0.06282, 0.07727, 0.09504, 0.11690, 0.14379, 0.17686, 0.21754, 0.26757, 0.32911, 0.40481, 0.49791, 0.61243, 0.75329, 1.0 } ;


     //--- From H1 internal web page:  https://www-h1.desy.de/h1/iww/ipwg/iinc/hiq2/hiq2-binning.html

      int nbins_q2 = 38 ;
      int nbins_x = 29 ;
      double q2_bin_low_edge[] = { 177.8, 199.5, 223.9, 251.2, 281.8, 316.2, 354.8, 398.1, 446.7, 501.2, 562.3, 631.0, 707.9, 794.3, 891.3, 1000.0, 1122.0, 1258.9, 1412.5, 1584.9, 1778.3, 1995.3, 2238.7, 2511.9, 2818.4, 3162.3, 3548.1, 4570.9, 5888.4, 7585.8, 9772.4, 12589.3, 16218.1, 20893.0, 26915.3, 34673.7, 44668.4, 57544.0, 74131.0 } ;
      double x_bin_low_edge[] = { 0.00158, 0.00200, 0.00251, 0.00316, 0.00398, 0.00501, 0.00631, 0.00794, 0.01000, 0.01259, 0.01585, 0.01995, 0.02512, 0.03162, 0.03981, 0.05012, 0.06310, 0.07943, 0.10000, 0.12303, 0.15136, 0.18621, 0.22909, 0.28184, 0.34674, 0.42658, 0.52481, 0.64565, 0.79433, 1.00000 } ;

      return new TH2F( hname, hname, nbins_x, x_bin_low_edge, nbins_q2, q2_bin_low_edge ) ;

   }


   TH2Poly* make_q2_vs_x_h1_binning_poly( const char* hname ) {

      int nbins_q2 = 18 ;
      int nbins_x_q2ge447 = 14 ;
      int nbins_x_q2lt447 = 12 ;

     //--- From H1 internal web page:  https://www-h1.desy.de/h1/iww/ipwg/iinc/hiq2/hiq2-binning.html
      double q2_bin_low_edge[] = { 177.8, 223.9, 281.8, 354.8, 446.7, 562.3, 707.9, 891.3, 1122.0, 1412.5, 1778.3, 2238.7, 3548.1, 6000.7, 10000.0, 16680.2, 27777.9, 46334.0, 77285.9 } ;
      double x_bin_low_edge_q2ge447[] = { 0.00158, 0.00251, 0.00398, 0.00631, 0.01000, 0.01585, 0.02512, 0.03981, 0.06310, 0.10000, 0.14501, 0.20893, 0.31623, 0.50119, 1.00000 } ;
      double x_bin_low_edge_q2lt447[] = { 0.00158, 0.00251, 0.00398, 0.00631, 0.01000, 0.01585, 0.02512, 0.03981, 0.06310, 0.10000, 0.17100, 0.31623, 1.00000 } ;

      double bin_vertices_x[4] ;
      double bin_vertices_q2[4] ;

      TH2Poly* hp = new TH2Poly() ;
      hp -> SetName( hname ) ;
      hp -> SetTitle( hname ) ;

      for ( int q2bi=0; q2bi<nbins_q2; q2bi++ ) {

         if ( q2bi < 4 ) {

            for ( int xbi=0; xbi < nbins_x_q2lt447; xbi++ ) {

               bin_vertices_x[0] = x_bin_low_edge_q2lt447[xbi] ;
               bin_vertices_x[1] = x_bin_low_edge_q2lt447[xbi] ;
               bin_vertices_x[2] = x_bin_low_edge_q2lt447[xbi+1] ;
               bin_vertices_x[3] = x_bin_low_edge_q2lt447[xbi+1] ;


               bin_vertices_q2[0] = q2_bin_low_edge[q2bi] ;
               bin_vertices_q2[1] = q2_bin_low_edge[q2bi+1] ;
               bin_vertices_q2[2] = q2_bin_low_edge[q2bi+1] ;
               bin_vertices_q2[3] = q2_bin_low_edge[q2bi] ;

               printf(" low  q2bi = %3d, xbi = %3d :  (%9.5f, %7.1f)  (%9.5f, %7.1f)  (%9.5f, %7.1f)  (%9.5f, %7.1f)\n",
                   q2bi, xbi,
                   bin_vertices_x[0], bin_vertices_q2[0],
                   bin_vertices_x[1], bin_vertices_q2[1],
                   bin_vertices_x[2], bin_vertices_q2[2],
                   bin_vertices_x[3], bin_vertices_q2[3] ) ;

               hp -> AddBin( 4, bin_vertices_x, bin_vertices_q2 ) ;

            } // xbi


         } else {

            for ( int xbi=0; xbi < nbins_x_q2ge447; xbi++ ) {

               bin_vertices_x[0] = x_bin_low_edge_q2ge447[xbi] ;
               bin_vertices_x[1] = x_bin_low_edge_q2ge447[xbi] ;
               bin_vertices_x[2] = x_bin_low_edge_q2ge447[xbi+1] ;
               bin_vertices_x[3] = x_bin_low_edge_q2ge447[xbi+1] ;


               bin_vertices_q2[0] = q2_bin_low_edge[q2bi] ;
               bin_vertices_q2[1] = q2_bin_low_edge[q2bi+1] ;
               bin_vertices_q2[2] = q2_bin_low_edge[q2bi+1] ;
               bin_vertices_q2[3] = q2_bin_low_edge[q2bi] ;

               printf(" high q2bi = %3d, xbi = %3d :  (%9.5f, %7.1f)  (%9.5f, %7.1f)  (%9.5f, %7.1f)  (%9.5f, %7.1f)\n",
                   q2bi, xbi,
                   bin_vertices_x[0], bin_vertices_q2[0],
                   bin_vertices_x[1], bin_vertices_q2[1],
                   bin_vertices_x[2], bin_vertices_q2[2],
                   bin_vertices_x[3], bin_vertices_q2[3] ) ;

               hp -> AddBin( 4, bin_vertices_x, bin_vertices_q2 ) ;

            } // xbi

         }


      } // q2bi

      hp -> GetXaxis() -> SetLimits( 0.00158, 1.0 ) ;
      hp -> GetYaxis() -> SetLimits( 177.8, 77285.9 ) ;

      gDirectory -> Add( hp ) ;

      return hp ;

   }




#endif

















