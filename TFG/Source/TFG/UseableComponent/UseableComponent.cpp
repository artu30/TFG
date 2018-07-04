// Fill out your copyright notice in the Description page of Project Settings.

#include "UseableComponent.h"
#include "WidgetComponent.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UUseableComponent::UUseableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	InfoWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidget"));

	static ConstructorHelpers::FClassFinder<UUserWidget> UseableWidget(TEXT("/Game/Blueprints/UI/UseableHUD"));
	if (UseableWidget.Succeeded())
	{
		WidgetClass = UseableWidget.Class;
	}
}

// Called when the game starts
void UUseableComponent::BeginPlay()
{
	Super::BeginPlay();

	if (InfoWidget)
	{
		InfoWidget->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		InfoWidget->SetWidgetSpace(EWidgetSpace::Screen);
		InfoWidget->SetVisibility(false);
		InfoWidget->SetRelativeLocation(FVector(0, 0, 0));
		if (!InfoWidget->GetWidgetClass())
		{
			InfoWidget->SetWidgetClass(WidgetClass);
		}
	}
}


// Called every frame
void UUseableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UUseableComponent::Mark_Implementation()
{
	if (!GetOwner()->bHidden)
	{
		InfoWidget = (UWidgetComponent*)GetOwner()->GetComponentByClass(UWidgetComponent::StaticClass());
		if (InfoWidget)
		{
			if (!InfoWidget->IsVisible())
			{
				InfoWidget->SetVisibility(true);
				OnMarked.Broadcast();
			}
		}
	}
}

void UUseableComponent::UnMark_Implementation()
{
	if (!GetOwner()->bHidden)
	{
		InfoWidget = (UWidgetComponent*)GetOwner()->GetComponentByClass(UWidgetComponent::StaticClass());
		if (InfoWidget)
		{
			if (InfoWidget->IsVisible())
			{
				InfoWidget->SetVisibility(false);
				OnUnmarked.Broadcast();
			}
		}
	}
}

void UUseableComponent::Use_Implementation()
{
	if (!GetOwner()->bHidden)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, "Using Object.");
		}

		OnUsed.Broadcast();
	}
}