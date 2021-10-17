#include "Service.hpp"

Service::Service(){
}

Service::~Service(){
}

void Service::run(){
    setupListenThreads();
}

void Service::setupListenThreads(){
    listenThreads.reserve(LISTEN_PORTS.size());
    for(int port : LISTEN_PORTS){
        // Copy ctor of std::thread is deleted, use std::move, and move ctor of ListenThread should be explicitly defined.
        listenThreads.emplace_back(ListenThread(port, clientPool)); // Ctor then move ctor.
    }
}

ListenThread::ListenThread(int port, ClientPool& clientPool) : clientPool(clientPool){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = port;

    if(bind(sockfd, (sockaddr*)&addr, (socklen_t)sizeof(addr)) == -1){
        perror("Bind error");
        exit(1);
    }

    if(listen(sockfd, MAX_QUEUE_SIZE) == -1){
        perror("Listen error.");
        exit(1);
    }

    t = std::move(std::thread(&ListenThread::run, this));
}

ListenThread::ListenThread(ListenThread&& listenThread) : 
    t(std::move(listenThread.t)), 
    sockfd(listenThread.sockfd), 
    clientPool(listenThread.clientPool) {
        // After std:move, listenThread.t is no longer joinable yet t is joinable.
        listenThread.sockfd = EXPIRED_SOCKET;
    }

ListenThread::~ListenThread(){
    // Ref: https://stackoverflow.com/questions/38287425/moved-objects-are-still-destructed
    // Ref: https://stackoverflow.com/questions/21767066/understanding-move-constructor-stdmove-and-destructor
    if(t.joinable()){
        t.join();
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
    
    // TODO
}