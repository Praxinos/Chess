#include "Pieces/Piece.h"

APiece::APiece()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
	RootComponent->bVisualizeComponent = true;

	//ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Pawn"));
	//ConstructorHelpers::FObjectFinder<UMaterialInterface> materialFinder(TEXT("/Game/StarterContent/Materials/M_Basic_Wall"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	//StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);
	//StaticMeshComponent->SetMaterial(0, materialFinder.Object);
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void
APiece::SetColor(EChessColor iColor)
{
	Color = iColor;

	
	switch (iColor)
	{
		default:
		case EChessColor::White:
		{
			UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/StarterContent/Materials/M_Basic_Wall"));
			StaticMeshComponent->SetMaterial(0, material);
		}
		break;

		case EChessColor::Black:
		{
			UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/StarterContent/Materials/M_Wood_Walnut"));
			StaticMeshComponent->SetMaterial(0, material);
		}
		break;
	}
}