/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:41:33 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/16 21:11:46 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		find_path(char **cmd, char **env);
void	make_tab_cmd(t_pipe *pipex, char **str, int size);
void	make_cmd_path(t_pipe *pipex);

void	init_cmd(t_pipe *pipex, int argc, char **argv)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
		return ;
	else
		make_tab_cmd(pipex, &argv[1], argc - 2);
}

void	error_exit(t_pipe *pipex, char *err_msg)
{
	ft_free_tab(pipex->env);
	ft_free_tab3(pipex->tab_cmd);
	perror(err_msg);
	exit(EXIT_FAILURE);
}


void	make_tab_cmd(t_pipe *pipex, char **str, int size)
{
	char	***tab_cmd;
	int		i;

	tab_cmd = malloc(sizeof(char **) * size + 1);
	if (!tab_cmd)
		error_exit(pipex, ERR_MALLOC);
	i = 0;
	while (i < size)
	{
		tab_cmd[i] = ft_split(str[i], ' ');
		if (!tab_cmd[i])
			error_exit(pipex, ERR_MALLOC);
		i++;
	}
	tab_cmd[i] = NULL;
	pipex->tab_cmd = tab_cmd;
	make_cmd_path(pipex);
}

void	make_cmd_path(t_pipe *pipex)
{
	int	i;
	int	id_err;

	i = 0;
	while (pipex->tab_cmd[i])
	{
		if (access(pipex->tab_cmd[i][0], X_OK) != 0)
		{
			id_err = find_path(&pipex->tab_cmd[i][0], pipex->env);
			if (id_err == 0)
				error_exit(pipex, ERR_CMD);
			else if (id_err == -1)
				error_exit(pipex, ERR_MALLOC);
		}
		i++;
	}
}

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
