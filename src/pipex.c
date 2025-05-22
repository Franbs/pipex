/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:57:01 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/05/22 15:09:52 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av)
{
	int	fd_out;

	if (ac != 5)
		ft_error("Error. There must be 4 args.");
	if (access(av[1], R_OK) == -1)
		ft_error("Error accessing the file1.");
	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!fd_out)
		ft_error("Error opening/creating the file2.");
	return (0);
}
