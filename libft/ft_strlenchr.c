/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 20:16:39 by vrybalko          #+#    #+#             */
/*   Updated: 2016/12/03 20:17:32 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strlenchr(char const *s, char c, int i)
{
	int		n;

	n = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		n++;
	}
	return (i);
}