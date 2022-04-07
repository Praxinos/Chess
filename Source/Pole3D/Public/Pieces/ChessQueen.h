#pragma once

#include "Piece.h"

#include "ChessQueen.generated.h"

UCLASS()
class AChessQueen : public APiece
{
    GENERATED_BODY()

public:
    AChessQueen();

    TArray<FMove> GetAvailableMoves() override;
};
