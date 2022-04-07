// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveTile.h"

#include "Board.generated.h"

UCLASS()
class POLE3D_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoard();

	void Init( int iSizeX, int iSizeY, int iAssetSize, UStaticMesh* iWhiteTileMesh, UStaticMesh* iBlackTileMesh );

	void GenerateBoard();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SizeX;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int SizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AssetSize;

	UPROPERTY( EditAnywhere )
	UInstancedStaticMeshComponent* WhiteTileInstancedMesh;

    UPROPERTY(EditAnywhere)
    UInstancedStaticMeshComponent* BlackTileInstancedMesh;

	UPROPERTY()
	UStaticMesh* WhiteTileMesh;

    UPROPERTY()
    UStaticMesh* BlackTileMesh;

	TMap<FIntPoint, AInteractiveTile*> Tiles;
};
