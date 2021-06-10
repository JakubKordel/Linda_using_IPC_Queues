#ifndef _LINDA_H
#define _LINDA_H

#include "Structs.h"

void linda_output(struct Tuple);

struct Tuple linda_input(struct Pattern, int timeout);

struct Tuple linda_read(struct Pattern, int timeout);

void linda_init();

void linda_close();

#endif
