/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nithramir <nithramir@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 12:00:23 by nithramir         #+#    #+#             */
/*   Updated: 2018/08/02 18:12:31 by nithramir        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
       #include <netinet/in.h>
#include <stdio.h>

int main(int argc, char **argv)
{
        printf("%d\n", IPPROTO_RAW);
        int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);  // IPPROTO_RAW == valid raw protocol?

}