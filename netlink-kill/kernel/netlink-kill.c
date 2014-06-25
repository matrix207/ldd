#include <linux/module.h>  
#include <linux/netlink.h>  
#include <linux/sched.h>  
#include <net/sock.h>  
#include <linux/proc_fs.h>  
#include <asm/siginfo.h>  
#include <linux/signal.h>  
static struct sock *netlink_kill_sock;  
static int flag = 0;  
struct sig_struct_info {  
    int pid;  
    int sig  
};  
static DECLARE_COMPLETION(exit_completion);  
static void recv_handler(struct sock * sk, int length)  
{  
    wake_up(sk->sk_sleep);  
}  
static int process_message_thread(void * data)  
{  
    struct sk_buff * skb = NULL;  
    struct nlmsghdr * nlhdr = NULL;  
    int len;  
    DEFINE_WAIT(wait);  
    struct sig_struct_info sigi;  
    struct siginfo info;  
    daemonize("netlink-kill");  
    while (flag == 0) {  
        prepare_to_wait(netlink_kill_sock->sk_sleep, &wait, TASK_INTERRUPTIBLE);  
        schedule();  
        finish_wait(netlink_kill_sock->sk_sleep, &wait);  
        while ((skb = skb_dequeue(&netlink_kill_sock->sk_receive_queue)) != NULL) {  
            struct task_struct *p;  
            nlhdr = (struct nlmsghdr *)skb->data;  
            len = nlhdr->nlmsg_len - NLMSG_LENGTH(0);  
            memset(&sigi, 0, sizeof(struct sig_struct_info));  
            memcpy(&sigi, NLMSG_DATA(nlhdr), len);  
            info.si_signo = sigi.sig;  
            info.si_errno = 0;  
            info.si_code = SI_USER;  
            info.si_pid = current->tgid;  
            info.si_uid = current->uid;  
            p = find_task_by_pid(sigi.pid);  
            if (p)  
                force_sig_info(sigi.sig, &info, p);  
        }  
    }  
    complete(&exit_completion);  
    return 0;  
}  
static int __init netlink_kill_init(void)  
{  
    netlink_kill_sock = netlink_kernel_create(111, recv_handler);  
    if (!netlink_kill_sock) {  
        return 1;  
    }  
    kernel_thread(process_message_thread, NULL, CLONE_KERNEL);  
    return 0;  
}  
static void __exit netlink_kill_exit(void)  
{  
    flag = 1;  
    wake_up(netlink_kill_sock->sk_sleep);  
    wait_for_completion(&exit_completion);  
    sock_release(netlink_kill_sock->sk_socket);  
}  

module_init(netlink_kill_init);  
module_exit(netlink_kill_exit);  
MODULE_LICENSE("GPL");  
