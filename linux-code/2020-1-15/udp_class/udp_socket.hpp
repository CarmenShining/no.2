#pragma once
#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstdio>
#include<cstring>
#include<string>
#include<unistd.h>
#include<netinet/in.h>

class UdpSocket
{
    public:
        UdpSocket()
            :fd_(-1)
        {

        }

        //打开一个Udp的socket
        bool Socket()
        {
            fd_=socket(AF_INET,SOCK_DGRAM,0);
            if(fd_<0){
                perror("socket");
                return false;
            }
            return true;
        }

        bool Close()
        {
            if(fd_!=-1){
                close(fd_);
            }
            return true;
        }

        bool Bind(const std::string &ip,uint16_t port)
        {
            //根据参数构造sockaddr_in 结构
            sockaddr_in addr;
            addr.sin_family=AF_INET;
            addr.sin_addr.s_addr=inet_addr(ip.c_str());
            addr.sin_port=htons(port);
            int ret=bind(fd_,(sockaddr *)&addr,sizeof(addr));
            if(ret<0){
                perror("bind");
                return false;
            }
            return true;
        }

        //函数的返回值除了成功失败还要返回读到的数据,对方的IP地址和端口号
        bool RecvFrom(std::string *msg,std::string *ip=NULL,uint16_t*port=NULL)
        {
            char buf[1024*10]={0};
            sockaddr_in peer;
            socklen_t len=sizeof(peer);
            //接收到数据保存在buf中
            ssize_t n=recvfrom(fd_,buf,sizeof(buf)-1,0,(sockaddr *)&peer,&len);
            if(n<0){
                perror("recvfrom");
                return false;
            }
            *msg=buf;
            if(ip!=NULL){
                *ip=inet_ntoa(peer.sin_addr);
            }
            if(port!=NULL){
                *port=ntohs(peer.sin_port);
            }
            return true;
        }

        bool SendTo(const std::string &msg,const std::string &ip,uint16_t port)
        {
            sockaddr_in addr;
            addr.sin_family=AF_INET;
            addr.sin_addr.s_addr=inet_addr(ip.c_str());
            addr.sin_port=htons(port);
            ssize_t n=sendto(fd_,msg.c_str(),msg.size(),0,(sockaddr*)&addr,sizeof(addr));
            if(n<0){
                perror("sendto");
                return false;
            }
            return true;
        }

    private:
        int fd_;//socket文件描述符
};
