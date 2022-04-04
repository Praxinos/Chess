#pragma once

#include "CoreMinimal.h"
#include "Pieces/Piece.h"

#include "ChessController.generated.h"

class AChessPlayer;
class AInteractiveTile;
class AInteractiveBoard;

UCLASS(Blueprintable)
class AChessController : public APlayerController
{
    GENERATED_BODY()

public:
    DECLARE_DELEGATE( FOnTurnEndDelegate )
    DECLARE_DELEGATE_OneParam( FOnSelectedPieceDelegate, APiece* )

public:
    AChessController();

    virtual void SetupInputComponent() override;

    //Select Piece
    UFUNCTION()
    void OnLeftMouseClick();
    
    //Select Tile to move piece to
    UFUNCTION()
    void OnRightMouseClick();

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