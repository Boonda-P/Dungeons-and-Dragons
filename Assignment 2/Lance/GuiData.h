#include <chrono>
#include "Texts.h"
#include "Events.h"
#include "Fonts.h"
#include "Ui.h"

using namespace std::chrono;

//Many
namespace GuiData{

  extern const sf::Color SELECTION_BACKGROUND_COLOR;
  extern const sf::Color ELLIPSIS_COLOR;

  extern const int WINDOW_HEIGHT;
  extern const int WINDOW_WIDTH;
  extern const float FADE_IN_STEP;
  extern const unsigned long UNIX_TIME_MS_START;
  extern const unsigned long GREETINGS_APPEAR_TIME;
  extern const unsigned long CALL_TO_ACTION_APPEAR_TIME;
  extern const unsigned long SELECTION_BOXES_APPEAR_TIME;
  extern const float TEXT_OUTLINE_THICKNESS;

  extern Fonts fontGenerator;
  extern Texts textGenerator;
  extern Events eventManager;
  extern Ui uiManager;

  extern sf::Font currentFont;
  extern sf::FloatRect createMapPosition;
  extern sf::FloatRect editMapPosition;
  extern sf::FloatRect createCampaignPosition;
  extern sf::FloatRect editCampaignPosition;
  extern sf::Text ellipsis;
  extern sf::Text greetings;
  extern sf::Text callToAction;
  extern sf::Text selectionBoxText;
  extern sf::Text selectMap;
  extern sf::Text typeMapName;
  extern sf::Text selectFileNames;
  extern sf::Text realTimeTypeFeedback;
  extern sf::Text NameConflictError;
  extern sf::Text HomeButton;
  extern sf::Text saveButton;
  extern sf::RectangleShape selectionBox;

  extern string chosenMap;
  extern string chosenCampaign;
  extern string createdCampaign;
  extern string createdMap;
  extern vector<string> current_maps;
  extern vector<sf::FloatRect> current_map_positions;
  extern vector<string> current_campaigns;
  extern vector<sf::FloatRect> current_campaign_positions;
  extern float greetingsTransparency;
  extern float callToActionTransparency;
  extern float selectionBoxTransparency;
  extern bool hasCreateMapPosition;
  extern bool hasEditMapPosition;
  extern bool hasCreateCampaignPosition;
  extern bool hasEditCampaignPosition;
  extern bool isSelectingChoice;
  extern bool isChoosingMapToCreate;
  extern bool isChoosingMapToEdit;
  extern bool isChoosingCampaignToCreate;
  extern bool isChoosingCampaignToEdit;
  extern bool isEditingCampaign;
  extern bool isEditingMap;
  extern bool shouldShowNameConflictError;
  extern unsigned long msSinceStart;
};

