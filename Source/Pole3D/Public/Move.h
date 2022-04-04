#pragma once

#include "CoreMinimal.h"

enum ETakeCondition
{
    kCanTakePiece,
    kCantTakePiece,
    kMustTakePiece
};

enum EMoveCondition
{
    kJumpOverPieces,
    kBlockedByPieces
};

enum EMoveLengthCondition
{
    kFixedLength,
    kEqualOrUnderLength
};

struct FMove
{
    FMove(ETakeCondition iTakeCondition, EMoveCondition iMoveCondition, EMoveLengthCondition iMoveLengthCondition, FIntPoint iMoveDirection, uint32 iMoveLength)
    : TakeCondition( iTakeCondition ),
      MoveCondition( iMoveCondition ),
      MoveLengthCondition( iMoveLengthCondition ),
      MoveUnitVector( iMoveDirection ),
      MoveLength( iMoveLength )
    {
    }

    ETakeCondition TakeCondition;
    EMoveCondition MoveCondition;
    EMoveLengthCondition MoveLengthCondition;

    FIntPoint MoveUnitVector;
    uint32 MoveLength;
};