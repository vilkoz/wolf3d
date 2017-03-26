/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:54:43 by vrybalko          #+#    #+#             */
/*   Updated: 2016/11/30 20:32:39 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dst2;
	unsigned char		*src2;
	unsigned char		s;
	size_t				i;

	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	s = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		dst2[i] = src2[i];
		if ((src2[i]) == s)
		{
			dst2[i] = src2[i];
			return (dst2 + i + 1);
		}
		i++;
	}
	return (0);
}
