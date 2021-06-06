#ifndef _DATASTRUCTS_H
#define _DATASTRUCTS_H

struct Tuple {
	union Element el[20];
}

union Element {
	char string[20];
	int i;
	float f;
}

struct Pattern {
	struct PatternElement pel[20];
}

struct PatternElement {
	int type; // 0 integer / 1 string / 2 float
	int condition; // 0 - == , 1 - <, 2 - <=, 3 - > ,4 - >=, 5 -  *
	Element value;
}

union Request {
  struct Tuple tuple;
	struct Pattern pattern;
}

struct Msg {
	int option; // 0 read/ 1 input/ 2 output
	union Request req;
}

struct PatternsList {
	key_t key;
	struct Msg message;

}

#endif
