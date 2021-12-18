

#include "histio.c"

#include "utils.c"

char gen_or_obs[100] ;

   void draw_x_reso( const char* gen_or_obs_arg = "gen", const char* infile = "x_reso_hists_fine_binning-dnn.root", const char* infile2 = "x_reso_hists_fine_binning-esigma.root" ) {

      sprintf( gen_or_obs, "%s", gen_or_obs_arg ) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;
      if ( strlen( infile2 ) > 1 ) loadHist( infile2, "2" ) ;

      TH2F* h_q2_vs_x_gen_no_cuts = get_hist2d( "h_q2_vs_x_gen_no_cuts" ) ;
      TH2F* h_q2_vs_x_gbi         = get_hist2d( "h_q2_vs_x_gbi" ) ;

      TCanvas* can_q2_vs_x = get_canvas( "can_q2_vs_x", "Q2 vs x", 50, 50, 1400, 900 ) ;
      can_q2_vs_x -> cd() ;
      can_q2_vs_x -> Clear() ;

      gStyle -> SetOptStat(0) ;

      h_q2_vs_x_gen_no_cuts -> Draw( "colz" ) ;

      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;

      h_q2_vs_x_gbi -> Draw( "text same" ) ;

      can_q2_vs_x -> AddExec( "dynamic", "dynamic_draw_x_reso()" ) ;


   } // draw_x_reso


  //-------------------------------------------------------------------------------------------------

   void dynamic_draw_x_reso() {

      TObject *select = gPad->GetSelected();
      if(!select) return;
      if (!select->InheritsFrom(TH2::Class())) {gPad->SetUniqueID(0); return;}
      TH2 *h = (TH2*)select;
      gPad->GetCanvas()->FeedbackMode(kTRUE);

      int pyold = gPad->GetUniqueID();
      int px = gPad->GetEventX();
      int py = gPad->GetEventY();
      float uxmin = gPad->GetUxmin();
      float uxmax = gPad->GetUxmax();
      int pxmin = gPad->XtoAbsPixel(uxmin);
      int pxmax = gPad->XtoAbsPixel(uxmax);
      //////////if(pyold) gVirtualX->DrawLine(pxmin,pyold,pxmax,pyold);
      //////////gVirtualX->DrawLine(pxmin,py,pxmax,py);
      gPad->SetUniqueID(py);
      Float_t upy = gPad->AbsPixeltoY(py);
      Float_t y = gPad->PadtoY(upy);
      gPad->SetUniqueID(px);
      Float_t upx = gPad->AbsPixeltoX(px);
      Float_t x = gPad->PadtoX(upx);

      int gbi = h -> FindBin( x, y ) ;

      printf("    x = %9.5f   Q2 = %9.1f    gbi = %3d\n", x, y, gbi ) ;

      TVirtualPad *padsav = gPad;
      TCanvas *c2a = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("c2a");
      if(c2a) delete c2a->GetPrimitive("Projection");
      else   c2a = new TCanvas("c2a","Projection Canvas",1410,10,700,500);
      c2a->cd();

      char hname[1000] ;
      sprintf( hname, "h_x_meas_over_x_gen__%s_binning_gbi%03d", gen_or_obs, gbi ) ;
      TH1F* h_xreso = (TH1F*) gDirectory -> FindObject( hname ) ;
      if ( h_xreso != 0x0 ) {
         gStyle -> SetOptStat("eimruo") ;
         h_xreso -> SetFillColor(30) ;
         h_xreso -> Draw( "hist" ) ;
         h_xreso -> Draw( "same" ) ;
         float hmax = h_xreso -> GetBinContent( h_xreso -> GetMaximumBin() ) ;
         sprintf( hname, "h_x_meas_over_x_gen__%s_binning_gbi%03d_2", gen_or_obs, gbi ) ;
         TH1F* h_xreso_2 = (TH1F*) gDirectory -> FindObject( hname ) ;
         if ( h_xreso_2 != 0x0 ) {
            h_xreso_2 -> Draw( "same" ) ;
            if ( h_xreso_2 -> GetBinContent( h_xreso_2 -> GetMaximumBin() ) > hmax ) hmax = h_xreso_2 -> GetBinContent( h_xreso_2 -> GetMaximumBin() ) ;
         }
         h_xreso -> SetMaximum( 1.1 * hmax ) ;
         c2a -> Update() ;
         padsav -> cd() ;
      }


      TCanvas *c2b = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("c2b");
      if(c2b) delete c2b->GetPrimitive("Projection");
      else   c2b = new TCanvas("c2b","Projection Canvas",1410,610,700,500);
      c2b->cd();

      sprintf( hname, "h_x_meas_minus_x_gen__%s_binning_gbi%03d", gen_or_obs, gbi ) ;
      TH1F* h_xdiff = (TH1F*) gDirectory -> FindObject( hname ) ;
      if ( h_xdiff != 0x0 ) {
         gStyle -> SetOptStat("eimruo") ;
         h_xdiff -> SetFillColor(30) ;
         h_xdiff -> Draw( "hist" ) ;
         h_xdiff -> Draw( "same" ) ;
         float hmax = h_xdiff -> GetBinContent( h_xdiff -> GetMaximumBin() ) ;
         sprintf( hname, "h_x_meas_minus_x_gen__%s_binning_gbi%03d_2", gen_or_obs, gbi ) ;
         TH1F* h_xdiff_2 = (TH1F*) gDirectory -> FindObject( hname ) ;
         if ( h_xdiff_2 != 0x0 ) {
            h_xdiff_2 -> Draw( "same" ) ;
            if ( h_xdiff_2 -> GetBinContent( h_xdiff_2 -> GetMaximumBin() ) > hmax ) hmax = h_xdiff_2 -> GetBinContent( h_xdiff_2 -> GetMaximumBin() ) ;
         }
         h_xdiff -> SetMaximum( 1.1 * hmax ) ;
         c2a -> Update() ;
         padsav -> cd() ;
      }



   } // dynamic_draw_x_reso

  //-------------------------------------------------------------------------------------------------









