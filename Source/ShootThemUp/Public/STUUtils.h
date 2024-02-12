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

	static bool AreEnemies(const AController* Lhs, const AController* Rhs);
};
