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
    Isograms = GetValidWords(HiddenWordList);

    SetupGame(); //Setting up game
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{ 
    if (bGameOver)
    {
      ClearScreen();
      SetupGame();
    }  
    else //Checking PlayerGuess
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    //Welcoming the Player
    PrintLine(TEXT("Welcome to Bulls & Cows!"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)]; 
    Lives = HiddenWord.Len() + 3;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    //PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); //Debug line
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue...")); //Prompt Player for Guess
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again..."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
    int32 Bulls, Cows;
    GetBullCows(Guess, Bulls, Cows);

    PrintLine(TEXT("You have %i Bulls and %i Cows."), Bulls, Cows);

    PrintLine(TEXT("Guess again, you have %i lives left."), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& HiddenWords) const
{
    TArray<FString> ValidWords;

    for(FString Word : HiddenWords)
    {
        if(Word.Len() >= 4 && Word.Len() <=8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    BullCount = 0;
    CowCount = 0;

    for (int32  GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            BullCount++;
            continue;
        }

        for(int32 HiddenIndex = 0; HiddenIndex < Guess.Len(); HiddenIndex++)
        {
            if(Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                CowCount++;
                break;
            }
        }
        
    }
    
}