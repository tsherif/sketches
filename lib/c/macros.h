#ifndef MACROS_H_
#define MACROS_H_

#include "concat.h"

#define METHOD(name) CONCAT(CONTAINER, name)
#define PRIVATE(name) CONCAT(_, METHOD(name))

#endif