// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InteractiveTile.h"
#include "ChessController.generated.h"

class APiece;
class AChessPlayer;

/**
 * 
 */
UCLASS()
class POLE3D_API AChessController : public APlayerController
{
	GENERATED_BODY()

public:
    DECLARE_DELEGATE( FOnTurnEndDelegate )
	DECLARE_DELEGATE_RetVal_OneParam( TArray<AInteractiveTile*>, FOnSelectedPieceDelegate, APiece* )


public:
	AChessController();
	virtual void SetupInputComponent() override;

	void OnLeftMouseClick();
	void OnRightMouseClick();

	void UnselectPiece();
	void UnselectTile();

public:
	UPROPERTY()
	AChessPlayer* CurrentPlayer;

	UPROPERTY()
	APiece* SelectedPiece;
	
    UPROPERTY()
    AInteractiveTile* SelectedTile;

public:
	FOnTurnEndDelegate& OnTurnEndDelegate();
	FOnSelectedPieceDelegate& OnSelectedPieceDelegate();

private:
	FOnTurnEndDelegate TurnEndDelegate;
	FOnSelectedPieceDelegate SelectedPieceDelegate;
};
