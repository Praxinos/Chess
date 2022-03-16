#include "Pieces/ChessQueen.h"

AChessQueen::AChessQueen()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Queen"));
	StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);
}