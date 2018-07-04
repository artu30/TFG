// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetComponent.h"
#include "Components/ActorComponent.h"
#include "UseableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUseableDelegate);

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TFG_API UUseableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUseableComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Detector")
	void Mark();
	void Mark_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Detector")
	void UnMark();
	void UnMark_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Detector")
	void Use();
	void Use_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets") UWidgetComponent* InfoWidget;

	UPROPERTY() TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(BlueprintAssignable) FUseableDelegate OnUsed;
	UPROPERTY(BlueprintAssignable) FUseableDelegate OnMarked;
	UPROPERTY(BlueprintAssignable) FUseableDelegate OnUnmarked;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
