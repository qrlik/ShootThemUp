#pragma once

class STUUtils {
public:
	static APawn* GetPawn(const AController* Controller);
	static AController* GetController(const AActor* Actor);

	template <typename T>
	static T* GetComponentByClass(const AActor* Pawn) {
		if (Pawn) {
			if (auto* Component = Pawn->GetComponentByClass<T>()) {
				return Component;
			}
		}
		return nullptr;
	}

	template <typename T = APlayerState>
	static T* GetPlayerState(const AController* Controller) {
		if (Controller) {
			if (auto* PlayerState = Controller->GetPlayerState<T>()) {
				return PlayerState;
			}
		}
		return nullptr;
	}

	template <typename T = AGameModeBase>
	static T* GetGameMode(const UWorld* World) {
		if (World) {
			if (auto* GameMode = World->GetAuthGameMode<T>()) {
				return GameMode;
			}
		}
		return nullptr;
	}

	static bool AreEnemies(const AController* Lhs, const AController* Rhs);
};
