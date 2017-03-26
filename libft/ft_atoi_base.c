/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 15:44:07 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/23 19:39:48 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inbase(char c, int base, char ba)
{
	if (base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= ba && c <= (ba + base - 10)));
}

static	int	check_case(char *str, int base)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'A' + base)
			return (1);
		if (str[i] >= 'a' && str[i] <= 'a' + base)
			return (0);
	}
	return (1);
}

int			ft_atoi_base(char *str, int base)
{
	int		value;
	int		sign;
	char	ba;

	value = 0;
	if (base < 2 || base > 16 || str == NULL)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
			|| *str == '\r' || *str == '\v')
		str++;
	sign = (*str == '-') ? -1 : 1;
	ba = check_case(str, base) ? 'A' : 'a';
	if (*str == '-' || *str == '+')
		str++;
	while (ft_inbase(*str, base, ba))
	{
		if (*str - ba >= 0)
			value = value * base + (*str - ba + 10);
		else
			value = value * base + (*str - '0');
		str++;
	}
	return (value * sign);
}
