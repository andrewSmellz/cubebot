//
// Created by andre on 2026-07-30.
//

#ifndef CUBEBOT_RINGBUFFER_H
#define CUBEBOT_RINGBUFFER_H
#include <stdint.h>


#define RB_SIZE 128

typedef struct {
    volatile uint8_t buf[RB_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} ring_buffer_t;

void rb_init(ring_buffer_t *rb);
int rb_push(ring_buffer_t *rb, uint8_t byte);
int rb_pop(ring_buffer_t *rb, uint8_t *byte);
int rb_empty(const ring_buffer_t *rb);
#endif //CUBEBOT_RINGBUFFER_H
