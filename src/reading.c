
#include "../fdf.h"

int	valid_file(const char *filename)
{
	int fd;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (0);
	}
	close (fd);
	return (1);
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

