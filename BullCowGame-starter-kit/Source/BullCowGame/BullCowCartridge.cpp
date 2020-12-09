// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    //Load Words from file
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordList/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(HiddenWordList, *WordListPath);


    SetupGame(); //Setting up game

    PrintLine(TEXT("The number of valid words is %i"), GetValidWords(HiddenWordList).Num());
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
    //Check if guess is correct length
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
        return;
    }

    if (!IsIsogram(Guess))//Check for Isogram
    {
        PrintLine(TEXT("No repeating letters, guess again."));
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

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for(int32 Index = 0; Index < Word.Len() - 1; Index++)
    {
        for(int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if(Word[Index] == Word[Comparison]) return false;
        }
    }
    
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> HiddenWords) const
{
    TArray<FString> ValidWords;

    for(int32 Index = 0 ; Index < HiddenWords.Num() ; Index++)
    {
        if(HiddenWords[Index].Len() >= 4 && HiddenWords[Index].Len() <=8 && IsIsogram(HiddenWords[Index]))
        {
            ValidWords.Emplace(HiddenWords[Index]);
        }
    }
    return ValidWords;
}