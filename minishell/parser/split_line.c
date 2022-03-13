#include "../minishell.h"

static int	ft_quotes(char *line)
{
	size_t	i;
	int	flag;

	i = 1;//чтоб начать со селд символа после кавычки
	if (*line == '\'')
		flag = 0;
	else if (*line == '"')
		flag = 1;
	while (((line[i] != '"' && flag == 1) || (line[i] != '\'' && flag == 0)) && line[i])
		i++;
	if (!line[i])
		return (i - 1);
	return (i);
}

static int ft_red(char **line)
{
	size_t	i;

	i = 1;
	while ((*line)[i] && ((*line)[i] == '>' || (*line)[i] == '<' || ((*line)[i] > 9 && (*line)[i] < 13) || (*line)[i] == ' '))
	{
		if ((*line)[i] == '\'' || (*line)[i] == '"')
			i += (ft_quotes((*line) + i));
		i++;
	}
	while ((*line)[i] && (*line)[i] != '|')
	{
		if ((*line)[i] == '\'' || (*line)[i] == '"')
			i += (ft_quotes((*line) + i));
		if (((*line)[i] == '>' || (*line)[i] == '<' || ((*line)[i] > 9 && (*line)[i] < 13) || (*line)[i] == ' '))
			break ;
		i++;
	}
	return (i);
}

static char *sub_split_line(char **line)
{
	size_t	i;
	char	*str;

	i = 0;
	while ((*line)[i])
	{
		if (((*line)[i] == ' ' || ((*line)[i] > 9 && (*line)[i] < 13)))
			break ;
		if ((*line)[i] == '\'' || (*line)[i] == '"')//если встретил кавычки
			i += (ft_quotes((*line) + i));
		if (((*line)[i] == '>' || (*line)[i] == '<') && i == 0)
		{
			i += ft_red(line);
			break ;
		}
		else if (((*line)[i] == '>' || (*line)[i] == '<') && i != 0)//если редирект был после аргумента
			break ;
		i++;
		if ((*line)[i] == '|')
			break ;
	}
	str = ft_strndup(*line, i);
	*line += i;
	return (str);
}

int 	split_line(char *line, t_mini *mini)//загонять результат в t_list для дальнейшего парсинга
{
	char	*str;//для проверки
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*line)
	{
		while (*line == ' ' || (*line > 9 && *line < 13))
			line++;
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		if (*line == '\0' && i == 0 && j == 0)//если пустая строка(условие после while и эта посмотреть почему одно не отрабатывает перед другим)
			return (SUCCESS);
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
		else if (i == 0 && j == 0 && *line)
		{
			mini->pars = init_pars();
			if (!mini->pars)
				return (ERROR);
			mini->head_pars = mini->pars;//заполняю голову списка парс
		}
		if (*line == '|' && i != 0)//если пайп
		{
			line++;
			while (*line == ' ' || (*line > 9 && *line < 13))
				line++;
			if (!*line)//если после пайпа ничего не было
				return (ERROR);
			i = 0;
			mini->pars->chunk = mini->pars->head_chunk;
			// mini->pars->next = malloc(sizeof(t_pars));
			// mini->pars = mini->pars->next;
			mini->pars->next = init_pars();
			if (!mini->pars->next)
				return (ERROR);
			mini->pars = mini->pars->next;
			j++;
		}
		if (*line == '|' && i == 0)// если до пайпа ничего не было
			return (ERROR);
		str = sub_split_line(&line);
		if (str == NULL)
			return (ERROR);
		if (i == 0)//если первая итерация сохраняю голову листа
		{
			mini->pars->chunk = ft_lstnew(str);
			mini->pars->head_chunk = mini->pars->chunk;
		}
		else
		{
			mini->pars->chunk->next = ft_lstnew(str);
			mini->pars->chunk = mini->pars->chunk->next;
		}
		if (!mini->pars->chunk)
			return (ERROR);
		mini->pars->chunk->next = NULL;
		while (*line == ' ' || (*line > 9 && *line < 13))
			line++;
		i++;
	}
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (j != 0 || i != 0)//на тот случай если пустая строка
	{
		mini->pars->chunk = mini->pars->head_chunk;
		mini->pars = mini->head_pars;
	}
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	return (SUCCESS);
}
