
#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

struct queue {
    double *items;
    int head;
    int capacity;
    int num_items;
};

queue queue_new() {
    int default_size = 7;
    int i;

    queue result = emalloc(sizeof * result);

    result->head = 0;
    result->capacity = default_size;
    result->num_items = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);

    for(i = 0; i < default_size; i++){
        result->items[i] = 0;
    }

    return result;
        
}

void enqueue(queue q, double item) {
    if (q->num_items < q->capacity) {
        q->items[(q->head + q->num_items++) % q->capacity] = item;
    }
}

double dequeue(queue q){
    double contents;
    if(q->num_items > 0){
        contents = q->items[q->head];

        q->head++;
        q->num_items--;
        return contents;
    }

    return EXIT_FAILURE;
}

void queue_print(queue q) {
    /* print queue contents one per line to 2 decimal places */
    int i;

    for(i = 0; i < q->num_items; i++){
        printf("%.2f\n", q->items[(q->head + i) % q->capacity]);
    }
}

void queue_print_info(queue q) {
    int i;
    printf("capacity %d, num_items %d, head %d\n[", q->capacity,
           q->num_items, q->head);
    for (i = 0; i < q->capacity; i++) {
        printf("%s%.2f", i == 0 ? "" : ", ", q->items[i]);
    }
    printf("]\n");
}

int queue_size(queue q){
    return q->num_items;
}

queue queue_free(queue q){

    if(q->items != NULL){
        free(q->items);
    }

    free(q);
}
