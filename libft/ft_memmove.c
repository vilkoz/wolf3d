/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 19:40:19 by vrybalko          #+#    #+#             */
/*   Updated: 2016/11/29 18:29:21 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s_s;
	unsigned char	*d_s;

	s_s = (unsigned char *)src;
	d_s = (unsigned char *)dst;
	if (s_s < d_s)
	{
		s_s += len - 1;
		d_s += len - 1;
		while (len-- > 0)
			*(d_s--) = *(s_s--);
		return (dst);
	}
	while (len-- > 0)
		*(d_s++) = *(s_s++);
	return (dst);
}
