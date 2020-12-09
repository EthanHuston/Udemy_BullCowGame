// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame(); //Setting up game

    PrintLine(TEXT("The HiddenWord is: %s. \nIt is %i characters long."), *HiddenWord, HiddenWord.Len()); //Debug line

    //Welcoming the Player
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len()); //Replace magic number!!!
    PrintLine(TEXT("Press enter to continue..."));

    //Prompt for guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen(); 
    //Check PlayerGuess

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You've guessed correctly! You win!"));
    } 
    else
    {
        if (Input.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("The Hidden Word is %i characters long, Try again!"), HiddenWord.Len()); //Magic number!
        }
        
        PrintLine(TEXT("Wrong answer! You have Lost!"));
    }

    //Check if isogram
    //Prompt to guess again
    //Check if right # of characters
    //Prompt to guess again
    //If correct, win game
    //Else...
    //Decrement life
    //Are lives > 0?
    //If Yes GuessAgain/Show lives
    //If No GameOver, Show word
    //Prompt to PlayAgain
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("cake"); 
    Lives = 4; 
}