#pragma once

#include "Command.h"
#include <string>

class NPCConversationCommand : public Command {
public:
    NPCConversationCommand();
    void execute() override;
}; 