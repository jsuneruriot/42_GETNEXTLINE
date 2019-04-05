/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juriot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:26:05 by juriot            #+#    #+#             */
/*   Updated: 2018/12/11 17:26:07 by juriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft/libft.h"

# define BUFF_SIZE 15

typedef	struct	s_data
{
	int				fd;
	char			*content;
	struct s_data	*next;
}				t_data;

int				get_next_line(const int fd, char **line);

#endif
