/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 13:26:47 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/19 23:46:13 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** tex[2] is always floor
*/

void		ft_init_path(t_tex  *tex)
{
	tex[0].path = "res/tex/wall0.xpm";
	tex[1].path = "res/tex/wall1.xpm";
	tex[2].path = "res/tex/floor.xpm";
}

t_e			*ft_load_tex(t_e *e)
{
	t_tex		*tex;
	int			i;

	i = -1;
	tex = (t_tex *)malloc(sizeof(t_tex) * TEX_NUM);
	ft_init_path(tex);
	while (++i < TEX_NUM)
	{
		tex[i].img = mlx_xpm_file_to_image(e->mlx, tex[i].path, &tex[i].w, &tex[i].h);
		if (tex[i].img == NULL)
		{
			perror(tex[i].path);
			return (0);
		}
	}
	e->tex = tex;
	return (e);
}
