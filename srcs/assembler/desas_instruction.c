/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desas_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:31:50 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/11 14:38:00 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_token	*add_token_operation_id(t_token *token, unsigned int id)
{
	token->value.operation = &g_tab[id];
	return (token);
}

t_token			*get_param(char param, unsigned char *prog, int *pos)
{
	int				size;
	unsigned int	value;
	t_token			*token;

	if (param == REG_CODE || param == T_REG)
		token = create_token(0, REGISTER);
	else if (param == DIR_CODE || param == T_DIR)
		token = create_token(0, DIRECT);
	else if (param == IND_CODE || param == T_IND)
		token = create_token(0, INDIRECT);
	else
		return (0x0);
	if (!token)
		return (0x0);
	if (token->type == DIRECT &&
			!(prog[0] > 8 && prog[0] < 16 && prog[0] != 13))
		size = 4;
	else
		size = (token->type == REGISTER) ? 1 : 2;
	ft_memcpy(&value, &prog[*pos], size);
	value = convert_bigendian(value, size);
	add_token_integer(token, value);
	*pos += size;
	return (token);
}

int				get_instruction_argcode(unsigned char *prog, t_token *token)
{
	int		pos;
	int		i;
	char	param[3];

	i = -1;
	pos = 2;
	ft_bzero(param, 3);
	param[0] = (prog[1] & 0xc0) >> 6;
	param[1] = (prog[1] & 0x30) >> 4;
	param[2] = (prog[1] & 0x0c) >> 2;
	while (param[++i] && i < 3)
		token->param[i] = get_param(param[i], prog,
				&pos);
	return (pos);
}

int				get_instruction(t_champion *champion, unsigned char *prog)
{
	t_token	*token;
	int		pos;
	int		i;

	i = -1;
	pos = 1;
	if (prog[0] > 16 && prog[0] <= 0)
		return (0);
	if (!(token = create_token(0, INSTRUCTION)))
		return (0);
	add_token_operation_id(token, prog[0] - 1);
	add_token(token, champion);
	if (!(prog[0] == 1 || prog[0] == 9 || prog[0] == 12 || prog[0] == 15))
		return (get_instruction_argcode(prog, token));
	else
		while (++i < token->value.operation->number_param)
			token->param[i] = get_param(token->value.operation->tab[i],
					prog, &pos);
	return (pos);
}
