/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-cho <min-cho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:57:15 by younhwan          #+#    #+#             */
/*   Updated: 2023/01/04 18:32:22 by min-cho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/builtin.h"
#include "../../incs/structs.h"
#include "../../incs/utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int				builtin_exit(t_list *token_list, int fd);
int				set_exit_status(int status);
static t_bool	is_num(const char *str);
static t_bool	ft_atoll(const char *str, long long *num);

int	builtin_exit(t_list *token_list, int fd)
{
	t_list		*tmp;
	t_token		*token;
	long long	i;

	i = 1;
	tmp = token_list->next;
	ft_putendl_fd("exit", fd);
	if (tmp == NULL)
		exit(set_exit_status(0) >> 8);
	token = tmp->content;
	if (is_num(token->value) == FALSE)
		exit(print_err(255, "exit", token->value, NUMERIC_ERR) >> 8);
	if (tmp->next != NULL)
		return (print_err(1, "exit", NULL, ARG_ERR));
	if (ft_atoll(token->value, &i) == FALSE || i < INT_MIN || INT_MAX < i)
		exit(print_err(255, "exit", token->value, NUMERIC_ERR) >> 8);
	if (i < 0)
		i = (256 - ((i * -1) % 256));
	i = (i % 256);
	exit(set_exit_status(i) >> 8);
	return (g_var->exit_status);
}

int	set_exit_status(int status)
{
	g_var->exit_status = status << 8;
	return (g_var->exit_status);
}

static t_bool	is_num(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (str && *str)
	{
		if (('0' <= *str && *str <= '9') == FALSE)
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static t_bool	ft_atoll(const char *str, long long *num)
{
	unsigned long long	nbr;
	size_t				i;

	i = 0;
	nbr = 0;
	while (str[i] && ft_is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			(*num) = -1;
		i++;
	}
	while (str[i] && ('0' <= str[i] && str[i] <= '9'))
	{
		nbr = 10 * nbr + (str[i] - '0');
		if ((*num) == 1 && __LONG_LONG_MAX__ < nbr)
			return (FALSE);
		if ((*num) == -1 && (unsigned long long)__LONG_LONG_MAX__ + 1 < nbr)
			return (FALSE);
		i++;
	}
	(*num) *= nbr;
	return (TRUE);
}
