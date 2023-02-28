#include <stdio.h>

#define KEY_TYPE int
#define TYPE float
#define IMPLEMENTATION
#include "../../lib/c/map.h"

int main(void) {
    Map_int_float m = Map_int_float_create();

    printf("Map is empty: %d\n", Map_int_float_empty(&m));

    printf("Adding entries.\n");
    Map_int_float_set(&m, 1, 1.5);    
    Map_int_float_set(&m, 2, 2.5);    
    Map_int_float_set(&m, 3, 3.5);    
    Map_int_float_set(&m, 4, 5.5);    
    Map_int_float_set(&m, 2, 6.5);    
    Map_int_float_set(&m, 3, 7.5);    
    Map_int_float_set(&m, 2, 8.5);    
    Map_int_float_set(&m, 1, 9.5);
    printf("Map size: %zd\n", Map_int_float_size(&m));
    printf("Map capacity: %zd\n", m.capacity);

    for (size_t i = 0; i < m.capacity; ++i) {
        if (m.entries[i].active) {
            printf("%d = %f\n", m.entries[i].key, Map_int_float_get(&m, m.entries[i].key));
        }
    }

    printf("Adding more entries.\n");
    for (int i = 0; i < 40; ++i) {
        Map_int_float_set(&m, i, i + 0.5f);    
    }
    printf("Map size: %zd\n", Map_int_float_size(&m));
    printf("Map capacity: %zd\n", m.capacity);

    for (int i = 0; i < 40; ++i) {
        printf("%d = %f\n", i, Map_int_float_get(&m, i));
    }

    Map_int_float_clear(&m);
    printf("Clearing map.\n");
    printf("Map size: %zd\n", Map_int_float_size(&m));
    printf("Map is empty: %d\n", Map_int_float_empty(&m));

    return 0;
}