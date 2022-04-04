#pragma once

#include "CoreMinimal.h"

#include "Board.generated.h"

class AInteractiveTile;

UCLASS(MinimalAPI, Blueprintable)
class ABoard : public AActor
{
    GENERATED_BODY()
    ABoard();

public:
    void Init(int iWidth, int iHeight, int iSpacing, UStaticMesh* iWhiteTileMesh, UStaticMesh* iBlackTileMesh);

    void GenerateTileMeshes();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Width;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Height;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Spacing;

    UPROPERTY()
    UInstancedStaticMeshComponent* WhiteTileInstancedStaticMesh;

    UPROPERTY()
    UInstancedStaticMeshComponent* BlackTileInstancedStaticMesh;

    UPROPERTY(EditAnywhere)
    UStaticMesh* WhiteTileMesh;

    UPROPERTY(EditAnywhere)
    UStaticMesh* BlackTileMesh;

    TMap<FIntPoint, AInteractiveTile*> Tiles;
};