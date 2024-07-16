/*
本程序是一个有关tcp服务端（接收端）的例程
本程序与Server程序的区别为，本程序具有多进程的功能可以同时接收
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <strings.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,const char *argv[])
{
   char buf[100];
   int TcpSocket_accept;
       if (3 != argc)
    {
        printf("Usage: %s <IP> <PROT>\n",argv[0]);
        return -1;
    }//检查输入格式


   int TcpSocket_fd =socket(AF_INET,SOCK_STREAM,0);
   if(-1==TcpSocket_fd)
   {
        perror("recv");     
        return -1;
   }//套接字申请

   struct sockaddr_in TcpSocket_addr;
   TcpSocket_addr.sin_family = AF_INET;
   TcpSocket_addr.sin_port =htons(atoi(argv[2]));
   TcpSocket_addr.sin_addr.s_addr=inet_addr(argv[1]);

    if(-1==bind(TcpSocket_fd,(struct sockaddr*)&TcpSocket_addr,sizeof(TcpSocket_addr)))
    {
      perror("bind");
       return -1;
    }//绑定监听ip以及端口号

    if(-1==listen(TcpSocket_fd,100))
    {
       perror("listen");
       return -1;
    }//开启监听
    
    signal(SIGCHLD,SIG_IGN); //处理僵尸进程
    
    while (1)
    {
        TcpSocket_accept = accept(TcpSocket_fd,NULL,NULL);
        if(-1==TcpSocket_accept)
        {
                perror("accept");
                return -1;
        }//接受连接

        if(0==fork())//交给子进程处理
        {
          close(TcpSocket_fd);//关闭子进程多余的资源
          while(1)
          {
              bzero(buf,sizeof(buf));
              if(0>=recv(TcpSocket_accept,buf,sizeof(buf),0))
              {
                perror("recv");
                return -1;
              }//检查是否断开
              printf("%s",&buf);            
              sleep(1); 
          }
          exit(0); 
        }
        close(TcpSocket_accept);//关闭本次服务剩下的多余资源
    }
    //close(TcpSocket_accept);  
}

