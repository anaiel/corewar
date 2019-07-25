/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:50:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/05 12:28:19 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	launch_visual(t_cor *cor)
{
	init_visu(cor);
	create_color_panel();
	draw_starting_arena(cor);
	battle(cor);
	announce_winner(cor);
	nodelay(stdscr, false);
	wgetch(stdscr);
	endwin();
}

void		usage(void)
{
	ft_putstr_fd("usage: ./corewar [-visual | [-v verbosity_level] ", 2);
	ft_putstr_fd("[-dump nbr_cycles]] [-n player_number] champion1.cor", 2);
	ft_putstr_fd(" ...\n\n*** VERBOSITY LEVEL ***\n 1: Live instructions\n", 2);
	ft_putstr_fd(" 2: Display current cycle and cycle to die decrement\n", 2);
	ft_putstr_fd(" 4: Display details of the instrutions\n 8: Display ", 2);
	ft_putstr_fd("carriage deaths\n16: Display movement of the PCs ", 2);
	ft_putstr_fd("(except in case of zjump)\nAdd the numbers for a ", 2);
	ft_putstr_fd("combination of verbosity levels\n", 2);
}

int			main(int ac, char **av)
{
	t_cor	cor;

	ac--;
	av++;
	initialize(&cor);
	if (!ac || get_options(&cor, &ac, &av) == ERROR || !ac)
	{
		usage();
		end(&cor);
	}
	get_champions(&cor, ac, av);
	order_champions(&cor);
	arena_setup(&cor);
	if (cor.visual_on)
		launch_visual(&cor);
	else
	{
		introduce_champions(&cor);
		battle(&cor);
		announce_winner(&cor);
	}
	end(&cor);
}
