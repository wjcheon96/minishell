/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:29:00 by wocheon           #+#    #+#             */
/*   Updated: 2023/02/02 21:00:03 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_loop(t_cmd **cmd, char *str)
{
	t_cmd	*tmp;

	tmp = (*cmd)->next;
	if (tmp->space == 2 || tmp->space == 3)
		(*cmd)->space = 2;
	else
		(*cmd)->space = 0;
	(*cmd)->next = tmp->next;
	free_str(tmp->str, (*cmd)->str, NULL);
	free(tmp);
	(*cmd)->quote = 3;
	(*cmd)->str = str;
}

void	join_quote(t_line *line)
{
	t_cmd	*cmd;
	char	*str;

	cmd = line->cmd;
	while (cmd->next)
	{
		if (cmd->space <= 1 && (cmd->next->space == 0 || cmd->next->space == 2))
		{
			if ((!cmd->type && !cmd->next->type) \
				&& (cmd->quote || cmd->next->quote))
			{
				str = ft_strjoin(cmd->str, cmd->next->str);
				join_loop(&cmd, str);
			}
			else
				cmd = cmd->next;
		}
		else
			cmd = cmd->next;
	}
}

void	tokenize(t_line *line, char *rd_line)
{
	seperate_quote(line, rd_line);
	if (line->syntax)
		return (syntax_error("syntax error", 1, 0));
	seperate_as_type(line);
	seperate_space(line);
	check_dollar(line);
	if (!line->cmd)
		return ;
	join_quote(line);
}

int	parse(t_line *line, char *rd_line)
{
	line->size = 1;
	line->syntax = 0;
	line->cmd = NULL;
	if (!quote_check(rd_line))
	{
		syntax_error("syntax error", 1, 0);
		return (0);
	}
	tokenize(line, rd_line);
	if (line->syntax)
		return (line->syntax);
	if (!check_error(line))
	{
		syntax_error("syntax error", 1, 0);
		clear_cmd(line);
		return (0);
	}
	if (!line->cmd)
	{
		if (line->cmd)
			clear_cmd(line);
		g_env->status = 0;
		return (0);
	}
	return (1);
}
