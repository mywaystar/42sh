/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/29 18:03:00 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <prompt.h>
#include <lexer.h>
#include <parser.h>
#include <executor.h>

t_sh			*t_sh_recover(void)
{
	static t_sh	sh;

	return (&sh);
}

static	void	prepare_env(void)
{
	char	*number;
	t_sh	*sh;

	sh = t_sh_recover();
	if (env_get(sh->env_list, "SHLVL"))
		number = ft_itoa(ft_atoi(env_get(sh->env_list, "SHLVL")) + 1);
	else
		number = ft_itoa(1);
	env_set(&sh->env_list, "SHLVL", number);
	if (number)
		free(number);
}

static void		process_input(char *input)
{
	t_list	*token_list;
	t_list	*job_list;

	token_list = input_to_token_list(input);
	update_job_status();
	if (check_lexer(token_list) == 0)
	{
		job_list = token_list_to_job_list(token_list);
		exec_job_list(job_list);
	}
}

static int		shell(void)
{
	char	*input;
	int		is_last_cmd_empty;
	t_sh	*sh;

	is_last_cmd_empty = 0;
	sh = t_sh_recover();
	sh->c_prompt = prompt_create_new();
	while (1)
	{
		prompt_init();
		prompt_add_command(is_last_cmd_empty);
		prompt_current_reset();
		prompt_display(1);
		input = prompt_input();
		is_last_cmd_empty = ft_isempty(input);
		if (input)
		{
			signal(SIGINT, SIG_IGN);
			prompt_reset();
			process_input(input);
			free(input);
			ignore_major_signals();
		}
	}
	return (0);
}

int				main(int argc, char **argv, char **environ)
{
	t_sh	*sh;

	UNUSED(argv);
	sh = t_sh_recover();
	sh->vars_list = NULL;
	sh->tty = open("/dev/tty", O_RDWR);
	sh->pgid = getpgrp();
	sh->jobs = NULL;
	ignore_major_signals();
	if (argc > 1)
	{
		ft_putendl_fd("42sh cannot execute commands", 2);
		return (0);
	}
	sh->env_list = NULL;
	env_to_list(&sh->env_list, environ);
	prepare_env();
	return (shell());
}
