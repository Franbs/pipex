/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:57:01 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/06/19 14:44:08 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_execute(char *cmd, char **envp)
{
	char	*path;
	char	**splitcmd;

	splitcmd = ft_split(cmd, ' ');
	path = ft_findpath(splitcmd[0], envp);
	if (!path)
	{
		ft_freearray(splitcmd);
		ft_erroralternate("Error command");
	}
	if (execve(path, splitcmd, envp) == -1)
	{
		free(path);
		ft_freearray(splitcmd);
		ft_erroralternate("Error command");
	}
}

void	ft_child_process(char **av, int *fd, char **envp)
{
	int	fd_in;

	fd_in = open(av[1], O_RDONLY);
	if (fd_in == -1)
		ft_error("Error opening file");
	dup2(fd_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	ft_execute(av[2], envp);
}

void	ft_parent_process(char **av, int *fd, char **envp)
{
	int	fd_out;

	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		ft_error("Error opening/creating the file2");
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	ft_execute(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		ft_error("Error. There must be 4 args");
	if (pipe(fd) == -1)
		ft_error("Error creating the pipe");
	pid1 = fork();
	if (pid1 < 0)
		ft_error("Fork error");
	if (pid1 == 0)
		ft_child_process(av, fd, envp);
	pid2 = fork();
	if (pid2 < 0)
		ft_error("Fork error");
	if (pid2 == 0)
		ft_parent_process(av, fd, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
