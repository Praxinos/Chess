// Copyright Epic Games, Inc. All Rights Reserved.

#include "Pole3DGameModeBase.h"

#include "ChessController.h"
#include "Pieces/ChessPawn.h"
#include "Pieces/ChessRook.h"
#include "Pieces/ChessKnight.h"
#include "Pieces/ChessBishop.h"
#include "Pieces/ChessQueen.h"
#include "Pieces/ChessKing.h"



APole3DGameModeBase::APole3DGameModeBase()
	: Super()
{
	PlayerControllerClass = AChessController::StaticClass();
}

void
APole3DGameModeBase::BeginPlay()
{
	CreateBoard();
}

void
APole3DGameModeBase::CreateBoard()
{
    //Theory: we're having a 8 * 8 checkboard

	Board = GetWorld()->SpawnActor<ABoard>();

	UStaticMesh* whiteTileMesh = LoadObject<UStaticMesh>(Board, TEXT("/Game/WhiteTileMesh"));
	UStaticMesh* blackTileMesh = LoadObject<UStaticMesh>(Board, TEXT("/Game/BlackTileMesh"));
	Board->Init(8, 8, 100, whiteTileMesh, blackTileMesh);
	
	//White line of pawns
	for (int x = 0; x < Board->Width; x++)
	{
		AddPiece<AChessPawn>(x, 1, EChessColor::White);
	}

	AddPiece<AChessRook>(0, 0, EChessColor::White);
    AddPiece<AChessRook>(Board->Width - 1, 0, EChessColor::White);
    AddPiece<AChessKnight>(1, 0, EChessColor::White);
    AddPiece<AChessKnight>(Board->Width - 2, 0, EChessColor::White);
    AddPiece<AChessBishop>(2, 0, EChessColor::White);
    AddPiece<AChessBishop>(Board->Width - 3, 0, EChessColor::White);
    AddPiece<AChessQueen>(3, 0, EChessColor::White);
    AddPiece<AChessKing>(Board->Width - 4, 0, EChessColor::White);

	//Black line of pawns
	for (int x = 0; x < Board->Width; x++)
	{
		AddPiece<AChessPawn>(x, Board->Height - 2, EChessColor::Black);
	}

    AddPiece<AChessRook>( 0, Board->Height - 1, EChessColor::Black);
    AddPiece<AChessRook>( Board->Width - 1, Board->Height - 1, EChessColor::Black);
    AddPiece<AChessKnight>( 1, Board->Height - 1, EChessColor::Black);
    AddPiece<AChessKnight>( Board->Width - 2, Board->Height - 1, EChessColor::Black);
    AddPiece<AChessBishop>( 2, Board->Height - 1, EChessColor::Black);
    AddPiece<AChessBishop>( Board->Width - 3, Board->Height - 1, EChessColor::Black);
    AddPiece<AChessKing>( 3, Board->Height - 1, EChessColor::Black);
    AddPiece<AChessQueen>( Board->Width - 4, Board->Height - 1, EChessColor::Black);
}

template<typename T>
void
APole3DGameModeBase::AddPiece(int iX, int iY, EChessColor iColor)
{
	APiece* piece = GetWorld()->SpawnActor<T>(T::StaticClass(), GetPieceTransform(iX, iY, iColor == EChessColor::White ? 0 : 180));
	piece->SetColor(iColor);

	piece->AttachToActor(Board, FAttachmentTransformRules::KeepRelativeTransform, "");

	Board->Tiles.Add(piece);
}

FTransform
APole3DGameModeBase::GetPieceTransform(int iX, int iY, int iRotationDegrees)
{
	FVector t(Board->Spacing * iX, Board->Spacing * iY, 0);
	return FTransform(FRotator( 0, iRotationDegrees, 0 ), t, FVector(0.25, 0.25, 0.25));
}