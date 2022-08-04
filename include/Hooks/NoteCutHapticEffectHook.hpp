#pragma once

#include "IHook.hpp"
#include "main.hpp"
using namespace RumbleMod;

#include "Libraries/HM/HMLib/VR/HapticPresetSO.hpp"
using namespace Libraries::HM::HMLib::VR;

namespace RumbleMod::Hooks {
    class NoteCutHapticEffectHook : IHook {
    public:
        void AddHooks() override;
        void RemoveHooks() override;
        explicit NoteCutHapticEffectHook(const std::string& name) : IHook(name) {}
    };
}