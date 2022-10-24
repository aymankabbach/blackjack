#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;
string deck[52]={"A","2","3","4","5","6","7","8","9","10","J","Q","K","A","2","3","4","5","6","7","8","9","10","J","Q","K","A","2","3","4","5","6","7","8","9","10","J","Q","K","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
int size=52;
int n=sizeof(deck)/sizeof(deck[0]);
vector <string> VdealerHand;
vector <string> VplayerHand;
int player_points=0;
int dealer_points=0;
int counter=0;
int A_counter=0;
int A_counter_dealer=0;
bool End_of_the_game=false;
enum choices {hit=1,stand=2,surrender=3};
string BlackJack_possibilities[8][2]={{"A","10"},{"A","J"},{"A","Q"},{"A","K"},{"10","A"},{"J","A"},{"Q","A"},{"K","A"}};
void shuffle_deck(string deck[52], int n)
{
    srand (time(NULL));
    random_shuffle(deck, deck + n);
};
void add_player_card(vector <string>& VplayerHand, string deck[52])
{
    VplayerHand.push_back(deck[::counter]);
    ::counter++;
}
void add_dealer_card(vector <string>& VdealerHand, string deck[52])
{
    VdealerHand.push_back(deck[::counter]);
    ::counter++;
}
void distribute_first_cards(string deck[52],vector <string>& VdealerHand, vector <string>& VplayerHand)
{
    for (int pos=0;pos<2;pos++)
    {
        VdealerHand.push_back(deck[::counter]);
        ::counter++;
        VplayerHand.push_back(deck[::counter]);
        ::counter++;
    };
}
int calculate_dealer_points(vector <string>& VdealerHand, int dealer_points)
{
    for (string element : VdealerHand)
    {
        (element=="A"|| element=="J" || element=="Q" || element=="K") ? dealer_points=dealer_points+10 :  element=="A" ? dealer_points=dealer_points+11 , ::A_counter_dealer=::A_counter_dealer+1 : dealer_points=dealer_points+stoi(element);
    }
    if (::A_counter_dealer>0 && dealer_points>21)
    {
        for (int x=0; x<::A_counter_dealer;x++)
        {
            dealer_points=dealer_points-11+1;
        }
    }
    return dealer_points;
}
int calculate_player_points(vector <string>& VplayerHand,int player_points)
{
    for (string element : VplayerHand)
    {
        (element=="J" || element=="Q" || element=="K") ? player_points=player_points+10 : element=="A" ? player_points=player_points+11 , ::A_counter=::A_counter+1 : player_points=player_points+stoi(element);
    }
    if (::A_counter>0 && player_points>21)
    {
        for (int x=0; x<::A_counter;x++)
        {
            player_points=player_points-11+1;
        }
    }
    return player_points;
}
bool check_blackjack(string BlackJack_possibilities[8][2],vector <string>& VdealerHand,vector <string>& VplayerHand)
{
    bool dealer_blackjack=false;
    bool player_blackjack=false;
    if (VdealerHand[0] == "A" || VdealerHand[1] == "A" || VplayerHand[0] =="A" || VplayerHand[1]== "A")
    {
        for (int x=0 ;x<8;x++)
        {
            if (VdealerHand[0] == BlackJack_possibilities[x][0] && VdealerHand[1]==BlackJack_possibilities[x][1])
            {
                dealer_blackjack=true;
            }
            if (VplayerHand[0] == BlackJack_possibilities[x][0] && VplayerHand[1] == BlackJack_possibilities[x][1])
            {
                player_blackjack=true;
                
            }
            if (dealer_blackjack && player_blackjack)
            {
                break;
            }
        } 
        if (dealer_blackjack && player_blackjack)
        {
            cout<<"it is a push"<<endl;
            return true;
        }
        else if (dealer_blackjack)
        {
            cout<<VdealerHand[0]<<VdealerHand[1]<<endl;
            cout<<"the dealer gets a Blackjack "<<endl;
            cout<<"dealer wins"<<endl;
            return true;
        }
        else if (player_blackjack)
        {
            cout<<VplayerHand[0]<<VplayerHand[1]<<endl;
            cout<<"the player gets a Blackjack "<<endl;
            cout<<"player wins"<<endl;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    { 
        return false;
    }
}; 
void showing_choices()
{
    string choices[3]={"hit","stand","surrender"};
    for (int x=0;x<3;x++)
    {
        cout<<x+1<<" "<<choices[x]<<endl; 
    }
}
int read_player_input()
{
    int player_input;
    cout<<"please, make a choice "<<endl;
    cin>>player_input;
    return player_input;
}
int get_player_input()
{
    int player_choice=0;
    while (player_choice<1 || player_choice>3)
    {
        player_choice=read_player_input();
    }
    return player_choice;
}
void show_first_cards()
{
    cout<<"the dealer's first card "<<VdealerHand[0]<<endl;
    cout<<"your cards\n";
    for (int x=0;x<VplayerHand.size();x++)
    {
        cout<<VplayerHand[x]<<endl;
    }
}
void show_players_cards()
{
    for (int x=0;x<VplayerHand.size();x++)
    {
        cout<<VplayerHand[x]<<endl;
    }
}
bool check_bust(int player_points,int dealer_points)
{
    if (player_points>21)
    {
        cout<<"it is a bust \nyou lose"<<endl;
        return true;
    }
    if (dealer_points>21)
    {
        cout<<"it is a bust \nyou win"<<endl;
        return true;
    }
    else
    {
        return false;
    }
}
int recalculate_player_points(vector <string>& VplayerHand,int player_points)
{
    string element=VplayerHand.back();
    (element=="J" || element=="Q" || element=="K") ? player_points=player_points+10 : element=="A" ? player_points=player_points+11 , ::A_counter=0,::A_counter=::A_counter+1 : player_points=player_points+stoi(element);
    if (::A_counter>0 && player_points>21)
    {
        for (int x=0; x<::A_counter;x++)
        {
            player_points=player_points-11+1;
        }
    }
    return player_points;
}
int recalculate_dealer_points(vector <string>& VdealerHand,int dealer_points)
{
    string element=VdealerHand.back();
    (element=="J" || element=="Q" || element=="K") ? dealer_points=dealer_points+10 : element=="A" ? dealer_points=dealer_points+11 , ::A_counter_dealer=0,::A_counter_dealer=A_counter_dealer+1 : dealer_points=dealer_points+stoi(element);
    if (::A_counter_dealer>0 && dealer_points>21)
    {
        for (int x=0; x<::A_counter_dealer;x++)
        {
            dealer_points=dealer_points-11+1;
        }
    }
    return dealer_points;
}
void check_win(int player_points,int dealer_points)
{
    cout<<"your score is "<<player_points<<endl;
    cout<<"dealer's score is "<<dealer_points<<endl;
    if (player_points>dealer_points)
    {
        cout<<"you win"<<endl;
    }
    else if (player_points<dealer_points)
    {
        cout<<"dealer wins"<<endl;
    }
    else
    {
        cout<<"it is a draw"<<endl;
    }
}
bool players_action(int player_choice)
{
    bool bust;
    if (player_choice==choices::hit)
    {
        add_player_card(VplayerHand,deck);
        show_players_cards();
        player_points=recalculate_player_points(VplayerHand,player_points);
        bust=check_bust(player_points,dealer_points);
        if (bust)
        { 
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (player_choice==choices::stand)
    {
        dealer_points=calculate_dealer_points(VdealerHand,dealer_points);
        if (dealer_points<17)
        {
            while (dealer_points<17)
            {
                add_dealer_card(VdealerHand,deck);
                dealer_points=recalculate_dealer_points(VdealerHand,dealer_points);
                bust=check_bust(player_points,dealer_points);
                if (bust==false)
                {
                    check_win(player_points,dealer_points);
                }
                
            }
        return true;    
        }
    }
    else if (player_choice==choices::surrender)
    {
        cout<<"you give up"<<endl;
        return true;
    }
}
void start_game()
{
    shuffle_deck(deck,n);
    distribute_first_cards(deck,VdealerHand,VplayerHand);
    End_of_the_game=check_blackjack(BlackJack_possibilities,VdealerHand,VplayerHand);
    show_first_cards();
    if (End_of_the_game==false)
    {
        player_points=calculate_player_points(VplayerHand,player_points);
    }
    while (End_of_the_game==false)
    {
        showing_choices();
        End_of_the_game=players_action(get_player_input());
    }
}
int main()
{   
    start_game();
    system("pause");
    return 0;
}
