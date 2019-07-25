/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:04:55 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/11 15:56:32 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		error_name_comment(t_champion *c, t_token *t, t_token *next, int nb_tok)
{
	int error;

	error = 0;
	if (nb_tok == 1 || !next || next->type != STRING)
		error += error_champion(c, "STRING not found", t->line);
	else if (!next->value.data ||
		(t->type == NAME && ft_strlen(next->value.data) > PROG_NAME_LENGTH) ||
		(t->type == COMMENT && ft_strlen(next->value.data) > COMMENT_LENGTH))
	{
		error += error_champion(c, "Name or comment doesn't have a good format",
		t->line);
	}
	else if (!ft_strlen(next->value.data))
		warning_champion(c, "Empty string", t->line);
	else if (nb_tok > 2 && !error)
		error += error_champion(c, "Too many elements on this line", t->line);
	return (error);
}

void	check_name_comment(t_champion *c, t_token *t, t_token *next, int nb_tok)
{
	int i;

	if (!error_name_comment(c, t, next, nb_tok))
	{
		if ((t->type == NAME && c->hasname) ||
			(t->type == COMMENT && c->hascomment))
			c->number_warning += warning_champion(c,
			"Champion already has a name or a comment", t->line);
		(t->type != NAME) ? ft_strcpy(c->header->comment, next->value.data) :
			ft_strcpy(c->header->prog_name, next->value.data);
		c->hasname = (t->type == NAME) ? 1 : c->hasname;
		c->hascomment = (t->type == COMMENT) ? 1 : c->hascomment;
	}
	i = -1;
	while (++i < c->number_token && c->tokens[i]->type == EMPTY)
		;
	if (i == c->number_token || t->type != c->tokens[i]->type)
		warning_champion(c, "comment or name are not at the begining", t->line);
	delete_token(t);
	delete_token(next);
}
