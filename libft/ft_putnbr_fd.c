/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:57:18 by vrybalko          #+#    #+#             */
/*   Updated: 2016/12/05 14:58:05 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnb1(long long num, int fd)
{
	if (num < 10)
		ft_putchar_fd(num + '0', fd);
	if (num >= 10)
	{
		ft_putnb1((num / 10), fd);
		ft_putchar_fd((num % 10) + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;

	num = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
	}
	ft_putnb1(num, fd);
}
