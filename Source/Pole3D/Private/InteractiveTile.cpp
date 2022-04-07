// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveTile.h"
#include "Pieces/Piece.h"

// Sets default values
AInteractiveTile::AInteractiveTile()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>("DefaultRootComponent");
    RootComponent->bVisualizeComponent = true;

    TileMesh = CreateDefaultSubobject<UStaticMeshComponent>("TileMesh");
    TileMesh->AttachToComponent( RootComponent, FAttachmentTransformRules::KeepRelativeTransform );

    ConstructorHelpers::FObjectFinder<UStaticMesh> staticMesh( TEXT("/Game/Meshes/Tile"));
    TileMesh->SetStaticMesh( staticMesh.Object );

    TileMesh->SetCollisionProfileName( TEXT("Chess"));

    IsSelected = false;
}

void AInteractiveTile::Select()
{
    UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/Materials/SelectMaterial"));
    TileMesh->SetMaterial(0, material);

    IsSelected = true;
}

void AInteractiveTile::Unselect()
{
    UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/Materials/TransparentMaterial"));
    TileMesh->SetMaterial(0, material);

    IsSelected = false;
}

APiece* AInteractiveTile::GetPieceOnTile()
{
    TArray<AActor*> overlappedActors;
    GetOverlappingActors( overlappedActors, APiece::StaticClass() );

    if( overlappedActors.Num() > 0 )
        return Cast<APiece>(overlappedActors[0]);

    return nullptr;
}
