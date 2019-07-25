/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:48:23 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/11 15:53:10 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		is_end_word(char c)
{
	if (c == '"' || c == COMMENT_CHAR || c == SEPARATOR_CHAR || c == ';')
		return (1);
	return (0);
}

static int		end_word(char *s, int start)
{
	int i;

	i = 0;
	if (!s[start])
		return (start);
	while (s[start + i] &&
	!(is_end_word(s[start + i]) || ft_isspace(s[start + i]) ||
	(i > 0 && s[start + i] == DIRECT_CHAR)))
		i++;
	return (start + i);
}

static t_token	*analyse_element(t_champion *champion, char **line,
					t_fichier *file)
{
	t_token		*token;
	int			end;

	if (**line == SEPARATOR_CHAR)
	{
		*line += 1;
		token = create_token(file->line_nb, SEPARATOR);
	}
	else
	{
		end = end_word(*line, 0);
		token = get_token(champion, *line, end, file->line_nb);
		*line += end;
	}
	return (token);
}

static int		analyse_line(t_fichier *file, char *line, t_champion *champion)
{
	t_token	*token;

	while (*line && ft_isspace(*line))
		line++;
	while (*line && *line != COMMENT_CHAR && *line != ';')
	{
		if (*line == '"')
		{
			line++;
			token = analyse_string(&line, file);
		}
		else
			token = analyse_element(champion, &line, file);
		if (!token)
			return (0);
		add_token(token, champion);
		while (*line && ft_isspace(*line))
			line++;
	}
	return (1);
}

int				parsing(t_fichier *f, t_champion *champion)
{
	while (get_next_line(f->fd_in, &f->line) > 0)
	{
		if (!analyse_line(f, f->line, champion) ||
				(champion->size > CHAMP_MAX_SIZE))
		{
			get_next_line(STOP_GNL_FD, &f->file_name);
			if (champion->size > CHAMP_MAX_SIZE)
				ft_printf("Exceeding file size\n");
			ft_strdel(&f->line);
			return (0);
		}
		ft_strdel(&f->line);
		f->line_nb++;
	}
	get_next_line(STOP_GNL_FD, &f->file_name);
	ft_strdel(&f->line);
	return (1);
}
