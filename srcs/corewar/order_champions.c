/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_champions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:31:47 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/02 13:57:32 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	push_back(t_champ **champs, int i)
{
	int		j;

	j = i;
	while (champs[++j])
		;
	while (j > i)
	{
		champs[j] = champs[j - 1];
		j--;
	}
}

static void	put_champ_here(t_champ **champs, int i, int j)
{
	t_champ *tmp;

	tmp = champs[i];
	champs[i] = champs[j];
	champs[j] = NULL;
	push_back(champs, i);
	champs[i + 1] = tmp;
}

/*
** Sorts the list of champions according to their player_no, and modifies
** player_no if necessary
*/

void		order_champions(t_cor *cor)
{
	int		i;
	int		j;

	i = -1;
	while (++i < cor->nb_champs)
	{
		if (cor->champs[i]->player_no < i + 1
				&& cor->champs[i]->player_no != 0)
			error(cor, "invalid option");
		j = i;
		while (cor->champs[i]->player_no != i + 1 && ++j < cor->nb_champs)
			if (cor->champs[j]->player_no == i + 1)
				put_champ_here(cor->champs, i, j);
		if (cor->champs[i]->player_no != i + 1)
		{
			j = i;
			while (cor->champs[i]->player_no != 0 && ++j < cor->nb_champs)
				if (cor->champs[j]->player_no == 0)
					put_champ_here(cor->champs, i, j);
			if (cor->champs[i]->player_no == 0)
				cor->champs[i]->player_no = i + 1;
			else
				error(cor, "invalid option");
		}
	}
}
