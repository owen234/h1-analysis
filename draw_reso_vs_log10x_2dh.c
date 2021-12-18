


void draw_reso_vs_log10x_2dh( const char* var = "x", const char* cuts = "wgt", const char* input_root_file = "dnn-output-h1-v2-Rapgap.root", const char* experiment = "athena", int can_size_y=800 ) {


   gSystem -> Exec( "mkdir -p reso-plots" ) ;

   gStyle -> SetOptStat(0) ;
   gStyle -> SetPadBottomMargin(0.15) ;
   gStyle -> SetPadLeftMargin(0.18) ;
   gStyle -> SetPadTopMargin(0.10) ;
   gStyle -> SetPadRightMargin(0.05) ;

   if ( can_size_y >= 800 ) {
      gStyle -> SetTitleOffset( 1.30, "y" ) ;
   } else {
      gStyle -> SetTitleOffset( 1.00, "y" ) ;
   }

   TChain ch("dnnout") ;

   char var_text[100] ;
   if ( strcmp( var, "q2") == 0 ) {
      sprintf( var_text, "Q^{2}" ) ;
   } else {
      sprintf( var_text, "%s", var ) ;
   }

   TText* tt_title = new TText() ;
   tt_title -> SetTextSize( 0.06 ) ;



   char cut_label[100] ;

   TString ts( cuts ) ;
   ts.ReplaceAll("_","-") ;
   ts.ReplaceAll(" ","-") ;
   if ( strlen( cuts ) > 0 ) {
      sprintf( cut_label, "-%s", ts.Data() ) ;
   } else {
      sprintf( cut_label, "-allevts" ) ;
   }



   char plot_title[1000] ;
   sprintf( plot_title, "" ) ;
   if ( strlen( cuts ) == 0 || strcmp( cuts, "wgt" ) == 0 ) { sprintf( plot_title, "All events" ) ; }
   if ( strcmp( cuts, "has_norad" ) == 0 ) { sprintf( plot_title, "No QED radiation only" ) ; }
   if ( strcmp( cuts, "has_isr" ) == 0 ) { sprintf( plot_title, "ISR events only" ) ; }
   if ( strcmp( cuts, "has_fsr" ) == 0 ) { sprintf( plot_title, "FSR events only" ) ; }







   ch.Add( input_root_file ) ;

   int nbins=20 ;
   int nbins_th2 = 100 ;
   float xaxis_min = -2.0 ;
   //float xaxis_min = -3.0 ;
   float xaxis_max = 0.0 ;
   float yaxis_min = 0. ;
   /////float yaxis_max = 2.0 ;
   float yaxis_max = 4.0 ;

   char hname[1000] ;
   char htitle[1000] ;
   char arg1[1000] ;
   char label[100] ;

   char save_fname[1000] ;


   //TCanvas* can = (TCanvas*) gDirectory -> FindObject("can") ;
   //if ( can == 0x0 ) can = new TCanvas("can","", 50, 50, 900, can_size_y ) ;

   TCanvas* can = new TCanvas("can","", 50, 50, 900, can_size_y ) ;



   sprintf( htitle, "%s resolution vs log10(x), DNN", var ) ;

   sprintf( hname, "th2_dnn_%s", var ) ;
   TH2F* th2_dnn = new TH2F( hname, htitle, nbins_th2, xaxis_min, xaxis_max, nbins_th2, yaxis_min, yaxis_max ) ;
   sprintf( arg1, "dnn_%s/from_tlv_gen_%s:log10(from_tlv_gen_x)>>%s", var, var, hname ) ;
   ch.Draw( arg1, cuts, "colz" ) ;
   can -> Update() ; can -> Draw() ; gSystem -> ProcessEvents() ;


   sprintf( hname, "tp_dnn_%s", var ) ;
   TProfile* tp_dnn = new TProfile( hname, htitle, nbins, xaxis_min, xaxis_max, yaxis_min, yaxis_max, "s" ) ;
   sprintf( arg1, "dnn_%s/from_tlv_gen_%s:log10(from_tlv_gen_x)>>%s", var, var, hname ) ;
   ch.Draw( arg1, cuts ) ;

   th2_dnn -> SetXTitle( "log10(gen x)" ) ;
   sprintf( label, "RMS, %s / %s_{gen}", var_text, var_text ) ;
   th2_dnn -> SetYTitle( label ) ;

   tp_dnn -> SetLineWidth(2) ;
   tp_dnn -> SetMarkerStyle(20) ;

   th2_dnn -> Draw("colz") ;
   tp_dnn -> Draw("same") ;
   gPad->SetLogz(1) ;
   can -> Update() ; can -> Draw() ; gSystem -> ProcessEvents() ;

   sprintf( save_fname, "reso-plots/%s-th2-%s-vs-log10x%s-dnn.pdf", experiment, var, cut_label ) ;
   can -> SaveAs(  save_fname ) ;
   sprintf( save_fname, "reso-plots/%s-th2-%s-vs-log10x%s-dnn.png", experiment, var, cut_label ) ;
   can -> SaveAs(  save_fname ) ;










   sprintf( htitle, "%s resolution vs log10(x), e", var ) ;

   sprintf( hname, "th2_e_%s", var ) ;
   TH2F* th2_e = new TH2F( hname, htitle, nbins_th2, xaxis_min, xaxis_max, nbins_th2, yaxis_min, yaxis_max ) ;
   sprintf( arg1, "obs_%s_e/from_tlv_gen_%s:log10(from_tlv_gen_x)>>%s", var, var, hname ) ;
   ch.Draw( arg1, cuts, "colz" ) ;
   can -> Update() ; can -> Draw() ; gSystem -> ProcessEvents() ;


   sprintf( hname, "tp_e_%s", var ) ;
   TProfile* tp_e = new TProfile( hname, htitle, nbins, xaxis_min, xaxis_max, yaxis_min, yaxis_max, "s" ) ;
   sprintf( arg1, "obs_%s_e/from_tlv_gen_%s:log10(from_tlv_gen_x)>>%s", var, var, hname ) ;
   ch.Draw( arg1, cuts ) ;

   tp_e -> SetLineWidth(2) ;
   tp_e -> SetMarkerStyle(20) ;

   th2_e -> Draw("colz") ;
   tp_e -> Draw("same") ;
   can -> Update() ; can -> Draw() ; gSystem -> ProcessEvents() ;


   sprintf( save_fname, "reso-plots/%s-th2-%s-vs-log10x%s-e.pdf", experiment, var, cut_label ) ;
   can -> SaveAs(  save_fname ) ;
   sprintf( save_fname, "reso-plots/%s-th2-%s-vs-log10x%s-e.png", experiment, var, cut_label ) ;
   can -> SaveAs(  save_fname ) ;






   sprintf( htitle, "%s resolution vs log10(x), DA", var ) ;

   sprintf( hname, "th2_da_%s", var ) ;
   TH2F* th2_da = new TH2F( hname, htitle, nbins_th2, xaxis_min, xaxis_max, nbins_th2, yaxis_min, yaxis_max ) ;
   sprintf( arg1, "obs_%s_DA/from_tlv_gen_%s:log10(from_tlv_gen_x)>>%s", var, var, hname ) ;
   ch.Draw( arg1, cuts, "colz" ) ;
   can -> Update() ; can -> Draw() ; gSystem -> ProcessEvents() ;


   sprintf( hname, "tp_da_%s", var ) ;
   TProfile* tp_da = new TProfile( hname, htitle, nbins, xaxis_min, xaxis_max, yaxis_min, yaxis_max, "s" ) ;
   sprintf( arg1, "obs_%s_DA/from_tlv_gen_%s:log10(from_tlv_gen_x)>>%s", var, var, hname ) ;
   ch.Draw( arg1, cuts ) ;

   tp_da -> SetLineWidth(2) ;
   tp_da -> SetMarkerStyle(20) ;

   th2_da -> Draw("colz") ;
   tp_da -> Draw("same") ;
   can -> Update() ; can -> Draw() ; gSystem -> ProcessEvents() ;


   sprintf( save_fname, "reso-plots/%s-th2-%s-vs-log10x%s-da.pdf", experiment, var, cut_label ) ;
   can -> SaveAs(  save_fname ) ;
   sprintf( save_fname, "reso-plots/%s-th2-%s-vs-log10x%s-da.png", experiment, var, cut_label ) ;
   can -> SaveAs(  save_fname ) ;






   sprintf( htitle, "%s resolution vs log10(x), eSigma", var ) ;

   sprintf( hname, "th2_esigma_%s", var ) ;
   TH2F* th2_esigma = new TH2F( hname, htitle, nbins_th2, xaxis_min, xaxis_max, nbins_th2, yaxis_min, yaxis_max ) ;
   sprintf( arg1, "obs_%s_eSigma/from_tlv_gen_%s:log10(from_tlv_gen_x)>>%s", var, var, hname ) ;
   ch.Draw( arg1, cuts, "colz" ) ;
   can -> Update() ; can -> Draw() ; gSystem -> ProcessEvents() ;


   sprintf( hname, "tp_esigma_%s", var ) ;
   TProfile* tp_esigma = new TProfile( hname, htitle, nbins, xaxis_min, xaxis_max, yaxis_min, yaxis_max, "s" ) ;
   sprintf( arg1, "obs_%s_eSigma/from_tlv_gen_%s:log10(from_tlv_gen_x)>>%s", var, var, hname ) ;
   ch.Draw( arg1, cuts ) ;

   tp_esigma -> SetLineWidth(2) ;
   tp_esigma -> SetMarkerStyle(20) ;

   th2_esigma -> Draw("colz") ;
   tp_esigma -> Draw("same") ;
   can -> Update() ; can -> Draw() ; gSystem -> ProcessEvents() ;


   sprintf( save_fname, "reso-plots/%s-th2-%s-vs-log10x%s-esigma.pdf", experiment, var, cut_label ) ;
   can -> SaveAs(  save_fname ) ;
   sprintf( save_fname, "reso-plots/%s-th2-%s-vs-log10x%s-esigma.png", experiment, var, cut_label ) ;
   can -> SaveAs(  save_fname ) ;


   return ;

//-------------------------------------------------------------------------------------------------------------------------



   sprintf( hname, "tp_h_%s", var ) ;
   sprintf( htitle, "%s resolution vs log10(x), hadron", var ) ;

   TProfile* tp_h = new TProfile( hname, htitle, nbins, xaxis_min, xaxis_max, yaxis_min, yaxis_max, "s" ) ;

   sprintf( arg1, "rec_%s_h/from_tlv_gen_%s:log10(from_tlv_gen_x)>>%s", var, var, hname ) ;

   ch.Draw( arg1, cuts ) ;



   sprintf( hname, "tp_is_%s", var ) ;
   sprintf( htitle, "%s resolution vs log10(x), ISigma", var ) ;

   TProfile* tp_is = new TProfile( hname, htitle, nbins, xaxis_min, xaxis_max, yaxis_min, yaxis_max, "s" ) ;

   sprintf( arg1, "rec_%s_is/from_tlv_gen_%s:log10(from_tlv_gen_x)>>%s", var, var, hname ) ;

   ch.Draw( arg1, cuts ) ;





   double x_vals[nbins] ;
   double dnn_rms[nbins] ;
   double e_rms[nbins] ;
   double da_rms[nbins] ;
   double h_rms[nbins] ;
   double is_rms[nbins] ;

   double dnn_mean[nbins] ;
   double e_mean[nbins] ;
   double da_mean[nbins] ;
   double h_mean[nbins] ;
   double is_mean[nbins] ;

   for ( int i=0; i<nbins; i++ ) {

      int bi = i+1 ;

      x_vals[i] = tp_dnn -> GetBinCenter( bi ) ;

      dnn_rms[i] = tp_dnn -> GetBinError( bi ) ;
      e_rms[i] = tp_e -> GetBinError( bi ) ;
      da_rms[i] = tp_da -> GetBinError( bi ) ;
      h_rms[i] = tp_h -> GetBinError( bi ) ;
      is_rms[i] = tp_is -> GetBinError( bi ) ;

      dnn_mean[i] = tp_dnn -> GetBinContent( bi ) ;
      e_mean[i] = tp_e -> GetBinContent( bi ) ;
      da_mean[i] = tp_da -> GetBinContent( bi ) ;
      h_mean[i] = tp_h -> GetBinContent( bi ) ;
      is_mean[i] = tp_is -> GetBinContent( bi ) ;


      printf("  %3d : x = %8.3f,  DNN = %7.3f, e = %7.3f, DA = %7.3f\n", bi, x_vals[i], dnn_rms[i], e_rms[i], da_rms[i] ) ;
   }

   TGraph* tg_rms_dnn = new TGraph( nbins, x_vals, dnn_rms ) ;
   TGraph* tg_rms_e = new TGraph( nbins, x_vals, e_rms ) ;
   TGraph* tg_rms_da = new TGraph( nbins, x_vals, da_rms ) ;
   TGraph* tg_rms_h = new TGraph( nbins, x_vals, h_rms ) ;
   TGraph* tg_rms_is = new TGraph( nbins, x_vals, is_rms ) ;

   TGraph* tg_mean_dnn = new TGraph( nbins, x_vals, dnn_mean ) ;
   TGraph* tg_mean_e = new TGraph( nbins, x_vals, e_mean ) ;
   TGraph* tg_mean_da = new TGraph( nbins, x_vals, da_mean ) ;
   TGraph* tg_mean_h = new TGraph( nbins, x_vals, h_mean ) ;
   TGraph* tg_mean_is = new TGraph( nbins, x_vals, is_mean ) ;


   float marker_size = 1.5 ;

   tg_rms_dnn -> SetMarkerStyle(20) ;
   tg_rms_dnn -> SetLineColor(2) ;
   tg_rms_dnn -> SetLineWidth(3) ;
   tg_rms_dnn -> SetMarkerColor(2) ;
   tg_rms_dnn -> SetMarkerSize(marker_size) ;

   tg_rms_e -> SetMarkerStyle(21) ;
   tg_rms_e -> SetLineColor(4) ;
   tg_rms_e -> SetLineWidth(3) ;
   tg_rms_e -> SetMarkerColor(4) ;
   tg_rms_e -> SetMarkerSize(marker_size) ;

   tg_rms_da -> SetMarkerStyle(22) ;
   tg_rms_da -> SetLineColor(6) ;
   tg_rms_da -> SetLineWidth(3) ;
   tg_rms_da -> SetMarkerColor(6) ;
   tg_rms_da -> SetMarkerSize(marker_size) ;

   tg_rms_h -> SetMarkerStyle(23) ;
   tg_rms_h -> SetLineColor(7) ;
   tg_rms_h -> SetLineWidth(3) ;
   tg_rms_h -> SetMarkerColor(7) ;
   tg_rms_h -> SetMarkerSize(marker_size) ;

   tg_rms_is -> SetMarkerStyle(33) ;
   tg_rms_is -> SetLineColor(8) ;
   tg_rms_is -> SetLineWidth(3) ;
   tg_rms_is -> SetMarkerColor(8) ;
   tg_rms_is -> SetMarkerSize(marker_size*1.3) ;




   tg_mean_dnn -> SetMarkerStyle(20) ;
   tg_mean_dnn -> SetLineColor(2) ;
   tg_mean_dnn -> SetLineWidth(3) ;
   tg_mean_dnn -> SetMarkerColor(2) ;
   tg_mean_dnn -> SetMarkerSize(marker_size) ;

   tg_mean_e -> SetMarkerStyle(21) ;
   tg_mean_e -> SetLineColor(4) ;
   tg_mean_e -> SetLineWidth(3) ;
   tg_mean_e -> SetMarkerColor(4) ;
   tg_mean_e -> SetMarkerSize(marker_size) ;

   tg_mean_da -> SetMarkerStyle(22) ;
   tg_mean_da -> SetLineColor(6) ;
   tg_mean_da -> SetLineWidth(3) ;
   tg_mean_da -> SetMarkerColor(6) ;
   tg_mean_da -> SetMarkerSize(marker_size) ;

   tg_mean_h -> SetMarkerStyle(23) ;
   tg_mean_h -> SetLineColor(7) ;
   tg_mean_h -> SetLineWidth(3) ;
   tg_mean_h -> SetMarkerColor(7) ;
   tg_mean_h -> SetMarkerSize(marker_size) ;

   tg_mean_is -> SetMarkerStyle(33) ;
   tg_mean_is -> SetLineColor(8) ;
   tg_mean_is -> SetLineWidth(3) ;
   tg_mean_is -> SetMarkerColor(8) ;
   tg_mean_is -> SetMarkerSize(marker_size*1.3) ;











   TH2F* hd_rms = new TH2F( "hd_rms", "", 100, xaxis_min, xaxis_max, 100, 0., 0.5 ) ;
   hd_rms -> SetTitleSize( 0.06, "x" ) ;
   hd_rms -> SetTitleSize( 0.06, "y" ) ;
   hd_rms -> SetLabelSize( 0.05, "x" ) ;
   hd_rms -> SetLabelSize( 0.05, "y" ) ;
   hd_rms -> SetXTitle( "log10(gen x)" ) ;
   sprintf( label, "RMS, %s / %s_{gen}", var_text, var_text ) ;
   hd_rms -> SetYTitle( label ) ;


   ////////TH2F* hd_mean = new TH2F( "hd_mean", "", 100, xaxis_min, xaxis_max, 100, 0.8, 1.2 ) ;
   TH2F* hd_mean = new TH2F( "hd_mean", "", 100, xaxis_min, xaxis_max, 100, 0.5, 2.0 ) ;
   hd_mean -> SetTitleSize( 0.06, "x" ) ;
   hd_mean -> SetTitleSize( 0.06, "y" ) ;
   hd_mean -> SetLabelSize( 0.05, "x" ) ;
   hd_mean -> SetLabelSize( 0.05, "y" ) ;
   hd_mean -> SetXTitle( "log10(gen x)" ) ;
   sprintf( label, "Mean, %s / %s_{gen}", var_text, var_text ) ;
   hd_mean -> SetYTitle( label ) ;



   float lx  ;
   float ly  ;
   float lw  ;
   float lh  ;



   //TCanvas* can_rms = (TCanvas*) gDirectory -> FindObject("can_rms") ;
   //if ( can_rms == 0x0 ) can_rms = new TCanvas("can_rms","", 50, 950, 900, can_size_y ) ;

   TCanvas* can_rms = new TCanvas("can_rms","", 50, 50, 900, can_size_y ) ;

   can_rms -> cd() ;

   hd_rms -> Draw() ;
   tg_rms_e->Draw("pl") ;
   tg_rms_da->Draw("pl") ;
   tg_rms_h->Draw("pl") ;
   tg_rms_is->Draw("pl") ;
   tg_rms_dnn->Draw("pl") ;

   gPad -> SetGridy(1) ;

   tt_title -> DrawTextNDC( 0.15, 0.93, plot_title ) ;

   lx = 0.55 ;
   ly = 0.57 ;
   lw = 0.18 ;
   lh = 0.30 ;

   TLegend* tl_rms = new TLegend( lx, ly, lx+lw, ly+lh ) ;

   tl_rms -> AddEntry( tg_rms_dnn, "DNN" ) ;
   tl_rms -> AddEntry( tg_rms_e, "electron" ) ;
   tl_rms -> AddEntry( tg_rms_da, "DA" ) ;
   tl_rms -> AddEntry( tg_rms_h, "hadron" ) ;
   tl_rms -> AddEntry( tg_rms_is, "ISigma" ) ;
   tl_rms -> Draw() ;


   sprintf( save_fname, "reso-plots/%s-rms-%s-vs-log10x%s.pdf", experiment, var, cut_label ) ;
   can_rms -> SaveAs( save_fname ) ;

   sprintf( save_fname, "reso-plots/%s-rms-%s-vs-log10x%s.png", experiment, var, cut_label ) ;
   can_rms -> SaveAs( save_fname ) ;

   can -> Update() ;
   can -> Draw() ;
   gSystem -> ProcessEvents() ;





   //TCanvas* can_mean = (TCanvas*) gDirectory -> FindObject("can_mean") ;
   //if ( can_mean == 0x0 ) can_mean = new TCanvas("can_mean","", 950, 950, 900, can_size_y ) ;

   TCanvas* can_mean = new TCanvas("can_mean","", 950, 50, 900, can_size_y ) ;

   can_mean -> cd() ;

   hd_mean -> Draw() ;
   tg_mean_e->Draw("pl") ;
   tg_mean_da->Draw("pl") ;
   tg_mean_h->Draw("pl") ;
   tg_mean_is->Draw("pl") ;
   tg_mean_dnn->Draw("pl") ;

   gPad -> SetGridy(1) ;

   tt_title -> DrawTextNDC( 0.15, 0.93, plot_title ) ;

   lx = 0.79 ;
   ly = 0.65 ;
   lw = 0.18 ;
   lh = 0.30 ;


   TLegend* tl_mean = new TLegend( lx, ly, lx+lw, ly+lh ) ;

   tl_mean -> AddEntry( tg_mean_dnn, "DNN" ) ;
   tl_mean -> AddEntry( tg_mean_e, "electron" ) ;
   tl_mean -> AddEntry( tg_mean_da, "DA" ) ;
   tl_mean -> AddEntry( tg_mean_h, "hadron" ) ;
   tl_mean -> AddEntry( tg_mean_is, "ISigma" ) ;
   tl_mean -> Draw() ;


   sprintf( save_fname, "reso-plots/%s-mean-%s-vs-log10x%s.pdf", experiment, var, cut_label ) ;
   can_mean -> SaveAs( save_fname ) ;

   sprintf( save_fname, "reso-plots/%s-mean-%s-vs-log10x%s.png", experiment, var, cut_label ) ;
   can_mean -> SaveAs( save_fname ) ;

   can -> Update() ;
   can -> Draw() ;
   gSystem -> ProcessEvents() ;



   gDirectory->ls() ;

}












