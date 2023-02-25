#ifndef MACROS_H_
#define MACROS_H_

#define _CONCAT(a, b) a##b
#define CONCAT(a, b) _CONCAT(a, b)
#define CONTAINER CONCAT(CONTAINER_PREFIX, TYPE)
#define METHOD(name) CONCAT(CONTAINER, name)
#define PRIVATE(name) CONCAT(_, METHOD(name))

#endif