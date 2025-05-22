//
// Created by Richard Skarbez on 5/7/23.
//

#include "NullPassage.h"
#include "Room.h"
#include <iostream>

#include <utility>


Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    if (passageMap.find(direction) != passageMap.end()) {
        passageMap.erase(direction);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    if (passageMap.find(direction) != passageMap.end()) {
        return passageMap.at(direction);
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(std::static_pointer_cast<Room>(shared_from_this()));
    }
}

void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(std::move(item));
}

void Room::removeItem(const std::string& itemName) {
    items.erase(
        std::remove_if(items.begin(), items.end(),
            [&itemName](const std::shared_ptr<Item>& item) {
                return item->getName() == itemName;
            }
        ),
        items.end()
    );
}

std::shared_ptr<Item> Room::getItem(const std::string& itemName) {
    for (const auto& item : items) {
        if (item->getName() == itemName) {
            return item;
        }
    }
    return nullptr;
}

std::shared_ptr<Item> Room::retrieveItem(const std::string& itemName) {
    auto item = getItem(itemName);
    if (item) {
        removeItem(itemName);
    }
    return item;
}