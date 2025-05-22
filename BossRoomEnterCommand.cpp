#include "BossRoomEnterCommand.h"
#include "Room.h"
#include "Passage.h"
#include <iostream>
#include <string>

void BossRoomEnterCommand::execute() {
    std::cout << "Would you like to proceed to the boss fight? (yes/no)\n> ";
    
    std::string input;
    std::getline(std::cin, input);
    
    // Convert input to lowercase
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    
    if (input == "yes" || input == "y") {
        // Show the room description
        std::cout << gameObject->getDescription() << "\n";
    } else {
        // Go back to the secret garden
        std::cout << "You decide to return to the garden.\n";
        // Find the passage back to the secret garden
        auto currentRoom = static_cast<Room*>(gameObject);
        auto passage = currentRoom->getPassage("west");
        if (passage) {
            passage->enter();
        }
    }
} 