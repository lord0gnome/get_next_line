/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <guiricha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:16:56 by guiricha          #+#    #+#             */
/*   Updated: 2016/01/25 17:02:26 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	read_buf(int const fd, t_stock *d)
{
	int retread;

	ft_bzero(d->buff, BUFF_SIZE + 1);
	d->inbuf = 0;
	d->sibuf = read(fd, d->buff, BUFF_SIZE);
		return (d->sibuf);
}

int	get_next_line(int const fd, char **line)
{
	static t_stock	*d;
	char *bck;

	if (!d)
	{
		if (!(*d = (t_stock*)malloc(sizeof(t_stock))))
			return (-1);
		if (!((*data)->buff = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (-1);
		if (!(readbuf(fd, d)))
	}
	if ()
	error_tests();
}
