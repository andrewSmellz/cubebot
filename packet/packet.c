#include "packet.h"


int buildPacket(uartPacket_t* packet, move_t operation){
    packet->startByte=START_BYTE;
    packet->stopByte=STOP_BYTE;
    packet->operation=(moveOperation_t)operation+1;
}