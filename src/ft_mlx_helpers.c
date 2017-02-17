/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 17:12:33 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/18 01:04:38 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

void	ft_move(t_e *e)
{
	if (e->k.move_y == 1)
	{
		if (e->map[(int)e->pl.pos.y][(int)(e->pl.pos.x + e->pl.dir.y * e->pl.ms)] < '0')
			e->pl.pos.x += e->pl.dir.x * e->pl.ms;
		if (e->map[(int)(e->pl.pos.y + e->pl.dir.y * e->pl.ms)][(int)(e->pl.pos.x)] < '0')
			e->pl.pos.y += e->pl.dir.y * e->pl.ms;
	}
	if (e->k.move_y == -1)
	{
		if (e->map[(int)e->pl.pos.y][(int)(e->pl.pos.x - e->pl.dir.y * e->pl.ms)] < '0')
			e->pl.pos.x -= e->pl.dir.x * e->pl.ms;
		if (e->map[(int)(e->pl.pos.y - e->pl.dir.y * e->pl.ms)][(int)(e->pl.pos.x)] < '0')
			e->pl.pos.y -= e->pl.dir.y * e->pl.ms;
	}
	printf("pos = %f %f\n", e->pl.pos.x, e->pl.pos.y);
}

void	ft_rotate(t_e *e)
{
	double old_dir_x;
	double old_plane_x;

	if (e->k.rot == -1)
	{
		old_dir_x = e->pl.dir.x;
		e->pl.dir.x = e->pl.dir.x * cos(-e->pl.rs) - e->pl.dir.y * sin(-e->pl.rs);
		e->pl.dir.y = old_dir_x * sin(-e->pl.rs) + e->pl.dir.y * cos(-e->pl.rs);
		old_plane_x = e->pl.plane.x;
		e->pl.plane.x = e->pl.plane.x * cos(-e->pl.rs) - e->pl.plane.y * sin(-e->pl.rs);
		e->pl.plane.y = old_plane_x * sin(-e->pl.rs) + e->pl.plane.y * cos(-e->pl.rs);
	}
	else
	{
		old_dir_x = e->pl.dir.x;
		e->pl.dir.x = e->pl.dir.x * cos(e->pl.rs) - e->pl.dir.y * sin(e->pl.rs);
		e->pl.dir.y = old_dir_x * sin(e->pl.rs) + e->pl.dir.y * cos(e->pl.rs);
		old_plane_x = e->pl.plane.x;
		e->pl.plane.x = e->pl.plane.x * cos(e->pl.rs) - e->pl.plane.y * sin(e->pl.rs);
		e->pl.plane.y = old_plane_x * sin(e->pl.rs) + e->pl.plane.y * cos(e->pl.rs);

	}
}

void	keys_init(t_k *k)
{
	k->move_x = 0;
	k->move_y = 0;
	k->rot = 0;
}
