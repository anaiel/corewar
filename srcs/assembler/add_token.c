/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:14:48 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/11 15:40:35 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token		*add_token_string(t_token *token, char *str)
{
	if (!token)
		return (0x0);
	if (!(token->value.data = ft_strdup(str)))
		return (0x0);
	return (token);
}

t_token		*add_token_integer(t_token *token, int value)
{
	if (!token)
		return (0x0);
	token->value.number = value;
	return (token);
}

t_token		*add_token_operation(t_token *token, char *s)
{
	int i;

	i = 0;
	if (!token)
		return (0x0);
	while (g_tab[i].operation && ft_strcmp(g_tab[i].operation, s))
		i++;
	if (!g_tab[i].operation)
		return (0x0);
	token->value.operation = &g_tab[i];
	return (token);
}
