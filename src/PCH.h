#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "RE/Skyrim.h"
#include "REX/REX.h"
#include "SKSE/SKSE.h"

#include <spdlog/sinks/basic_file_sink.h>

#define DLLEXPORT __declspec(dllexport)

using namespace std::literals;

namespace stl
{
	template <class T>
	void write_thunk_call(std::uintptr_t a_src)
	{
		auto& trampoline = REL::GetTrampoline();
		T::func = trampoline.write_call<5>(a_src, T::thunk);
	}

	template <class F, class T>
	void write_vfunc()
	{
		REL::Relocation<std::uintptr_t> vtbl{ F::VTABLE[0] };
		T::func = vtbl.write_vfunc(T::size, T::thunk);
	}
}

namespace Runtime
{
	inline constexpr REL::Version SSE_1_7_99(1, 7, 99, 0);
	inline constexpr REL::Version MIN_ADDRESS_LIBRARY_V5 = SSE_1_7_99;

	[[nodiscard]] inline bool IsAtLeast1_7_99() noexcept
	{
		static bool result = REX::FModule::GetExecutingModule().GetFileVersion() >= Runtime::SSE_1_7_99;
		return result;
	}
}

#ifdef SKYRIM_AE
#	define OFFSET(se, ae) ae
#	define OFFSET_VERSIONED(se, ae, ae1799) \
		(Runtime::IsAtLeast1_7_99() ? (ae1799) : (ae))
#	define RELOCATION_ID_VERSIONED(se, ae, ae1799) \
		REL::ID(Runtime::IsAtLeast1_7_99() ? (ae1799) : (ae))
#else
#	define OFFSET(se, ae) se
#	define OFFSET_VERSIONED(se, ae, ae1799) se
#	define RELOCATION_ID_VERSIONED(se, ae, ae1799) REL::ID(se)
#endif

#include "Version.h"
