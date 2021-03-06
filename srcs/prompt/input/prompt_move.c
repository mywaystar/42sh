/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/11 20:38:10 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <prompt.h>

enum e_prompt_status	prompt_move_start(char *buf)
{
	t_sh	*sh;

	sh = t_sh_recover();
	if (!HOME)
		return (TRYING);
	sh->c_prompt->cursor_index = 0;
	prompt_display(1);
	return (READING);
}

enum e_prompt_status	prompt_move_end(char *buf)
{
	t_sh	*sh;

	sh = t_sh_recover();
	if (!END)
		return (TRYING);
	sh->c_prompt->cursor_index = sh->c_prompt->lenght;
	prompt_display(1);
	return (READING);
}

enum e_prompt_status	prompt_move_to_last_prompt(char *buf)
{
	t_sh		*sh;

	sh = t_sh_recover();
	if (!UP)
		return (TRYING);
	if (ft_lstget_at(sh->history, sh->prompt_position + 1))
	{
		sh->prompt_position++;
		sh->c_prompt = ft_lstget_at(
			sh->history, sh->prompt_position)->content;
		prompt_display(1);
	}
	else
		tputs(tgetstr("bl", NULL), 0, tputs_putchar);
	return (READING);
}

enum e_prompt_status	prompt_move_to_next_prompt(char *buf)
{
	t_sh		*sh;

	sh = t_sh_recover();
	if (!DOWN)
		return (TRYING);
	if (ft_lstget_at(sh->history, sh->prompt_position - 1))
	{
		sh->prompt_position--;
		sh->c_prompt = ft_lstget_at(
			sh->history, sh->prompt_position)->content;
		prompt_display(1);
	}
	else
		tputs(tgetstr("bl", NULL), 0, tputs_putchar);
	return (READING);
}
