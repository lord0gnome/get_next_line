/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <guiricha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:16:56 by guiricha          #+#    #+#             */
/*   Updated: 2016/01/28 22:03:11 by guiricha         ###   ########.fr       */
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

int	handle_i(t_ints *v, t_stock *d, char **line)
{
	char	*tmp;

	if (v->i)
	{
		tmp = *line;
		if (!(*line = (char *)malloc(sizeof(char) * (v->size + v->i + 1))))
			return (0);
		if (v->size)
			ft_memcpy(*line, tmp, v->size);
		ft_strncpy(*line + v->size, d->buff + d->ib, (size_t)v->i);
		(*line)[v->size + v->i] = 0;
		v->size += v->i;
		d->ib += v->i;
		free(tmp);
	}
	if (!v->i && ((d->buff[d->ib] == '\n') || (d->ib < d->sb)))
	{
		v->ret = (d->buff[d->ib] == '\n' || d->ib < d->sb ? 1 : 0);
		if (d->buff[d->ib] == '\n' && !(v->size))
			*line = ft_strdup("");
		d->ib++;
	}
	return (1);
}

int	gnl_do(int const fd, char **line, t_stock *d)
{
	char	*tmp;
	t_ints	v;

	v.size = 0;
	v.ret = 42;
	tmp = NULL;
	while (v.ret == 42)
	{
		if (d->ib >= d->sb)
			v.ret = read_buf(fd, d);
		if (v.ret == -1 || v.ret == 0)
			return (v.ret);
		v.ret = 42;
		v.i = 0;
		while (d->buff[v.i + d->ib] != '\n' && d->ib + v.i < d->sb)
			v.i++;
		if (!(handle_i(&v, d, line)))
			return (-1);
	}
	return (v.ret);
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
	if (ret == -1 || ret == 0)
		return (ret);
	ret = gnl_do(fd, line, d);
	return (ret);
}
