#include "ChessController.h"

#include "Pieces/Piece.h"
#include "ChessPlayer.h"

AChessController::AChessController()
{
    bShowMouseCursor = true;
}

void AChessController::BeginPlay()
{
    PlayerTwo = GetWorld()->SpawnActor<AChessPlayer>(FVector(1600.0, 3700.0, 1500), FRotator(20.0f, -90.0f, 0.0f));
    PlayerTwo->bIsWhite = false;
    PlayerOne = GetWorld()->SpawnActor<AChessPlayer>(FVector(1600.0, -500.0, 1500), FRotator(20.0f, 90.0f, 0.0f));
    PlayerOne->bIsWhite = true;
    CurrentPlayer = PlayerOne;
}

void AChessController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Bind actions for mouse events
    InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AChessController::OnLeftMouseClick);
    InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &AChessController::OnRightMouseClick);

    UE_LOG(LogTemp, Display, TEXT("Setup"));
}

void AChessController::OnLeftMouseClick()
{
    UE_LOG(LogTemp, Display, TEXT("HIT"));

    FHitResult TraceResult(ForceInit);
    GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult);

    if (TraceResult.GetActor() != nullptr)
    {
        UE_LOG(LogTemp, Display, TEXT("%s"), *TraceResult.GetActor()->GetFName().ToString())
    }
}

void AChessController::OnRightMouseClick()
{

}
