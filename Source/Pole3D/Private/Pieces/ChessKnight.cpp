#include "Pieces/ChessKnight.h"

AChessKnight::AChessKnight()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Knight"));
	StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);
}