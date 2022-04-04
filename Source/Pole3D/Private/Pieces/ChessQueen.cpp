#include "Pieces/ChessQueen.h"

AChessQueen::AChessQueen()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Queen"));
	StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);
}

TArray<FMove> AChessQueen::GetPiecePossibleMoves()
{
    TArray<FMove> possibleMoves;

    //TODO: Change 8 by size of Board
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(0, 1), 8));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(0, -1), 8));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(1, 0), 8));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(-1, 0), 8));

    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(1, 1), 8));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(1, -1), 8));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(-1, 1), 8));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kEqualOrUnderLength, FIntPoint(-1, -1), 8));

    return possibleMoves;
}