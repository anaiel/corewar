/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:48:47 by abossard          #+#    #+#             */
/*   Updated: 2019/07/11 14:38:05 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define NUMBER_OPERATION_MAX 16

int		islabel(char *s)
{
	int i;
	int len;

	len = ft_strlen(s);
	i = 0;
	while (i < len && ft_strchr(LABEL_CHARS, s[i]))
		i++;
	if (i == len - 1 && s[i] == LABEL_CHAR && len > 1)
		return (1);
	return (0);
}

int		isintruction(char *s)
{
	int i;

	i = -1;
	while (g_tab[++i].operation)
		if (!ft_strcmp(g_tab[i].operation, s))
			return (1);
	return (0);
}

int		isregister(char *s)
{
	int i;

	if (s && *s == 'r' && ft_atoi(s + 1) <= REG_NUMBER)
	{
		i = 1;
		while (ft_isdigit(s[i]))
			i++;
		if (i > 1 && i == (int)ft_strlen(s))
			return (1);
	}
	return (0);
}

int		compose_withthese_letters(char *word, char *letters)
{
	while (*word)
	{
		if (!ft_strchr(letters, *word))
			return (0);
		word++;
	}
	return (1);
}

int		isindirect_label(char *s)
{
	if (*s == LABEL_CHAR && ft_strlen(s) > 1 &&
	compose_withthese_letters(&s[1], LABEL_CHARS))
		return (1);
	return (0);
}
