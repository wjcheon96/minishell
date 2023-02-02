/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 05:22:40 by wocheon           #+#    #+#             */
/*   Updated: 2023/02/02 22:28:50 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_cmd(t_cmd **cmd, char *str)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
		{
			(*cmd)->str = ft_substr(str, 0, i);
			tmp = seperate_cmd(cmd);
			tmp->str = ft_strdup(str + i);
			free(str);
			if ((*cmd)->space == 1)
				(*cmd)->space = 3;
			else
				(*cmd)->space = 2;
			return ;
		}
		i++;
	}
}

void	before_split(t_line *line, t_cmd **cmd, char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (remove_cmd(line, cmd));
	if (i != 0)
		(*cmd)->space = 1;
	(*cmd)->str = ft_strdup(str + i);
	free(str);
	str = (*cmd)->str;
	split_cmd(cmd, str);
}

int	check_space(char *str)
{
	while (*str)
	{
		if (ft_isspace(*str))
			return (1);
		str++;
	}
	return (0);
}

void	seperate_space(t_line *line)
{
	t_cmd	*cmd;
	char	*str;

	cmd = line->cmd;
	while (cmd)
	{
		if (cmd->type == 0 && !cmd->quote)
		{
			if (check_space(cmd->str))
			{
				str = cmd->str;
				before_split(line, &cmd, str);
			}
		}
		cmd = cmd->next;
	}
}
