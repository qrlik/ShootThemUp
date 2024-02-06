#pragma once

class STUUtils {
public:
	static APawn* GetPawn(const AController* Controller);

	template <typename T>
	static T* GetComponentByClass(AActor* Pawn) {
		if (Pawn) {
			if (auto* Component = Pawn->GetComponentByClass<T>()) {
				return Component;
			}
		}
		return nullptr;
	}
};
