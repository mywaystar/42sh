/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/18 20:06:13 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		builtin_help(t_list *environ, char **cmds)
{
	UNUSED(cmds);
	UNUSED(environ);
	ft_putendl("help:\n");
	ft_putendl("builtins:");
	ft_putendl("cd [-LP] [path]");
	ft_putendl("pwd [-LP]");
	ft_putendl("exit [code]");
	ft_putendl("env [-i] [var=value, ...] [cmd]");
	ft_putendl("setenv [var] [value]");
	ft_putendl("unsetenv [var]");
	ft_putendl("export [var=val]...");
	ft_putendl("unset [var]...");
	ft_putendl("read [var]...");
	ft_putendl("jobs");
	ft_putendl("fg");
	ft_putendl("bg");
	return (0);
}
