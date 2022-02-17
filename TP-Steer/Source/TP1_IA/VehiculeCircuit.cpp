#include "VehiculeCircuit.h"

AVehiculeCircuit::AVehiculeCircuit(){PrimaryActorTick.bCanEverTick = true;}

void AVehiculeCircuit::BeginPlay(){Super::BeginPlay();}

void AVehiculeCircuit::Tick(float DeltaTime){
	if (AlgoCircuit == AlgoCuircuit::CIRCUIT) TargCirc();
	else if (AlgoCircuit == AlgoCuircuit::ONE_WAY) TargOne();
	else TargTwo(DeltaTime);
	FVector SteeringDirection = CalculDirection();
	FVector SteeringForce = Truncate(SteeringDirection, MaxForce);
	FVector Acceleration = SteeringForce / Mass;
	Velocity = Truncate(Velocity + Acceleration, MaxSpeed);
	SetActorLocation(GetActorLocation() + Velocity);
	SetActorRotation(FRotator(Velocity.Rotation()));
}

FVector AVehiculeCircuit::CalculDirection() {
	FVector Path = ListTargets[Index]->GetActorLocation();
	if (IsArrived) return ArrivalVelocity(Path);
	return SeekVelocity(Path);
}

void AVehiculeCircuit::TargCirc(){
	FVector Path = ListTargets[Index]->GetActorLocation();
	float Distance = (Path - GetActorLocation()).Size();
	if (Distance <= DistanceChangeTarget) Index += Direction;
	if (Index >= ListTargets.Num()) Index = 0;
}

void AVehiculeCircuit::TargOne(){
	if (IsArrived) return;
	FVector Path = ListTargets[Index]->GetActorLocation();
	float Distance = (Path - GetActorLocation()).Size();
	if (Distance <= DistanceChangeTarget) Index += Direction;
	if (Index >= ListTargets.Num()){
		IsArrived = true;
		Index = ListTargets.Num() - 1;
	}
}


void AVehiculeCircuit::TargTwo(float DeltaTime){
	FVector Path = ListTargets[Index]->GetActorLocation();
	float Distance = (Path - GetActorLocation()).Size();
	if (IsArrived){
		if (Distance <= 1.f) IsOnTarget = true;
		if (IsOnTarget){
			CurrentTime -= DeltaTime;
			if (CurrentTime <= 0){
				Direction = -Direction;
				IsArrived = false;
				IsOnTarget = false;
			}
		}
		return;
	}

	if (Distance <= DistanceChangeTarget) Index += Direction;
	if (Index >= ListTargets.Num()){
		IsArrived = true;
		Index = ListTargets.Num() - 1;
		CurrentTime = Time;
	}
	else if (Index <= 0 && Direction == -1){
		IsArrived = true;
		Index = 0;
		CurrentTime = Time;
	}
}


