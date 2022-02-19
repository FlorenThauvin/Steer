#include "VehiculeIA.h"

AVehiculeIA::AVehiculeIA(){PrimaryActorTick.bCanEverTick = true;}

void AVehiculeIA::BeginPlay(){Super::BeginPlay();}

void AVehiculeIA::Tick(float Delta){
	Super::Tick(Delta);
	FVector TargetLocation = Target->GetActorLocation();
	FVector SteeringDirection;
	if (UsingAlgo == AlgoUsing::SEEK) SteeringDirection = SeekVelocity(TargetLocation,true);
	else if (UsingAlgo == AlgoUsing::PURSUIT) SteeringDirection = PursuitVelocity(true);
	else if (UsingAlgo == AlgoUsing::ARRIVAL) SteeringDirection = ArrivalVelocity(TargetLocation);
	else if (UsingAlgo == AlgoUsing::EVADE) SteeringDirection = EvadeVelocity(Delta);
	else SteeringDirection = FleeVelocity(TargetLocation);
	FVector SteeringForce = Truncate(SteeringDirection, MaxForce);
	FVector Acceleration = SteeringForce / Mass;
	Velocity = Truncate(Velocity + Acceleration, MaxSpeed);
	SetActorLocation(GetActorLocation() + Velocity);
	SetActorRotation(FRotator(Velocity.Rotation()));
}

FVector AVehiculeIA::SeekVelocity(FVector TargetLocation,bool IsShow){
	/*
	The character moves in order to reach a fixed target.
	*/
	if(IsShow)GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, TEXT("SEEK"));
	FVector VectorDist = TargetLocation - GetActorLocation();
	VectorDist.Normalize();
	FVector VelocityDesired = VectorDist * MaxSpeed;
	return VelocityDesired - Velocity;
}


FVector AVehiculeIA::ArrivalVelocity(FVector TargetLocation){
	/*
	The character moves in order to stop on a fixed target.
	*/
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, TEXT("ARRIVAL"));
	FVector VectorDist = TargetLocation - GetActorLocation();
	float Distance = VectorDist.Size();
	float RampedSpeed = MaxSpeed * (Distance / SlowingDistance);
	float ClippedSpeed = FMath::Min(RampedSpeed, MaxSpeed);
	FVector VelocityDesired = VectorDist * (ClippedSpeed / Distance);
	return VelocityDesired - Velocity;
}

FVector AVehiculeIA::FleeVelocity(FVector TargetLocation){
	/*
	The character moves away from a fixed target.
	*/
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, TEXT("FLEE"));
	FVector VectorDist = TargetLocation - GetActorLocation();
	VectorDist = -VectorDist;
	VectorDist.Normalize();
	FVector VelocityDesired = VectorDist * MaxSpeed;
	return VelocityDesired - Velocity;
}

FVector AVehiculeIA::PursuitVelocity(bool IsShow){
	/*
	The character moves in order to intercept a moving target
	*/
	if(IsShow)GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, TEXT("PURSUIT"));
	float Dot = FVector::DotProduct(Target->GetVelocity().GetSafeNormal(), (GetActorLocation() - Target->GetActorLocation()).GetSafeNormal());
	float Para;
	float Distance = (Target->GetActorLocation() - GetActorLocation()).Size();
	if (Dot >= 0) Para = 1 - Dot;
	else Para = 1;
	float T = Distance / Velocity.Size() * Para;
	FVector FuturTarget = Target->GetVelocity() * T;
	return SeekVelocity(Target->GetActorLocation() + FuturTarget,false);
}

FVector AVehiculeIA::EvadeVelocity(float DeltaTime){
	/*The character moves in order to evade a pursuer.*/
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, TEXT("EVADE")); 
	return -PursuitVelocity(false);
}


void AVehiculeIA::ChangeAlgo(){
	Index = (Index + 1) % 5;
	UsingAlgo = IntToEnum();
}

AlgoUsing AVehiculeIA::IntToEnum(){
	switch (Index){
	case 0:
		return AlgoUsing::SEEK;
	case 1:
		return AlgoUsing::FLEE;
	case 2:
		return AlgoUsing::PURSUIT;
	case 3:
		return AlgoUsing::EVADE;
	default:
		return AlgoUsing::ARRIVAL;
	}
}