
#include "draw_reso_vs_log10x_2dh.c"


   void run_draw_reso_vs_log10x_2dh_h1( const char* input_root_file = "dnn-output-h1-v2-Rapgap.root" ) {

      draw_reso_vs_log10x_2dh( "x", "wgt", input_root_file, "h1", 800 ) ;
///   draw_reso_vs_log10x_2dh( "x", "has_norad" , input_root_file, "h1", 600) ;
///   draw_reso_vs_log10x_2dh( "x", "has_isr" , input_root_file, "h1", 600) ;
///   draw_reso_vs_log10x_2dh( "x", "has_fsr" , input_root_file, "h1", 600) ;

      draw_reso_vs_log10x_2dh( "y", "wgt" , input_root_file, "h1", 800) ;
///   draw_reso_vs_log10x_2dh( "y", "has_norad" , input_root_file, "h1", 600) ;
///   draw_reso_vs_log10x_2dh( "y", "has_isr" , input_root_file, "h1", 600) ;
///   draw_reso_vs_log10x_2dh( "y", "has_fsr" , input_root_file, "h1", 600) ;

      draw_reso_vs_log10x_2dh( "Q2", "wgt" , input_root_file, "h1", 800) ;
///   draw_reso_vs_log10x_2dh( "Q2", "has_norad" , input_root_file, "h1", 600) ;
///   draw_reso_vs_log10x_2dh( "Q2", "has_isr" , input_root_file, "h1", 600) ;
///   draw_reso_vs_log10x_2dh( "Q2", "has_fsr" , input_root_file, "h1", 600) ;


   }
