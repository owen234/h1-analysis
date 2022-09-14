
#include "TFile.h"
#include "TH1F.h"


int main() {

   TH1F* hp = new TH1F("h","htitle", 10, 0., 5. ) ;
   TFile* tf = new TFile("simple.root", "RECREATE" ) ;
   hp->Write() ;
   tf->Close() ;

   return 0 ;

}
