#pragma once

class Settings : public REX::TSingleton<Settings>
{
public:
	template <class T>
	class Setting : public REX::TIniSetting<T>
	{
	public:
		Setting(std::string_view a_section, std::string_view a_oldKey, std::string_view a_newKey, T a_default) :
			REX::TIniSetting<T>(a_section, a_newKey, a_default)
		{
			GetSettingsToUpdate().emplace_back(a_section, a_oldKey, a_newKey);
		}
	};

	struct SettingsToUpdate
	{
		std::string_view section;
		std::string_view oldKey;
		std::string_view newKey;
	};

	void LoadSettings();

	// members
	static constexpr auto path = "Data/SKSE/Plugins/po3_SaveUnbaker.ini"sv;

	Setting<bool> npcWeights{ "Settings", "NPC Weights", "bNPCWeights", true };
	Setting<bool> oppositeGenderAnims{ "Settings", "OppositeGenderAnims Flag", "bOppositeGenderAnimsFlag", true };
	Setting<bool> persistentTransforms{ "Settings", "Persistent Ref Transforms", "bPersistentRefTransforms", true };

private:
	static std::vector<SettingsToUpdate>& GetSettingsToUpdate()
	{
		static std::vector<SettingsToUpdate> settings;
		return settings;
	}

	void UpdateINISettings();
};
