#include "netfile.h"

int netfile_write(char *data)
{
    FILE *file = fopen(RESPONSE_FILE, "w");
    if(file == NULL){
        return 0;
    }
    
    fprintf(file, data);
    fclose(file);
    
    return 1;
}

char *netfile_read()
{
    
    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen ( REQUEST_FILE , "rb" );

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

    /* allocate memory for entire content */
    buffer = calloc( 1, lSize+1 );
    if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr);

    /* copy the file into the buffer */
    if( 1!=fread( buffer , lSize, 1 , fp) )
        fclose(fp),free(buffer),fputs("entire read fails",stderr);

    fclose(fp);
    
    return buffer;
}