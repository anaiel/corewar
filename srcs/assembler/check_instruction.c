/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 19:33:31 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/11 14:37:59 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	isgoodparam(t_champion *c, t_token *token, int expected)
{
	int		type;
	int		tmp;

	type = token->type;
	if ((type == DIRECT_LABEL_STR || type == INDIRECT_LABEL_STR))
	{
		tmp = manage_label_param(c, token->value.data);
		ft_strdel(&(token->value.data));
		token->type = (type == DIRECT_LABEL_STR) ?
			DIRECT_LABEL : INDIRECT_LABEL;
		if (tmp == -1)
			return (0);
		token->value.number = tmp;
		type = token->type;
	}
	if (type == REGISTER && expected & T_REG)
		return (1);
	if ((type == DIRECT_LABEL || type == DIRECT) && expected & T_DIR)
		return (1);
	if ((type == INDIRECT_LABEL || type == INDIRECT) && expected & T_IND)
		return (1);
	return (0);
}

static int	manage_instruction(t_champion *c, int limits, t_token *token,
		int pos)
{
	int i;
	int param;

	i = -1;
	param = -1;
	while (++i < limits)
		if (c->tokens[pos + i]->type != SEPARATOR)
			move_token(&token->param[++param], &c->tokens[pos + i]);
		else
			delete_token(c->tokens[pos + i]);
	return (1);
}

static int	check_parameters(t_champion *c, t_token *token, int pos, int limits)
{
	int		i;
	t_op	*instruction;
	int		param;
	int		expected;

	param = 0;
	expected = 0;
	instruction = token->value.operation;
	i = -1;
	while (++i < limits && param < instruction->number_param)
	{
		if (!expected)
		{
			if (!isgoodparam(c, c->tokens[pos + i], instruction->tab[param++]))
				return (error_champion(c, "Incorrect parameter", token->line));
		}
		else if (c->tokens[pos + i]->type != SEPARATOR)
		{
			i--;
			warning_champion(c, "SEPARATOR expected", token->line);
		}
		expected = (expected == 0) ? SEPARATOR : 0;
	}
	manage_instruction(c, limits, token, pos);
	return (limits);
}

int			check_instruction(t_champion *c, t_token *token, int pos,
		int tok_line)
{
	t_op	*instruction;

	instruction = token->value.operation;
	if (tok_line > instruction->number_param * 2)
		return (error_champion(c, "Too many parameters", token->line));
	else if (tok_line > instruction->number_param)
		return (check_parameters(c, token, pos + 1, tok_line - 1));
	else
		error_champion(c, "Missing parameter", token->line);
	return (1);
}
