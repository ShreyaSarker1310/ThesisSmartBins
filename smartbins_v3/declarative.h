#ifndef DECLARATIVE_H_
#define DECLARATIVE_H_

#ifndef TYPES_H_
#include "types.h"
#endif

std::map<std::string, Direction> gateToDirection = {
    {"customer", DOWN},
    {"sibling", SIDE_SIBLING},
    {"peer", SIDE_PEER},
    {"provider", UP},
};

#endif
