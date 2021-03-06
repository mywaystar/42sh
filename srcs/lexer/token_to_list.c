/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 16:02:34 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/13 21:49:10 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

t_list		*new_token(t_token_type type, void *content)
{
	t_token		new_t;

	new_t.type = type;
	new_t.content = content;
	return (ft_lstnew(&new_t, sizeof(t_token)));
}

void		del_token(void *token_void, size_t size_content)
{
	t_token		*token;

	if (!token_void)
		return ;
	if (size_content != sizeof(t_token))
		return ;
	token = (t_token *)token_void;
	if (token->content)
		free(token->content);
	free(token);
}
