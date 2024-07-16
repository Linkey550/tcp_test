/*
��������һ���й�tcp�ͻ��ˣ����Ͷˣ�������
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc,char *argv[])
{
    char s[20]={};

    if (3 != argc)
    {
        printf("Usage: %s <IP> <PROT>\n",argv[0]);
        return -1;
    }//��������ʽ
    
    int fd =socket(AF_INET,SOCK_STREAM,0);
    if(-1 == fd)
    {
       perror("socket ");
       return -1;
    }//�׽�������

    struct sockaddr_in severip={0};
    severip.sin_family =AF_INET;
    severip.sin_port = htons(atoi(argv[2]));
    severip.sin_addr.s_addr=inet_addr(argv[1]);
    if(-1==connect(fd,(struct sockaddr*)&severip,sizeof(severip)))
    {
       perror("connect");
       return -1;
    }//��������
    while (1)
    {
        memset(&s, 0x00, 20);          //������� 
        if(-1==scanf("%s",&s))//�������
        {
           perror("scanf in err");
        }
        else if(strlen(s)>=20)
        {
            perror("scanf in too long");
        }
        else
        {
         // strncat("\n",s,1);  
         //s[strlen(s)+1]='\n';
          send(fd,s,sizeof(s),0);//��������
        }
        sleep(1);
    }   
   // close(fd);
}