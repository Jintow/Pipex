/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:22:07 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/17 15:24:20 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(t_pipe *pipex, char *err_msg)
{
	ft_free_tab(pipex->env);
	ft_free_tab3(pipex->tab_cmd);
	perror(err_msg);
	exit(EXIT_FAILURE);
}

void	gate_away(t_pipe *pipex)
{
	ft_free_tab(pipex->env);
	ft_free_tab3(pipex->tab_cmd);
	exit(EXIT_SUCCESS);
}
