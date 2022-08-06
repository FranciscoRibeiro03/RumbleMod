#include "main.hpp"
#include "Config/ModConfig.hpp"
#include "hooking.hpp"

#include "GlobalNamespace/ObstacleSaberSparkleEffectManager.hpp"
using namespace GlobalNamespace;

#include "Libraries/HM/HMLib/VR/HapticPresetSO.hpp"
using namespace Libraries::HM::HMLib::VR;

MAKE_AUTO_HOOK_MATCH(ObstacleSaberSparkleEffectManager_Update, &ObstacleSaberSparkleEffectManager::Update, void,
    ObstacleSaberSparkleEffectManager* self
) {
    if (getModConfig().enabled.GetValue()) {
        self->rumblePreset->strength = getModConfig().strength_wall.GetValue();
    }

    ObstacleSaberSparkleEffectManager_Update(self);
}