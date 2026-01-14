#include "dsm.h"
#include <mpi.h>
#include <algorithm>
#include <cstring>
#include <iostream>

DSM::DSM(int r, int s) : rank(r), size(s), lamport_clock(0) {
    std::vector<std::string> var_names = {"VAR_A", "VAR_B"};
    for (const std::string& name : var_names) {
        vars[name] = 0;
        for (int i = 0; i < size; ++i) {
            subscribers[name].push_back(i);
        }
    }
    for (int i = 0; i < PREDEFINED_NODES; ++i) {
        last_timestamp_from[i] = 0;
    }
}

void DSM::set_callback(ChangeCallback cb) { on_change_cb = cb; }

void DSM::write(std::string var, int val) {
    lamport_clock++; 
    broadcast(WRITE_REQ, var, val, 0);
}

void DSM::compare_and_exchange(std::string var, int expected, int new_val) {
    lamport_clock++; 
    broadcast(CAS_REQ, var, new_val, expected);
}

void DSM::broadcast(MsgType type, std::string var, int val, int expected) {
    Message msg;
    msg.type = type;
    std::strncpy(msg.var_name, var.c_str(), 16);
    msg.value = val;
    msg.expected = expected;
    msg.timestamp = lamport_clock;
    msg.sender_rank = rank;

    std::cout << "[Node " << rank << "] SENDING: " << (type == WRITE_REQ ? "WRITE" : "CAS") 
              << " | Var: " << var << " | Val: " << val << " | TS: " << msg.timestamp << std::endl;

    for (int dest : subscribers[var]) {
        if (dest == rank) {
            pending_queue.push(msg);
        } else {
            MPI_Send(&msg, sizeof(Message), MPI_BYTE, dest, 0, MPI_COMM_WORLD);
        }
    }
}

void DSM::send_ack(int dest) {
    Message ack;
    ack.type = ACK;
    ack.timestamp = lamport_clock;
    ack.sender_rank = rank;
    MPI_Send(&ack, sizeof(Message), MPI_BYTE, dest, 0, MPI_COMM_WORLD);
}

void DSM::sync() {
    int flag;
    MPI_Status status;
    while (true) {
        MPI_Iprobe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &flag, &status);
        if (!flag) break;

        Message msg;
        MPI_Recv(&msg, sizeof(Message), MPI_BYTE, status.MPI_SOURCE, 0, MPI_COMM_WORLD, &status);
        
        std::cout << "[Node " << rank << "] RECEIVED: " << (msg.type == ACK ? "ACK" : "REQ") 
                  << " from " << msg.sender_rank << " | TS: " << msg.timestamp << std::endl;

        lamport_clock = std::max(lamport_clock, msg.timestamp) + 1;
        last_timestamp_from[msg.sender_rank] = std::max(last_timestamp_from[msg.sender_rank], msg.timestamp);

        if (msg.type == WRITE_REQ || msg.type == CAS_REQ) {
            pending_queue.push(msg);
            send_ack(msg.sender_rank);
        }
    }
    process_queue();
}

void DSM::process_queue() {
    while (!pending_queue.empty()) {
        Message msg = pending_queue.top();
        bool safe = true;
        for (int peer : subscribers[msg.var_name]) {
            if (peer != rank && last_timestamp_from[peer] <= msg.timestamp) {
                safe = false;
                break;
            }
        }
        if (!safe) break;

        pending_queue.pop();
        std::cout << "[Node " << rank << "] COMMITTING: " << msg.var_name << " = " << msg.value << std::endl;

        if (msg.type == WRITE_REQ) {
            vars[msg.var_name] = msg.value;
            if (on_change_cb) on_change_cb(msg.var_name, msg.value);
        } else if (msg.type == CAS_REQ) {
            if (vars[msg.var_name] == msg.expected) {
                vars[msg.var_name] = msg.value;
                if (on_change_cb) on_change_cb(msg.var_name, msg.value);
            }
        }
    }
}