//
// Created by andre on 2026-07-07.
//

#ifndef CUBEBOT_UART_H
#define CUBEBOT_UART_H
#include <stdint.h>

int uartInit(void);
int uartTest(int fd);
int uartWrite(void);
int uartRead(void);

#endif //CUBEBOT_UART_H
