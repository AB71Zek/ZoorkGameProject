//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"
#include <memory>
#include <vector>

class Player : public Character {
public:
    static std::shared_ptr<Player> instance() {
        // Note: lazy instantiation of the singleton Player object
        if (!playerInstance) {
            playerInstance = std::shared_ptr<Player>(new Player());
        }
        return playerInstance;
    }

    void setCurrentRoom(std::shared_ptr<Room>);

    std::shared_ptr<Room> getCurrentRoom() const;

    void addItem(std::shared_ptr<Item>);
    void removeItem(const std::string&);
    std::shared_ptr<Item> getItem(const std::string&);
    std::shared_ptr<Item> retrieveItem(const std::string&);
    void showInventory() const;

    Player(const Player &) = delete;

    Player &operator=(const Player &) = delete;

private:
    static std::shared_ptr<Player> playerInstance;
    std::shared_ptr<Room> currentRoom;
    std::vector<std::shared_ptr<Item>> inventory;

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(std::make_shared<NullRoom>()) {}
};

#endif //ZOORK_PLAYER_H
