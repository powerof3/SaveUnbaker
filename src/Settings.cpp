#include "Settings.h"

#include <SimpleIni.h>
#undef ERROR

void Settings::LoadSettings()
{
	UpdateINISettings();
	
	const auto store = REX::FIniSettingStore::GetSingleton();
	store->Init(path.data(), "");

	store->Load();
	store->Save();
}

void Settings::UpdateINISettings()
{
	CSimpleIniA ini;
	ini.SetUnicode();

	if (ini.LoadFile(path.data()) < SI_OK) {
		return; 
	}

	if (ini.GetValue("Settings", "bNPCWeights")) {
		return;
	}

	for (auto& [section, oldKey, newKey] : GetSettingsToUpdate()) {
		CSimpleIniA::TNamesDepend values;
		if (ini.GetAllValues(section.data(), oldKey.data(), values) && !values.empty()) {
			const auto& entry = values.front();
			ini.SetValue(section.data(), newKey.data(), entry.pItem, entry.pComment);
			ini.Delete(section.data(), oldKey.data(), true);
			REX::INFO("Migrated [{}] {} -> {}", section, oldKey, newKey);
		}
	}

	ini.Delete("Settings", "Auto Update NPC Weights", true);

	(void)ini.SaveFile(path.data());
}
