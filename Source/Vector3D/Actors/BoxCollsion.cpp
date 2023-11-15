// Copyright 2023, Malachias Harris, All rights reserved


#include "BoxCollsion.h"
#include "Vector3D/GameMode/Vector3DGameModeBase.h"
#include <DrawDebugHelpers.h>
#include <Components/BoxComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include "Kismet/GameplayStatics.h"
#include "Vector3D/Interfaces/ShapeInterace.h"

// Sets default values
ABoxCollsion::ABoxCollsion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollsion = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollsion"));
	BoxCollsion->SetBoxExtent(FVector(200, 200, 160));
	BoxCollsion->bHiddenInGame = false;
}

// Called when the game starts or when spawned
void ABoxCollsion::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AVector3DGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
}

// Called every frame
void ABoxCollsion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CollsionPoints.Reset();
	UpdateCollsionPoints();
	DrawDebugPoints();

	if (GameMode) {
		for (int i = 0; i < GameMode->ShapeActors.Num(); i++) {

			IShapeInterace* Interface = Cast<IShapeInterace>(GameMode->ShapeActors[i]);
			if (Interface) {
				if(IsZBetween(GameMode->ShapeActors[i]->GetActorLocation()) == false || 
					SumOfAreas(GameMode->ShapeActors[i]->GetActorLocation()) > CollsionBoxArea()) {
					Interface->ChangeMeshColor(FColor::White);
				}
				else {
					Interface->ChangeMeshColor(FColor(219,172,52));
				}
			}
		}
	}



}

float ABoxCollsion::FindAreaOfTriangle(FVector a, FVector b, FVector c)
{
	return 0.5 * FMath::Abs((a.X*(b.Y - c.Y) + b.X * (c.Y - a.Y) + c.X*(a.Y - b.Y)));
}

float ABoxCollsion::SumOfAreas(FVector point)
{
	return FindAreaOfTriangle(CollsionPoints[0], point, CollsionPoints[3]) +
	FindAreaOfTriangle(CollsionPoints[3], point, CollsionPoints[2]) +
	FindAreaOfTriangle(CollsionPoints[2], point, CollsionPoints[1]) +
	FindAreaOfTriangle(point, CollsionPoints[1], CollsionPoints[0]);
}

float ABoxCollsion::CollsionBoxArea()
{
	return FMath::Abs(CollsionPoints[0].X - CollsionPoints[1].X)* FMath::Abs(CollsionPoints[1].Y - CollsionPoints[2].Y);
}

bool ABoxCollsion::IsZBetween(FVector point)
{
	return ( point.Z >= CollsionPoints[0].Z && point.Z <= CollsionPoints[7].Z);
}

void ABoxCollsion::UpdateCollsionPoints()
{
	int x = 1; int y = 1; int z = 1;

	for (int i = 0; i < 8; i++) {

		switch (i)
		{
		case 1:
			x = -1;
			break;
		case 2:
			x = -1;
			y = -1;
			break;
		case 3:
			x = 1;
			y = -1;
			break;
		case 4:
			x = 1;
			y = 1;
			z = -1;
			break;
		case 5:
			x = -1;
			y = 1;
			z = -1;
			break;
		case 6:
			x = -1;
			y = -1;
			z = -1;
			break;
		case 7:
			x = 1;
			y = -1;
			z = -1;
			break;

		default:
			break;
		}

		CollsionPoints.Add(UKismetMathLibrary::ConvertTransformToRelative(
			FTransform(FVector(BoxCollsion->GetUnscaledBoxExtent().X * x, BoxCollsion->GetUnscaledBoxExtent().Y * y,
				BoxCollsion->GetUnscaledBoxExtent().Z * z))
			, GetActorTransform()).GetLocation());
	}

}

void ABoxCollsion::DrawDebugPoints()
{
	for (int i = 0; i < CollsionPoints.Num(); i++) {
		DrawDebugSphere(GetWorld(), CollsionPoints[i], 6, 8, FColor::Emerald);
	}
}

