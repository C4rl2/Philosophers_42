/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafraixe <cafraixe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:29:07 by cafraixe          #+#    #+#             */
/*   Updated: 2023/08/23 13:25:32 by cafraixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	droutine_n(t_eachphilo *eachphilo)
{
	int	i;

	while (eachphilo->all->isdead == 0)
	{
		i = 0;
		while (i < eachphilo->all->nbp)
		{
			pthread_mutex_lock(&eachphilo->all->mutex_lastmeal);
			if ((p_tool_time() - eachphilo[i].lastmeal) > eachphilo[i].ttd)
			{
				droutine_firsthelp(eachphilo);
				break ;
			}
			pthread_mutex_unlock(&eachphilo->all->mutex_lastmeal);
			pthread_mutex_lock(&eachphilo->all->mutex_haveeaten);
			if (eachphilo[(eachphilo[i].all->nbp - 1)].haveeaten
				== eachphilo[i].musteat)
			{
				droutine_secondhelp(eachphilo);
				break ;
			}
			pthread_mutex_unlock(&eachphilo->all->mutex_haveeaten);
		}
	}
}

void	droutine_firsthelp(t_eachphilo *eachphilo)
{
	pthread_mutex_lock(eachphilo->mutexforprintf);
	pthread_mutex_lock(&eachphilo->all->mutex_isdead);
	eachphilo->all->isdead = eachphilo->id;
	pthread_mutex_unlock(&eachphilo->all->mutex_isdead);
	pthread_mutex_unlock(&eachphilo->all->mutex_lastmeal);
}

void	droutine_secondhelp(t_eachphilo *eachphilo)
{
	pthread_mutex_lock(eachphilo->mutexforprintf);
	pthread_mutex_lock(&eachphilo->all->mutex_isdead);
	eachphilo->all->isdead = eachphilo->id;
	pthread_mutex_unlock(&eachphilo->all->mutex_isdead);
	pthread_mutex_unlock(&eachphilo->all->mutex_haveeaten);
}

int	isdead(t_eachphilo *eachphilo)
{
	pthread_mutex_lock(&eachphilo->all->mutex_isdead);
	if (eachphilo->all->isdead == 0)
	{
		pthread_mutex_unlock(&eachphilo->all->mutex_isdead);
		return (0);
	}
	pthread_mutex_unlock(&eachphilo->all->mutex_isdead);
	return (1);
}

int	ft_usleep(useconds_t usec)
{
	useconds_t		start;
	useconds_t		after;

	start = p_tool_time();
	after = start;
	while (after - start < usec)
	{
		if (usleep(usec) == -1)
			return (-1);
		after = p_tool_time();
	}
	return (0);
}
