/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:27:11 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/03 13:59:40 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_dump_info(t_cor *cor, int *ac, char ***av)
{
	if (*ac >= 2)
	{
		if (!ft_isuint((*av)[1]))
			return (ERROR);
		cor->dump = !cor->visual_on;
		cor->dump_cycle = ft_atoui((*av)[1]);
		(*av) += 2;
		(*ac) -= 2;
		return (0);
	}
	else
		return (ERROR);
}

static int	get_verbose_info(t_cor *cor, int *ac, char ***av)
{
	if (*ac >= 2)
	{
		if (!ft_isuint((*av)[1]) || ft_atoui((*av)[1]) > 31)
			return (ERROR);
		cor->verbose = (cor->visual_on == true) ? 0 : (char)ft_atoui((*av)[1]);
		(*av) += 2;
		(*ac) -= 2;
		return (0);
	}
	else
		return (ERROR);
}

int			get_options(t_cor *cor, int *ac, char ***av)
{
	while (*ac && (*av)[0][0] == '-')
		if (ft_strequ((*av)[0], "-dump"))
		{
			if (get_dump_info(cor, ac, av) == ERROR)
				return (ERROR);
		}
		else if (ft_strequ((*av)[0], "-v"))
		{
			if (get_verbose_info(cor, ac, av) == ERROR)
				return (ERROR);
		}
		else if (ft_strequ((*av)[0], "-n"))
			break ;
		else if (ft_strequ((*av)[0], "-visual"))
		{
			cor->visual_on = true;
			cor->dump = false;
			cor->verbose = 0;
			(*av)++;
			(*ac)--;
		}
		else
			return (ERROR);
	return (0);
}
