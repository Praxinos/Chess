#include "Pieces/Piece.h"
#include "InteractiveTile.h"

APiece::APiece()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
	RootComponent->bVisualizeComponent = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    StaticMeshComponent->SetGenerateOverlapEvents(true);
    StaticMeshComponent->SetCollisionProfileName(TEXT("Piece"));
    //StaticMeshComponent->SetSimulatePhysics(true);
}

void
APiece::SetColor(bool iIsWhite)
{
	bIsWhite = iIsWhite;

	if (bIsWhite)
	{
        UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/StarterContent/Materials/M_Basic_Wall"));
        StaticMeshComponent->SetMaterial(0, material);
	}
	else
	{
        UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/StarterContent/Materials/M_Wood_Walnut"));
        StaticMeshComponent->SetMaterial(0, material);
	}
}

void APiece::Highlight()
{
    UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/Materials/SelectMaterial"));
    StaticMeshComponent->SetMaterial(0, material);
}

void APiece::RemoveHighlight()
{
    if (bIsWhite)
    {
        UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/StarterContent/Materials/M_Basic_Wall"));
        StaticMeshComponent->SetMaterial(0, material);
    }
    else
    {
        UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/StarterContent/Materials/M_Wood_Walnut"));
        StaticMeshComponent->SetMaterial(0, material);
    }
}

AInteractiveTile* APiece::GetTileOfPiece() const
{
    TArray<AActor*> overlapedActors;
    this->GetOverlappingActors(overlapedActors, AInteractiveTile::StaticClass());

    if (overlapedActors.Num() > 0)
        return Cast<AInteractiveTile>(overlapedActors[0]);

    return nullptr;
}

TArray<FMove> APiece::GetPiecePossibleMoves()
{
    return TArray<FMove>();
}
