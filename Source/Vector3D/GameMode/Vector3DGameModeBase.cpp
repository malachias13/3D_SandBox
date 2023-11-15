// Copyright 2023, Malachias Harris, All rights reserved


#include "Vector3DGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "Vector3D/Interfaces/ShapeInterace.h"

void AVector3DGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithInterface(this, UShapeInterace::StaticClass(), ShapeActors);
}
