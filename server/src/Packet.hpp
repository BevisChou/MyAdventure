#include "common.hpp"

struct StatePacket{
    char identifier[IDENTIFIER_SIZE];
    uint8 mapId;
    uint16 x;
    uint16 y;
    uint8 status[STATUS_SIZE];
};

struct SimpleStatePacket{
    char identifier[IDENTIFIER_SIZE];
    uint16 x;
    uint16 y;
    uint8 status[SIMPLE_STATUS_SIZE];
};

struct MessagePacket{
    char sender[IDENTIFIER_SIZE];
    char receiver[IDENTIFIER_SIZE];
    char message[MESSAGE_SIZE];
};

class GroupPacket{
public:
    GroupPacket(SimpleStatePacket, std::vector<std::string>);
private:
    SimpleStatePacket packet;
    std::vector<std::string> receivers;
};