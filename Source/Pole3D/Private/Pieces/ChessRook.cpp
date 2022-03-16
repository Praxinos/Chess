#include "Pieces/ChessRook.h"

AChessRook::AChessRook()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Rook"));
	StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);
}