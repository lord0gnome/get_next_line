/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <guiricha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 14:48:40 by guiricha          #+#    #+#             */
/*   Updated: 2016/01/28 18:38:24 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int fd;
	char *line;
	int test;

	line = NULL;
	if (argc == 2)
	{
		if (!(fd = open(argv[1], O_RDONLY)))
			return (-1);
		while((test = get_next_line(fd, &line)) == 1)
		{
			if (line)
			{
				ft_putstr(line);
				ft_putchar('\n');
			}
		}
		if (line)
		{
			ft_putstr(line);
			ft_putchar('\n');
		}
	}
	else if (argc == 1)
	{
		fd = 1;
		while((test = get_next_line(fd, &line)))
		{
			ft_putnbr(test);
			if (line)
			{
				ft_putstr(line);
				ft_putchar('\n');
			}
		}
			ft_putnbr(test);
	}
	return (0);
}
