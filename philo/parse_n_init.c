/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_n_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafraixe <cafraixe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:09:03 by cafraixe          #+#    #+#             */
/*   Updated: 2023/08/23 11:46:43 by cafraixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	neg;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] < '0' || str[i] > '9')
		i++;
	if (str[i - 1] == '-')
		neg = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * neg);
}

int	check_argv_digit(char **av)
{
	int	i;
	int	j;
	int	index;

	index = 1;
	if (av[5] == NULL)
		i = 2;
	else
		i = 1;
	while (i++ <= 5)
	{
		j = 0;
		while (av[index][j])
		{
			if ((av[index][j] < '0' || av[index][j] > '9')
				&& av[index][j] != '-')
			{
				printf(ERRDIG);
				return (1);
			}
			j++;
		}
		index++;
	}
	return (0);
}

int	check_argv_negative(char **av)
{
	int	i;
	int	index;

	index = 1;
	if (av[5] == NULL)
		i = 2;
	else
		i = 1;
	while (i < 5)
	{
		if (ft_atoi(&av[index][0]) < 1)
		{
			printf(ERRNEG);
			return (1);
		}
		i++;
		index++;
	}
	return (0);
}

void	init_tab(t_philo *data, char **av)
{
	int	i;

	i = 0;
	while (i < data->nbp)
	{
		data->eachphilo[i].id = i + 1;
		data->eachphilo[i].ttd = ft_atoi(av[2]);
		data->eachphilo[i].tte = ft_atoi(av[3]);
		data->eachphilo[i].tts = ft_atoi(av[4]);
		data->eachphilo[i].lastmeal = 0;
		if (av[5] != NULL)
			data->eachphilo[i].musteat = ft_atoi(av[5]);
		else
			data->eachphilo[i].musteat = -1;
		data->eachphilo[i].haveeaten = 0;
		pthread_mutex_init(&data->mutex[i], NULL);
		data->eachphilo[i].mymutex = &data->mutex[i];
		if (i == (data->nbp - 1))
			data->eachphilo[i].nextmutex = &data->mutex[0];
		else
			data->eachphilo[i].nextmutex = &data->mutex[i + 1];
		data->eachphilo[i].mutexforprintf = &data->mutexprintf;
		data->eachphilo[i].all = data;
		i++;
	}
}

t_philo	*init(char **av)
{
	t_philo	*data;

	data = (t_philo *)malloc(sizeof(t_philo));
	data->nbp = ft_atoi(av[1]);
	data->eachphilo = malloc(sizeof(t_eachphilo) * data->nbp);
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->nbp);
	data->isdead = 0;
	data->flag = 0;
	init_tab(data, av);
	return (data);
}
