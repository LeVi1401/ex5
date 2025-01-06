#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************
name: Roei Lev
id: 216015164
*************/

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

//inputs a string saves it in the heap and returns it's address
char* getInput();
//delete a song from a playlist's array
void deleteSong(int i, Song** songs, int songsNum);
//fills the song's content
void addSong(Song* s);
//prints all the songs in a playlist as requested
void showPlaylist(Playlist pl);
//plays a single song
void playSong(Song* song);
//frees a song and it's content
void freeSong(Song** song);
//frees a playlist and all its content (using freeSong)
void freePlaylist(Playlist* playlist);
//frees all the playlists in the main playlists array (using freePlaylist)
void freeAll(Playlist** playlists, int numOfPlaylists);
//prints the first menu (the main one)
void printPlaylistsMenu();
//prints the action menu for a specific playlist
void printPlaylistMenu();
//prints the sub menu for choosing a playlist
void printAllPlaylists(Playlist** pl, int numOfPlaylists);
//removes a playlist from the main playlists array
void removePlaylist(int index, Playlist** playlists, int numOfPlaylists);
//plays all the songs in a playlist (using playSong)
void playAll(Playlist* playlist);
//sorts a playlist depending on the chosen method
void sortPlaylist(Playlist* playlist, int sort);
//sorts a playlist by year
void sortByYear(Playlist* playlist);
//sorts a playlist by streams (ascending)
void sortStreamsAscending(Playlist* playlist);
//sorts a playlist by streams (descending)
void sortStreamsDescending(Playlist* playlist);
//sorts a playlist alphabetically
void sortAlphabetically(Playlist* playlist);


int main() {

    int choice, numOfPlaylists = 0;
    //main playlists array
    Playlist** playlists = (Playlist**)calloc(1,sizeof(Playlist*));
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
                            //chosen playlist
                            Playlist* pl = playlists[chosenPl - 1];
                            printf("playlist %s:\n", pl->name);
                            do
                            {
                                printPlaylistMenu();
                                if (scanf("%d", &action))
                                {
                                    //secondary menu
                                    switch (action)
                                    {
                                        case 1:
                                            {
                                                int chosenSong = 0;
                                                showPlaylist(*pl);
                                                printf("choose a song to play, or 0 to quit:\n");
                                                scanf("%d", &chosenSong);
                                                if(pl->songsNum == 0)
                                                    break;
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
                                                //creates a song in the heap
                                                Song* song = malloc(sizeof(Song));
                                                if(song == NULL){printf("malloc failed"); exit(1);}
                                                //creating the song itself
                                                addSong(song);
                                                //adds the song to the playlist
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
                                                //removing the song from the playlist
                                                deleteSong(chosenSong - 1 , pl->songs, pl->songsNum);
                                                pl->songsNum--;
                                                if(pl->songsNum == 0)
                                                    break;
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
                            //back to the sub menu for choosing a playlist
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
                        //creates a playlist in the heap and initializing it
                        Playlist* pl = malloc(sizeof(Playlist));
                        pl->songs = (Song**)malloc(sizeof(Song*));
                        if(pl->songs == NULL){printf("malloc failed"); exit(1);}
                        pl->songsNum = 0;
                        pl->name = NULL;
                        printf("Enter playlist's name:\n");
                        pl->name = getInput();
                        //adds the playlist to the main playlists array
                        playlists = realloc(playlists, (numOfPlaylists + 1) * sizeof(Playlist*));
                        if(playlists == NULL){printf("malloc failed"); exit(1);}
                        playlists[numOfPlaylists] = NULL;
                        playlists[numOfPlaylists] = pl;
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
                        //removes the chosen playlist from the main playlists array
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
                        //frees all the memory
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

//inputs a string saves it in the heap and returns it's address
char* getInput()
{
    //creates a new string in the heap
    char* input = malloc(sizeof(char));
    if(input == NULL){printf("malloc failed"); exit(1);}

    char temp;
    int i = 1;

    //inputs characters until the end of the string while allocating new memory for them
    scanf(" %c", &temp);
    *(input) = temp;
    while(scanf("%c", &temp) && temp != '\r' && temp != '\n')
    {
        input = realloc(input, ++i);
        if(input == NULL){printf("malloc failed"); exit(1);}
        *(input + (i - 1)) = temp;
    }
    if(temp == '\r')
        scanf("%*c");
    input = realloc(input, i + 1);
    if(input == NULL){printf("malloc failed"); exit(1);}

    return input;
}
//delete a song from a playlist's array
void deleteSong(int index, Song** songs, int songsNum)
{
    //frees the memory of the song it needs to delete
    freeSong(&songs[index]);
    //moves the pointers forward
    for(int i = index; (i + 1) < songsNum ; i++)
    {
        songs[i] = songs[i + 1];
    }
    songs[songsNum - 1] = NULL;
    printf("Song deleted successfully.\n");
}
//fills the song's content
void addSong(Song* s)
{
    //get data for creating a song
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
//prints all the songs in a playlist as requested
void showPlaylist(Playlist pl)
{
    for(int i = 0 ; i < pl.songsNum ; i++)
    {
        printf("%d. Title: %s\n   Artist: %s\n   Released: %d\n   Streams: %d\n\n",
            i + 1, pl.songs[i]->title, pl.songs[i]->artist, pl.songs[i]->year, pl.songs[i]->streams);
    }
}
//plays a single song
void playSong(Song* song)
{
    printf("Now playing %s:\n", song->title);
    printf("$ %s $\n", song->lyrics);
    song->streams++;
}
//frees a song and it's content
void freeSong(Song** song)
{
    free((*song)->title);
    (*song)->title = NULL;
    free((*song)->artist);
    (*song)->artist = NULL;
    free((*song)->lyrics);
    (*song)->lyrics = NULL;
    free((*song));
    (*song) = NULL;
}
//frees a playlist and all its content (using freeSong)
void freePlaylist(Playlist* playlist)
{
    free(playlist->name);
    playlist->name = NULL;
    for(int i = 0 ; i < playlist->songsNum ; i++)
    {
        freeSong(&(playlist->songs[i]));
    }
    free(playlist->songs);
    playlist->songs = NULL;
    free(playlist);
    playlist = NULL;
}
//frees all the playlists in the main playlists array (using freePlaylist)
void freeAll(Playlist** playlists, int numOfPlaylists)
{
    for(int i = numOfPlaylists - 1 ; i >= 0 ; i--)
    {
        freePlaylist(playlists[i]);
    }
    free(playlists);
    playlists = NULL;
}
//prints the first menu (the main one)
void printPlaylistsMenu() {
    printf("Please Choose:\n");
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
}
//prints the action menu for a specific playlist
void printPlaylistMenu()
{
    printf("\t1. Show Playlist\n\t2. Add Song\n\t3. Delete Song\n\t4. Sort\n\t5. Play\n\t6. exit\n");
}
//prints the sub menu for choosing a playlist
void printAllPlaylists(Playlist** pl, int numOfPlaylists)
{
    printf("Choose a playlist:\n");
    for(int i = 0 ; i < numOfPlaylists ; i++)
    {
        printf("\t%d. %s\n", i + 1, pl[i]->name);
    }
    printf("\t%d. Back to main menu\n", numOfPlaylists + 1);
}
//removes a playlist from the main playlists array
void removePlaylist(int index, Playlist** playlists, int numOfPlaylists)
{
    //frees the memory of the playlist it needs to delete
    freePlaylist(playlists[index]);
    //moves the pointers forward
    for(int i = index ; (i + 1) < numOfPlaylists ; i++)
    {
        playlists[i] = playlists[i + 1];
    }
    playlists[numOfPlaylists - 1] = NULL;
    printf("Playlist deleted.\n");
}
//plays all the songs in a playlist (using playSong)
void playAll(Playlist* playlist)
{
    for(int i = 0 ; i < playlist->songsNum ; i++)
    {
        playSong(playlist->songs[i]);
        printf("\n");
    }
}
//sorts a playlist depending on the chosen method
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
//sorts a playlist by year
void sortByYear(Playlist* playlist)
{
    //bubble sorts by year
    Song* temp = NULL;
    for(int i = 0 ; i < playlist->songsNum - 1 ; i++)
    {
        for (int j = 0 ; j < playlist->songsNum - 1 - i ; j++)
        {
            //swaps if the next song's year is smaller
            if(playlist->songs[j]->year > playlist->songs[j + 1]->year)
            {
                temp = playlist->songs[j];
                playlist->songs[j] = playlist->songs[j + 1];
                playlist->songs[j + 1] = temp;
            }
        }
    }
}
//sorts a playlist by streams (ascending)
void sortStreamsAscending(Playlist* playlist)
{
    //bubble sorts by streams (ascending)
    Song* temp = NULL;
    for(int i = 0 ; i < playlist->songsNum - 1 ; i++)
    {
        for (int j = 0 ; j < playlist->songsNum - 1 - i ; j++)
        {
            //swaps if the next song has fewer streams
            if(playlist->songs[j]->streams > playlist->songs[j + 1]->streams)
            {
                temp = playlist->songs[j];
                playlist->songs[j] = playlist->songs[j + 1];
                playlist->songs[j + 1] = temp;
            }
        }
    }
}
//sorts a playlist by streams (descending)
void sortStreamsDescending(Playlist* playlist)
{
    //bubble sorts by streams (descending)
    Song* temp = NULL;
    for(int i = 0 ; i < playlist->songsNum - 1 ; i++)
    {
        for (int j = 0 ; j < playlist->songsNum - 1 - i ; j++)
        {
            //swaps if the next song has more streams
            if(playlist->songs[j]->streams < playlist->songs[j + 1]->streams)
            {
                temp = playlist->songs[j];
                playlist->songs[j] = playlist->songs[j + 1];
                playlist->songs[j + 1] = temp;
            }
        }
    }
}
//sorts a playlist alphabetically
void sortAlphabetically(Playlist* playlist)
{
    //bubble sorts alphabetically
    Song* temp = NULL;
    for(int i = 0 ; i < playlist->songsNum - 1 ; i++)
    {
        for (int j = 0 ; j < playlist->songsNum - 1 - i ; j++)
        {
            //swaps if the current song appears after the next song alphabetically
            if(strcmp(playlist->songs[j]->title, playlist->songs[j + 1]->title) > 0)
            {
                temp = playlist->songs[j];
                playlist->songs[j] = playlist->songs[j + 1];
                playlist->songs[j + 1] = temp;
            }
        }
    }
}