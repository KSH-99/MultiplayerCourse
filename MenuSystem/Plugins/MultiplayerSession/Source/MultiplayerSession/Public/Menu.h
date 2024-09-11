// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSION_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPublicConnections = 4, FString TypeOfMatch = FString(TEXT("FreeForAll")));

protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;
	
	// MultiplayerSessionSubsystem에서 커스텀 델리게이트에 대한 콜백들
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	
private:
    UPROPERTY(meta = (BindWidget)) // 이것을 하면 변수이름과 에디터 내에 버튼(다른것들도 포함) 이름이 같아야함
    class UButton* HostButton;
    
    UPROPERTY(meta = (BindWidget))
    UButton* JoinButton;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	void MenuTearDown();

	//모든 온라인 세션 기능을 처리하도록 설계된 subsystem
	class UMultiplayerSessionSubsystem* MultiplayerSessionSubsystem;

	int32 NumPublicConnections{4};
	FString MatchType{TEXT("FreeForAll")};
};
