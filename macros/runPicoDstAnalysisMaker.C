// C++ headers
#include <iostream>

//_________________
void runPicoDstAnalysisMaker(TString inFileName = "/workspaces/star-tutorial/st_physics_20069002_raw_1500008.picoDst.root", 
                            TString outFileName = "output_tree.root",
                            const int maxEvents = 10) {

  // Load all the STAR libraries
  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();

  gSystem->Load("StPicoEvent");
  gSystem->Load("StPicoDstMaker");
  gSystem->AddDynamicPath(gSystem->ExpandPathName("$PWD/.sl79_gcc485/LIB"));
  gSystem->Load("StPicoDstAnalysisMaker");

  StChain *chain = new StChain();
  StPicoDstMaker *picoMaker = new StPicoDstMaker(2, inFileName, "picoDst");
  StPicoDstAnalysisMaker *anaMaker = new StPicoDstAnalysisMaker(picoMaker, outFileName);
  anaMaker->setVtxZ(-40., 40.);

  if (chain->Init() == kStErr) {
    std::cout << "[ERROR] Chain initialization failed." << std::endl;
    return;
  }

  const Int_t totalEntries = picoMaker->chain()->GetEntries();
  const Int_t nEvents = (maxEvents > 0 && maxEvents < totalEntries) ? maxEvents : totalEntries; 

  for (Int_t iEvent = 0; iEvent < nEvents; ++iEvent) {
    chain->Clear();
    const Int_t status = chain->Make();
    if (status) {
      std::cout << "[WARN] Stopped early at event " << iEvent << " (status " << status << ")" << std::endl;
      break;
    }
  }
  chain->Finish();
}
