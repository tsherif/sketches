#ifndef MACROS_H_
#define MACROS_H_

#define CONCAT(a, b) a##b
#define PREFIX(prefix, name) CONCAT(prefix, name)
#define SUFFIX(name, suffix) CONCAT(name, suffix)
#define CONTAINER PREFIX(CONTAINER_PREFIX, TYPE)
#define METHOD(name) SUFFIX(CONTAINER, name)

#endif