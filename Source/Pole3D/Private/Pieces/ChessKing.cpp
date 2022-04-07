#include "Pieces/ChessKing.h"

AChessKing::AChessKing()
{
    ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/King"));
    PieceMesh->SetStaticMesh(staticMeshFinder.Object);
}

TArray<FMove> AChessKing::GetAvailableMoves()
{
    TArray<FMove> moves;

    moves.Add(FMove(FIntPoint(0, -1), 1, kCanKill, kBlocked, kFixed));
    moves.Add(FMove(FIntPoint(0, 1), 1, kCanKill, kBlocked, kFixed));
    moves.Add(FMove(FIntPoint(1, 0), 1, kCanKill, kBlocked, kFixed));
    moves.Add(FMove(FIntPoint(-1, 0), 1, kCanKill, kBlocked, kFixed));

    moves.Add(FMove(FIntPoint(1, 1), 1, kCanKill, kBlocked, kFixed));
    moves.Add(FMove(FIntPoint(1, -1), 1, kCanKill, kBlocked, kFixed));
    moves.Add(FMove(FIntPoint(-1, 1), 1, kCanKill, kBlocked, kFixed));
    moves.Add(FMove(FIntPoint(-1, -1), 1, kCanKill, kBlocked, kFixed));

    return moves;
}