#pragma once

#include "Piece.h"

#include "ChessQueen.generated.h"

UCLASS()
class AChessQueen : public APiece
{
    GENERATED_BODY()

public:
    AChessQueen();

    virtual TArray<FMove> GetPiecePossibleMoves() override;
};
