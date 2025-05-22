//
// Created by Richard Skarbez on 5/7/23.
//

#include "Player.h"

std::shared_ptr<Player> Player::playerInstance = nullptr;

void Player::setCurrentRoom(std::shared_ptr<Room> room) {
    currentRoom = std::move(room);
}

std::shared_ptr<Room> Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::addItem(std::shared_ptr<Item> item) {
    inventory.push_back(std::move(item));
}

void Player::removeItem(const std::string& itemName) {
    inventory.erase(
        std::remove_if(inventory.begin(), inventory.end(),
            [&itemName](const std::shared_ptr<Item>& item) {
                return item->getName() == itemName;
            }
        ),
        inventory.end()
    );
}

std::shared_ptr<Item> Player::getItem(const std::string& itemName) {
    for (const auto& item : inventory) {
        if (item->getName() == itemName) {
            return item;
        }
    }
    return nullptr;
}

std::shared_ptr<Item> Player::retrieveItem(const std::string& itemName) {
    auto item = getItem(itemName);
    if (item) {
        removeItem(itemName);
    }
    return item;
}

void Player::showInventory() const {
    if (inventory.empty()) {
        std::cout << "Your inventory is empty.\n";
        return;
    }
    
    std::cout << "Your inventory contains:\n";
    for (const auto& item : inventory) {
        std::cout << "- " << item->getName() << ": " << item->getDescription() << "\n";
    }
}
