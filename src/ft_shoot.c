/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shoot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:19:31 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/02 00:28:15 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw_gun(t_e *e, t_gif g, t_pi shift)
{
	int		i;
	int		j;
	int		color;

	i = shift.y - 1;
	while (++i < g.h + shift.y)
	{
		j = shift.x - 1;
		while (++j < g.w + shift.x)
		{
			color = ft_img_px_get_gif(g.img,
					point_in(j - shift.x, i - shift.y), g);
			if (color != 0)
				ft_img_px_put(e, j, i, color);
		}
	}
}

void		put_gun(t_e *e)
{
	if (e->is_shot > 0 && e->is_shot < GIF_GUN_NUM)
	{
		draw_gun(e, e->gun_gif[e->is_shot],
				point_in(e->width / 2 - e->gun_gif[e->is_shot].w / 2,
					e->height - e->gun_gif[e->is_shot].h));
		e->is_shot += 1;
	}
	else
	{
		e->is_shot = 0;
		draw_gun(e, e->gun_gif[e->is_shot],
				point_in(e->width / 2 - e->gun_gif[e->is_shot].w / 2,
					e->height - e->gun_gif[e->is_shot].h));
	}
}

void		check_shot(t_e *e, t_spr *s)
{
	double	ang1;
	double	ang2;

	ang1 = atan2(e->pl.dir.y, e->pl.dir.x) / RAD;
	ang2 = atan2(s->pos.y - e->pl.pos.y, s->pos.x - e->pl.pos.x) / RAD;
	if (fabs(ang2 - ang1) < 10 / s->dist)
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
	e->is_shot = 1;
	while (++i < e->spr_num)
	{
		if (e->spr[i].c == 'z')
			check_shot(e, &(e->spr[i]));
	}
}
