#include "NPCConversationCommand.h"
#include "Player.h"
#include "Room.h"
#include "Passage.h"
#include <iostream>
#include <algorithm>

NPCConversationCommand::NPCConversationCommand() : Command(nullptr) {}

void NPCConversationCommand::execute() {
    std::string conversation =
        "Stranger: Ah, a brave adventurer! I've been waiting for someone like you.\n"
        "Stranger: There's a terrible dragon that has taken residence in the temple ruins to the east.\n"
        "Stranger: The beast is powerful, but there is hope. A secret potion lies hidden in the temple chamber.\n"
        "Stranger: This potion will give you the strength to face the dragon. Find it before you attempt to fight the beast.\n"
        "Stranger: Now, I must be going. Good luck on your quest!\n";

    std::cout << conversation;
    while (true) {
        std::cout << "\ncontinue game? (yes/no)\n> ";
        std::string input;
        std::getline(std::cin, input);
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "yes" || input == "y") {
            // Move player back to ancient ruins (forest clearing)
            auto player = Player::instance();
            if (player) {
                auto currentRoom = player->getCurrentRoom();
                if (currentRoom) {
                    auto passage = currentRoom->getPassage("north");
                    if (passage) {
                        auto dest = passage->getTo();
                        player->setCurrentRoom(dest);
                        dest->enter();
                    }
                }
            }
            break;
        } else if (input == "no" || input == "n") {
            std::cout << conversation;
        } else {
            std::cout << "Please answer yes or no." << std::endl;
        }
    }
} 