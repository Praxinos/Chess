#include "Pieces/ChessPawn.h"

AChessPawn::AChessPawn()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Pawn"));
	StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);
}