#include "generator.hh"
#include "Randomize.hh"  // Include this for random number generation

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "pi0";
    G4ParticleDefinition *particle = particleTable->FindParticle("pi0");

    G4ThreeVector pos(0., 0., -20. * cm);

    // Generate random angles and random energy
    G4double theta = G4UniformRand() * 180.0 * deg; // Random polar angle in the range [0, 180] degrees
    G4double phi = G4UniformRand() * 360.0 * deg;   // Random azimuthal angle in the range [0, 360] degrees
    G4double energy = G4UniformRand() * 1.0 * GeV; // Random energy up to 1.0 GeV

    // Calculate momentum direction that projects onto +z direction
    G4ThreeVector mom(0.0, 0.0, 1.0);

    // Rotate momentum direction by the random polar angle around y-axis
    mom.rotateY(theta);

    // Rotate momentum direction by the random azimuthal angle around z-axis
    mom.rotateZ(phi);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(energy);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
