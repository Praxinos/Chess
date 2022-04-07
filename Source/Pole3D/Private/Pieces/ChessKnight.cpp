#include "Pieces/ChessKnight.h"

AChessKnight::AChessKnight()
{
    ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Knight"));
    PieceMesh->SetStaticMesh(staticMeshFinder.Object);
}

TArray<FMove> AChessKnight::GetAvailableMoves()
{
    TArray<FMove> moves;

    moves.Add(FMove(FIntPoint(1, 2), 1, kCanKill, kJump, kFixed));
    moves.Add(FMove(FIntPoint(1, -2), 1, kCanKill, kJump, kFixed));
    moves.Add(FMove(FIntPoint(-1, 2), 1, kCanKill, kJump, kFixed));
    moves.Add(FMove(FIntPoint(-1, -2), 1, kCanKill, kJump, kFixed));

    moves.Add(FMove(FIntPoint(2, 1), 1, kCanKill, kJump, kFixed));
    moves.Add(FMove(FIntPoint(2, -1), 1, kCanKill, kJump, kFixed));
    moves.Add(FMove(FIntPoint(-2, 1), 1, kCanKill, kJump, kFixed));
    moves.Add(FMove(FIntPoint(-2, -1), 1, kCanKill, kJump, kFixed));

    return moves;
}