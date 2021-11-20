
#include "histio.c"
#include "utils.c"

   void draw_norad_nom_hists( float rmin=0.80, float rmax=1.20,
      const char* input_file = "norad-nom-hists-rapgap.root" ) {

      char answ ;

      gStyle -> SetOptStat(0) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.10) ;
      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetOptTitle(0) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( input_file ) ;

      gDirectory -> ls() ;


      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> Clear() ;
      can1 -> cd() ;

      TH1F* h_norad ;
      TH1F* h_nom ;

      TH2F* h_norad2d ;
      TH2F* h_nom2d ;



    //----

      h_norad = get_hist( "h_log10x_norad" ) ;
      h_nom = get_hist( "h_log10x_nom" ) ;

      h_norad -> Divide( h_nom ) ;

      h_norad -> SetLineWidth(2) ;
      h_norad -> SetMarkerStyle(20) ;

      h_norad -> SetXTitle( "Gen log10(x)" ) ;
      h_norad -> SetYTitle( " NoRad / Nominal ratio" ) ;
      h_norad -> SetTitleOffset( 1.3, "x" ) ;
      h_norad -> SetTitleOffset( 1.4, "y" ) ;
      h_norad -> SetMinimum( rmin ) ;
      h_norad -> SetMaximum( rmax ) ;

      h_norad -> Draw() ;
      gPad -> SetGridy(1) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;
      answ = getchar() ; if ( answ == 'q' ) return ;


    //----

      h_norad = get_hist( "h_log10q2_norad" ) ;
      h_nom = get_hist( "h_log10q2_nom" ) ;

      h_norad -> Divide( h_nom ) ;

      h_norad -> SetLineWidth(2) ;
      h_norad -> SetMarkerStyle(20) ;

      h_norad -> SetXTitle( "log10(Q2)" ) ;
      h_norad -> SetYTitle( " NoRad / Nominal ratio" ) ;
      h_norad -> SetTitleOffset( 1.3, "x" ) ;
      h_norad -> SetTitleOffset( 1.4, "y" ) ;
      h_norad -> SetMinimum( rmin ) ;
      h_norad -> SetMaximum( rmax ) ;

      h_norad -> Draw() ;
      gPad -> SetGridy(1) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;
      answ = getchar() ; if ( answ == 'q' ) return ;


    //----

      h_norad = get_hist( "h_y_norad" ) ;
      h_nom = get_hist( "h_y_nom" ) ;

      h_norad -> Divide( h_nom ) ;

      h_norad -> SetLineWidth(2) ;
      h_norad -> SetMarkerStyle(20) ;

      h_norad -> SetXTitle( "Gen y" ) ;
      h_norad -> SetYTitle( " NoRad / Nominal ratio" ) ;
      h_norad -> SetTitleOffset( 1.3, "x" ) ;
      h_norad -> SetTitleOffset( 1.4, "y" ) ;
      h_norad -> SetMinimum( rmin ) ;
      h_norad -> SetMaximum( rmax ) ;

      h_norad -> Draw() ;
      gPad -> SetGridy(1) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;
      answ = getchar() ; if ( answ == 'q' ) return ;


    //----

      gStyle -> SetPadRightMargin(0.18) ;

      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 1000, 900 ) ;
      can2 -> Clear() ;
      can2 -> cd() ;

      h_norad2d = get_hist2d( "h_log10q2_vs_log10x_norad" ) ;
      h_nom2d = get_hist2d( "h_log10q2_vs_log10x_nom" ) ;

      h_norad2d -> Divide( h_nom2d ) ;

      h_norad2d -> SetLineWidth(2) ;
      h_norad2d -> SetMarkerStyle(20) ;

      h_norad2d -> SetXTitle( "Gen log10(x)" ) ;
      h_norad2d -> SetYTitle( "Gen log10(Q2)" ) ;
      h_norad2d -> SetTitleOffset( 1.3, "x" ) ;
      h_norad2d -> SetTitleOffset( 1.4, "y" ) ;
      h_norad2d -> SetMinimum( rmin ) ;
      h_norad2d -> SetMaximum( rmax ) ;

      TExec* change_cor_palette = new TExec( "change_cor_palette", "SetupCorrelationPalette();" );

      h_norad2d -> Draw( "colz" ) ;
      change_cor_palette -> Draw() ;
      h_norad2d -> Draw( "colz same" ) ;
      gPad -> SetGridy(1) ;

      TText* tt = new TText() ;
      tt -> DrawTextNDC( 0.12, 0.93, "NoRad / Nominal ratio" ) ;

      TPaletteAxis* tpa = (TPaletteAxis*) h_norad2d -> GetListOfFunctions() -> FindObject( "palette" ) ;
      tpa -> SetX1NDC( 0.85 ) ;
      tpa -> SetX2NDC( 0.90 ) ;
      can2 -> Modified() ;


      can2 -> Update() ; can2 -> Draw() ; gSystem -> ProcessEvents() ;
      answ = getchar() ; if ( answ == 'q' ) return ;


    //----

      TH2F* h_2d_err = (TH2F*) h_norad2d -> Clone( "h_2d_err" ) ;
      h_2d_err -> Reset() ;
      for ( int xbi = 1; xbi <= h_2d_err -> GetNbinsX(); xbi ++ ) {
         for ( int ybi = 1; ybi <= h_2d_err -> GetNbinsY(); ybi ++ ) {
            h_2d_err -> SetBinContent( xbi, ybi, h_norad2d -> GetBinError( xbi, ybi ) ) ;
         } // ybi
      } // xbi
      h_2d_err -> SetMinimum(0) ;
      h_2d_err -> SetMaximum(0.20) ;

      TExec* change_hist_palette = new TExec( "change_hist_palette", "Setup2DhistPalette();" );

      h_2d_err -> Draw( "colz" ) ;
      change_hist_palette -> Draw() ;
      h_2d_err -> Draw( "colz same" ) ;

      tt -> DrawTextNDC( 0.12, 0.93, "Stat. Uncertainty on NoRad / Nominal ratio" ) ;

      can2 -> Update() ; can2 -> Draw() ; gSystem -> ProcessEvents() ;
      answ = getchar() ; if ( answ == 'q' ) return ;






   } // draw_norad_nom_hists




