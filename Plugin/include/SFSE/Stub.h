#pragma once

#include "DKUtil/Hook.hpp"
#include "sfse/PluginAPI.h"
#include "sfse_common/sfse_version.h"

// interface
namespace SFSE
{
	namespace detail
	{
		inline static SFSEInterface* load_storage = nullptr;
		inline static SFSEMessagingInterface* messaging_storage = nullptr;
		inline static SFSETrampolineInterface* trampoline_storage = nullptr;
	}  // namespace detail

	class LoadInterface : public dku::model::Singleton<LoadInterface>
	{
	public:
		enum
		{
			kVersion = 1,
		};

		enum : std::uint32_t
		{
			kInvalid = 0,
			kMessaging,
			kTrampoline,

			kTotal,
		};

		[[nodiscard]] constexpr auto RuntimeVersion() const { return GetProxy()->runtimeVersion; }
		[[nodiscard]] constexpr auto SFSEVersion() const { return GetProxy()->sfseVersion; }
		[[nodiscard]] constexpr auto GetPluginHandle() const { return handle; };
		[[nodiscard]] constexpr const auto* GetPluginInfo(const char* a_name) const { return GetProxy()->GetPluginInfo(a_name); }
		template <typename T>
		[[nodiscard]] constexpr T* QueryInterface(std::uint32_t a_id) const
		{
			return std::bit_cast<T*>(GetProxy()->QueryInterface(a_id));
		};

		PluginHandle handle = static_cast<PluginHandle>(-1);

	protected:
		constexpr const SFSEInterface* const GetProxy() const
		{
			return detail::load_storage;
		}
	};

	class MessagingInterface : public dku::model::Singleton<MessagingInterface>
	{
	public:
		enum
		{
			kVersion = 1,
		};

		struct Message
		{
			const char* sender;
			std::uint32_t type;
			std::uint32_t dataLen;
			void* data;
		};
		using EventCallback = std::add_pointer_t<void(Message* a_msg)>;

		enum : std::uint32_t
		{
			kPostLoad,      // sent to registered plugins once all plugins have been loaded (no data)
			kPostPostLoad,  // sent right after kPostPostLoad to facilitate the correct dispatching/registering of messages/listeners
		};

		constexpr bool Dispatch(std::uint32_t a_messageType, void* a_data, std::uint32_t a_dataLength, std::string_view a_receiver) const
		{
			auto success = GetProxy()->Dispatch(LoadInterface::GetSingleton()->GetPluginHandle(), a_messageType, a_data, a_dataLength, a_receiver.data());
			if (!success) {
				FATAL(
					"failed to dispatch message!\nexpected receiver : {}\n"
					"message {{\ntype : {}\nlength : {}}}",
					a_receiver, a_messageType, a_dataLength);
			}

			return success;
		}

		constexpr bool RegisterListener(std::string_view a_sender, EventCallback a_callback) const
		{
			auto success = GetProxy()->RegisterListener(LoadInterface::GetSingleton()->GetPluginHandle(), a_sender.data(), std::bit_cast<SFSEMessagingInterface::EventCallback>(a_callback));
			if (!success) {
				FATAL("failed to register messaging listener!\nexpected sender : {}\nmessage handler : {}.{:X}",
					a_sender, Plugin::NAME, AsAddress(a_callback));
			}

			return success;
		}

		constexpr bool RegisterListener(EventCallback a_callback) const
		{
			return RegisterListener("SFSE"sv, a_callback);
		}

	protected:
		constexpr const SFSEMessagingInterface* const GetProxy() const
		{
			return detail::messaging_storage;
		}
	};

	class TrampolineInterface : public dku::model::Singleton<TrampolineInterface>
	{
	public:
		enum
		{
			kVersion = 1,
		};

		[[nodiscard]] constexpr void* AllocateFromBranchPool(std::size_t a_size) const
		{
			return GetProxy()->AllocateFromBranchPool(LoadInterface::GetSingleton()->GetPluginHandle(), a_size);
		}

		[[nodiscard]] constexpr void* AllocateFromLocalPool(std::size_t a_size) const
		{
			return GetProxy()->AllocateFromLocalPool(LoadInterface::GetSingleton()->GetPluginHandle(), a_size);
		}

	protected:
		constexpr const SFSETrampolineInterface* const GetProxy() const
		{
			return detail::trampoline_storage;
		}
	};
}  // namespace SFSE

// stubs
namespace SFSE
{
	inline void Init(SFSEInterface* a_intfc) noexcept
	{
		if (!a_intfc) {
			FATAL("SFSEInterface is null"sv);
		}

		auto* storage = SFSE::LoadInterface::GetSingleton();

		detail::load_storage = std::launder(a_intfc);
		detail::messaging_storage = std::launder(storage->QueryInterface<SFSEMessagingInterface>(LoadInterface::kMessaging));
		detail::trampoline_storage = std::launder(storage->QueryInterface<SFSETrampolineInterface>(LoadInterface::kTrampoline));

		storage->handle = detail::load_storage->GetPluginHandle();
	}

	[[nodiscard]] inline constexpr const auto* GetLoadInterface() noexcept { return SFSE::LoadInterface::GetSingleton(); }
	[[nodiscard]] inline constexpr const auto* GetMessagingInterface() noexcept
	{
		return MessagingInterface::GetSingleton();
	}
	[[nodiscard]] inline constexpr const auto* GetTrampolineInterface() noexcept
	{
		return TrampolineInterface::GetSingleton();
	}

	[[nodiscard]] inline auto& GetTrampoline() noexcept { return DKUtil::Hook::Trampoline::GetTrampoline(); }

	// offer SFSE reserve pool first, otherwise use local trampoline
	void* AllocTrampoline(std::size_t a_size, bool a_useSFSEReserve = true)
	{
		auto& trampoline = GetTrampoline();

		if (auto intfc = GetTrampolineInterface(); intfc && a_useSFSEReserve) {
			auto* mem = intfc->AllocateFromBranchPool(a_size);
			if (mem) {
				trampoline.set_trampoline(mem, a_size);
				return mem;
			} else {
				WARN(
					"requesting allocation from SFSE branch pool failed\n"
					"falling back to local trampoline");
			}
		}

		auto* mem = trampoline.PageAlloc(a_size);
		if (mem) {
			return mem;
		} else {
			FATAL(
				"failed to allocate any memory from either branch pool or local trampoline\n"
				"this is fatal!\nSize : {}",
				a_size);
			std::unreachable();
		}
	}
}  // namespace SFSE

// versiondata
namespace SFSE
{
	struct PluginVersionData
	{
	public:
		enum
		{
			kVersion = 1,
		};

		constexpr void PluginVersion(std::uint32_t a_version) noexcept { pluginVersion = a_version; }
		constexpr void PluginName(std::string_view a_plugin) noexcept { SetCharBuffer(a_plugin, std::span{ pluginName }); }
		constexpr void AuthorName(std::string_view a_name) noexcept { SetCharBuffer(a_name, std::span{ author }); }
		constexpr void UsesSigScanning(bool a_value) noexcept { addressIndependence = !a_value; }
		constexpr void UsesAddressLibrary(bool a_value) noexcept { addressIndependence = a_value; }
		constexpr void HasNoStructUse(bool a_value) noexcept { structureCompatibility = !a_value; }
		constexpr void IsLayoutDependent(bool a_value) noexcept { structureCompatibility = a_value; }
		constexpr void CompatibleVersions(std::initializer_list<std::uint32_t> a_versions) noexcept
		{
			// must be zero-terminated
			assert(a_versions.size() < std::size(compatibleVersions) - 1);
			std::ranges::copy(a_versions, compatibleVersions);
		}
		constexpr void MinimumRequiredXSEVersion(std::uint32_t a_version) noexcept { xseMinimum = a_version; }

		const std::uint32_t dataVersion{ kVersion };  // shipped with xse
		std::uint32_t pluginVersion = 0;              // version number of your plugin
		char pluginName[256] = {};                    // null-terminated ASCII plugin name (please make this recognizable to users)
		char author[256] = {};                        // null-terminated ASCII plugin author name
		std::uint32_t addressIndependence;            // describe how you find your addressese using the kAddressIndependence_ enums
		std::uint32_t structureCompatibility;         // describe how you handle structure layout using the kStructureIndependence_ enums
		std::uint32_t compatibleVersions[16] = {};    // list of compatible versions
		std::uint32_t xseMinimum = 0;                 // minimum version of the script extender required
		const std::uint32_t reservedNonBreaking = 0;  // set to 0
		const std::uint32_t reservedBreaking = 0;     // set to 0

	private:
		static constexpr void SetCharBuffer(
			std::string_view a_src,
			std::span<char> a_dst) noexcept
		{
			assert(a_src.size() < a_dst.size());
			std::ranges::fill(a_dst, '\0');
			std::ranges::copy(a_src, a_dst.begin());
		}
	};
	static_assert(offsetof(PluginVersionData, dataVersion) == 0x000);
	static_assert(offsetof(PluginVersionData, pluginVersion) == 0x004);
	static_assert(offsetof(PluginVersionData, pluginName) == 0x008);
	static_assert(offsetof(PluginVersionData, author) == 0x108);
	static_assert(offsetof(PluginVersionData, addressIndependence) == 0x208);
	static_assert(offsetof(PluginVersionData, structureCompatibility) == 0x20C);
	static_assert(offsetof(PluginVersionData, compatibleVersions) == 0x210);
	static_assert(offsetof(PluginVersionData, xseMinimum) == 0x250);
	static_assert(offsetof(PluginVersionData, reservedNonBreaking) == 0x254);
	static_assert(offsetof(PluginVersionData, reservedBreaking) == 0x258);
	static_assert(sizeof(PluginVersionData) == 0x25C);
}  // namespace SFSE
