#ifndef CONCAT_H_
#define CONCAT_H_

#define _CONCAT(a, b) a##b
#define CONCAT(a, b) _CONCAT(a, b)

#endif