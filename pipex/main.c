/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:07:53 by grbuchne          #+#    #+#             */
/*   Updated: 2024/05/11 14:23:19 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child1(char *cmd, char **envp, t_data *data)
{
	char	*args[4];

	args[0] = "sh";
	args[1] = "-c";
	args[2] = cmd;
	args[3] = NULL;
	close(data->fd[0]);
	close(data->out);
	if (dup2(data->in, STDIN_FILENO) == -1)
	{
		exit(-1);
	}
	close(data->in);
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
	{
		exit(-1);
	}
	close(data->fd[1]);
	if (execve("/bin/sh", args, envp) == -1)
		exit(127);
	exit(1);
}

static void	child2(char *cmd, char **envp, t_data *data)
{
	char	*args[4];

	args[0] = "sh";
	args[1] = "-c";
	args[2] = cmd;
	args[3] = NULL;
	close(data->fd[1]);
	close(data->in);
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
	{
		exit(-1);
	}
	close(data->fd[0]);
	if (dup2(data->out, STDOUT_FILENO) == -1)
	{
		exit(-1);
	}
	close(data->out);
	if (execve("/bin/sh", args, envp) == -1)
		exit(127);
	exit(1);
}

static void	close_wait(t_data *data)
{
	int	status;

	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, &status, 0);
	close(data->in);
	close(data->out);
	if (WIFEXITED(status))
	{
		exit (WEXITSTATUS(status));
	}
}

void	input_check(int ac, char *envp[])
{
	if (ac != 5)
		manual_info("to use please enter: ./pipex infile cmd1 cmd2 outfile\n");
	if (!envp)
		manual_info("no environment\n");
}

int	main(int ac, char *av[], char *envp[])
{
	t_data	data;

	input_check(ac, envp);
	if (pipe(data.fd) == -1)
		message_error();
	data.in = access_check(av[1]);
	if (data.in == -1)
		file_error();
	data.out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data.out == -1)
		file_error();
	data.pid1 = fork();
	if (data.pid1 == -1)
		message_fork_error(&data);
	if (data.pid1 == 0)
		child1(av[2], envp, &data);
	data.pid2 = fork();
	if (data.pid2 == -1)
		message_fork_error(&data);
	if (data.pid2 == 0)
		child2(av[3], envp, &data);
	close_wait(&data);
	return (0);
}
