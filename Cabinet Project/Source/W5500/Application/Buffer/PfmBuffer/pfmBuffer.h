#ifndef __PFMBUFFER_H
#define __PFMBUFFER_H

#include "version.h"

extern uint8_t recv_head;
extern uint8_t recv_tail;

uint8_t tcpc_RevcDatToBuff(uint8_t sn);
uint8_t PfmBuffer_Read(void);
uint8_t PfmBuffer_Next(uint8_t size);
void ParseInstruction(void);

#endif
