
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fts.h>
#include <string.h>
#include <errno.h>

#include "ftree_matcher.h"

int compare (const FTSENT**, const FTSENT**);

int ftree_matcher_match(char* const* path_list)
{
    FTS* file_system = NULL;
    FTSENT *node = NULL;

    file_system = fts_open(path_list,FTS_COMFOLLOW|FTS_NOCHDIR|FTS_LOGICAL,&compare);

    if (NULL == file_system)
    {
        return 0;
    }

    while( (node = fts_read(file_system)) != NULL)
    {
        if(node->fts_info == FTS_F){
            // DO MAGIC HERE
            printf("walking: %s\n", node->fts_path);
        }
    }

    fts_close(file_system);
    return 0;
}

int compare(const FTSENT** one, const FTSENT** two)
{
    return (strcmp((*one)->fts_name, (*two)->fts_name));
}
