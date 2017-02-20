/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:25:07 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/20 21:10:28 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		free_lst(t_lst *tmp)
{
	free(tmp->line);
	free(tmp);
	tmp = NULL;
}

char		**init_array(t_e *e, int size_y)
{
	char	**arr;
	t_lst	*tmp;
	t_lst	*fre;
	size_t	l_len;
	char	*pl;

	arr = (char **)malloc(sizeof(char *) * (size_y + 1));
	arr[size_y] = 0;
	tmp = e->lst;
	if ((fre = tmp) != NULL)
		l_len = ft_strlen(tmp->line);
	while (--size_y >= 0 && tmp)
	{
		if (size_y != tmp->y || ft_strlen(tmp->line) != l_len)
			return (NULL);
		arr[size_y] = tmp->line;
		if ((pl = ft_strchr(tmp->line, 'P')) != NULL && e->pl.pos.x == 1.5 &&
				e->pl.pos.x == 1.5)
			e->pl.pos = init_point((int)(pl - tmp->line), size_y);
		tmp = tmp->next;
		free(fre);
		fre = tmp;
	}
	e->lst = NULL;
	return (arr);
}

t_pl		init_player(t_pl pl)
{
	pl.pos.x = 1.5;
	pl.pos.y = 1.5;
	pl.dir.x = -1;
	pl.dir.y = 0;
	pl.plane.x = 0;
	pl.plane.y = 0.66;
	pl.ms = 0.3;
	pl.rs = 0.03;
	return (pl);
}

t_e			*count_size(t_e *e)
{
	int		i;

	i = -1;
	e->map_w = ft_strlen(e->map[0]);
	while (e->map[++i] != 0)
		;
	e->map_h = i;
	return (e);
}

t_e			*ft_mlx_init(t_lst *lst, int size_y, t_e *e)
{
	e = (t_e *)malloc(sizeof(t_e));
	e->mlx = mlx_init();
	e->height = 700;
	e->width = 800;
	e->win = mlx_new_window(e->mlx, e->width, e->height, "wolf3D");
	e->img = mlx_new_image(e->mlx, e->width, e->height);
	e->lst = lst;
	e->pl = init_player(e->pl);
	e->map = init_array(e, size_y);
	e->time = 0;
	if (e->map != NULL)
		e->map[(int)e->pl.pos.y][(int)e->pl.pos.x] = ' ';
	e = count_size(e);
	if ((e = ft_load_tex(e)) == NULL)
		return (0);
	return (e);
}
