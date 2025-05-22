cmake_minimum_required(VERSION 3.10)
project(ZOOrk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ZOOrk
    main.cpp
    Item.cpp
    Character.cpp
    Location.cpp
    GameObject.cpp
    Room.cpp
    Passage.cpp
    NullRoom.cpp
    NullCommand.cpp
    Player.cpp
    RoomDefaultEnterCommand.cpp
    ZOOrkEngine.cpp
    PassageDefaultEnterCommand.cpp
    NullPassage.cpp
    BossRoomEnterCommand.cpp
    NPCConversationCommand.cpp
)
