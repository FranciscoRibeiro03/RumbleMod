#include "main.hpp"
#include "Config/ModConfig.hpp"
#include "hooking.hpp"

#include "VRUIControls/VRInputModule.hpp"
using namespace VRUIControls;

#include "Libraries/HM/HMLib/VR/HapticPresetSO.hpp"
using namespace Libraries::HM::HMLib::VR;

MAKE_AUTO_HOOK_MATCH(VRInputModule_HandlePointerExitAndEnter, &VRInputModule::HandlePointerExitAndEnter, void,
    VRInputModule* self, UnityEngine::EventSystems::PointerEventData* currentPointerData, UnityEngine::GameObject* newEnterTarget
) {
    if (getModConfig().enabled.GetValue()) {
        self->rumblePreset->strength = getModConfig().strength_ui.GetValue();
    }

    VRInputModule_HandlePointerExitAndEnter(self, currentPointerData, newEnterTarget);
}