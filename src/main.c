/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:56:57 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/18 10:24:49 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipe	pipex;

	if (argc < 5)
	{
		ft_dprintf(2, ERR_USER);
		return (1);
	}
	init_information(&pipex, argc, argv, env);
	init_cmd(&pipex, argc - 1, &argv[1]);
	pipe_and_exec(&pipex);
	return (0);
}	
