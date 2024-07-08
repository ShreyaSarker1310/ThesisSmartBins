#ifndef UTILS_H_

#define UTILS_H_

enum Direction { UP = 0, DOWN = 1, SIDE_SIBLING = 2, SIDE_PEER = 3, NODIR = 4 };

enum ResultCode { SUCCESS = 0, NOT_FOUND = -1 };

enum OpCode {
  REGISTRATION = 0,
  UPDATE = 1,
  CANCELLATION = 2,
  QUERY = 3,
  PUT = 4,
  GET = 5,
  REPLY = 6,
  RESPONSE = 7,
  NOTIFY = 8
};

#endif
