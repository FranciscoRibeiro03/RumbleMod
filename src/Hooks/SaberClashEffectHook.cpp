#include "main.hpp"
#include "Config/ModConfig.hpp"
#include "hooking.hpp"

#include "GlobalNamespace/SaberClashEffect.hpp"
using namespace GlobalNamespace;

#include "Libraries/HM/HMLib/VR/HapticPresetSO.hpp"
using namespace Libraries::HM::HMLib::VR;

MAKE_AUTO_HOOK_MATCH(SaberClashEffect_LateUpdate, &SaberClashEffect::LateUpdate, void,
    SaberClashEffect* self
) {
    if (getModConfig().enabled.GetValue()) {
        self->rumblePreset->strength = getModConfig().strength_saber.GetValue();
    }

    SaberClashEffect_LateUpdate(self);
}