#include "cub3d.h"

int switchParams(t_vars *v, char *param, t_list **head)
{
	char	*tmp;
	unsigned int 	tmpint;
	char	*p;

	if (ft_strncmp(param, "R", 1) == 0 && param[1] == ' ')
		return (parseWindowSize(v, head));
	if (((ft_strncmp(param, "NO", 2) == 0 || ft_strncmp(param, "SO", 2) == 0 
		|| ft_strncmp(param, "WE", 2) == 0 || ft_strncmp(param, "EA", 2) == 0)
		&& param[2] == ' ') || (ft_strncmp(param, "S ", 2) == 0))
	{
		p = ft_strdup(param);
		if (!parseOneTexture(head, &tmp))
			return (0);
		switchTexture(v, &p, &tmp);
	}
	else if (ft_strncmp(param, "F", 1) == 0 && param[1] == ' ')
	{
		if (!(parseOneColors(head,"F", &tmpint)))
			return (0);
		v->F = tmpint;
	}	
	else if (ft_strncmp(param, "C", 1) == 0 && param[1] == ' ')
	{
		if (!(parseOneColors(head,"C", &tmpint)))
			return (0);
		v->C = tmpint;
	}
	else{
		return (errors("Invalid parameter name", NULL));
	}
	return (1);
}

int parseLines(t_list **head, t_vars *v)
{
	int i;
	char **tmp;
	int count;

	count = 8;
	while (*head && count > 0)
	{
		i = 0;
		while (*((char *)(*head)->content + i) 
			&& *((char *)(*head)->content + i) == ' ')
			i++;
		if (!(*((char *)(*head)->content + i)))
			if(!nextLine(head))
				return (errors("Invalid number of parameters)", NULL));
		if (!switchParams(v, (*head)->content + i, head))
			return (0);
		count--;
	}
	if (count == 0)
		return (1);
	return (0);
}



int	parseFile(char *name_of_file, t_vars *v)
{
	int	fd;
	char	  *line = NULL;
	t_list	*head = NULL;

	fd = open(name_of_file, O_RDONLY);
	if (fd < 0)
		return (errors("File .cub was not found", NULL));
	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	if (!parseLines(&head, v))
		return (0);
	if (!parseMap(v, &head))
		return (0);
	return (1);
}