/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:55:26 by vrybalko          #+#    #+#             */
/*   Updated: 2016/11/27 17:14:23 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	check_min(char *str)
{
	if (*str == '-')
		return (-1);
	return (1);
}

static	int	check_plus(char *str)
{
	if (*str == '+')
		return (1);
	return (0);
}

int			ft_atoi(const char *s)
{
	int		res;
	int		is_neg;
	int		is_plus;
	char	*str;

	res = 0;
	str = (char *)s;
	is_neg = 1;
	is_plus = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32 || *str == '-' || *str == 43)
	{
		if (is_neg == -1 || is_plus == 1)
			return (0);
		is_neg = check_min(str);
		is_plus = check_plus(str);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * is_neg);
}
