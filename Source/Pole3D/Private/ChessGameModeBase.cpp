// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameModeBase.h"
#include "Pieces/ChessPawn.h"
#include "Pieces/ChessRook.h"
#include "Pieces/ChessBishop.h"
#include "Pieces/ChessKnight.h"
#include "Pieces/ChessKing.h"
#include "Pieces/ChessQueen.h"
#include "ChessPlayer.h"
#include "ChessController.h"

AChessGameModeBase::AChessGameModeBase()
{
    PlayerControllerClass = AChessController::StaticClass();
    DefaultPawnClass = nullptr;
    HUDClass = nullptr;
    GameStateClass = nullptr;
}


void AChessGameModeBase::BeginPlay()
{
    ChessController = Cast<AChessController>(GetWorld()->GetFirstPlayerController());
    ChessController->OnTurnEndDelegate().BindUObject( this, &AChessGameModeBase::SwitchPlayer ); 
    ChessController->OnSelectedPieceDelegate().BindUObject( this, &AChessGameModeBase::GetTilesPieceCanMoveTo ); 

    Board = GetWorld()->SpawnActor<ABoard>();

    PlayerOne = GetWorld()->SpawnActor<AChessPlayer>();
    PlayerOne->Init( true, 8, 8, 100 );
    PlayerTwo = GetWorld()->SpawnActor<AChessPlayer>();
    PlayerTwo->Init( false, 8, 8, 100 );

    UStaticMesh* whiteTileMesh = LoadObject<UStaticMesh>( Board, TEXT("/Game/Meshes/WhiteTile"));
    UStaticMesh* blackTileMesh = LoadObject<UStaticMesh>( Board, TEXT("/Game/Meshes/BlackTile"));
    
    Board->Init(8, 8, 100, whiteTileMesh, blackTileMesh);

    SetupBoard();
    ChessController->Possess(PlayerOne);
    ChessController->CurrentPlayer = PlayerOne;
}

void AChessGameModeBase::SetupBoard()
{
    //White line of pawns
    for (int x = 0; x < Board->SizeX; x++)
    {
        AddPiece<AChessPawn>(x, 1, true);
    }

    AddPiece<AChessRook>(0, 0, true);
    AddPiece<AChessRook>(Board->SizeX - 1, 0, true);
    AddPiece<AChessKnight>(1, 0, true);
    AddPiece<AChessKnight>(Board->SizeX - 2, 0, true);
    AddPiece<AChessBishop>(2, 0, true);
    AddPiece<AChessBishop>(Board->SizeX - 3, 0, true);
    PlayerOneKing = AddPiece<AChessKing>(3, 0, true);
    AddPiece<AChessQueen>(Board->SizeX - 4, 0, true);
    
    //Black line of pawns
    for (int x = 0; x < Board->SizeX; x++)
    {
        AddPiece<AChessPawn>(x, Board->SizeY - 2, false);
    }

    AddPiece<AChessRook>(0, Board->SizeY - 1, false);
    AddPiece<AChessRook>(Board->SizeX - 1, Board->SizeY - 1, false);
    AddPiece<AChessKnight>(1, Board->SizeY - 1, false);
    AddPiece<AChessKnight>(Board->SizeX - 2, Board->SizeY - 1, false);
    AddPiece<AChessBishop>(2, Board->SizeY - 1, false);
    AddPiece<AChessBishop>(Board->SizeX - 3, Board->SizeY - 1, false);
    PlayerTwoKing = AddPiece<AChessKing>(3, Board->SizeY - 1, false);
    AddPiece<AChessQueen>(Board->SizeX - 4, Board->SizeY - 1, false);
}

template< typename T >
T* AChessGameModeBase::AddPiece(int iX, int iY, bool iIsWhite)
{
    int rotationDegrees = 0;
    if( !iIsWhite )
        rotationDegrees = 180;

    T* piece = GetWorld()->SpawnActor<T>(T::StaticClass(), GetPieceTransform( iX, iY, rotationDegrees ));
    piece->SetColor( iIsWhite );

    piece->AttachToActor( Board, FAttachmentTransformRules::KeepRelativeTransform );

    return piece;
}

FTransform AChessGameModeBase::GetPieceTransform(int iX, int iY, int iRotationDegrees)
{
    FVector vec ( Board->AssetSize * iX, Board->AssetSize * iY, Board->AssetSize / 2 );
    return FTransform( FRotator( 0, iRotationDegrees, 0 ), vec, FVector( 0.25, 0.25, 0.25 ));
}

void AChessGameModeBase::SwitchPlayer()
{
    for (auto it = Board->Tiles.CreateConstIterator(); it; ++it)
    {
        it->Value->Unselect();
    }

    ChessController->UnPossess();
    if (ChessController->CurrentPlayer == PlayerOne)
    {
        ChessController->CurrentPlayer = PlayerTwo;
        ChessController->Possess( PlayerTwo );
    }
    else
    {
        ChessController->CurrentPlayer = PlayerOne;
        ChessController->Possess( PlayerOne );
    }

    if( IsInCheckMate() )
        UE_LOG(LogTemp, Display, TEXT("You lose"));

}

TArray<AInteractiveTile*> AChessGameModeBase::GetTilesPieceCanMoveTo(APiece* iPiece)
{
    TArray<AInteractiveTile*> moveTiles;

    for (auto it = Board->Tiles.CreateConstIterator(); it; ++it)
    {
        it->Value->Unselect();
    }
    
    if( iPiece == nullptr )
        return moveTiles;

    AInteractiveTile* tile = iPiece->GetTileOfPiece();
    FIntPoint positionOnBoard = *Board->Tiles.FindKey(tile);

    TArray<FMove> availableMoves = iPiece->GetAvailableMoves();

    bool isCurrentPlayerWhite = ChessController->CurrentPlayer->IsWhite;
    AChessKing* currentKing = PlayerOneKing;
    if( !isCurrentPlayerWhite )
        currentKing = PlayerTwoKing;


    for (int i = 0; i < availableMoves.Num(); i++)
    {
        switch (availableMoves[i].ExtendMove)
        {
        case kExtend:
        {
            switch (availableMoves[i].MoveCondition)
            {
            case kJump:
            {
                switch (availableMoves[i].KillCondition)
                {
                case kCanKill:
                {
                    bool endOfmove = false;
                    int j = 1;
                    while( !endOfmove )
                    {
                        FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                            if ( pieceOnTile != nullptr && pieceOnTile->IsWhite != isCurrentPlayerWhite )
                            {
                                if( !IsTileDangerousAfterMove( currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition] ) )
                                    moveTiles.Add(Board->Tiles[movePosition]);
                            }
                            else if (pieceOnTile == nullptr)
                            {
                                if (!IsTileDangerousAfterMove( currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                    moveTiles.Add(Board->Tiles[movePosition]);
                            }
                        }
                        else
                        {
                            endOfmove = true;
                        }
                        j++;
                    }
                }
                break;
                case kCantKill:
                {
                    bool endOfmove = false;
                    int j = 1;
                    while( !endOfmove )
                    {
                        FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                            if (pieceOnTile == nullptr)
                            {
                                if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                    moveTiles.Add(Board->Tiles[movePosition]);
                            }
                        }
                        else
                        {
                            endOfmove = true;
                        }
                        j++;
                    }
                }
                break;
                case kMustKill:
                {
                    bool endOfmove = false;
                    int j = 1;
                    while (!endOfmove)
                    {
                        FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                            if (pieceOnTile != nullptr && pieceOnTile->IsWhite != isCurrentPlayerWhite)
                            {
                                if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                    moveTiles.Add(Board->Tiles[movePosition]);
                            }
                        }
                        else
                        {
                            endOfmove = true;
                        }
                        j++;
                    }
                }
                break;
                default:
                {}
                }
            }
            break;
            case kBlocked:
            {
                switch (availableMoves[i].KillCondition)
                {
                case kCanKill:
                {
                    bool endOfmove = false;
                    int j = 1;
                    while (!endOfmove)
                    {
                        FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                            if (pieceOnTile != nullptr)
                            {
                                if (pieceOnTile->IsWhite != isCurrentPlayerWhite)
                                {
                                    if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                        moveTiles.Add(Board->Tiles[movePosition]);
                                }

                                endOfmove = true;
                            }
                            else
                            {
                                if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                    moveTiles.Add(Board->Tiles[movePosition]);
                            }
                        }
                        else
                        {
                            endOfmove = true;
                        }
                        j++;
                    }
                }
                break;
                case kCantKill:
                {
                    bool endOfmove = false;
                    int j = 1;
                    while (!endOfmove)
                    {
                        FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                            if (pieceOnTile != nullptr)
                            {
                                endOfmove = true;
                            }
                            else
                            {
                                if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                    moveTiles.Add(Board->Tiles[movePosition]);
                            }
                        }
                        else
                        {
                            endOfmove = true;
                        }
                        j++;
                    }
                }
                break;
                case kMustKill:
                {
                    bool endOfmove = false;
                    int j = 1;
                    while (!endOfmove)
                    {
                        FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                            if (pieceOnTile != nullptr)
                            {
                                if (pieceOnTile->IsWhite != isCurrentPlayerWhite)
                                {
                                    if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                        moveTiles.Add(Board->Tiles[movePosition]);
                                }
                                
                                endOfmove = true;
                            }
                        }
                        else
                        {
                            endOfmove = true;
                        }
                        j++;
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
        }
        break;
        case kFixed:
        {
            switch (availableMoves[i].MoveCondition)
            {
            case kJump:
            {
                switch (availableMoves[i].KillCondition)
                {
                case kCanKill:
                {
                    FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * availableMoves[i].Length;
                    if (Board->Tiles.Contains(movePosition))
                    {
                        APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                        if (pieceOnTile == nullptr)
                        {
                            if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                moveTiles.Add(Board->Tiles[movePosition]);
                        }
                        else if (pieceOnTile != nullptr && isCurrentPlayerWhite != pieceOnTile->IsWhite)
                        {
                            if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                moveTiles.Add(Board->Tiles[movePosition]);
                        }
                    }
                }
                break;
                case kCantKill:
                {
                    FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * availableMoves[i].Length;
                    if (Board->Tiles.Contains(movePosition))
                    {
                        APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                        if (pieceOnTile == nullptr)
                        {
                            if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                moveTiles.Add(Board->Tiles[movePosition]);
                        }
                    }
                }
                break;
                case kMustKill:
                {
                    FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * availableMoves[i].Length;
                    if (Board->Tiles.Contains(movePosition))
                    {
                        APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                        if (pieceOnTile != nullptr && isCurrentPlayerWhite != pieceOnTile->IsWhite)
                        {
                            if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                moveTiles.Add(Board->Tiles[movePosition]);
                        }
                    }
                }
                break;
                default:
                {}
                }
            }
            break;
            case kBlocked:
            {
                switch (availableMoves[i].KillCondition)
                {
                case kCanKill:
                {
                    for (int j = 1; j <= availableMoves[i].Length; j++)
                    {
                        FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                            if (pieceOnTile == nullptr && j == availableMoves[i].Length)
                            {
                                if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                    moveTiles.Add(Board->Tiles[movePosition]);
                            }
                            else if (pieceOnTile != nullptr)
                            {
                                if( j != availableMoves[i].Length )
                                    break;

                                if (isCurrentPlayerWhite != pieceOnTile->IsWhite)
                                {
                                    if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                        moveTiles.Add(Board->Tiles[movePosition]);
                                }
                            }
                        }
                    }
                }
                break;
                case kCantKill:
                {
                    for (int j = 1; j <= availableMoves[i].Length; j++)
                    {
                        FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                            if (pieceOnTile == nullptr && j == availableMoves[i].Length )
                            {
                                if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                    moveTiles.Add(Board->Tiles[movePosition]);
                            }
                            else if (pieceOnTile != nullptr)
                            {
                                break;
                            }
                        }
                    }
                }
                break;
                case kMustKill:
                {
                    for (int j = 1; j <= availableMoves[i].Length; j++)
                    {
                        FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                        if (Board->Tiles.Contains(movePosition))
                        {
                            APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                            if (pieceOnTile != nullptr && pieceOnTile->IsWhite != isCurrentPlayerWhite && j == availableMoves[i].Length)
                            {
                                if (!IsTileDangerousAfterMove(currentKing->GetTileOfPiece(), iPiece, Board->Tiles[movePosition]))
                                    moveTiles.Add(Board->Tiles[movePosition]);
                            }
                            else if (pieceOnTile != nullptr)
                            {
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
        }
        break;
        default:
        {}
        }
    }

    return moveTiles;
}


bool AChessGameModeBase::IsTileDangerousAfterMove(AInteractiveTile* iTileToCheck, APiece* iPieceToMove, AInteractiveTile* iTileToMoveTo)
{
    if( iTileToCheck == nullptr || iPieceToMove == nullptr || iTileToMoveTo == nullptr )
        return false;

    bool isPieceWhite = iPieceToMove->IsWhite;
    AChessKing* currentKing = PlayerOneKing;
    if( !isPieceWhite )
        currentKing = PlayerTwoKing;

    if( iPieceToMove == currentKing )
        iTileToCheck = iTileToMoveTo;

    for (auto it = Board->Tiles.CreateConstIterator(); it; ++it)
    {
        APiece* pieceOnControlTile = it->Value->GetPieceOnTile();

        if( pieceOnControlTile == iPieceToMove || it->Value == iTileToMoveTo )
            continue;

        if (pieceOnControlTile && pieceOnControlTile->IsWhite != isPieceWhite)
        {
            FIntPoint positionOnBoard = *Board->Tiles.FindKey(it->Value);

            TArray<FMove> availableMoves = pieceOnControlTile->GetAvailableMoves();
            
            for (int i = 0; i < availableMoves.Num(); i++)
            {
                switch (availableMoves[i].ExtendMove)
                {
                case kExtend:
                {
                    switch (availableMoves[i].MoveCondition)
                    {
                    case kJump:
                    {
                        switch (availableMoves[i].KillCondition)
                        {
                        case kCanKill:
                        {
                            bool endOfmove = false;
                            int j = 1;
                            while( !endOfmove )
                            {
                                FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                                if (Board->Tiles.Contains(movePosition))
                                {
                                    if( Board->Tiles[movePosition] == iTileToCheck )
                                        return true;
                                }
                                else
                                {
                                    endOfmove = true;
                                }
                                j++;
                            }
                        }
                        break;
                        case kMustKill:
                        {
                            bool endOfmove = false;
                            int j = 1;
                            while (!endOfmove)
                            {
                                FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                                if (Board->Tiles.Contains(movePosition))
                                {
                                    if (Board->Tiles[movePosition] == iTileToCheck)
                                        return true;
                                }
                                else
                                {
                                    endOfmove = true;
                                }
                                j++;
                            }
                        }
                        break;
                        default:
                        {}
                        }
                    }
                    break;
                    case kBlocked:
                    {
                        switch (availableMoves[i].KillCondition)
                        {
                        case kCanKill:
                        {
                            bool endOfmove = false;
                            int j = 1;
                            while (!endOfmove)
                            {
                                FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                                if (Board->Tiles.Contains(movePosition))
                                {
                                    if( Board->Tiles[movePosition] == iTileToCheck )
                                        return true;

                                    APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                                    if( pieceOnTile == iPieceToMove )
                                        pieceOnTile = nullptr;

                                    if( Board->Tiles[movePosition] == iTileToMoveTo )
                                        pieceOnTile = iPieceToMove;

                                    if (pieceOnTile != nullptr)
                                    {
                                        endOfmove = true;
                                    }
                                }
                                else
                                {
                                    endOfmove = true;
                                }
                                j++;
                            }
                        }
                        break;
                        case kMustKill:
                        {
                            bool endOfmove = false;
                            int j = 1;
                            while (!endOfmove)
                            {
                                FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                                if (Board->Tiles.Contains(movePosition))
                                {
                                    if( Board->Tiles[movePosition] == iTileToCheck )
                                        return true;

                                    APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                                    if( pieceOnTile == iPieceToMove )
                                        pieceOnTile = nullptr;

                                    if( Board->Tiles[movePosition] == iTileToMoveTo )
                                        pieceOnTile = iPieceToMove;

                                    if (pieceOnTile != nullptr)
                                    {
                                        endOfmove = true;
                                    }
                                }
                                else
                                {
                                    endOfmove = true;
                                }
                                j++;
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
                }
                break;
                case kFixed:
                {
                    switch (availableMoves[i].MoveCondition)
                    {
                    case kJump:
                    {
                        switch (availableMoves[i].KillCondition)
                        {
                        case kCanKill:
                        {
                            FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector;

                            if (Board->Tiles.Contains(movePosition))
                            {
                                if( Board->Tiles[movePosition] == iTileToCheck )
                                    return true;
                            }
                        }
                        break;
                        case kMustKill:
                        {
                            FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector;

                            if (Board->Tiles.Contains(movePosition))
                            {
                                if (Board->Tiles[movePosition] == iTileToCheck)
                                    return true;
                            }
                        }
                        break;
                        default:
                        {}
                        }
                    }
                    break;
                    case kBlocked:
                    {
                        switch (availableMoves[i].KillCondition)
                        {
                        case kCanKill:
                        {
                            for (int j = 1; j <= availableMoves[i].Length; j++)
                            {
                                FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                                if (Board->Tiles.Contains(movePosition))
                                {
                                    APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                                    if( pieceOnTile == iPieceToMove )
                                        pieceOnTile = nullptr;

                                    if( Board->Tiles[movePosition] == iTileToMoveTo )
                                        pieceOnTile = iPieceToMove;

                                    if (pieceOnTile == nullptr && j == availableMoves[i].Length)
                                    {
                                        if( Board->Tiles[movePosition] == iTileToCheck )
                                            return true;
                                    }
                                    else if (pieceOnTile != nullptr)
                                    {
                                        if( j != availableMoves[i].Length )
                                            break;

                                        if( Board->Tiles[movePosition] == iTileToCheck )
                                            return true;
                                    }
                                }
                            }
                        }
                        break;
                        case kMustKill:
                        {
                            for (int j = 1; j <= availableMoves[i].Length; j++)
                            {
                                FIntPoint movePosition = positionOnBoard + availableMoves[i].MoveVector * j;
                                if (Board->Tiles.Contains(movePosition))
                                {
                                    APiece* pieceOnTile = Board->Tiles[movePosition]->GetPieceOnTile();

                                    if( pieceOnTile == iPieceToMove )
                                        pieceOnTile = nullptr;

                                    if( Board->Tiles[movePosition] == iTileToMoveTo )
                                        pieceOnTile = iPieceToMove;

                                    if (pieceOnTile == nullptr && j == availableMoves[i].Length)
                                    {
                                        if( Board->Tiles[movePosition] == iTileToCheck )
                                            return true;
                                    }
                                    else if (pieceOnTile != nullptr)
                                    {
                                        if( j != availableMoves[i].Length )
                                            break;

                                        if( Board->Tiles[movePosition] == iTileToCheck )
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
    }
    return false;
}

bool AChessGameModeBase::IsInCheckMate()
{
    for (auto it = Board->Tiles.CreateConstIterator(); it; ++it)
    {
        bool isWhiteTurn = ChessController->CurrentPlayer->IsWhite;
        APiece* pieceOnTile = it->Value->GetPieceOnTile();
        if (pieceOnTile && pieceOnTile->IsWhite == isWhiteTurn)
        {
            if( GetTilesPieceCanMoveTo( pieceOnTile ).Num() != 0 )
                return false;
        }
    }
    return true;
}