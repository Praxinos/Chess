// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Board.h"
#include "ChessColor.h"

#include "Pole3DGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class POLE3D_API APole3DGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	//constructor
	APole3DGameModeBase();

public:
	/** Overridable native event for when play begins for this actor. */
	virtual void BeginPlay();

private:
	void CreateBoard();

	template<typename T>
	void AddPiece(int iX, int iY, EChessColor iColor);

	FTransform GetPieceTransform(int iX, int iY, int iRotationDegrees);
public:
	UPROPERTY()
	ABoard* Board;
};
