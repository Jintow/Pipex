/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:00:51 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/17 14:03:53 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_and_write_result(t_pipe *pipex);
void	exec_first_cmd(t_pipe *pipex);
void	close_and_save(t_pipe *pipex, int *pipe_current, int *pipe_prev);
void	exec_next_cmd(t_pipe *pipex, char **cmd, int *pipe_prev);

void	pipe_and_exec(t_pipe *pipex)
{
	int		i;
	char	***tab_cmd;

	exec_first_cmd(pipex);
	if (close(pipex->fd_input) == -1)
		error_exit(pipex, ERR_CLOSE);
	tab_cmd = &pipex->tab_cmd[1];
	i = 0;
	while (tab_cmd[i])
	{
		exec_next_cmd(pipex, tab_cmd[i], pipex->pipe_current);
		i++;
	}
	read_and_write_result(pipex);
}

void	exec_first_cmd(t_pipe *pipex)
{
	int		pipe_current[2];
	int		pid;
	char	**cmd;

	cmd = pipex->tab_cmd[0];
	if (pipe(pipe_current) == -1)
		error_exit(pipex, ERR_PIPE);
	pid = fork();
	if (pid == -1)
		error_exit(pipex, ERR_FORK);
	if (pid == 0)
	{
		if (dup2(pipex->fd_input, STDIN_FILENO) == -1)
			error_exit(pipex, ERR_DUP);
		if (dup2(pipe_current[1], STDOUT_FILENO) == -1)
			error_exit(pipex, ERR_DUP);
		if (close(pipe_current[0]) == -1)
			error_exit(pipex, ERR_CLOS_PIP);
		if (close(pipe_current[1]) == -1)
			error_exit(pipex, ERR_CLOS_PIP);
		if (execve(cmd[0], cmd, NULL) == -1)
			error_exit(pipex, ERR_EXEC);
	}
	wait(NULL);
	close_and_save(pipex, pipe_current, NULL);
}

void	close_and_save(t_pipe *pipex, int *pipe_current, int *pipe_prev)
{
	if (pipe_prev)
	{
		if (close(pipe_prev[0]) == -1)
			error_exit(pipex, ERR_CLOS_PIP);
	}
	ft_bzero(pipex->pipe_current, sizeof(int));
	ft_memcpy(pipex->pipe_current, pipe_current, 2);
	dprintf(2, "%d\n", pipex->pipe_current[0]);
	if (close(pipe_current[1]) == -1)
		error_exit(pipex, ERR_CLOS_PIP);
}

void	exec_next_cmd(t_pipe *pipex, char **cmd, int *pipe_prev)
{
	int		pipe_current[2];
	int		pid;

	if (pipe(pipe_current) == -1)
		error_exit(pipex, ERR_PIPE);
	pid = fork();
	if (pid == -1)
		error_exit(pipex, ERR_FORK);
	if (pid == 0)
	{
		if (dup2(pipe_prev[0], STDIN_FILENO) == -1)
			error_exit(pipex, ERR_DUP);
		dprintf(2, "%d\n", pipe_prev[0]);
		if (dup2(pipe_current[1], STDOUT_FILENO) == -1)
			error_exit(pipex, ERR_DUP);
		if (close(pipe_current[0]) == -1)
			error_exit(pipex, ERR_CLOS_PIP);
		if (close(pipe_current[1]) == -1)
			error_exit(pipex, ERR_CLOS_PIP);
		if (execve(cmd[0], cmd, NULL) == -1)
			error_exit(pipex, ERR_EXEC);
	}
	wait(NULL);
	close_and_save(pipex, pipe_current, pipe_prev);
}

void	read_and_write_result(t_pipe *pipex)
{
	char	buffer[1000000];
	int		size;

	size = 0;
	while (read(pipex->pipe_current[0], &buffer[size], 1))
		size++;
	if (write(pipex->fd_output, buffer, ft_strlen(buffer)) == -1)
		error_exit(pipex, ERR_WRITE);
	if (close(pipex->fd_output) == -1)
		error_exit(pipex, ERR_CLOSE);
}
