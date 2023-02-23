#include "Settings.h"

Settings::Settings()
{
	constexpr auto path = L"Data/SKSE/Plugins/po3_SaveUnbaker.ini";

	CSimpleIniA ini;
	ini.SetUnicode();

	ini.LoadFile(path);

	//	1.0.2
	ini.Delete("Settings", "Auto Update NPC Weights", true);

	ini::get_value(ini, npcWeights, "Settings", "NPC Weights", ";Unbake NPC weights");
	ini::get_value(ini, oppositeGenderAnims, "Settings", "OppositeGenderAnims Flag", ";Unbake OppositeGenderAnims Flag.");
	ini::get_value(ini, persistentTransforms, "Settings", "Persistent Ref Transforms", ";Unbake persistent reference position/rotation\n;Only affects immovable references (ie. statics, furniture, anything that cannot be moved using scripts)");

	(void)ini.SaveFile(path);
}
