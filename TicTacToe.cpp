#include <iostream>
#include <limits>
#include <ctime>
enum Priority{computer, user};

void toss(char &comp_symbol, char &user_symbol, int &turn){

    srand(time(NULL));
    int toss_result = (rand()%2);

    if(toss_result){
        std::cout << "Winner of the toss is Computer !!" << std::endl;
        comp_symbol = 'X';
        user_symbol = 'O';
        turn = 1;
    }
    else{
        std::cout << "Winner of the toss is Player !!" << std::endl;
        user_symbol = 'X';
        comp_symbol = 'O';
        turn = 0;
    }
}
int traverse(char TTT_board[3][3], int row, int col, char primary_symbol, char secondary_symbol, char *&most_recent_comp_choice){
    int i, j;
    int count = 0, search = 1;
    char *arr[3] = {nullptr};

    switch(search){
        case 1:
            for( i = row; i < row+1; i++){
                for( j = 0; j < 3; j++){
                    arr[j] = &TTT_board[i][j];
                    if(*arr[j] == primary_symbol){ // check user or comp symbol
                        count++;
                    }
                }
            }
            if(count == 2){
                for( i=0; i<3; i++){
                    if (*arr[i] ==  '-'){
                        *arr[i] = secondary_symbol; // rewrite with only comp symbol
                        *most_recent_comp_choice = secondary_symbol;
                        return search;
                    }
                }
            }
            count = 0;
        case 2:
            for( i = 0; i < 3; i++){
                for( j = col; j <col+1; j++){
                    arr[i] = &TTT_board[i][j];
                    if(*arr[i] == primary_symbol){ // check user or comp symbol
                        count++;
                    }
                }
            }

            if(count == 2){
                for( i=0; i<3; i++){
                    if (*arr[i] ==  '-'){
                        *arr[i] = secondary_symbol; // rewrite with only comp symbol
                        *most_recent_comp_choice = secondary_symbol;
                        return search;
                    }
                }
            }
            count = 0;
        case 3:
            if( TTT_board[0][0] == primary_symbol || // check user or comp symbol
                TTT_board[1][1] == primary_symbol ||
                TTT_board[2][2] == primary_symbol ){
                for(i=0; i<3; i++){
                    arr[i] = &TTT_board[i][i];
                    if(*arr[i] == primary_symbol){
                        count++;
                    }
                }
            }
            if(count == 2){
                for( i=0; i<3; i++){
                    if (*arr[i] ==  '-'){
                        *arr[i] = secondary_symbol; // rewrite with only comp symbol
                        *most_recent_comp_choice = secondary_symbol;
                        return search;
                    }
                }
            }
                count = 0;
        case 4:
            j = 2;
            if( TTT_board[0][2] == primary_symbol || // check user or comp symbol
                TTT_board[1][1] == primary_symbol ||
                TTT_board[2][0] == primary_symbol ){
                for(i=0; i<3; i++){
                    arr[i] = &TTT_board[i][j];
                    if(*arr[i] == primary_symbol){
                        count++;
                    }
                    j--;
                }
            }
            if(count == 2){
                for( i=0; i<3; i++){
                    if (*arr[i] ==  '-'){
                        *arr[i] = secondary_symbol; // rewrite with only comp symbol
                        *most_recent_comp_choice = secondary_symbol;
                        return search;
                    }
                }
            }
    }
    return search = 0;
}
void coordinate(char TTT_board[3][3],char *recent_choice, int &row, int &col){
    char *p = recent_choice;
    char *base = &TTT_board[0][0];
    char offset = p - base;
    row = offset / 3; // return row value of recent choice by com or user
    col = offset % 3; // return col value of recent choice by com or user
}
void computerTurn(char TTT_board[3][3], int &round, char *&most_recent_comp_choice, char *&most_recent_user_choice, char comp_symbol, char user_symbol){
    Priority prio = computer;
    int row, col, found, x=0;
    char *space_array[9] = {};
    char *comp_initial_arr[5] = {&TTT_board[0][0], &TTT_board[0][2], &TTT_board[1][1],
                                 &TTT_board[2][0], &TTT_board[2][2]};

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(TTT_board[i][j] == '-'){
                space_array[x] = &TTT_board[i][j];
                x++;
            }
        }
    }
    
    if(round == 0){
        do{
            most_recent_comp_choice = comp_initial_arr[rand()%5];
        }while(*most_recent_comp_choice != '-');
        *most_recent_comp_choice = comp_symbol;
    }
    else{

        switch(prio){
            case computer:
                coordinate(TTT_board,most_recent_comp_choice, row, col); // It will return row and col number chosen by computer randomly
                found = traverse(TTT_board, row, col, comp_symbol, comp_symbol, *&most_recent_comp_choice); // This func performs a search row and column wise according the previous deed of computer
                if(found == 1){
                    break;
                }
            case user:
                coordinate(TTT_board,most_recent_user_choice, row, col); // It will return row and col number chosen by the user
                found = traverse(TTT_board, row, col, user_symbol, comp_symbol, *&most_recent_comp_choice); // This func performs a search row and column wise according the previous deed of user
                if(found == 1){
                    break;
                }
            default:
                *space_array[rand()%x] = comp_symbol;
                *most_recent_comp_choice = comp_symbol;
                break;
        }
    }
}
void userTurn(char TTT_board[3][3], char user_symbol, char *&most_recent_user_choice ){
    int choice;
    while(true){
        std::cout << "\nEnter your desired position (1-9): ";
        std::cin >> choice;
        if(std::cin.fail() || choice < 1 || choice > 9 ){
            std::cout << "Invalid Choice..!! You have to choose a number among 1 to 9..!!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        int row = (choice-1)/3;
        int col = (choice-1)%3;
        if(TTT_board[row][col] == '-'){
            TTT_board[row][col] = user_symbol;
            most_recent_user_choice = &TTT_board[row][col];
            break;
        }
        else{
            std::cout << "Entered position is already occupied..!! Please enter another position..!!\n";
        }
    }
}
void DisplayBoard(char TTT_board[3][3], int &round, int &turn){
    (turn == 1)? std::cout <<"\n<<<- Computer ->>>\n":std::cout << "\n<<<- Player ->>>\n";
    std::cout << "Round  " << round << '\n';

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            std::cout << TTT_board[i][j] << "  ";
        }
        std::cout << '\n';
    }
}
void checkWinner(char TTT_board[3][3],char symbol, char *recent_choice, int round, int turn){
    int row, col, search = 1;
    coordinate(TTT_board, recent_choice, row, col);
    switch(search){
        case 1:
            if(TTT_board[row][0] == symbol && TTT_board[row][1] == symbol && TTT_board[row][2] == symbol){
                (turn == 0) ? std::cout << "\nWinner is PLAYER..!!" : std::cout << "\nWinner is COMPUTER..!!";
                exit(0);
            }
        case 2:
            if(TTT_board[0][col] == symbol && TTT_board[1][col] == symbol && TTT_board[2][col] == symbol){
                (turn == 0) ? std::cout << "\nWinner is PLAYER..!!" : std::cout << "\nWinner is COMPUTER..!!";
                exit(0);
            }
        case 3:
            if(TTT_board[0][0] == symbol && TTT_board[1][1] == symbol && TTT_board[2][2] == symbol){
                (turn == 0) ? std::cout << "\nWinner is PLAYER..!!" : std::cout << "\nWinner is COMPUTER..!!";
                exit(0);
            }
        case 4:
            if(TTT_board[0][2] == symbol && TTT_board[1][1] == symbol && TTT_board[2][0] == symbol){
                (turn == 0) ? std::cout << "\nWinner is PLAYER..!!" : std::cout << "\nWinner is COMPUTER..!!";
                exit(0);
            }
    }   
}


int main(){

    //---variables---
    srand(time(NULL));
    int turn, round = 0;
    char *most_recent_comp_choice = nullptr;
    char *most_recent_user_choice = nullptr;
    char comp_symbol, user_symbol;

    char TTT_board[3][3] = {{'-', '-', '-'},
                            {'-', '-', '-'},
                            {'-', '-', '-'}};

    std::cout << "\n**** Tic-Tac-Toe ****\n" << std::endl;
    std::cout << "[Disclaimer:- Y/y starts the game by performing a toss..\n";
    std::cout << "Toss winner will get 'X' & other one will get 'O'..\n";
    std::cout << "As per rule Toss winner starts the GAME..]\n";

    // ---Toss---
    do{
        std::cout << "\nToss [Y/N] -> ";
        std::string ans; 
        std::cin >> ans;
        if(ans == "Y" || ans == "y"){
            toss(comp_symbol, user_symbol, turn);
            break;
        }
        else if(ans == "N" || ans == "n"){
            exit(0);
        }
        else{
            std::cout << "\nNot Valid !!\n";
        }
    }while(true);

    std::cout << "\n<<<<- Enter coresponding number of the desired coordinate ->>>>\n" << std::endl;
    std::cout << "_1_|_2_|_3_\n_4_|_5_|_6_\n 7 | 8 | 9 " << std::endl;

    //---Board---
    for(int i=0; i<9; i++){
        round = i++/2;
        if(turn == 1){
            computerTurn(TTT_board, round, most_recent_comp_choice, most_recent_user_choice, comp_symbol, user_symbol);
            DisplayBoard(TTT_board, round, turn);
            if(round >= 2){
                checkWinner(TTT_board, comp_symbol, most_recent_comp_choice, round, turn);
            }
            turn--;
        }
        else{

            userTurn(TTT_board, user_symbol, most_recent_user_choice);
            DisplayBoard(TTT_board, round, turn);
            if(round >= 2){
                checkWinner(TTT_board, user_symbol, most_recent_user_choice, round, turn);
            }
            turn++;
        }
        i--;
        if(i == 8){
            std::cout << "\nIt's a TIE..!!\n";
        }
    }
    return 0;
}