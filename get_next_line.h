/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <guiricha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:17:00 by guiricha          #+#    #+#             */
/*   Updated: 2016/01/26 15:56:52 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#define BUFF_SIZE 3
int				get_next_line(int fd, char **line);

typedef struct	s_stock
{
	int			ib;
	int			sb;
	char		*buff;
}				t_stock;

#endif
