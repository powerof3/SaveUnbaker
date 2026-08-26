#pragma once

class Settings : public REX::TSingleton<Settings>
{
public:
	void LoadSettings();

	// members
	static constexpr auto path = "Data/SKSE/Plugins/po3_SaveUnbaker.ini"sv;

	REX::TIniSetting<bool> npcWeights{ "Settings", "bNPCWeights", true };
	REX::TIniSetting<bool> oppositeGenderAnims{ "Settings", "bOppositeGenderAnimsFlag", true };
	REX::TIniSetting<bool> persistentTransforms{ "Settings", "bPersistentRefTransforms", true };
};
