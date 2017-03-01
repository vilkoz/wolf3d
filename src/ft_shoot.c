/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shoot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:19:31 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/01 17:30:59 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		check_shot(t_e *e, t_spr *s)
{
	double	ang1;
	double	ang2;

	ang1 = atan2(e->pl.dir.y, e->pl.dir.x) / RAD;
	ang2 = atan2(s->pos.y - e->pl.pos.y, s->pos.x - e->pl.pos.x) / RAD;
	if (fabs(ang2 - ang1) < 10)
		s->c = 'Z';
}

void		ft_play_gif(t_e *e, t_spr *s)
{
	if ((s->spr_swp += 1) >= 2 && s->spr_swp < GIF_NUM + 2)
	{
		s->img = e->z_death[s->spr_swp - 2].img;
		s->w = e->z_death[s->spr_swp - 2].w;
		s->h = e->z_death[s->spr_swp - 2].h;
	}
}

void		ft_shoot(t_e *e)
{
	int		i;

	i = -1;
	while (++i < e->spr_num)
	{
		if (e->spr[i].c == 'z')
			check_shot(e, &(e->spr[i]));
	}
}
