//! @file
//! @brief Implementation file for the Events class
//!
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "GameData.h"
#include "GuiData.h"
#include "Events.h"
#include "MapCampaignFileIO.h"

void Events::respondToSelectionBoxClick(sf::RenderWindow& window) {
  if (GuiData::msSinceStart > GuiData::SELECTION_BOXES_APPEAR_TIME && GuiData::isSelectingChoice) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      MapCampaignFileIO mapSerializer;
      if (GuiData::createMapPosition.contains(mousePosition)) {
        GuiData::current_maps = mapSerializer.readCurrentDirectoryContents("map");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingMapToCreate = true;

      }
      if (GuiData::editMapPosition.contains(mousePosition)) {
        GuiData::current_maps = mapSerializer.readCurrentDirectoryContents("map");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingMapToEdit = true;
      }
      if (GuiData::createCampaignPosition.contains(mousePosition)) {
        GuiData::current_campaigns = mapSerializer.readCurrentDirectoryContents("campaign");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingCampaignToCreate = true;
      }
      if (GuiData::editCampaignPosition.contains(mousePosition)) {
        GuiData::current_campaigns = mapSerializer.readCurrentDirectoryContents("campaign");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingCampaignToEdit = true;
      }
    }
  }
}

void Events::respondToFileSelectionClick(sf::RenderWindow& window) {
  if (GuiData::isChoosingMapToEdit) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)GuiData::current_map_positions.size(); i++) {
        if (GuiData::current_map_positions[i].contains(mousePosition)) {
          GuiData::isChoosingMapToEdit = false;
          GuiData::isEditingMap = true;
          string ext = ".map";
          GuiData::chosenMap = string(GuiData::current_maps[i]) + string(ext);
          MapCampaignFileIO mfio;
          mfio.readMapJSON(GuiData::chosenMap);
          GuiData::shouldBlockThread = true;
        }
      }
    }
  }

  if (GuiData::isChoosingCampaignToEdit) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)GuiData::current_campaign_positions.size(); i++) {
        if (GuiData::current_campaign_positions[i].contains(mousePosition)) {
          GuiData::isChoosingCampaignToEdit = false;
          GuiData::isEditingCampaign = true;
          string ext = ".campaign";
          GuiData::chosenCampaign = string(GuiData::current_campaigns[i]) + string(ext);
          MapCampaignFileIO mfio;
          mfio.readCampaignJSON(GuiData::chosenCampaign);
          GuiData::shouldBlockThread = true;
        }
      }
    }
  }
}

void Events::respondToRealTimeTypeFeedback(sf::Event& evt) {
    if (evt.type == sf::Event::TextEntered) {
        if (GuiData::isChoosingMapToCreate) {
          if (evt.text.unicode == 13) { // ENTER
            bool hasNameConflict = false;
            for (int i = 0; i < (int)GuiData::current_maps.size(); i++) {
              if (GuiData::current_maps[i] == GuiData::createdMap) {
                hasNameConflict = true;
                break;
              }
            }
            if (hasNameConflict) {
              GuiData::shouldShowNameConflictError = true;
            } else {
              GuiData::createdMap = GuiData::createdMap + ".map";
              GuiData::isChoosingMapToCreate = false;
              GuiData::isSelectingMapSize = true;

            }
          } else if (evt.text.unicode == 8) { // BACKSPACE
              GuiData::createdMap.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              GuiData::createdMap += evt.text.unicode;
          }
        }
        if (GuiData::isChoosingCampaignToCreate) {
          if (evt.text.unicode == 13) { // ENTER
            bool hasNameConflict = false;
            for (int i = 0; i < (int)GuiData::current_campaigns.size(); i++) {
              if (GuiData::current_campaigns[i] == GuiData::createdCampaign) {
                hasNameConflict = true;
                break;
              }
            }
            if (hasNameConflict) {
              GuiData::shouldShowNameConflictError = true;
            } else {
              GuiData::createdCampaign = GuiData::createdCampaign + ".campaign";
              GuiData::isChoosingCampaignToCreate = false;
              GuiData::isCreatingCampaign = true;
            }
          } else if (evt.text.unicode == 8) { // BACKSPACE
              GuiData::createdCampaign.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              GuiData::createdCampaign += evt.text.unicode;
          }
        }
    }
}

void Events::respondToHomeButtonClick(sf::RenderWindow& window) {
  if (!GuiData::isSelectingChoice) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      if (GuiData::HomeButton.getGlobalBounds().contains(mousePosition)) {
        GuiData::hasCreateMapPosition = false;
        GuiData::hasEditMapPosition = false;
        GuiData::hasCreateCampaignPosition = false;
        GuiData::hasEditCampaignPosition = false;
        GuiData::isSelectingChoice = true;
        GuiData::isChoosingMapToCreate = false;
        GuiData::isChoosingMapToEdit = false;
        GuiData::isChoosingCampaignToCreate = false;
        GuiData::isChoosingCampaignToEdit = false;
        GuiData::isEditingCampaign = false;
        GuiData::isEditingMap = false;
        GuiData::isSelectingMapSize = false;
        GuiData::isCreatingMap = false;
        GuiData::isCreatingCampaign = false;
        GuiData::shouldShowNameConflictError = false;

        GuiData::createdMap = "";
        GuiData::chosenMap = "";
        GuiData::createdCampaign = "";
        GuiData::chosenCampaign = "";
      }
    }
  }
}

void Events::respondToSaveMapCampaign(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::saveButton.getGlobalBounds().contains(mousePosition)) {
      MapCampaignFileIO mfio;
      if (GuiData::isEditingMap) {
        mfio.saveMapJSON(GuiData::chosenMap);
      }
      if (GuiData::isCreatingMap) {
        mfio.saveMapJSON(GuiData::createdMap);
      }
      if (GuiData::isEditingCampaign) {
        mfio.saveCampaignJSON(GuiData::chosenCampaign);
      }
      if (GuiData::isCreatingCampaign) {
        mfio.saveCampaignJSON(GuiData::createdCampaign);
      }
    }
  }
}

void Events::respondToWidthPlusClick(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::isSelectingMapSize) {
      if (GuiData::widthPlus.getGlobalBounds().contains(mousePosition)) {
        GuiData::tempMapWidth += 1;
        GuiData::shouldBlockThread = true;
      }
    }
  }
}
void Events::respondToWidthMinusClick(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::isSelectingMapSize) {
      if (GuiData::widthMinus.getGlobalBounds().contains(mousePosition)) {
        if (GuiData::tempMapWidth > 4) {
            GuiData::tempMapWidth -= 1;
          GuiData::shouldBlockThread = true;
        }
      }
    }
  }
}
void Events::respondToLengthPlusClick(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::isSelectingMapSize) {
      if (GuiData::lengthPlus.getGlobalBounds().contains(mousePosition)) {
        GuiData::tempMapLength += 1;
        GuiData::shouldBlockThread = true;
      }
    }
  }
}

void Events::respondToLengthMinusClick(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::isSelectingMapSize) {
      if (GuiData::lengthMinus.getGlobalBounds().contains(mousePosition)) {
        if (GuiData::tempMapLength > 4) {
          GuiData::tempMapLength -= 1;
          GuiData::shouldBlockThread = true;
        }
      }
    }
  }
}


void Events::respondToMapCreateOkButton(sf::RenderWindow& window) {
  if (GuiData::isSelectingMapSize) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      if (GuiData::mapCreateOkButton.getGlobalBounds().contains(mousePosition)) {
        delete GameData::currentMapObject;
        int numBoxes = GuiData::tempMapWidth * GuiData::tempMapLength;
        string placement(numBoxes, ' ');

        // No saving here, because the map won't be valid to begin with.
        GameData::currentMapObject = new Map(GuiData::tempMapWidth, GuiData::tempMapLength, placement);

        GuiData::isSelectingMapSize = false;
        GuiData::isCreatingMap = true;
        GuiData::shouldBlockThread = true;
      }
    }
  }
}

void Events::respondToMapTileSelect(sf::RenderWindow& window) {
  if (GuiData::isEditingMap || GuiData::isCreatingMap) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      if (GuiData::wallSelectionSprite.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapTileSelectedChar = 'W';
      }
      if (GuiData::exitSelectionSprite.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapTileSelectedChar = 'E';
      }
      if (GuiData::startSelectionSprite.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapTileSelectedChar = 'S';
      }
      if (GuiData::treasureSelectionSprite.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapTileSelectedChar = 'T';
      }
      if (GuiData::monsterSelectionSprite.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapTileSelectedChar = 'O';
      }
      if (GuiData::emptySelectionSprite.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapTileSelectedChar = ' ';
      }
    }
  }
}

void Events::respondToMapBoxClick(sf::RenderWindow& window) {
  if (GuiData::isEditingMap || GuiData::isCreatingMap) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      int tempWidth = GameData::currentMapObject->getMapWidth();
      int tempLength = GameData::currentMapObject->getMapLength();

      for (int i = 0; i< tempWidth; i++) {
        for (int j =0; j < tempLength; j++) {
          if (GuiData::currentMapTilePositions[i][j].contains(mousePosition)) {
            GameData::currentMapObject->setCell(i, j, GuiData::currentMapTileSelectedChar);
            GuiData::shouldBlockThread = true;
          }
        }
      }
    }
  }
}
