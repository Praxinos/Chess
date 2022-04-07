#include "Pieces/ChessQueen.h"

AChessQueen::AChessQueen()
{
    ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Queen"));
    PieceMesh->SetStaticMesh(staticMeshFinder.Object);
}

TArray<FMove> AChessQueen::GetAvailableMoves()
{
    TArray<FMove> moves;

    moves.Add(FMove(FIntPoint(0, -1), 0, kCanKill, kBlocked, kExtend));
    moves.Add(FMove(FIntPoint(0, 1), 0, kCanKill, kBlocked, kExtend));
    moves.Add(FMove(FIntPoint(1, 0), 0, kCanKill, kBlocked, kExtend));
    moves.Add(FMove(FIntPoint(-1, 0), 0, kCanKill, kBlocked, kExtend));

    moves.Add(FMove(FIntPoint(1, 1), 0, kCanKill, kBlocked, kExtend));
    moves.Add(FMove(FIntPoint(1, -1), 0, kCanKill, kBlocked, kExtend));
    moves.Add(FMove(FIntPoint(-1, 1), 0, kCanKill, kBlocked, kExtend));
    moves.Add(FMove(FIntPoint(-1, -1), 0, kCanKill, kBlocked, kExtend));

    return moves;
}