/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_gif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:08:57 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/01 23:53:00 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		init_path_death(t_gif **g)
{
	(*g)[0].path = "res/tex/death0.xpm";
	(*g)[1].path = "res/tex/death1.xpm";
	(*g)[2].path = "res/tex/death2.xpm";
	(*g)[3].path = "res/tex/death3.xpm";
	(*g)[4].path = "res/tex/death4.xpm";
	(*g)[5].path = "res/tex/death5.xpm";
	(*g)[6].path = "res/tex/death6.xpm";
}

void		init_path_gun(t_gif **g)
{
	(*g)[0].path = "res/tex/gun0.xpm";
	(*g)[1].path = "res/tex/gun1.xpm";
	(*g)[2].path = "res/tex/gun2.xpm";
	(*g)[3].path = "res/tex/gun3.xpm";
	(*g)[4].path = "res/tex/gun4.xpm";
}

t_gif		*read_xpm(t_e *e, t_gif *g, int num)
{
	int		i;

	i = -1;
	while (++i < num)
	{
		g[i].img = mlx_xpm_file_to_image(e->mlx, g[i].path, &g[i].w,
				&g[i].h);
		if (g[i].img == NULL)
		{
			perror(g[i].path);
			exit(1);
		}
	}
	return (g);
}

void		ft_load_gif(t_e *e)
{
	t_gif	*g;
	t_gif	*g1;

	g = (t_gif *)malloc(sizeof(t_gif) * GIF_NUM);
	g1 = (t_gif *)malloc(sizeof(t_gif) * GIF_GUN_NUM);
	init_path_death(&g);
	init_path_gun(&g1);
	e->z_death = read_xpm(e, g, GIF_NUM);
	e->gun_gif = read_xpm(e, g1, GIF_GUN_NUM);
	e->gun = mlx_new_image(e->mlx, e->gun_gif[0].w, e->gun_gif[0].h);
}
