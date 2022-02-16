#include "Vehicule.h"

AVehicule::AVehicule()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AVehicule::BeginPlay(){Super::BeginPlay();}

void AVehicule::Tick(float DeltaTime){Super::Tick(DeltaTime);}

FVector AVehicule::Truncate(FVector v, float maxi)
{
	if (v.Size() > maxi){
		v.Normalize();
		return  v * maxi;
	}
	else return v;
}