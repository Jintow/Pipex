/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:22:07 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/10 12:29:05 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
	General error function for the most common cases.
*/
void	error_exit(t_pipe *pipex, char *err_msg, int id)
{
	if (id)
		ft_free_tab(pipex->cmd_path);
	if (id && pipex->tab_pid)
		free(pipex->tab_pid);
	if (id)
		ft_free_tab((char **)pipex->tab_pipe);
	if (id)
		ft_free_tab3(pipex->tab_cmd);
	if (id && pipex->here_doc)
		free(pipex->here_doc);
	if (err_msg)
		perror(err_msg);
	exit(EXIT_FAILURE);
}

/*
	Error function for command not found.
*/
void	error_exit2(t_pipe *pipex, char *cmd)
{
	(void)pipex;
	ft_dprintf(2, "%s%s\n", ERR_CMD, cmd);
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
