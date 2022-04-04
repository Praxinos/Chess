#include "Pieces/ChessKnight.h"

AChessKnight::AChessKnight()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Knight"));
	StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);
}

TArray<FMove> AChessKnight::GetPiecePossibleMoves()
{
    TArray<FMove> possibleMoves;

    possibleMoves.Add(FMove(kCanTakePiece, kJumpOverPieces, kFixedLength, FIntPoint(2, 1), 1));
    possibleMoves.Add(FMove(kCanTakePiece, kJumpOverPieces, kFixedLength, FIntPoint(2, -1), 1));
    possibleMoves.Add(FMove(kCanTakePiece, kJumpOverPieces, kFixedLength, FIntPoint(-2, 1), 1));
    possibleMoves.Add(FMove(kCanTakePiece, kJumpOverPieces, kFixedLength, FIntPoint(-2, -1), 1));

    possibleMoves.Add(FMove(kCanTakePiece, kJumpOverPieces, kFixedLength, FIntPoint(1, 2), 1));
    possibleMoves.Add(FMove(kCanTakePiece, kJumpOverPieces, kFixedLength, FIntPoint(-1, 2), 1));
    possibleMoves.Add(FMove(kCanTakePiece, kJumpOverPieces, kFixedLength, FIntPoint(1, -2), 1));
    possibleMoves.Add(FMove(kCanTakePiece, kJumpOverPieces, kFixedLength, FIntPoint(-1, -2), 1));

    return possibleMoves;
}