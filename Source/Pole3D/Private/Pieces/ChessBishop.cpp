#include "Pieces/ChessBishop.h"

AChessBishop::AChessBishop()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Bishop"));
	StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);
}