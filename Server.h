#ifndef _SERVER_H
#define _SERVER_H

#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <vector>

#include "DataStructs.h"

class Server{

  std::vector<struct PatternsList> unhandledRequests;
  std::vector<struct Tuple> tuplesList;

  key_t mainqueue_key;

public:
  //ftok(): is use to generate a unique key.
  //msgget(): either returns the message queue identifier for a newly created message queue or returns the identifiers for a queue which exists with the same key value.
  //msgsnd(): Data is placed on to a message queue by calling msgsnd().
  //msgrcv(): messages are retrieved from a queue.
  //msgctl(): It performs various operations on a queue. Generally it is use to destroy message queue.

  Server(){
      //TODO
       ftok();
       msgget();
  }

  void run(){
    for ( ; ; ) {
      struct Msg msg = recieve();
      handleMsg(msg);
    }

  }

private:

  struct Msg recieve(){
    //TODO
    return msgrvc(); // take data from main queue
  }

  void handleMsg(struct Msg msg){

    if (msg.option == 2) {
        tuplesList.push_back(msg.req);
        handleNewTuple(msg.req);
    }
    else {
        handleRequest(msg);
    }
  }

  void handleNewTuple(struct Tuple tuple){
        for (int i = 0; i < unhandledRequests.size() ; ++i){
          if (compareTupleWithPattern(tuple, unhandledRequests[i].message.req) ){
              returnTuple(unhandledRequests[i].key, tuple);
              unhandledRequests.erase(i);
              if (unhandledRequests[i].message.option == 1){ //option input
                tuplesList.erase(tuplesList.size()-1);
                return;
              }
          }
        }
  }

  void handleRequest(struct Msg msg){
      for (int i = 0; i < tuplesList.size() ; ++i){
        if (compareTupleWithPattern(tuplesList[i], msg.req)){
          tupleFoundFlag = false
          returnTuple(?key?, tuplesList[i]); //TODO
          if (msg.option == 1) {
            tuplesList.erase(i);
          }
          return;
        }
      }
      PatternsList patternsList;
      patternsList.msg = msg;
      patternsList.key = ?key?; //TODO
      unhandledRequests.push_back(patternsList);
  }

  bool compareTupleWithPattern(struct Tuple tuple, struct Pattern pattern){

    // TODO

  }

  void returnTuple(key_t key, struct Tuple){
    msgget(); //get users input queue
    msgsend(); //send tuple to users input queue
  }
};

#endif
