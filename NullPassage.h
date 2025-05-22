//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_NULLPASSAGE_H
#define ZOORK_NULLPASSAGE_H

#include "Passage.h"
#include <memory>

class NullPassage : public Passage {
public:
    explicit NullPassage(std::shared_ptr<Room>);
};


#endif //ZOORK_NULLPASSAGE_H
