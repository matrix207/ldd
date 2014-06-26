#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <linux/netlink.h>  

#define MAX_MSGSIZE 128

struct sig_struct_info {  
    int pid;  
    int sig;
};  

int main(int argc, char * argv[])  
{  
    struct sockaddr_nl saddr, daddr;  
    struct nlmsghdr *nlhdr = NULL;  
    struct msghdr msg;  
    struct iovec iov;  
    int sd;  
    char text_line[MAX_MSGSIZE];  
    int ret = -1;  
    struct sig_struct_info sigi;  
    memset(&sigi, 0, sizeof(sigi));  
    sigi.pid=atoi(argv[1]);  
    sigi.sig=atoi(argv[2]);  

    sd = socket(AF_NETLINK, SOCK_RAW, 111);  
    memset(&saddr, 0, sizeof(saddr));  
    memset(&daddr, 0, sizeof(daddr));  
    saddr.nl_family = AF_NETLINK;  
    saddr.nl_pid = getpid();  
    saddr.nl_groups = 0;  
    bind(sd, (struct sockaddr*)&saddr, sizeof(saddr));  
    daddr.nl_family = AF_NETLINK;  
    daddr.nl_pid = 0;  
    daddr.nl_groups = 0;  
    nlhdr = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_MSGSIZE));  
    memcpy(NLMSG_DATA(nlhdr), &sigi, sizeof(sigi));  
    memset(&msg, 0 ,sizeof(struct msghdr));  
    //    ...  
    iov.iov_base = (void *)nlhdr;  
    iov.iov_len = nlhdr->nlmsg_len;  
    msg.msg_name = (void *)&daddr;  
    msg.msg_namelen = sizeof(daddr);  
    msg.msg_iov = &iov;  
    msg.msg_iovlen = 1;  
    ret = sendmsg(sd, &msg, 0);  
    close(sd);  
    return 0;  
}  
