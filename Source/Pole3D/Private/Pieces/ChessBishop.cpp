#include "Pieces/ChessBishop.h"

AChessBishop::AChessBishop()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Bishop"));
	StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);
}

TArray<FMove> AChessBishop::GetPiecePossibleMoves()
{
    TArray<FMove> possibleMoves;

    //TODO: Change 8 by size of Board
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(1, 1), 8));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(1, -1), 8));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(-1, 1), 8));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(-1, -1), 8));

    return possibleMoves;
}