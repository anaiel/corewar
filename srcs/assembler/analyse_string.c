/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:38:22 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/11 14:37:58 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*join_norme(char *s, char *line, int line_nb, int option)
{
	char *res;

	if (ft_strlen(s) + ft_strlen(line) < COMMENT_LENGTH + PROG_NAME_LENGTH)
	{
		res = (option) ? ft_strcjoin(s, line, '\n') : ft_strjoin(s, line);
		free(s);
		return (res);
	}
	else
	{
		ft_printf("fatal error: String is too big or does not end: %d\n",
				line_nb);
		return (0x0);
	}
}

static char		*string_exeption(t_fichier *file, char *line)
{
	int		line_nb;
	char	*s;
	char	*tmp;
	int		last;

	last = 0;
	s = ft_strnew(1);
	line_nb = file->line_nb;
	while (!(tmp = ft_strchr(line, '"')) && file->line)
	{
		if (!(s = join_norme(s, line, line_nb, last++)))
			return (0x0);
		ft_strdel(&file->line);
		if (get_next_line(file->fd_in, &file->line) < 1)
			return (0x0);
		line = file->line;
		file->line_nb++;
	}
	*tmp = '\0';
	if (!(s = join_norme(s, line, line_nb, last)))
		return (0x0);
	*tmp = '"';
	return (s);
}

t_token			*analyse_string(char **line, t_fichier *file)
{
	int		end;
	char	*tmp;
	int		actual;
	t_token *token;

	actual = file->line_nb;
	token = create_token(actual, STRING);
	if (!(tmp = string_exeption(file, *line)))
		return (0x0);
	token = add_token_string(token, tmp);
	ft_strdel(&tmp);
	*line = (actual < file->line_nb) ? file->line : *line;
	end = ft_strchr(*line, '"') - *line + 1;
	*line += end;
	return (token);
}
