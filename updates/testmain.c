/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:58:30 by mryan             #+#    #+#             */
/*   Updated: 2021/06/30 14:53:11 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int main()
{
	char *pathEnvVar;
	register char *thePath;
	char **path_array;
	char *path;
	int i;
	
	path_array = (char **)malloc(ARG_MAX);
	i = 0;
	//pathEnvVar = calloc(255, sizeof(char));
	//pathEnvVar = getenv("PATH");
	pathEnvVar = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Frameworks/Mono.framework/Versions/Current/Commands";
	if(pathEnvVar)
    	printf("The current path is: %s\n", pathEnvVar);
	
	thePath = (char *)malloc(strlen(pathEnvVar) + 1);
    strcpy(thePath, pathEnvVar);

	path = pathEnvVar;
	if (thePath)
	{
		while (thePath++)
		{
			if (*thePath == ':' || *thePath == '\0') // /?
			{
				path_array[i] = path;
				printf("%s\n", path_array[i]);
				i++;
				if (*thePath == '\0')
					break ;
				*thePath = '\0';
				path = thePath + 1;
			}
		}
	}
	return (0);
}