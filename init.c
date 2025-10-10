/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:45 by jlopes-c          #+#    #+#             */
/*   Updated: 2025/10/10 11:04:52 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*initialize_forks(t_info *data)
{
	int				i;
	pthread_mutex_t	*forks_assign;

	i = 0;
	forks_assign = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!forks_assign)
		return (NULL);
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&forks_assign[i], NULL) != 0)
		{
			mutex_destroy(data);
			free(forks_assign);
			return (NULL);
		}
		i++;
	}
	return (forks_assign);
}

void	give_forks(t_philo *data)
{
	data->fork[0] = data->id - 1;
	data->fork[1] = (data->id) % data->info->philo_num;
	if (data->id % 2 == 0)
	{
		data->fork[0] = (data->id) % data->info->philo_num;
		data->fork[1] = data->id - 1;
	}
}

t_philo	**initialize_philosophers(t_info *data)
{
	int		i;
	t_philo	**philo_assign;

	i = 0;
	philo_assign = malloc(sizeof(t_philo) * data->philo_num);
	if (!philo_assign)
		return (NULL);
	while (i < data->philo_num)
	{
		philo_assign[i] = malloc(sizeof(t_philo) * 1);
		if (!philo_assign[i])
			return (NULL);
		if (pthread_mutex_init(&philo_assign[i]->meal_lock, NULL) != 0)
			mutex_destroy(data);
		philo_assign[i]->id = i + 1;
		philo_assign[i]->info = data;
		philo_assign[i]->info->start_philo = get_time_in_ms();
		philo_assign[i]->last_meal = data->start_philo;
		philo_assign[i]->times_ate = 0;
		give_forks(philo_assign[i]);
		i++;
	}
	return (philo_assign);
}

void	init_mutex(t_info *data)
{
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		mutex_destroy(data);
	if (pthread_mutex_init(&data->simulation_lock, NULL) != 0)
		mutex_destroy(data);
}

void	init_values(char **argv, t_info *data)
{
	data->philo_num = ft_atoi(argv[1]);
	data->philo_ttd = ft_atoi(argv[2]);
	data->philo_tte = ft_atoi(argv[3]);
	data->philo_tts = ft_atoi(argv[4]);
	data->start_philo = get_time_in_ms();
	data->simulation_end = 0;
	if (argv[5])
		data->philo_num_eat = ft_atoi(argv[5]);
	else
		data->philo_num_eat = -1;
	data->forks = initialize_forks(data);
	if (!data->forks)
	{
		mutex_destroy(data);
		return ;
	}
	data->philo = initialize_philosophers(data);
	if (!data->philo)
	{
		mutex_destroy(data);
		return ;
	}
	init_mutex(data);
}
