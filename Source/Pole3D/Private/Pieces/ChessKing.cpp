#include "Pieces/ChessKing.h"

AChessKing::AChessKing()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/King"));
	StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);
}