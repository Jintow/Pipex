/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:22:07 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/18 12:31:05 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(t_pipe *pipex, char *err_msg)
{
	ft_free_tab(pipex->env);
	ft_free_tab3(pipex->tab_cmd);
	if (pipex->here_doc)
		free(pipex->here_doc);
	perror(err_msg);
	exit(EXIT_FAILURE);
}

void	error_exit2(t_pipe *pipex, int i)
{
	char	*err_msg;
	
	ft_free_tab(pipex->env);
	err_msg = ft_strjoin(ERR_CMD, pipex->tab_cmd[i][0]);
	err_msg = ft_strjoin_free_s1(err_msg, "\n");
	ft_free_tab3(pipex->tab_cmd);
	ft_dprintf(2, err_msg);
	free(err_msg);
	exit(EXIT_FAILURE);
}

void	error_exit3(t_pipe *pipex, char *err_msg)
{
	ft_free_tab(pipex->env);
	ft_free_tab3(pipex->tab_cmd);
	if (pipex->here_doc)
		free(pipex->here_doc);
	ft_dprintf(2, err_msg);
	exit(EXIT_FAILURE);
}

void	gate_away(t_pipe *pipex)
{
	ft_free_tab(pipex->env);
	ft_free_tab3(pipex->tab_cmd);
	exit(EXIT_SUCCESS);
}
