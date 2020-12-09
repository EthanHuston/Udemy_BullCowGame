// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));
    PrintLine(TEXT("Guess the 4 letter word")); //Replace magic number!!!
    PrintLine(TEXT("Press enter to continue..."));
    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen(); 
    FString HiddenWord = TEXT("cake"); //Move outside this function

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You've guessed correctly! You win!"));
    } 
    else
    {
        PrintLine(TEXT("Wrong answer!"));
    }
    
    //PrintLine(Input);
}