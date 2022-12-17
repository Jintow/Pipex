/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:56:57 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/17 17:21:11 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipe	pipex;

	if (argc < 4)
		return (0);
	init_information(&pipex, argc, argv, env);
	init_cmd(&pipex, argc - 1, &argv[1]);
	pipe_and_exec(&pipex);
	return (0);
}	
