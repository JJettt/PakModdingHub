﻿#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FortniteGame.h"
#include "FortInitializationInterface.h"
#include "FortniteGame.h"
#include "FortPawn.h"
#include "FortPlayerState.h"
#include "FortMusicManager.generated.h"

class AFortPlayerController;
class UFortMusicAsset;
class UFortMusicManagerBank;

UDELEGATE(BlueprintCallable) DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMusicVoiceEvent, UFortMusicVoice*, Voice);


USTRUCT(BlueprintType)
struct FORTNITEGAME_API FFortPlayerDeathReport {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    float ServerTimeForRespawn;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    float ServerTimeForResurrect;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    float LethalDamage;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AFortPlayerState* KillerPlayerState;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AFortPawn* KillerPawn;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AActor* DamageCauser;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    uint8 bDroppedBackpack: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    uint8 bNotifyUI: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FGameplayTagContainer Tags;
};

UCLASS(Blueprintable)
class UFortMusicVoice : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnMusicVoiceEvent OnVoiceStarted;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnMusicVoiceEvent OnVoiceFinished;
    
    UFortMusicVoice();
};

UCLASS(Blueprintable)
class AFortMusicManager : public AActor, public IFortInitializationInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AFortPlayerController* ControllerOwner;
    
private:
    UPROPERTY(EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UFortMusicVoice* Voices[2];
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<UFortMusicVoice*> VoicesToCleanUp;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    uint8 bWorldReadyCalled: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UFortMusicManagerBank* MusicBank;
    
public:
    AFortMusicManager();
    UFUNCTION(BlueprintCallable)
    void StopPrimaryMusic(bool bPlayOutro);
    
    UFUNCTION(BlueprintCallable)
    void StopMusicVoice(UFortMusicVoice* Voice);
    
protected:
    UFUNCTION(BlueprintCallable)
    void SetPrimaryMusicVolume(float InVolumeMultiplier);
    
public:
    UFUNCTION(BlueprintCallable)
    void SetMusicBank(UFortMusicManagerBank* Bank);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void PlayStinger(UFortMusicAsset* NewMusicAsset);
    
    UFUNCTION(BlueprintCallable)
    UFortMusicVoice* PlayMusicVoice(UFortMusicAsset* Asset);
    
private:
    UFUNCTION(BlueprintCallable)
    void OnVoiceFinished(UFortMusicVoice* Voice);
    
public:
    //UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
  // void OnThresholdChange(TEnumAsByte<EFortCombatThresholds::Type> OldThreshold, TEnumAsByte<EFortCombatThresholds::Type> NewThreshold);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPlayerSpawned();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPlayerDowned(const FFortPlayerDeathReport& DeathReport);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnMusicBankChanged(UFortMusicManagerBank* NewBank);
    
    //UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
   // void OnDayPhaseChanged(TEnumAsByte<EFortDayPhase> CurrentDayPhase, TEnumAsByte<EFortDayPhase> PreviousDayPhase, bool bAtCreation);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetPrimaryMusicVolume() const;
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UFortMusicManagerBank* GetMusicBank() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetEventHeatPercentTotal(TEnumAsByte<EFortCombatEvents::Type> CombatEvent);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetEventHeatPercent(TEnumAsByte<EFortCombatEvents::Type> CombatEvent);
    
    UFUNCTION(BlueprintCallable)
    UFortMusicVoice* ChangePrimaryMusic(UFortMusicAsset* NewMusicAsset, bool bPlayStinger);
    
    
    // Fix for true pure virtual functions not being implemented
    UFUNCTION()
    void WorldReady() override PURE_VIRTUAL(WorldReady,);
    
    UFUNCTION()
    bool NeedsWorldReady() const override PURE_VIRTUAL(NeedsWorldReady, return false;);
    
    UFUNCTION()
    void MatchStarted() override PURE_VIRTUAL(MatchStarted,);
    
};

