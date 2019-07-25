/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 22:33:54 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/11 15:12:00 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static int				ft_decal_finish(t_gnl *gnl, int i)
{
	int				j;

	if (i == -1)
	{
		ft_strdel(&gnl->str);
		return (0);
	}
	j = 0;
	while ((gnl->str)[i])
	{
		(gnl->str)[j] = (gnl->str)[i];
		i++;
		j++;
	}
	j--;
	while (++j < BUFF_SIZE + 1)
		(gnl->str)[j] = '\0';
	return (1);
}

static t_gnl			*ft_new_gnl(int fd, char **l, t_gnl *gnl, t_gnl *prec)
{
	int				len;

	while (gnl != 0x0 && gnl->fd != fd && (prec = gnl) != 0x0)
		gnl = gnl->next;
	len = (gnl && gnl->fd == fd) ? gnl->len : 1;
	if (!(*l = (char *)ft_memalloc(sizeof(char) * ((len * BUFF_SIZE) + 1))))
		return (0x0);
	if (gnl && gnl->fd == fd)
		return (gnl);
	if (!(gnl = (t_gnl *)malloc(sizeof(t_gnl))))
		return (0x0);
	gnl->fd = fd;
	gnl->len = 1;
	gnl->empty = 1;
	if (!(gnl->str = (char *)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (0x0);
	gnl->next = 0x0;
	gnl->prec = prec;
	if (prec)
		prec->next = gnl;
	return (gnl);
}

static int				ft_gnl_suite(char **l, t_gnl *gnl, int i, int j)
{
	int				vide;
	int				n;

	vide = (i == 0) ? -1 : 0;
	while (gnl->empty)
	{
		j = 0;
		if ((n = read(gnl->fd, gnl->str, BUFF_SIZE)))
			vide++;
		else
			gnl->empty = 0;
		gnl->str[n] = '\0';
		j = ft_strccpy(l, gnl, '\n', i);
		if (j == -1)
			return (-1);
		i += j;
		if (gnl->str[j] == '\n')
			return (ft_decal_finish(gnl, j + 1));
		if (j == n)
			ft_bzero(gnl->str, BUFF_SIZE);
	}
	if (gnl->empty == 0 && vide == -1)
		return (ft_decal_finish(gnl, -1));
	return (1);
}

static int				exit_gnl(t_gnl **gnl, int fd)
{
	if (fd == STOP_GNL_FD && gnl)
		ft_strdel(&((*gnl)->str));
	ft_memdel((void**)gnl);
	return (0);
}

int						get_next_line(const int fd, char **l)
{
	static t_gnl	*gnl = 0x0;
	int				i;

	if (fd > 1000000000)
		return (exit_gnl(&gnl, fd));
	i = -1;
	if (l == 0x0 || fd < 0 || read(fd, 0x0, 0))
		return (-1);
	if (gnl != 0x0)
		while (gnl->prec)
			gnl = gnl->prec;
	gnl = ft_new_gnl(fd, l, gnl, 0x0);
	if (!gnl->str)
		return (0);
	while (gnl->str[++i] && gnl->str[i] != '\n')
		(*l)[i] = gnl->str[i];
	(*l)[i] = '\0';
	if (gnl->empty == 0 && i == 0)
		return (ft_decal_finish(gnl, -1));
	if (gnl->str[i] == '\n' || (gnl->empty == 0 && gnl->str[i] == '\0'))
		return (ft_decal_finish(gnl, i + 1));
	return (ft_gnl_suite(l, gnl, i, 0));
}
