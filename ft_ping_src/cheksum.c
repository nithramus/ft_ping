/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheksum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nithramir <nithramir@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 02:29:44 by nithramir         #+#    #+#             */
/*   Updated: 2018/08/10 03:07:03 by nithramir        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int checksum(unsigned short *buf, int sz)
{
  int nleft = sz;
  int sum = 0;
  unsigned short *w = buf;
  unsigned short ans = 0;
   
  while (nleft > 1) {
    sum += *w++;
    nleft -= 2;
  }
   
  if (nleft == 1) {
    *(unsigned char *) (&ans) = *(unsigned char *) w;
    sum += ans;
  }
   
  sum = (sum >> 16) + (sum & 0xFFFF);
  sum += (sum >> 16);
  ans = (short)~sum;
  return (ans);
}