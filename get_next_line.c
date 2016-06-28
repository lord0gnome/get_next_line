/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <guiricha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:16:56 by guiricha          #+#    #+#             */
/*   Updated: 2016/06/23 15:31:02 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

int	read_buf(int const fd, t_stock *d)
{
	if (fd < 0)
		return (-1);
	if (d->buff[fd])
		ft_bzero(d->buff[fd], BUFF_SIZE + 1);
	d->i[fd] = 0;
	d->s[fd] = read(fd, d->buff[fd], BUFF_SIZE);
	return (d->s[fd]);
}

int	handle_i(t_ints *v, t_stock *d, char **line, int const fd)
{
	char	*tmp;

	if (v->i)
	{
		tmp = *line;
		if (!(*line = (char *)malloc(sizeof(char) * (v->size + v->i + 1))))
			return (0);
		if (v->size)
			ft_memcpy(*line, tmp, v->size);
		ft_strncpy(*line + v->size, d->buff[fd] + d->i[fd], (size_t)v->i);
		(*line)[v->size + v->i] = 0;
		v->size += v->i;
		d->i[fd] += v->i;
		free(tmp);
	}
	if (!v->i && (d->buff[fd][d->i[fd]] == '\n'))
	{
		v->ret = 1;
		if (d->buff[fd][d->i[fd]] == '\n' && !(v->size))
			*line = ft_strdup("");
		d->i[fd]++;
	}
	return (v->ret);
}

int	gnl_do(int const fd, char **line, t_stock *d)
{
	t_ints	v;

	v.size = 0;
	v.ret = 42;
	while (v.ret == 42)
	{
		if (d->i[fd] >= d->s[fd])
			v.ret = read_buf(fd, d);
		if (v.ret == -1 || v.ret == 0)
		{
			if (v.ret == 0)
				v.ret = 1;
			return (v.ret);
		}
		v.ret = 42;
		v.i = 0;
		while (d->buff[fd][v.i + d->i[fd]] != '\n' && d->i[fd] + v.i < d->s[fd])
			v.i++;
		if (!(handle_i(&v, d, line, fd)))
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
		if (!((d)->buff = (char **)malloc(sizeof(char *) * 255)))
			return (-1);
	}
	if (d->i[fd] >= d->s[fd] || !d->s[fd])
	{
		if (!((d)->buff[fd] = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (-1);
		ret = read_buf(fd, d);
		if (ret == -1 || ret == 0)
			return (ret);
	}
	ret = gnl_do(fd, line, d);
	return (ret);
}
