//
// Created by andre on 2026-07-07.
//

#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int uartInit(void){

    int fd = -1;

    // Open the Port. the options mean to read/write, no "controlling tty" status
    fd = open("/dev/ttyAMA0",O_RDWR | O_NOCTTY);

    if(fd==-1){
        printf("unable to open port /dev/ttyAMA");
        return -1;
    }

    struct termios options;

    //reads the current termios settings for file descriptor into options
    if(tcgetattr(fd, &options)!=0){
        printf("tcgetattr failed");
        close(fd);
        return -1;
    }

    //set i/o baud rates, note B115200 is a termios constant
    cfsetospeed(&options, B115200);
    cfsetispeed(&options, B115200);

    /**
     * NOTE
     * &= ~FLAG   means "clear this bit" (turn the option off)
     * |=  FLAG   means "set this bit"   (turn the option on)
     */
    options.c_cflag &= ~PARENB;//disables parity bit
    options.c_cflag &= ~CSTOPB;//disables 2 stop bits, using only 1 stop bit
    options.c_cflag &= ~CSIZE;//mask to clear many fields about size of packet
    options.c_cflag |= CS8;//set to 8 data bits
    options.c_cflag &= ~CRTSCTS;//disables hardware flow control
    options.c_cflag |= CREAD | CLOCAL;//enable reciever so bytes are read, ignore modem status lines

    //enters a raw mode where bytes are read as raw bytes are not translated
    cfmakeraw(&options);

    //options to wait 1 second for a byte
    options.c_cc[VMIN]  = 0;
    options.c_cc[VTIME] = 10;

    /**
     * actually sets all the settings chosen previously
     * TCSANOW means to apply immeditaly as opposed to waiting for an io drain/flush
     */
    if (tcsetattr(fd, TCSANOW, &options) != 0) {
        printf("tcsetattr failed");
        close(fd);
        return -1;
    }

    tcflush(fd, TCIOFLUSH);//flush any potentially stale bytes sitting around

    return fd;
}


int uartTest(int fd){
    unsigned char test_bytes[] = { 0xAA, 0xCB, 0x01, 0xFF };
    
    for (size_t i = 0; i < sizeof(test_bytes); i++) {
        unsigned char tx = test_bytes[i];
        ssize_t writeBytes = write(fd, &tx, 1);
        printf("TX: %02x\n", tx);

        unsigned char rx;
        ssize_t readBytes = read(fd, &rx, 1);
        printf("RX: %02x  %s\n", rx, (rx == tx) ? "OK" : "MISMATCH");
    }
}

int uartWrite(uartPacket_t* packet, int fd){
    unsigned char rx;
    //TODO when in a more confident position, remove these tests
    write(fd, &packet->startByte, 1);
    printf("TX: %02x\n", packet->startByte);
    read(fd, &rx, 1);
    printf("RX: %02x  %s\n", rx, (rx == packet->startByte) ? "OK" : "MISMATCH");

    write(fd, &packet->operation, 1);
    printf("TX: %02x\n", packet->operation);
    read(fd, &rx, 1);
    printf("RX: %02x  %s\n", rx, (rx == packet->operation) ? "OK" : "MISMATCH");

    write(fd, &packet->stopByte, 1);
    printf("TX: %02x\n", packet->stopByte);
    read(fd, &rx, 1);
    printf("RX: %02x  %s\n", rx, (rx == packet->stopByte) ? "OK" : "MISMATCH");
}