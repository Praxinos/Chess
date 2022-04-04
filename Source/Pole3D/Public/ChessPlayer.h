#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"

#include "ChessPlayer.generated.h"

class AChessController;

UCLASS()
class AChessPlayer : public APawn
{
    GENERATED_BODY()

public:
    AChessPlayer();

public:
    UPROPERTY()
    bool bIsWhite;

    UPROPERTY()
    UCameraComponent* Camera;
};