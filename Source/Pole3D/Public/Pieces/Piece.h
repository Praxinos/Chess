// Fill out your copyright notice in the Description page of Project Settings.

/* ---------------------------------------------------------------------- */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Move.h"
#include "Piece.generated.h"

class AInteractiveTile;

UCLASS(Abstract)
class POLE3D_API APiece : public AActor
{
    GENERATED_BODY()

public: 
    APiece();

public:
    void SetColor( bool iIsWhite );

    void Select();
    void Unselect();

    AInteractiveTile* GetTileOfPiece();

    virtual TArray<FMove> GetAvailableMoves();

public:
    UPROPERTY()
    UStaticMeshComponent* PieceMesh;

    UPROPERTY()
    bool IsWhite;

    UPROPERTY()
    bool IsFirstMove;
};