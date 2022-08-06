#include "main.hpp"
#include "Config/ModConfig.hpp"

#include "Hooks/NoteCutHapticEffectHook.hpp"
using namespace RumbleMod::Hooks;

#include "GlobalNamespace/ObstacleSaberSparkleEffectManager.hpp"
#include "GlobalNamespace/NoteCutHapticEffect.hpp"
#include "GlobalNamespace/HapticFeedbackController.hpp"
#include "GlobalNamespace/NoteCutHapticEffect_Type.hpp"
using namespace GlobalNamespace;

#include "UnityEngine/XR/XRNode.hpp"
using namespace UnityEngine::XR;

#include "Libraries/HM/HMLib/VR/HapticPresetSO.hpp"
using namespace Libraries::HM::HMLib::VR;

MAKE_HOOK_MATCH(NoteCutHapticEffect_HitNote, &NoteCutHapticEffect::HitNote, void,
    NoteCutHapticEffect* self, SaberType saberType, NoteCutHapticEffect::Type type
) {
    static float originalStrengthNormal = self->normalPreset->strength;
    static float originalDurationNormal = self->normalPreset->duration;

    if (getModConfig().enabled.GetValue()) {
        self->normalPreset->strength = getModConfig().strength.GetValue();
        self->normalPreset->duration = getModConfig().duration.GetValue();
    } else {
        self->normalPreset->strength = originalStrengthNormal;
        self->normalPreset->duration = originalDurationNormal;
    }

    NoteCutHapticEffect_HitNote(self, saberType, type);
}

void NoteCutHapticEffectHook::AddHooks() {
    INSTALL_HOOK(getLogger(), NoteCutHapticEffect_HitNote)
}

void NoteCutHapticEffectHook::RemoveHooks() {
    UNINSTALL_HOOK(getLogger(), NoteCutHapticEffect_HitNote);
}