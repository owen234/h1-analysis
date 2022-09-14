


TH2*  calc_acceptance( TH2F* h_no_cuts, TH2F* h_sel, const char* h_acc_name = "h_acceptance" ) {

   if ( h_no_cuts == 0x0 ) { printf("\n\n *** bad input hist for h_no_cuts.\n\n" ) ; return 0x0 ; }
   if ( h_sel     == 0x0 ) { printf("\n\n *** bad input hist for h_sel.\n\n" ) ; return 0x0 ; }

   TH2* h_acc = (TH2*) h_sel -> Clone( h_acc_name ) ;
   h_acc -> SetTitle("Acceptance") ;

   h_acc -> Divide( h_no_cuts ) ;

   h_acc -> Draw("colz") ;

   return h_acc ;




} // 

