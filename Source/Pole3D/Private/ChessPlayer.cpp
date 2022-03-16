#include "ChessPlayer.h"
#include "ChessController.h"

AChessPlayer::AChessPlayer()
{
    PrimaryActorTick.bCanEverTick = true;
}


void AChessPlayer::BeginPlay()
{
    Super::BeginPlay();
    ChessController = Cast<AChessController>(GetController());
}