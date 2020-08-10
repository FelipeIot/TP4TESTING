       
       
#include <sys/types.h>
#include <sys/socket.h>
       
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,struct sockaddr *src_addr, socklen_t *addrlen);