#include "MessageBus.hpp"

MessageBus::MessageBus(){}

MessageBus::~MessageBus(){}

void MessageBus::addStatePacket(StatePacket){}
    
State MessageBus::getState(){}

void MessageBus::addSimpleState(SimpleState, std::vector<std::string>){}

GroupPacket MessageBus::getGroupPacket(){}

template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(){}

template<typename T>
void ThreadSafeQueue<T>::push(T val){
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(std::move(val));
}

template<typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::pop(){
    std::lock_guard<std::mutex> lock(mutex);
    if(queue.empty()) throw EmptyQueue();
    std::shared_ptr<T> const ret = std::make_shared<T>(queue.top());
    queue.pop();
    return ret;
}

template<typename T>
bool ThreadSafeQueue<T>::empty() const{
    std::lock_guard<std::mutex> lock(mutex);
    return queue.empty();
}