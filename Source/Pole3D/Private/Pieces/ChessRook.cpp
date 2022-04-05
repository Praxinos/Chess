#include "Pieces/ChessRook.h"

AChessRook::AChessRook()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Rook"));
	StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);
}

TArray<FMove> AChessRook::GetPiecePossibleMoves()
{
    TArray<FMove> possibleMoves;

    //TODO: Change 8 by size of Board
    possibleMoves.Add(FMove(kCanTakePiece, kCanBeTaken, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(0, 1), 8));
    possibleMoves.Add(FMove(kCanTakePiece, kCanBeTaken, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(0, -1), 8));
    possibleMoves.Add(FMove(kCanTakePiece, kCanBeTaken, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(1, 0), 8));
    possibleMoves.Add(FMove(kCanTakePiece, kCanBeTaken, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(-1, 0), 8));

    return possibleMoves;
}