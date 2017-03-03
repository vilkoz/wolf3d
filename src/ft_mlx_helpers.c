/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 17:12:33 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/03 18:37:35 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

char	s_map(t_e *e, int y, int x)
{
	if (x >= 0 && x < e->map_w && y >= 0 && y < e->map_h)
		return (e->map[y][x]);
	else
		return (127);
}

void	ft_open_door1(t_e *e)
{
	if (s_map(e, (int)(e->spr[e->spr_num - 1].pos.y + 1 - 0.5),
				(int)(e->spr[e->spr_num - 1].pos.x - 0.5)) >= '0' ||
			(s_map(e, (int)(e->spr[e->spr_num - 1].pos.y - 1 - 0.5),
				(int)(e->spr[e->spr_num - 1].pos.x - 0.5)) >= '0'))
	{
		e->spr[e->spr_num - 1].old_pos = e->spr[e->spr_num - 1].pos;
		e->map[(int)(e->spr[e->spr_num - 1].pos.y - 0.5)]
			[(int)(e->spr[e->spr_num - 1].pos.x - 0.5)] = ' ';
		e->spr[e->spr_num - 1].pos.y += 1;
	}
	else if (s_map(e, (int)(e->spr[e->spr_num - 1].pos.y - 0.5),
				(int)(e->spr[e->spr_num - 1].pos.x + 1 - 0.5)) >= '0' ||
			(s_map(e, (int)(e->spr[e->spr_num - 1].pos.y - 0.5),
				(int)(e->spr[e->spr_num - 1].pos.x - 1 - 0.5)) >= '0'))
	{
		e->spr[e->spr_num - 1].old_pos = e->spr[e->spr_num - 1].pos;
		e->map[(int)(e->spr[e->spr_num - 1].pos.y - 0.5)]
			[(int)(e->spr[e->spr_num - 1].pos.x - 0.5)] = ' ';
		e->spr[e->spr_num - 1].pos.x += 1;
	}
	e->spr[e->spr_num - 1].op = 1;
}

void	open_hidden_door(t_e *e)
{
	if (s_map(e, (int)(e->pl.pos.y + e->pl.dir.y),
				(int)(e->pl.pos.x + e->pl.dir.x)) == '7')
	{
		e->map[(int)(e->pl.pos.y + e->pl.dir.y)]
			[(int)(e->pl.pos.x + e->pl.dir.x)] = ' ';
		e->pl.points += 1337;
	}
	if (s_map(e, (int)(e->pl.pos.y + e->pl.dir.y),
				(int)(e->pl.pos.x + e->pl.dir.x)) == '8')
		e->k.menu = 2;
}

void	ft_open_door(t_e *e)
{
	open_hidden_door(e);
	if (s_map(e, (int)(e->pl.pos.y + e->pl.dir.y),
				(int)(e->pl.pos.x + e->pl.dir.x)) != 127 &&
			(e->spr[e->spr_num - 1].c == 'd' || e->spr[e->spr_num - 1].c == 'D')
			&& e->spr[e->spr_num - 1].op == 0
			&& e->spr[e->spr_num - 1].dist < 2)
	{
		ft_open_door1(e);
	}
	else if ((e->spr[e->spr_num - 1].c == 'd' ||
				e->spr[e->spr_num - 1].c == 'D') &&
			e->spr[e->spr_num - 1].op == 1 && e->spr[e->spr_num - 1].dist < 3)
	{
		e->spr[e->spr_num - 1].pos = e->spr[e->spr_num - 1].old_pos;
		e->map[(int)(e->spr[e->spr_num - 1].pos.y - 0.5)]
			[(int)(e->spr[e->spr_num - 1].pos.x - 0.5)] = 'd';
		e->spr[e->spr_num - 1].op = 0;
	}
}

void	keys_init(t_k *k)
{
	k->move_x = 0;
	k->move_y = 0;
	k->rot = 0;
	k->map = 0;
	k->tex = 0;
	k->menu = 0;
}
