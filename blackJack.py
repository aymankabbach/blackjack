import random
dealer_Hand=[]
player_Hand=[]
dealer_Score=0
player_Score=0
Counter_A_player=0
Counter_A_dealer=0
End_of_The_Game=False
Deck=["A",2,3,4,5,6,7,8,9,10,"J","Q","K"]*4
BlackJack_possibilities=[["A",10],["A","J"],["A","Q"],["A","K"],[10,"A"],["J","A"],["Q","A"],["K","A"]]
choices=["hit","stand","surrender"]
def shuffle_Deck():
    random.shuffle(Deck)
def Distribute_Cards():
    for x in range(2):
        dealer_Hand.append(Deck.pop(0))
        player_Hand.append(Deck.pop(0))
    print(f"one of the dealer's card is : {random.choice(dealer_Hand)}")
    print(f"your cards are :{player_Hand}")
def check_BlackJack():
    global End_of_The_Game
    if player_Hand in BlackJack_possibilities and dealer_Hand in BlackJack_possibilities: 
        End_of_The_Game=True
        print("it is a push")
    elif player_Hand in BlackJack_possibilities :
        End_of_The_Game=True
        print("you get a BlackJack")
        print("you win")
    elif dealer_Hand in BlackJack_possibilities :
        End_of_The_Game=True
        print(dealer_Hand)
        print("the dealer gets a Blackjack")
        print("dealer wins")
def showing_Choices():
    x=0
    for choice in choices:
        print(x+1,choice)
        x=x+1
def read_player_choice():
    user_choice=int(input("what is your choice"))
    return user_choice
def get_player_choice():
    wrong_input=True
    user_choice : int
    while wrong_input==True or user_choice<1 or user_choice>len(choices):
        try:
            user_choice=read_player_choice()
        except ValueError:
            print("invalid input, Please enter an integer")
        else:
            if user_choice<1 or user_choice>len(choices):
                print("Please enter an integer between 1 and 3")
            else:
                wrong_input=False
    return user_choice
def hit_Choice():
    player_Hand.append(Deck.pop(0))
    print(player_Hand)
def hit_Choice_dealer():
    dealer_Hand.append(Deck.pop(0))
    print(dealer_Hand)
def stand_Choice():
    Calculate_Dealer_Score()
    if dealer_Score<17:
        while dealer_Score<17:
            hit_Choice_dealer()
            Calculate_New_Dealer_Score()
            check_Bust()
def surrender_Choice():
    global End_of_The_Game
    End_of_The_Game=True
    print("you give up")
def check_Bust():
    global player_Score,End_of_The_Game,dealer_Score
    if player_Score>21:
        End_of_The_Game=True
        print("it is a bust \nyou lose")
    if dealer_Score>21:
        End_of_The_Game=True
        print("it is a bust \nyou win")
def Calculate_Player_Score():
    global player_Score,player_Hand,Counter_A_player
    for card in player_Hand:
        if card=="J" or card=="Q" or card=="K":
            player_Score=player_Score+10
        elif card=="A":
            player_Score=player_Score+11
            Counter_A_player=Counter_A_player+1
        else :
            player_Score=player_Score+card
    x=0
    if player_Score > 21 and "A" in player_Hand:
        while x<Counter_A_player:
            player_Score=player_Score-11+1
            x=x+1
def Calculate_Dealer_Score():
    global dealer_Score,dealer_Hand,Counter_A_dealer
    print(f"dealer's hand : {dealer_Hand}")
    for card in dealer_Hand:
        if card=="J" or card=="Q" or card=="K":
            dealer_Score=dealer_Score+10
        elif card=="A":
            dealer_Score=dealer_Score+11
            Counter_A_dealer=Counter_A_dealer+1
        else :
            dealer_Score=dealer_Score+card
    x=0
    if dealer_Score > 21 and "A" in dealer_Hand:
        while x<Counter_A_dealer:
            dealer_Score=dealer_Score-11+1
            x=x+1
def Calculate_New_Player_Score():
    global player_Score,player_Hand,Counter_A_player
    if player_Hand[-1]=="J" or player_Hand[-1]=="Q" or player_Hand[-1]=="K":
        player_Score=player_Score+10
    elif player_Hand[-1]=="A":
            player_Score=player_Score+11
            Counter_A_player=0
            Counter_A_player=Counter_A_player+1
    else:
        player_Score=player_Score+player_Hand[-1]
    if player_Score > 21 and "A" in player_Hand and Counter_A_player>0:
        x=0
        while x<Counter_A_player:
            player_Score=player_Score-11+1
            x=x+1
        Counter_A_player=0
def Calculate_New_Dealer_Score():
    global dealer_Score,dealer_Hand,Counte_r_Adealer
    if dealer_Hand[-1]=="J" or dealer_Hand[-1]=="Q" or dealer_Hand[-1]=="K":
        dealer_Score=dealer_Score+10
    elif dealer_Hand[-1]=="A":
            dealer_Score=dealer_Score+11
            Counter_A_dealer=0
            Counter_A_dealer=Counter_A_dealer+1
    else:
        dealer_Score=dealer_Score+dealer_Hand[-1]
    if dealer_Score > 21 and "A" in dealer_Hand and Counter_A_dealer>0:
        x=0
        while x<Counter_A_dealer:
            dealer_Score=dealer_Score-11+1
            x=x+1
        Counter_A_dealer=0
def check_win():
    global End_of_The_Game,player_Score,dealer_Score
    if End_of_The_Game==False:
        End_of_The_Game=True
        if player_Score>dealer_Score:
            print(f"your score is : {player_Score}")
            print(f"the dealer's score is :{dealer_Score}")
            print("you win")
        elif dealer_Score>player_Score:
            print(f"your score is : {player_Score}")
            print(f"the dealer's score is : {dealer_Score}")
            print("the dealer wins")
        elif player_Score==dealer_Score:
            print("it is a draw")
def Start_Game():
    global End_of_The_Game
    shuffle_Deck()
    Distribute_Cards()
    check_BlackJack()
    if End_of_The_Game==False:
        Calculate_Player_Score()
    while End_of_The_Game==False:
        showing_Choices()
        player_Choice=get_player_choice()
        if player_Choice==1:
            hit_Choice()
            Calculate_New_Player_Score()
            check_Bust()
        elif player_Choice==2:
            stand_Choice()
            check_win()
        elif player_Choice==3:
            surrender_Choice()
Start_Game()
        





