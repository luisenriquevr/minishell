/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:21:53 by cristianama       #+#    #+#             */
/*   Updated: 2022/05/14 07:00:57 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	handle_signal(int sig)
{
	global.exit_status += sig;
	if (sig == 2)
	{
		global.exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		//write()
		signal(SIGQUIT, SIG_DFL);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		global.exit_status = 127;
	}
}
