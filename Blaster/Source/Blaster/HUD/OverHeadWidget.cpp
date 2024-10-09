// Fill out your copyright notice in the Description page of Project Settings.


#include "OverHeadWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverHeadWidget::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverHeadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	// ENetRole RemoteRole = InPawn->GetRemoteRole();
	// FString Role;
	// switch (RemoteRole)
	// {
	// case ROLE_Authority:
	// 	Role = FString("Authority");
	// 	break;
	// case ROLE_AutonomousProxy:
	// 	Role = FString("Autonomous Proxy");
	// 	break;
	// case ROLE_SimulatedProxy:
	// 	Role = FString("Simulated Proxy");
	// 	break;
	// case ROLE_None:
	// 	Role = FString("None");
	// 	break;
	// }
	// FString RemoteRoleString = FString::Printf(TEXT("Remote Role: %s"), *Role);
	// SetDisplayText(RemoteRoleString);
}

void UOverHeadWidget::ShowPlayerName(APawn* InPawn)
{
	const TObjectPtr<APlayerState> PlayerState = InPawn->GetPlayerState();

	if (!PlayerState)
	{
		SetDisplayText(FString("No Player State"));
		return;
	}
	SetDisplayText(PlayerState->GetPlayerName());
}

void UOverHeadWidget::NativeDestruct()
{
	RemoveFromParent();
	
	Super::NativeDestruct();
}
