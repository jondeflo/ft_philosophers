/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:40:11 by jondeflo          #+#    #+#             */
/*   Updated: 2021/02/08 15:32:01 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct		s_fork
{
	pthread_mutex_t	*mutex;
}					t_fork;

typedef struct		s_cond
{
	int				num;
	size_t			die;
	int				eat;
	int				sleep;
	int				limit;
	int				is_limit;
	size_t			start;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*state_lock;

}					t_cond;

typedef struct		s_phil
{
	int				num;
	int				eats;
	int				alive;
	t_fork			*left;
	t_fork			*right;
	struct s_phil	*left_phil;
	struct s_phil	*right_phil;
	size_t			prev_eat;
	t_cond			*cond;
}					t_phil;

typedef struct		s_main
{
	t_cond			*cond;
	t_fork			*fork;
	t_phil			*phil;
	pthread_t		*thread;
}					t_main;

int					ready_set_go(t_main *main);
int					checker(t_main *main, int k, int eats, int flag);
void				*eat(void *args);
int					get_forks(t_phil *tmp);
int					parce_free(t_main *main);
int					fill_conditions(char **av, t_main *main);
int					ft_atoi(const char *nptr);
void				add_phil(t_main *main, int i);
int					make_arrays(t_main *main);
void				get_neighbours(t_main *main, int i);
int					init_phils(t_main *main);
int					init_forks(t_main *main);
int					print_err(char *str);
int					print_state(t_phil *tmp, size_t time, char state);
int					print_dead(t_phil *tmp, size_t time);
size_t				get_time(void);
void				prec_sleep(size_t time);
void				clear_all(t_main *main);

#endif
