/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafraixe <cafraixe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:48:21 by cafraixe          #+#    #+#             */
/*   Updated: 2023/08/23 13:21:38 by cafraixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

# define ERRNEG "ERROR : NEGATIVE NUMBERS IN ARGUMENTS !\n"
# define ERRDIG "ERROR : NON-DIGITS IN ARGUMENTS !\n"
# define ERRARG "ERROR : 4 or 5 ARGUMENTS NEEDED !\n"

typedef struct s_eachphilo
{
	int				id;
	int				ttd;
	int				tte;
	int				ttt;
	int				tts;
	int				musteat;
	int				haveeaten;
	long long int	lastmeal;
	struct s_philo	*all;
	pthread_t		thread;
	pthread_mutex_t	*mymutex;
	pthread_mutex_t	*nextmutex;
	pthread_mutex_t	*mutexforprintf;
}	t_eachphilo;

typedef struct s_philo
{
	int				nbp;
	int				isdead;
	long long int	timestart;
	pthread_t		dthread;
	t_eachphilo		*eachphilo;
	pthread_mutex_t	mutexprintf;
	pthread_mutex_t	mutex_haveeaten;
	pthread_mutex_t	mutex_lastmeal;
	pthread_mutex_t	mutex_isdead;
	int				flag;
	pthread_mutex_t	*mutex;
}	t_philo;

//PARSING//
int				ft_atoi(char *str);
int				check_argv_digit(char **av);
int				check_argv_negative(char **av);
t_philo			*init(char **av);
void			norme(void);
//THREADS//
void			*routine(void *datasent);
void			*printf_state(t_eachphilo *eachphilo, char *str);
void			*droutine(void *datasent);
int				ft_usleep(useconds_t usec);
long long int	p_tool_time(void);
int				isdead(t_eachphilo *eachphilo);
void			droutine_firsthelp(t_eachphilo *eachphilo);
void			droutine_secondhelp(t_eachphilo *eachphilo);
void			droutine_n(t_eachphilo *eachphilo);

#endif