/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:58:57 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/24 20:38:53 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_p			calc_floor(t_ray ray, t_p map)
{
	t_p		floor;

	floor = init_point(0, 0);
	if ((ray.side == 0 || ray.side == 2) && ray.dir.x > 0)
	{
		floor.x = map.x;
		floor.y = map.y + ray.wall.x;
	}
	else if ((ray.side == 0 || ray.side == 2) && ray.dir.x < 0)
	{
		floor.x = map.x + 1.0;
		floor.y = map.y + ray.wall.x;
	}
	else if ((ray.side == 1 || ray.side == 3) && ray.dir.y > 0)
	{
		floor.x = map.x + ray.wall.x;
		floor.y = map.y;
	}
	else if ((ray.side == 1 || ray.side == 3) && ray.dir.y < 0)
	{
		floor.x = map.x + ray.wall.x;
		floor.y = map.y + 1.0;
	}
	return (floor);
}

void		tex_put_floor(t_e *e, t_ray ray, t_p map, int i)
{
	t_p		floor;
	t_p		cur_floor;
	t_pi	floor_tex;
	double	cur_d;
	int		y;
	double	weight;

	floor = calc_floor(ray, map);
	y = ray.d_end;
	while (++y < e->height)
	{
		cur_d = e->height / (2.0 * y - e->height);
		weight = cur_d / ray.wall_d;
		cur_floor.x = weight * floor.x + (1. - weight) * e->pl.pos.x;
		cur_floor.y = weight * floor.y + (1. - weight) * e->pl.pos.y;
		floor_tex.x = (int)(cur_floor.x * e->tex[2].w) % e->tex[2].w;
		floor_tex.y = (int)(cur_floor.y * e->tex[2].h) % e->tex[2].h;
		ft_img_px_put(e, i, y, add_shade_f(ft_img_px_get(e->tex[2].img,
						floor_tex, &e->tex[2]), y));
		ft_img_px_put(e, i, e->height - y, add_shade_f(ft_img_px_get(
						e->tex[3].img, floor_tex, &e->tex[3]), y));
	}
}

void		tex_put(t_e *e, t_ray ray, t_p map, int i)
{
	int		tex;
	int		y;
	int		d;
	int		color;

	if ((tex = s_map(e, (int)map.y, (int)map.x) - 48 - 1) >= TEX_NUM)
	{
		choose_color(e, ray, map, i);
		return ;
	}
	ray.wall.x = (ray.side == 0 || ray.side == 2) ? ray.pos.y + ray.wall_d *
		ray.dir.y : ray.pos.x + ray.wall_d * ray.dir.x;
	ray.wall.x -= floor(ray.wall.x);
	ray.tex.x = (int)(ray.wall.x * (double)e->tex[tex].w);
	y = ray.d_start - 1;
	while (++y < ray.d_end)
	{
		d = y * 256 - e->height * 128 + ray.l_height * 128;
		ray.tex.y = ((d * e->tex[tex].h) / ray.l_height) / 256;
		color = ft_img_px_get(e->tex[tex].img, ray.tex, &e->tex[tex]);
		ft_img_px_put(e, i, y, add_shade(e, ray, color));
	}
	tex_put_floor(e, ray, map, i);
}
