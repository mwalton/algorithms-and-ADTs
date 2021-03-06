/*
 * findBooks.c
 *
 *  	Michael Walton
 * 		mwwalton@ucsc.edu
 */

#include "hashtbl.h"
#include "util.h"

int main(int argc, char **argv) {
    FILE *libFile;
    FILE *reqFile;
    char str[60];
    char *token;

    int *libBuffer;
    String *titleBuffer;

    int nLibraries;

    int nReqs;

    HashTable bookTable;
    float loadFactor = .75;
    unsigned long nBuckets;

    /*
     * validate arguments
     */
    if (argc < 2) {
        perror("Please specify a library file & request file\n");
        return (-1);
    }

    if (argc < 3) {
        perror("Please specify a request file\n");
        return (-1);
    }
    
    libFile = fopen(argv[1], "r");
    if (libFile == NULL) {
        perror("Could not open library file");
        return (-1);
    }

    reqFile = fopen(argv[2], "r");
    if (reqFile == NULL) {
        perror("Could not open request file");
        return (-1);
    }

    /*
     * read library file
     */

    fgets(str, 60, libFile);
    strtok(str, "\n");
    token = strtok(str, " ");
    nLibraries = atoi( token );

    nBuckets = nLibraries / loadFactor;
    bookTable = newHashTbl( nBuckets );
    libBuffer = malloc( nLibraries * sizeof( int ) );
    titleBuffer = malloc( nLibraries * sizeof( char*));

   // printf("Number of entries: %d, Number of Books: %d\n", nLibraries, nBooks);

    /*
     * build hashtable
     */
    for (int i = 0; i < nLibraries; ++i ) {
        fgets (str, 60, libFile);
        strtok(str, "\n");
        token = strtok(str, ",");
        libBuffer[i] = atoi( str );

        String tmpTitle = strstrip( strtok(NULL, ",") );
       // printf("Inserting Key: %s [%d]\n", tmpTitle, libBuffer[i]);

        titleBuffer[i] = (String) malloc( 60 * sizeof(char));
        strcpy(titleBuffer[i], tmpTitle);

        insertKey( bookTable, titleBuffer[i], &libBuffer[i]);
    }

    fclose (libFile);
    //printTable( stdout, bookTable);


    /*
     * read request file and print results
     */
    fgets(str, 60, reqFile);
    strtok(str, "\n");
    nReqs = atoi( str );

    for (int i = 0; i < nReqs; i++) {
        fgets(str, 60, reqFile);
        strtok(str, "\n");
        
        BookHndl book = find(bookTable, str);
        if ( book == NULL) {
            fprintf(stdout, "\n");
        } else {
            ListHndl libs = getLibraryList( book );
            moveLast( libs );
            while( !offEnd( libs )) {
                fprintf(stdout, "%d ", *(int*)getCurrent( libs ));
                movePrev( libs );
            }
            fprintf(stdout, "\n");
        }
    }


    fclose (reqFile);


    free( libBuffer );
    freeHashTbl( bookTable );

    for (int i = 0; i < nLibraries; i++) {
        free( titleBuffer[i] );
    }

    free(titleBuffer);

    return (0);
}
