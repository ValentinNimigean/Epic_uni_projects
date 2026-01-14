#ifndef DSM_H
#define DSM_H

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <functional>

#define PREDEFINED_NODES 3

enum MsgType { WRITE_REQ, ACK, CAS_REQ };

struct Message {
    MsgType type;
    char var_name[16];
    int value;
    int expected;     
    int timestamp;   
    int sender_rank;  

    bool operator>(const Message& other) const {
    if (timestamp != other.timestamp)
        return timestamp > other.timestamp;
    return sender_rank > other.sender_rank;
}
};

class DSM {
public:
    using ChangeCallback = std::function<void(std::string, int)>;

    DSM(int rank, int size);
    void write(std::string var, int val);
    void compare_and_exchange(std::string var, int expected, int new_val);
    void set_callback(ChangeCallback cb);
    void sync();
    int read(std::string var) { return vars[var]; }

private:
    int rank, size, lamport_clock;
    std::map<std::string, int> vars;
    std::map<std::string, std::vector<int>> subscribers;
    std::priority_queue<Message, std::vector<Message>, std::greater<Message>> pending_queue;
    
    int last_timestamp_from[PREDEFINED_NODES];
    
    ChangeCallback on_change_cb;
    void broadcast(MsgType type, std::string var, int val, int expected);
    void send_ack(int dest);
    void process_queue();

};

#endif