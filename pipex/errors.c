/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:28:14 by grbuchne          #+#    #+#             */
/*   Updated: 2024/05/11 14:18:55 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	message_error(void)
{
	perror("pipex");
	strerror(errno);
	exit(EXIT_FAILURE);
}

void	message_fork_error(t_data *data)
{
	ft_putendl_fd("pipex: fork error", STDERR_FILENO);
	if (data->fd[1] >= 1)
		close(data->fd[1]);
	if (data->fd[0] >= 1)
		close(data->fd[0]);
	exit(1);
}

bool	error_true(char *error)
{
	perror(error);
	return (true);
}

void	file_error(void)
{
	perror("pipex:");
	exit(127);
}
