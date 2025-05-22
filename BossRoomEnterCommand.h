#ifndef ZOORK_BOSSROOMENTERCOMMAND_H
#define ZOORK_BOSSROOMENTERCOMMAND_H

#include "Command.h"
#include <memory>

class BossRoomEnterCommand : public Command {
public:
    explicit BossRoomEnterCommand(GameObject* g) : Command(g) {}

    void execute() override;
};

#endif //ZOORK_BOSSROOMENTERCOMMAND_H 