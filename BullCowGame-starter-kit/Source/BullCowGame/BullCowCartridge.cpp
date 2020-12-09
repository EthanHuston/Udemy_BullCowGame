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
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));

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
    PrintLine(TEXT("Press enter to continue..."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
        {
            PrintLine(TEXT("You've guessed correctly! You win!"));
            EndGame();
        } 
        else
        {
            PrintLine(TEXT("Lost a life!"));
            PrintLine(TEXT("%i"), --Lives);
            if(Lives > 0)
            {
                if (Guess.Len() != HiddenWord.Len())
                {
                     PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
                }
            }
            else
            {
                PrintLine(TEXT("You have no lives left!"));
                EndGame();
            } 
        }
}