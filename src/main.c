/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:56:57 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/10 09:53:57 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipe	pipex;

	if (argc != 5)
	{
		ft_dprintf(2, ERR_USER);
		return (1);
	}
	pipex.bonus = 0;
	pipex.tab_cmd = NULL;
	pipex.cmd_path = NULL;
	pipex.here_doc = NULL;
	pipex.env = NULL;
	pipex.tab_pipe = NULL;
	pipex.tab_pid = NULL;
	init_information(&pipex, argc, argv, env);
	init_cmd(&pipex, argc - 1, &argv[1]);
	pipe_and_exec(&pipex);
	return (0);
}	
