#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generateGuesses(
    string& in,
    string& floating,
    set<string>& dict,
    set<string>& guesses,
    int index);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    string input = in;
    string yellow = floating;
    set<string> dictionary = dict;
    set<string> guesses;
    generateGuesses(input, yellow, dictionary, guesses, 0);
    return guesses;
}

// Define any helper functions here
void generateGuesses(
    string& in,
    string& floating,
    set<string>& dict,
    set<string>& guesses,
    int index)
{
    if(in.empty()) //if input is empty return empty set
        return;

    if(index == in.size()){ //if we reached the end position of the word
        if(floating.empty() && dict.find(in) != dict.end()) // add word if all floating letters used & word is in dictionary
            guesses.insert(in);
      return;
    }

    if(in[index] != '-'){ //if letter is known at this position, move on to next position
      generateGuesses(in, floating, dict, guesses, index + 1);
      return;
    }

		//tries all possible letters in blank
    for(char i='a'; i<='z'; ++i){
        in[index] = i;
        size_t pos = floating.find(i);
        if(pos != string::npos){   		//checks if this is one of the floating letters
            string newFloating = floating;
            newFloating.erase(pos,1);
            generateGuesses(in, newFloating, dict, guesses, index+ 1);
        }
        else{				// if not floating		
            int count = 0;
            for(int i = index + 1; i < in.size(); ++i){ //count number of blanks
                if(in[i] == '-')
                    count++;
            }
            if(floating.size() <= count + 1) //moves onto next index if unused floating letters can fit later
                generateGuesses(in, floating, dict, guesses, index+1);
        }
    }
	in[index] = '-'; //reset to blank so other iterations can try other letters
}