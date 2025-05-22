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
