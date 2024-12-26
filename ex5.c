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
void freeAll(Playlist** playlists, int numOfPlaylists);
void printPlaylistsMenu();
void printPlaylistMenu();
void sortPlaylist();
void printAllPlaylists(Playlist* pl, int numOfPlaylists);
void removePlaylist(int index, Playlist* playlists, int playlistsNum);


int main() {
    int choice, numOfPlaylists = 0;
    Playlist* playlists = (Playlist*)calloc(1,sizeof(Playlist));
    if(playlists == NULL){printf("malloc failed"); exit(1);}

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
                                                int chosenSong = 0;
                                                showPlaylist(pl);
                                                printf("choose a song to play, or 0 to quit:\n");
                                                scanf("%d", &chosenSong);
                                                while(chosenSong != 0)
                                                {
                                                    if(chosenSong > pl.songsNum)
                                                    {
                                                        printf("Invalid option\n");
                                                        break;
                                                    }
                                                    playSong(pl.songs[chosenSong - 1]);
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
                                                pl.songs = realloc(pl.songs, (pl.songsNum + 1) * sizeof(Song*));
                                                if(pl.songs == NULL){printf("malloc failed"); exit(1);}
                                                *(pl.songs + pl.songsNum) = song;
                                                pl.songsNum++;
                                                break;
                                            }
                                        case 3:
                                            {
                                                int chosenSong = 0;
                                                showPlaylist(pl);
                                                printf("choose a song to delete, or 0 to quit:\n");
                                                scanf("%d", &chosenSong);
                                                if(chosenSong == 0)
                                                    break;
                                                deleteSong(chosenSong - 1 , pl.songs, pl.songsNum);
                                                pl.songsNum--;
                                                pl.songs = realloc(pl.songs, (pl.songsNum) * sizeof(Song*));
                                                if(pl.songs == NULL){printf("malloc failed"); exit(1);}
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
    free(song->artist);
    free(song->lyrics);
    free(song);
}

void freePlaylist(Playlist* playlist) {
    free(playlist->name);
    for(int i = 0 ; i < playlist->songsNum ; i++)
    {
        freeSong(playlist->songs[i]);
    }
    free(playlist->songs);
}

void freeAll(Playlist** playlists, int numOfPlaylists)
{
    for(int i = 0 ; i < numOfPlaylists ; i++)
    {
        freePlaylist(playlists[i]);
    }
    free(playlists);
}

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

void removePlaylist(int index, Playlist* playlists, int playlistsNum)
{
    freePlaylist(&playlists[index]);
    for(int i = index ; (i + 1) < playlistsNum ; i++)
    {
        playlists[i] = playlists[i + 1];
    }
    printf("Playlist deleted.\n");
}