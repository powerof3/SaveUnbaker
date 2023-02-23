#include "Hooks.h"
#include "Settings.h"

namespace Hooks
{
	namespace Character
	{
		struct LoadGame
		{
			static void thunk(RE::Character* a_this, std::uintptr_t a_buf)
			{
				const auto npc = a_this->GetActorBase();
			    const auto weight = npc->weight;

				func(a_this, a_buf);

				if (npc->weight != weight) {
					if (const auto biped = a_this->GetBiped()) {
						biped->RemoveAllParts();
					}
				    npc->weight = weight;
				}
			}
			static inline REL::Relocation<decltype(thunk)> func;
			static inline constexpr std::size_t size{ 0x0F };
		};

	    // Unbake weights
		void Install()
		{
			if (Settings::GetSingleton()->npcWeights) {
				logger::info("NPCWeights : true");

			    stl::write_vfunc<RE::Character, LoadGame>();
			}
		}
	}

	// Unbake OppositeGenderAnims
	namespace NPC
	{
		struct LoadGame
		{
			using Flag = RE::ACTOR_BASE_DATA::Flag;

			static void thunk(RE::TESNPC* a_this, std::uintptr_t a_buf)
			{
				const auto flags = a_this->actorData.actorBaseFlags;

				func(a_this, a_buf);

				if (flags.any(Flag::kOppositeGenderAnims)) {
					a_this->actorData.actorBaseFlags.set(Flag::kOppositeGenderAnims);
				} else {
					a_this->actorData.actorBaseFlags.reset(Flag::kOppositeGenderAnims);
				}
			}
			static inline REL::Relocation<decltype(thunk)> func;
			static inline constexpr std::size_t size{ 0x0F };
		};

		void Install()
		{
			if (Settings::GetSingleton()->oppositeGenderAnims) {
				logger::info("OppositeGenderAnimsFlag : true");

			    stl::write_vfunc<RE::TESNPC, LoadGame>();
			}
		}
	}

	// Unbake position/rotation on persistent unmovable references
	namespace ObjectREFR
	{
		struct detail
		{
			static bool is_persistent_immovable(RE::TESObjectREFR* a_refr)
			{
				return a_refr->IsPersistent() && !a_refr->CanBeMoved();
			}
		};

		struct SetAngleOnReference
		{
			static void thunk(RE::TESObjectREFR* a_this, const RE::NiPoint3& a_rot)
			{
				if (!detail::is_persistent_immovable(a_this)) {
					func(a_this, a_rot);
				}
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct SetLocationOnReference
		{
			static void thunk(RE::TESObjectREFR* a_this, const RE::NiPoint3& a_pos)
			{
				if (!detail::is_persistent_immovable(a_this)) {
					func(a_this, a_pos);
				}
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		void Install()
		{
			if (Settings::GetSingleton()->persistentTransforms) {
				logger::info("PersistentTransforms : true");

			    REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(34808, 35717) };
				stl::write_thunk_call<SetAngleOnReference>(target.address() + OFFSET(0x3BE, 0x3D4));
				stl::write_thunk_call<SetLocationOnReference>(target.address() + OFFSET(0x3CA, 0x3E0));
			}
		}
	}

	void Install()
	{
		logger::info("{:*^30}", "HOOKS");

	    Character::Install();
		NPC::Install();
		ObjectREFR::Install();
	}
}
