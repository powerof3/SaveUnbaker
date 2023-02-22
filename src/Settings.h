#pragma once

class Settings
{
public:
	[[nodiscard]] static Settings* GetSingleton()
	{
		static Settings singleton;
		return std::addressof(singleton);
	}

	bool npcWeights{ true };
	bool autoUpdateWeights{ true };
	bool oppositeGenderAnims{ true };
	bool persistentTransforms{ true };

private:
	Settings();
};
