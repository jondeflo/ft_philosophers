/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:40:11 by jondeflo          #+#    #+#             */
/*   Updated: 2021/02/10 16:48:07 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>

typedef struct		s_cond
{
	int				num;
	size_t			die;
	int				eat;
	int				sleep;
	int				limit;
	int				is_limit;
	size_t			start;
	sem_t			*print;
	sem_t			*state;
	sem_t			*forks;
}					t_cond;

typedef struct		s_phil
{
	int				num;
	int				eats;
	int				alive;
	size_t			prev_eat;
	t_cond			*cond;
}					t_phil;

typedef struct		s_main
{
	t_cond			*cond;
	t_phil			*phil;
	pthread_t		*thread;
}					t_main;

int					ready_set_go(t_main *main);
int					checker(t_main *main, int k, int eats, int flag);
void				*eat(void *args);
int					get_forks(t_phil *tmp);
int					init_phils(t_main *main);
int					make_arrays(t_main *main);
void				add_phil(t_main *main, int i);
void				clear_all(t_main *main);
int					ft_atoi(const char *nptr);
int					fill_conditions(char **av, t_main *main);
int					parce_free(t_main *main);
int					print_err(char *str);
int					print_state(t_phil *tmp, size_t time, char state);
int					print_dead(t_phil *tmp, size_t time);
size_t				get_time(void);
void				prec_sleep(size_t time);

#endif
