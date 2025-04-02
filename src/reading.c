
#include "../fdf.h"

int	file_lenght(const char *filename)
{
	int fd;
	int	len;
	char	*str;

	len = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return(0);
	str = get_next_line(fd);
	while (str)
	{
		++len;
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
	return (len);
}

int	valid_file(const char *filename)
{
	int	fd;

	if (!(ft_strlen(filename) > 4 && \
	ft_strncmp(filename + (ft_strlen(filename) - 4), ".fdf", 4) == 0))
		return (0);
	fd = open(filename, O_RDONLY);
	if (!fd)
		return (0);
	if (file_lenght(filename) > 0)
		return (1);
	return (0);
}

int get_map_name(t_data *data, const char *mapname)
{
	size_t	slen;
	int	i;

	i = 0;
	slen = ft_strlen(mapname);
	data->line_reader.mapname = malloc((slen + 1) * sizeof(char));
	if (!data->line_reader.mapname)
	{
		perror("Error allocating memory for the map name");
		return (1);
	}
	while (mapname[i] != '\0')
	{
		data->line_reader.mapname[i] = mapname[i];
		i++;
	}
	data->line_reader.mapname[i] = '\0';
	return (0);
}

