/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 00:52:57 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/12 22:58:40 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl_md5.h"

int	ft_putstr_std(char *str, int std)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	write(std, str, i);
	return (i);
}

int	ft_puthex(unsigned int nbr, int flag, int std)
{
	char	*base;
	char	tab[19];
	int		index;
	int		nb;

	base = "0123456789abcdef";
	nb = 0;
	index = 0;
	if (nbr == 0)
		return (write(std, "0", 1));
	while (nbr)
	{
		tab[index] = base[nbr % 16];
		if (tab[index] >= 'a')
			tab[index] -= flag;
		index++;
		nbr = nbr / 16;
	}
	nb = nb + index;
	while (index)
		write(std, &tab[--index], 1);
	return (nb);
}

int	ft_putint(int nbr, int std)
{
	char	tab[10];
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	if (nbr <= 0)
	{
		if (nbr == 0)
			return (write(std, "0", 1));
		else if (nbr == -2147483648)
			return (ft_putstr_std("-2147483648", std));
		else
			nb = nb + ft_putstr_std("-", std);
		nbr = nbr * -1;
	}
	while (nbr)
	{
		tab[i++] = (nbr % 10) + 48;
		nbr /= 10;
	}
	nb = nb + i;
	while (i)
		write(std, &tab[--i], 1);
	return (nb);
}

int	ft_put_size_t(size_t nbr, int std)
{
	char	tab[20];
	int		i;
	int		nb;

	i = 0;
	if (nbr == 0)
		return (write(std, "0", 1));
	while (nbr)
	{
		tab[i++] = (nbr % 10) + '0';
		nbr /= 10;
	}
	nb = i;
	while (i)
		write(std, &tab[--i], 1);
	return (nb);
}
