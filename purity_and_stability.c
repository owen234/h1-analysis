#define purity_and_stability_cxx
#include "purity_and_stability.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "histio.c"
#include "draw_p_and_s.c"

void purity_and_stability::Loop()
{
   if (fChain == 0) return;

   gDirectory -> Delete( "h*" ) ;

   gStyle -> SetOptStat(0) ;

   Long64_t nentries = fChain->GetEntries();

   printf("\n\n Number of events:  %lld\n\n", nentries ) ;

   int nbins = 30 ;

   float xmin = 1e-3 ;
   float xmax = 1 ;
   float q2min = 1e2 ;
   float q2max = 1e5 ;

   TH2F* h_all_gen_bins = new TH2F( "h_all_gen_bins", "h_all_gen_bins", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;

   TH2F* h_all_rec_bins_dnn = new TH2F( "h_all_rec_bins_dnn", "h_all_rec_bins_dnn", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;
   TH2F* h_same_gen_bins_dnn = new TH2F( "h_same_gen_bins_dnn", "h_same_gen_bins_dnn", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;
   TH2F* h_same_rec_bins_dnn = new TH2F( "h_same_rec_bins_dnn", "h_same_rec_bins_dnn", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;

   TH2F* h_all_rec_bins_e = new TH2F( "h_all_rec_bins_e", "h_all_rec_bins_e", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;
   TH2F* h_same_gen_bins_e = new TH2F( "h_same_gen_bins_e", "h_same_gen_bins_e", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;
   TH2F* h_same_rec_bins_e = new TH2F( "h_same_rec_bins_e", "h_same_rec_bins_e", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;

   TH2F* h_all_rec_bins_isigma = new TH2F( "h_all_rec_bins_isigma", "h_all_rec_bins_isigma", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;
   TH2F* h_same_gen_bins_isigma = new TH2F( "h_same_gen_bins_isigma", "h_same_gen_bins_isigma", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;
   TH2F* h_same_rec_bins_isigma = new TH2F( "h_same_rec_bins_isigma", "h_same_rec_bins_isigma", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;

   TH2F* h_all_rec_bins_da = new TH2F( "h_all_rec_bins_da", "h_all_rec_bins_da", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;
   TH2F* h_same_gen_bins_da = new TH2F( "h_same_gen_bins_da", "h_same_gen_bins_da", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;
   TH2F* h_same_rec_bins_da = new TH2F( "h_same_rec_bins_da", "h_same_rec_bins_da", nbins, log10(xmin), log10(xmax),   nbins, log10(q2min), log10(q2max) ) ;

   bool verbose = true ;

   float nominal_s(0.) ;

   Long64_t nbytes = 0, nb = 0;
   printf("\n\n Starting loop.\n") ;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      int ei = jentry ;

      if ( !verbose && ei%100 == 0 ) {
         printf(" --- Event: %7d / %lld    %6.3f\r", ei, nentries, (1.*ei)/(1.*nentries) ) ;
         fflush(stdout) ;
      }

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


      if ( jentry == 0 ) {
         nominal_s = 4. * beam_e_e * beam_p_e ;
         printf("\n\n Set nominal s to  4 * %9.2f * %9.2f = %9.2f\n\n", beam_e_e, beam_p_e, nominal_s ) ;
      }

      float log10_gen_x  = log10( from_tlv_gen_x  ) ;
      float log10_gen_q2 = log10( from_tlv_gen_Q2 ) ;

      float log10_rec_x_dnn  = log10( dnn_x  ) ;
      float log10_rec_q2_dnn = log10( dnn_Q2 ) ;

      float log10_rec_x_e  = log10( obs_x_e ) ;
      float log10_rec_q2_e = log10( obs_Q2_e ) ;

      float log10_rec_x_isigma  = log10( obs_x_ISigma  ) ;
      float log10_rec_q2_isigma = log10( obs_Q2_ISigma ) ;

      float log10_rec_x_da  = log10( obs_x_DA  ) ;
      float log10_rec_q2_da = log10( obs_Q2_DA ) ;

      int gen_gbi = h_all_gen_bins -> FindBin( log10_gen_x, log10_gen_q2 ) ;

      int rec_gbi_dnn = h_all_rec_bins_dnn -> FindBin( log10_rec_x_dnn, log10_rec_q2_dnn ) ;
      int rec_gbi_e   = h_all_rec_bins_e   -> FindBin( log10_rec_x_e, log10_rec_q2_e ) ;
      int rec_gbi_isigma = h_all_rec_bins_isigma -> FindBin( log10_rec_x_isigma, log10_rec_q2_isigma ) ;
      int rec_gbi_da = h_all_rec_bins_da -> FindBin( log10_rec_x_da, log10_rec_q2_da ) ;

      if ( verbose ) {
         printf("   %lld :  gen  log10(x) = %9.5f  log10(q2) = %9.5f   gbi %5d     rec  log10(x) = %9.5f  log10(q2) = %9.5f   gbi %5d\n",
            jentry, log10_gen_x, log10_gen_q2, gen_gbi,   log10_rec_x_dnn, log10_rec_q2_dnn, rec_gbi_dnn ) ;
      }

      h_all_gen_bins -> Fill( log10_gen_x, log10_gen_q2 ) ;

      h_all_rec_bins_dnn -> Fill( log10_rec_x_dnn, log10_rec_q2_dnn ) ;
      h_all_rec_bins_e -> Fill( log10_rec_x_e, log10_rec_q2_e ) ;
      h_all_rec_bins_isigma -> Fill( log10_rec_x_isigma, log10_rec_q2_isigma ) ;
      h_all_rec_bins_da -> Fill( log10_rec_x_da, log10_rec_q2_da ) ;

      if ( rec_gbi_dnn == gen_gbi ) {
         h_same_gen_bins_dnn -> Fill( log10_gen_x, log10_gen_q2 ) ;
         h_same_rec_bins_dnn -> Fill( log10_rec_x_dnn, log10_rec_q2_dnn ) ;
      }
      if ( rec_gbi_e == gen_gbi ) {
         h_same_gen_bins_e -> Fill( log10_gen_x, log10_gen_q2 ) ;
         h_same_rec_bins_e -> Fill( log10_rec_x_e, log10_rec_q2_e ) ;
      }
      if ( rec_gbi_isigma == gen_gbi ) {
         h_same_gen_bins_isigma -> Fill( log10_gen_x, log10_gen_q2 ) ;
         h_same_rec_bins_isigma -> Fill( log10_rec_x_isigma, log10_rec_q2_isigma ) ;
      }
      if ( rec_gbi_da == gen_gbi ) {
         h_same_gen_bins_da -> Fill( log10_gen_x, log10_gen_q2 ) ;
         h_same_rec_bins_da -> Fill( log10_rec_x_da, log10_rec_q2_da ) ;
      }

      if ( verbose && jentry > 50 ) verbose = false ;


   } // jentry

   TH2F* h_purity_dnn = (TH2F*) h_same_rec_bins_dnn -> Clone( "h_purity_dnn" ) ;
   h_purity_dnn -> SetTitle( "h_purity_dnn" ) ;
   h_purity_dnn -> Divide( h_all_rec_bins_dnn ) ;

   TH2F* h_purity_e = (TH2F*) h_same_rec_bins_e -> Clone( "h_purity_e" ) ;
   h_purity_e -> SetTitle( "h_purity_e" ) ;
   h_purity_e -> Divide( h_all_rec_bins_e ) ;

   TH2F* h_purity_isigma = (TH2F*) h_same_rec_bins_isigma -> Clone( "h_purity_isigma" ) ;
   h_purity_isigma -> SetTitle( "h_purity_isigma" ) ;
   h_purity_isigma -> Divide( h_all_rec_bins_isigma ) ;

   TH2F* h_purity_da = (TH2F*) h_same_rec_bins_da -> Clone( "h_purity_da" ) ;
   h_purity_da -> SetTitle( "h_purity_da" ) ;
   h_purity_da -> Divide( h_all_rec_bins_da ) ;


   TH2F* h_stability_dnn = (TH2F*) h_same_gen_bins_dnn -> Clone( "h_stability_dnn" ) ;
   h_stability_dnn -> SetTitle( "h_stability_dnn" ) ;
   h_stability_dnn -> Divide( h_all_gen_bins ) ;

   TH2F* h_stability_e = (TH2F*) h_same_gen_bins_e -> Clone( "h_stability_e" ) ;
   h_stability_e -> SetTitle( "h_stability_e" ) ;
   h_stability_e -> Divide( h_all_gen_bins ) ;

   TH2F* h_stability_isigma = (TH2F*) h_same_gen_bins_isigma -> Clone( "h_stability_isigma" ) ;
   h_stability_isigma -> SetTitle( "h_stability_isigma" ) ;
   h_stability_isigma -> Divide( h_all_gen_bins ) ;

   TH2F* h_stability_da = (TH2F*) h_same_gen_bins_da -> Clone( "h_stability_da" ) ;
   h_stability_da -> SetTitle( "h_stability_da" ) ;
   h_stability_da -> Divide( h_all_gen_bins ) ;




   h_purity_dnn -> SetMaximum(1.) ;
   h_purity_e -> SetMaximum(1.) ;
   h_purity_isigma -> SetMaximum(1.) ;
   h_purity_da -> SetMaximum(1.) ;

   h_stability_dnn -> SetMaximum(1.) ;
   h_stability_e -> SetMaximum(1.) ;
   h_stability_isigma -> SetMaximum(1.) ;
   h_stability_da -> SetMaximum(1.) ;

   h_purity_dnn -> SetMinimum(0.) ;
   h_purity_e -> SetMinimum(0.) ;
   h_purity_isigma -> SetMinimum(0.) ;
   h_purity_da -> SetMinimum(0.) ;

   h_stability_dnn -> SetMinimum(0.) ;
   h_stability_e -> SetMinimum(0.) ;
   h_stability_isigma -> SetMinimum(0.) ;
   h_stability_da -> SetMinimum(0.) ;


   gDirectory -> ls() ;




   saveHist( "p-and-s.root", "h*" ) ;

   draw_p_and_s( "p-and-s.root" ) ;



} // Loop
















