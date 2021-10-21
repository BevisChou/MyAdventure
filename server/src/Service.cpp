#include "Service.hpp"

Service::Service() : messageBus(), network(messageBus), world(messageBus) {
    WorldConfig worldConfig("dummy");
    NetworkConfig networkConfig("dummy");
    network.setListenThreads(networkConfig.getListenPorts());
    world.setMaps(worldConfig.getMaps());
}

Service::~Service(){}

void Service::run(){
    world.run();
    network.run();
}

WorldConfig::WorldConfig(std::string configPath){}

const std::vector<Map>& WorldConfig::getMaps(){}

NetworkConfig::NetworkConfig(std::string configPath){}

const std::vector<int>& NetworkConfig::getListenPorts(){}