
#include "histio.c"

#include "draw_2d_slice_plots.c"
#include "fill_h1_rxsec_th2.c"
#include "utils.c"


void compare_h1qcdfunc_with_h1( const char* h1qcdfunc_file = "cbc-output.root" ) {

   gDirectory -> Delete( "h*" ) ;

   loadHist( h1qcdfunc_file ) ;

   fill_h1_rxsec_th2() ;

   TH2F* h_h1qcdfunc = get_hist2d( "h_rxsec" ) ;

   TH2F* h_h1 = get_hist2d( "h_h1_rxsec" ) ;

   //draw_2d_slice_plots( h_h1qcdfunc, h_h1 ) ;
   draw_2d_slice_plots( h_h1, h_h1qcdfunc ) ;


}


