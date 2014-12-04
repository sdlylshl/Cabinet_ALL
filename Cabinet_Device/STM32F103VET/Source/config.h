#ifndef __CONFIG_H
#define __CONFIG_H
//使用StdPeriph_Driver库
//#define USE_STDPERIPH_DRIVER 1

#define CABINET_DEVICE 0
//#define CABINET_HOST 1

//#include "config.h"
#include "stm32f10x.h"

//全局IO配置
#include "io_config.h"
#include ".\GPIO\led.h"
#include ".\W5500\Ethernet_config.h"
#include ".\System\System_config.h"
#include ".\LCD12864\LCD12864_config.h"
#endif
