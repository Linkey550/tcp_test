#include <stdio.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc,char *argv[])
{
    if (3 != argc)
    {
        printf("Usage: %s <IP> <PROT>\n",argv[0]);
        return -1;
    }//检查输入格式
    int fd =socket(AF_INET,SOCK_STREAM,0);
    if(-1 == fd)
    {
       perror("socket ");
       return -1;
    }

    struct sockaddr_in reseveradd ={0};
    reseveradd.sin_family=AF_INET;
    reseveradd.sin_port=htons(atoi(argv[2]));
    reseveradd.sin_addr.s_addr=inet_addr(argv[1]);
    if(-1==bind(fd,(struct sockaddr*)&reseveradd,sizeof(reseveradd)))
    {
      perror("bind");
       return -1;
    }//套接字申请

    if(-1==listen(fd,100))
    {
       perror("listen");
       return -1;
    }//开启监听

    int Clientfd = accept(fd,NULL,NULL);
    if(-1==Clientfd)
    {
            perror("accept");
            return -1;
    }//接受连接

    while(1)
    {
        char buf[100]={0};
        if(0>=read(Clientfd,buf,sizeof(buf),0))
        {
            perror("recv");
            break;
        }
        else
        {
            printf("%s",buf);
        }//检查是否断开

    }
}