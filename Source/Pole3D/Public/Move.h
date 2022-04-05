#pragma once

#include "CoreMinimal.h"

enum ETakeCondition
{
    kCanTakePiece,
    kCantTakePiece,
    kMustTakePiece
};

enum ETakenCondition
{
    kCantBeTaken,
    kCanBeTaken
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
    FMove(ETakeCondition iTakeCondition, ETakenCondition iTakenCondition, EMoveCondition iMoveCondition, EMoveLengthCondition iMoveLengthCondition, FIntPoint iMoveDirection, uint32 iMoveLength)
    : TakeCondition( iTakeCondition ),
      TakenCondition( iTakenCondition ),
      MoveCondition( iMoveCondition ),
      MoveLengthCondition( iMoveLengthCondition ),
      MoveUnitVector( iMoveDirection ),
      MoveLength( iMoveLength )
    {
    }

    ETakeCondition TakeCondition;
    ETakenCondition TakenCondition;
    EMoveCondition MoveCondition;
    EMoveLengthCondition MoveLengthCondition;

    FIntPoint MoveUnitVector;
    uint32 MoveLength;
};