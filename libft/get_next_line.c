/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 15:32:05 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/28 00:09:36 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		nl_free(char **line, t_buf *lst, int *is_sec)
{
	char	*tmp;

	if (*is_sec == 0)
	{
		*line = ft_strdup((const char*)lst->text);
		ft_bzero(lst->text, BUFF_SIZE + 1);
		*is_sec = 1;
		return (0);
	}
	else
	{
		tmp = *line;
		*line = ft_strjoin((const char*)tmp, (const char*)lst->text);
		ft_bzero(lst->text, BUFF_SIZE + 1);
		free(tmp);
		return (0);
	}
	return (0);
}

int		proc_buf(char **line, t_buf *lst, int *is_sec)
{
	char	*nl;
	char	*tmp;

	if (!lst)
		return (0);
	if (lst->text[0] == '\0')
		return (0);
	if ((nl = ft_strchr((const char*)lst->text, '\n')) == NULL)
		return (nl_free(line, lst, is_sec));
	*nl = '\0';
	if (*is_sec == 0)
	{
		*line = ft_strdup((const char*)lst->text);
		lst->text = ft_strcpy((char*)lst->text, (const char*)(nl + 1));
		return (1);
	}
	else
	{
		tmp = *line;
		*line = ft_strjoin((const char*)tmp, (const char*)lst->text);
		lst->text = ft_strcpy((char*)lst->text, (const char*)(nl + 1));
		free(tmp);
		return (1);
	}
	return (0);
}

t_buf	*ft_buf_new(void *content, const int fd, t_buf *head, t_buf **lst)
{
	t_buf	*new;
	t_buf	*tmp;

	if (head && lst)
	{
		tmp = head;
		while (tmp->next && tmp->next != *lst)
			tmp = tmp->next;
		tmp->next = (*lst)->next;
		free((*lst)->text);
		free(*lst);
		return (0);
	}
	if (content)
	{
		new = (t_buf *)malloc(sizeof(t_buf));
		new->text = (char *)malloc(BUFF_SIZE + 1);
		new->text = ft_memcpy((void *)new->text,
				(const void *)content, BUFF_SIZE + 1);
		new->fd = (int)fd;
		new->next = NULL;
		return (new);
	}
	return (0);
}

t_buf	*find_fd(t_buf **lst, const int fd)
{
	t_buf	*tmp;
	t_buf	*last;
	char	*tmp1;

	if (!(*lst))
	{
		tmp1 = ft_strnew(BUFF_SIZE);
		*lst = ft_buf_new(tmp1, fd, 0, 0);
		free(tmp1);
		return (*lst);
	}
	tmp = *lst;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		last = tmp;
		tmp = tmp->next;
	}
	tmp1 = ft_strnew(BUFF_SIZE);
	tmp = ft_buf_new(tmp1, fd, 0, 0);
	last->next = tmp;
	free(tmp1);
	return (tmp);
}

int		get_next_line(const int fd, char **line)
{
	static t_buf	*head;
	t_buf			*lst;
	int				is_sec;
	int				i;

	if (fd < 0)
		return (-1);
	i = 0;
	is_sec = 0;
	head = (!head) ? (find_fd(&head, fd)) : head;
	lst = find_fd(&head, fd);
	if (proc_buf(line, lst, &is_sec))
		return (1);
	while ((i = read(fd, lst->text, BUFF_SIZE)) > 0)
		if (proc_buf(line, lst, &is_sec))
			return (1);
	if (proc_buf(line, lst, &is_sec))
		return (1);
	if (i == -1)
		return (-1);
	if (is_sec != 0)
		return (1);
	ft_buf_new(0, 0, head, &lst);
	return (0);
}
