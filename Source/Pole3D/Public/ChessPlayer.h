// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "ChessPlayer.generated.h"

UCLASS()
class POLE3D_API AChessPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AChessPlayer();

    void Init(bool iIsWhite, int iSizeX, int iSizeY, int iAssetSize );

public:
	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY()
	bool IsWhite;
};
