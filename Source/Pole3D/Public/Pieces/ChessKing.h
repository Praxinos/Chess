#pragma once

#include "Piece.h"

#include "ChessKing.generated.h"

UCLASS()
class AChessKing : public APiece
{
    GENERATED_BODY()

public:
    AChessKing();

    TArray<FMove> GetAvailableMoves() override;

};
