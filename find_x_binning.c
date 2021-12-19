
#include "histio.c"

#include "utils.c"

   TTree* tt ;

   bool verbose = true ;

   int nentries ;

   float from_tlv_gen_Q2 ;
   float from_tlv_gen_x  ;
   float from_tlv_gen_y  ;
   float wgt             ;
   float obs_x           ;
   float obs_y           ;
   float obs_Q2          ;
   int   q2_bin_obs      ;
   int   q2_bin_gen      ;


  //-------------

   int get_counts( int q2bin, float x_min, float x_max,
                     float& n_gen_in_bin,
                     float& n_obs_in_bin,
                     float& n_both_in_bin ) ;

  //-------------

   void find_x_binning(
          int first_q2bin = 2,
          int last_q2bin = 18,
          float Pmin = 0.40,
          float Smin = 0.40,
          float Emax = 0.50,
          float Omin = 1.0,
          float dlog10x_scan_step = 0.02,
          float min_dlog10x_bin_width = 0.06,
          const char* input_ttree_file = "micro-binning-tree-esigma.root"
        ) {

      float bin_step_sf = pow( 10., dlog10x_scan_step ) ;
      float first_bin_step_sf = pow( 10., min_dlog10x_bin_width ) ;

      TFile* tf_in = new TFile( input_ttree_file, "read" ) ;
      if ( tf_in == 0x0 ) { printf("\n\n *** bad input file: %s\n\n", input_ttree_file ) ; gSystem -> Exit(-1) ; }
      if ( ! tf_in -> IsOpen() ) { printf("\n\n *** bad input file: %s\n\n", input_ttree_file ) ; gSystem -> Exit(-1) ; }

      tt = (TTree*) tf_in -> Get( "dnnout" ) ;
      if ( tt == 0x0 ) { printf("\n\n *** can't find dnnout TTree in %s\n\n", input_ttree_file ) ; gSystem -> Exit(-1) ; }
      nentries = tt -> GetEntries() ;
      printf("\n\n   %s  :  %d events\n", input_ttree_file, nentries ) ;

      TH2F* h_q2_vs_x_h1_binning = (TH2F*) tf_in -> Get( "h_q2_vs_x_h1_binning" ) ;
      if ( h_q2_vs_x_h1_binning == 0x0 ) { printf("\n\n *** Input file %s does not have binning histogram with name h_q2_vs_x_h1_binning\n\n", input_ttree_file ) ; gSystem -> Exit(-1) ; }

      if ( last_q2bin > h_q2_vs_x_h1_binning -> GetNbinsY() ) { printf("\n\n *** q2bin = %d is out of range.  Histogram has %d bins\n\n", last_q2bin, h_q2_vs_x_h1_binning -> GetNbinsY() ) ; return ; }


      float beam_e_e = 27.6 ;
      float beam_p_e = 920.0 ;


      tt -> SetBranchAddress( "from_tlv_gen_Q2", &from_tlv_gen_Q2 ) ;
      tt -> SetBranchAddress( "from_tlv_gen_x", &from_tlv_gen_x ) ;
      tt -> SetBranchAddress( "from_tlv_gen_y", &from_tlv_gen_y ) ;
      tt -> SetBranchAddress( "wgt", &wgt ) ;
      tt -> SetBranchAddress( "obs_x", &obs_x ) ;
      tt -> SetBranchAddress( "obs_y", &obs_y ) ;
      tt -> SetBranchAddress( "obs_Q2", &obs_Q2 ) ;
      tt -> SetBranchAddress( "q2_bin_obs", &q2_bin_obs ) ;
      tt -> SetBranchAddress( "q2_bin_gen", &q2_bin_gen ) ;

      float n_gen_in_bin ;
      float n_obs_in_bin ;
      float n_both_in_bin ;

      int   n_obs_in_q2bin_for_all_x ;

      TH2Poly* h_output_binning = new TH2Poly() ;
      h_output_binning -> SetName( "h_output_binning" ) ;
      h_output_binning -> SetTitle( "Output binning" ) ;



      for ( int q2bin = last_q2bin; q2bin >= first_q2bin; q2bin -- ) {

         int nbins = 0 ;
         int max_bins = 200 ;

         float q2bin_min = h_q2_vs_x_h1_binning -> GetYaxis() -> GetBinLowEdge( q2bin ) ;
         float q2bin_max = h_q2_vs_x_h1_binning -> GetYaxis() -> GetBinLowEdge( q2bin + 1 ) ;

         float min_x_allowed = q2bin_min / (4 * beam_e_e * beam_p_e ) ;

         printf("\n\n q2Bin %d range [%7.1f, %7.1f] , min x allowed = %7.5f\n\n", q2bin, q2bin_min, q2bin_max, min_x_allowed ) ;

        //-- find the overflow bin.

         float x_max = 1. ;
         float x_min = x_max ;
         n_obs_in_bin = 0. ;
         while ( n_obs_in_bin < Omin && x_min >= min_x_allowed ) {
            x_min = x_min / bin_step_sf ;
            n_obs_in_q2bin_for_all_x = get_counts( q2bin, x_min, x_max, n_gen_in_bin, n_obs_in_bin, n_both_in_bin ) ;
            if ( n_obs_in_q2bin_for_all_x <= 0 ) { printf("\n\n *** No observed events in q2bin %d\n\n", q2bin ) ; return ; }
         }
         printf(" Final x_min for overflow is %7.5f\n", x_min ) ;

         h_output_binning -> AddBin( x_min, q2bin_min, x_max, q2bin_max ) ;



         while ( nbins < max_bins && x_min > min_x_allowed ) {

            printf(" Scanning next bin.\n") ;

            float purity = 0. ;
            float stability = 0. ;
            float stat_err = 1. ;

            x_max = x_min ;
            bool first_step = true ;
            while ( (purity < Pmin || stability < Smin || stat_err > Emax) && x_min >= min_x_allowed ) {
               if ( first_step ) {
                  x_min = x_min / first_bin_step_sf ;
                  first_step = false ;
               } else {
                  x_min = x_min / bin_step_sf ;
               }
               n_obs_in_q2bin_for_all_x = get_counts( q2bin, x_min, x_max, n_gen_in_bin, n_obs_in_bin, n_both_in_bin ) ;
               if ( n_obs_in_q2bin_for_all_x <= 0 ) { printf("\n\n *** No observed events in q2bin %d\n\n", q2bin ) ; return ; }
               if ( n_obs_in_bin > 0 ) purity = n_both_in_bin / n_obs_in_bin ;
               if ( n_gen_in_bin > 0 ) stability = n_both_in_bin / n_gen_in_bin ;
               if ( n_obs_in_bin > 0 ) stat_err = 1. / sqrt( n_obs_in_bin ) ;
            }
            printf(" Final x_min for bin %d is %7.5f\n", nbins, x_min ) ;

            h_output_binning -> AddBin( x_min, q2bin_min, x_max, q2bin_max ) ;

            x_max = x_min ;

            nbins ++ ;

         }

      } // q2bin


      printf("\n\n Saving output binning in output-binning.root\n\n") ;

      TFile* tf_out = new TFile( "output-binning.root", "recreate" ) ;

      h_output_binning -> Write() ;

      tf_out -> Close() ;



   } // find_x_binning

  //-------------

   int get_counts( int q2bin, float x_min, float x_max,
                     float& n_gen_in_bin,
                     float& n_obs_in_bin,
                     float& n_both_in_bin ) {

       if ( verbose ) {  printf(" get_counts : beginning for q2bin %2d with x [%6.4f, %6.4f]  ", q2bin, x_min, x_max ) ; }

       n_gen_in_bin = 0. ;
       n_obs_in_bin = 0. ;
       n_both_in_bin = 0. ;

       float q2min = 1e9 ;
       float q2max = 0. ;

       int n_obs_in_q2bin_for_all_x = 0 ;

       for ( int ei=0; ei<nentries; ei++ ) {

          tt -> GetEntry( ei ) ;

          if ( q2_bin_obs == q2bin ) {
             n_obs_in_q2bin_for_all_x ++ ;
             if ( obs_x >= x_min && obs_x < x_max ) {
                n_obs_in_bin += wgt ;
             }
             if ( obs_Q2 > q2max ) q2max = obs_Q2 ;
             if ( obs_Q2 < q2min ) q2min = obs_Q2 ;
          }
          if ( q2_bin_gen == q2bin ) {
             if ( from_tlv_gen_x >= x_min && from_tlv_gen_x < x_max ) {
                n_gen_in_bin += wgt ;
                if ( q2_bin_obs == q2bin ) {
                   if ( obs_x >= x_min && obs_x < x_max ) {
                      n_both_in_bin += wgt ;
                   }
                }
             }
          }

          if ( verbose ) {
             if ( ei % (nentries/10) == 0 ) {
                printf(".") ; fflush(stdout) ;
             }
          }


       } // ei

       if ( verbose ) {
          float purity = 0. ;
          float stability = 0. ;
          float stat_err = 1. ;
          if ( n_obs_in_bin > 0 ) purity    = n_both_in_bin / n_obs_in_bin ;
          if ( n_gen_in_bin > 0 ) stability = n_both_in_bin / n_gen_in_bin ;
          if ( n_obs_in_bin > 0 ) stat_err = 1. / sqrt( n_obs_in_bin ) ;
          printf( "  returning:  n_obs_in_bin = %8.2f, n_gen_in_bin = %8.2f, n_both_in_bin = %8.2f |  P = %5.3f , S = %5.3f , E = %5.3f  | Q2min = %5.0f, Q2max = %5.0f\n",
             n_obs_in_bin, n_gen_in_bin, n_both_in_bin, purity, stability, stat_err, q2min, q2max ) ;
       }

       return n_obs_in_q2bin_for_all_x ;

   } // get_counts

  //-------------







