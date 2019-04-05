/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juriot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:25:50 by juriot            #+#    #+#             */
/*   Updated: 2018/12/11 17:25:51 by juriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

void	del_list(const int fd, t_data **hdlst)
{
	t_data	*list_to_free;
	t_data	*tmp_list;

	list_to_free = *hdlst;
	tmp_list = NULL;
	while (list_to_free)
	{
		if (list_to_free->fd != fd)
		{
			if (tmp_list)
				tmp_list->next = list_to_free->next;
			else
				*hdlst = list_to_free->next;
			ft_strdel(&list_to_free->content);
			free(list_to_free);
			break ;
		}
		tmp_list = list_to_free;
		list_to_free = list_to_free->next;
	}
}

t_data	*add_list(const int fd)
{
	t_data	*new;

	if (!(new = (t_data *)malloc(sizeof(t_data))))
		return (0);
	new->fd = fd;
	new->content = NULL;
	new->next = NULL;
	return (new);
}

t_data	*get_list(const int fd, t_data **hdlst)
{
	t_data	*current;
	t_data	*backup;

	current = *hdlst;
	backup = NULL;
	while (current)
	{
		backup = current;
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	current = add_list(fd);
	backup->next = current;
	return (current);
}

int		get_one_line(const int fd, char **line, t_data **hdlst)
{
	char	*newline;
	char	*tmp;
	t_data	*currentlst;

	currentlst = get_list(fd, hdlst);
	tmp = currentlst->content;
	if (!*currentlst->content)
	{
		del_list(fd, hdlst);
		return (0);
	}
	if ((newline = ft_strchr(tmp, '\n')))
		*newline = '\0';
	if (!(*line = ft_strdup(currentlst->content)))
		return (-1);
	if (newline)
	{
		if (!(currentlst->content = ft_strdup(newline + 1)))
			return (-1);
		ft_strdel(&tmp);
	}
	else
		ft_strdel(&currentlst->content);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_data	*hdlst;
	t_data			*currentlst;
	char			*buff;
	int				rd;

	if (fd < 0)
		return (-1);
	if (!hdlst && !(hdlst = add_list(fd)))
		return (-1);
	currentlst = get_list(fd, &hdlst);
	if (!(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	rd = 1;
	while (rd > 0 && (!currentlst->content ||
		(currentlst->content && !(ft_strchr(currentlst->content, '\n')))))
	{
		rd = read(fd, buff, BUFF_SIZE);
		currentlst->content = ft_strjoinf(&(currentlst->content), &buff, 1);
		ft_strclr(buff);
	}
	ft_strdel(&buff);
	return (rd == -1 ? -1 : get_one_line(fd, line, &hdlst));
}
