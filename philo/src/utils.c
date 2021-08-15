//
// Created by Diani on 13/07/2021.
//

#include "../includes/philosophers.h"

int	ft_iswhitespace(char c)
{
	return (c == '\t' || c == '\n' || c == ' ' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	ft_atoi(const char *str)
{
	unsigned long	result;
	int				i;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
		if (result > 9223372036854775807 && sign == -1)
			return (0);
		else if (result > 9223372036854775807 && sign == 1)
			return (-1);
	}
	return ((int)(sign * result));
}

int	print_error(char *str)
{
	printf("%s\n", str);
	return (-1);
}

int	ft_is_pos_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
