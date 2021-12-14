/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 14:13:32 by tokino            #+#    #+#             */
/*   Updated: 2020/11/14 14:13:35 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	abs_n;

	abs_n = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		abs_n = -abs_n;
	}
	if (abs_n > 9)
	{
		ft_putnbr_fd(abs_n / 10, fd);
	}
	ft_putchar_fd(abs_n % 10 + 48, fd);
}
