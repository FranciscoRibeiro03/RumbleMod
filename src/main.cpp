#include "main.hpp"
#include "Config/ModConfig.hpp"

#include "IHook.hpp"
using namespace RumbleMod;

#include "custom-types/shared/register.hpp"

#include "questui/shared/QuestUI.hpp"

#include "Hooks/NoteCutHapticEffectHook.hpp"
#include "Hooks/ObstacleSaberSparkleEffectManagerHook.hpp"
#include "Hooks/SaberClashEffectHook.hpp"
#include "Hooks/VRInputModuleHook.hpp"
using namespace RumbleMod::Hooks;

#include "UI/ViewControllers/RumbleModSettingsViewController.hpp"
using namespace RumbleMod::UI::ViewControllers;

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;

    getConfig().Load(); // Load the config file
    getModConfig().Init(info);
    getConfig().Reload();
    getConfig().Write();
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    custom_types::Register::AutoRegister();
    QuestUI::Init();
    QuestUI::Register::RegisterModSettingsViewController<RumbleModSettingsViewController*>(modInfo);

    //if (getModConfig().enabled.GetValue()) {
        new NoteCutHapticEffectHook("NoteCutHapticEffect");
        new ObstacleSaberSparkleEffectManagerHook("ObstacleSaberSparkleEffectManager");
        new SaberClashEffectHook("SaberClashEffect");
        new VRInputModuleHook("VRInputModule");

    //}

    getLogger().info("Installing hooks...");
    if (!IHook::InstallHooks())
        getLogger().error("Failed to install hooks");
    else
        getLogger().info("Finished installing hooks!");
    getLogger().info("Installed all hooks!");
}