//
// Created by andre on 2026-07-07.
//

#ifndef CUBEBOT_UART_H
#define CUBEBOT_UART_H
#include <stdint.h>
#include "../packet/packet.h"

int uartInit(void);
int uartTest(int fd);
int uartWrite(const uartPacket_t* packet, int fd);
void uartWriteSolution(const move_t* solution, const int fd);
int uartRead(void);

#endif //CUBEBOT_UART_H
