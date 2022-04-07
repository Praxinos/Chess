#include "Pieces/ChessBishop.h"

AChessBishop::AChessBishop()
{
    ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Bishop"));
    PieceMesh->SetStaticMesh(staticMeshFinder.Object);
}

TArray<FMove> AChessBishop::GetAvailableMoves()
{
    TArray<FMove> moves;

    moves.Add(FMove(FIntPoint(1, 1), 0, kCanKill, kBlocked, kExtend));
    moves.Add(FMove(FIntPoint(1, -1), 0, kCanKill, kBlocked, kExtend));
    moves.Add(FMove(FIntPoint(-1, 1), 0, kCanKill, kBlocked, kExtend));
    moves.Add(FMove(FIntPoint(-1, -1), 0, kCanKill, kBlocked, kExtend));

    return moves;
}