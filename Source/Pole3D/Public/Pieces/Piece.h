#pragma once

#include "CoreMinimal.h"

#include "ChessColor.h"

#include "Piece.generated.h"

UCLASS(Abstract)
class APiece : public AActor
{
    GENERATED_BODY()

public:
    APiece();

public:
    void SetColor(EChessColor iColor);

public:
    UPROPERTY()
    EChessColor Color;

    UPROPERTY()
    UStaticMeshComponent* StaticMeshComponent;
};
