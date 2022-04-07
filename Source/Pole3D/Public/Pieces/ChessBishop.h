#pragma once

#include "Piece.h"

#include "ChessBishop.generated.h"

UCLASS()
class AChessBishop : public APiece
{
    GENERATED_BODY()

public:
    AChessBishop();

    TArray<FMove> GetAvailableMoves() override;
};
