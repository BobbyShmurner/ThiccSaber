#include "main.hpp"

#include "MainViewController.hpp"
#include "MainConfig.hpp"

#include "bs-utils/shared/utils.hpp"

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"

#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/NoteData.hpp"

#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Transform.hpp"

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup
DEFINE_CONFIG(MainConfig);

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

MAKE_HOOK_MATCH(thickNote, &GlobalNamespace::NoteController::Init, void, GlobalNamespace::NoteController* self, GlobalNamespace::NoteData* noteData, float worldRotation, UnityEngine::Vector3 moveStartPos, UnityEngine::Vector3 moveEndPos, UnityEngine::Vector3 jumpEndPos, float moveDuration, float jumpDuration, float jumpGravity, float endRotation, float uniformScale) {
    thickNote(self, noteData, worldRotation, moveStartPos, moveEndPos, jumpEndPos, moveDuration, jumpDuration,  jumpGravity, endRotation, uniformScale);
    
    UnityEngine::Vector3 baseScale = self->get_noteTransform()->get_localScale();

    if (noteData->colorType == GlobalNamespace::ColorType::None && noteData->cutDirection) { // If True The Note Is A Bomb
        if (getMainConfig().ChangeBombSizes.GetValue()) {
            self->get_noteTransform()->set_localScale(UnityEngine::Vector3(baseScale.x * getMainConfig().Width.GetValue(), baseScale.y * getMainConfig().Height.GetValue(), baseScale.z * getMainConfig().Depth.GetValue()));    
            getLogger().info("Made Bomb THICK! (Color Type: %i, Note Cut Direction: %i)", noteData->colorType.value, noteData->cutDirection.value);
        }

        return;
    } else {
        if (getMainConfig().ChangeNoteSizes.GetValue()) {
            self->get_noteTransform()->set_localScale(UnityEngine::Vector3(baseScale.x * getMainConfig().Width.GetValue(), baseScale.y * getMainConfig().Height.GetValue(), baseScale.z * getMainConfig().Depth.GetValue()));    
            getLogger().info("Made Note THICK! (Color Type: %i, Note Cut Direction: %i)", noteData->colorType.value, noteData->cutDirection.value);
        }
    }
}

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    getLogger().info("DidActivate: %p, %d, %d, %d", self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;

    getMainConfig().Init(modInfo); //

    getConfig().Load(); // Load the config file

    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), thickNote);
    getLogger().info("Installed all hooks!");

    getLogger().info("Registering UI...");
    QuestUI::Init();
    QuestUI::Register::RegisterMainMenuModSettingsViewController<ThickSaber::MainViewController*>(modInfo);
    getLogger().info("UI Registered!");

    getLogger().info("Disabling Score Submissions...");
    bs_utils::Submission::disable(modInfo);
    getLogger().info("Disabled Score Submissions!");
}