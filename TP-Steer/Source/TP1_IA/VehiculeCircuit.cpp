#include "VehiculeCircuit.h"

AVehiculeCircuit::AVehiculeCircuit() { PrimaryActorTick.bCanEverTick = true; }

void AVehiculeCircuit::BeginPlay() { Super::BeginPlay(); }

void AVehiculeCircuit::Tick(float Delta) {
	if (AlgoCircuit == AlgoCuircuit::CIRCUIT) TargCirc();				
	else if (AlgoCircuit == AlgoCuircuit::ONE_WAY) TargOne();						
	else TargTwo();														
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
	return SeekVelocity(Path,false);
}

float AVehiculeCircuit::TargPath() {
	/*
	Vector qui récupère les coordonnées X,Y,Z du prochain point
	*/
	FVector Path = ListTargets[Index]->GetActorLocation();
	return (Path - GetActorLocation()).Size();

}


void AVehiculeCircuit::TargCirc() {
	/*
	the character follows a path continuously. The end of the path rejoins the
	beginning, so that the character keeps following the same path indefinitely.
	*/
	float Distance = TargPath();
	if (Distance <= DistanceChangeTarget) Index += Direction;			// quand le prochain Waypoint est proche on change de destination
	if (Index >= ListTargets.Num()) Index = 0;							// on reprend la liste depuis le départ
}

void AVehiculeCircuit::TargOne() {
	/*
	the character follows a path that ends in a certain point. The character “arrives”
	at that point and stops.
	*/
	if (IsArrived) return;				// si il est arrivé on stop
	float Distance = TargPath();		
	if (Distance <= DistanceChangeTarget) Index += Direction;   // quand le prochain Waypoint est proche on change de destination
	if (Index >= ListTargets.Num()) {							// on vérifie qu'il est bien sur le dernier
		IsArrived = true;
		Index = ListTargets.Num() - 1;
	}
}


void AVehiculeCircuit::TargTwo() {
	/*
	the character follows a path that ends in a certain point. The character
	“arrives” at that point and then starts to follow the path on the opposite direction. When
	the character “arrives” at the starting point, it starts to follow the path on the original
	direction again.
	*/
	float Distance = TargPath();
	if (Distance <= DistanceChangeTarget){		// quand le prochain Waypoint est proche on change de destination
		Index += Direction;
		if (Index >= ListTargets.Num() || Index == 0) {
			if(Direction==1)Index = ListTargets.Num() - 1;		// on décremente quand on est sur le dernier
			Direction = -Direction;								// on change de direction								
		}
	}
}

