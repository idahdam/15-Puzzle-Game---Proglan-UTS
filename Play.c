// selfmade preprocessor
#include "selfHeader.h"

// def kalau pake linux
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// define constants
#define BARIS 4
#define KOLOM 4  
#define ANGKA_MAX 15
#define ANGKA_MIN 1
#define BANYAK_ANGKA 15

// declaring global variables
int arrayMatrix[BARIS][KOLOM], arr[BANYAK_ANGKA], arrayAcuan[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
int globalX = 3, globalY = 3, moveCounter = 0, debugTrigger, stopTrigger = 0, timer = 300;
bool gameLoop;
char areYouSure;

// main function in main.c will run this.
void startFunc(){
    randomizeElements();
    setMainMatrixElements();
    printWholeMainGame();
}

// this function will randomize each element on the block
void randomizeElements(){
    int get, c, i, j, k =0, chk, x;
    c = i = 0;
    srand(time(NULL)); // this will ensure that every time, program will generate different set of numbers. If you remove this, same set of numbers will generated every time you run the program.
    while(c < ANGKA_MAX)
    {
        get = ((rand() % (ANGKA_MAX-ANGKA_MIN+1)) + ANGKA_MIN); // generate random number.
        //After generating that number check if it is already in array.
        for(i=0; i<=c; i++)
        {
            if(arr[i] == get)
            {
                chk = 0;
                break;
            }
            else if(arr[i] != get)
            {
                chk = 1;
            }
        }
        if(chk==1)
        {
            arr[c]=get;
            //printf("%d\n",arr[c]);
            c++;
        }
    }
}

// randomized element from randomizeElements will be moved here
void setMainMatrixElements(){
    int i, j, k = 0;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(j == 3 && i == 3){
                arrayMatrix[i][j] = 0;
            }
            arrayMatrix[i][j] = arr[k];
            k++;
        }  
    }
}

// main interface
void printWholeMainGame(){
    int i, j, msec, menit, detik, rmsec;
    char areYouSure;
    char movement;
    char test = movement;
    clock_t before  = clock(), difference;
    gameLoop = true;
    globalX = 3, globalY = 3;
    debugTrigger = 0;
    stopTrigger = 0, moveCounter = 0;
    pressStartOrEscape();
	
	// game loop
    while(gameLoop){
        TIMER:
        system("cls");
        difference = clock() - before;
        msec = difference * 1000/CLOCKS_PER_SEC;
        rmsec = timer - msec/1000;
        detik = formattingSeconds(rmsec);
        menit = formattingMinutes(rmsec);
        printf("\t\t\ttimer: %d:%d\n\n", menit, detik);
        printf("\t\t\ttimer: %d\n\n", rmsec);
        printf("\t\t\t");
        printf("=======================================\n");
        for(i = 0; i < BARIS; i++){
        	printf("\t\t\t");
        	printf("|| ");
            for(j = 0; j < KOLOM; j++){
                if(j == globalX && i == globalY){
                	printf("       ||");
				}
                else{
                    printf("  %-5d||", arrayMatrix[i][j]);
                }
            }
            if(i >= 0 && i < BARIS - 1){
                printf("\n\t\t\t---------------------------------------");
            }
            else{
                printf("\n\t\t\t=======================================\n");
            }
            printf("\n");
        }

        printf("\n\t\t\tMove You Take:  %d\n", moveCounter);
        printf("\t\t\tk to quit.\n");
        printf("\t\t\tWhere would you like to move? up/left/right/down: ");
        movement = getch();
        switch (movement){
        case 'w':
            /* code */
            printf("\n\t\t\tYou pressed up.");
            //Sleep(1000);
            moveTo(checkIfAbleToMove(globalX, globalY, movement), movement);
            break;
        case 'a':
            printf("\n\t\t\tYou pressed left.");
            //Sleep(1000);
            moveTo(checkIfAbleToMove(globalX, globalY, movement), movement);
            break;
        case 's':
            printf("\n\t\t\tYou pressed down.");
            //Sleep(1000);
            moveTo(checkIfAbleToMove(globalX, globalY, movement), movement);
            break;
        case 'd':
            printf("\n\t\t\tYou pressed right.");
            //Sleep(1000);
            moveTo(checkIfAbleToMove(globalX, globalY, movement), movement);
            break;
        case 'k':
            // gameLoop = false;
            printf("\n\n\t\t\tAre you sure? y/n: ");
            areYouSure = getch();
            Sleep(500);
            switch(areYouSure){
            	case 'y':
            		gameLoop = false;
            		continue;
            	case 'n':
            		printf("\t\t\tGoing back");
            		continue;
			}
        case '/':
            printf("\n\t\t\tdebug mode.\n\n");
            printf("\t\t\tEnter debug menu: \n\n\t\t\t1. Finish the Game\n\t\t\t2. Maxout Move\n\t\t\t3. Reset\n\t\t\t4. Return to game\n\n\t\t\t"), scanf("%d", &debugTrigger);
            debugMode(debugTrigger);
            Sleep(500);
            break;

        default:
            printf("\t\t\tNot a valid input.");
            //Sleep(500);
        }

        if(stopTrigger == 16){
            gameLoop = false;
            printWin();
        }
        if(rmsec <= 0){
            // stopTrigger = 1;
            printLose();
            gameLoop = false;
        }
        
        if(moveCounter == 500){
        	printLose();
        	gameLoop = false;
		}

        for(i = 0; i < KOLOM; i++){
            for(j = 0; j < BARIS; j++){
                if(arrayMatrix[i][j] == arrayAcuan[i][j]){
                    stopTrigger += 1;
                }
                else{
                    stopTrigger = 0;
                }
            }
        }

    }
    // put the enter the score here
    enterScore(moveCounter, menit, detik);
    // put print the score here  
    showScore();
    stopTrigger = 0;
    askPlayOrMain();
    Sleep(2000);
}

// before playing, will be asked to press enter
void pressStartOrEscape(){
    system("cls");
    int i, j;
    printf("\n\n\t\t\t");
    printf("=====================================\n");

    for(i = 0; i < BARIS; i++){
            for(j = 0; j < KOLOM; j++){
                if(j == 2 && i == 2){
                	printf("\t\t\t");
                        printf("========Press Enter To Start========\n");
                }
            }
            if(i >= 0 && i < BARIS - 1){
                //printf("\n-------------------------------------");
            }
            else{
                printf("\n\t\t\t=====================================\n");
            }
            printf("\n");
        }

    getch();
}

// each input will make this function runs
bool checkIfAbleToMove(int X, int Y, char input){
    int moveToWhere;
    // checking corners
    // last row (Y =)
    if(Y == 3){
        if(X == 3){
            if(input == 'd' || input == 's'){
                return false;
            }
            else{
                if(input == 'w'){
                    return true;
                }
                else if(input == 'a'){
                    return true;
                }
            }

        }
        else if(X == 1 || X == 2){
            if(input == 's'){
                return false;
            }
            else{
                if(input == 'w' || input == 'd' || input == 'a'){
                    return true;
                }
            }
        }
        else if(X == 0){
            if(input == 'a' || input == 's'){
                return false;
            }
            else{
                if(input == 'w' || input == 'd'){
                    return true;
                }
            }
        }
    }
    else if(Y == 2 || Y == 1){
        if(X == 3){
            if(input == 'd'){
                return false;
            }
            else{
                if(input == 'w' || input == 'a' || input == 's'){
                    return true;
                }
            }

        }
        else if(X == 1 || X == 2){
            if(input == 'a' || input == 's' || input == 'w' || input == 'd'){
                return true;
            }
        }
        else if(X == 0){
            if(input == 'a'){
                return false;
            }
            else{
                if(input == 'w' || input == 'd' || input == 's'){
                    return true;
                }
            }
        }
    }
    else if(Y == 0){
        if(X == 3){
            if(input == 'd' || input == 'w'){
                return false;
            }
            else{
                if(input == 'a' || input == 's'){
                    return true;
                }
            }

        }
        else if(X == 1 || X == 2){
            if(input == 'w'){
                return false;
            }
            else if(input == 'a' || input == 's' || input == 'd'){
                return true;
            }
        }
        else if(X == 0){
            if(input == 'a' || input == 'w'){
                return false;
            }
            else{
                if(input == 'd'){
                    return true;
                }
                else if(input == 's'){
                    return true;
                }
            }
        }
    }
}

// if checkIfAbleToMove == true, you can move to the destined location
void moveTo(bool movement, int move){
    int a, b, temp;
    if(movement == false){
    	system("COLOR 84");
        printf("\n\t\t\tYou can't move.");
        system("COLOR 8f");
        Sleep(1000);
    }
    else{
        if(move == 'w'){
            a = arrayMatrix[globalY][globalX];
            b = arrayMatrix[globalY-1][globalX];

            temp = a;
            a = b;
            b = temp;

            arrayMatrix[globalY][globalX] = a;
            arrayMatrix[globalY-1][globalX] = b;

            globalY--;
        }
        else if (move == 'a'){
            a = arrayMatrix[globalY][globalX];
            b = arrayMatrix[globalY][globalX-1];

            temp = a;
            a = b;
            b = temp;

            arrayMatrix[globalY][globalX] = a;
            arrayMatrix[globalY][globalX-1] = b;

            globalX--;
        }
        else if (move == 's'){
            a = arrayMatrix[globalY][globalX];
            b = arrayMatrix[globalY+1][globalX];

            temp = a;
            a = b;
            b = temp;

            arrayMatrix[globalY][globalX] = a;
            arrayMatrix[globalY+1][globalX] = b;  

            globalY++;          
        }
        else if (move == 'd'){
            a = arrayMatrix[globalY][globalX];
            b = arrayMatrix[globalY][globalX+1];

            temp = a;
            a = b;
            b = temp;

            arrayMatrix[globalY][globalX] = a;
            arrayMatrix[globalY][globalX+1] = b;   

            globalX++;         
        }
        system("COLOR 82");
        printf("\n\t\t\tYou've succesfully moved.");
        system("COLOR 8f");
        moveCounter++;
    }
}

// translate time in seconds into minutes ;D
int formattingSeconds(int seconds){
    int detik;
    detik = seconds%60;
    return detik;
}

int formattingMinutes(int seconds){
    int menit;
    menit = seconds/60;
    return menit;
}

// this function is made to test final position, max move, timer max
void debugMode(int enableDebug){
    int i, j;
    if(enableDebug == 1){
        for(i = 0; i < KOLOM; i++){
            for(j = 0; j < BARIS; j++){
                arrayMatrix[i][j] = arrayAcuan[i][j];
                globalX = 3;
                globalY = 3;
            }
        }
        moveCounter = 1;
        printf("\nTransferred.");
    }
    else if(enableDebug == 2){
        //debugMode(1);
        moveCounter = 500;
        printf("\n\t\t\tCounter maxed out");
    }
    else if(enableDebug == 3){
        startFunc();
    }
    else if(enableDebug == 4){
        printf("Ok...");
    }
}

// asking if they wanna play again or go to main menu
void askPlayOrMain(){
    int opt;
    system("cls");
    printf("\t\t\t");
    printf("=======================================================\n");printf("\t\t\t");
    printf("                Do you want to play again?\n");printf("\t\t\t");
    printf("=======================================================\n");
    printf("\t\t\t");
    printf("1. Play again\n");
    printf("\t\t\t");
    printf("2. Go to main menu\n");printf("\t\t\t");
    printf("=======================================================\n");printf("\t\t\t");
    printf("input: "), scanf("%d", &opt);
    switch(opt){
        case 1:
            startFunc();
        case 2:
        	printf("\t\t\t");
            printf("Bringing you back to main menu in 2 seconds.");
            
            // insert main menu here
            Sleep(2000);
            main();
    }
}

// asking if they're sure to quit
void areYouSureQuit(){
	printf("\t\t\t");
    printf("Are you sure? Y/N: ");
    scanf("%c", &areYouSure);
}
