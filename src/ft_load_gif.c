/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_gif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:08:57 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/01 17:26:41 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		init_path_death(t_gif **g)
{
	g[0]->path = "res/tex/death0.xpm";
	g[1]->path = "res/tex/death1.xpm";
	g[2]->path = "res/tex/death2.xpm";
	g[3]->path = "res/tex/death3.xpm";
	g[4]->path = "res/tex/death4.xpm";
	g[5]->path = "res/tex/death5.xpm";
	g[6]->path = "res/tex/death6.xpm";
}

void		read_xpm(t_e *e, t_gif **g)
{
	int		i;

	i = -1;
	while (++i < GIF_NUM)
	{
		g[i]->img = mlx_xpm_file_to_image(e->mlx, g[i]->path, &g[i]->w,
				&g[i]->h);
		if (g[i]->img == NULL)
		{
			perror(g[i]->path);
			exit(1);
		}
	}
}

void		ft_load_gif(t_e *e)
{
	e->z_death = (t_gif *)malloc(sizeof(t_gif) * GIF_NUM);
	init_path_death(&e->z_death);
	read_xpm(e, &e->z_death);
}
