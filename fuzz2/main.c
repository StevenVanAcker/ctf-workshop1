/*******************************************************************************
 *
 *  CREATED BY:                 JADEN YUROS
 *  DATE:                       05/01/2016
 *  CS 344 (Operating Systems): PROGRAM 2
 *
 *  This assignment asks you to write a simple game akin to old text 
 *  adventure games like Adventure:
 * 
 *  https://en.wikipedia.org/wiki/Colossal_Cave_Adventure
 *
 *  All formatting, file/directory creation (and non-removal of those), and 
 *  output is done per program specifications
 * 
 *******************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>           // used to seed srand
#include <string.h>         
#include <unistd.h>         // used to get PID to name directory
#include <fcntl.h>          // used to create directory

// DEFINING SOME MACROS
#define MAX_ROOMS 6
#define BUFFER_SIZE 512


struct room {
    char name[20];
    char connectingRooms[MAX_ROOMS][20];    // creates a 2d array for string names
    int connectionTotal;
    char type[20];
};

// generates a random number between 2 numbers (inclusive)
int genRandom(int lowerBound, int upperBound){
    int result=0;
    int low = 0;
    int high = 0;
    
    if(lowerBound < upperBound) {
        low = lowerBound;
        high = upperBound + 1;
    }
    else {
        low = upperBound;
        high = lowerBound + 1;
    }
    
    result = (rand()%(high-low))+low;
    return result;
}

void printRoom(struct room* r){
    
    printf("CURRENT LOCATION: %s\n", r->name);
    printf("POSSIBLE CONNECTIONS: "); 
    int i;    
    for (i=0; i < r->connectionTotal; i++){
        if(i+1 < r->connectionTotal)        
            printf("%s, ",r->connectingRooms[i]);
        else if (i+1 == r->connectionTotal)
            printf("%s.\n",r->connectingRooms[i]);
    }
    printf("WHERE TO?>");         
}

void writeRoomFile(struct room* r, char* filename) {
    
    FILE *f;
    f = fopen(filename, "w");
    
    if (f == NULL) {
        fprintf(stderr, "Can't open input file!\n");
        exit(1);
    } 
    
    // builds the data in file
    fprintf(f,"ROOM NAME: %s\n", r->name);
    int i;
    for (i=0; i<r->connectionTotal; i++){
        fprintf(f,"CONNECTION %i: %s\n", i+1, r->connectingRooms[i]);
    }
    fprintf(f,"ROOM TYPE: %s\n", r->type);
    fclose(f);    
}

struct room* readRoomFile(char* inputFile){

    FILE* f;
    f = fopen(inputFile, "r");
    char line[BUFFER_SIZE];
    
    struct room *r = malloc(sizeof(struct room));
    r->connectionTotal = 0;
    
    char* token;
    
    // parses the file, line by line and builds a room struct
    if (f) {
        while(fgets(line,BUFFER_SIZE,f)) {
            // search line for ' ' delimiter
            token = strtok(line, " ");
            
            while (token != NULL ){
                
                if (strcmp("ROOM", token) == 0){
                    token = strtok(NULL, " ");
                    // get room name
                    if(strcmp("NAME:", token) == 0){
                        token = strtok(NULL, "\n");
                        strcpy(r->name, token);
                        break;
                    }
                    // get room type
                    if(strcmp("TYPE:", token) == 0){
                        token = strtok(NULL, "\n");
                        strcpy(r->type, token);
                        break;
                    }
                }
                // get connections
                if (strcmp("CONNECTION", token) == 0){
                    token = strtok(NULL, " ");
                    // token is an int now
                    int i = atoi(token);
                    i--; // set up index
                    token = strtok(NULL, "\n");
                    strcpy(r->connectingRooms[i], token);
                    r->connectionTotal++;
                    break;                    
                }
            }
        }
    fclose(f);
    }
    return r;
}

struct room* findStart(struct room* r) {
    
    int i;
    for(i=0; i<7; i++) {
        if(strcmp(r[i].type, "START_ROOM") == 0) {
            return &r[i];
        }
    }
}

struct room* createRooms(){
    
    // allocate memory for room structs
    struct room *house = malloc(7*sizeof(struct room));
    
    // assign room names
    char roomNames[10][20];
    
    strcpy(roomNames[0], "A");
    strcpy(roomNames[1], "B");
    strcpy(roomNames[2], "C");
    strcpy(roomNames[3], "D");
    strcpy(roomNames[4], "E");
    strcpy(roomNames[5], "F");
    strcpy(roomNames[6], "G");
    strcpy(roomNames[7], "H");
    strcpy(roomNames[8], "I");
    strcpy(roomNames[9], "J");

    int startRoomIndex = genRandom(0,9);
    
    // assign room ids and number of connections, set total connections to 0
    int i;
    for (i=0; i<7; i++){
        house[i].connectionTotal = 0;                  // no connections made yet
        strcpy(house[i].name, roomNames[(i+startRoomIndex)%10]);  // assigns names in order from a random starting point in roomNames[]
        strcpy(house[i].type, "MID_ROOM");
    }
    
    // get random start and end room indices
    int start_room = genRandom(0,6);
    int end_room;
    do{
        end_room = genRandom(0,6);
    } while (start_room == end_room);
    strcpy(house[start_room].type, "START_ROOM");
    strcpy(house[end_room].type, "END_ROOM");

    // Start making 2 way connections between rooms
    int rand;
    for (i=0; i<7; i++){
        int newConnection;
        int validConnection = 0;    // set flag to check validity, 0 = invalid, 1 = valid
        rand = genRandom(3,6);  // number of connections to make
       
        while (house[i].connectionTotal < rand) {
        
            // generate a random number, cannot be the same as the room id we are in.
            do{
                newConnection = genRandom(0,6);
            } while (newConnection == i);
            validConnection = 1;
            
            // make sure we aren't already connected to this attempted room connection
            int j;
            for (j=0; j<MAX_ROOMS; j++) {
                if (strcmp(house[i].connectingRooms[j], house[newConnection].name) == 0) {
                    validConnection = 0; // already connected to that room
                }
            }

            // check if our new connection can make anymore connections
            if (validConnection == 1 && house[newConnection].connectionTotal >= MAX_ROOMS) {
                    validConnection = 0;
                }
           
            // if passes all tests, then make connection
            if (validConnection == 1){
                strcpy(house[i].connectingRooms[house[i].connectionTotal], house[newConnection].name);
                strcpy(house[newConnection].connectingRooms[house[newConnection].connectionTotal], house[i].name);
                house[i].connectionTotal++;
                house[newConnection].connectionTotal++;
            }
        } 
    }
    return house;
}

void createFiles(struct room* r){
  
    // get PID
    int pid;
    pid = getpid();
    
    // create buffer for file path
    char dirname[128];
    
    // builds the name of directory
    sprintf(dirname, "%s.%d", "yurosj.rooms",pid);  
        
    // check if the directory exists, if not, create it, then navigate to it
    struct stat path = {0};
    if (stat(dirname, &path) == -1) {
        mkdir(dirname, 0777);
    }
    chdir(dirname);
    
    // create the room files

    FILE *f;
    int i;
    for (i=0; i<7; i++){
        char file[10];
        strcpy(file, r[i].name);
        
        // creates the file (empty at this point)
        f = fopen(file, "w");
        if (f == NULL) {
            fprintf(stderr, "Can't open input file!\n");
        exit(1);
        }  
        fclose(f);
        
        // function writes data to file
        writeRoomFile(&r[i], file);
    }
}


int main(int argc, char** argv) {

    // seed rand with current time
    srand(0);
    
    // creates the room structures from memory and saves them in structs
    struct room *myHouse = createRooms();
    
    // builds files from the structs and places them in a new directory
    createFiles(myHouse);
    
    // search for the starting room and copy the name of the room
    struct room *startRoom = findStart(myHouse);
    char startName[20];
    strcpy(startName, startRoom->name);

    // room pointers that are used in game loop   
    struct room *current;
    struct room *nameValidation;

    // variables to count steps and the path from start to finish
    int steps = 0;
    char path[BUFFER_SIZE];

    // set starting location
    current = readRoomFile(startName);
    
    // main game loop
    do {
        printRoom(current);
        
        // get user input and clear input stream
        char nextLoc[20];
        scanf ("%s", nextLoc);
        while ( getchar() != '\n' );
        
        nameValidation = readRoomFile(nextLoc);
        
        // user enters an invalid name 
        if(strcmp(nameValidation->name, nextLoc) != 0){
            printf("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
        }
        
        // user enters name of the current room
        else if(strcmp(current->name, nextLoc) == 0){
            printf("\n");
        }
        
        // user has entered a valid input
        else {
            // builds path taken string and increases steps taken
            strcat(path, current->name);
            strcat(path, "\n");
            steps++;
            
            // clean up memory
            free(current);
            
            // move to the next location
            current = readRoomFile(nextLoc);
            printf("\n");
        }
        
        // clean up memory
        free(nameValidation);
        nameValidation = NULL;
        
    } while(strcmp(current->type, "END_ROOM") != 0);
    
    // clean up memory
    free(current);
    free(myHouse);
    myHouse = NULL;
    current = NULL;
        
    // victory!    
    printf("\nYOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
    printf("YOU TOOK %i STEPS. YOUR PATH TO VICTORY WAS:\n", steps);
    printf("%s", path);
    printf("\n");

    *(unsigned long *)NULL = 12345;
    
    return 0;
}

