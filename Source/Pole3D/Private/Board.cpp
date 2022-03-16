
#include "Board.h"

ABoard::ABoard()
{
    USceneComponent* component = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
    SetRootComponent(component);
	RootComponent->bVisualizeComponent = true;
	RootComponent->Mobility = EComponentMobility::Movable;

    WhiteTileInstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("WhiteTileInstancedStaticMesh"));
    BlackTileInstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("BlackTileInstancedStaticMesh"));
    
    WhiteTileInstancedStaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    BlackTileInstancedStaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void
ABoard::Init(int iWidth, int iHeight, int iSpacing, UStaticMesh* iWhiteTileMesh, UStaticMesh* iBlackTileMesh)
{
    Width = iWidth;
    Height = iHeight;
    Spacing = iSpacing;
    WhiteTileMesh = iWhiteTileMesh;
    BlackTileMesh = iBlackTileMesh;

    WhiteTileInstancedStaticMesh->SetStaticMesh(WhiteTileMesh);
    BlackTileInstancedStaticMesh->SetStaticMesh(BlackTileMesh);

    GenerateTileMeshes();
}

void
ABoard::GenerateTileMeshes()
{
    WhiteTileInstancedStaticMesh->ClearInstances();
    BlackTileInstancedStaticMesh->ClearInstances();

    for(int y = 0; y < Height; y++)
    {
        for(int x = 0; x < Width; x++)
        {
            FTransform transform;
            transform.SetTranslation(FVector(x * Spacing, y * Spacing, -50));

            if ( x % 2 == y % 2 )
            {
                WhiteTileInstancedStaticMesh->AddInstance(transform);
            }
            else
            {
                BlackTileInstancedStaticMesh->AddInstance(transform);
            }
        }
    }
}
