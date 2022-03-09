#include "MainViewController.hpp"

#include "MainConfig.hpp"

#include "bs-utils/shared/utils.hpp"

#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"
#include "HMUI/ScrollView.hpp"
#include "HMUI/ModalView.hpp"
#include "HMUI/Touchable.hpp"
#include "HMUI/CurvedCanvasSettings.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include <stdlib.h>

#include <sstream>
#include <string>
#include <vector>

using namespace QuestUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace UnityEngine::Events;
using namespace HMUI;
using namespace TMPro;

extern ModInfo modInfo;

DEFINE_TYPE(ThiccSaber, MainViewController);

void SetSubmisionsActive(bool active) {
	if (active) {
		bs_utils::Submission::enable(modInfo);
	} else {
		bs_utils::Submission::disable(modInfo);
	}
}

void UpdateSubmmisionActivity() {
	bool active = false;

	if (!getMainConfig().ChangeNoteSizes.GetValue() && !getMainConfig().ChangeBombSizes.GetValue()) {
		active = true;
	}

	if (getMainConfig().Width.GetValue() == 1.0f && getMainConfig().Height.GetValue() == 1.0f && getMainConfig().Depth.GetValue() == 1.0f) {
		active = true;
	}

	SetSubmisionsActive(active);
	getLogger().info("Score Submision Status: %s", bs_utils::Submission::getEnabled() ? "True" : "False");
}

void ThiccSaber::MainViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
	if (!firstActivation) return;

	getLogger().info("Drawing Canvas...");

	UnityEngine::GameObject* mainContainer = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

	QuestUI::BeatSaberUI::CreateToggle(mainContainer->get_transform(), "Change Note Sizes", getMainConfig().ChangeNoteSizes.GetValue(), [](bool value) {
		getMainConfig().ChangeNoteSizes.SetValue(value, true);
		UpdateSubmmisionActivity();
		
		getLogger().info("Change Note Sizes: %s", value ? "Enabled" : "Disabled");
	});

	QuestUI::BeatSaberUI::CreateToggle(mainContainer->get_transform(), "Change Bomb Sizes", getMainConfig().ChangeBombSizes.GetValue(), [](bool value) {
		getMainConfig().ChangeBombSizes.SetValue(value, true);
		UpdateSubmmisionActivity();
		
		getLogger().info("Change Bomb Sizes: %s", value ? "Enabled" : "Disabled");
	});

	QuestUI::BeatSaberUI::CreateSliderSetting(mainContainer->get_transform(), "Width", 0.1f, getMainConfig().Width.GetValue(), 0.1f, 5.0f, 0.2f, [](float value){
		getMainConfig().Width.SetValue(value, true);
		UpdateSubmmisionActivity();

		getLogger().info("Changed width value to %.2f", value);
	});

	QuestUI::BeatSaberUI::CreateSliderSetting(mainContainer->get_transform(), "Height", 0.1f, getMainConfig().Height.GetValue(), 0.1f, 5.0f, 0.2f, [](float value){
		getMainConfig().Height.SetValue(value, true);
		UpdateSubmmisionActivity();
		
		getLogger().info("Changed height value to %.2f", value);
	});

	QuestUI::BeatSaberUI::CreateSliderSetting(mainContainer->get_transform(), "Depth", 0.1f, getMainConfig().Depth.GetValue(), 0.1f, 5.0f, 0.2f, [](float value){
		getMainConfig().Depth.SetValue(value, true);
		UpdateSubmmisionActivity();
		
		getLogger().info("Changed depth value to %.2f", value);
	});

	getLogger().info("Completed Drawing Canvas");
}
