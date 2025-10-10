/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:40:32 by marvin            #+#    #+#             */
/*   Updated: 2025/09/22 12:40:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_command(t_info *data)
{
	pthread_mutex_lock(&data->simulation_lock);
	data->simulation_end = 1;
	pthread_mutex_unlock(&data->simulation_lock);
}

void	*death_checknsleep(t_info *data)
{
	if (data->philo_num_eat != -1 && ate_everything(data))
	{
		pthread_mutex_lock(&data->simulation_lock);
		data->simulation_end = 1;
		pthread_mutex_unlock(&data->simulation_lock);
		return (NULL);
	}
	usleep(100);
	return (NULL);
}

void	*death_monitor(void *arg)
{
	t_info	*data;
	int		i;

	data = (t_info *)arg;
	if (data->philo_num == 1)
		return (NULL);
	while (1)
	{
		i = 0;
		while (i < data->philo_num)
		{
			pthread_mutex_lock(&data->philo[i]->meal_lock);
			if (get_time_in_ms() - data->philo[i]->last_meal >= data->philo_ttd)
			{
				print_current_action(data->philo[i], " died");
				pthread_mutex_unlock(&data->philo[i]->meal_lock);
				kill_command(data);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i]->meal_lock);
			i++;
		}
		death_checknsleep(data);
	}
	return (NULL);
}

int	ate_everything(t_info *data)
{
	int	i;
	int	food_flag;

	i = 0;
	food_flag = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->philo[i]->meal_lock);
		if ((data->philo[i]->times_ate >= data->philo_num_eat)
			&& data->philo_num_eat != -1)
			food_flag++;
		pthread_mutex_unlock(&data->philo[i]->meal_lock);
		i++;
	}
	if (food_flag == data->philo_num)
		return (1);
	return (0);
}
