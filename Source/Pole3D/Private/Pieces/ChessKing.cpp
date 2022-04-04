#include "Pieces/ChessKing.h"

AChessKing::AChessKing()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/King"));
	StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);
}

TArray<FMove> AChessKing::GetPiecePossibleMoves()
{
    TArray<FMove> possibleMoves;

    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kFixedLength, FIntPoint(0, 1), 1));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kFixedLength, FIntPoint(0, -1), 1));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kFixedLength, FIntPoint(1, 0), 1));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kFixedLength, FIntPoint(-1, 0), 1));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kFixedLength, FIntPoint(1, 1), 1));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kFixedLength, FIntPoint(1, -1), 1));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kFixedLength, FIntPoint(-1, 1), 1));
    possibleMoves.Add(FMove(kCanTakePiece, kBlockedByPieces, kFixedLength, FIntPoint(-1, -1), 1));

    return possibleMoves;
}