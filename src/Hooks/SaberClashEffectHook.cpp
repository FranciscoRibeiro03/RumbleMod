#include "main.hpp"
#include "Config/ModConfig.hpp"

#include "Hooks/SaberClashEffectHook.hpp"
using namespace RumbleMod::Hooks;

#include "GlobalNamespace/SaberClashEffect.hpp"
using namespace GlobalNamespace;

#include "Libraries/HM/HMLib/VR/HapticPresetSO.hpp"
using namespace Libraries::HM::HMLib::VR;

MAKE_HOOK_MATCH(SaberClashEffect_LateUpdate, &SaberClashEffect::LateUpdate, void,
    SaberClashEffect* self
) {
    if (getModConfig().enabled.GetValue()) {
        self->rumblePreset->strength = getModConfig().strength_saber.GetValue();
    }

    SaberClashEffect_LateUpdate(self);
}

void SaberClashEffectHook::AddHooks() {
    INSTALL_HOOK(getLogger(), SaberClashEffect_LateUpdate)
}

void SaberClashEffectHook::RemoveHooks() {
    // UNINSTALL_HOOK(getLogger(), SaberClashEffect_LateUpdate);
    getLogger().info("Uninstalling hooks not supported yet");
}