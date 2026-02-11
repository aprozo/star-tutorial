#include <TBranch.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>

// one may need to copy header files on personal laptop - instructions how to read your TTree
#include "../StRoot/StPicoDstAnalysisMaker/MyTreeEvent.h"
#include "../StRoot/StPicoDstAnalysisMaker/MyTrack.h"

#ifdef __CINT__
#pragma link C++ class MyTrack+;
#pragma link C++ class MyTreeEvent+;
#pragma link C++ class std::vector<MyTrack>+;
#endif

ClassImp(MyTrack)
ClassImp(MyTreeEvent)

void readMyTreeEvent(TString filename = "./output_tree.root")
{

  TFile *file = TFile::Open(filename, "READ");
  TTree *tree = (TTree *)file->Get("events");

  MyTreeEvent *event = new MyTreeEvent();
  tree->SetBranchAddress("MyTreeEvent", &event);

  Long64_t nEntries = tree->GetEntries();
  for (Long64_t i = 0; i < nEntries; i++)
  {
    tree->GetEntry(i);

    // Now you can access all members of your event
    std::cout << "\n--- Entry " << i << " ---" << std::endl;
    std::cout << "Run ID: " << event->runId << std::endl;
    std::cout << "Event ID: " << event->eventId << std::endl;
    std::cout << "Vertex Z: " << event->vertexZ << " cm " <<std::endl;

    // Access the track vectors
    std::cout << "Inclusive tracks: " << event->inclusiveTracks.size()
              << std::endl;
    if (event->inclusiveTracks.size() < 5)
      continue;

    for (size_t iTrack = 0; iTrack < 5; iTrack++) // print first tracks
    {
      std::cout << "Track pt: " << event->inclusiveTracks[iTrack].pt << " GeV/c"
                << ", eta: " << event->inclusiveTracks[iTrack].eta
                << ", phi: " << event->inclusiveTracks[iTrack].phi
                << ", charge: " << event->inclusiveTracks[iTrack].charge
                << std::endl;
    }

    // Break after first few events for demonstration
    if (i >= 4)
    {
      break;
    }
  }

  // Clean up
  delete event;
  file->Close();
}
