#pragma once

#include "CoreMinimal.h"

#include "ChessPlayer.generated.h"

class AChessController;

UCLASS()
class AChessPlayer : public APawn
{
    GENERATED_BODY()

public:
    AChessPlayer();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY()
    AChessController* ChessController;

    UPROPERTY()
    bool bIsWhite;
};