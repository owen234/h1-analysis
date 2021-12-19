
#include "utils.c"



   void make_binning_micro_tree(
                const char* method_name = "dnn",
                const char* output_fname = "micro-binning-tree-dnn.root",
                const char* input_fname = "dnn-output-h1-v2-Rapgap.root"
                                 ) {

      printf("\n\n Opening %s\n\n", input_fname ) ;
      TFile* tf_in = new TFile( input_fname, "read" ) ;
      if ( tf_in == 0x0 ) { printf("\n\n *** bad input file: %s\n\n", input_fname ) ; gSystem -> Exit(-1) ; }

      if ( ! tf_in -> IsOpen() ) { printf("\n\n *** bad input file 2: %s\n\n", input_fname ) ; gSystem -> Exit(-1) ; }

      TTree* tt_in = (TTree*) tf_in -> Get( "dnnout" ) ;
      if ( tt_in == 0x0 ) { printf("\n\n *** no dnnout TTree in %s\n\n", input_fname ) ; gSystem -> Exit(-1) ; }
      int nentries = tt_in -> GetEntries() ;
      if ( nentries <= 0 ) { printf("\n\n *** no events in TTree.\n\n") ; gSystem -> Exit(-1) ; }
      printf("\n\n Nentries : %d\n\n", nentries ) ;

      tt_in -> SetBranchStatus("*", 0) ;

      tt_in -> SetBranchStatus( "wgt", 1 ) ;

      tt_in -> SetBranchStatus( "from_tlv_gen_Q2", 1 ) ;
      tt_in -> SetBranchStatus( "from_tlv_gen_x", 1 ) ;
      tt_in -> SetBranchStatus( "from_tlv_gen_y", 1 ) ;


      printf("\n\n Creating %s\n\n", output_fname ) ;
      TFile* tf_out = new TFile( output_fname, "recreate" ) ;

      auto tt_out = tt_in -> CloneTree(0) ;


      if ( strcmp( method_name, "dnn" ) == 0 ) {
         tt_in -> SetBranchStatus( "dnn_x", 1 ) ;
         tt_in -> SetBranchStatus( "dnn_y", 1 ) ;
         tt_in -> SetBranchStatus( "dnn_Q2", 1 ) ;
      }
      if ( strcmp( method_name, "esigma" ) == 0 ) {
         tt_in -> SetBranchStatus( "obs_x_eSigma", 1 ) ;
         tt_in -> SetBranchStatus( "obs_y_eSigma", 1 ) ;
         tt_in -> SetBranchStatus( "obs_Q2_eSigma", 1 ) ;
      }


      float wgt ;
      float from_tlv_gen_x ;
      float from_tlv_gen_y ;
      float from_tlv_gen_Q2 ;

      float obs_x ;
      float obs_y ;
      float obs_Q2 ;

      tt_in -> SetBranchAddress( "wgt", &wgt ) ;
      tt_in -> SetBranchAddress( "from_tlv_gen_x", &from_tlv_gen_x ) ;
      tt_in -> SetBranchAddress( "from_tlv_gen_y", &from_tlv_gen_y ) ;
      tt_in -> SetBranchAddress( "from_tlv_gen_Q2", &from_tlv_gen_Q2 ) ;

      if ( strcmp( method_name, "dnn" ) == 0 ) {
         tt_out -> SetBranchStatus( "dnn_x", 0 ) ;
         tt_out -> SetBranchStatus( "dnn_y", 0 ) ;
         tt_out -> SetBranchStatus( "dnn_Q2", 0 ) ;
         tt_in -> SetBranchAddress( "dnn_x", &obs_x ) ;
         tt_in -> SetBranchAddress( "dnn_y", &obs_y ) ;
         tt_in -> SetBranchAddress( "dnn_Q2", &obs_Q2 ) ;
      }
      if ( strcmp( method_name, "esigma" ) == 0 ) {
         tt_out -> SetBranchStatus( "obs_x_eSigma", 0 ) ;
         tt_out -> SetBranchStatus( "obs_y_eSigma", 0 ) ;
         tt_out -> SetBranchStatus( "obs_Q2_eSigma", 0 ) ;
         tt_in -> SetBranchAddress( "obs_x_eSigma", &obs_x ) ;
         tt_in -> SetBranchAddress( "obs_y_eSigma", &obs_y ) ;
         tt_in -> SetBranchAddress( "obs_Q2_eSigma", &obs_Q2 ) ;
      }


      int   q2_bin_obs ;
      int   q2_bin_gen ;

      tt_out -> Branch( "obs_x", &obs_x, "obs_x/F" ) ;
      tt_out -> Branch( "obs_y", &obs_y, "obs_y/F" ) ;
      tt_out -> Branch( "obs_Q2", &obs_Q2, "obs_Q2/F" ) ;

      tt_out -> Branch( "q2_bin_obs", &q2_bin_obs, "q2_bin_obs/I" ) ;
      tt_out -> Branch( "q2_bin_gen", &q2_bin_gen, "q2_bin_gen/I" ) ;



      tt_out -> Print() ;

      TH2F* h_q2_vs_x_h1_binning = make_q2_vs_x_h1_binning( "h_q2_vs_x_h1_binning" ) ;

      for ( int ei=0; ei<nentries; ei++ ) {

         tt_in -> GetEntry( ei ) ;

         if ( ei%100 == 0 ) {
            printf(" --- Event: %7d / %d    %6.3f\r", ei, nentries, (1.*ei)/(1.*nentries) ) ;
            fflush(stdout) ;
         }

         q2_bin_obs = -1 ;
         q2_bin_gen = -1 ;

         q2_bin_obs = h_q2_vs_x_h1_binning -> GetYaxis() -> FindBin( obs_Q2 ) ;
         q2_bin_gen = h_q2_vs_x_h1_binning -> GetYaxis() -> FindBin( from_tlv_gen_Q2 ) ;

         tt_out -> Fill() ;

      } // ei

      h_q2_vs_x_h1_binning -> Write() ;
      tf_out -> Write() ;
      tf_out -> Close() ;


   }



