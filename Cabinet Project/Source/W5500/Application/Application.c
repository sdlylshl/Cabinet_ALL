
#include "..\Ethernet_Config.h"

// 1.客户端主动连接服务器
// 2.服务器维护一个可用列表
// 3.可用列表下面维护一个可用设备表（由用户配置）
// 4.客户端只负责执行服务端的命令，无法检测设备好坏
// 5.客户端A.定时上报设备端口状态 B.设备执行后上报设备端口状态。
//


#ifdef CABINET_DEVICE 
// 客户端动作
// 1.连接服务器
// 2.定时上报设备端口状态
// 3.接收服务器指令

void Application(void){
	// 通过第1路socket创建连接
	 loopback_tcpc(1);
	// 解析数据并执行相应命令
	
}
#else

// 服务端动作
//  1.监听传入连接
//  2.判断传入类型
//  3.创建连接表 ----总表对应
//  ID = CRC();
void Application(void){


}

#endif // CABINET_DEVICE 

