/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 19:21:02 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/09 22:49:45 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

long long				convert_bigendian(long long val, unsigned int size)
{
	int					i;
	int					len;
	long long unsigned	res;
	int					base;

	if (size == 1)
		return (val);
	if (size > sizeof(long long) || !size || size % 2)
		return (0);
	i = -1;
	len = (size - 1) * 8;
	res = 0;
	base = 0x000000ff;
	while (++i < (int)size)
	{
		if (len > 0)
			res += (base & val) << len;
		else
			res += (base & val) >> (-len);
		len -= 16;
		base <<= 8;
	}
	return (res);
}

int						convert_param_hexa(t_champion *c, t_token *token,
							int start, int id)
{
	int res;
	int type;

	res = 0;
	type = token->type;
	if (type != REGISTER)
	{
		if ((type == DIRECT || type == DIRECT_LABEL) &&
		!(id > 8 && id < 16 && id != 13))
		{
			c->prog[start + ++res] = (token->value.number & 0xff000000) >> 24;
			c->prog[start + ++res] = (token->value.number & 0x00ff0000) >> 16;
		}
		c->prog[start + ++res] = (token->value.number & 0x0000ff00) >> 8;
	}
	c->prog[start + ++res] = token->value.number & 0x000000ff;
	return (res);
}

int						convert_token_hexa(t_champion *c, int start,
							t_token *token)
{
	int		res;
	int		id;
	int		i;

	res = -1;
	id = token->value.operation->id;
	c->prog[start + ++res] = id;
	if (!(id == 1 || id == 9 || id == 12 || id == 15))
		c->prog[start + ++res] = opcode(token);
	i = -1;
	while (++i < token->value.operation->number_param)
	{
		if (token->param[i]->type == DIRECT_LABEL ||
				token->param[i]->type == INDIRECT_LABEL)
			token->param[i]->value.number -= start;
		res += convert_param_hexa(c, token->param[i], start + res,
				token->value.operation->id);
	}
	return (res + 1);
}
