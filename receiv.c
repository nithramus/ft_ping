
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main(int argc, char **argv)
{
    // int sockfd;
    // char buff[60000];
    // struct sockaddr saddr;
    // int len = sizeof(struct sockaddr);
    // struct msghdr msg;

    // sockfd = socket(AF_INET, SOCK_RAW, htons(ETH_P_ALL));
    // if (sockfd < 0)
    // {
    //     printf("Error\n");
    //     perror("rze");
    //     return (0);
    // }
    // write(1, "test", 4);
    // int ret = recvfrom(sockfd, buff, 60000, 0, NULL, NULL);
    // printf("coucou%d\n", ret);
    // printf("%s\n", buff);
    int sock_r;
    printf("%d\n", IPPROTO_ICMP);
    sock_r = socket(AF_INET, SOCK_RAW, 1);
    if (sock_r < 0)
    {
        perror("error: ");
        printf("error in socket\n");
        return -1;
    }
    unsigned char *buffer = (unsigned char *)malloc(65536); //to receive data
    // memset(buffer, 0, 65536);
    struct sockaddr saddr;
    int saddr_len = sizeof(saddr);
    printf("beofre");
    //Receive a network packet and copy in to buffer
    fork();
    int buflen = recvfrom(sock_r, buffer, 65536, 0,(struct sockaddr *) &saddr, (socklen_t *)&saddr_len);
    if (buflen < 0)
    {
        printf("error in reading recvfrom function\n");
        return -1;
    }
    printf("buffer %s", buffer);
    struct ethhdr *eth = (struct ethhdr *)(buffer);
    printf("\nEthernet Header\n");
    printf("\t|-Source Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",eth->h_source[0],eth->h_source[1],eth->h_source[2],eth->h_source[3],eth->h_source[4],eth->h_source[5]);
    printf("\t|-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
    printf("\t|-Protocol : %d\n",eth->h_proto);
    struct ip *ips = (struct ip*)(buffer);
    // printf("%s\n", inet_ntoa(ips->daddr));

    struct sockaddr_in source;
    source.sin_addr = ips->ip_dst;
    printf("%s\n", inet_ntoa(source.sin_addr));
    source.sin_addr = ips->ip_src;
    printf("%s\n", inet_ntoa(source.sin_addr));
    printf("%hu\n", ips->ip_id);
    return (1);
}