/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahtouh <atahtouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:29:18 by atahtouh          #+#    #+#             */
/*   Updated: 2024/12/31 15:29:41 by atahtouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		k;
	char	*ptr;
	long	nb;

	nb = n;
	k = ft_len(nb);
	ptr = (char *)malloc((k + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[k] = '\0';
	if (nb == 0)
		ptr[--k] = '0';
	if (nb < 0)
	{
		ptr[0] = '-';
		nb = nb * -1;
	}
	while (nb != 0)
	{
		k--;
		ptr[k] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (ptr);
}
