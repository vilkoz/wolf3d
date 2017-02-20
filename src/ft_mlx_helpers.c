/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 17:12:33 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/20 19:59:12 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_print_map(t_e *e)
{
	int		i;
	int		j;

	i = -1;
	while (e->map[++i / 5] != 0)
	{
		j = -1;
		while (e->map[i / 5][++j / 5] != '\0')
		{
			if (e->map[i / 5][j / 5] >= '0')
				ft_img_px_put(e, j + 1, i + 1, 0xffffff);
			else
				ft_img_px_put(e, j + 1, i + 1, 0x001100);
		}
	}
	ft_img_px_put(e, (int)(e->pl.pos.x * 5) + 1, ((int)e->pl.pos.y * 5) + 1,
			0xFF0000);
	ft_draw_line(e, point_in(e->pl.pos.x * 5 + 1, e->pl.pos.y * 5 + 1),
			point_in(e->pl.pos.x * 5 + 1 + e->pl.dir.x * 2 + 1, e->pl.pos.y
			* 5 + e->pl.dir.y * 2 + 1), 0xee0000);
}

char	s_map(t_e *e, int y, int x)
{
	if (x >= 0 && x < e->map_w && y >= 0 && y < e->map_h)
		return (e->map[y][x]);
	else
		return (127);
}

void	ft_move_x(t_e *e)
{
	if (e->k.move_x == 1)
	{
	//	if (s_map(e, (int)e->pl.pos.y, (int)(e->pl.pos.x +
	//				e->pl.dir.y * e->pl.ms)) < '0')
			e->pl.pos.x += (-e->pl.dir.y) * e->pl.ms;
	//	if (s_map(e, (int)(e->pl.pos.y + e->pl.dir.x *
	//				e->pl.ms), (int)(e->pl.pos.x)) < '0')
			e->pl.pos.y += e->pl.dir.x * e->pl.ms;
	}
	if (e->k.move_x == -1)
	{
	//	if (s_map(e, (int)e->pl.pos.y, (int)(e->pl.pos.x -
	//				e->pl.dir.y * e->pl.ms)) < '0')
			e->pl.pos.x -= (-e->pl.dir.y) * e->pl.ms;
	//	if (s_map(e, (int)(e->pl.pos.x -
	//				e->pl.dir.y * e->pl.ms), (int)(e->pl.pos.x)) < '0')
			e->pl.pos.y -= e->pl.dir.x * e->pl.ms;
	}
}

void	ft_move(t_e *e)
{
	if (e->k.move_y == 1)
	{
		if (s_map(e, (int)e->pl.pos.y, (int)(e->pl.pos.x +
					e->pl.dir.x * (e->pl.ms + 0.3))) < '0')
			e->pl.pos.x += e->pl.dir.x * e->pl.ms;
		if (s_map(e, (int)(e->pl.pos.y + e->pl.dir.y *
					(e->pl.ms + 0.3)), (int)(e->pl.pos.x)) < '0')
			e->pl.pos.y += e->pl.dir.y * e->pl.ms;
	}
	if (e->k.move_y == -1)
	{
		if (s_map(e, (int)e->pl.pos.y, (int)(e->pl.pos.x -
					e->pl.dir.x * e->pl.ms)) < '0')
			e->pl.pos.x -= e->pl.dir.x * e->pl.ms;
		if (s_map(e, (int)(e->pl.pos.y -
					e->pl.dir.y * e->pl.ms), (int)(e->pl.pos.x)) < '0')
			e->pl.pos.y -= e->pl.dir.y * e->pl.ms;
	}
	ft_move_x(e);
}

void	ft_rotate(t_e *e)
{
	double old_dir_x;
	double old_plane_x;

	if (e->k.rot == -1)
	{
		old_dir_x = e->pl.dir.x;
		e->pl.dir.x = e->pl.dir.x * cos(-e->pl.rs) -
			e->pl.dir.y * sin(-e->pl.rs);
		e->pl.dir.y = old_dir_x * sin(-e->pl.rs) +
			e->pl.dir.y * cos(-e->pl.rs);
		old_plane_x = e->pl.plane.x;
		e->pl.plane.x = e->pl.plane.x * cos(-e->pl.rs) -
			e->pl.plane.y * sin(-e->pl.rs);
		e->pl.plane.y = old_plane_x * sin(-e->pl.rs) +
			e->pl.plane.y * cos(-e->pl.rs);
	}
	else
	{
		old_dir_x = e->pl.dir.x;
		e->pl.dir.x = e->pl.dir.x * cos(e->pl.rs) -
			e->pl.dir.y * sin(e->pl.rs);
		e->pl.dir.y = old_dir_x * sin(e->pl.rs) +
			e->pl.dir.y * cos(e->pl.rs);
		old_plane_x = e->pl.plane.x;
		e->pl.plane.x = e->pl.plane.x * cos(e->pl.rs) -
			e->pl.plane.y * sin(e->pl.rs);
		e->pl.plane.y = old_plane_x * sin(e->pl.rs) +
			e->pl.plane.y * cos(e->pl.rs);
	}
}

void	keys_init(t_k *k)
{
	k->move_x = 0;
	k->move_y = 0;
	k->rot = 0;
	k->map = 0;
}
