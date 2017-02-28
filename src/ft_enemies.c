/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enemies.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 17:15:57 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/28 15:08:16 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		move_enemy(t_e *e, t_spr *s)
{
	t_p			delta;
	t_p			bak;
	void		*tmp;

	if (s->dist < 25)
	{
		delta.x = s->pos.x - e->pl.pos.x;
		delta.y = s->pos.y - e->pl.pos.y;
		bak = s->pos;
		s->pos.x -= delta.x * e->pl.ms / 10;
		s->pos.y -= delta.y * e->pl.ms / 10;
		if (s_map(e, (int)(s->pos.y), (int)(s->pos.x)) >= '0')
			s->pos = bak;
		if (s->spr_swp % 4 == 0)
		{
			tmp = s->img;
			s->img = s->img2;
			s->img2 = tmp;
			s->spr_swp = 0;
		}
		s->spr_swp++;
	}
}

void		deal_damage(t_e *e, t_spr *s)
{
	if (sqrt(s->dist) < 0.7)
		e->pl.hp -= 10;
}

void		ft_move_enemies(t_e *e)
{
	int		i;

	i = -1;
	while (++i < e->spr_num)
	{
		if (e->spr[i].c == 'z')
		{
			move_enemy(e, &(e->spr[i]));
			deal_damage(e, &(e->spr[i]));
		}
	}
}
