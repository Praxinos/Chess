// Fill out your copyright notice in the Description page of Project Settings.

#include "Board.h"

// Sets default values
ABoard::ABoard()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>("DefaultRootComponent");
    RootComponent->bVisualizeComponent = true;

    WhiteTileInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>("WhiteTileInstancedStaticMesh");
    BlackTileInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>("BlackTileInstancedStaticMesh");

    WhiteTileInstancedMesh->AttachToComponent( RootComponent, FAttachmentTransformRules::KeepRelativeTransform );
    BlackTileInstancedMesh->AttachToComponent( RootComponent, FAttachmentTransformRules::KeepRelativeTransform );
}

void ABoard::Init( int iSizeX, int iSizeY, int iAssetSize, UStaticMesh* iWhiteTileMesh, UStaticMesh* iBlackTileMesh )
{
    SizeX = iSizeX;
    SizeY = iSizeY;
    AssetSize = iAssetSize;
    WhiteTileMesh = iWhiteTileMesh;
    BlackTileMesh = iBlackTileMesh;

    WhiteTileInstancedMesh->SetStaticMesh( WhiteTileMesh );
    BlackTileInstancedMesh->SetStaticMesh( BlackTileMesh );

    GenerateBoard();
}

void ABoard::GenerateBoard()
{
    WhiteTileInstancedMesh->ClearInstances();
    BlackTileInstancedMesh->ClearInstances();

    for( int y = 0; y < SizeY; y++ )
    {
        for (int x = 0; x < SizeX; x++)
        {
            FTransform transform;
            transform.SetTranslation( FVector( x * AssetSize, y * AssetSize, 0 ) );

            if ((x + y) % 2 == 0)
            {
                WhiteTileInstancedMesh->AddInstance(transform);
            }
            else
            {
                BlackTileInstancedMesh->AddInstance(transform);
            }
            transform.AddToTranslation( FVector( 0, 0, AssetSize / 2 + 1 ));
            Tiles.Add( FIntPoint(x,y), GetWorld()->SpawnActor<AInteractiveTile>( AInteractiveTile::StaticClass(), transform ));
        }
    }
}

