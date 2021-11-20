
#include "draw_reso_vs_log10y.c"


   void run_draw_reso_vs_log10y_h1( const char* input_root_file = "dnn-output-h1-v2-Rapgap.root" ) {

      draw_reso_vs_log10y( "x", "", input_root_file, "h1", 800 ) ;
///   draw_reso_vs_log10y( "x", "has_norad" , input_root_file, "h1", 600) ;
///   draw_reso_vs_log10y( "x", "has_isr" , input_root_file, "h1", 600) ;
///   draw_reso_vs_log10y( "x", "has_fsr" , input_root_file, "h1", 600) ;

      draw_reso_vs_log10y( "y", "" , input_root_file, "h1", 800) ;
///   draw_reso_vs_log10y( "y", "has_norad" , input_root_file, "h1", 600) ;
///   draw_reso_vs_log10y( "y", "has_isr" , input_root_file, "h1", 600) ;
///   draw_reso_vs_log10y( "y", "has_fsr" , input_root_file, "h1", 600) ;

      draw_reso_vs_log10y( "Q2", "" , input_root_file, "h1", 800) ;
///   draw_reso_vs_log10y( "q2", "has_norad" , input_root_file, "h1", 600) ;
///   draw_reso_vs_log10y( "q2", "has_isr" , input_root_file, "h1", 600) ;
///   draw_reso_vs_log10y( "q2", "has_fsr" , input_root_file, "h1", 600) ;


   }
