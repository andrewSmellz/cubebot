//
// Created by andre on 2026-07-07.
//

#ifndef CUBEBOT_PACKET_H
#define CUBEBOT_PACKET_H
#include <stdint.h>

#define START_BYTE 0xAA
#define STOP_BYTE 0xFF

typedef enum {
    MOVE_OP_U = 0x01, MOVE_OP_U2 = 0x02, MOVE_OP_UP = 0x03,
    MOVE_OP_R = 0x04, MOVE_OP_R2 = 0x05, MOVE_OP_RP = 0x06,
    MOVE_OP_F = 0x07, MOVE_OP_F2 = 0x08, MOVE_OP_FP = 0x09,
    MOVE_OP_D = 0x0A, MOVE_OP_D2 = 0x0B, MOVE_OP_DP = 0x0C,
    MOVE_OP_L = 0x0D, MOVE_OP_L2 = 0x0E, MOVE_OP_LP = 0x0F,
    MOVE_OP_B = 0x10, MOVE_OP_B2 = 0x11, MOVE_OP_BP = 0x12,
} moveOperation_t;

typedef struct {
    uint8_t startByte;
    uint8_t operation;
    uint8_t stopByte;
}uartPacket_t;

#endif //CUBEBOT_PACKET_H
