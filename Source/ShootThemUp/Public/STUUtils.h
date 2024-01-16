#pragma once

class STUUtils {
public:
	template <typename T>
	static T* GetComponentByClass(APawn* Pawn) {
		if (Pawn) {
			if (auto* Component = Pawn->GetComponentByClass<T>()) {
				return Component;
			}
		}
		return nullptr;
	}
};
