/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:04:22 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/11 15:57:50 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		verify_champion_line(t_champion *c, int t, int deb,
		int tok_line)
{
	if (t == NAME || t == COMMENT)
		check_name_comment(c, c->tokens[deb], c->tokens[deb + 1], tok_line);
	else if (t == LABEL)
		check_label(c, c->tokens[deb], deb, tok_line);
	else if (t == INSTRUCTION)
		check_instruction(c, c->tokens[deb], deb, tok_line);
	else if (t == UNKNOWN)
		error_champion(c, "Unknown token", c->tokens[deb]->line);
	else
	{
		ft_printf("Does not belong here: (%d)\n", c->tokens[deb]->line);
		c->number_error++;
	}
	return (1);
}

static void		check_warning_champion(t_champion *c)
{
	int i;

	i = -1;
	while (++i < c->number_token && c->tokens[i]->type != INSTRUCTION)
		;
	if (i == c->number_token)
		warning_champion(c, "code empty", -1);
	if (!c->hasname || !c->hascomment)
		warning_champion(c, "Missing name or comment", -1);
}

int				verify_champion(t_champion *c)
{
	int i;
	int l;
	int j;

	i = 0;
	while (i < c->number_token)
	{
		while (i < c->number_token && c->tokens[i] &&
			c->tokens[i]->type == EMPTY)
			i++;
		if (i == c->number_token)
			break ;
		l = c->tokens[i]->line;
		j = i;
		while (j < c->number_token && c->tokens[j] && c->tokens[j]->line == l)
			j++;
		verify_champion_line(c, c->tokens[i]->type, i, j - i);
		i = j;
		if (c->number_error > NUMBERMAX_ERROR)
			return (-1);
	}
	check_warning_champion(c);
	return ((c->number_error || !c->hasname || !c->hascomment) ? -1 : 1);
}
