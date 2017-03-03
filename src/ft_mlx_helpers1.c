/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_helpers1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 18:35:33 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/03 18:56:57 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_print_map(t_e *e)
{
	int		i;
	int		j;
	t_pi	p;

	p = point_in(200, 0);
	i = -1;
	while (e->map[++i / 5] != 0)
	{
		j = -1;
		while (e->map[i / 5][++j / 5] != '\0')
		{
			if (e->map[i / 5][j / 5] >= '0')
				(e->map[i / 5][j / 5] == 'd') ? ft_img_px_put(e, j + 1 + p.x,
						i + 1 + p.y, 0xff5555) :
					ft_img_px_put(e, j + 1 + p.x, i + 1 + p.y, 0xffffff);
			else
				ft_img_px_put(e, j + 1 + p.x, i + 1 + p.y, 0x001100);
		}
	}
	ft_draw_line(e, point_in1((e->pl.pos.x * 5 + 1 + p.x),
				(e->pl.pos.y * 5 + 1 + p.y)), point_in1(e->pl.pos.x * 5 + 1 +
					p.x + e->pl.dir.x * 10 + 1, e->pl.pos.y * 5 +
				e->pl.dir.y * 10 + 1 + p.y), 0xee0000);
}

void	ft_move_x(t_e *e)
{
	if (e->k.move_x == 1)
	{
		if (s_map(e, (int)e->pl.pos.y, (int)(e->pl.pos.x +
						-e->pl.dir.y * (e->pl.ms + 0.4))) < '0')
			e->pl.pos.x += (-e->pl.dir.y) * e->pl.ms;
		if (s_map(e, (int)(e->pl.pos.y + e->pl.dir.x *
						(e->pl.ms + 0.4)), (int)(e->pl.pos.x)) < '0')
			e->pl.pos.y += e->pl.dir.x * e->pl.ms;
	}
	if (e->k.move_x == -1)
	{
		if (s_map(e, (int)e->pl.pos.y, (int)(e->pl.pos.x -
						-e->pl.dir.y * (e->pl.ms + 0.4))) < '0')
			e->pl.pos.x -= (-e->pl.dir.y) * e->pl.ms;
		if (s_map(e, (int)(e->pl.pos.y - e->pl.dir.x *
						(e->pl.ms + 0.4)), (int)(e->pl.pos.x)) < '0')
			e->pl.pos.y -= e->pl.dir.x * e->pl.ms;
	}
}

void	ft_move(t_e *e)
{
	e->bob_param.x = 1;
	if (e->k.move_y == 1)
	{
		if (s_map(e, (int)e->pl.pos.y, (int)(e->pl.pos.x +
					e->pl.dir.x * (e->pl.ms + 0.4))) < '0')
			e->pl.pos.x += e->pl.dir.x * e->pl.ms;
		if (s_map(e, (int)(e->pl.pos.y + e->pl.dir.y *
					(e->pl.ms + 0.4)), (int)(e->pl.pos.x)) < '0')
			e->pl.pos.y += e->pl.dir.y * e->pl.ms;
	}
	if (e->k.move_y == -1)
	{
		if (s_map(e, (int)e->pl.pos.y, (int)(e->pl.pos.x -
					e->pl.dir.x * (e->pl.ms + 0.4))) < '0')
			e->pl.pos.x -= e->pl.dir.x * e->pl.ms;
		if (s_map(e, (int)(e->pl.pos.y -
					e->pl.dir.y * (e->pl.ms + 0.4)), (int)(e->pl.pos.x)) < '0')
			e->pl.pos.y -= e->pl.dir.y * e->pl.ms;
	}
	ft_move_x(e);
}

void	ft_rotate_rev(t_e *e)
{
	double old_dir_x;
	double old_plane_x;

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
		ft_rotate_rev(e);
}
