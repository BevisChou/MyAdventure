#include "Client.hpp"

#include <thread>
#include <future>
#include <vector>

const std::vector<int> LISTEN_PORTS = {10000, 10001, 10002, 10003, 10004};
const int MAX_QUEUE_SIZE = 10;

const int EXPIRED_SOCKET = -1;

class ListenThread;

class Service{
public:
    Service();
    ~Service();
    void run();
private:
    void setupListenThreads();
    ClientPool clientPool;
    std::vector<ListenThread> listenThreads;
};

class ListenThread{
public:
    ListenThread(int, ClientPool&);
    ListenThread(const ListenThread&) = delete;
    ListenThread(ListenThread&&);
    ~ListenThread();
private:
    void run();
    void establishConnection(int, sockaddr_in);
    std::thread t;
    int sockfd;
    ClientPool& clientPool; // Ref: https://stackoverflow.com/questions/892133/should-i-prefer-pointers-or-references-in-member-data
};