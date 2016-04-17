/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 18:24:02 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/17 17:17:03 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <executor.h>
#include <builtins.h>
#include <stdio.h>
#include <sys/errno.h>
void		launch_process_builtin(t_process *p)
{
	t_sh	*shell;

	shell = t_sh_recover();
	dup2(p->stdio[0].fd, 0);
	dup2(p->stdio[1].fd, 1);
	dup2(p->stdio[2].fd, 2);
	p->status = boot_builtin(shell->env_list, p->argv);
	p->completed = 1;
}

void		launch_process(t_process *p, pid_t pgid, int foreground)
{
	char	**env;
	t_sh	*shell;
	pid_t	pid;

	if (!p)
		exit(1);
	pid = getpid();
	if (pgid == 0)
		pgid = pid;
	setpgid(pid, pgid);
	shell = t_sh_recover();
	env = env_from_list(shell->env_list);
	if (foreground)
		tcsetpgrp(0, pgid);
	reset_major_signals();
	dup2(p->stdio[0].fd, 0);
	dup2(p->stdio[1].fd, 1);
	dup2(p->stdio[2].fd, 2);
	execve(p->argv[0], p->argv, env);
	ft_putstr("42sh: command not found: "); // PIMP MY ERROR MESSAGE
	ft_putendl(p->argv[0]);
	exit(1);
}

int		update_process_status(t_job *j, pid_t pid, int status)
{
	t_list	*process;

	process = j->process_list;
	if (pid > 0)
	{
		while (process)
		{
			if (((t_process *)process->content)->pid == pid)
			{
				if (WIFEXITED(status))
				{
					((t_process *)process->content)->status = WEXITSTATUS(status);
					((t_process *)process->content)->completed = 1;
				}
				for (int i = 0; i <= 2; i++) {
					if (((t_process *)process->content)->stdio[i].to_close)
					{
						printf("Closing fd %d\n", ((t_process *)process->content)->stdio[i].fd);
						close(((t_process *)process->content)->stdio[i].fd);
					}
				}
				return (0);
			}
			process = process->next;
		}
	}
	else if (pid == 0 || errno == ECHILD) /* No processes ready to report.  */
		return -1;
	else
	{
		perror ("waitpid");
		return -1;
  	}
	return -1;
}