// Fill out your copyright notice in the Description page of Project Settings.


#include "Pieces/Piece.h"
#include "InteractiveTile.h"

APiece::APiece()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>("DefaultRootComponent");
    RootComponent->bVisualizeComponent = true;

    PieceMesh = CreateDefaultSubobject<UStaticMeshComponent>("PieceMesh");
    PieceMesh->AttachToComponent( RootComponent, FAttachmentTransformRules::KeepRelativeTransform );

    PieceMesh->SetCollisionProfileName( TEXT("Chess") );

    IsFirstMove = true;
}

void APiece::SetColor(bool iIsWhite)
{
    IsWhite = iIsWhite;

    if (IsWhite)
    {
        UMaterialInterface* material = LoadObject<UMaterialInterface>( this, TEXT("/Game/StarterContent/Materials/M_Wood_Pine"));
        PieceMesh->SetMaterial(0, material);
    }
    else
    {
        UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/StarterContent/Materials/M_Wood_Floor_Walnut_Worn"));
        PieceMesh->SetMaterial(0, material);
    }
}

void APiece::Select()
{
    UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/Materials/SelectMaterial"));
    PieceMesh->SetMaterial(0, material);
}

void APiece::Unselect()
{
    if (IsWhite)
    {
        UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/StarterContent/Materials/M_Wood_Pine"));
        PieceMesh->SetMaterial(0, material);
    }
    else
    {
        UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/StarterContent/Materials/M_Wood_Floor_Walnut_Worn"));
        PieceMesh->SetMaterial(0, material);
    }
}

AInteractiveTile* APiece::GetTileOfPiece()
{
    TArray<AActor*> overlappedActors;
    GetOverlappingActors(overlappedActors, AInteractiveTile::StaticClass());

    if (overlappedActors.Num() > 0)
        return Cast<AInteractiveTile>(overlappedActors[0]);

    return nullptr;
}

TArray<FMove> APiece::GetAvailableMoves()
{
    return TArray<FMove>();
}
