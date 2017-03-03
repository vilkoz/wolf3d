/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:24:47 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/03 14:36:44 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_p			init_point(double x, double y)
{
	t_p		p;

	p.x = x;
	p.y = y;
	return (p);
}

t_lst	*lst_new(int y, char *line)
{
	t_lst		*lst;
	char		*new_l;

	lst = (t_lst *)malloc(sizeof(t_lst));
	new_l = ft_strdup((const char *)line);
	lst->line = new_l;
	ft_strdel(&line);
	lst->y = y;
	return (lst);
}

t_lst	*lst_add(t_lst *old, t_lst *new)
{
	if (new != NULL)
		new->next = old;
	return (new);
}

t_e		*ft_read_map(char *s)
{
	t_e		*e;
	t_lst	*lst;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	e = NULL;
	lst = NULL;
	if ((fd = open((const char *)s, O_RDONLY)) < 0)
	{
		perror((const char *)s);
		return (0);
	}
	while (get_next_line(fd, &line) > 0)
	{
		lst = lst_add(lst, lst_new(i, line));
		i++;
	}
	e = ft_mlx_init(lst, i--, e, s);
	return (e);
}
