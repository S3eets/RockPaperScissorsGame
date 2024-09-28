#include <iostream>
#include <cstdlib>

using namespace std;

enum enTypeOfHand { Stone = 1, Paper = 2, Scissor = 3 };

enum enTheWiner { Player = 100, Computer = 200, NoOne = 300 };

struct stWinPoints
{
    int PlayerPoints = 0;
    int ComputerPoints = 0;
    int NoPoints = 0;

    string RoundsWiner;

    
};

int ReadNumberOfRounds(int From, int To)
{
    int Number = 0;

    do
    {
        system("color 0E");
        cout << "Enter Number of Rounds 1 to 10?  ";
        cin >> Number;

    } while (Number < From || Number > To);

    return Number;
}

short PlayerChoice(int From, int To)
{
    short PlayerChoice;

    do
    {
        system("color 0E");
        cout << "PlayerChoice: [1]:Stone, [2]:Paper, [3]:Scissor ?  ";
        cin >> PlayerChoice;

    } while (PlayerChoice < From || PlayerChoice > To);

    return PlayerChoice;
}

short ComputerChoice(int From, int To)
{
    int ComputerRandomChoice = (rand() % (To - From + 1)) + From;
    return ComputerRandomChoice;
}

enTheWiner FinedTheWiner(short PlayerChoice, short ComputerChoice)
{
    enTheWiner Winer;

    if (PlayerChoice == enTypeOfHand::Paper && ComputerChoice == enTypeOfHand::Stone)
        Winer = enTheWiner::Player;

    else if (PlayerChoice == enTypeOfHand::Stone && ComputerChoice == enTypeOfHand::Scissor)
        Winer = enTheWiner::Player;

    else if (PlayerChoice == enTypeOfHand::Scissor && ComputerChoice == enTypeOfHand::Paper)
        Winer = enTheWiner::Player;

    else if (PlayerChoice == enTypeOfHand::Scissor && ComputerChoice == enTypeOfHand::Stone)
        Winer = enTheWiner::Computer;

    else if (PlayerChoice == enTypeOfHand::Paper && ComputerChoice == enTypeOfHand::Scissor)
        Winer = enTheWiner::Computer;

    else if (PlayerChoice == enTypeOfHand::Stone && ComputerChoice == enTypeOfHand::Paper)
        Winer = enTheWiner::Computer;

    else
        Winer = enTheWiner::NoOne;

    return Winer;
}

string GetChoiceString(short Choice)
{
    switch (Choice)
    {
    case enTypeOfHand::Paper:
        return "Paper";
        break;

    case enTypeOfHand::Stone:
        return "Stone";
        break;

    case enTypeOfHand::Scissor:
        return "Scissor";
        break;

    default:
        return "NULL";
    }
}

void ShowRoundResult(short ComputerChoice, short PlayerChoice, short Counter, enTheWiner Winer)
{
    cout << "\n________________Round [" << Counter << "]________________\n\n";

    cout << "Player   Choice : " << GetChoiceString(PlayerChoice) << endl;
    cout << "Computer Choice : " << GetChoiceString(ComputerChoice) << endl;

    if (Winer == enTheWiner::Player)
        cout << "The Winer [ Player ]" << endl;
    else if (Winer == enTheWiner::Computer)
        cout << "The Winer [ Computer ]" << endl;
    else if (Winer == enTheWiner::NoOne)
        cout << "The Winer [ No Winner ]" << endl;

    cout << "\n________________________________________\n";
}

void CountingTheWinerPoints(short Player, short Computer, stWinPoints& Win)
{
    enTheWiner Winer;

    Winer = FinedTheWiner(Player, Computer);

    if (Winer == enTheWiner::Player)
        Win.PlayerPoints++;
    else if (Winer == enTheWiner::Computer)
        Win.ComputerPoints++;
    else if (Winer == enTheWiner::NoOne)
        Win.NoPoints++;
}

void StartRounds(short Rounds, stWinPoints& Win)
{
    enTheWiner Winer;
    
    int CountRounds = 0;
    short Player = 0;
    short Computer = 0;

    for (int i = 1; i <= Rounds; i++)
    {
        cout << "\n\nRound [" << i << "]: begin\n\n";

        Player = PlayerChoice(1, 3);
        Computer = ComputerChoice(1, 3);

        CountingTheWinerPoints(Player, Computer, Win);
        
        Winer = FinedTheWiner(Player, Computer);
        ShowRoundResult(Computer,Player,i,Winer);
    }


}

string FinalWinner(stWinPoints Winer)
{
    if (Winer.PlayerPoints > Winer.ComputerPoints)
        return "Player";
    else if (Winer.PlayerPoints < Winer.ComputerPoints)
        return "Computer";
    else
        return "No Winner";
}

void GameOver(stWinPoints Win, int CountRounds)
{

    cout << "________________________________________________________________________\n\n";

    cout << "\t\t\t +++ G a m e  O v e r +++\n\n";

    cout << "________________________________________________________________________\n\n";

    cout << "_____________________________ [Game Results]____________________________\n\n";

    cout << "Game Rounds       : " << CountRounds << endl;
    cout << "Player Won times  : " << Win.PlayerPoints << endl;
    cout << "Computer Won times: " << Win.ComputerPoints << endl;
    cout << "Draw times        : " << Win.NoPoints << endl;
    cout << "Final Winner      : " << FinalWinner(Win) << endl;

    cout << "\n________________________________________________________________________\n\n";
}

bool WantPlayAgin(char WantContinue)
{
    do {
        system("color 0E");
        cout << "Do you want to play again? Y/N? ";
        cin >> WantContinue;

    } while (WantContinue != 'Y' && WantContinue != 'y' && WantContinue != '1' && WantContinue != 'N' && WantContinue != 'n' && WantContinue != '0');

    if (WantContinue == 'Y' || WantContinue == 'y' || WantContinue == '1')
        return true;
    else
        return false;
}

void StartGame()
{
    stWinPoints Win;

    char WantContinue = 'Y';
    int CountRounds = 0;
    short Rounds;

    do
    {
        system("cls");

        Rounds = ReadNumberOfRounds(1, 10);

        StartRounds(Rounds, Win);

        CountRounds += Rounds;
        GameOver(Win, CountRounds);

    } while (WantPlayAgin(WantContinue));
}

int main()
{
    srand((unsigned)time(NULL));
    
    StartGame();

    return 0;
}
