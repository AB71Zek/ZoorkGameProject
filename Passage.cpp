//
// Created by Richard Skarbez on 5/7/23.
//

#include "Passage.h"

#include <utility>
#include "PassageDefaultEnterCommand.h"

std::string Passage::oppositeDirection(const std::string &s) {
    if (s == "north") return "south";
    else if (s == "south") return "north";
    else if (s == "east") return "west";
    else if (s == "west") return "east";
    else if (s == "up") return "down";
    else if (s == "down") return "up";
    else if (s == "in") return "out";
    else if (s == "out") return "in";
    else return "unknown_direction";
}

void Passage::createBasicPassage(std::shared_ptr<Room> from, std::shared_ptr<Room> to,
                                 const std::string &direction, bool bidirectional) {
    std::string passageName = from->getName() + "_to_" + to->getName();
    auto temp1 = std::make_shared<Passage>(passageName, "A totally normal passageway.", from, to);
    from->addPassage(direction, temp1);
    if (bidirectional) {
        std::string passageName2 = to->getName() + "_to_" + from->getName();
        auto temp2 = std::make_shared<Passage>(passageName, "A totally normal passageway.", to, from);
        to->addPassage(oppositeDirection(direction), temp2);
    }
}

Passage::Passage(const std::string &n, const std::string &d, std::shared_ptr<Room> from, std::shared_ptr<Room> to)
        : Location(n, d), fromRoom(std::move(from)), toRoom(std::move(to)) {
    setEnterCommand(std::make_shared<PassageDefaultEnterCommand>(this));
}

Passage::Passage(const std::string &n, const std::string &d, std::shared_ptr<Command> c, std::shared_ptr<Room> from,
                 std::shared_ptr<Room> to)
        : Location(n, d, std::move(c)), fromRoom(std::move(from)), toRoom(std::move(to)) {}

void Passage::setFrom(std::shared_ptr<Room> r) {
    fromRoom = std::move(r);
}

std::shared_ptr<Room> Passage::getFrom() const {
    return fromRoom;
}

void Passage::setTo(std::shared_ptr<Room> r) {
    toRoom = std::move(r);
}

std::shared_ptr<Room> Passage::getTo() const {
    return toRoom;
}