/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:41:33 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/22 12:08:48 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		find_path(char **cmd, char **env);
void	make_tab_cmd(t_pipe *pipex, char **str, int size);
void	make_cmd_path(t_pipe *pipex);

/*
	Function that call the make_tab_command depending 
	on the initial inputs. If the output file descriptor 
	is invalid, the last command won't be executed.
*/

void	init_cmd(t_pipe *pipex, int argc, char **argv)
{
	if (ft_strcmp(argv[0], "here_doc") == 0)
		make_tab_cmd(pipex, &argv[2], argc - 3);
	else if (pipex->fd_output == -1)
		make_tab_cmd(pipex, &argv[1], argc - 3);
	else
		make_tab_cmd(pipex, &argv[1], argc - 2);
}

/*
	Function that initiate arrays of command, pipes and pid
	corresponding to each of the command input arguments.
*/

void	make_tab_cmd(t_pipe *pipex, char **str, int size)
{
	int		i;

	pipex->tab_cmd = malloc(sizeof(char **) * (size + 1));
	pipex->tab_pid = malloc(sizeof(int) * (size + 1));
	pipex->tab_pipe = malloc(sizeof(int *) * (size + 1));
	pipex->size = size;
	if (!pipex->tab_cmd || !pipex->tab_pid || !pipex->tab_pipe)
		error_exit(pipex, ERR_MALLOC);
	i = 0;
	while (i < size)
	{
		pipex->tab_cmd[i] = ft_split(str[i], ' ');
		pipex->tab_pipe[i] = calloc(2, sizeof(int));
		if (!pipex->tab_cmd[i] || !pipex->tab_pipe[i])
			error_exit(pipex, ERR_MALLOC);
		i++;
	}
	pipex->tab_cmd[i] = NULL;
	pipex->tab_pipe[i] = NULL;
	pipex->tab_pid[i] = -10;
	make_cmd_path(pipex);
}

/*
	Function that check the access of each command input argument.
	If access isn't valid, it will call the finding path function.
	If there is no valid path in the environment, it will display an error.
*/

void	make_cmd_path(t_pipe *pipex)
{
	int	i;
	int	id_err;

	i = 0;
	while (pipex->tab_cmd[i])
	{
		if (access(pipex->tab_cmd[i][0], X_OK) != 0)
		{
			id_err = find_path(&pipex->tab_cmd[i][0], pipex->cmd_path);
			if (id_err == 0)
				error_exit2(pipex, i);
			if (id_err == -1)
				error_exit(pipex, ERR_MALLOC);
		}
		i++;
	}
}

/* 
	Function that will try each possible path for command input argument.
*/

int	find_path(char **cmd, char **env)
{
	int		i;
	char	*test_path;

	i = 0;
	while (env[i])
	{
		test_path = ft_strjoin(env[i], "/");
		if (!test_path)
			return (-1);
		test_path = ft_strjoin_free_s1(test_path, *cmd);
		if (!test_path)
			return (-1);
		if (access(test_path, X_OK) == 0)
		{
			free(*cmd);
			*cmd = test_path;
			return (1);
		}
		free(test_path);
		i++;
	}
	return (0);
}
