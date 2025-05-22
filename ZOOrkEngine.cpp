//
// Created by Richard Skarbez on 5/7/23.
//

#include "ZOOrkEngine.h"

#include <utility>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start);
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look") || (command == "inspect")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "inventory" || command == "i") {
            player->showInventory();
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else {
        direction = arguments[0];
    }

    auto currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);
    player->setCurrentRoom(passage->getTo());
    passage->enter();
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    auto currentRoom = player->getCurrentRoom();
    
    if (arguments.empty()) {
        // Show room description
        currentRoom->enter();
        
        // Show items in the room
        std::cout << "\nItems in this room:\n";
        bool hasItems = false;
        for (const auto& item : currentRoom->getItems()) {
            if (!hasItems) {
                hasItems = true;
            }
            std::cout << "- " << item->getName() << ": " << item->getDescription() << "\n";
        }
        if (!hasItems) {
            std::cout << "There are no items here.\n";
        }
    } else {
        // Combine all arguments into a single string for the object name
        std::string objectName;
        for (const auto& arg : arguments) {
            if (!objectName.empty()) {
                objectName += " ";
            }
            objectName += arg;
        }
        
        // Look for the object in the current room
        auto item = currentRoom->getItem(objectName);
        if (item) {
            std::cout << item->getDescription() << "\n";
        } else {
            std::cout << "You don't see any " << objectName << " here.\n";
        }
    }
}

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "What would you like to take?\n";
        return;
    }

    // Combine all arguments into a single string for the item name
    std::string itemName;
    for (const auto& arg : arguments) {
        if (!itemName.empty()) {
            itemName += " ";
        }
        itemName += arg;
    }

    auto currentRoom = player->getCurrentRoom();
    auto item = currentRoom->retrieveItem(itemName);
    
    if (item) {
        player->addItem(item);
        std::cout << "You take the " << itemName << ".\n";
    } else {
        std::cout << "You don't see any " << itemName << " here.\n";
    }
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "What would you like to drop?\n";
        return;
    }

    // Combine all arguments into a single string for the item name
    std::string itemName;
    for (const auto& arg : arguments) {
        if (!itemName.empty()) {
            itemName += " ";
        }
        itemName += arg;
    }

    auto item = player->retrieveItem(itemName);
    
    if (item) {
        player->getCurrentRoom()->addItem(item);
        std::cout << "You drop the " << itemName << ".\n";
    } else {
        std::cout << "You don't have any " << itemName << ".\n";
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}
