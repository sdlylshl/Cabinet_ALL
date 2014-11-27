#ifndef _LOOPBACK_CLIENT_H_
#define _LOOPBACK_CLIENT_H_

#include <stdint.h>
#include "..\Ethernet_Config.h"

void loopback_tcpc(uint8_t sn);
int32_t loopback_udpc(uint8_t sn);

/************************/
/* Select LOOPBACK_MODE */
/************************/
#define LOOPBACK_MAIN_NOBLOCK    0
#define LOOPBACK_BLOCK_API       1
#define LOOPBACK_NONBLOCK_API    2

#define LOOPBACK_MODE   LOOPBACK_NONBLOCK_API



#endif
