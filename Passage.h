//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_PASSAGE_H
#define ZOORK_PASSAGE_H

#include "NullRoom.h"
#include "Room.h"
#include <iostream>
#include <memory>

class Passage : public Location {
public:
    static void
    createBasicPassage(std::shared_ptr<Room>, std::shared_ptr<Room>, const std::string &, bool);

    Passage(const std::string &, const std::string &, std::shared_ptr<Room>, std::shared_ptr<Room>);

    Passage(const std::string &, const std::string &, std::shared_ptr<Command>, std::shared_ptr<Room>, std::shared_ptr<Room>);

    void setFrom(std::shared_ptr<Room>);

    std::shared_ptr<Room> getFrom() const;

    void setTo(std::shared_ptr<Room>);

    std::shared_ptr<Room> getTo() const;

protected:
    static std::string oppositeDirection(const std::string &);

    std::shared_ptr<Room> fromRoom;
    std::shared_ptr<Room> toRoom;
};

#endif //ZOORK_PASSAGE_H
