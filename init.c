/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:45 by jlopes-c          #+#    #+#             */
/*   Updated: 2025/09/25 11:08:23 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*initialize_forks(t_info *data)
{
	int	i;

	pthread_mutex_t *forks_assign; // think of forks like mutex locks

	i = 0;

	forks_assign = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!forks_assign)
		return (NULL); // make error stat later 
	
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&forks_assign[i], NULL) != 0)
			mutex_destroy(data); //error check
		printf("Fork %d created\n", i);
		i++;
	}
	return (forks_assign);

}

void give_forks(t_philo *data)
{
	//printf("Teste 5 %d\n", data->info->philo_num); // data info philo num call WORKS... need to restructure this
	data->fork[0] = data->id;
	data->fork[1] = (data->id + 1) % data->info->philo_num; //to prevent getting a fork that doesnt exist
	if (data->id % 2) // make even philosophers take the locks in a different order to prevent deadlock
	{
		data->fork[0] = (data->id + 1) % data->info->philo_num;
		data->fork[1] = data->id;
	}
}

t_philo **initialize_philosophers(t_info *data)
{
	int i;
	t_philo	**philo_assign;
	i = 0;

	philo_assign = malloc(sizeof(t_philo *) * data->philo_num);
	if (!philo_assign)
	{
		return NULL; //error message
	}
	while(i < data->philo_num)
	{
		philo_assign[i] = malloc(sizeof(t_philo) * 1); //hmm
		if (!philo_assign[i])
		{
			return NULL; //error message
		}
		if (pthread_mutex_init(&philo_assign[i]->meal_lock, NULL) != 0)
		{
			mutex_destroy(data);
		}

		philo_assign[i]->info = data;
		philo_assign[i]->id = i;
		philo_assign[i]->is_eating = 0;
		philo_assign[i]->is_sleeping = 0;
		philo_assign[i]->is_thinking = 0;
		philo_assign[i]->last_meal = data->start_philo; // Initialize last meal to start time
		philo_assign[i]->is_dead = 0;
		philo_assign[i]->times_ate = 0;
		
		give_forks(philo_assign[i]);
		i++;
	}
	//works...
	return (philo_assign);
}         

void init_values(char **argv, t_info *data)
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
		data->philo_num_eat = -1; //indicates no limit
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
		return ; //error
	}
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		mutex_destroy(data);
}
