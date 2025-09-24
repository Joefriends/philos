/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:16:45 by jlopes-c          #+#    #+#             */
/*   Updated: 2025/09/24 15:10:45 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ate_everything(t_info *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->philo[i]->meal_lock);
		if ((data->philo[i]->times_ate >= data->philo_num_eat) && data->philo_num_eat != -1)
		{
			data->food_flag++;
			printf("FOOD FLAG : %d\n", data->food_flag);
		}
		pthread_mutex_unlock(&data->philo[i]->meal_lock);
		i++;
		
	}
	if (data->food_flag == data->philo_num)
		return (1);
	return (0);
}

void	eat_routine(t_philo *data)
{
	pthread_mutex_lock(&data->info->forks[data->fork[0]]);
	print_current_action(data, " has taken a fork");
	pthread_mutex_lock(&data->info->forks[data->fork[1]]);
	print_current_action(data, " has taken a fork");
	pthread_mutex_lock(&data->meal_lock);
	print_current_action(data, "is eating");
	data->last_meal = get_time_in_ms();
	data->times_ate = data->times_ate + 1;
	pthread_mutex_unlock(&data->meal_lock);
	philo_sleep(data->info->philo_tte, data->info);
	pthread_mutex_unlock(&data->info->forks[data->fork[0]]);
	pthread_mutex_unlock(&data->info->forks[data->fork[1]]);
	print_current_action(data, "is sleeping");
	philo_sleep(data->info->philo_tts, data->info);
	print_current_action(data, "is thinking");
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->info->philo_num == 1) //Kill philo if only one
	{
		pthread_mutex_lock(&philo->info->forks[0]);
		print_current_action(philo, " has taken a fork");// Wait for time to die, then print death
		philo_sleep(philo->info->philo_ttd, philo->info);
		print_current_action(philo, " died");
		pthread_mutex_unlock(&philo->info->forks[0]);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		philo_sleep(10, philo->info);//stagger start times a bit
	while (philo && philo->info->simulation_end == 0 && !ate_everything(philo->info))
		eat_routine(philo);
	return (NULL);
}

void	create_thrd(t_info *data)
{
	int	i;

	i = 0;	
	while (i < data->philo_num)
	{
		pthread_create(&data->philo[i]->thread, NULL, philo_routine, data->philo[i]); //// FUCKKK
		i++;
	}
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
}

void	end_thrd(t_info *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philo[i]->thread, NULL);
		i++;
	}
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
				data->simulation_end = 1;
				pthread_mutex_unlock(&data->philo[i]->meal_lock);
				return (NULL); // End simulation /////FOUND THE TIME ISSUE LEAK OR DOESNT WORK, DONT KNOW HOW TO FIX
			}
			pthread_mutex_unlock(&data->philo[i]->meal_lock);
			i++;
		}
		// Check if all philosophers have eaten enough
		if (data->philo_num_eat != -1 && ate_everything(data))
		{
			data->simulation_end = 1;
			return (NULL); // End simulation
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		exit(1);
	//check_valid_stuff
	t_info data;
	
	//initiate thread
	if (!is_valid(argc, argv))
		{
			return (0);
		}
	init_values(argv, &data);
	create_thrd(&data); //works? not really
	
	pthread_t monitor;
	pthread_create(&monitor, NULL, death_monitor, &data);

	pthread_join(monitor, NULL);
	end_thrd(&data); //doesnt work
	
	mutex_destroy(&data);
	
	free_data(&data);

	//start simulation

	//end simulation

	return (0);
}