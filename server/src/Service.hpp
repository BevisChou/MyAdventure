#pragma once

#include "Network.hpp"
#include "World.hpp"
#include "MessageBus.hpp"

#include <string>

class Service{
public:
    Service();
    ~Service();
    void run();
private:
    MessageBus messageBus;
    Network network;
    World world;
};

class WorldConfig{
public:
    WorldConfig(std::string);
    const std::vector<Map>& getMaps();
private:
    std::vector<Map> maps;
};

class NetworkConfig{
public:
    NetworkConfig(std::string);
    const std::vector<int>& getListenPorts();
private:
    std::vector<int> listenPorts;
};