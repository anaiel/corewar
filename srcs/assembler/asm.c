/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:29:46 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/11 15:41:30 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		firstcheck(t_fichier **file, char *s)
{
	int				len;

	len = ft_strlen(s);
	if (len > 2 && s[len - 2] == '.' && s[len - 1] == 's')
		if (((*file)->fd_in = open(s, O_RDONLY)) != -1)
		{
			if (!((*file)->file_name = ft_strnjoin(s, "cor", ft_strlen(s) - 1)))
				return (0);
			return (1);
		}
	return (0);
}

static int		main_asm(t_champion *champion, t_fichier *file, char *name)
{
	clear_champion(champion);
	clear_file(file);
	if (!firstcheck(&file, name))
		return (0);
	if (!parsing(file, champion))
		return (0);
	verify_champion(champion);
	if (champion->number_error == 0)
		return (create_champion(file, champion));
	return (0);
}

int				main(int argc, char **argv)
{
	t_champion		*champion;
	t_fichier		*file;
	int				i;

	if (argc == 1)
	{
		ft_printf("usage: ./asm champion_file1.s ...\n");
		return (0);
	}
	i = 0;
	if (!(champion = init_champion()) ||
			!(file = init_file()))
		return (0);
	while (++i < argc)
	{
		if (main_asm(champion, file, argv[i]))
			ft_printf("Writing output program to %s\n", file->file_name);
		else
			ft_printf("IMPOSSIBLE: %s\n", argv[i]);
	}
	get_next_line(NO_MORE_REACHABLE, &file->line);
	close(file->fd_in);
	free_champion(&champion);
	free_file(&file);
	return (0);
}
