/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nithramir <nithramir@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 12:00:23 by nithramir         #+#    #+#             */
/*   Updated: 2018/08/06 03:24:50 by nithramir        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
       #include <netinet/in.h>
#include <stdio.h>
#include <netinet/ip.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// #include <linux/ip.h>


unsigned short csum(unsigned short *ptr,int nbytes) 
{
    register long sum;
    unsigned short oddbyte;
    register short answer;
    sum=0;
    while(nbytes>1) {
        sum+=*ptr++;
        nbytes-=2;
    }
    if(nbytes==1) {
        oddbyte=0;
        *((unsigned char*)&oddbyte)=*(unsigned char*)ptr;
        sum+=oddbyte;
    }
    sum = (sum>>16)+(sum & 0xffff);
    sum = sum + (sum>>16);
    answer=(short)~sum;
    return(answer);
}

int main(int argc, char **argv)
{
        char buff[5000];
        struct sockaddr_in sin;
        int len = sizeof(struct sockaddr);
        int             on = 1;

        printf("%d\n", IPPROTO_RAW);
        int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);  // IPPROTO_RAW == valid raw protocol?
        if (sock < 0)
        {
                perror("error: ");
                return 1;
        }
        sin.sin_family = AF_INET;
        sin.sin_port = htons(3000);
        sin.sin_addr.s_addr = inet_addr("127.0.0.1");
        printf("%d %d", IPPROTO_IP, IP_HDRINCL);
        if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
        {
                perror("wtf: ");
                return -1;
        }
        struct ip *ip_header = (struct ip*) buff;
        // memset(ip_header, 0, );
        ip_header->ip_v = 4;
        ip_header->ip_hl = 5;
        ip_header->ip_tos = 0;
        ip_header->ip_len = 5000;
        ip_header->ip_id = 25;
        ip_header->ip_off = 0;
        ip_header->ip_ttl = 255;
        ip_header->ip_p = 1; //ICMP
        ip_header->ip_sum = 0;
        int test = inet_addr("127.0.0.1");
        memcpy(&ip_header->ip_src, &test, 4);
        memcpy(&ip_header->ip_dst, &test, 4);


        if (sendto(sock, buff, 5000, 0, (const struct sockaddr*)&sin, len) < 0)
        {
                perror("yolo: ");
                return 1;
        }
        return (0);

}