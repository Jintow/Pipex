/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:00:51 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/10 10:59:17 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_cmd(t_pipe *pipex, char **cmd);
void	exec_next_cmd(t_pipe *pipex, char **cmd, int i);
void	dup_close_exec(t_pipe *pipex, char **cmd, \
		int *pipe_current, int *pipe_prev);
void	close_all_prev_pipe(t_pipe *pipex, int fd);

void	pipe_and_exec(t_pipe *pipex)
{
	int		i;

	exec_first_cmd(pipex, pipex->tab_cmd[0]);
	if (pipex->fd_input != -1 && close(pipex->fd_input) == -1)
		error_exit(pipex, ERR_CLOSE, 1);
	i = 1;
	while (pipex->tab_cmd[i])
	{
		exec_next_cmd(pipex, pipex->tab_cmd[i], i);
		i++;
	}
	read_and_write_result(pipex);
}

/*
Function that will execute the first command except if the file descriptor
of the input file is invalid. 
*/
void	exec_first_cmd(t_pipe *pipex, char **cmd)
{
	int		*pipe_current;

	if (pipe(pipex->tab_pipe[0]) == -1)
		error_exit(pipex, ERR_PIPE, 1);
	pipe_current = pipex->tab_pipe[0];
	pipex->tab_pid[0] = fork();
	if (pipex->tab_pid[0] == -1)
		error_exit(pipex, ERR_FORK, 1);
	if (pipex->tab_pid[0] == 0)
	{
		if (pipex->fd_input != -1 && dup2(pipex->fd_input, STDIN_FILENO) == -1)
			error_exit(pipex, ERR_DUP, 0);
		if (dup2(pipe_current[1], STDOUT_FILENO) == -1)
			error_exit(pipex, ERR_DUP, 0);
		if (close(pipe_current[0]) == -1 || close(pipe_current[1]) == -1)
			error_exit(pipex, ERR_CLOS_PIP, 0);
		if (pipex->fd_input == -1)
			error_exit(pipex, NULL, 0);
		if (!ft_strlen(cmd[0]) || access(cmd[0], X_OK))
			error_exit2(pipex, cmd[0]);
		if (execve(cmd[0], cmd, pipex->env) == -1)
			error_exit(pipex, ERR_EXEC, 0);
	}
	if (close(pipe_current[1]) == -1)
		error_exit(pipex, ERR_CLOS_PIP, 1);
}

/*
Function that will execute a command, putting the previous pipe[0] 
as a standard input and the current pipe[1] as a standard output. 
*/
void	exec_next_cmd(t_pipe *pipex, char **cmd, int i)
{
	int	*pipe_current;
	int	*pipe_prev;

	pipe_current = pipex->tab_pipe[i];
	pipe_prev = pipex->tab_pipe[i - 1];
	if (pipe(pipe_current) == -1)
		error_exit(pipex, ERR_PIPE, 1);
	pipex->tab_pid[i] = fork();
	if (pipex->tab_pid[i] == -1)
		error_exit(pipex, ERR_FORK, 1);
	if (pipex->tab_pid[i] == 0)
		dup_close_exec(pipex, cmd, pipe_current, pipe_prev);
	if (close(pipe_current[1]) == -1)
		error_exit(pipex, ERR_CLOS_PIP, 1);
}

void	dup_close_exec(t_pipe *pipex, char **cmd, \
		int *pipe_current, int *pipe_prev)
{
	if (dup2(pipe_prev[0], STDIN_FILENO) == -1)
		error_exit(pipex, ERR_DUP, 0);
	if (dup2(pipe_current[1], STDOUT_FILENO) == -1)
		error_exit(pipex, ERR_DUP, 0);
	close_all_prev_pipe(pipex, pipe_current[0]);
	if (close(pipe_current[0]) == -1)
		error_exit(pipex, ERR_CLOS_PIP, 0);
	if (close(pipe_current[1]) == -1)
		error_exit(pipex, ERR_CLOS_PIP, 0);
	if (!ft_strlen(cmd[0]) || access(cmd[0], X_OK))
		error_exit2(pipex, cmd[0]);
	if (execve(cmd[0], cmd, pipex->env) == -1)
		error_exit(pipex, ERR_EXEC, 0);
}

/*
	The aim of this functions is to close all previous pipe reading fd 
	(pipe[0]) as they were still opened.
*/
void	close_all_prev_pipe(t_pipe *pipex, int fd)
{
	int	i;

	i = 0;
	while (pipex->tab_pipe[i][0] != fd)
	{
		if (close(pipex->tab_pipe[i][0]) == -1)
			error_exit(pipex, ERR_CLOS_PIP, 0);
		i++;
	}
}
