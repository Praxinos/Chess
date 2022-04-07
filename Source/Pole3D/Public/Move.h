// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum EKillCondition
{
    kCanKill,
    kCantKill,
    kMustKill
};

enum EMoveCondition
{
    kJump,
    kBlocked
};

enum EExtendMove
{
    kFixed,
    kExtend
};


struct FMove
{
    FMove(FIntPoint iMoveVector, int iLength, EKillCondition iKillCondition, EMoveCondition iMoveCondition, EExtendMove iExtendMove)
    {
        MoveVector = iMoveVector;
        Length = iLength;
        KillCondition = iKillCondition;
        MoveCondition = iMoveCondition;
        ExtendMove = iExtendMove;
    }

    FIntPoint MoveVector;
    int Length;
    EKillCondition KillCondition;
    EMoveCondition MoveCondition;
    EExtendMove ExtendMove;
};