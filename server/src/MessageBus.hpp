#pragma once

#include "Packet.hpp"
#include "State.hpp"

template<typename T>
class ThreadSafeQueue{
public:
    ThreadSafeQueue();
    void push(T);
    std::shared_ptr<T> pop();
    bool empty() const; // const decides that std::mutex must be mutable, see "Ref" for mutex
private:
    mutable std::mutex mutex; // Ref: https://stackoverflow.com/questions/105014/does-the-mutable-keyword-have-any-purpose-other-than-allowing-the-variable-to
    std::queue<T> queue;
};

class MessageBus{
public:
    MessageBus();
    ~MessageBus();
    void addStatePacket(StatePacket); // Called by Network class.
    State getState(); // Called by World class. 
    void addSimpleState(SimpleState, std::vector<std::string>); // Called by World class.
    GroupPacket getGroupPacket(); // Called by Network class.
private:    
    ThreadSafeQueue<StatePacket> statePackets;
    ThreadSafeQueue<State> states;
    ThreadSafeQueue<GroupPacket> groupPackets;
};

struct EmptyQueue : std::exception{};