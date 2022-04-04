#include "ChessPlayer.h"
#include "ChessController.h"

AChessPlayer::AChessPlayer()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerPointOfView"));
    Camera->SetupAttachment(RootComponent, "");
}
