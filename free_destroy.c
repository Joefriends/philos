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

void	destroy_mutexes(t_info *data)
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
}
