// Copyright 2023, Malachias Harris, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxCollsion.generated.h"

UCLASS()
class VECTOR3D_API ABoxCollsion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxCollsion();

protected:
	UPROPERTY(VisibleAnyWhere)
	class UBoxComponent* BoxCollsion;

	TArray<FVector> CollsionPoints;
	class AVector3DGameModeBase* GameMode;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float FindAreaOfTriangle(FVector a, FVector b, FVector c);
	float SumOfAreas(FVector point);
	float CollsionBoxArea();
	bool IsZBetween(FVector point);
	void UpdateCollsionPoints();

	// Debug.
	void DrawDebugPoints();


};
