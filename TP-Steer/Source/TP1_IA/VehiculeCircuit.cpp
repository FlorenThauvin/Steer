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

void AVehiculeCircuit::TargCirc() {
	/*
	The character follows a path continuously. The end of the path rejoins the
	beginning, so that the character keeps following the same path indefinitely.
	*/
	FVector Path = ListTargets[Index]->GetActorLocation();
	float Dist = (Path - GetActorLocation()).Size();
	if (Dist <= DistanceChangeTarget) Index += Direction;
	if (Index >= ListTargets.Num()) Index = 0;
}

void AVehiculeCircuit::TargOne(){
	/*
	The character follows a path that ends in a certain point. The character “arrives”
	at that point and stops.
	*/
	if (IsArrived) return;
	FVector Path = ListTargets[Index]->GetActorLocation();
	float Dist = (Path - GetActorLocation()).Size();
	if (Dist <= DistanceChangeTarget) Index += Direction;
	if (Index >= ListTargets.Num()) {
		IsArrived = true;
		Index = ListTargets.Num() - 1;
	}
}


void AVehiculeCircuit::TargTwo(float DeltaTime){
	/*
	the character follows a path that ends in a certain point. The character
	“arrives” at that point and then starts to follow the path on the opposite direction. When
	the character “arrives” at the starting point, it starts to follow the path on the original
	direction again.
	*/
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
			}}return;}
	if (Distance <= DistanceChangeTarget) Index += Direction;
	if (Index >= ListTargets.Num()){
		IsArrived = true;
		Index = ListTargets.Num() - 1;
		CurrentTime = Time;
		if (Index <= 0 && Direction == -1) Index = 0;
		else Index = ListTargets.Num() - 1;
	}
}


