/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nithramir <nithramir@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 01:09:38 by nithramir         #+#    #+#             */
/*   Updated: 2018/08/10 03:11:03 by nithramir        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
#define FT_PING_H
#include "libft/libft/libft.h"
#include "libft_chained_list/libft_chained_list_src/libft_chained_list.h"

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/signal.h>
#include <string.h>
#define LIST t_libft_chained_list

typedef struct  s_paramaters
{
    int        dest;
    int         verbose;
    int         help;
    int         send;
    int         received;
    LIST        *packets;
}               t_parameters;

int parse_options(int argc, char **argv, t_parameters *params);
int checksum(unsigned short *buf, int sz);
int ft_ping(t_parameters params);

#endif
