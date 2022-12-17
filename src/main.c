/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:56:57 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/17 15:06:39 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	char	*path_f2;
	int		size_tab;
	int		i;
	t_pipe	pipex;

	if (argc < 4)
		return (0);
	init_information(&pipex, argc, argv, env);
	i = 0;
	init_cmd(&pipex, argc - 1, &argv[1]);
	while (pipex.tab_cmd[i])
		ft_printf("%s\n", pipex.tab_cmd[i++][0]);
	pipe_and_exec(&pipex);
	return (0);
}	
