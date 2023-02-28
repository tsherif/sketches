#ifndef MACROS_H_
#define MACROS_H_

#include "concat.h"

#define CONTAINER CONCAT(CONTAINER_PREFIX, TYPE)
#define METHOD(name) CONCAT(CONTAINER, name)
#define PRIVATE(name) CONCAT(_, METHOD(name))

#endif