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
} ringBuffer_t;

void rbInit(ringBuffer_t *rb);
int rbPush(ringBuffer_t *rb, uint8_t byte);
int rbPop(ringBuffer_t *rb, uint8_t *byte);
int rbEmpty(const ringBuffer_t *rb);
#endif //CUBEBOT_RINGBUFFER_H
