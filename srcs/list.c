/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:20:22 by wocheon           #+#    #+#             */
/*   Updated: 2023/02/02 22:24:13 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		print_error("malloc error", 1, 1);
	new->str = 0;
	new->dollar = 0;
	new->type = 0;
	new->pipe = 0;
	new->status = g_env->status;
	new->quote = 0;
	new->space = 0;
	new->heredoc = 0;
	new->next = NULL;
	return (new);
}

t_cmd	*push_back(t_line *line)
{
	t_cmd	*new;

	if (line->cmd == NULL)
	{
		line->cmd = new_cmd();
		return (line->cmd);
	}
	new = line->cmd;
	while (new->next)
		new = new->next;
	new->next = new_cmd();
	return (new->next);
}

void	remove_cmd(t_line *line, t_cmd **cmd)
{
	t_cmd	*temp;

	temp = line->cmd;
	if ((*cmd) == line->cmd)
	{
		line->cmd = (*cmd)->next;
		free((*cmd)->str);
		free(*cmd);
		return ;
	}
	while (temp->next != *cmd)
		temp = temp->next;
	temp->next = (*cmd)->next;
	free((*cmd)->str);
	free(*cmd);
	(*cmd) = temp;
}

t_cmd	*seperate_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = new_cmd();
	tmp->next = (*cmd)->next;
	(*cmd)->next = tmp;
	return (tmp);
}
