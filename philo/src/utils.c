//
// Created by Diani on 13/07/2021.
//

#include "../includes/philosophers.h"

//size_t	ft_strlen(const char *s)
//{
//	size_t	len;
//
//	len = 0;
//	while (s[len] != '\0')
//		len++;
//	return (len);
//}
//
//char	*ft_strchr(const char *s, int c)
//{
//	size_t	i;
//
//	if (s == NULL)
//		return (NULL);
//	i = 0;
//	while (s[i] != '\0')
//	{
//		if (s[i] == (char)c)
//			return ((char *)(s + i));
//		i++;
//	}
//	if (s[i] == (char)c)
//		return ((char *)(s + i));
//	return (NULL);
//}
//
//char	*ft_strdup(const char *s1)
//{
//	char	*str;
//	size_t	size;
//
//	size = 0;
//	while (s1[size] != '\0')
//		size++;
//	str = (char *)malloc(sizeof(char) * (size + 1));
//	if (!str)
//		return (NULL);
//	size = 0;
//	while (s1[size] != '\0')
//	{
//		str[size] = s1[size];
//		size++;
//	}
//	str[size] = '\0';
//	return (str);
//}
//
//char	*ft_substr(const char *s, unsigned int start, size_t len)
//{
//	char	*string;
//	size_t	i;
//	size_t	length;
//
//	if (!s)
//		return (NULL);
//	length = ft_strlen(s);
//	if (start > length)
//		return (ft_strdup(""));
//	if (length - start < len)
//		len = length - start;
//	string = (char *)malloc(sizeof(char) * (len + 1));
//	i = 0;
//	while (s[start] != '\0' && i < len)
//	{
//		string[i] = s[start];
//		start++;
//		i++;
//	}
//	string[i] = '\0';
//	return (string);
//}
//
//char	*ft_strtrim(const char *s1, const char *set)
//{
//	size_t	i;
//	size_t	j;
//
//	if (!s1)
//		return (NULL);
//	if (!set)
//		return (ft_strdup(s1));
//	i = 0;
//	j = ft_strlen(s1) - 1;
//	while (s1[i] && ft_strchr(set, s1[i]))
//		i++;
//	if (!s1[i])
//		return (ft_strdup(""));
//	while (s1[j] && ft_strchr(set, s1[j]))
//		j--;
//	return (ft_substr(s1, i, j - i + 1));
//}
//
//
//
//int	ft_isnumber(char *str)
//{
//	int		i;
//	char	*no_space;
//	char	*white_spaces;
//
//	white_spaces = " \t\n\v\f\r";
//	no_space = ft_strtrim(str, white_spaces);
//	i = 0;
//	if (!no_space || no_space[i] == '\0')
//	{
//		free(no_space);
//		return (0);
//	}
//	if (no_space[i] == '-')
//		i++;
//	while (no_space[i] != '\0')
//	{
//		if (no_space[i] < '0' || no_space[i] > '9')
//		{
//			free(no_space);
//			return (0);
//		}
//		i++;
//	}
//	free(no_space);
//	return (1);
//}

int	ft_iswhitespace(char c)
{
	return (c == '\t' || c == '\n' || c == ' ' || c == '\v' || c == '\f'
			|| c == '\r');
}
//
//long	ft_atol(const char *str)
//{
//	unsigned long	result;
//	int				i;
//	int				sign;
//
//	i = 0;
//	result = 0;
//	sign = 1;
//	while (ft_iswhitespace(str[i]))
//		i++;
//	if (str[i] == '-')
//		sign *= -1;
//	if (str[i] == '-' || str[i] == '+')
//		i++;
//	while (str[i] >= '0' && str[i] <= '9')
//	{
//		result = result * 10 + str[i] - '0';
//		i++;
//		if (result > 9223372036854775807 && sign == -1)
//			return (0);
//		else if (result > 9223372036854775807 && sign == 1)
//			return (-1);
//	}
//	return (sign * result);
//}

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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

//int			ft_ispositive_number(char *str)
//{
//	int		i;
//	char	*no_space;
//	char	*white_spaces;
//
//	white_spaces = " \t\n\v\f\r";
//	no_space = ft_strtrim(str, white_spaces);
//	i = 0;
//	if (!no_space || no_space[i] == '\0')
//	{
//		free(no_space);
//		return (0);
//	}
//	while (no_space[i] != '\0')
//	{
//		if (no_space[i] < '0' || no_space[i] > '9')
//		{
//			free(no_space);
//			return (0);
//		}
//		i++;
//	}
//	free(no_space);
//	return (1);
//}
//
//int map_data_to_int(char *str)
//{
//	long data;
////	if (!ft_isnumber(str))
////		print_error("Argument is not a number");
//	data = ft_atol(str);
//	if (data > INT_MAX || data < INT_MIN)
//		print_error("Argument is not correct for an integer value");
//	return ((int)data);
//}





//int main(void)
//{
//	char *str = "-10`.tg23556$#";
//	printf("miio %d\n", ft_is_pos_number(str));
//	printf("real %d\n", atoi(str));
//	return 0;
//}