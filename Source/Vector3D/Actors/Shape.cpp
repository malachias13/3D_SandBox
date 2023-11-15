// Copyright 2023, Malachias Harris, All rights reserved


#include "Shape.h"

// Sets default values
AShape::AShape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(Mesh);

	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	Mesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AShape::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShape::ChangeColor(FLinearColor color)
{
	if (Mesh && Mesh->GetStaticMesh()) {
		Mesh->SetVectorParameterValueOnMaterials("Color", FVector(color));
	}
}

void AShape::ChangeMeshColor(FLinearColor color)
{
	ChangeColor(color);
}


