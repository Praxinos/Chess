#include "ChessController.h"

#include "ChessPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Pole3DGameModeBase.h"
#include "InteractiveTile.h"

AChessController::AChessController()
{
    bShowMouseCursor = true;
    SelectedPiece = nullptr;
    SelectedTile = nullptr;
}

void AChessController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Bind actions for mouse events
    InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AChessController::OnLeftMouseClick);
    InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &AChessController::OnRightMouseClick);
}

void AChessController::OnLeftMouseClick()
{
    FHitResult TraceResult(ForceInit);
    GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult);

    if (SelectedPiece)
    {
        SelectedPiece->RemoveHighlight();
        SelectedPiece = nullptr;
    }

    if ( TraceResult.GetActor() != nullptr && TraceResult.GetActor()->IsA( APiece::StaticClass()) )
    {
        SelectedPiece = Cast<APiece>(TraceResult.GetActor());
        if( SelectedPiece->bIsWhite == CurrentPlayer->bIsWhite )
            SelectedPiece->Highlight();
        else
            SelectedPiece = nullptr;
    }
    OnSelectedPieceDelegate().ExecuteIfBound( SelectedPiece );
}

void AChessController::OnRightMouseClick()
{
    FHitResult TraceResult(ForceInit);
    GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult);

    if (TraceResult.GetActor() != nullptr && TraceResult.GetActor()->IsA( AInteractiveTile::StaticClass()) )
    {
        SelectedTile = Cast<AInteractiveTile>(TraceResult.GetActor());

        if (SelectedPiece && SelectedTile->IsSelected )
        {
            APiece* pieceOnTile = SelectedTile->GetPieceOnTile();
            if( pieceOnTile )
                pieceOnTile->Destroy();

            SelectedPiece->SetActorLocation(FVector(SelectedTile->GetActorLocation().X, SelectedTile->GetActorLocation().Y, SelectedPiece->GetActorLocation().Z));
            SelectedPiece->bFirstMove = false;
            SelectedPiece->RemoveHighlight();
            SelectedPiece = nullptr;
            TurnEndDelegate.ExecuteIfBound();
        }
        else
        {
            SelectedTile = nullptr;
        }
    }
}

AChessController::FOnTurnEndDelegate& AChessController::OnTurnEndDelegate()
{
    return TurnEndDelegate;
}


AChessController::FOnSelectedPieceDelegate& AChessController::OnSelectedPieceDelegate()
{
    return SelectedPieceDelegate;
}
