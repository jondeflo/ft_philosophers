/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jondeflo <jondeflo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 18:19:17 by jondeflo          #+#    #+#             */
/*   Updated: 2021/02/14 13:04:17 by jondeflo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int		parce_free(t_main *main)
{
	free(main->cond);
	free(main);
	return (1);
}

int		fill_conditions(char **av, t_main *main)
{
	if (!(main->cond->num = ft_atoi(av[1])))
		return (parce_free(main));
	if (!(main->cond->die = ft_atoi(av[2])))
		return (parce_free(main));
	if (!(main->cond->eat = ft_atoi(av[3])))
		return (parce_free(main));
	if (!(main->cond->sleep = ft_atoi(av[4])))
		return (parce_free(main));
	if (av[5])
	{
		if (!(main->cond->limit = ft_atoi(av[5])))
			return (parce_free(main));
		main->cond->is_limit = 1;
	}
	else
	{
		main->cond->limit = -1;
		main->cond->is_limit = 0;
	}
	if (main->cond->num < 2)
		return (parce_free(main));
	main->cond->start = get_time();
	return (0);
}

int		ft_atoi(const char *nptr)
{
	int					cnt;
	int					sign;
	unsigned long long	res;

	cnt = 0;
	res = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == 45)
		sign = -1;
	if (*nptr == 45 || *nptr == 43)
		nptr++;
	while (*nptr >= 48 && *nptr <= 57)
	{
		res = *nptr - 48 + (res * 10);
		nptr++;
		cnt++;
	}
	if (cnt > 19)
		return (sign == -1 ? 0 : -1);
	return (int)(res * sign);
}

void	clear_all(t_main *main)
{
	int i;

	i = -1;
	while (++i < main->cond->num)
		free(main->phil[i].thread);
	free(main->phil);
	sem_unlink("/print");
	sem_unlink("/state");
	sem_unlink("/forks");
	free(main->cond);
	free(main);
}
