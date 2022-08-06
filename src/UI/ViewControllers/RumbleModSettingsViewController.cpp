#include "UI/ViewControllers/RumbleModSettingsViewController.hpp"
using namespace RumbleMod::UI::ViewControllers;

#include "main.hpp"
#include "Config/ModConfig.hpp"

#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI::BeatSaberUI;

#include "UnityEngine/Color.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/ScriptableObject.hpp"
using namespace UnityEngine;

#include "UnityEngine/XR/XRNode.hpp"
using namespace UnityEngine::XR;

#include "VRUIControls/VRInputModule.hpp"
using namespace VRUIControls;

#include "GlobalNamespace/MenuTransitionsHelper.hpp"
using namespace GlobalNamespace;

DEFINE_TYPE(RumbleMod::UI::ViewControllers, RumbleModSettingsViewController)

void
RumbleModSettingsViewController::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling) {
    if (!firstActivation)
        return;
    layout = CreateVerticalLayoutGroup(get_transform());

        horizontal = CreateHorizontalLayoutGroup(layout->get_transform());
        horizontal->set_spacing(4.0f);
            text = CreateText(horizontal->get_transform(), "Use at your own risk!");
            text->set_color(Color::get_red());
            text->set_alignment(TextAlignmentOptions::Center);

            button = CreateUIButton(horizontal->get_transform(), "Default", OnDefaultClick);
                SetButtonTextSize(button, 4.0f);
                AddHoverHint(button->get_gameObject(), "I'll pass this time.");

            button = CreateUIButton(horizontal->get_transform(), "Recommended", OnRecommendedClick);
                SetButtonTextSize(button, 4.0f);
                AddHoverHint(button->get_gameObject(), "I'm okay to go.");

        horizontal = CreateHorizontalLayoutGroup(layout->get_transform());
            toggle() = CreateToggle(horizontal->get_transform(), "Enable RumbleMod", getModConfig().enabled.GetValue(), [](bool value) {
                getModConfig().enabled.SetValue(value);
            });
            AddHoverHint(toggle()->get_gameObject(), "I'm okay to go.");

        horizontal = CreateHorizontalLayoutGroup(layout->get_transform());
            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                text = CreateText(horizontalChild->get_transform(), "Note Strength", true);
                text->set_fontSize(4.0f);

            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                horizontalChild->set_padding(RectOffset::New_ctor(-27, 1, 0, 0));
                strengthSlider() = CreateSliderSetting(horizontalChild->get_transform(), "", 0.05f, getModConfig().strength.GetValue(), 0.0f, 1.0f, 0.0f, [](float value) {
                    getModConfig().strength.SetValue(value);
                });
                AddHoverHint(strengthSlider()->get_gameObject(), "The default value is 1.00");

            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                button = CreateUIButton(horizontalChild->get_transform(), "Rumble", OnRumbleNoteClick);

        horizontal = CreateHorizontalLayoutGroup(layout->get_transform());
            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                text = CreateText(horizontalChild->get_transform(), "Note Duration", true);
                text->set_fontSize(4.0f);

            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                horizontalChild->set_padding(RectOffset::New_ctor(-27, 1, 0, 0));
                durationSlider() = CreateSliderSetting(horizontalChild->get_transform(), "", 0.01f, getModConfig().duration.GetValue(), 0.0f, 1.0f, 0.0f, [](float value) {
                    getModConfig().duration.SetValue(value);
                });
                AddHoverHint(durationSlider()->get_gameObject(), "The default is 0.14 (sec)");

            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                horizontalChild->set_padding(RectOffset::New_ctor(0.0f, 24.0f, 0.0f, 0.0f));
                text = CreateText(horizontalChild->get_transform(), "");
                text->set_fontSize(4.0f);

        horizontal = CreateHorizontalLayoutGroup(layout->get_transform());
            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                text = CreateText(horizontalChild->get_transform(), "Saber Strength", true);
                text->set_fontSize(4.0f);

            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                horizontalChild->set_padding(RectOffset::New_ctor(-27, 1, 0, 0));
                saberSlider() = CreateSliderSetting(horizontalChild->get_transform(), "", 0.05f, getModConfig().strength_saber.GetValue(), 0.0f, 1.0f, 0.0f, [](float value) {
                    getModConfig().strength_saber.SetValue(value);
                });
                AddHoverHint(saberSlider()->get_gameObject(), "The default value is 1.00");

            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                button = CreateUIButton(horizontalChild->get_transform(), "Rumble", OnRumbleSaberClick);

        horizontal = CreateHorizontalLayoutGroup(layout->get_transform());
            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                text = CreateText(horizontalChild->get_transform(), "Wall Strength", true);
                text->set_fontSize(4.0f);

            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                horizontalChild->set_padding(RectOffset::New_ctor(-27, 1, 0, 0));
                wallSlider() = CreateSliderSetting(horizontalChild->get_transform(), "", 0.05f, getModConfig().strength_wall.GetValue(), 0.0f, 1.0f, 0.0f, [](float value) {
                    getModConfig().strength_wall.SetValue(value);
                });
                AddHoverHint(wallSlider()->get_gameObject(), "The default value is 1.00");

            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                button = CreateUIButton(horizontalChild->get_transform(), "Rumble", OnRumbleWallClick);

        horizontal = CreateHorizontalLayoutGroup(layout->get_transform());
            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                text = CreateText(horizontalChild->get_transform(), "UI Strength", true);
                text->set_fontSize(4.0f);

            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                horizontalChild->set_padding(RectOffset::New_ctor(-27, 1, 0, 0));
                uiSlider() = CreateSliderSetting(horizontalChild->get_transform(), "", 0.05f, getModConfig().strength_ui.GetValue(), 0.0f, 1.0f, 0.0f, [](float value) {
                    getModConfig().strength_ui.SetValue(value);
                });
                AddHoverHint(uiSlider()->get_gameObject(), "The default value is 1.00");

            horizontalChild = CreateHorizontalLayoutGroup(horizontal->get_transform());
                button = CreateUIButton(horizontalChild->get_transform(), "Rumble", OnRumbleUIClick);
}

void RumbleModSettingsViewController::DidDeactivate(bool removedFromHeirarchy, bool screenSystemDisabling) {
    Resources::FindObjectsOfTypeAll<MenuTransitionsHelper*>()->values[0]->RestartGame(nullptr);
    // soft restart to stop crashes on song load
}

void RumbleModSettingsViewController::ctor() {
    rumblePreset() = ScriptableObject::CreateInstance<HapticPresetSO*>();
}

void RumbleModSettingsViewController::OnDefaultClick() {
    toggle()->set_isOn(getModConfig().enabled.GetDefaultValue());
    strengthSlider()->set_value(getModConfig().strength.GetDefaultValue());
    durationSlider()->set_value(getModConfig().duration.GetDefaultValue());
    saberSlider()->set_value(getModConfig().strength_saber.GetDefaultValue());
    wallSlider()->set_value(getModConfig().strength_wall.GetDefaultValue());
    uiSlider()->set_value(getModConfig().strength_ui.GetDefaultValue());

    getModConfig().enabled.SetValue(toggle()->get_isOn());
    getModConfig().strength.SetValue(strengthSlider()->get_value());
    getModConfig().duration.SetValue(durationSlider()->get_value());
    getModConfig().strength_saber.SetValue(saberSlider()->get_value());
    getModConfig().strength_wall.SetValue(wallSlider()->get_value());
    getModConfig().strength_ui.SetValue(uiSlider()->get_value());
}

void RumbleModSettingsViewController::OnRecommendedClick() {
    toggle()->set_isOn(true);
    strengthSlider()->set_value(1.0f);
    durationSlider()->set_value(0.14f);
    saberSlider()->set_value(0.25f);
    wallSlider()->set_value(0.25f);
    uiSlider()->set_value(0.5f);

    getModConfig().enabled.SetValue(toggle()->get_isOn());
    getModConfig().strength.SetValue(strengthSlider()->get_value());
    getModConfig().duration.SetValue(durationSlider()->get_value());
    getModConfig().strength_saber.SetValue(saberSlider()->get_value());
    getModConfig().strength_wall.SetValue(wallSlider()->get_value());
    getModConfig().strength_ui.SetValue(uiSlider()->get_value());
}

void RumbleModSettingsViewController::OnRumbleNoteClick() {
    RumbleTest(strengthSlider()->get_value(), durationSlider()->get_value());
}

void RumbleModSettingsViewController::OnRumbleSaberClick() {
    RumbleTest(saberSlider()->get_value(), 1.0f);
}

void RumbleModSettingsViewController::OnRumbleWallClick() {
    RumbleTest(wallSlider()->get_value(), 1.0f);
}

void RumbleModSettingsViewController::OnRumbleUIClick() {
    RumbleTest(uiSlider()->get_value(), 0.02f);
}

void RumbleModSettingsViewController::RumbleTest(float strength, float duration) {
    getLogger().info("RumbleTest: strength=%f, duration=%f", strength, duration);

    if (hapticFeedbackController() == nullptr) {
        auto vrInputModules = Resources::FindObjectsOfTypeAll<VRInputModule*>();
        VRInputModule* vrInputModule;
        if (vrInputModules->Length() > 0) vrInputModule = vrInputModules->values[0]; else vrInputModule = nullptr;
        if (vrInputModule != nullptr) {
            hapticFeedbackController() = vrInputModule->hapticFeedbackController;
        }
    }

    if (hapticFeedbackController() != nullptr) {
        rumblePreset()->strength = strength;
        rumblePreset()->duration = duration;
        hapticFeedbackController()->PlayHapticFeedback(XRNode::LeftHand, rumblePreset());
        hapticFeedbackController()->PlayHapticFeedback(XRNode::RightHand, rumblePreset());
    } else {
        getLogger().error("Error getting HapticFeedbackController");
    }
}