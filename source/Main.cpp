#include "Hooks.h"

void InitializeLogger()
{
    auto path = SKSE::log::log_directory();
   
    if (!path) { return; }

    const auto plugin = SKSE::PluginDeclaration::GetSingleton();
    *path /= std::format("{}.log", plugin->GetName());

    std::vector<spdlog::sink_ptr> sinks{
        std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true),
        std::make_shared<spdlog::sinks::msvc_sink_mt>()
    };

    auto logger = std::make_shared<spdlog::logger>("global", sinks.begin(), sinks.end());
   
    logger->set_level(spdlog::level::info);
    logger->flush_on(spdlog::level::info);

    spdlog::set_default_logger(std::move(logger));
    spdlog::set_pattern("[%^%L%$] %v");
}

void HandleMessage(SKSE::MessagingInterface::Message* aMessage)
{
    switch (aMessage->type) {
    case SKSE::MessagingInterface::kDataLoaded:
        {
            Addresses::Hook();
        }
        break;
    }
}

SKSEPluginLoad(const SKSE::LoadInterface* aLoadInterface)
{
    InitializeLogger();

    SKSE::Init(aLoadInterface);

    SKSE::AllocTrampoline(14 * 1);

    const auto messaging_interface = SKSE::GetMessagingInterface();

    if (!messaging_interface) { stl::report_and_fail("Failed to communicate with the messaging interface!"); }

    messaging_interface->RegisterListener(HandleMessage);

    return true;
}
