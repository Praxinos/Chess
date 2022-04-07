// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayer.h"

// Sets default values
AChessPlayer::AChessPlayer()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>("DefaultRootComponent");
    RootComponent->bVisualizeComponent = true;

    Camera = CreateDefaultSubobject<UCameraComponent>("PlayerPointOfView");
    Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AChessPlayer::Init(bool iIsWhite, int iSizeX, int iSizeY, int iAssetSize)
{
    IsWhite = iIsWhite;

    int rotationDegrees = 180;
    if( !iIsWhite )
        rotationDegrees = 0;

    FTransform transform = FTransform( FRotator( -90, -90, rotationDegrees ), FVector((iSizeX * iAssetSize) / 2 - iAssetSize / 2, (iSizeY * iAssetSize) / 2 - iAssetSize / 2, FMath::Max(iSizeX, iSizeY) * iAssetSize));
    RootComponent->AddWorldTransform( transform );
}

