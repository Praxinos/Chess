// Copyright Epic Games, Inc. All Rights Reserved.

#include "Pole3DGameModeBase.h"

#include "ChessController.h"
#include "Pieces/ChessPawn.h"
#include "Pieces/ChessRook.h"
#include "Pieces/ChessKnight.h"
#include "Pieces/ChessBishop.h"
#include "Pieces/ChessQueen.h"
#include "Pieces/ChessKing.h"
#include "InteractiveTile.h"


APole3DGameModeBase::APole3DGameModeBase()
	: Super()
{
	PlayerControllerClass = AChessController::StaticClass();
	DefaultPawnClass = AChessPlayer::StaticClass();
}

void
APole3DGameModeBase::BeginPlay()
{
	PlayerController = GetWorld()->GetFirstPlayerController<AChessController>();
	PlayerController->OnTurnEndDelegate().BindUObject(this, &APole3DGameModeBase::TurnEnd);
    PlayerController->OnSelectedPieceDelegate().BindUObject(this, &APole3DGameModeBase::CheckAndHighlightPossibleMovesForPiece);

	CreateBoard();

	CreatePlayers();
}

void
APole3DGameModeBase::CreateBoard()
{
	Board = GetWorld()->SpawnActor<ABoard>();

	UStaticMesh* whiteTileMesh = LoadObject<UStaticMesh>(Board, TEXT("/Game/Meshes/WhiteTileMesh"));
	UStaticMesh* blackTileMesh = LoadObject<UStaticMesh>(Board, TEXT("/Game/Meshes/BlackTileMesh"));
	Board->Init(8, 8, 100, whiteTileMesh, blackTileMesh);
	
	//White line of pawns
	for (int x = 0; x < Board->Width; x++)
	{
		AddPiece<AChessPawn>(x, 1, true);
	}

	AddPiece<AChessRook>(0, 0, true);
    AddPiece<AChessRook>(Board->Width - 1, 0, true);
    AddPiece<AChessKnight>(1, 0, true);
    AddPiece<AChessKnight>(Board->Width - 2, 0, true);
    AddPiece<AChessBishop>(2, 0, true);
    AddPiece<AChessBishop>(Board->Width - 3, 0, true);
    AddPiece<AChessQueen>(3, 0, true);
    AddPiece<AChessKing>(Board->Width - 4, 0, true);

	//Black line of pawns
	for (int x = 0; x < Board->Width; x++)
	{
		AddPiece<AChessPawn>(x, Board->Height - 2, false);
	}

    AddPiece<AChessRook>( 0, Board->Height - 1, false);
    AddPiece<AChessRook>( Board->Width - 1, Board->Height - 1, false);
    AddPiece<AChessKnight>( 1, Board->Height - 1, false);
    AddPiece<AChessKnight>( Board->Width - 2, Board->Height - 1, false);
    AddPiece<AChessBishop>( 2, Board->Height - 1, false);
    AddPiece<AChessBishop>( Board->Width - 3, Board->Height - 1, false);
    AddPiece<AChessKing>( 3, Board->Height - 1, false);
    AddPiece<AChessQueen>( Board->Width - 4, Board->Height - 1, false);
}

template<typename T>
void
APole3DGameModeBase::AddPiece(int iX, int iY, bool iIsWhite)
{
	APiece* piece = GetWorld()->SpawnActor<T>(T::StaticClass(), GetPieceTransform(iX, iY, iIsWhite == true ? 0 : 180));
	piece->SetColor(iIsWhite);

	piece->AttachToActor(Board, FAttachmentTransformRules::KeepRelativeTransform, "");
}

FTransform
APole3DGameModeBase::GetPieceTransform(int iX, int iY, int iRotationDegrees)
{
	FVector t(Board->Spacing * iX, Board->Spacing * iY, 0);
	return FTransform(FRotator( 0, iRotationDegrees, 0 ), t, FVector(0.25, 0.25, 0.25));
}


void APole3DGameModeBase::CreatePlayers()
{
    PlayerOne = GetWorld()->SpawnActor<AChessPlayer>(FVector(Board->Spacing * Board->Width / 2, -300, Board->Spacing * Board->Height / 2), FRotator(-30.f, 90.f, 0.f));
	PlayerOne->bIsWhite = true;
    PlayerTwo = GetWorld()->SpawnActor<AChessPlayer>(FVector(Board->Spacing * Board->Width / 2, Board->Spacing * Board->Height + 300, Board->Spacing * Board->Height / 2), FRotator(-30.f, -90.f, 0.f));
    PlayerTwo->bIsWhite = false;
	PlayerController->CurrentPlayer = PlayerOne;

	PlayerController->Possess( PlayerOne );
}

void APole3DGameModeBase::TurnEnd()
{
    //Remove highlights on the board
	RemoveHighlightBoard();

    //Switch Player
	PlayerController->UnPossess();

	if( PlayerController->CurrentPlayer == PlayerOne )
	{
		PlayerController->Possess( PlayerTwo );
		PlayerController->CurrentPlayer = PlayerTwo;
	}
	else
	{
		PlayerController->Possess( PlayerOne );
		PlayerController->CurrentPlayer = PlayerOne;
	}

}

void APole3DGameModeBase::CheckAndHighlightPossibleMovesForPiece( APiece* iPiece )
{
    RemoveHighlightBoard();

	if( !iPiece )
		return;

	AInteractiveTile* tile = iPiece->GetTileOfPiece();

	if( !tile )
		return;

	FIntPoint piecePosition = *Board->Tiles.FindKey( tile );
	TArray<FMove> possibleMoves = iPiece->GetPiecePossibleMoves();

	bool isCurrentPlayerWhite = PlayerController->CurrentPlayer->bIsWhite;

	for (int i = 0; i < possibleMoves.Num(); i++)
	{
        switch (possibleMoves[i].MoveLengthCondition)
        {
        case kEqualOrUnderLength:
            switch (possibleMoves[i].MoveCondition)
            {
            case kJumpOverPieces:
            {
                switch (possibleMoves[i].TakeCondition)
                {
                case kCanTakePiece:
                {
                    for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                    {
                        FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                            if (pieceOnTile == nullptr || (isCurrentPlayerWhite != pieceOnTile->bIsWhite))
                                Board->Tiles[movePosition]->Highlight();
                        }
                    }
                }
                break;
                case kCantTakePiece:
                {
                    for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                    {
                        FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                            if (pieceOnTile == nullptr)
                                Board->Tiles[movePosition]->Highlight();
                        }
                    }
                }
                break;
                case kMustTakePiece:
                {
                    for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                    {
                        FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                            if (pieceOnTile != nullptr && (isCurrentPlayerWhite != pieceOnTile->bIsWhite))
                                Board->Tiles[movePosition]->Highlight();
                        }
                    }
                }
                break;
                default:
                {}
                }
            }
            break;
            case kBlockedByPieces:
            {
                switch (possibleMoves[i].TakeCondition)
                {
                case kCanTakePiece:
                {
                    for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                    {
                        FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                            if (pieceOnTile == nullptr)
                            {
                                Board->Tiles[movePosition]->Highlight();
                            }
                            else if (pieceOnTile != nullptr)
                            {
                                if (isCurrentPlayerWhite == pieceOnTile->bIsWhite)
                                {
                                    break;
                                }
                                else
                                {
                                    Board->Tiles[movePosition]->Highlight();
                                    break;
                                }
                            }
                        }
                    }
                }
                break;
                case kCantTakePiece:
                {
                    for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                    {
                        FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                            if (pieceOnTile == nullptr)
                            {
                                Board->Tiles[movePosition]->Highlight();
                            }
                            else if (pieceOnTile != nullptr)
                            {
                                break;
                            }
                        }
                    }
                }
                break;
                case kMustTakePiece:
                {
                    for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                    {
                        FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                            if (pieceOnTile != nullptr)
                            {
                                if (pieceOnTile->bIsWhite != isCurrentPlayerWhite)
                                    Board->Tiles[movePosition]->Highlight();

                                break;
                            }
                        }
                    }
                }
                break;
                default:
                {}
                }
            }
            break;
            default:
            {}
            }
            break;
        case kFixedLength:
            switch (possibleMoves[i].MoveCondition)
            {
            case kJumpOverPieces:
            {
                switch (possibleMoves[i].TakeCondition)
                {
                case kCanTakePiece:
                {
                    FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * possibleMoves[i].MoveLength;

                    if (Board->Tiles.Contains(movePosition))
                    {
                        APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                        if (pieceOnTile == nullptr || (isCurrentPlayerWhite != pieceOnTile->bIsWhite))
                            Board->Tiles[movePosition]->Highlight();
                    }
                }
                break;
                case kCantTakePiece:
                {
                    FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * possibleMoves[i].MoveLength;

                    if (Board->Tiles.Contains(movePosition))
                    {
                        APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                        if (pieceOnTile == nullptr)
                            Board->Tiles[movePosition]->Highlight();
                    }
                }
                break;
                case kMustTakePiece:
                {
                    FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * possibleMoves[i].MoveLength;

                    if (Board->Tiles.Contains(movePosition))
                    {
                        APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                        if (pieceOnTile != nullptr && (isCurrentPlayerWhite != pieceOnTile->bIsWhite))
                            Board->Tiles[movePosition]->Highlight();
                    }
                }
                break;
                default:
                {}
                }
            }
            break;
            case kBlockedByPieces:
            {
                switch (possibleMoves[i].TakeCondition)
                {
                case kCanTakePiece:
                {
                    switch (possibleMoves[i].TakenCondition)
                    {
                    case kCanBeTaken:
                    {
                        for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                        {
                            FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                            if (Board->Tiles.Contains(movePosition))
                            {
                                APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                                if (pieceOnTile == nullptr && j == possibleMoves[i].MoveLength )
                                {
                                    Board->Tiles[movePosition]->Highlight();
                                }
                                else if (pieceOnTile != nullptr)
                                {
                                    if (j != possibleMoves[i].MoveLength)
                                        break;
                                
                                    if (isCurrentPlayerWhite != pieceOnTile->bIsWhite)
                                        Board->Tiles[movePosition]->Highlight();
                                }
                            }
                        }
                    }
                    break;
                    case kCantBeTaken:
                    {
                        for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                        {
                            FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                            if (Board->Tiles.Contains(movePosition))
                            {
                                if( IsTileDangerousForPiece( iPiece, Board->Tiles[movePosition] ) )
                                    continue;

                                APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                                if (pieceOnTile == nullptr && j == possibleMoves[i].MoveLength)
                                {
                                    Board->Tiles[movePosition]->Highlight();
                                }
                                else if (pieceOnTile != nullptr)
                                {
                                    if (j != possibleMoves[i].MoveLength)
                                        break;

                                    if (isCurrentPlayerWhite != pieceOnTile->bIsWhite)
                                        Board->Tiles[movePosition]->Highlight();
                                }
                            }
                        }
                    }
                    default:
                    {}
                    }
                }
                break;
                case kCantTakePiece:
                {
                    for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                    {
                        FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                            if (pieceOnTile == nullptr && j == possibleMoves[i].MoveLength )
                            {
                                Board->Tiles[movePosition]->Highlight();
                            }
                            else if (pieceOnTile != nullptr)
                            {
                                break;
                            }
                        }
                    }
                }
                break;
                case kMustTakePiece:
                {
                    for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                    {
                        FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                            if (pieceOnTile != nullptr)
                            {
                                if (j != possibleMoves[i].MoveLength)
                                {
                                    break;
                                }
                                else
                                {
                                    if( pieceOnTile->bIsWhite != isCurrentPlayerWhite )
                                        Board->Tiles[movePosition]->Highlight();
                                }
                            }
                        }
                    }
                }
                break;
                default:
                {}
                }
            }
            break;
            default:
                {}
            }
            break;
        default:
            {}
        }
	}
}

bool APole3DGameModeBase::IsTileDangerousForPiece(APiece* iPiece, AInteractiveTile* iTile)
{
    if( !iPiece || !iTile )
        return false;

    bool isPieceWhite = iPiece->bIsWhite;

    //Parcourt toutes les tiles, si on tombe sur iPiece ou iTile, on simule le fait que la piece soit sur iTile
    for (auto it = Board->Tiles.CreateConstIterator(); it; ++it )
    {
        APiece* pieceOnControlTile = it->Value->GetPieceOnTile();

        if( pieceOnControlTile == iPiece || it->Value == iTile )
            continue;


        if (pieceOnControlTile && pieceOnControlTile->bIsWhite != isPieceWhite)
        {
            FIntPoint piecePosition = *Board->Tiles.FindKey(it->Value);
            TArray<FMove> possibleMoves = pieceOnControlTile->GetPiecePossibleMoves();
            for (int i = 0; i < possibleMoves.Num(); i++)
            {
                switch (possibleMoves[i].MoveLengthCondition)
                {
                case kEqualOrUnderLength:
                    switch (possibleMoves[i].MoveCondition)
                    {
                    case kJumpOverPieces:
                    {
                        switch (possibleMoves[i].TakeCondition)
                        {
                        case kCanTakePiece:
                        {
                            for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                            {
                                FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                                if (Board->Tiles.Contains(movePosition))
                                {
                                    if( Board->Tiles[movePosition] == iTile )
                                        return true;
                                }
                            }
                        }
                        break;
                        case kMustTakePiece:
                        {
                            for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                            {
                                FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                                if (Board->Tiles.Contains(movePosition))
                                {
                                    if (Board->Tiles[movePosition] == iTile)
                                        return true;
                                }
                            }
                        }
                        break;
                        default:
                        {}
                        }
                    }
                    break;
                    case kBlockedByPieces:
                    {
                        switch (possibleMoves[i].TakeCondition)
                        {
                        case kCanTakePiece:
                        {
                            for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                            {
                                FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                                if (Board->Tiles.Contains(movePosition))
                                {
                                    if (Board->Tiles[movePosition] == iTile)
                                        return true;

                                    APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                                    if (pieceOnTile != nullptr && pieceOnTile != iPiece)
                                    {
                                        if (isPieceWhite == pieceOnTile->bIsWhite)
                                        {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                        case kMustTakePiece:
                        {
                            for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                            {
                                FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                                if (Board->Tiles.Contains(movePosition))
                                {
                                    if (Board->Tiles[movePosition] == iTile)
                                        return true;

                                    APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                                    if (pieceOnTile != nullptr && pieceOnTile != iPiece)
                                    {
                                        if (isPieceWhite == pieceOnTile->bIsWhite)
                                        {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                        default:
                        {}
                        }
                    }
                    break;
                    default:
                    {}
                    }
                    break;
                case kFixedLength:
                    switch (possibleMoves[i].MoveCondition)
                    {
                    case kJumpOverPieces:
                    {
                        switch (possibleMoves[i].TakeCondition)
                        {
                        case kCanTakePiece:
                        {
                            FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * possibleMoves[i].MoveLength;

                            if (Board->Tiles.Contains(movePosition))
                            {
                                if (Board->Tiles[movePosition] == iTile)
                                    return true;
                            }
                        }
                        break;
                        case kMustTakePiece:
                        {
                            FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * possibleMoves[i].MoveLength;

                            if (Board->Tiles.Contains(movePosition))
                            {
                                if (Board->Tiles[movePosition] == iTile)
                                    return true;
                            }
                        }
                        break;
                        default:
                        {}
                        }
                    }
                    break;
                    case kBlockedByPieces:
                    {
                        switch (possibleMoves[i].TakeCondition)
                        {
                        case kCanTakePiece:
                        {
                            for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                            {
                                FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                                if (Board->Tiles.Contains(movePosition))
                                {
                                    APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                                    if (pieceOnTile == nullptr && j == possibleMoves[i].MoveLength )
                                    {
                                        if (Board->Tiles[movePosition] == iTile)
                                            return true;
                                    }
                                    else if (pieceOnTile != nullptr && pieceOnTile != iPiece)
                                    {
                                        if (j != possibleMoves[i].MoveLength)
                                            break;

                                        if (Board->Tiles[movePosition] == iTile)
                                            return true;
                                    }
                                }
                            }
                        }
                        break;
                        case kMustTakePiece:
                        {
                            for (uint32 j = 1; j <= possibleMoves[i].MoveLength; j++)
                            {
                                FIntPoint movePosition = piecePosition + possibleMoves[i].MoveUnitVector * j;

                                if (Board->Tiles.Contains(movePosition))
                                {
                                    APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();
                                    if (pieceOnTile == nullptr && j == possibleMoves[i].MoveLength)
                                    {
                                        if (Board->Tiles[movePosition] == iTile)
                                            return true;
                                    }
                                    else if (pieceOnTile != nullptr && pieceOnTile != iPiece)
                                    {
                                        if (j != possibleMoves[i].MoveLength)
                                            break;

                                        if (Board->Tiles[movePosition] == iTile)
                                            return true;
                                    }
                                }
                            }
                        }
                        break;
                        default:
                        {}
                        }
                    }
                    break;
                    default:
                    {}
                    }
                    break;
                default:
                {}
                }
            }
        }
    }

    return false;
}

void APole3DGameModeBase::RemoveHighlightBoard()
{
	for (auto it = Board->Tiles.CreateConstIterator(); it; ++it )
	{
		it->Value->RemoveHighlight();
	}
}
