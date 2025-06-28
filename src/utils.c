/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:06:41 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/06/28 20:26:08 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	ft_erroralternate(void)
{
	perror("Error command");
	exit(127);
}

void	ft_freearray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_splitpath(char **envp)
{
	int		i;
	char	**dirs;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	dirs = ft_split(envp[i] + 5, ':');
	return (dirs);
}

char	*ft_findpath(char *cmd, char **envp)
{
	int		i;
	char	**dirs;
	char	*tmp;
	char	*fullpath;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	dirs = ft_splitpath(envp);
	if (!dirs)
		ft_error();
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		fullpath = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(fullpath, X_OK) == 0)
		{
			ft_freearray(dirs);
			return (fullpath);
		}
		free(fullpath);
		i++;
	}
	return (ft_freearray(dirs), NULL);
}
