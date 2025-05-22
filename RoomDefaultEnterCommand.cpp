//
// Created by Richard Skarbez on 5/7/23.
//

#include "RoomDefaultEnterCommand.h"

void RoomDefaultEnterCommand::execute() {
    std::cout << "[" << gameObject->getName() << "]\n";
    std::cout << gameObject->getDescription() << "\n";
}