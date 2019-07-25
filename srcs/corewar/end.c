/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:03:03 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/10 15:59:39 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Frees a single champion
*/

void			delete_champion(t_champ **champ)
{
	if (*champ)
		free((*champ)->redcode);
	free(*champ);
	*champ = NULL;
}

static void		delete_visu(t_cor *cor)
{
	if (cor->visu)
	{
		if (cor->visu->arena)
			delwin(cor->visu->arena);
		if (cor->visu->arena_info)
			delwin(cor->visu->arena_info);
		if (cor->visu->arena_period_bar)
			delwin(cor->visu->arena_period_bar);
		free(cor->visu);
	}
}

/*
** Frees the whole t_cor structure.
*/

void			end(t_cor *cor)
{
	int		i;

	if (cor->champs)
	{
		i = -1;
		while (cor->champs[++i])
			delete_champion(&(cor->champs[i]));
	}
	free(cor->champs);
	free(cor->arena);
	free(cor->aff);
	delete_procs(&(cor->procs));
	if (cor->visual_on == true)
		delete_visu(cor);
	exit(0);
}

/*
** Frees the whole cor structure, prints the given error message on the error
** output and exits the program.
*/

void			error(t_cor *cor, char *err_type)
{
	ft_putstr_fd("error: ", 2);
	ft_putendl_fd(err_type, 2);
	end(cor);
}
