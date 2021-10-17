#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <iostream>
#include <map>
#include <string>
#include <mutex>

class Client{
public:
    Client(std::string, int, sockaddr_in);
private:
    std::string nickname;
    int tcpSock;
    sockaddr_in addr;
};

class ClientPool{
public:
    ClientPool();
    ~ClientPool();
    void addClient(std::string, int, sockaddr_in);
private:
    std::mutex mutex;
    std::map<std::string, Client> clients;
};