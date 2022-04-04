
#include "Board.h"
#include "InteractiveTile.h"

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

    FTransform transform;
    transform.SetTranslation( FVector( Spacing / 2 ));
    RootComponent->AddWorldTransform(transform);

    WhiteTileInstancedStaticMesh->SetStaticMesh(WhiteTileMesh);
    BlackTileInstancedStaticMesh->SetStaticMesh(BlackTileMesh);

    GenerateTileMeshes();
}

void
ABoard::GenerateTileMeshes()
{
    Tiles.Empty();
    WhiteTileInstancedStaticMesh->ClearInstances();
    BlackTileInstancedStaticMesh->ClearInstances();

    UMaterialInterface* material = LoadObject<UMaterialInterface>(this, TEXT("/Game/Materials/TransparentMaterial"));

    for(int y = 0; y < Height; y++)
    {
        for(int x = 0; x < Width; x++)
        {
            FTransform transform;
            transform.SetTranslation(FVector(x * Spacing, y * Spacing, -Spacing / 2));

            if ( x % 2 == y % 2 )
            {
                WhiteTileInstancedStaticMesh->AddInstance(transform);
            }
            else
            {
                BlackTileInstancedStaticMesh->AddInstance(transform);
            }

            Tiles.Add( FIntPoint(x, y), GetWorld()->SpawnActor<AInteractiveTile>(FVector(x * Spacing, y * Spacing, 1), FRotator(0, 0, 0)) );
            Tiles[FIntPoint(x,y)]->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
            Tiles[FIntPoint(x,y)]->StaticMeshComponent->SetMaterial(0, material);
        }
    }
}
