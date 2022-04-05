// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Board.h"
#include "ChessPlayer.h"

#include "Pole3DGameModeBase.generated.h"

/**
 * 
 */

class APiece;

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
	/** Board Setup */
	void CreateBoard();

	template<typename T>
	void AddPiece(int iX, int iY, bool iIsWhite);

	FTransform GetPieceTransform(int iX, int iY, int iRotationDegrees);

	/** Players Setup */
	void CreatePlayers();

public:
	/** Utility functions */
	void TurnEnd();

	void CheckAndHighlightPossibleMovesForPiece( APiece* iPiece );

	//Check if Tile is dangerous for said piece. Simulate the fact that we move iPiece to iTile and check if this move is dangerous
	bool IsTileDangerousForPiece( APiece* iPiece, AInteractiveTile* iTile );

	void RemoveHighlightBoard();

public:
	UPROPERTY()
	ABoard* Board;

    UPROPERTY()
	AChessController* PlayerController;

    UPROPERTY()
    AChessPlayer* PlayerOne;

    UPROPERTY()
    AChessPlayer* PlayerTwo;
};
