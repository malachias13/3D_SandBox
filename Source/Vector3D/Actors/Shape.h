// Copyright 2023, Malachias Harris, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Vector3D/Interfaces/ShapeInterace.h"
#include "Shape.generated.h"

UCLASS()
class VECTOR3D_API AShape : public AActor, public IShapeInterace
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShape();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ChangeColor(FLinearColor color);

public:
	// Inherited via IShapeInterace
	virtual void ChangeMeshColor(FLinearColor color) override;

};
