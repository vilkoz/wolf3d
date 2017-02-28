/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 23:26:35 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/28 15:56:59 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		ft_putstry(t_e *e, char *str)
{
	e->txt_shift += 15;
	mlx_string_put(e->mlx, e->win, 15, e->txt_shift, 0xffffff, str);
	free(str);
}

/*
** ft_realloc_str
*/

char		*ft_rs(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

void		ft_put_info(t_e *e)
{
	ft_putstry(e, ft_rs(ft_strdup("FPS: "), ft_itoa(e->fps)));
	ft_putstry(e, ft_rs(ft_strdup("HP: "), ft_itoa(e->pl.hp)));
	e->txt_shift = 0;
}
