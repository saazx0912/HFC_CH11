# HFC_CH11
HFC_CH11


1. int listener_d = socket(PF_INET , SOCK_STREAM , 0);  listener_d是socket的描述子
   SERVER端 四個階段：bind(繫結埠口)、listen(偵聽)、Accept(接受連結)、Begin(開始交談)

2. int connect_d = accept(listener_d , (struct sockaddr *) &client_addr , &address_size);  連接描述子
