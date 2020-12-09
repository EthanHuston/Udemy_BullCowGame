// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame(); //Setting up game

    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); //Debug line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{ 
    if (bGameOver)
    {
      ClearScreen();
      SetupGame();
    }  
    else //Checking PlayerGuess
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    //Welcoming the Player
    PrintLine(TEXT("Welcome to Bulls & Cows!"));

    HiddenWord = TEXT("cakes"); 
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue...")); //Prompt Player for Guess
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again..."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    //Check if guess is correct
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You've guessed correctly! You win!"));
        EndGame();
        return;
    }

    // if (IsIsogram())//Check for Isogram
    // {
    //     PrintLine(TEXT("No repeating letters, guess again."));
    //     return;
    // }

    //Check if guess is correct length
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
        return;
    }

    //Remove a life
    PrintLine(TEXT("Lost a life!"));
    --Lives;

    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was %s."), *HiddenWord);
        EndGame();
        return;
    }

    //Show Player the Bulls and Cows
    PrintLine(TEXT("Guess again, you have %i lives left."), Lives);
}