#pragma once

#include "MessageBus.hpp"
#include "common.hpp"

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

const int MAX_QUEUE_SIZE = 10;
const int EXPIRED_SOCKET = -1;

class Client{
public:
    Client(int, sockaddr_in);
    int getSocket() const;
    sockaddr_in getAddr() const;
private:
    int tcpSocket;
    sockaddr_in addr;
};

class ClientPool{
public:
    ClientPool();
    ~ClientPool();
    void addClient(std::string, int, sockaddr_in);
    const Client& getClient(std::string) const;
private:
    mutable std::mutex mutex;
    std::unordered_map<std::string, Client> clients;
};

// Ref: https://stackoverflow.com/questions/12466055/field-has-incomplete-type-error

// Pending: considering whether it's appropriate to create a base class for the following three classes.
class ListenThread{
public:
    ListenThread(int, ClientPool&);
    ListenThread(const ListenThread&) = delete;
    ListenThread(ListenThread&&);
    ~ListenThread();
private:
    void run();
    void establishConnection(int, sockaddr_in);
    std::thread thread;
    int sockfd;
    ClientPool& clientPool; // Ref: https://stackoverflow.com/questions/892133/should-i-prefer-pointers-or-references-in-member-data
};

class StatusSyncThread{
public:
    StatusSyncThread(MessageBus&, ClientPool&);
    StatusSyncThread(const StatusSyncThread&) = delete;
    StatusSyncThread(StatusSyncThread&&);
    ~StatusSyncThread();
private:
    void run();
    std::thread thread;
    MessageBus& messageBus;
    const ClientPool& clientPool;
};

class MessageThread{
public:
    MessageThread(ClientPool&);
    MessageThread(const MessageThread&) = delete;
    MessageThread(MessageThread&&);
    ~MessageThread();
private:
    void run();
    std::thread thread;
    ClientPool& clientPool; // Might remove disconnected clients.
};

class Network{
public:
    Network(MessageBus&);
    ~Network();
    void setListenThreads(const std::vector<int>&);
    void setStatusSyncThreads(const std::vector<int>&);
    void run();
private:
    MessageBus& messageBus;
    ClientPool clientPool;
    
    std::vector<ListenThread> listenThreads;
    std::vector<StatusSyncThread> statusSyncThreads;
    std::vector<MessageThread> messageThreads;
};

struct BindError : std::exception{};
struct ListenError : std::exception{};

struct ClientNotExist : std::exception{};
struct ClientAlreadyExist : std::exception{};