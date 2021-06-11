#ifndef UNIX_PROJEKT_STRUCTS_H
#define UNIX_PROJEKT_STRUCTS_H

#include <sys/types.h>

union Element
{
    char s[20];
    int i;
    float f;
};

struct TupleElement
{
    int type;           // 0 integer / 1 string / 2 float
    Element value;
};

struct Tuple
{
    TupleElement tel[20];
    int tel_amount;
};

struct PatternElement
{
    int type;           // 0 integer / 1 string / 2 float
    int condition;      // 0 - == , 1 - <, 2 - <=, 3 - > ,4 - >=, 5 -  *
    Element value;
};

struct Pattern
{
    PatternElement pel[20];
    int pel_amount;
};

union Request
{
    Tuple tuple;
    Pattern pattern;
};

struct Msg
{
    int option;         // 0 read/ 1 input/ 2 output
    Request req;
    key_t key;
};

struct msgbufMsg {
    long mtype;
    Msg mtext;
};

struct msgbufTuple {
    long mtype;       /* typ wiadomości, musi być > 0 */
    Tuple mtext;    /* dane wiadomości */
};



#endif //UNIX_PROJEKT_STRUCTS_H
