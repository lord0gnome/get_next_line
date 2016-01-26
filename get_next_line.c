/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <guiricha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:16:56 by guiricha          #+#    #+#             */
/*   Updated: 2016/01/26 15:58:54 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int	read_buf(int const fd, t_stock *d)
{
	ft_bzero(d->buff, BUFF_SIZE + 1);
	d->ib = 0;
	if (fd < 0)
		return (-1);
	d->sb = read(fd, d->buff, BUFF_SIZE);
	return (d->sb);
}

int	gnl_do(int const fd, char **line, t_stock *d)
{
	char	*tmp;
	int		size;
	int		i;
	int		ret;

	tmp = *line;
	size = 0;
	ret = 1;
	while (42)
	{
		if (d->ib >= d->sb)
			ret = read_buf(fd, d);
		if (ret == -1 || ret == 0)
			return (ret);
		i = 0;
		while (d->buff[i + d->ib] && d->buff[i + d->ib] != '\n' && d->ib + i < d->sb)
			i++;
		if (i)
		{
			tmp = *line;
			if (!(*line = (char *)malloc(sizeof(char) * (size + i + 1))))
				return (-1);
			if (size)
				ft_strcpy(*line, tmp);
			ft_strncpy(*line + size, d->buff + d->ib, (size_t)i);
			size += i;
			d->ib += i;
		}
		if (!i)
		{
			if (d->buff[d->ib] == '\n' && d->ib < d->sb)
			{
				d->ib++;
				return (1);
			}
			else
			{
				d->ib++;
				return (0);
			}
		}
	}
	return (ret);
}

int	get_next_line(int const fd, char **line)
{
	static t_stock	*d;
	int				ret;

	ret = 1;
	if (!line)
		return (-1);
	*line = NULL;
	if (!d)
	{
		if (!(d = (t_stock*)malloc(sizeof(t_stock))))
			return (-1);
		if (!((d)->buff = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (-1);
		ret = read_buf(fd, d);
		if (ret == -1 || ret == 0)
			return (ret);
	}
	if (d->ib >= d->sb)
		ret = read_buf(fd, d);
	if(ret == -1 || ret == 0)
		return (ret);
	ret = gnl_do(fd, line, d);
	return (ret);
}
