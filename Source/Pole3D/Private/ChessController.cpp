// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessController.h"
#include "Pieces/Piece.h"
#include "InteractiveTile.h"
#include "ChessPlayer.h"


AChessController::AChessController()
{
    bShowMouseCursor = true;
    SelectedPiece = nullptr;
}

void AChessController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AChessController::OnLeftMouseClick );
    InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &AChessController::OnRightMouseClick );
}


void AChessController::OnLeftMouseClick()
{
    FHitResult TraceResult(ForceInit);
    GetHitResultUnderCursor( ECollisionChannel::ECC_WorldDynamic, false, TraceResult );

    UnselectPiece();

    if ( TraceResult.GetActor() != nullptr && TraceResult.GetActor()->IsA( APiece::StaticClass() ) )
    {
        SelectedPiece = Cast<APiece>(TraceResult.GetActor());

        if( SelectedPiece->IsWhite == CurrentPlayer->IsWhite )
            SelectedPiece->Select();
        else
            SelectedPiece = nullptr;
    }

    TArray<AInteractiveTile*> tilesToHighlight;
    if( OnSelectedPieceDelegate().IsBound() )
        tilesToHighlight = OnSelectedPieceDelegate().Execute(SelectedPiece);

    for( int i = 0; i < tilesToHighlight.Num(); i++ )
        tilesToHighlight[i]->Select();
}

void AChessController::OnRightMouseClick()
{
    FHitResult TraceResult(ForceInit);
    GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult);

    UnselectTile();

    if ( SelectedPiece != nullptr && TraceResult.GetActor() != nullptr && TraceResult.GetActor()->IsA( AInteractiveTile::StaticClass() ) )
    {
        SelectedTile = Cast<AInteractiveTile>(TraceResult.GetActor());
        if (SelectedTile->IsSelected == true)
        {
            APiece* pieceToTake = SelectedTile->GetPieceOnTile();
            if (pieceToTake != nullptr)
                pieceToTake->Destroy();

            SelectedPiece->SetActorLocation(FVector(SelectedTile->GetActorLocation().X, SelectedTile->GetActorLocation().Y, SelectedPiece->GetActorLocation().Z));
            SelectedPiece->IsFirstMove = false;
            UnselectPiece();
            UnselectTile();

            TurnEndDelegate.ExecuteIfBound();
        }
    }
}

void AChessController::UnselectPiece()
{
    if( SelectedPiece == nullptr )
        return;

    SelectedPiece->Unselect();
    SelectedPiece = nullptr;
}

void AChessController::UnselectTile()
{
    if( SelectedTile == nullptr )
        return;

    SelectedTile->Unselect();
    SelectedTile = nullptr;
}

AChessController::FOnTurnEndDelegate& AChessController::OnTurnEndDelegate()
{
    return TurnEndDelegate;
}

AChessController::FOnSelectedPieceDelegate& AChessController::OnSelectedPieceDelegate()
{
    return SelectedPieceDelegate;
}
