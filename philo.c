/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:34:48 by jlopes-c          #+#    #+#             */
/*   Updated: 2025/10/10 10:41:29 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_order(t_philo *data)
{
	if (data->id % 2 == 0)
	{
		pthread_mutex_lock(&data->info->forks[data->fork[1]]);
		print_current_action(data, " has taken a fork");
		pthread_mutex_lock(&data->info->forks[data->fork[0]]);
		print_current_action(data, " has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->info->forks[data->fork[0]]);
		print_current_action(data, " has taken a fork");
		pthread_mutex_lock(&data->info->forks[data->fork[1]]);
		print_current_action(data, " has taken a fork");
	}
}

void	eat_routine(t_philo *data)
{
	fork_order(data);
	pthread_mutex_lock(&data->meal_lock);
	print_current_action(data, " is eating");
	data->last_meal = get_time_in_ms();
	data->times_ate = data->times_ate + 1;
	pthread_mutex_unlock(&data->meal_lock);
	philo_sleep(data->info->philo_tte, data->info);
	if (data->id % 2 == 0)
	{
		pthread_mutex_unlock(&data->info->forks[data->fork[0]]);
		pthread_mutex_unlock(&data->info->forks[data->fork[1]]);
	}
	else
	{
		pthread_mutex_unlock(&data->info->forks[data->fork[1]]);
		pthread_mutex_unlock(&data->info->forks[data->fork[0]]);
	}
	print_current_action(data, " is sleeping");
	philo_sleep(data->info->philo_tts, data->info);
	print_current_action(data, " is thinking");
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->info->philo_num == 1)
	{
		pthread_mutex_lock(&philo->info->forks[0]);
		print_current_action(philo, " has taken a fork");
		philo_sleep(philo->info->philo_ttd, philo->info);
		print_current_action(philo, " died");
		pthread_mutex_unlock(&philo->info->forks[0]);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		philo_sleep(10, philo->info);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	while (philo)
{
	pthread_mutex_lock(&philo->info->simulation_lock);
	if (philo->info->simulation_end == 1)
	{
		pthread_mutex_unlock(&philo->info->simulation_lock);
		break ;
	}
	pthread_mutex_unlock(&philo->info->simulation_lock);
	eat_routine(philo);
}

	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info	*data;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		exit(1);
	}
	
	data = malloc(sizeof(t_info));
	if (!data)
		return (1);
	if (!is_valid(argc, argv))
		return (0);
	init_values(argv, data);
	create_thrd(data);
	end_thrd(data);
	mutex_destroy(data);
	free_data(data);
	free(data);
	return (0);
}
