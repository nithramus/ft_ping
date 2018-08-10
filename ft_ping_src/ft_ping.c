/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nithramir <nithramir@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 01:19:04 by nithramir         #+#    #+#             */
/*   Updated: 2018/08/10 03:12:42 by nithramir        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

extern t_parameters params;

// struct icmp {};

int create_socket()
{
    int sock;
    
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0)
    {
            perror("error: ");
            return (-1);
    }
    return (sock);
}

int icmp_header(struct icmp *header)
{
    memset(header, 0, 150);
    header->icmp_type = ICMP_ECHO;
    header->icmp_cksum = checksum((unsigned short *)header, 150);
    return (1);
}

int send_message(int sock, char buff[150])
{
    int c;
    struct sockaddr_in dest;

    dest.sin_family = AF_INET;
    dest.sin_port = htons(3000);
    dest.sin_addr.s_addr = inet_addr("127.0.0.1");
    c = sendto(sock, buff, 150, 0, (struct sockaddr*)&dest, sizeof(dest));
    if (c < 0)
    {
        perror("sendto: ");
        return (-1);
    }
    if (c < 150)
    {
        ft_putendl("incomplete write");
        return -1;
    }
    return (1);
}

int receivemsg(int sock)
{
    int c;
    char buff[150];
    struct sockaddr_in from;
    socklen_t size;

    c = recvfrom(sock, buff, 150, 0, (struct sockaddr*)&from, &size);
    if (c < 0)
    {
        perror("recvfrom");
        return (-1);
    }
    ft_putendl("yepi !");
          struct iphdr *ips = (struct iphdr *) buff;
             struct sockaddr_in source;

      source.sin_addr.s_addr = ips->saddr;
        printf("%s\n", inet_ntoa(source.sin_addr));
        printf("%hhu\n", ips->ttl);
    return (1);
}

int ft_ping(t_parameters params)
{
    int sock;
    int pid;
    char buff[150];

    sock = create_socket();
    if (sock < 0)
        return (-1);
    if (icmp_header((struct icmp *)buff) < 0)
        return (-1);
    if (send_message(sock, buff) < 0)
        return (-1);
    if (receivemsg(sock) < 0)
        return (-1);
    return (1);
}