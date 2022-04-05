#include "Pieces/ChessPawn.h"

AChessPawn::AChessPawn()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/Meshes/Pawn"));
	StaticMeshComponent->SetStaticMesh(staticMeshFinder.Object);
}

TArray<FMove> AChessPawn::GetPiecePossibleMoves()
{
	TArray<FMove> possibleMoves;
	
	if (bIsWhite)
	{
		possibleMoves.Add( FMove( kCantTakePiece, kCanBeTaken, kBlockedByPieces, kFixedLength, FIntPoint( 0, 1 ), 1 ) );
		possibleMoves.Add( FMove( kMustTakePiece, kCanBeTaken, kBlockedByPieces, kFixedLength, FIntPoint( -1, 1 ), 1 ) );
		possibleMoves.Add( FMove( kMustTakePiece, kCanBeTaken, kBlockedByPieces, kFixedLength, FIntPoint( 1, 1 ), 1 ) );

		if( bFirstMove )
			possibleMoves.Add( FMove( kCantTakePiece, kCanBeTaken, kBlockedByPieces, kFixedLength, FIntPoint( 0, 1 ), 2 ) );
	}
    else
    {
        possibleMoves.Add(FMove(kCantTakePiece, kCanBeTaken, kBlockedByPieces, kFixedLength, FIntPoint(0, -1), 1));
        possibleMoves.Add(FMove(kMustTakePiece, kCanBeTaken, kBlockedByPieces, kFixedLength, FIntPoint(-1, -1), 1));
        possibleMoves.Add(FMove(kMustTakePiece, kCanBeTaken, kBlockedByPieces, kFixedLength, FIntPoint(1, -1), 1));

        if (bFirstMove)
            possibleMoves.Add(FMove(kCantTakePiece, kCanBeTaken, kBlockedByPieces, kFixedLength, FIntPoint(0, -1), 2));
    }

	return possibleMoves;
}
