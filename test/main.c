#include <stdlib.h>
#include <sys/socket.h>

#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <errno.h>

int main (int argc, char *argv[])
{
    int    ret, len;
    int    pass_sd;
    char write_buf[1024];
    struct iovec   iov;
    struct msghdr  msg;

    int accepted;


    int sock;
    struct sockaddr_un downstream;
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    downstream.sun_family = AF_UNIX;
    strcpy(downstream.sun_path, argv[1]);
    len = sizeof(downstream.sun_path) + sizeof(downstream.sun_family);

    if (connect(sock, (struct sockaddr *)&downstream, len) == -1) {
        perror("connect");
        exit(1);
    }

    memset(&msg,   0, sizeof(msg));
    memset(&iov,    0, sizeof(iov));

    char fd_buf[CMSG_SPACE(sizeof(int))];
    msg.msg_iov     = &iov;
    msg.msg_iovlen  = 1;
    msg.msg_control    = fd_buf;
    msg.msg_controllen = sizeof(fd_buf);

    printf("Waiting on recvmsg\n");
    ret = recvmsg(sock, &msg, 0);
    if (ret < 0)
    {
        perror("recvmsg() failed");
        close(sock);
        exit(-1);
    }

    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    memcpy(&pass_sd, CMSG_DATA(cmsg), sizeof(int));
    printf("Received descriptor = %d\n", pass_sd);

    accepted = accept(pass_sd, NULL, NULL);
    printf("Waiting on data: ");
    recv(accepted, write_buf, 1024, 0);
    printf("%s", write_buf);
}
