#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) 
{}

MySensitiveDetector::~MySensitiveDetector() 
{}


G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhis)
{

    G4Track *track = aStep->GetTrack();
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber();
    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    G4double energyDeposit = aStep->GetTotalEnergyDeposit();

    // if (energyDeposit != 0.){
    //     G4cout << "Hit in sensitive detector!" << G4endl;
    //     G4cout << "Particle: " << track->GetDefinition()->GetParticleName() << G4endl;
    //     G4cout << "Particle:-" << track->GetTrackID() << G4endl;
    //     G4cout << "Energy Deposit: " << energyDeposit << " MeV" << G4endl;
    // };



 
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();



       
        G4AnalysisManager *man = G4AnalysisManager::Instance();
        man->FillNtupleIColumn(0, evt);
        man->FillNtupleIColumn(1, track->GetTrackID()); 
        man->FillNtupleDColumn(2, posDetector[0]);
        man->FillNtupleDColumn(3, posDetector[1]);
        man->FillNtupleDColumn(4, posDetector[2]);
        man->FillNtupleDColumn(5, energyDeposit);
        man->FillNtupleSColumn(6, track->GetDefinition()->GetParticleName());

        man->AddNtupleRow(0);



    return true;
}


