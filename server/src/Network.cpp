#include "Network.hpp"

// Network

Network::Network(MessageBus& messageBus) : messageBus(messageBus){}

Network::~Network(){}

void Network::run(){}

void Network::setListenThreads(const std::vector<int>& ports){
    listenThreads.reserve(ports.size());
    for(int port : ports){
        // Copy ctor of std::thread is deleted, use std::move, and move ctor of ListenThread should be explicitly defined.
        listenThreads.emplace_back(ListenThread(port, clientPool)); // Ctor then move ctor.
    }
}

// ListenThread

ListenThread::ListenThread(int port, ClientPool& clientPool) : clientPool(clientPool){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = port;

    if(bind(sockfd, (sockaddr*)&addr, (socklen_t)sizeof(addr)) == -1){
        throw BindError();
    }

    if(listen(sockfd, MAX_QUEUE_SIZE) == -1){
        throw ListenError();
    }

    thread = std::move(std::thread(&ListenThread::run, this));
}

ListenThread::ListenThread(ListenThread&& listenThread) : 
    thread(std::move(listenThread.thread)), 
    sockfd(listenThread.sockfd), 
    clientPool(listenThread.clientPool) {
        // After std:move, listenThread.thread is no longer joinable yet thread is joinable.
        listenThread.sockfd = EXPIRED_SOCKET;
    }

ListenThread::~ListenThread(){
    // Ref: https://stackoverflow.com/questions/38287425/moved-objects-are-still-destructed
    // Ref: https://stackoverflow.com/questions/21767066/understanding-move-constructor-stdmove-and-destructor
    if(thread.joinable()){
        thread.join();
    }
    close(sockfd); // close(EXPIRED_SOCKET) would not throw exception.
}

void ListenThread::run(){
    int clientSock;
    sockaddr_in clientAddr;
    while(true){
        int addrLen = sizeof(clientAddr);

        clientSock = accept(sockfd, (sockaddr*)&clientAddr, (socklen_t*)&addrLen);

        // Parameter type must match the signature, or there would be "static assertion failed: std::thread arguments must be invocable after conversion to rvalues".
        std::thread connT(&ListenThread::establishConnection, this, clientSock, clientAddr);
        connT.detach();
    }
}

void ListenThread::establishConnection(int clientSock, sockaddr_in clientAddr){
    timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;

    setsockopt(clientSock, SOL_SOCKET, SO_RCVTIMEO, (const void*)&tv, sizeof(tv));
}

// StatusSyncThread
StatusSyncThread::StatusSyncThread(MessageBus&, ClientPool&) : messageBus(messageBus), clientPool(clientPool) {}

StatusSyncThread::StatusSyncThread(StatusSyncThread&& statusSyncThread) : 
    thread(std::move(statusSyncThread.thread)),
    messageBus(statusSyncThread.messageBus),
    clientPool(statusSyncThread.clientPool) {}

StatusSyncThread::~StatusSyncThread(){}

void StatusSyncThread::run(){}

// MessageThread
MessageThread::MessageThread(ClientPool&) : clientPool(clientPool) {}
    
MessageThread::MessageThread(MessageThread&& messageThread):
    thread(std::move(messageThread.thread)),
    clientPool(messageThread.clientPool) {}

MessageThread::~MessageThread(){}

void MessageThread::run(){}

// Client

Client::Client(int tcpSocket, sockaddr_in addr) : tcpSocket(tcpSocket), addr(addr) {}

int Client::getSocket() const{
    return tcpSocket;
}

sockaddr_in Client::getAddr() const{
    return addr;
}

// ClientPool

ClientPool::ClientPool(){}

ClientPool::~ClientPool(){}

void ClientPool::addClient(std::string nickname, int tcpSocket, sockaddr_in addr){
    std::lock_guard<std::mutex> lock(mutex);
    auto res = clients.find(nickname);
    if(res != clients.end()){
        throw ClientAlreadyExist();
    }
    clients.emplace(std::make_pair(nickname, Client(tcpSocket, addr)));
}

const Client& ClientPool::getClient(std::string nickname) const{
    std::lock_guard<std::mutex> lock(mutex);
    auto res = clients.find(nickname);
    if(res == clients.end()){
        throw ClientNotExist();
    }
    return (res->second);
}