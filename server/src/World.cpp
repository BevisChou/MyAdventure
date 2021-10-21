#include "World.hpp"

World::World(MessageBus& messageBus) : messageBus(messageBus){}

World::~World(){}

void World::setMaps(const std::vector<Map>& maps){
    this->maps = maps;
}

void World::run(){}

void World::setItems(){}