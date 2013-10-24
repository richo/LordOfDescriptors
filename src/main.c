#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <sys/select.h>


void usage(char *program_name) {
    printf("Usage: %s <upstream socket> <downstream socket>\n", program_name);
}

int bind_socket(char* path) {
    int sock, res, len;
    struct sockaddr_un local;
    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, path);
    len = sizeof(local.sun_path) + sizeof(local.sun_family);

    if (sock == -1) {
        return 0;
    }

    unlink(path);
    res = bind(sock, (struct sockaddr*)&local, len);
    listen(sock, 16);

    if (res == -1) {
        return 0;
    }
    return sock;
}

int main(int argc, char **argv) {
    fd_set fds, rfds, wfds;
    size_t n_fds, fds_handled;
    int i, client;
    int upstream, downstream;
    if (argc != 3) {
        usage(argv[0]);
        exit(1);
    }

    if ((upstream = bind_socket(argv[1])) == 0) {
        fprintf(stderr, "Couldn't bind to %s\n", argv[1]);
        exit(1);
    }
    if ((downstream = bind_socket(argv[2])) == 0) {
        fprintf(stderr, "Couldn't bind to %s\n", argv[2]);
        exit(1);
    }

    FD_ZERO(&fds);
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);

    FD_SET(downstream, &fds);
    while (1) {
        memcpy(&rfds, &fds, sizeof(fd_set));
        n_fds = select(FD_SETSIZE, &rfds, &wfds, NULL, NULL);
        for(i = 0; i < FD_SETSIZE; i++) {
            if (!FD_ISSET(i, &rfds) &&
                !FD_ISSET(i, &wfds))
                continue;

            if (i == downstream) {
                client = accept(downstream, NULL, NULL);
                FD_SET(client, &wfds);
            } else {
                send(i, "butts", sizeof("butts"), 0);
                close(i);
                FD_CLR(i, &fds);
            }
        }
    }
}
