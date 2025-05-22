//
// Created by Richard Skarbez on 5/7/23.
//

#include "NullPassage.h"

NullPassage::NullPassage(std::shared_ptr<Room> from) : Passage("null", "Time is a flat circle.", from, from) {}