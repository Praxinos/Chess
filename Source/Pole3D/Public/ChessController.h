#pragma once

#include "CoreMinimal.h"

#include "ChessController.generated.h"

class AChessPlayer;

UCLASS(Blueprintable)
class AChessController : public APlayerController
{
    GENERATED_BODY()

public:
    AChessController();

    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    UFUNCTION()
    void OnLeftMouseClick();

    UFUNCTION()
    void OnRightMouseClick();

public:
    UPROPERTY()
    AChessPlayer* PlayerOne;

    UPROPERTY()
    AChessPlayer* PlayerTwo;

    UPROPERTY()
    AChessPlayer* CurrentPlayer;
};