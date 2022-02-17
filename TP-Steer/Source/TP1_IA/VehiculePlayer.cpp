#include "VehiculePlayer.h"
#include "VehiculeIA.h"
#include <Components/InputComponent.h>

AVehiculePlayer::AVehiculePlayer(){PrimaryActorTick.bCanEverTick = true;}

void AVehiculePlayer::BeginPlay(){
	Super::BeginPlay();
	BindInput();
}

void AVehiculePlayer::BindInput(){
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		InputComponent->BindAction("ChangeAlgo", IE_Pressed, this, &AVehiculePlayer::Change);
		InputComponent->BindAxis("MoveForward", this, &AVehiculePlayer::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &AVehiculePlayer::MoveRight);

		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void AVehiculePlayer::Tick(float DeltaTime){
	FVector SteeringForce = Truncate(Direction, MaxForce);
	FVector Acceleration = SteeringForce / Mass;
	Velocity = Truncate(Velocity + Acceleration, MaxSpeed);
	SetActorLocation(GetActorLocation() + Velocity);
	SetActorRotation(FRotator(Velocity.Rotation()));
}

void AVehiculePlayer::Change(){
	AVehiculeIA* IA = Cast<AVehiculeIA>(Vehicule);
	if (IA) IA->ChangeAlgo();
}

void AVehiculePlayer::MoveForward(float Value){
	Direction = FVector(Direction.X + Value, Direction.Y, Direction.Z);
}

void AVehiculePlayer::MoveRight(float Value){
	Direction = FVector(Direction.X, Direction.Y + Value, Direction.Z);

}