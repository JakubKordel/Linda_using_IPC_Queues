#include "linda.h"
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

void linda_output(struct Tuple tuple){

  Msg msg;
  msg.option = 2;
  msg.req.tuple = tuple;

  key_t key = ftok("keyFile.txt", 0);
  int msgid = msgget(key, 0666);
  msgsnd(msgid, &msg, sizeof(struct Msg), 0);

}


struct Tuple linda_input(struct Pattern pattern, int timeout){

  Tuple tuple;

  key_t client_key = ftok("keyFile.txt", getpid());
  int client_msgid = msgget(client_key, 0666);

  Msg msg;
  msg.option = 1;
  msg.req.pattern = pattern;
  msg.key = client_key;

  key_t mainqueue_key = ftok("keyFile.txt", 0);
  int server_msgid = msgget(mainqueue_key, 0666);

  msgsnd(server_msgid, &msg, sizeof(struct Msg), 0);
  msgrcv(client_msgid, &tuple, sizeof(struct Tuple), 1, 0);
  return tuple;

}

struct Tuple linda_read(struct Pattern pattern, int timeout){

  Tuple tuple;

  key_t client_key = ftok("keyFile.txt", getpid());
  int client_msgid = msgget(client_key, 0666);

  Msg msg;
  msg.option = 0;
  msg.req.pattern = pattern;
  msg.key = client_key;

  key_t mainqueue_key = ftok("keyFile.txt", 0);
  int server_msgid = msgget(mainqueue_key, 0666);

  msgsnd(server_msgid, &msg, sizeof(struct Msg), 0);
  msgrcv(client_msgid, &tuple, sizeof(struct Tuple), 1, 0);
  return tuple;
}

void linda_init(){
  key_t key = ftok("keyFile.txt", getpid());
  int msgid = msgget(key, IPC_CREAT);
}

void linda_close(){
  key_t key = ftok("keyFile.txt", getpid());
  int msgid = msgget(key, 0666);
  msgctl(msgid, IPC_RMID, NULL);
}
