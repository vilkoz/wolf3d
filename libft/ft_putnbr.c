/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 14:28:05 by vrybalko          #+#    #+#             */
/*   Updated: 2016/12/01 18:23:37 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnb(long long num)
{
	if (num < 10)
		ft_putchar(num + '0');
	if (num >= 10)
	{
		ft_putnb((num / 10));
		ft_putchar((num % 10) + '0');
	}
}

void	ft_putnbr(int n)
{
	long long	num;

	num = n;
	if (n < 0)
	{
		ft_putchar('-');
		num *= -1;
	}
	ft_putnb(num);
}
