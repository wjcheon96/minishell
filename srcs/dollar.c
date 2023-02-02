/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:20:26 by wocheon           #+#    #+#             */
/*   Updated: 2023/02/02 22:05:20 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollar(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		if (str[i] && (ft_isalpha(str[i + 1]) \
			|| str[i + 1] == '?'))
		{
			i += 2;
			size++;
		}
		else if (str[i])
			i++;
	}
	return (size);
}

int	get_len(t_env *temp)
{
	int	i;

	i = 0;
	if (temp)
		i = ft_strlen(temp->val);
	return (i);
}

char	*trans_dollar(char *str, int *i)
{
	t_env	*temp;
	char	*ret;
	char	*key;
	char	*free_ret;
	int		j;

	j = 1;
	while (str[*i + j] && ft_isalnum(str[*i + j]))
		j++;
	key = ft_substr(str, *i + 1, j - 1);
	temp = check_env(key);
	free(key);
	ret = ft_substr(str, 0, *i);
	if (temp)
	{
		key = ret;
		ret = ft_strjoin(key, temp->val);
		free(key);
	}
	key = ft_strdup(str + *i + j);
	free_ret = ret;
	ret = ft_strjoin(ret, key);
	free_str(free_ret, key, str);
	*i += get_len(temp);
	return (ret);
}

char	*trans_status(char *str, int *i)
{
	char	*ret;
	char	*key;
	char	*free_ret;
	int		len;

	ret = ft_substr(str, 0, *i);
	key = ft_itoa(g_env->status);
	len = ft_strlen(key);
	free_ret = ret;
	ret = ft_strjoin(ret, key);
	free_str(free_ret, key, NULL);
	key = ft_strdup(str + *i + 2);
	*i += len;
	free_ret = ret;
	ret = ft_strjoin(ret, key);
	free_str(free_ret, key, str);
	return (ret);
}

char	*change_dollar(char *str, int dollar)
{
	int		i;
	int		size;
	char	*ret;

	i = 0;
	size = 0;
	ret = str;
	while (size < dollar)
	{
		while (ret[i] && ret[i] != '$')
			i++;
		if (ret[i] && ft_isalpha(ret[i + 1]))
		{
			size++;
			ret = trans_dollar(ret, &i);
		}
		else if (ret[i] && (ret[i + 1] == '?'))
		{
			size++;
			ret = trans_status(ret, &i);
		}
		else
			i++;
	}
	return (ret);
}
