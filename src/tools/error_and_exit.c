/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:22:07 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/09 17:33:01 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
	General error function for the most common cases.
*/
void	error_exit(t_pipe *pipex, char *err_msg)
{
	ft_free_tab(pipex->cmd_path);
	if (pipex->tab_pid)
		free(pipex->tab_pid);
	ft_free_tab((char **)pipex->tab_pipe);
	ft_free_tab3(pipex->tab_cmd);
	if (pipex->here_doc)
		free(pipex->here_doc);
	perror(err_msg);
	exit(EXIT_FAILURE);
}

/*
	Error function for command not found.
*/
void	error_exit2(t_pipe *pipex, int i)
{
	ft_free_tab(pipex->cmd_path);
	if (pipex->tab_pid)
		free(pipex->tab_pid);
	ft_free_tab((char **)pipex->tab_pipe);
	ft_dprintf(2, "%s%s\n", ERR_CMD, pipex->tab_cmd[i][0]);
	ft_free_tab3(pipex->tab_cmd);
	exit(EXIT_FAILURE);
}

/*
	Error function for unconvenient input parameters such as
	too few arguments or NULL here_doc limiter.
*/
void	error_exit3(t_pipe *pipex, char *err_msg)
{
	ft_free_tab(pipex->cmd_path);
	ft_free_tab3(pipex->tab_cmd);
	if (pipex->tab_pid)
		free(pipex->tab_pid);
	ft_free_tab((char **)pipex->tab_pipe);
	if (pipex->here_doc)
		free(pipex->here_doc);
	ft_dprintf(2, err_msg);
	exit(EXIT_FAILURE);
}

/*
	Exit function for program success.
*/
void	gate_away(t_pipe *pipex)
{
	free(pipex->tab_pid);
	ft_free_tab((char **)pipex->tab_pipe);
	ft_free_tab(pipex->cmd_path);
	ft_free_tab3(pipex->tab_cmd);
	exit(EXIT_SUCCESS);
}

/*
	Exit function for program Failure. It it used almost only for the case
	of invalid input file descriptor to allow the first command to exit 
	without displaying any additionnal error message.
*/
void	free_and_exit(t_pipe *pipex)
{
	ft_free_tab(pipex->cmd_path);
	ft_free_tab3(pipex->tab_cmd);
	free(pipex->tab_pid);
	ft_free_tab((char **)pipex->tab_pipe);
	exit(EXIT_FAILURE);
}
