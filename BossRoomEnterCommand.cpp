#include "BossRoomEnterCommand.h"
#include "Room.h"
#include "Passage.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <random>
#include <ctime>

void BossRoomEnterCommand::execute() {
    std::cout << "Would you like to proceed to the boss fight? (yes/no)\n> ";
    
    std::string input;
    std::getline(std::cin, input);
    
    // Convert input to lowercase
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    
    if (input == "yes" || input == "y") {
        // Check if the player has a sword
        auto player = static_cast<Player*>(gameObject);
        if (!player->getItem("sword")) {
            std::cout << "You don't have required items to fight a dragon!\n";
            return;
        }
        // Start the boss fight
        int playerHP = 100;
        int bossHP = 100;
        std::default_random_engine rng(static_cast<unsigned>(std::time(nullptr)));
        std::uniform_int_distribution<int> dist(0, 3);
        std::cout << "\nThe fight begins!\n";
        while (playerHP > 0 && bossHP > 0) {
            // Display current HP at the start of each turn
            std::cout << "\nYour HP: " << playerHP << " | Dragon HP: " << bossHP << "\n";
            // Ask if the player wants to attack
            std::cout << "Would you like to attack? (yes/no)\n> ";
            std::getline(std::cin, input);
            std::transform(input.begin(), input.end(), input.begin(), ::tolower);
            if (input == "yes" || input == "y") {
                // Player's turn
                std::cout << "You attack the dragon! ";
                bool hasPotion = player->getItem("potion") != nullptr;
                if ((hasPotion && dist(rng) < 3) || (!hasPotion && dist(rng) < 2)) {
                    bossHP -= 20;
                    std::cout << "Hit! The dragon loses 20 HP. (Dragon HP: " << bossHP << ")\n";
                } else {
                    std::cout << "Miss!\n";
                }
            } else {
                std::cout << "You choose not to attack.\n";
            }
            if (bossHP <= 0) break;
            // Boss's turn
            std::cout << "The dragon attacks you! ";
            if (dist(rng) < 2) {
                playerHP -= 20;
                std::cout << "Hit! You lose 20 HP. (Your HP: " << playerHP << ")\n";
            } else {
                std::cout << "Miss!\n";
            }
        }
        if (playerHP <= 0) {
            std::cout << "\nYou Died.... try again? (yes/no)\n> ";
            std::getline(std::cin, input);
            std::transform(input.begin(), input.end(), input.begin(), ::tolower);
            if (input == "yes" || input == "y") {
                // Go back to the secret garden
                auto currentRoom = static_cast<Room*>(gameObject);
                auto passage = currentRoom->getPassage("west");
                if (passage) {
                    passage->enter();
                }
            } else {
                std::cout << "Game Over.\n";
                exit(0);
            }
        } else {
            std::cout << "\nYou have defeated the dragon! Congratulations!\n";
        }
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