/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 12:51:33 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/11 14:38:03 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** libft ??
*/

int					ft_isnumber(char *s)
{
	int size;

	size = 0;
	if (*s == '-')
		s++;
	while (ft_isdigit(*s))
	{
		s++;
		size++;
	}
	if (size > 0 && !*s)
		return (1);
	return (0);
}

int					move_token(t_token **token, t_token **anc)
{
	t_token *tok;

	if (!(tok = create_token((*anc)->line, EMPTY)))
		return (0);
	*token = *anc;
	*anc = tok;
	return (1);
}

static t_token		*get_direct_token(int line, char *s)
{
	if (*s == DIRECT_CHAR)
	{
		s++;
		if (ft_isnumber(s))
			return (add_token_integer(create_token(line, DIRECT), ft_atoi(s)));
		if (*s == LABEL_CHAR)
		{
			s++;
			if (compose_withthese_letters(s, LABEL_CHARS))
				return (add_token_string(create_token(line, DIRECT_LABEL_STR),
							s));
		}
	}
	ft_printf("Issue: Incorrect Syntax for a \"Direct\" %s\n", s);
	return (create_token(line, UNKNOWN));
}

static t_token		*get_token_param(char *s, int line_nb)
{
	t_token *token;

	if (ft_strchr(s, DIRECT_CHAR))
		token = get_direct_token(line_nb, s);
	else if (isregister(s))
		token = add_token_integer(create_token(line_nb, REGISTER),
				ft_atoi(&s[1]));
	else if (ft_isnumber(s))
		token = add_token_integer(create_token(line_nb, INDIRECT), ft_atoi(s));
	else if (isindirect_label(s))
		token = add_token_string(create_token(line_nb, INDIRECT_LABEL_STR),
				&s[1]);
	else
	{
		token = create_token(line_nb, UNKNOWN);
		ft_printf("Issue: Syntax Error %s\n", s);
	}
	return (token);
}

t_token				*get_token(t_champion *c, char *s, int end, int line_nb)
{
	t_token	*token;
	char	last_char;

	last_char = s[end];
	s[end] = '\0';
	if (!ft_strcmp(s, NAME_CMD_STRING))
		token = create_token(line_nb, NAME);
	else if (!ft_strcmp(s, COMMENT_CMD_STRING))
		token = create_token(line_nb, COMMENT);
	else if (islabel(s))
	{
		token = add_token_string(create_token(line_nb, LABEL), s);
		token->value.data[ft_strlen(s) - 1] = '\0';
		token->pos = c->number_instructions;
	}
	else if (isintruction(s))
		token = add_token_operation(create_token(line_nb, INSTRUCTION), s);
	else
		token = get_token_param(s, line_nb);
	s[end] = last_char;
	return (token);
}
