#include "Pieces/ChessRook.h"

AChessRook::AChessRook()
{
    ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Rook"));
    PieceMesh->SetStaticMesh(staticMeshFinder.Object);
}

TArray<FMove> AChessRook::GetAvailableMoves()
{
    TArray<FMove> moves;

    moves.Add(FMove(FIntPoint(0, -1), 0, kCanKill, kBlocked, kExtend));
    moves.Add(FMove(FIntPoint(0, 1), 0, kCanKill, kBlocked, kExtend));
    moves.Add(FMove(FIntPoint(1, 0), 0, kCanKill, kBlocked, kExtend));
    moves.Add(FMove(FIntPoint(-1, 0), 0, kCanKill, kBlocked, kExtend));

    return moves;
}