/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 18:19:22 by jondeflo          #+#    #+#             */
/*   Updated: 2021/02/15 10:23:03 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int		get_forks(t_phil *tmp)
{
	if (!(tmp->num % 2))
		prec_sleep(50);
	if (pthread_mutex_lock(tmp->left->mutex))
		return (1);
	if (print_state(tmp, get_time() - tmp->cond->start, 'f'))
		return (1);
	if (pthread_mutex_lock(tmp->right->mutex))
		return (1);
	if (print_state(tmp, get_time() - tmp->cond->start, 'f'))
		return (1);
	prec_sleep(25);
	if (print_state(tmp, get_time() - tmp->cond->start, 'e'))
		return (1);
	tmp->prev_eat = get_time();
	return (0);
}

void	*eat(void *args)
{
	t_phil	*tmp;

	tmp = (t_phil*)args;
	while (1)
	{
		if (get_time() - tmp->prev_eat >= tmp->cond->die)
		{
			tmp->alive = 0;
			return (0);
		}
		if (print_state(tmp, get_time() - tmp->cond->start, 't'))
			return (0);
		if (get_forks(tmp))
			return (0);
		prec_sleep(tmp->cond->eat * 1000);
		if (pthread_mutex_unlock(tmp->left->mutex) ||
		pthread_mutex_unlock(tmp->right->mutex))
			return (0);
		tmp->eats++;
		if (print_state(tmp, get_time() - tmp->cond->start, 's'))
			return (0);
		prec_sleep(tmp->cond->sleep * 1000);
	}
	return (0);
}

int		checker(t_main *main, int k, int eats, int flag)
{
	while (flag == 0)
	{
		if (pthread_mutex_lock(main->cond->state_lock))
			return (print_err("Error in mutex"));
		if (main->cond->is_limit == 1 &&
		main->phil[k].eats == main->cond->limit)
		{
			eats++;
			main->phil[k].eats = -1;
			if (eats == main->cond->num)
				break ;
		}
		if (main->phil[k].alive == 0 ||
		(get_time() - main->phil[k].prev_eat) >= main->cond->die)
		{
			print_dead(&main->phil[k], (get_time() - main->cond->start));
			break ;
		}
		if (pthread_mutex_unlock(main->cond->state_lock))
			return (1);
		k < main->cond->num - 1 ? (k++) : (k = 0);
	}
	return (0);
}

int		ready_set_go(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->cond->num)
		if (pthread_create(&(main->thread[i]), NULL, eat, &(main->phil[i])))
			return (1);
	if (checker(main, 0, 0, 0))
		return (1);
	i = -1;
	while (++i < main->cond->num)
		if (pthread_detach(main->thread[i]))
			return (1);
	usleep(100);
	return (0);
}

int		main(int ac, char **av)
{
	t_main	*main;
	t_cond	*cond;

	if (!(main = (t_main*)malloc(sizeof(t_main))))
		return (print_err("Memory allocation error"));
	if (!(cond = (t_cond*)malloc(sizeof(t_cond))))
		return (print_err("Memory allocation error"));
	main->cond = cond;
	if (ac < 5 || ac > 6)
	{
		printf("Wrong arguments number\n");
		return (parce_free(main));
	}
	if (fill_conditions(av, main) == 1)
		return (print_err("Error in arguments"));
	if (make_arrays(main) == 1)
		return (print_err("Error in malloc/init"));
	if (init_forks(main) == 1)
		return (print_err("Error in malloc/init"));
	if (init_phils(main) == 1)
		return (print_err("Error in malloc/init"));
	if (ready_set_go(main) == 1)
		return (print_err("Error in malloc/init"));
	clear_all(main);
	return (0);
}
