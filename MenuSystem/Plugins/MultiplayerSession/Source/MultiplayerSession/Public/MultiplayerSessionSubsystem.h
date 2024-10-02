// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiplayerSessionSubsystem.generated.h"

//Menu 클래스에서 콜백을 바인딩하기 위한 사용자 정의 델리게이트 선언
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccessful); //대리자 이름, 타입, 매개변수 순
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindSessionComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FMultiplayerOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroySessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionComplete, bool, bWasSuccessful);

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSION_API UMultiplayerSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerSessionSubsystem();

	//세션 기능을 처리합니다. 메뉴 클래스는 다음과 같이 부릅니다
	void CreateSession(int32 NumPublicConnections, FString MatchType);
	void FindSession(int32 MaxSearchResult);
	void JoinSession(const FOnlineSessionSearchResult& SearchResult);
	void DestroySession();
	void StartSession();

	// 콜백을 바인딩하기 위해 Menu 클래스에 대한 커스텀 델리게이트들
	FMultiplayerOnCreateSessionComplete MultiplayerOnCreateSessionComplete;
	FMultiplayerOnFindSessionComplete MultiplayerOnFindSessionComplete;
	FMultiplayerOnJoinSessionComplete MultiplayerOnJoinSessionComplete;
	FMultiplayerOnDestroySessionComplete MultiplayerOnDestroySessionComplete;
	FMultiplayerOnStartSessionComplete MultiplayerOnStartSessionComplete;
protected:

	 // 온라인 세션 인터페이스 대리자 목록에 추가할 대리자에 대한 콜백입니다.
	 // 이것들은 클래스 외부에서 호출할 필요가 없습니다
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	
private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;
	
	// 온라인 세션 인터페이스 대리자 목록을 추가합니다.
	// 멀티플레이어 세션 서브시스템 콜백을 여기에 바인딩합니다. 
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate; // 세션 생성 대리자
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate; // 세션 탐색 대리자
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate; // 세션 참가 대리자
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate; //세션 파괴 대리자
	FDelegateHandle DestroySessionCompleteDelegateHandle;
	
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate; //세션 시작 대리자
	FDelegateHandle StartSessionCompleteDelegateHandle;

	bool bCreateSessionOnDestroy{false};
	int32 LastNumPublicConnections;
	FString LastMatchType;
};
