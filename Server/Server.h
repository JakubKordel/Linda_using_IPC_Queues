#ifndef _SERVER_H
#define _SERVER_H

#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <vector>
#include <map>
#include <utility>

#include "Structs.h"

class Server{

  std::vector<struct Msg> unhandledRequests;
  std::vector<struct Tuple> tuplesList;
  std::map<key_t,std::pair<int, int>> mapClients;

  key_t mainqueue_key;
  int msgid;

public:
  //ftok(): is use to generate a unique key.
  //msgget(): either returns the message queue identifier for a newly created message queue or returns the identifiers for a queue which exists with the same key value.
  //msgsnd(): Data is placed on to a message queue by calling msgsnd().
  //msgrcv(): messages are retrieved from a queue.
  //msgctl(): It performs various operations on a queMsgue. Generally it is use to destroy message queue.

  Server(){
       key_t mainqueue_key = ftok("keyFile.txt", 0);
       msgid = msgget(mainqueue_key, 0666 | IPC_CREAT);
  }

  void run(){
    for ( ; ; ) {
      struct Msg msg = recieve();
      std::cout << msg.option << std::endl;
      handleMsg(msg);
    }

  }

private:

  struct Msg recieve(){
    struct msgbufMsg msgbuffer;
    std::cout << "waiting for next msg" << std::endl;
    msgrcv(msgid, &msgbuffer, sizeof(struct msgbufMsg), 1, 0); // take data from main queue
    return msgbuffer.mtext;
  }

  void handleMsg(struct Msg msg){

    if (msg.option == 2) {
        std::cout << "Pushing back tuple" << std::endl;
        tuplesList.push_back(msg.req.tuple);
        handleNewTuple(msg.req.tuple);
    } else
    if (msg.option == 3) {
      auto it = mapClients.find(msg.key);
      if (it->second.first == it->second.second){
          deleteRequest(msg.key);
          setHandledRequest(msg.key);
          sendTimeout(msg.key);
      }
      ++(it->second.second);

    }
    else {
      auto it = mapClients.find(msg.key);

      if (it == mapClients.end()){
        mapClients.insert(std::pair<key_t,std::pair<int,int>>(msg.key, std::pair<int, int>(0,0 ) ));
      }
      handleRequest(msg);
    }
  }

  void setHandledRequest(key_t client_key){
    auto it = mapClients.find(client_key);
    if (it != mapClients.end()){
      ++(it->second.first);
    }
  }


  void handleNewTuple(struct Tuple tuple){
        for (auto i = unhandledRequests.begin(); i != unhandledRequests.end() ; ++i){
          if (compareTupleWithPattern(tuple, i->req.pattern) ){
              std::cout << "Returning tuple" << std::endl;
              returnTuple(i->key, tuple);
              unhandledRequests.erase(i);
              setHandledRequest(i->key);
              if (i->option == 1){ //option input
                tuplesList.pop_back();
              }
              return;
          }
        }
  }

  void handleRequest(struct Msg msg){
      for (auto i = tuplesList.begin(); i < tuplesList.end() ; ++i){
        std::cout << "I am comparing tuples" << std::endl;
        if (compareTupleWithPattern(*i, msg.req.pattern)){
          std::cout << "Returning tuple" << std::endl;
          returnTuple(msg.key, *i);
          setHandledRequest(msg.key);
          if (msg.option == 1) {
            tuplesList.erase(i);
          }
          return;
        }
      }
      unhandledRequests.push_back(msg);
  }

  bool compareTupleWithPattern(struct Tuple tuple, struct Pattern pattern){
    if (tuple.tel_amount != pattern.pel_amount) {
        return false;
    }
    for (int i = 0; i < pattern.pel_amount; ++i) {
        if (pattern.pel[i].type != tuple.tel[i].type) {
            return false;
        }
        switch (pattern.pel[i].condition) {
        case 0: // ==
            switch (pattern.pel[i].type) {
            case 0: // integer
                if (! (tuple.tel[i].value.i == pattern.pel[i].value.i) ) {
                    return false;
                }
                break;
            case 1: // string
                if ( strcmp(tuple.tel[i].value.s, pattern.pel[i].value.s) ) {
                    return false;
                }
                break;
            case 2: // float
                if (! (tuple.tel[i].value.f == pattern.pel[i].value.f) ) {
                    return false;
                }
                break;
            }
            break;
        case 1: // <
            switch (pattern.pel[i].type) {
            case 0: // integer
                if (! (tuple.tel[i].value.i < pattern.pel[i].value.i) ) {
                    return false;
                }
                break;
            case 1: // string
                if (! (strcmp(tuple.tel[i].value.s, pattern.pel[i].value.s) < 0) ) {
                    return false;
                }
                break;
            case 2: // float
                if (!(tuple.tel[i].value.f < pattern.pel[i].value.f)) {
                    return false;
                }
                break;
            }
            break;
        case 2: // <=
            switch (pattern.pel[i].type) {
            case 0: // integer
                if (! (tuple.tel[i].value.i <= pattern.pel[i].value.i) ) {
                    return false;
                }
                break;
            case 1: // string
                if (! (strcmp(tuple.tel[i].value.s, pattern.pel[i].value.s) <= 0) ) {
                    return false;
                }
                break;
            case 2: // float
                if (! (tuple.tel[i].value.f <= pattern.pel[i].value.f) ) {
                    return false;
                }
                break;
            }
            break;
        case 3: // >
            switch (pattern.pel[i].type) {
            case 0: // integer
                if (! (tuple.tel[i].value.i > pattern.pel[i].value.i) ) {
                    return false;
                }
                break;
            case 1: // string
                if (! (strcmp(tuple.tel[i].value.s, pattern.pel[i].value.s) > 0) ) {
                    return false;
                }
                break;
            case 2: // float
                if (! (tuple.tel[i].value.f > pattern.pel[i].value.f) ) {
                    return false;
                }
                break;
            }
            break;
        case 4: // >=
            switch (pattern.pel[i].type) {
            case 0: // integer
                if (! (tuple.tel[i].value.i >= pattern.pel[i].value.i) ) {
                    return false;
                }
                break;
            case 1: // string
                if (! (strcmp(tuple.tel[i].value.s, pattern.pel[i].value.s) >= 0) ) {
                    return false;
                }
                break;
            case 2: // float
                if (! (tuple.tel[i].value.f >= pattern.pel[i].value.f) ) {
                    return false;
                }
                break;
            }
            break;
        case 5: // *
            break;
        }
    }
    return true;
  }

  void returnTuple(key_t client_key, struct Tuple tuple){
    int client_msgid = msgget(client_key, 0); //get users input queue
    msgbufTuple msgbuf;
    msgbuf.mtype = 1;
    msgbuf.mtext = tuple;
    std::cout << "sending msg to client gid: " << client_msgid << std::endl;
    msgsnd(client_msgid, &msgbuf, sizeof(struct msgbufTuple), 0);
  }

  void deleteRequest(key_t client_key){
    for (auto i = unhandledRequests.begin(); i != unhandledRequests.end() ; ++i){
      if (i->key == client_key){
        unhandledRequests.erase(i);
        break;
      }
    }
  }

  void sendTimeout(key_t client_key){
    int client_msgid = msgget(client_key, 0); //get users input queue
    msgbufTuple msgbuf;
    msgbuf.mtype = 1;
    msgbuf.mtext.tel_amount = -1;
    std::cout << "sending timeout to client gid: " << client_msgid << std::endl;
    msgsnd(client_msgid, &msgbuf, sizeof(struct msgbufTuple), 0);
  }
};

#endif
