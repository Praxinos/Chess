// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Board.h"
#include "ChessGameModeBase.generated.h"

class AChessPlayer;
class AChessController;
class AChessKing;

/**
 * 
 */
UCLASS()
class POLE3D_API AChessGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AChessGameModeBase();

	virtual void BeginPlay();

	void SetupBoard();

	template< typename T >
	T* AddPiece( int iX, int iY, bool iIsWhite );

	FTransform GetPieceTransform( int iX, int iY, int iRotationDegrees );

public:
	void SwitchPlayer();

	TArray<AInteractiveTile*> GetTilesPieceCanMoveTo( APiece* iPiece );

    bool IsTileDangerousAfterMove( AInteractiveTile* iTileToCheck, APiece* iPieceToMove, AInteractiveTile* iTileToMoveTo );

    bool IsInCheckMate();

public:
	UPROPERTY()
	ABoard* Board;

	UPROPERTY()
	AChessPlayer* PlayerOne;

    UPROPERTY()
    AChessPlayer* PlayerTwo;

	UPROPERTY()
	AChessKing* PlayerOneKing;

    UPROPERTY()
	AChessKing* PlayerTwoKing;

	UPROPERTY()
	AChessController* ChessController;
};
