//
// Created by andre on 2026-07-30.
//
#include "../Inc/ringbuffer.h"

void rb_init(ring_buffer_t *rb) {
    rb->head = 0;
    rb->tail = 0;
}

int rb_push(ring_buffer_t *rb, uint8_t byte) {
    const uint16_t next = (rb->head + 1) & (RB_SIZE - 1);
    if (next == rb->tail) return -1; // full — byte dropped
    rb->buf[rb->head] = byte;
    rb->head = next;
    return 1;
}

int rb_pop(ring_buffer_t *rb, uint8_t *byte) {
    if (rb->tail == rb->head) return -1; // empty
    *byte = rb->buf[rb->tail];
    rb->tail = (rb->tail + 1) & (RB_SIZE - 1);
    return 1;
}

int rb_empty(const ring_buffer_t *rb) {
    return rb->tail == rb->head;
}