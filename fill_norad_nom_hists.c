
#include "histio.c"


   void fill_norad_nom_hists(
          const char* norad_fpat   = "/Users/owen/work/eic/work-2021-11-15/out_em_A/RaNorad_Eminus06_*.nominal.root",
          const char* nominal_fpat = "/Users/owen/work/eic/work-2021-11-15/out_em06/Rapgap_Eminus06_*.nominal.root"
        //const char* norad_fpat   = "/Users/owen/work/eic/work-2021-11-15/out_em_A/DjNorad_Eminus06_*.nominal.root",
        //const char* nominal_fpat = "/Users/owen/work/eic/work-2021-11-15/out_em06/Django_Eminus06_*.nominal.root"
           ) {

      gDirectory -> Delete( "h*" ) ;

      gStyle -> SetOptStat(0) ;

      TChain ch_norad("RaNorad/minitree") ;
      //TChain ch_norad("DjNorad/minitree") ;
      ch_norad.Add( norad_fpat ) ;
      int nevts_norad = ch_norad.GetEntries() ;
      printf("\n\n Number of no-rad events in %s : %d\n\n", norad_fpat, nevts_norad ) ;
      if ( nevts_norad <= 0 ) { printf("\n\n *** ???\n\n" ) ; return ; }

      TChain ch_nom("Rapgap/minitree") ;
      //TChain ch_nom("Django/minitree") ;
      ch_nom.Add( nominal_fpat ) ;
      int nevts_nom = ch_nom.GetEntries() ;
      printf("\n\n Number of nominal MC events in %s : %d\n\n", nominal_fpat, nevts_nom ) ;
      if ( nevts_nom <= 0 ) { printf("\n\n *** ???\n\n" ) ; return ; }


      TCanvas* can1 = (TCanvas*) gDirectory -> FindObject( "can1" ) ;
      if ( can1 == 0x0 ) can1 = new TCanvas( "can1", "", 50, 50, 800, 800 ) ;
      can1 -> Clear() ;
      can1 -> cd() ;


    //-----

      int nbins_q2 = 20 ;
      float q2min = 200. ;
      float q2max = 15000. ;

      printf("\n\n Norad.\n") ;
      TH1F* h_q2_norad = new TH1F( "h_q2_norad", "Q2, norad", nbins_q2, q2min, q2max ) ;
      ch_norad.Draw( "from_tlv_gen_Q2 >> h_q2_norad", "wgt*(from_tlv_gen_Q2>200)" ) ;

      gPad -> SetLogy(1) ;
      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;

      printf("\n\n Nominal.\n") ;
      TH1F* h_q2_nom = new TH1F( "h_q2_nom", "Q2, nominal", nbins_q2, q2min, q2max ) ;
      ch_nom.Draw( "from_tlv_gen_Q2 >> h_q2_nom", "wgt*(from_tlv_gen_Q2>200)" ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;

    //-----

      int nbins_q2_low = 13 ;
      float q2min_low = 200. ;
      float q2max_low = 1500. ;

      printf("\n\n Norad.\n") ;
      TH1F* h_q2_norad_low = new TH1F( "h_q2_norad_low", "Q2, norad", nbins_q2_low, q2min_low, q2max_low ) ;
      ch_norad.Draw( "from_tlv_gen_Q2 >> h_q2_norad_low", "wgt*(from_tlv_gen_Q2>200)" ) ;

      gPad -> SetLogy(1) ;
      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;

      printf("\n\n Nominal.\n") ;
      TH1F* h_q2_nom_low = new TH1F( "h_q2_nom_low", "Q2, nominal", nbins_q2_low, q2min_low, q2max_low ) ;
      ch_nom.Draw( "from_tlv_gen_Q2 >> h_q2_nom_low", "wgt*(from_tlv_gen_Q2>200)" ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;




    //-----

      float log10q2min = 2.3 ;
      float log10q2max = 5.0 ;

      printf("\n\n Norad.\n") ;
      TH1F* h_log10q2_norad = new TH1F( "h_log10q2_norad", "log10Q2, norad", nbins_q2, log10q2min, log10q2max ) ;
      ch_norad.Draw( "log10(from_tlv_gen_Q2) >> h_log10q2_norad", "wgt*(from_tlv_gen_Q2>200)" ) ;

      gPad -> SetLogy(1) ;
      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;

      printf("\n\n Nominal.\n") ;
      TH1F* h_log10q2_nom = new TH1F( "h_log10q2_nom", "log10Q2, nominal", nbins_q2, log10q2min, log10q2max ) ;
      ch_nom.Draw( "log10(from_tlv_gen_Q2) >> h_log10q2_nom", "wgt*(from_tlv_gen_Q2>200)" ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;


    //-----

      int nbins_x = 20 ;
      float xmin = 0. ;
      float xmax = 1. ;

      printf("\n\n Norad.\n") ;
      TH1F* h_x_norad = new TH1F( "h_x_norad", "x, norad", nbins_x, xmin, xmax ) ;
      ch_norad.Draw( "from_tlv_gen_x >> h_x_norad", "wgt*(from_tlv_gen_Q2>200)" ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;

      printf("\n\n Nominal.\n") ;
      TH1F* h_x_nom = new TH1F( "h_x_nom", "x, nominal", nbins_x, xmin, xmax ) ;
      ch_nom.Draw( "from_tlv_gen_x >> h_x_nom", "wgt*(from_tlv_gen_Q2>200)" ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;


    //-----

      float log10xmin = -3. ;
      float log10xmax = 0. ;

      printf("\n\n Norad.\n") ;
      TH1F* h_log10x_norad = new TH1F( "h_log10x_norad", "log10x, norad", nbins_x, log10xmin, log10xmax ) ;
      ch_norad.Draw( "log10(from_tlv_gen_x) >> h_log10x_norad", "wgt*(from_tlv_gen_Q2>200)" ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;

      printf("\n\n Nominal.\n") ;
      TH1F* h_log10x_nom = new TH1F( "h_log10x_nom", "log10x, nominal", nbins_x, log10xmin, log10xmax ) ;
      ch_nom.Draw( "log10(from_tlv_gen_x) >> h_log10x_nom", "wgt*(from_tlv_gen_Q2>200)" ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;






    //-----

      int nbins_y = 20 ;
      float ymin = 0. ;
      float ymax = 1. ;

      printf("\n\n Norad.\n") ;
      TH1F* h_y_norad = new TH1F( "h_y_norad", "y, norad", nbins_y, ymin, ymax ) ;
      ch_norad.Draw( "from_tlv_gen_y >> h_y_norad", "wgt*(from_tlv_gen_Q2>200)" ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;

      printf("\n\n Nominal.\n") ;
      TH1F* h_y_nom = new TH1F( "h_y_nom", "y, nominal", nbins_y, ymin, ymax ) ;
      ch_nom.Draw( "from_tlv_gen_y >> h_y_nom", "wgt*(from_tlv_gen_Q2>200)" ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;



    //-----

      printf("\n\n Norad.\n") ;
      TH2F* h_q2_vs_x_norad = new TH2F( "h_q2_vs_x_norad", "Q2 vs x, norad", nbins_x, xmin, xmax,  nbins_q2, q2min, q2max ) ;

      ch_norad.Draw( "from_tlv_gen_Q2:from_tlv_gen_x >> h_q2_vs_x_norad", "wgt*(from_tlv_gen_Q2>200)", "colz" ) ;

      gPad -> SetLogy(0) ; gPad -> SetLogz(1) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;

      printf("\n\n Nominal.\n") ;
      TH2F* h_q2_vs_x_nom = new TH2F( "h_q2_vs_x_nom", "Q2 vs x, nominal", nbins_x, xmin, xmax,  nbins_q2, q2min, q2max ) ;
      ch_nom.Draw( "from_tlv_gen_Q2:from_tlv_gen_x >> h_q2_vs_x_nom", "wgt*(from_tlv_gen_Q2>200)", "colz" ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;


    //-----

      printf("\n\n Norad.\n") ;
      TH2F* h_log10q2_vs_log10x_norad = new TH2F( "h_log10q2_vs_log10x_norad", "log10Q2 vs log10x, norad", nbins_x, log10xmin, log10xmax,  nbins_q2, log10q2min, log10q2max ) ;
      ch_norad.Draw( "log10(from_tlv_gen_Q2):log10(from_tlv_gen_x) >> h_log10q2_vs_log10x_norad", "wgt*(from_tlv_gen_Q2>200)", "colz" ) ;

      gPad -> SetLogy(0) ; gPad -> SetLogz(1) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;

      printf("\n\n Nominal.\n") ;
      TH2F* h_log10q2_vs_log10x_nom = new TH2F( "h_log10q2_vs_log10x_nom", "log10Q2 vs log10x, nominal", nbins_x, log10xmin, log10xmax,  nbins_q2, log10q2min, log10q2max ) ;
      ch_nom.Draw( "log10(from_tlv_gen_Q2):log10(from_tlv_gen_x) >> h_log10q2_vs_log10x_nom", "wgt*(from_tlv_gen_Q2>200)", "colz" ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;


      saveHist( "norad-nom-hists.root", "h*" ) ;


   } // norad_ratio



