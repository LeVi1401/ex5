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

char* getInput();
void deleteSong(int i, Song** songs, int songsNum);
void addSong(Song* s);
void showPlaylist(Playlist pl);
void playSong(Song* song);
void freeSong(Song* song);
void freePlaylist(Playlist* playlist);
void freeAll(Playlist* playlists, int numOfPlaylists);
void printPlaylistsMenu();
void printPlaylistMenu();
void printAllPlaylists(Playlist* pl, int numOfPlaylists);
void removePlaylist(int index, Playlist* playlists, int playlistsNum);
void playAll(Playlist* playlist);
void sortPlaylist(Playlist* playlist, int sort);
void sortByYear(Playlist* playlist);
void sortStreamsAscending(Playlist* playlist);
void sortStreamsDescending(Playlist* playlist);
void sortAlphabetically(Playlist* playlist);


int main() {
    int choice, numOfPlaylists = 0;
    Playlist* playlists = (Playlist*)calloc(1,sizeof(Playlist));
    if(playlists == NULL){printf("malloc failed"); exit(1);}

    do
    {
        printPlaylistsMenu();
        if (scanf("%d", &choice))
        {
            scanf("%*[^\n]%*c");
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
                            Playlist* pl = &playlists[chosenPl - 1];
                            printf("playlist %s:\n", pl->name);

                            do
                            {
                                printPlaylistMenu();
                                if (scanf("%d", &action))
                                {
                                    switch (action)
                                    {
                                        case 1:
                                            {
                                                int chosenSong = 0;
                                                showPlaylist(*pl);
                                                printf("choose a song to play, or 0 to quit:\n");
                                                scanf("%d", &chosenSong);
                                                while(chosenSong != 0)
                                                {
                                                    if(chosenSong > pl->songsNum)
                                                    {
                                                        printf("Invalid option\n");
                                                        break;
                                                    }
                                                    playSong(pl->songs[chosenSong - 1]);
                                                    printf("choose a song to play, or 0 to quit:\n");
                                                    scanf("%d", &chosenSong);
                                                }
                                                break;
                                            }
                                        case 2:
                                            {
                                                Song* song = malloc(sizeof(Song));
                                                if(song == NULL){printf("malloc failed"); exit(1);}
                                                addSong(song);
                                                pl->songs = realloc(pl->songs, (pl->songsNum + 1) * sizeof(Song*));
                                                if(pl->songs == NULL){printf("malloc failed"); exit(1);}
                                                *(pl->songs + pl->songsNum) = song;
                                                pl->songsNum++;
                                                break;
                                            }
                                        case 3:
                                            {
                                                int chosenSong = 0;
                                                showPlaylist(*pl);
                                                printf("choose a song to delete, or 0 to quit:\n");
                                                scanf("%d", &chosenSong);
                                                if(chosenSong == 0)
                                                    break;
                                                deleteSong(chosenSong - 1 , pl->songs, pl->songsNum);
                                                pl->songsNum--;
                                                pl->songs = realloc(pl->songs, (pl->songsNum) * sizeof(Song*));
                                                if(pl->songs == NULL){printf("malloc failed"); exit(1);}
                                                break;
                                            }
                                        case 4:
                                            {
                                                int sort = 0;
                                                printf("choose:\n1. sort by year\n2. sort by streams - ascending order"
                                                             "\n3. sort by streams - descending order\n4. sort alphabetically\n");
                                                scanf("%d", &sort);
                                                sortPlaylist(pl, sort);
                                                break;
                                            }
                                        case 5:
                                            {
                                                playAll(pl);
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
                        Playlist* pl = malloc(sizeof(Playlist));
                        pl->songs = (Song**)malloc(sizeof(Song*));
                        if(pl->songs == NULL){printf("malloc failed"); exit(1);}
                        pl->songsNum = 0;
                        pl->name = NULL;
                        printf("Enter playlist's name:\n");
                        pl->name = getInput();
                        playlists = realloc(playlists, (numOfPlaylists + 1) * sizeof(Playlist));
                        if(playlists == NULL){printf("malloc failed"); exit(1);}
                        playlists[numOfPlaylists] = *pl;
                        numOfPlaylists++;
                        break;
                    }
                case 3:
                    {
                        int chosenPl = 0;
                        printAllPlaylists(playlists, numOfPlaylists);
                        scanf("%d", &chosenPl);
                        if (chosenPl <= 0 || chosenPl > numOfPlaylists + 1)
                        {
                            printf("Invalid option\n");
                            break;
                        }
                        if(chosenPl == numOfPlaylists + 1)
                            break;
                        removePlaylist(chosenPl - 1, playlists, numOfPlaylists);
                        numOfPlaylists--;
                        if(numOfPlaylists == 0)
                            break;
                        playlists = realloc(playlists, numOfPlaylists * sizeof(Playlist));
                        if(playlists == NULL){printf("malloc failed"); exit(1);}
                        break;
                    }
                case 4:
                    {
                        freeAll(playlists, numOfPlaylists);
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

}


char* getInput()
{
    char* input = malloc(sizeof(char));
    if(input == NULL){printf("malloc failed"); exit(1);}

    char temp;
    int i = 1;

    scanf(" %c", &temp);
    *(input) = temp;
    while(scanf("%c", &temp) && temp != '\n')
    {
        input = realloc(input, ++i);
        if(input == NULL){printf("malloc failed"); exit(1);}
        *(input + (i - 1)) = temp;
    }
    input = realloc(input, i + 1);
    if(input == NULL){printf("malloc failed"); exit(1);}
    *(input + i) = '\0';

    return input;
}

void deleteSong(int index, Song** songs, int songsNum)
{
    freeSong(songs[index]);
    for(int i = index; (i + 1) < songsNum ; i++)
    {
        songs[i] = songs[i + 1];
    }
    printf("Song deleted successfully.\n");
}

void addSong(Song* s)
{
    printf("Enter song's details\n");
    printf("Title:\n");
    s->title = getInput();
    printf("Artist:\n");
    s->artist = getInput();
    printf("Year of release:\n");
    scanf("%d", &s->year);
    printf("Lyrics:\n");
    s->lyrics = getInput();
    s->streams = 0;
}

void showPlaylist(Playlist pl)
{
    for(int i = 0 ; i < pl.songsNum ; i++)
    {
        printf("%d. Title: %s\n   Artist: %s\n   Released: %d\n   Streams: %d\n\n",
            i + 1, pl.songs[i]->title, pl.songs[i]->artist, pl.songs[i]->year, pl.songs[i]->streams);
    }
}

void playSong(Song* song)
{
    printf("Now playing %s:\n", song->title);
    printf("$ %s $\n", song->lyrics);
    song->streams++;
}


void freeSong(Song* song)
{
    free(song->title);
    song->title = NULL;
    free(song->artist);
    song->artist = NULL;
    free(song->lyrics);
    song->lyrics = NULL;
    free(song);
    song = NULL;
}

void freePlaylist(Playlist* playlist)
{
    free(playlist->name);
    playlist->name = NULL;
    for(int i = 0 ; i < playlist->songsNum ; i++)
    {
        freeSong(playlist->songs[i]);
    }
    free(playlist->songs);
    playlist->songs = NULL;
}

void freeAll(Playlist* playlists, int numOfPlaylists)
{
    for(int i = numOfPlaylists - 1 ; i >= 0 ; i--)
    {
        freePlaylist(playlists + i);
    }
    free(playlists);
    playlists = NULL;
}

void printPlaylistsMenu() {
    printf("Please Choose:\n");
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
}

void printPlaylistMenu()
{
    printf("\t1. Show Playlist\n\t2. Add Song\n\t3. Delete Song\n\t4. Sort\n\t5. Play\n\t6. exit\n");
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

void removePlaylist(int index, Playlist* playlists, int playlistsNum)
{
    freePlaylist(&playlists[index]);
    for(int i = index ; (i + 1) < playlistsNum ; i++)
    {
        playlists[i] = playlists[i + 1];
    }
    printf("Playlist deleted.\n");
}

void playAll(Playlist* playlist)
{
    for(int i = 0 ; i < playlist->songsNum ; i++)
    {
        playSong(playlist->songs[i]);
        printf("\n");
    }
}

void sortPlaylist(Playlist* playlist, int sort)
{
    switch(sort)
    {
        case 1:
            {
                sortByYear(playlist);
                break;
            }
        case 2:
            {
                sortStreamsAscending(playlist);
                break;
            }
        case 3:
            {
                sortStreamsDescending(playlist);
                break;
            }
        default:
            sortAlphabetically(playlist);
    }
    printf("sorted\n");
}
void sortByYear(Playlist* playlist)
{
    Song* temp = NULL;
    for(int i = 0 ; i < playlist->songsNum - 1 ; i++)
    {
        for (int j = 0 ; j < playlist->songsNum - 1 - i ; j++)
        {
            //swaps of the next song's year is bigger
            if(playlist->songs[j]->year > playlist->songs[j + 1]->year)
            {
                temp = playlist->songs[j];
                playlist->songs[j] = playlist->songs[j + 1];
                playlist->songs[j + 1] = temp;
            }
        }
    }
}

void sortStreamsAscending(Playlist* playlist)
{
    Song* temp = NULL;
    for(int i = 0 ; i < playlist->songsNum - 1 ; i++)
    {
        for (int j = 0 ; j < playlist->songsNum - 1 - i ; j++)
        {
            //swaps if the next song has more streams
            if(playlist->songs[j]->streams > playlist->songs[j + 1]->streams)
            {
                temp = playlist->songs[j];
                playlist->songs[j] = playlist->songs[j + 1];
                playlist->songs[j + 1] = temp;
            }
        }
    }
}

void sortStreamsDescending(Playlist* playlist)
{
    Song* temp = NULL;
    for(int i = 0 ; i < playlist->songsNum - 1 ; i++)
    {
        for (int j = 0 ; j < playlist->songsNum - 1 - i ; j++)
        {
            //swaps if the next song has fewer streams
            if(playlist->songs[j]->streams < playlist->songs[j + 1]->streams)
            {
                temp = playlist->songs[j];
                playlist->songs[j] = playlist->songs[j + 1];
                playlist->songs[j + 1] = temp;
            }
        }
    }
}

void sortAlphabetically(Playlist* playlist)
{
    Song* temp = NULL;
    for(int i = 0 ; i < playlist->songsNum - 1 ; i++)
    {
        for (int j = 0 ; j < playlist->songsNum - 1 - i ; j++)
        {
            //swaps if the current song appears before the next song alphabetically
            if(strcmp(playlist->songs[j]->title, playlist->songs[j + 1]->title) > 0)
            {
                temp = playlist->songs[j];
                playlist->songs[j] = playlist->songs[j + 1];
                playlist->songs[j + 1] = temp;
            }
        }
    }
}