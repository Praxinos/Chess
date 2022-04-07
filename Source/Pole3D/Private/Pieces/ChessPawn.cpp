// Fill out your copyright notice in the Description page of Project Settings.


#include "Pieces/ChessPawn.h"

AChessPawn::AChessPawn()
{
    ConstructorHelpers::FObjectFinder<UStaticMesh> staticMesh(TEXT("/Game/Meshes/Pawn"));
    PieceMesh->SetStaticMesh( staticMesh.Object );
}

TArray<FMove> AChessPawn::GetAvailableMoves()
{
    TArray<FMove> moves;
    if (IsWhite)
    {
        moves.Add(FMove(FIntPoint(0, 1), 1, kCantKill, kBlocked, kFixed ));
        moves.Add(FMove(FIntPoint(1, 1), 1, kMustKill, kBlocked, kFixed ));
        moves.Add(FMove(FIntPoint(-1, 1), 1, kMustKill, kBlocked, kFixed ));
        
        if( IsFirstMove )
            moves.Add(FMove(FIntPoint(0, 1), 2, kCantKill, kBlocked, kFixed));
    }
    else
    {
        moves.Add(FMove(FIntPoint(0, -1), 1, kCantKill, kBlocked, kFixed));
        moves.Add(FMove(FIntPoint(1, -1), 1, kMustKill, kBlocked, kFixed));
        moves.Add(FMove(FIntPoint(-1, -1), 1, kMustKill, kBlocked, kFixed));

        if (IsFirstMove)
            moves.Add(FMove(FIntPoint(0, -1), 2, kCantKill, kBlocked, kFixed));
    }

    return moves;
}
