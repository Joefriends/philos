/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_and_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:54:03 by jlopes-c          #+#    #+#             */
/*   Updated: 2025/10/09 10:53:37 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	pos;
	int	num;

	pos = 1;
	i = 0;
	num = 0;
	while (((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' '))
	{
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
		{
			pos = pos * -1;
		}
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + nptr[i] - '0';
		i++;
	}
	return (num * pos);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_isdigit(argv[i]))
		{
			printf("Error: Incorrect Param\n");
			return (0);
		}
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Error: Incorrect Param\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	*free_data(t_info *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		free(data->philo[i]);
		i++;
	}
	free(data->philo);
	free(data->forks);
	return (NULL);
}

void	mutex_destroy(t_info *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i]->meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->simulation_lock);
}
