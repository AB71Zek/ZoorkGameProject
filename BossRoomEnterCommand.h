#ifndef ZOORK_BOSSROOMENTERCOMMAND_H
#define ZOORK_BOSSROOMENTERCOMMAND_H

#include "Command.h"
#include "Player.h"
#include "Room.h"
#include <memory>

class BossRoomEnterCommand : public Command {
public:
    BossRoomEnterCommand(Player* player, std::shared_ptr<Room> villageSquare);
    void execute() override;
private:
    std::shared_ptr<Room> villageSquare;
};

#endif //ZOORK_BOSSROOMENTERCOMMAND_H 