
#include "histio.c"
#include "utils.c"

   void draw_simple_comp( const char* infile_full   = "norad-nom-hists-rapgap.root",
                          const char* infile_simple = "simple-norad-nom-hists-rapgap.root"
                          ) {

      char answ ;
      gDirectory -> Delete( "h*" ) ;

      gStyle -> SetOptStat(0) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.10) ;
      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetOptTitle(0) ;

      loadHist( infile_full, "full" ) ;

      loadHist( infile_simple, "simple" ) ;

      gDirectory -> ls( "*q2*" ) ;

      TH1F* h_norad_full ;
      TH1F* h_norad_simple ;
      TH1F* h_nom_full ;
      TH1F* h_nom_simple ;
      TLegend* legend ;


      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> Clear() ;
      can1 -> cd() ;



    //----

      h_nom_full = get_hist( "h_q2_nom_low_full" ) ;
      h_norad_full = get_hist( "h_q2_norad_low_full" ) ;
      h_nom_simple = get_hist( "h_q2_nom_low_simple" ) ;
      h_norad_simple = get_hist( "h_q2_norad_low_simple" ) ;

      h_norad_full -> Divide( h_nom_full ) ;

      h_norad_simple -> Divide( h_nom_simple ) ;

      h_norad_simple -> SetLineColor(2) ;
      h_norad_simple -> SetMarkerColor(2) ;
      h_norad_full -> SetLineColor(4) ;
      h_norad_full -> SetMarkerColor(4) ;

      h_norad_simple -> SetLineWidth(2) ;
      h_norad_full -> SetLineWidth(2) ;

      h_norad_simple -> SetMarkerStyle(20) ;
      h_norad_full -> SetMarkerStyle(23) ;


      h_norad_simple -> SetMinimum(0.80) ;
      h_norad_simple -> SetMaximum(1.20) ;

      h_norad_simple -> SetXTitle( "Q2" ) ;
      h_norad_simple -> SetYTitle( "NoRad / Nominal ratio" ) ;
      h_norad_simple -> SetTitleOffset( 1.3, "x" ) ;
      h_norad_simple -> SetTitleOffset( 1.5, "y" ) ;

      h_norad_simple -> Draw() ;
      h_norad_full -> Draw("same") ;

      legend = new TLegend( 0.25, 0.70, 0.70, 0.85 ) ;
      legend -> AddEntry( h_norad_full, "DNN paper defn." ) ;
      legend -> AddEntry( h_norad_simple, "Q2 from gen electron" ) ;
      legend -> Draw() ;

      gPad -> SetGridy(1) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;
      answ = getchar() ; if ( answ == 'q' ) return ;


    //----

      h_nom_full = get_hist( "h_q2_nom_full" ) ;
      h_norad_full = get_hist( "h_q2_norad_full" ) ;
      h_nom_simple = get_hist( "h_q2_nom_simple" ) ;
      h_norad_simple = get_hist( "h_q2_norad_simple" ) ;

      h_norad_full -> Divide( h_nom_full ) ;

      h_norad_simple -> Divide( h_nom_simple ) ;

      h_norad_simple -> SetLineColor(2) ;
      h_norad_simple -> SetMarkerColor(2) ;
      h_norad_full -> SetLineColor(4) ;
      h_norad_full -> SetMarkerColor(4) ;

      h_norad_simple -> SetLineWidth(2) ;
      h_norad_full -> SetLineWidth(2) ;

      h_norad_simple -> SetMarkerStyle(20) ;
      h_norad_full -> SetMarkerStyle(23) ;


      h_norad_simple -> SetMinimum(0.80) ;
      h_norad_simple -> SetMaximum(1.20) ;

      h_norad_simple -> SetXTitle( "Q2" ) ;
      h_norad_simple -> SetYTitle( "NoRad / Nominal ratio" ) ;
      h_norad_simple -> SetTitleOffset( 1.3, "x" ) ;
      h_norad_simple -> SetTitleOffset( 1.5, "y" ) ;

      h_norad_simple -> Draw() ;
      h_norad_full -> Draw("same") ;

      legend = new TLegend( 0.25, 0.70, 0.70, 0.85 ) ;
      legend -> AddEntry( h_norad_full, "DNN paper defn." ) ;
      legend -> AddEntry( h_norad_simple, "Q2 from gen electron" ) ;
      legend -> Draw() ;

      gPad -> SetGridy(1) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;
      answ = getchar() ; if ( answ == 'q' ) return ;


    //----

      h_nom_full = get_hist( "h_log10q2_nom_full" ) ;
      h_norad_full = get_hist( "h_log10q2_norad_full" ) ;
      h_nom_simple = get_hist( "h_log10q2_nom_simple" ) ;
      h_norad_simple = get_hist( "h_log10q2_norad_simple" ) ;

      h_norad_full -> Divide( h_nom_full ) ;

      h_norad_simple -> Divide( h_nom_simple ) ;

      h_norad_simple -> SetLineColor(2) ;
      h_norad_simple -> SetMarkerColor(2) ;
      h_norad_full -> SetLineColor(4) ;
      h_norad_full -> SetMarkerColor(4) ;

      h_norad_simple -> SetLineWidth(2) ;
      h_norad_full -> SetLineWidth(2) ;

      h_norad_simple -> SetMarkerStyle(20) ;
      h_norad_full -> SetMarkerStyle(23) ;


      h_norad_simple -> SetMinimum(0.80) ;
      h_norad_simple -> SetMaximum(1.20) ;

      h_norad_simple -> SetXTitle( "Q2" ) ;
      h_norad_simple -> SetYTitle( "NoRad / Nominal ratio" ) ;
      h_norad_simple -> SetTitleOffset( 1.3, "x" ) ;
      h_norad_simple -> SetTitleOffset( 1.5, "y" ) ;

      h_norad_simple -> Draw() ;
      h_norad_full -> Draw("same") ;

      legend = new TLegend( 0.25, 0.70, 0.70, 0.85 ) ;
      legend -> AddEntry( h_norad_full, "DNN paper defn." ) ;
      legend -> AddEntry( h_norad_simple, "Q2 from gen electron" ) ;
      legend -> Draw() ;

      gPad -> SetGridy(1) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;
      answ = getchar() ; if ( answ == 'q' ) return ;


   }















