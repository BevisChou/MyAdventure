#pragma once

#include "MessageBus.hpp"
#include "common.hpp"

class Map;

class World{
public:
    World(MessageBus&);
    ~World();
    void setMaps(const std::vector<Map>&);
    void run();
private:
    void setItems();
    MessageBus& messageBus;
    std::vector<Map> maps;
};

class Map{
public:
private:
};