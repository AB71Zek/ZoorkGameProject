#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"
#include "BossRoomEnterCommand.h"

int main() {
    // Create rooms for the hero's journey
    std::shared_ptr<Room> village = std::make_shared<Room>("village",
        "You are in a peaceful village. The sun is setting, casting long shadows across the cobblestone streets. "
        "The village square is quiet, with only a few villagers going about their evening business.\n");

    std::shared_ptr<Room> village_inn = std::make_shared<Room>("village-inn",
        "The village inn is warm and cozy. A fire crackles in the hearth, and the smell of fresh bread fills the air. "
        "The innkeeper is behind the counter, polishing glasses.\n");

    std::shared_ptr<Room> village_square = std::make_shared<Room>("village-square",
        "The village square is the heart of the community. A large fountain stands in the center, surrounded by market stalls. "
        "The town hall rises majestically to the north.\n");

    std::shared_ptr<Room> town_hall = std::make_shared<Room>("town-hall",
        "The town hall is an impressive building with high ceilings and polished wooden floors. "
        "The mayor's office is to the north, and the council chamber is to the east.\n");

    std::shared_ptr<Room> mayors_office = std::make_shared<Room>("mayors-office",
        "The mayor's office is elegantly furnished with a large desk and comfortable chairs. "
        "A map of the kingdom hangs on the wall, showing the dangerous forest to the east of the village square.\n");

    std::shared_ptr<Room> council_chamber = std::make_shared<Room>("council-chamber",
        "The council chamber is a circular room with a large round table in the center. "
        "Ancient tapestries line the walls, telling stories of past heroes.\n");

    std::shared_ptr<Room> forest_entrance = std::make_shared<Room>("forest-entrance",
        "You stand at the edge of the Dark Forest. The trees loom tall and foreboding, their branches creating a natural archway. "
        "The path continues deeper into the forest to the east.\n");

    std::shared_ptr<Room> forest_clearing = std::make_shared<Room>("forest-clearing",
        "A small clearing in the forest. Sunlight filters through the canopy, creating dappled patterns on the ground. "
        "A mysterious stone altar stands in the center.\n");

    std::shared_ptr<Room> ancient_ruins = std::make_shared<Room>("ancient-ruins",
        "Crumbling stone walls and broken columns rise from the forest floor. This was once a great temple, "
        "now reclaimed by nature. A staircase leads down into darkness.\n");

    std::shared_ptr<Room> temple_chamber = std::make_shared<Room>("temple-chamber",
        "The underground temple chamber is surprisingly well-preserved. Ancient runes glow faintly on the walls, "
        "and a pedestal stands in the center of the room.\n");

    std::shared_ptr<Room> secret_garden = std::make_shared<Room>("secret-garden",
        "A hidden garden behind the temple. Crystal-clear water flows from a spring, feeding a small pool. "
        "Magical plants grow in abundance, their flowers glowing with inner light. You hear a dragon roar coming from the east.\n");

    std::shared_ptr<Room> boss_room = std::make_shared<Room>("boss-room",
        "A massive chamber with high ceilings. The air is thick with smoke and the smell of sulfur. "
        "A huge dragon stands before you, its scales glinting in the dim light.\n",
        std::make_shared<BossRoomEnterCommand>(Player::instance().get(), village_square));  // Pass the Player instance and village_square

    // Create some test items
    auto key = std::make_shared<Item>("key", "A rusty old key that might unlock something.");
    auto map = std::make_shared<Item>("map", "A detailed map of the kingdom.");
    auto sword = std::make_shared<Item>("sword", "A gleaming steel sword.");
    auto potion = std::make_shared<Item>("potion", "A mysterious glowing potion.");

    // Add items to rooms
    village->addItem(key);
    village_square->addItem(map);
    town_hall->addItem(sword);
    mayors_office->addItem(potion);

    // Create passages between rooms
    Passage::createBasicPassage(village, village_inn, "in", true);
    Passage::createBasicPassage(village, village_square, "north", true);
    Passage::createBasicPassage(village_square, town_hall, "north", true);
    Passage::createBasicPassage(town_hall, mayors_office, "north", true);
    Passage::createBasicPassage(town_hall, council_chamber, "east", true);
    Passage::createBasicPassage(village_square, forest_entrance, "east", true);
    Passage::createBasicPassage(forest_entrance, forest_clearing, "east", true);
    Passage::createBasicPassage(forest_clearing, ancient_ruins, "east", true);
    Passage::createBasicPassage(ancient_ruins, temple_chamber, "down", true);
    Passage::createBasicPassage(temple_chamber, secret_garden, "east", true);
    Passage::createBasicPassage(secret_garden, boss_room, "east", true);

    // Set the gameObject for the boss room command
    boss_room->setEnterCommand(std::make_shared<BossRoomEnterCommand>(Player::instance().get(), village_square));

    // Start the game in the village
    ZOOrkEngine zoork(village);
    zoork.run();

    return 0;
}
