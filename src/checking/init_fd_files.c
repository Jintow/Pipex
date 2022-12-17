/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:28:53 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/16 22:06:40 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_in_out_put(t_pipe *pipex, int argc, char **argv);
void	get_path(t_pipe *pipex, char **env);

void	init_information(t_pipe *pipex, int argc, char **argv, char **env)
{
	get_in_out_put(pipex, argc, argv);
	get_path(pipex, env);
}

void	get_in_out_put(t_pipe *pipex, int argc, char **argv)
{
	pipex->fd_input = open(argv[1], O_RDONLY);
	if (pipex->fd_input < 0)
	{
		perror(ERR_INPUT);
		exit(EXIT_FAILURE);
	}
	pipex->fd_output = open(argv[argc -1], O_WRONLY | O_CREAT \
		| O_APPEND, 0000644);
	if (pipex->fd_output < 0)
	{
		perror(ERR_OUTPUT);
		exit(EXIT_FAILURE);
	}
}

void	get_path(t_pipe *pipex, char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		path = ft_strnstr(env[i], "PATH=", 10);
		if (path)
			break ;
		i++;
	}
	pipex->env = ft_split(&path[5], ':');
	if (!(pipex->env))
	{
		perror(ERR_MALLOC);
		exit(EXIT_FAILURE);
	}
}
