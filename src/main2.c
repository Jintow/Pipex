/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:23:19 by Teiki             #+#    #+#             */
/*   Updated: 2022/12/15 15:11:03 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int	fd[2];
	int fd2[2];
	int	id1;
	int id2;

	if (pipe(fd) == -1)
		return (1);
	id1 = fork();
	if (id1 == 0)
	{
		close(fd[0]);
		char	*str;

		str = ft_calloc(50, sizeof(char));
		ft_printf("Write something\n");
		scanf("%s", str);
		ft_printf("str : %s, len :%d\n", str, ft_strlen(str));
		if (write(fd[1], str, ft_strlen(str)) == -1)
			return (2);
		close(fd[1]);
	}
	else
	{
		wait(NULL);
		if (pipe(fd2) == -1)
			return (1);
		id2 = fork();
		if (id2 == 0)
		{
			close(fd[1]);
			close(fd2[0]);
			char	str2[100];
			if (read(fd[0], str2, 100) == -1)
				return (3);
			close(fd[0]);
			int	file;
			file = open("file1.txt", O_WRONLY);
			ft_printf("%s", str2);
			if (file == -1)
				return (4);
			if (write(file, str2, ft_strlen(str2)) == -1)
				return (5);
			if (write(fd2[1], str2, ft_strlen(str2)) == -1)
				return (5);
			close(file);
			close(fd2[1]);
		}
		else
		{
			wait(NULL);
			close(fd2[1]);
			char	str3[100];
			if (read(fd2[0], str3, 100) == -1)
				return (3);
			close(fd2[0]);
			int	file2;
			file2 = open("file2.txt", O_WRONLY);
			ft_printf("%s", str3);
			if (file2 == -1)
				return (4);
			if (write(file2, str3, ft_strlen(str3)) == -1)
				return (5);
			close(file2);
		}

	}
}
