/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:03:47 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/11 14:38:05 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token		*create_token(int line_nb, int type)
{
	t_token		*token;

	if (!(token = malloc(sizeof(t_token))))
	{
		malloc_error("create_token");
		return (0x0);
	}
	token->line = line_nb;
	token->type = type;
	token->param[0] = 0x0;
	token->param[1] = 0x0;
	token->param[2] = 0x0;
	return (token);
}

static int	get_last_intruction_id(t_champion *champion)
{
	int id;
	int i;

	i = champion->number_token;
	while (--i >= 0 && champion->tokens[i]->type != INSTRUCTION)
		;
	id = (i < 0) ? -1 : champion->tokens[i]->value.operation->id;
	return (id);
}

/*
**	en cad de pb return 10
*/

int			size_token(int t, int id)
{
	int		res;

	res = 0;
	if (t == UNKNOWN)
		res = 10;
	if (t == REGISTER)
		res = 1;
	if (t == INDIRECT || t == INDIRECT_LABEL || t == INDIRECT_LABEL_STR)
		res = 2;
	if (t == INSTRUCTION)
		res = (id == 1 || id == 9 || id == 12 || id == 15) ? 1 : 2;
	if (t == DIRECT || t == DIRECT_LABEL || t == DIRECT_LABEL_STR)
	{
		if (id < 0)
			return (10);
		res = (id > 8 && id < 16 && id != 13) ? 2 : 4;
	}
	return (res);
}

int			add_token(t_token *token, t_champion *champion)
{
	if (token->type == INSTRUCTION)
	{
		champion->instructions[champion->number_instructions++] =
			champion->size;
		champion->size += size_token(token->type, token->value.operation->id);
	}
	else
		champion->size += size_token(token->type,
				get_last_intruction_id(champion));
	if (token->type == LABEL)
	{
		if (champion->number_labels % BUFFER_LABELS == BUFFER_LABELS - 1)
			if (!(champion->labels = realloc(champion->labels,
			(champion->number_labels + BUFFER_LABELS + 1) * sizeof(int))))
				return (malloc_error("add_token"));
		champion->labels[champion->number_labels] = champion->number_token;
		champion->number_labels++;
	}
	if (champion->number_token % BUFFER_TOKENS == BUFFER_TOKENS - 1)
		if (!(champion->tokens = realloc(champion->tokens,
		(champion->number_token + BUFFER_TOKENS + 1) * sizeof(t_token*))))
			return (malloc_error("add_token"));
	champion->tokens[champion->number_token] = token;
	champion->number_token++;
	return (1);
}
