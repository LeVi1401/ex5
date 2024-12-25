#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;

typedef struct Playlist {
    char* name;
    Song** songs;
    int songsNum;
} Playlist;

char* getInput()
{
    char* input = (char*)malloc(sizeof(char));
    if(input == NULL){free(input); return NULL;}

    char temp;
    int i = 1;

    scanf(" %c", &temp);
    *(input) = temp;
    while(scanf("%c", &temp) && temp != '\n')
    {
        input = realloc(input, ++i);
        *(input + (i - 1)) = temp;
    }
    input = realloc(input, i + 1);
    *(input + i) = '\0';

    return input;
}

//some recommendations for functions, you may implement however you want

void deleteSong() {

    printf("Song deleted successfully.\n");
}

Song* addSong(Song* s)
{
    Song* newSong = (Song*)calloc(1, sizeof(Song));
    printf("Enter song's details\n");
    printf("Title:\n");
    s->title = getInput();
    printf("Artist:\n");
    s->artist = getInput();
    printf("Year of release:\n");
    scanf("%d", &s->year);
    printf("Lyrics:\n");
    s->lyrics = getInput();

    newSong = s;
    return newSong;
}

void showPlaylist(Playlist pl)
{
    for(int i = 0 ; i < pl.songsNum ; i++)
    {
        printf("%d. Title: %s\n   Artist: %s\n   Released: %d\n   Streams: %d\n\n",
            i + 1, pl.songs[i]->title, pl.songs[i]->artist, pl.songs[i]->year, pl.songs[i]->streams);
    }
}

void playSong() {
    
}



void freeSong() {

}

/*void freePlaylist(P) {
    
}*/

void printPlaylistsMenu() {
    printf("Please Choose:\n"); 
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");   
}

void printPlaylistMenu()
{
    printf("\t1. Show Playlist\n\t2. Add Song\n\t3. Delete Song\n\t4. Sort\n\t5. Play\n\t6. exit\n");
}



void sortPlaylist() {
    
    printf("sorted\n");
}

void printAllPlaylists(Playlist* pl, int numOfPlaylists)
{
    printf("Choose a playlist:\n");
    for(int i = 0 ; i < numOfPlaylists ; i++)
    {
        printf("\t%d. %s\n", i + 1, (pl + i)->name);
    }
    printf("\t%d. Back to main menu\n", numOfPlaylists + 1);
}

int main() {
    int choice, numOfPlaylists = 0;
    Playlist* playlists = (Playlist*)calloc(1,sizeof(Playlist));
    if(playlists == NULL){return 1; free(playlists);}
    do
    {
        printPlaylistsMenu();
        if (scanf("%d", &choice))
        {
            switch (choice)
            {
                case 1:
                    {
                        int chosenPl = 0, action = 0;
                        printAllPlaylists(playlists, numOfPlaylists);
                        scanf("%d", &chosenPl);
                        if (chosenPl <= 0 || chosenPl > numOfPlaylists + 1)
                        {
                            printf("Invalid option\n");
                            break;
                        }
                        while(chosenPl != numOfPlaylists + 1)
                        {
                            Playlist pl = playlists[chosenPl - 1];
                            printf("playlist %s:\n", pl.name);
                            do
                            {
                                printPlaylistMenu();
                                if (scanf("%d", &action))
                                {
                                    switch (action)
                                    {
                                        case 1:
                                            {
                                                showPlaylist(pl);
                                                break;
                                            }
                                        case 2:
                                            {
                                                Song song = {NULL, NULL, 0, NULL, 0};
                                                Song* spt = addSong(&song);
                                                pl.songs = realloc(pl.songs, (pl.songsNum + 1) * sizeof(Song*));
                                                *(pl.songs + pl.songsNum) = spt;
                                                pl.songsNum++;
                                                break;
                                            }
                                        case 3:
                                            {
                                                break;
                                            }
                                        case 4:
                                            {
                                                break;
                                            }
                                        case 5:
                                            {
                                                break;
                                            }
                                        case 6:
                                            {
                                                break;
                                            }
                                        default:
                                            {
                                                printf("Invalid option\n");
                                                action = 0;
                                                break;
                                            }
                                    }
                                }

                            }while(action != 6);
                            printAllPlaylists(playlists, numOfPlaylists);
                            scanf("%d", &chosenPl);
                            if (chosenPl <= 0 || chosenPl > numOfPlaylists + 1)
                            {
                                printf("Invalid option\n");
                                break;
                            }
                        }

                        break;
                    }
                case 2:
                    {
                        Playlist pl = {NULL, NULL, 0};
                        pl.songs = (Song**)malloc(sizeof(Song*));
                        pl.songsNum = 0;
                        pl.name = NULL;
                        printf("Enter playlist's name:\n");
                        pl.name = getInput();
                        playlists[numOfPlaylists++] = pl;
                        break;
                    }
                case 3:
                    {
                        break;
                    }
                case 4:
                    {
                        printf("Goodbye!\n");
                        break;
                    }
                default:
                    {
                        printf("Invalid option\n");
                        choice = 0;
                        break;
                    }
            }
        }
    } while (choice != 4);
    free(playlists);

}
