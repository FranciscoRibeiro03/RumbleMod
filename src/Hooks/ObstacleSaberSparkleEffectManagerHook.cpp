#include "main.hpp"
#include "Config/ModConfig.hpp"

#include "Hooks/ObstacleSaberSparkleEffectManagerHook.hpp"
using namespace RumbleMod::Hooks;

#include "GlobalNamespace/ObstacleSaberSparkleEffectManager.hpp"
using namespace GlobalNamespace;

#include "Libraries/HM/HMLib/VR/HapticPresetSO.hpp"
using namespace Libraries::HM::HMLib::VR;

MAKE_HOOK_MATCH(ObstacleSaberSparkleEffectManager_Update, &ObstacleSaberSparkleEffectManager::Update, void,
    ObstacleSaberSparkleEffectManager* self
) {
    if (getModConfig().enabled.GetValue()) {
        self->rumblePreset->strength = getModConfig().strength_wall.GetValue();
    }

    ObstacleSaberSparkleEffectManager_Update(self);
}

void ObstacleSaberSparkleEffectManagerHook::AddHooks() {
    INSTALL_HOOK(getLogger(), ObstacleSaberSparkleEffectManager_Update)
}

void ObstacleSaberSparkleEffectManagerHook::RemoveHooks() {
    // UNINSTALL_HOOK(getLogger(), ObstacleSaberSparkleEffectManager_Update);
    getLogger().info("Uninstalling hooks not supported yet");
}