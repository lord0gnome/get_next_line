/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <guiricha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 12:17:59 by guiricha          #+#    #+#             */
/*   Updated: 2016/01/22 20:50:07 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int		read_buf(int const fd, t_stock *data)
{
	ft_bzero(data->buff, BUFF_SIZE);
	if (-1 == (data->sibuf = read(fd, data->buff, BUFF_SIZE)))
		return (-1);
	data->inbuf = 0;
	data->buff[data->sibuf] = '\0';
	if (data->sibuf == 0)
		return (0);
	return (1);
}

int		make_data(int const fd, t_stock **data)
{
	int ret;

	if (!(*data = (t_stock*)malloc(sizeof(t_stock))))
		return (-1);
	if (!((*data)->buff = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	if (!(ret = read_buf(fd, *data)))
		return (0);
	return (ret);
}

int		bakreptest(t_ints *si, char *b, t_stock *d, char **line)
{
	int	i;

	i = 0;
	if ((si->i))
	{
		/*ft_putchar('\n');
		  ft_putchar('{');
		  ft_putstr(d->buff);
		  ft_putchar('}');
		  ft_putchar('[');
		  ft_putnbr(d->sibuf);
		  ft_putchar(']');
		  ft_putchar('\n');*/
		b = *line;
		if (!(*line = (char *)malloc(sizeof(char) * (si->size + si->i + 1))))
			return (-1);
		if (si->size)
			ft_strcpy(*line, b);
		ft_strncpy(*line + si->size, (d->buff) + (d->inbuf), (size_t)si->i);
		si->size += si->i;
		d->inbuf += si->i;
	}
	return (1);
}

int		error_tests(int const fd, char **line)
{
	if (fd < 0)
		return (-1);
	if (!line)
		return (-1);
	if ((read(fd, NULL, 0)) == -1)
		return (-1);
	return (1);
}

int		get_next_line(int const fd, char **line)
{
	t_ints			si;
	char			*b;
	static t_stock	*d;

	if (error_tests(fd, line) == -1)
		return (-1);
	if (!d)
		if (!make_data(fd, &d))
			return (-1);
	si.size = 0;
	*line = NULL;
	while (42)
	{
		if (d->inbuf >= d->sibuf)
			if (!read_buf(fd, d))
				return (0);
		si.i = 0;
		while (d->buff[si.i + d->inbuf] != '\n' && si.i + d->inbuf < d->sibuf)
			si.i++;
		b = *line;
		if (!(bakreptest(&si, b, d, line)))
			return (-1);
		if (d->inbuf >= d->sibuf)
			if (!read_buf(fd, d))
				return (0);
		if (d->buff[d->inbuf] == '\n' && (d->inbuf < d->sibuf && si.i == 0))
		{
			d->inbuf++;
			return (1);
		}
	}
	return (1);
}
