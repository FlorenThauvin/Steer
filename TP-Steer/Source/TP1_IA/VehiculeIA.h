#pragma once
#include "CoreMinimal.h"
#include "Vehicule.h"
#include "VehiculeIA.generated.h"

UENUM()
enum AlgoUsing{
	SEEK	  UMETA(DisplayName = "Seek"),
	EVADE	  UMETA(DisplayName = "Evade"),
	FLEE	  UMETA(DisplayName = "Flee"),
	ARRIVAL   UMETA(DisplayName = "Arrival"),
	PURSUIT	  UMETA(DisplayName = "Pursuit"),
};

UCLASS()
class TP1_IA_API AVehiculeIA : public AVehicule{
	GENERATED_BODY()

public:
	AVehiculeIA();
	virtual void Tick(float Delta) override;
	FVector ArrivalVelocity(FVector TargetLocation);
	FVector SeekVelocity(FVector TargetLocation,bool IsShow);
	FVector FleeVelocity(FVector TargetLocation);
	FVector EvadeVelocity(float Delta);
	FVector PursuitVelocity(bool IsShow);
	void ChangeAlgo();
	AlgoUsing IntToEnum();

protected:
	virtual void BeginPlay() override;
	bool IsNew = false;
	float Time = 0;
	int Index = 0;
	UPROPERTY(EditAnywhere, Category = "Algo")
	TEnumAsByte<AlgoUsing> UsingAlgo;
	UPROPERTY(EditAnywhere, Category = "Algo")
	float SlowingDistance;
	UPROPERTY(EditAnywhere, Category = "Target")
	AVehicule* Target;
	UPROPERTY(EditAnywhere, Category = "Algo")
	float DistanceChange;
	FVector NewTargetEvade;
};
