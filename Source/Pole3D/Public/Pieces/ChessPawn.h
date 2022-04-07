// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pieces/Piece.h"
#include "ChessPawn.generated.h"

/**
 * 
 */
UCLASS()
class POLE3D_API AChessPawn : public APiece
{
	GENERATED_BODY()
	
public:
	AChessPawn();

	TArray<FMove> GetAvailableMoves() override;
};
