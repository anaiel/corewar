/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 22:07:14 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/11 15:13:31 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "libft.h"

# define STOP_GNL_FD 1000000002
# define NO_MORE_REACHABLE 1000000001

int					get_next_line(const int fd, char **l);

typedef struct		s_gnl
{
	char			*str;
	int				fd;
	int				len;
	int				empty;
	struct s_gnl	*next;
	struct s_gnl	*prec;
}					t_gnl;

int					get_next_line(const int fd, char **line);
int					ft_strccpy(char **l, t_gnl *gnl, char c, int k);

#endif
