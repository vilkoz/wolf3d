/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 15:13:50 by vrybalko          #+#    #+#             */
/*   Updated: 2016/11/30 21:09:13 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
** len = len - 1; by default
*/

int			num_len(int n)
{
	int		len;

	len = 0;
	while (n /= 10)
		len++;
	return (len);
}

char		*ft_itoa(int n)
{
	int		len;
	char	*res;

	len = num_len(n);
	if (n < 0)
		len += 1;
	if ((res = (char *)malloc(sizeof(char) * len + 2)) == NULL)
		return (0);
	res[len + 1] = '\0';
	if (n < 0)
		res[0] = '-';
	if (n == 0)
		res[0] = '0';
	while (n)
	{
		if (n < 0)
			res[len--] = '0' - (n % 10);
		else
			res[len--] = n % 10 + '0';
		n = n / 10;
	}
	return (res);
}
