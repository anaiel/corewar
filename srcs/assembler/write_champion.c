/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:22:02 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/10 20:14:31 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int						write_header(t_header *header, int fd)
{
	char		buff[SIZEMAX_STRING + 4];
	int			tmp;

	tmp = convert_bigendian(header->magic, 4);
	write(fd, &tmp, 4);
	ft_putstr_fd(header->prog_name, fd);
	ft_bzero(buff, SIZEMAX_STRING + 4);
	tmp = PROG_NAME_LENGTH - ft_strlen(header->prog_name);
	write(fd, buff, tmp + 4);
	tmp = convert_bigendian(header->prog_size, 4);
	write(fd, &tmp, 4);
	ft_putstr_fd(header->comment, fd);
	tmp = COMMENT_LENGTH - ft_strlen(header->comment);
	write(fd, buff, tmp + 4);
	return (1);
}

unsigned char			opcode(t_token *token)
{
	unsigned char	res;
	int				i;
	int				decalage;
	int				tmp;

	i = -1;
	decalage = 6;
	res = 0;
	while (++i < token->value.operation->number_param)
	{
		tmp = token->param[i]->type;
		if (tmp == REGISTER)
			res += 1 << decalage;
		else if (tmp == DIRECT || tmp == DIRECT_LABEL)
			res += 2 << decalage;
		else if (tmp == INDIRECT || tmp == INDIRECT_LABEL)
			res += 3 << decalage;
		decalage -= 2;
	}
	return (res);
}

int						manage_prog(t_champion *champion)
{
	int i;
	int tok;

	i = 0;
	tok = -1;
	while (++tok < champion->number_token)
	{
		while (tok < champion->number_token &&
				champion->tokens[tok]->type != INSTRUCTION)
			tok++;
		if (tok < champion->number_token)
			i += convert_token_hexa(champion, i, champion->tokens[tok]);
	}
	return (i);
}

int						create_champion(t_fichier *file, t_champion *champion)
{
	int size;

	file->fd_out = open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC);
	champion->header->prog_size = champion->size;
	write_header(champion->header, file->fd_out);
	size = manage_prog(champion);
	write(file->fd_out, champion->prog, size);
	close(file->fd_out);
	return (1);
}
