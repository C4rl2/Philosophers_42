/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafraixe <cafraixe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:48:16 by cafraixe          #+#    #+#             */
/*   Updated: 2023/08/23 11:37:55 by cafraixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>

long long int	p_tool_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	clean_n_free(t_philo *data)
{
	int	i;

	i = 0;
	while (i < data->nbp)
		pthread_mutex_destroy(&data->mutex[i++]);
	pthread_mutex_destroy(&data->mutexprintf);
	pthread_mutex_destroy(&data->mutex_haveeaten);
	pthread_mutex_destroy(&data->mutex_lastmeal);
	pthread_mutex_destroy(&data->mutex_isdead);
	free(data->mutex);
	free(data->eachphilo);
	free(data);
}

void	join_threads(t_philo *data)
{
	int	i;

	i = 0;
	pthread_join(data->dthread, NULL);
	while (i < data->nbp)
	{
		pthread_join(data->eachphilo[i].thread, NULL);
		i++;
	}
}

void	create_threads(t_philo *data, int i, int tab)
{
	pthread_mutex_init(&data->mutex_isdead, NULL);
	while (i < data->nbp)
	{
		tab = tab + 2;
		pthread_create(&data->eachphilo[tab].thread, NULL, &routine,
			(void *) &data->eachphilo[tab]);
		i = i + 2;
	}
	i = 2;
	tab = -1;
	usleep(300);
	while (i <= data->nbp)
	{
		tab = tab + 2;
		pthread_create(&data->eachphilo[tab].thread, NULL, &routine,
			(void *) &data->eachphilo[tab]);
		i = i + 2;
	}
	if (data->nbp % 2 == 1)
	{
		pthread_create(&data->eachphilo[i - 2].thread, NULL, &routine,
			&data->eachphilo[i - 2]);
	}
	pthread_create(&data->dthread, NULL, &droutine, data->eachphilo);
	join_threads(data);
}

int	main(int ac, char **av)
{
	int		i;
	int		tab;
	t_philo	*data;

	(norme(), tab = -2, i = 1);
	if (ac == 5 || ac == 6)
	{
		if ((check_argv_digit(av) == 0) && (check_argv_negative(av) == 0))
		{
			data = init(av);
			pthread_mutex_init(&data->mutexprintf, NULL);
			pthread_mutex_init(&data->mutex_lastmeal, NULL);
			pthread_mutex_init(&data->mutex_haveeaten, NULL);
			data->timestart = p_tool_time();
			if (ft_atoi(av[3]) + ft_atoi(av[4]) < ft_atoi(av[2])
				&& ft_atoi(av[1]) > 1)
				create_threads(data, i, tab);
			else
				printf("0 1 died\n");
			clean_n_free(data);
		}
	}
	else
		printf(ERRARG);
	return (0);
}
