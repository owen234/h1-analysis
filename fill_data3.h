//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Nov 19 08:15:12 2021 by ROOT version 6.24/01
// from TChain dnnout/
//////////////////////////////////////////////////////////

#ifndef fill_data3_h
#define fill_data3_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class fill_data3 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         tower_sum_40;
   Long64_t        n_towers_40;
   Float_t         eta_pho_closest_to_ebeam;
   Double_t        e_pho_closest_to_ebeam;
   Float_t         phi_pho_closest_to_ebeam;
   Float_t         obs_x_e;
   Float_t         obs_x_E0ESigma;
   Float_t         obs_x_E0ThetaSigma;
   Float_t         obs_x_DA;
   Float_t         obs_x_h;
   Float_t         obs_x_ISigma;
   Float_t         obs_x_IDA;
   Float_t         obs_x_ThetaSigmagamma;
   Float_t         obs_x_eSigma;
   Float_t         obs_y_e;
   Float_t         obs_y_E0ESigma;
   Float_t         obs_y_E0ThetaSigma;
   Float_t         obs_y_DA;
   Float_t         obs_y_h;
   Float_t         obs_y_ISigma;
   Float_t         obs_y_IDA;
   Float_t         obs_y_ThetaSigmagamma;
   Float_t         obs_y_eSigma;
   Float_t         obs_Q2_e;
   Float_t         obs_Q2_E0ESigma;
   Float_t         obs_Q2_E0ThetaSigma;
   Float_t         obs_Q2_DA;
   Float_t         obs_Q2_h;
   Float_t         obs_Q2_ISigma;
   Float_t         obs_Q2_IDA;
   Float_t         obs_Q2_ThetaSigmagamma;
   Float_t         obs_Q2_eSigma;
   Float_t         obs_e_e;
   Float_t         obs_e_pz;
   Float_t         obs_e_pt;
   Float_t         obs_e_phi;
   Float_t         obs_hfs_e;
   Float_t         obs_hfs_pz;
   Float_t         obs_hfs_pt;
   Float_t         obs_hfs_phi;
   Float_t         obs_dphi;
   Float_t         Empz;
   Float_t         obs_e_trk_e;
   Float_t         beam_e_e;
   Float_t         beam_p_e;
   Float_t         obs_hfs_Empz;
   Float_t         obs_e_Empz;
   Float_t         obs_event_Empz;
   Float_t         rot_pt1;
   Float_t         rot_pt2;
   Float_t         rot_Empz1;
   Float_t         rot_Empz2;
   Double_t        e_ecal_over_trk_ratio;
   Double_t        dphi_pho_closest_to_ebeam;
   Float_t         obs_ptbal;
   Float_t         obs_pzbal;
   Float_t         obs_hfs_theta;
   Float_t         dnn_x;
   Float_t         dnn_y;
   Float_t         dnn_Q2;

   // List of branches
   TBranch        *b_tower_sum_40;   //!
   TBranch        *b_n_towers_40;   //!
   TBranch        *b_eta_pho_closest_to_ebeam;   //!
   TBranch        *b_e_pho_closest_to_ebeam;   //!
   TBranch        *b_phi_pho_closest_to_ebeam;   //!
   TBranch        *b_obs_x_e;   //!
   TBranch        *b_obs_x_E0ESigma;   //!
   TBranch        *b_obs_x_E0ThetaSigma;   //!
   TBranch        *b_obs_x_DA;   //!
   TBranch        *b_obs_x_h;   //!
   TBranch        *b_obs_x_ISigma;   //!
   TBranch        *b_obs_x_IDA;   //!
   TBranch        *b_obs_x_ThetaSigmagamma;   //!
   TBranch        *b_obs_x_eSigma;   //!
   TBranch        *b_obs_y_e;   //!
   TBranch        *b_obs_y_E0ESigma;   //!
   TBranch        *b_obs_y_E0ThetaSigma;   //!
   TBranch        *b_obs_y_DA;   //!
   TBranch        *b_obs_y_h;   //!
   TBranch        *b_obs_y_ISigma;   //!
   TBranch        *b_obs_y_IDA;   //!
   TBranch        *b_obs_y_ThetaSigmagamma;   //!
   TBranch        *b_obs_y_eSigma;   //!
   TBranch        *b_obs_Q2_e;   //!
   TBranch        *b_obs_Q2_E0ESigma;   //!
   TBranch        *b_obs_Q2_E0ThetaSigma;   //!
   TBranch        *b_obs_Q2_DA;   //!
   TBranch        *b_obs_Q2_h;   //!
   TBranch        *b_obs_Q2_ISigma;   //!
   TBranch        *b_obs_Q2_IDA;   //!
   TBranch        *b_obs_Q2_ThetaSigmagamma;   //!
   TBranch        *b_obs_Q2_eSigma;   //!
   TBranch        *b_obs_e_e;   //!
   TBranch        *b_obs_e_pz;   //!
   TBranch        *b_obs_e_pt;   //!
   TBranch        *b_obs_e_phi;   //!
   TBranch        *b_obs_hfs_e;   //!
   TBranch        *b_obs_hfs_pz;   //!
   TBranch        *b_obs_hfs_pt;   //!
   TBranch        *b_obs_hfs_phi;   //!
   TBranch        *b_obs_dphi;   //!
   TBranch        *b_Empz;   //!
   TBranch        *b_obs_e_trk_e;   //!
   TBranch        *b_beam_e_e;   //!
   TBranch        *b_beam_p_e;   //!
   TBranch        *b_obs_hfs_Empz;   //!
   TBranch        *b_obs_e_Empz;   //!
   TBranch        *b_obs_event_Empz;   //!
   TBranch        *b_rot_pt1;   //!
   TBranch        *b_rot_pt2;   //!
   TBranch        *b_rot_Empz1;   //!
   TBranch        *b_rot_Empz2;   //!
   TBranch        *b_e_ecal_over_trk_ratio;   //!
   TBranch        *b_dphi_pho_closest_to_ebeam;   //!
   TBranch        *b_obs_ptbal;   //!
   TBranch        *b_obs_pzbal;   //!
   TBranch        *b_obs_hfs_theta;   //!
   TBranch        *b_dnn_x;   //!
   TBranch        *b_dnn_y;   //!
   TBranch        *b_dnn_Q2;   //!

   fill_data3(TTree *tree=0);
   virtual ~fill_data3();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop( const char* rur_file_name = "rapgap-for-q2-vs-y-gen012_obs024-0.05-obs-good.root" );
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef fill_data3_cxx
fill_data3::fill_data3(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("dnn-output-h1-v2-Data.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("dnn-output-h1-v2-Data.root");
      }
      f->GetObject("dnnout",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("dnnout","");
      chain->Add("dnn-output-h1-v2-Data.root/dnnout");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

fill_data3::~fill_data3()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t fill_data3::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t fill_data3::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void fill_data3::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("tower_sum_40", &tower_sum_40, &b_tower_sum_40);
   fChain->SetBranchAddress("n_towers_40", &n_towers_40, &b_n_towers_40);
   fChain->SetBranchAddress("eta_pho_closest_to_ebeam", &eta_pho_closest_to_ebeam, &b_eta_pho_closest_to_ebeam);
   fChain->SetBranchAddress("e_pho_closest_to_ebeam", &e_pho_closest_to_ebeam, &b_e_pho_closest_to_ebeam);
   fChain->SetBranchAddress("phi_pho_closest_to_ebeam", &phi_pho_closest_to_ebeam, &b_phi_pho_closest_to_ebeam);
   fChain->SetBranchAddress("obs_x_e", &obs_x_e, &b_obs_x_e);
   fChain->SetBranchAddress("obs_x_E0ESigma", &obs_x_E0ESigma, &b_obs_x_E0ESigma);
   fChain->SetBranchAddress("obs_x_E0ThetaSigma", &obs_x_E0ThetaSigma, &b_obs_x_E0ThetaSigma);
   fChain->SetBranchAddress("obs_x_DA", &obs_x_DA, &b_obs_x_DA);
   fChain->SetBranchAddress("obs_x_h", &obs_x_h, &b_obs_x_h);
   fChain->SetBranchAddress("obs_x_ISigma", &obs_x_ISigma, &b_obs_x_ISigma);
   fChain->SetBranchAddress("obs_x_IDA", &obs_x_IDA, &b_obs_x_IDA);
   fChain->SetBranchAddress("obs_x_ThetaSigmagamma", &obs_x_ThetaSigmagamma, &b_obs_x_ThetaSigmagamma);
   fChain->SetBranchAddress("obs_x_eSigma", &obs_x_eSigma, &b_obs_x_eSigma);
   fChain->SetBranchAddress("obs_y_e", &obs_y_e, &b_obs_y_e);
   fChain->SetBranchAddress("obs_y_E0ESigma", &obs_y_E0ESigma, &b_obs_y_E0ESigma);
   fChain->SetBranchAddress("obs_y_E0ThetaSigma", &obs_y_E0ThetaSigma, &b_obs_y_E0ThetaSigma);
   fChain->SetBranchAddress("obs_y_DA", &obs_y_DA, &b_obs_y_DA);
   fChain->SetBranchAddress("obs_y_h", &obs_y_h, &b_obs_y_h);
   fChain->SetBranchAddress("obs_y_ISigma", &obs_y_ISigma, &b_obs_y_ISigma);
   fChain->SetBranchAddress("obs_y_IDA", &obs_y_IDA, &b_obs_y_IDA);
   fChain->SetBranchAddress("obs_y_ThetaSigmagamma", &obs_y_ThetaSigmagamma, &b_obs_y_ThetaSigmagamma);
   fChain->SetBranchAddress("obs_y_eSigma", &obs_y_eSigma, &b_obs_y_eSigma);
   fChain->SetBranchAddress("obs_Q2_e", &obs_Q2_e, &b_obs_Q2_e);
   fChain->SetBranchAddress("obs_Q2_E0ESigma", &obs_Q2_E0ESigma, &b_obs_Q2_E0ESigma);
   fChain->SetBranchAddress("obs_Q2_E0ThetaSigma", &obs_Q2_E0ThetaSigma, &b_obs_Q2_E0ThetaSigma);
   fChain->SetBranchAddress("obs_Q2_DA", &obs_Q2_DA, &b_obs_Q2_DA);
   fChain->SetBranchAddress("obs_Q2_h", &obs_Q2_h, &b_obs_Q2_h);
   fChain->SetBranchAddress("obs_Q2_ISigma", &obs_Q2_ISigma, &b_obs_Q2_ISigma);
   fChain->SetBranchAddress("obs_Q2_IDA", &obs_Q2_IDA, &b_obs_Q2_IDA);
   fChain->SetBranchAddress("obs_Q2_ThetaSigmagamma", &obs_Q2_ThetaSigmagamma, &b_obs_Q2_ThetaSigmagamma);
   fChain->SetBranchAddress("obs_Q2_eSigma", &obs_Q2_eSigma, &b_obs_Q2_eSigma);
   fChain->SetBranchAddress("obs_e_e", &obs_e_e, &b_obs_e_e);
   fChain->SetBranchAddress("obs_e_pz", &obs_e_pz, &b_obs_e_pz);
   fChain->SetBranchAddress("obs_e_pt", &obs_e_pt, &b_obs_e_pt);
   fChain->SetBranchAddress("obs_e_phi", &obs_e_phi, &b_obs_e_phi);
   fChain->SetBranchAddress("obs_hfs_e", &obs_hfs_e, &b_obs_hfs_e);
   fChain->SetBranchAddress("obs_hfs_pz", &obs_hfs_pz, &b_obs_hfs_pz);
   fChain->SetBranchAddress("obs_hfs_pt", &obs_hfs_pt, &b_obs_hfs_pt);
   fChain->SetBranchAddress("obs_hfs_phi", &obs_hfs_phi, &b_obs_hfs_phi);
   fChain->SetBranchAddress("obs_dphi", &obs_dphi, &b_obs_dphi);
   fChain->SetBranchAddress("Empz", &Empz, &b_Empz);
   fChain->SetBranchAddress("obs_e_trk_e", &obs_e_trk_e, &b_obs_e_trk_e);
   fChain->SetBranchAddress("beam_e_e", &beam_e_e, &b_beam_e_e);
   fChain->SetBranchAddress("beam_p_e", &beam_p_e, &b_beam_p_e);
   fChain->SetBranchAddress("obs_hfs_Empz", &obs_hfs_Empz, &b_obs_hfs_Empz);
   fChain->SetBranchAddress("obs_e_Empz", &obs_e_Empz, &b_obs_e_Empz);
   fChain->SetBranchAddress("obs_event_Empz", &obs_event_Empz, &b_obs_event_Empz);
   fChain->SetBranchAddress("rot_pt1", &rot_pt1, &b_rot_pt1);
   fChain->SetBranchAddress("rot_pt2", &rot_pt2, &b_rot_pt2);
   fChain->SetBranchAddress("rot_Empz1", &rot_Empz1, &b_rot_Empz1);
   fChain->SetBranchAddress("rot_Empz2", &rot_Empz2, &b_rot_Empz2);
   fChain->SetBranchAddress("e_ecal_over_trk_ratio", &e_ecal_over_trk_ratio, &b_e_ecal_over_trk_ratio);
   fChain->SetBranchAddress("dphi_pho_closest_to_ebeam", &dphi_pho_closest_to_ebeam, &b_dphi_pho_closest_to_ebeam);
   fChain->SetBranchAddress("obs_ptbal", &obs_ptbal, &b_obs_ptbal);
   fChain->SetBranchAddress("obs_pzbal", &obs_pzbal, &b_obs_pzbal);
   fChain->SetBranchAddress("obs_hfs_theta", &obs_hfs_theta, &b_obs_hfs_theta);
   fChain->SetBranchAddress("dnn_x", &dnn_x, &b_dnn_x);
   fChain->SetBranchAddress("dnn_y", &dnn_y, &b_dnn_y);
   fChain->SetBranchAddress("dnn_Q2", &dnn_Q2, &b_dnn_Q2);
   Notify();
}

Bool_t fill_data3::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void fill_data3::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t fill_data3::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef fill_data3_cxx
