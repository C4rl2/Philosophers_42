/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafraixe <cafraixe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:22:15 by cafraixe          #+#    #+#             */
/*   Updated: 2023/08/23 13:18:43 by cafraixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*printf_state(t_eachphilo *eachphilo, char *str)
{
	pthread_mutex_lock(&eachphilo->all->mutex_haveeaten);
	if (eachphilo->all->isdead == eachphilo->id
		&& eachphilo->musteat == eachphilo->haveeaten)
		printf("Each philo has eaten enough times\n");
	else if (eachphilo->all->isdead == eachphilo->id)
	{
		printf("%lli %i", (p_tool_time() - eachphilo->all->timestart),
			eachphilo->id);
		printf("%s", str);
	}
	else if (isdead(eachphilo) == 0)
	{
		pthread_mutex_lock(eachphilo->mutexforprintf);
		if (isdead(eachphilo) == 0)
			printf("%lli %i", (p_tool_time() - eachphilo->all->timestart),
				eachphilo->id);
		if (isdead(eachphilo) == 0)
			printf("%s", str);
	}
	pthread_mutex_unlock(eachphilo->mutexforprintf);
	pthread_mutex_unlock(&eachphilo->all->mutex_haveeaten);
	return (0);
}

void	*r_eat_n_sleep(t_eachphilo *eachphilo)
{
	pthread_mutex_lock(eachphilo->mymutex);
	if (isdead(eachphilo) == 0)
		printf_state(eachphilo, " has taken a fork\n");
	pthread_mutex_lock(eachphilo->nextmutex);
	if (isdead(eachphilo) == 0)
		printf_state(eachphilo, " has taken a fork\n");
	if (isdead(eachphilo) == 0)
		printf_state(eachphilo, " is eating\n");
	pthread_mutex_lock(&eachphilo->all->mutex_lastmeal);
	eachphilo->lastmeal = p_tool_time();
	pthread_mutex_unlock(&eachphilo->all->mutex_lastmeal);
	ft_usleep(eachphilo->tte);
	pthread_mutex_unlock(eachphilo->mymutex);
	pthread_mutex_unlock(eachphilo->nextmutex);
	if (isdead(eachphilo) == 0)
		printf_state(eachphilo, " is sleeping\n");
	ft_usleep(eachphilo->tts);
	return (0);
}

void	*routine(void *datasent)
{
	t_eachphilo	*eachphilo;

	eachphilo = (t_eachphilo *) datasent;
	while (eachphilo->all->isdead == 0)
	{
		if (isdead(eachphilo) == 0)
			r_eat_n_sleep(eachphilo);
		pthread_mutex_lock(&eachphilo->all->mutex_haveeaten);
		eachphilo->haveeaten++;
		pthread_mutex_unlock(&eachphilo->all->mutex_haveeaten);
		if (isdead(eachphilo) == 0)
			printf_state(eachphilo, " is thinking\n");
	}
	return (0);
}

void	*droutine(void *datasent)
{
	t_eachphilo	*eachphilo;

	eachphilo = (t_eachphilo *)datasent;
	droutine_n(eachphilo);
	return (printf_state(eachphilo, " died\n"));
}
