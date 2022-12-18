/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:28:53 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/18 12:58:18 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_in_out_put(t_pipe *pipex, int argc, char **argv);
void	get_output_here_doc(t_pipe *pipex, char *output);
void	get_path(t_pipe *pipex, char **env);

void	init_information(t_pipe *pipex, int argc, char **argv, char **env)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			error_exit3(pipex, ERR_USER_HERE_DOC);
		if (!argv[2][0])
			error_exit3(pipex, ERR_LIMITER);
		pipex->limiter = argv[2];
		make_here_doc(pipex);
		get_output_here_doc(pipex, argv[argc - 1]);
	}
	else
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
	pipex->fd_output = open(argv[argc -1], O_WRONLY | O_TRUNC | \
		O_CREAT, 0000644);
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

void	get_output_here_doc(t_pipe *pipex, char *output)
{
	pipex->fd_output = open((output), O_WRONLY | O_TRUNC | \
		O_CREAT, 0000644);
	if (pipex->fd_output < 0)
	{
		perror(ERR_OUTPUT);
		exit(EXIT_FAILURE);
	}
}