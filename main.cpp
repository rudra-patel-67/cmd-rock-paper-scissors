#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <time.h>
using namespace std;

char getch();

void clearScreen();
//rock=1; paper=2; scissors=3;      --- For A.I.

class rps
{
    private:
        bool gameOver=false;
        int p1Score, p2Score;
        int r; 
    public:
        
        void startGame()
        {
            char mode;
            p1Score = p2Score = 0;
            cout<<"Single Player or Multiplayer? (Singleplayer - 's' / Two Player 't'): ";
            cin>>mode;
            cin.ignore();
            if(mode=='s' || mode=='S')
            {
                cout<<"Starting"<<endl<<endl;
                cout<<"Playing against AI"<<endl<<endl;
                r=rounds();
                for(int i=0; i<r; i++)
                singlePlayer();
            }
            else if(mode=='t' || mode=='T')
            {
                cout<<"Starting"<<endl<<endl;
                cout<<"Playing against each other"<<endl<<endl;
                r=rounds();
                for(int i=0; i<r; i++)
                twoPlayer();
            }
            else
            {
                cout<<"Invalid input! Please try again."<<endl;
                startGame();
            }
        }

        void singlePlayer()
        {
            int ai;
            char choice;
            char weapon[3]={'r','p','s'};
            while (!gameOver)
            {
                if(p1Score>(r/2))
                {
                    cout<<"You won the game!"<<endl;
                    gameOver=true;
                    break;
                }
                if(p2Score>(r/2))
                {
                    cout<<"A.I. won the game!"<<endl;
                    gameOver=true;
                    break;
                }
                cout<<"Enter input 'e' to exit the game!"<<endl<<endl;  
                cout<<"Player 1: Choose your weapon (Rock/Paper/Scissor): ";
                cin>>choice;
                cin.ignore();
                if(choice=='e' || choice=='E')
                {
                    cout<<"Game ended forcefully"<<endl;
                    cout<<"Enter any key to close the window. "<<endl;
                    getch();
                    exit(0);
                }
                if(choice!='r' && choice!='p' && choice!='s' && choice!='R' && choice!='P' && choice!='S')
                {
                    cout<<"Invalid choice! Please try again."<<endl;
                    continue;
                }
                srand(time(0)); 
                ai = (rand() % (2)) + 1;
                clearScreen();
                cout<<"Your choice ->\t  "<<choice<<"  |  "<<weapon[ai-1]<<"   <- AI's choice"<<endl<<endl;
                
                if(((choice=='r' || choice=='R') && ai==1) || ((choice=='p' || choice=='P') && ai==2) || ((choice=='s' || choice=='S') && ai==3))
                {
                    cout<<"It's a tie!"<<endl;
                }
                else if((((choice=='r' || choice=='R') && ai==2) || ((choice=='p' || choice=='P') && ai==3) || ((choice=='s' || choice=='S') && ai==1)) && choice!=weapon[ai-1])
                {
                    p2Score++;
                    cout<<"A.I. wins!"<<endl;
                }
                else
                {
                    p1Score++;
                    cout<<"You wins!"<<endl;
                }
                cout<<endl;
                cout<<"Your Score: "<<p1Score<<endl;
                cout<<"A.I. Score: "<<p2Score<<endl;
                cout<<endl;
            }
            getch();
        }

        void twoPlayer()
        {
            char p1choice;
            char p2choice;
            // char weapon[3]={'r','p','s'};
            while (!gameOver)
            {
                if(p1Score>(r/2))
                {
                    cout<<"Player 1 won the game!"<<endl;
                    gameOver=true;
                    break;
                }
                if(p2Score>(r/2))
                {
                    cout<<"Player 2 won the game!"<<endl;
                    gameOver=true;
                    break;
                }
                cout<<"Enter input 'e' to exit the game!"<<endl<<endl;
                p1turn:
                cout<<"Player 1: Choose your weapon (Rock/Paper/Scissor): ";
                cin>>p1choice;  
                cin.ignore();
                p1choice=tolower(p1choice);
                if(p1choice=='e')
                {
                    cout<<"Game ended forcefully"<<endl;
                    cout<<"Enter any key to close the window."<<endl;
                    getch();
                    exit(0);
                }
                if(p1choice!='r' && p1choice!='p' && p1choice!='s')
                {
                    cout<<"Invalid choice! Player 1, please try again."<<endl;
                    goto p1turn;
                    continue;
                }
                clearScreen();
                p2turn:
                cout<<"Player 2: Choose your weapon (Rock/Paper/Scissor): ";
                cin>>p2choice;
                cin.ignore();
                p2choice=tolower(p2choice);
                if(p2choice=='e')
                {
                    cout<<"Game ended forcefully"<<endl;
                    cout<<"Enter any key to close the window."<<endl;
                    getch();
                    exit(0);
                }
                if(p2choice!='r' && p2choice!='p' && p2choice!='s')
                {
                    cout<<"Invalid choice! Player 1, please try again."<<endl;
                    goto p2turn;
                    continue;
                }
                clearScreen();
                cout<<"Player 1's choice ->\t  "<<p1choice<<"  |  "<<p2choice<<"   <- Player 2's choice"<<endl<<endl;
                
                if(p1choice==p2choice)
                {
                    cout<<"It's a tie!"<<endl;
                }
                else if(((p1choice=='r'&& p2choice=='p') || (p1choice=='p' && p2choice=='s') || (p1choice=='s' && p2choice=='r')) && p1choice!=p2choice)
                {
                    p2Score++;
                    cout<<"Player 2 wins!"<<endl;
                }
                else
                {
                    p1Score++;
                    cout<<"Player 1 wins!"<<endl;
                }
                cout<<endl;
                cout<<"Player 1 Score: "<<p1Score<<endl;
                cout<<"Player 2 Score: "<<p2Score<<endl;
                cout<<endl;
            }           
            getch();
        }


        int rounds()
        {
            int choice;
            rounds:
            cout<<"Rounds Selection"<<endl<<endl;
            cout<<"1. One Round Win"<<endl;
            cout<<"2. Best of Three"<<endl;
            cout<<"3. Best of Five"<<endl;
            cout<<"4. First to _____ Wins "<<endl;
            cout<<"5. Exit "<<endl;
            cin>>choice;
            clearScreen();
            switch (choice)
            {
            case 1:
                cout<<"One Round Win selected"<<endl;
                return 1;
            
            case 2:
                cout<<"Best of Three selected"<<endl;
                return 3;
                
            case 3:
                cout<<"Best of Five selected"<<endl;
                return 5;

            case 4:
                int a;
                cout<<"First to _____ Wins selected"<<endl;
                cout<<"Enter the number of wins required: ";
                cin>>a;
                return (a*2)-1;

            case 5:
                cout<<"Exiting..."<<endl;
                break;
            
            default:
                cout<<"Invalid Input"<<endl;
                goto rounds;
            }
            return 0;
        }

};

int main()
{
    class rps game;
    char a;
    clearScreen();
    cout << "XX--------------------->\tRock \t Paper \t Scissor \t<----------------------XX"<<endl<<endl;
    cout<<"\t\t\t     Press any key to start the game"<<endl<<endl;
    getch();
    game.startGame();
    return 0;
}







// Linux-compatible getch()
char getch() {
    termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);          // Get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);        // Disable buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new settings

    ch = getchar();                          // Read single character

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old settings
    return ch;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");    // Windows
#else
    system("clear");  // Linux/macOS
#endif
}
