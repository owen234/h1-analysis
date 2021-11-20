
#include "histio.c"

float nom_s ;

//=====================

TH2F* get_hist( const char* hname ) {
   TH2F* hp = (TH2F*) gDirectory -> FindObject( hname ) ;
   if ( hp == 0x0 ) { printf("\n\n *** can't find %s\n\n", hname ) ; gSystem->Exit(-1) ; }
   return hp ;
}

//=====================

void draw_const_y_lines( TH2F* hp ) {

   gSystem -> Exec( "mkdir -p plots" ) ;

   TLine* tl = new TLine() ;

   float min_log10_x = hp -> GetXaxis() -> GetXmin() ;
   float max_log10_x = hp -> GetXaxis() -> GetXmax() ;

   float min_log10_q2 = hp -> GetYaxis() -> GetXmin() ;
   float max_log10_q2 = hp -> GetYaxis() -> GetXmax() ;

   float min_q2 = pow( 10., min_log10_q2 ) ;
   float max_x  = pow( 10., max_log10_x  ) ;

   float yval ;

   float p1_x_coord ;
   float p1_y_coord ;

   float p2_x_coord ;
   float p2_y_coord ;



   float legend_x = min_log10_x + 0.07 * (max_log10_x - min_log10_x) ;
   float legend_y = min_log10_q2 + 0.90 * (max_log10_q2 - min_log10_q2) ;

   float ldy = 0.30 ;
   float lldx = 0.30 ;

   char label[100] ;

   TText* tt = new TText() ;

   int li = 0 ;




   yval = 0.70 ;

   tl -> SetLineStyle(1) ;

   p1_x_coord = log10( min_q2 / ( nom_s * yval ) ) ;
   p1_y_coord = min_log10_q2 ;

   p2_x_coord = max_log10_x ;
   p2_y_coord = log10( yval * nom_s * max_x ) ;

   tl -> DrawLine( p1_x_coord, p1_y_coord,   p2_x_coord, p2_y_coord ) ;

   tl -> DrawLine( legend_x, legend_y-li*ldy,   legend_x+lldx, legend_y-li*ldy ) ;

   sprintf( label, "y = %.2f", yval ) ;
   tt -> DrawText( legend_x + 1.5 * lldx, legend_y-li*ldy, label ) ;







   yval = 0.1 ;

   li ++ ;

   tl -> SetLineStyle(2) ;

   p1_x_coord = log10( min_q2 / ( nom_s * yval ) ) ;
   p1_y_coord = min_log10_q2 ;

   p2_x_coord = max_log10_x ;
   p2_y_coord = log10( yval * nom_s * max_x ) ;

   tl -> DrawLine( p1_x_coord, p1_y_coord,   p2_x_coord, p2_y_coord ) ;

   tl -> DrawLine( legend_x, legend_y-li*ldy,   legend_x+lldx, legend_y-li*ldy ) ;

   sprintf( label, "y = %.2f", yval ) ;
   tt -> DrawText( legend_x + 1.5 * lldx, legend_y-li*ldy, label ) ;





   yval = 0.01 ;

   li ++ ;

   tl -> SetLineStyle(3) ;

   p1_x_coord = log10( min_q2 / ( nom_s * yval ) ) ;
   p1_y_coord = min_log10_q2 ;

   p2_x_coord = max_log10_x ;
   p2_y_coord = log10( yval * nom_s * max_x ) ;

   tl -> DrawLine( p1_x_coord, p1_y_coord,   p2_x_coord, p2_y_coord ) ;

   tl -> DrawLine( legend_x, legend_y-li*ldy,   legend_x+lldx, legend_y-li*ldy ) ;

   sprintf( label, "y = %.2f", yval ) ;
   tt -> DrawText( legend_x + 1.5 * lldx, legend_y-li*ldy, label ) ;





}


//=====================

   void draw_p_and_s( const char* histfile = "p-and-s.root", float nominal_s = 101568.05  ) {

      nom_s = nominal_s ;

      gStyle -> SetOptStat(0) ;
      gStyle -> SetPadRightMargin(0.11) ;

      gDirectory -> Delete( "h*" ) ;


      loadHist( histfile ) ;

      TH2F* h_purity_dnn = get_hist( "h_purity_dnn" ) ;
      TH2F* h_purity_e = get_hist( "h_purity_e" ) ;
      TH2F* h_purity_isigma = get_hist( "h_purity_isigma" ) ;
      TH2F* h_purity_da = get_hist( "h_purity_da" ) ;

      TH2F* h_stability_dnn = get_hist( "h_stability_dnn" ) ;
      TH2F* h_stability_e = get_hist( "h_stability_e" ) ;
      TH2F* h_stability_isigma = get_hist( "h_stability_isigma" ) ;
      TH2F* h_stability_da = get_hist( "h_stability_da" ) ;

      gDirectory -> ls() ;

      TCanvas* can1 = new TCanvas( "can1", "", 50, 50, 1800, 900 ) ;



      can1 -> Divide( 4, 2 ) ;

      can1 -> cd(1) ;
      h_purity_dnn -> Draw("colz") ;
      draw_const_y_lines( h_purity_dnn ) ;

      can1 -> cd(2) ;
      h_purity_e -> Draw("colz") ;
      draw_const_y_lines( h_purity_e ) ;

      can1 -> cd(3) ;
      h_purity_isigma -> Draw("colz") ;
      draw_const_y_lines( h_purity_isigma ) ;

      can1 -> cd(4) ;
      h_purity_da -> Draw("colz") ;
      draw_const_y_lines( h_purity_da ) ;




      can1 -> cd(5) ;
      h_stability_dnn -> Draw("colz") ;
      draw_const_y_lines( h_stability_dnn ) ;

      can1 -> cd(6) ;
      h_stability_e -> Draw("colz") ;
      draw_const_y_lines( h_stability_e ) ;

      can1 -> cd(7) ;
      h_stability_isigma -> Draw("colz") ;
      draw_const_y_lines( h_stability_isigma ) ;

      can1 -> cd(8) ;
      h_stability_da -> Draw("colz") ;
      draw_const_y_lines( h_stability_da ) ;


      TString tsfn( histfile ) ;
      tsfn.ReplaceAll( ".root", "" ) ;
      char outfile[1000] ;
      sprintf( outfile, "plots/%s.png", tsfn.Data() ) ;
      can1 -> SaveAs( outfile ) ;


   }


