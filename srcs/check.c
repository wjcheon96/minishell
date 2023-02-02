/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:23:00 by wocheon           #+#    #+#             */
/*   Updated: 2023/02/02 22:27:26 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check(char *rd_line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (rd_line[i])
	{
		if (rd_line[i] == '\'' && flag == 0)
			flag = 1;
		else if (rd_line[i] == '\"' && flag == 0)
			flag = 2;
		else if (rd_line[i] == '\'' && flag == 1)
			flag = 0;
		else if (rd_line[i] == '\"' && flag == 2)
			flag = 0;
		i++;
	}
	if (flag)
		return (0);
	return (1);
}

void	check_dollar(t_line *line)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = line->cmd;
	tmp = 0;
	while (cmd)
	{
		if (cmd->quote != 1)
		{
			cmd->dollar = is_dollar(cmd->str);
			if (cmd->dollar)
			{
				cmd->str = change_dollar(cmd->str, cmd->dollar);
				if (!cmd->str[0] && cmd->quote == 0 && tmp && tmp->type != 1)
				{
					remove_cmd(line, &cmd);
					if (!line->cmd)
						return ;
				}
			}
		}
		tmp = cmd;
		if (cmd)
			cmd = cmd->next;
	}
}

int	check_type(char *str, int i)
{
	if (str[i] == '|')
		return (1);
	else if (!ft_strncmp(str + i, ">>", 2))
		return (2);
	else if (!ft_strncmp(str + i, "<<", 2))
		return (2);
	else if (str[i] == '>')
		return (1);
	else if (str[i] == '<')
		return (1);
	return (0);
}

int	check_error(t_line *line)
{
	t_cmd	*cmd;

	cmd = line->cmd;
	if (cmd && cmd->type == pip)
		return (0);
	while (cmd)
	{
		if (cmd->type)
		{
			if (cmd->type && !cmd->next)
				return (0);
			else if (cmd->type == cmd->next->type)
				return (0);
			else if (cmd->type == 1 && cmd->next->type)
				return (0);
		}
		cmd = cmd->next;
	}
	return (1);
}

int	check_quote(char *str)
{
	int		i;
	char	quote;

	i = 1;
	quote = str[0];
	while (str[i] && str[i] != quote)
		i++;
	if (!str[i])
		return (-1);
	return (i - 1);
}
