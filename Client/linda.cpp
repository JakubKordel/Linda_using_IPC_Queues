#include "linda.h"
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <iostream>

void linda_output(struct Tuple tuple){

  Msg msg;
  msg.option = 2;
  msg.req.tuple = tuple;

  key_t key = ftok("../Server/keyFile.txt", 0);
  int msgid = msgget(key, 0);

  msgbufMsg msgbuffer;
  msgbuffer.mtype = 1;
  msgbuffer.msg = msg;
  msgsnd(msgid, &msgbuffer, sizeof(struct msgbufMsg), 0);

}


struct Tuple linda_input(struct Pattern pattern, int timeout){

  Tuple tuple;

  key_t client_key = ftok("../Server/keyFile.txt", getpid());
  int client_msgid = msgget(client_key, 0);
  std::cout << "Msggid: " << client_msgid << std::endl;

  Msg msg;
  msg.option = 1;
  msg.req.pattern = pattern;
  msg.key = client_key;

  key_t mainqueue_key = ftok("../Server/keyFile.txt", 0);
  int server_msgid = msgget(mainqueue_key, 0);

  msgbufMsg msgbuffer;
  msgbuffer.mtype = 1;
  msgbuffer.msg = msg;

  msgsnd(server_msgid, &msgbuffer, sizeof(struct msgbufMsg), 0);

  msgbufTuple msgbufferTuple;
  msgrcv(client_msgid, &msgbufferTuple, sizeof(struct msgbufTuple), 1, 0);


  return msgbufferTuple.tuple;
}

struct Tuple linda_read(struct Pattern pattern, int timeout){

  Tuple tuple;

  key_t client_key = ftok("../Server/keyFile.txt", getpid());
  int client_msgid = msgget(client_key, 0);
  std::cout << "Msggid: " << client_msgid << std::endl;

  Msg msg;
  msg.option = 0;
  msg.req.pattern = pattern;
  msg.key = client_key;

  key_t mainqueue_key = ftok("../Server/keyFile.txt", 0);
  int server_msgid = msgget(mainqueue_key, 0);

  msgbufMsg msgbuffer;
  msgbuffer.mtype = 1;
  msgbuffer.msg = msg;

  msgsnd(server_msgid, &msgbuffer, sizeof(struct msgbufMsg), 0);

  msgbufTuple msgbufferTuple;
  msgrcv(client_msgid, &msgbufferTuple, sizeof(struct msgbufTuple), 1, 0);


  return msgbufferTuple.tuple;

  return tuple;
}

void linda_init(){
  key_t key = ftok("../Server/keyFile.txt", getpid());
  int msgid = msgget(key, 0666 | IPC_CREAT);
  std::cout << "Msggid: " << msgid << std::endl;
}

void linda_close(){
  key_t key = ftok("../Server/keyFile.txt", getpid());
  int msgid = msgget(key, 0);
  std::cout << "Msggid: " << msgid << std::endl;
  msgctl(msgid, IPC_RMID, NULL);
}
