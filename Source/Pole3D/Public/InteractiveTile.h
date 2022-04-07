// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveTile.generated.h"

class APiece;

UCLASS()
class POLE3D_API AInteractiveTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveTile();

    void Select();
    void Unselect();

    APiece* GetPieceOnTile();

public:
    UPROPERTY()
    UStaticMeshComponent* TileMesh;

    UPROPERTY()
    bool IsSelected;
};
