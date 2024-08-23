#include <iostream>
#include <cstdlib>

using namespace std;
int check(int num,int guess){
    if(num == guess){
        return 1;
    }
    else if (num < guess){
        return 2;
    }
    else if (num > guess){
        return 3;
    }
    return 0;
}
int main(){
    int ch;
    cout << "HELLO!\n";
    while(1){
    cout << "1.PLAY\n2.QUIT\n";
    cin >> ch; 
    if(ch==1){
        int guess,count = 0;
        srand(time(0));
        int num = rand()%100+1;
        cout << "Guess the number between 1 to 100:";
        cin >> guess;
        count++;
        bool bol = true;
        while(bol){
            int res = check(num,guess);
            switch(res){
                case 1:
                    cout << "HURRAY!You've Guessed it in " << count << " moves!\n";
                    bol=false;
                    break;
                case 2:
                    cout << "Too High!\n";
                    cout << "Enter new Guess:";
                    cin >> guess;
                    count++;
                    break;
                case 3:
                    cout << "Too Low!\n";
                    cout << "Enter new Guess:";
                    cin >> guess;
                    count++;
                    break;
            }
        }
        
    }
    else if(ch == 2){
        exit(1);
    }
    else{
        cout << "Enter a valid number!";
    }    
    }
    return 0;
}