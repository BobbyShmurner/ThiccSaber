#include "MainViewController.hpp"

#include "MainConfig.hpp"

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

DEFINE_TYPE(ThickSaber, MainViewController);

void ThickSaber::MainViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
	if (!firstActivation) return;

	getLogger().info("Drawing Canvas...");

	UnityEngine::GameObject* mainContainer = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

	QuestUI::BeatSaberUI::CreateToggle(mainContainer->get_transform(), "Change Note Sizes", getMainConfig().ChangeNoteSizes.GetValue(), [](bool value) {
		getMainConfig().ChangeNoteSizes.SetValue(value, true);

		getLogger().info("Change Note Sizes: %s", value ? "Enabled" : "Disabled");
	});

	QuestUI::BeatSaberUI::CreateToggle(mainContainer->get_transform(), "Change Bomb Sizes", getMainConfig().ChangeBombSizes.GetValue(), [](bool value) {
		getMainConfig().ChangeBombSizes.SetValue(value, true);

		getLogger().info("Change Bomb Sizes: %s", value ? "Enabled" : "Disabled");
	});

	QuestUI::BeatSaberUI::CreateSliderSetting(mainContainer->get_transform(), "Width", 0.1f, getMainConfig().Width.GetValue(), 0.1f, 5.0f, 0.2f, [](float value){
		getMainConfig().Width.SetValue(value, true);
		getLogger().info("Changed width value to %.2f", value);
	});

	QuestUI::BeatSaberUI::CreateSliderSetting(mainContainer->get_transform(), "Height", 0.1f, getMainConfig().Height.GetValue(), 0.1f, 5.0f, 0.2f, [](float value){
		getMainConfig().Height.SetValue(value, true);
		getLogger().info("Changed height value to %.2f", value);
	});

	QuestUI::BeatSaberUI::CreateSliderSetting(mainContainer->get_transform(), "Depth", 0.1f, getMainConfig().Depth.GetValue(), 0.1f, 5.0f, 0.2f, [](float value){
		getMainConfig().Depth.SetValue(value, true);
		getLogger().info("Changed depth value to %.2f", value);
	});

	getLogger().info("Completed Drawing Canvas");
}