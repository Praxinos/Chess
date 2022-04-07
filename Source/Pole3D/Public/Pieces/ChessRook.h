#pragma once

#include "Piece.h"

#include "ChessRook.generated.h"

UCLASS()
class AChessRook : public APiece
{
    GENERATED_BODY()

public:
    AChessRook();

    TArray<FMove> GetAvailableMoves() override;

};
