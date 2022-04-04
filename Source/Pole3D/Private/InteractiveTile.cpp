
#include "InteractiveTile.h"
#include "Pieces/Piece.h"
#include <Components/BoxComponent.h>

AInteractiveTile::AInteractiveTile()
{
    USceneComponent* component = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
    SetRootComponent(component);
	RootComponent->bVisualizeComponent = true;

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/TileMesh"));
    StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);

    StaticMeshComponent->SetGenerateOverlapEvents(true);
    StaticMeshComponent->SetCollisionProfileName(TEXT("Piece"));

    IsSelected = false;
}

void AInteractiveTile::Highlight()
{
    UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/Materials/SelectMaterial"));
    StaticMeshComponent->SetMaterial(0, material);

    IsSelected = true;
}

void AInteractiveTile::RemoveHighlight()
{
    UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/Materials/TransparentMaterial"));
    StaticMeshComponent->SetMaterial(0, material);

    IsSelected = false;
}

APiece* AInteractiveTile::GetPieceOnTile()
{
    TArray<AActor*> overlapedActors;    
    this->GetOverlappingActors( overlapedActors, APiece::StaticClass() );

    if( overlapedActors.Num() > 0 )
        return Cast<APiece>( overlapedActors[0] );

    return nullptr;
}

