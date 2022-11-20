#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "thead.h"

void	print(char c)
{
	write(1, &c, 1);
}

void	printstr(char *c)
{
	int i;

	i = 0;
	while (c[i])
	{
		print(c[i++]);
	}
}

void	print_struct(char *c)
{
	int	i;
	Tuple	tab;

	i = 0;
	while (tab.a[i])
	{
		printstr(tab.a[i]);
		printstr(" : ");
		printstr(tab.b[i++]);
		printstr(" , ");
	}
}

int	size_str(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		i++;
	}
	return (i);
}

int	is_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
	
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;
	char	*c;

	c = malloc(sizeof(char)*size_str(dest) + 1);
	i = 0;
	while (dest[i] != '\0')
	{
		c[i] = dest[i];
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		if (is_alpha(src[j]) == 1)
		{
			c[i + j] = src[j];
		}
		j++;
	}
	c[i + j] = '\0';
	return (c);
}

char	*ft_tab(int size, char *dic)
{
	int	i;
	int	j;
	int	fd_to_read;
	char	*temp;
	char	c;
	Tuple tab;

	i = 0;
	j = 0;
	temp = "";
	fd_to_read = open(dic, O_RDONLY);
	while ((read(fd_to_read, &c, sizeof (char))) > 0)
	{
		if (c == ':')
		{
			tab.a[i] = temp;
			temp = "";			
			j = 1;
		}
		else if (c == '\n')
		{
			tab.b[i] = temp;
			temp = "";
			i++;
			j = 0;
		}
		else
		{
			temp = ft_strcat(temp, &c);
		}
	}
	close(fd_to_read);

/*
	i = 0;
	while (i < size)
	{
		printstr(tab1[i]);
		printstr(tab2[i]);
		i++;
	}*/
	return (temp);
}

int	ft_nb_line(char *dic)
{
	int	fd_to_read;
	int	i;
	char	c;

	i = 0;
	fd_to_read = open(dic, O_RDONLY);
	while ((read(fd_to_read, &c, sizeof (char))) > 0)
	{
		if (c == '\n')
			i++;
	}
	close(fd_to_read);
	return (i);
}

int	main(int argc, char **argv)
{
	int	nb_line;
	char	*dic;
	Tuple	tab;

	if (argc == 2)
	{
		dic = "numbers.dict";
		nb_line = ft_nb_line(dic);
		ft_tab(nb_line,dic);
		print_struct(argv[1]);
	}
	else if (argc == 3)
	{
		dic = argv[1];
		nb_line = ft_nb_line(dic);
		ft_tab(nb_line,dic);
		print_struct(argv[2]);
	}
	else
	{
	}
}
