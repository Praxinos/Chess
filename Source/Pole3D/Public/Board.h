#pragma once

#include "CoreMinimal.h"

#include "Pieces/Piece.h"

#include "Board.generated.h"

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
    int Width = 8;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Height = 8;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Spacing = 64;

    UPROPERTY()
    UInstancedStaticMeshComponent* WhiteTileInstancedStaticMesh;

    UPROPERTY()
    UInstancedStaticMeshComponent* BlackTileInstancedStaticMesh;

    UPROPERTY(EditAnywhere)
    UStaticMesh* WhiteTileMesh;

    UPROPERTY(EditAnywhere)
    UStaticMesh* BlackTileMesh;

    UPROPERTY()
    TArray<APiece*> Tiles;
};