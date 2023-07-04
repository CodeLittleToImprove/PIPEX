/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:12:59 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/03/13 17:15:18 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: split string, with specified character as delimiter, into an array
**			of strings
**
** DESCRIPTION:
** 		Allocates (with malloc(3)) and returns an array of strings obtained by
**	splitting ’s’ using the character ’c’ as a delimiter. The array must be
**	ended by a NULL pointer.
*/

#include "libft.h"

static	size_t	ft_count_word(char const *s, char c)
{
	int	i;
	int	word_counter;

	i = 0;
	word_counter = 0;
	while (s != 0 && s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			word_counter++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (word_counter);
}

static	size_t	ft_word_size(char const *s, char c)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		size++;
		i++;
	}
	return (size);
}

static	void	ft_free(char **strarray, size_t array_index)
{
	while (array_index-- > 0)
		free(strarray[array_index]);
	free(strarray);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_counter;
	char	**strarray;
	size_t	array_index;

	word_counter = ft_count_word(s, c);
	array_index = 0;
	strarray = (char **)malloc((word_counter + 1) * sizeof(char *));
	if (!strarray)
		return (0);
	while (word_counter--)
	{
		while (*s == c)
			s++;
		strarray[array_index] = ft_substr(s, 0, ft_word_size(s, c));
		if (!strarray[array_index])
		{
			ft_free(strarray, array_index);
			return (0);
		}
		array_index++;
		s += ft_word_size(s, c);
	}
	strarray[array_index] = 0;
	return (strarray);
}

// int	main(void)
// {
// 	char	*s = "  tripouille  42  ";
// 	char	c = ' ';

// 	char **str_array = ft_split(s, c);
// 	if (str_array == NULL)
// 	{
// 		printf("Memory allocation failed\n");
// 		return (1);
// 	}

// 	int	i = 0;
// 	while (str_array[i] != NULL)
// 	{
// 		printf("%s\n", str_array[i]);
// 		i++;
// 	}

// 	// Don't forget to free the memory allocated by ft_split
// 	i = 0;
// 	while (str_array[i] != NULL)
// 	{
// 		free(str_array[i]);
// 		i++;
// 	}
// 	free(str_array);

//     return 0;
// }
