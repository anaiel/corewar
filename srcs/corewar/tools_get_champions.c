/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_get_champions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 12:20:12 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/21 11:27:04 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Reads the first 8 bytes of the champion file and returns them as an unsigned
** int
*/

unsigned int	get_magic(int fd)
{
	unsigned int	magic;
	unsigned char	c;
	int				i;

	magic = 0;
	i = -1;
	while (++i < 4)
	{
		if (read(fd, &c, 1) != 1)
			return ((COREWAR_EXEC_MAGIC == 0) ? 1 : 0);
		magic = magic * 256 + c;
	}
	return (magic);
}

/*
** Reads the PROG_NAME_LENGTH next characters of the binary and stores them in
** the champ structure
*/

int				get_prog_name(t_champ *champ, int fd)
{
	int		rval;

	if ((rval = read(fd, champ->head.prog_name, PROG_NAME_LENGTH))
			!= PROG_NAME_LENGTH)
		return (-1);
	champ->head.prog_name[rval] = 0;
	return (0);
}

/*
** Reads and returns the prog length in the binary
*/

unsigned int	get_prog_size(int fd)
{
	unsigned int	prog_size;
	int				rval;
	unsigned char	buf[5];
	int				i;

	if ((rval = read(fd, buf, 4)) != 4)
		return (CHAMP_MAX_SIZE + 1);
	buf[rval] = 0;
	prog_size = 0;
	i = -1;
	while (++i < 4)
		prog_size = prog_size * 16 * 16 + buf[i];
	return (prog_size);
}

/*
** Reads the comment in the binary and stores them in the champ structure
*/

int				get_comment(t_champ *champ, int fd)
{
	int		rval;

	if ((rval = read(fd, champ->head.comment, COMMENT_LENGTH))
			!= COMMENT_LENGTH)
		return (-1);
	champ->head.comment[COMMENT_LENGTH] = 0;
	return (0);
}

/*
** Reads and returns the instructions of the champion. Returns NULL if the
** size doesn't correspond to the given size or if the end of the file has
** not been reached.
*/

unsigned char	*get_redcode(int fd, unsigned int size)
{
	unsigned char	*instr;
	int				rval;
	unsigned char	buf;

	if (!(instr = (unsigned char *)malloc(sizeof(unsigned char)
			* (size + 1))))
		return (NULL);
	if ((rval = read(fd, instr, size)) != (int)size)
	{
		free(instr);
		return (NULL);
	}
	instr[rval] = 0;
	if ((rval = read(fd, &buf, 1)) != 0)
	{
		free(instr);
		return (NULL);
	}
	return (instr);
}
