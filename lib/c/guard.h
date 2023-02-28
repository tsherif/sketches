#ifndef GUARD_H_
#define GUARD_H_

#include "macros.h"

#define GUARD(COND, POST) for (int CONCAT(GUARD_FLAG_, __LINE__) = 0; COND && !CONCAT(GUARD_FLAG_, __LINE__); POST, ++CONCAT(GUARD_FLAG_, __LINE__))
#define GUARD_BREAK continue

#endif