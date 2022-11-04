#include <string>

const std::string vowels{"aeiouAEIOU"};

/*
 * is_vowel
 *
 * takes in a character argument and returns true of the character is a vowel.
 * If it's not a vowel then it'll return false.
 *
 * input: a single character that is being tested on if it's a vowel
 * output: a boolean based on if the character is a vowel or not
 */
bool is_vowel(char c) {
    for (int i = 0; i < vowels.length(); i++)
    {
        if (c == vowels.at(i))
        {
            return true;
        }
        
    }
    return false;
}

/*
 * is_consonant
 *
 * takes in a character argument and returns true of the character is a consonant.
 * If it's not a consonant then it'll return false.
 *
 * input: a single character that is being tested on if it's a consonant
 * output: a boolean based on if the character is a consonant or not
 */
bool is_consonant(char c) {
    for (int i = 0; i < vowels.length(); i++)
    {
        if (c == vowels.at(i))
        {
            return false;
        }
        
    }
    return true;
}

/*
 * ends_with
 *
 * If both candidate and suffix are empty strings then the function returns true.
 * If candidate is empty, but suffix is not then the function returns false.
 * If candidate ends with a suffix then the function returns true.
 * If candidate does not end with a suffix then the function returns false.
 *
 * input: two strings (candidate and suffix) testing to see
 *        if they are empty or if candidate contains the suffix
 * output: a boolean based on if the strings are empty or if the candidate ends with the suffix
 */
bool ends_with(std::string candidate, std::string suffix) {
    if (candidate.empty() && suffix.empty())
    {
        return true;
    }
    else if (candidate.empty() && !(suffix.empty())) 
    {
        return false;
    }
    else if (candidate.length() >= suffix.length())
    {
        return (0 == candidate.compare(candidate.length() - suffix.length(), suffix.length(), suffix));
    }
    else
    {
        return false;
    }
}

/*
 * ends_with_double_consonant
 *
 * If the last two characters of the string argument are both constants or
 * the same letter the function will return true. Otherwise it will return false.
 *
 * input: a string that is being tested on if it ends with two consonants
 * output: a boolean based on if the string ends with a double consonant
 */
bool ends_with_double_consonant(std::string string) {
    if (string.length() < 2){
        return false;
    }
    else {
        char lastCharacter = string.at(string.length() - 1);
        char secondLastCharacter = string.at(string.length() - 2);

        if ((is_consonant(lastCharacter) && is_consonant(secondLastCharacter)) && (lastCharacter == secondLastCharacter))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

/*
 * ends_with_cvc
 *
 * If the last three characters of the string argument are a consonant, vowel, consonant
 * (in that order) the function will return true. Otherwise it will return false.
 *
 * input: a string that is being tested on if it ends
 *        with this sequence: consonant, vowel, consonant
 * output: a boolean based on if the string ends with the cvc sequence
 */
bool ends_with_cvc(std::string string) {
    if (string == "" || string.length() < 3) {
        return false;
    }
    else {
        char lastCharacter = string.at(string.length() - 1);
        char secondLastCharacter = string.at(string.length() - 2);
        char thirdLastCharcter = string.at(string.length() - 3);

        if (is_consonant(lastCharacter) && is_vowel(secondLastCharacter) && is_consonant(thirdLastCharcter))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

/*
 * count_consonants_at_front
 *
 * The function returns the number of consecutive consonants
 * at the beginning of the string argument.
 *
 * input: a string thats first characters are being counted 
 * output: an int based on the number of consecutive
 *         consonants in the beginng of the string argument
 */
int count_consonants_at_front(std::string string) {
    if (string == "") {
        return 0;
    }
    else {
        int charIndex = 0;

        while(is_consonant(string.at(charIndex))) {
            ++charIndex;
        }
        return charIndex;
    }
}

/*
 * count_vowels_at_back
 *
 * The function returns the number of consecutive vowels at the end of the string argument.
 *
 * input: a string thats last characters are being counted
 * output: an int based on the number of consecutive vowels at the end of the string argument
 */
int count_vowels_at_back(std::string string) {
    static int charIndex = string.length() - 1;
    static int counter = 0;
    if (string == "") {
        return 0;
    }
    else {
        
        while(is_vowel(string.at(charIndex))) {
            charIndex--;
            ++counter;
        }
    
        return counter;
    }
}

/*
 * contains_vowel
 *
 * The function returns true if there is a vowel anywhere in the string argument.
 * If there is not a vowel in the string then it returns false.
 *
 * input: a string that is being tested on if it contains any vowels
 * output: a boolean based on if the string contains a vowel
 */
bool contains_vowel(std::string string) {
    for (int i = 0; i < string.length(); i++)
    {
        if (is_vowel(string.at(i)))
        {
            return true;
        }
    }
    return false;
}

/*
 * new_ending
 *
 * Returns a new string by taking the candidate string and removing the
 * last suffix characters and replacing them with the replacement string.
 *
 * input: 2 strings and an int (candidate, suffixLength, and replacement) the last characters
 *        on the candidate string are being removed based on the suffixLength number. The replacement
 *        string is then being added to the end of the candidate string.
 * output: a new string constructed from the 2 string arguments
 */
std::string new_ending(std::string candidate, int suffixLength, std::string replacement) {
    if (candidate.length() == suffixLength) {
        return replacement;
    }
    else {
        static std::string newString = "";
        
        for (int i = 0; i < candidate.length() - suffixLength; i++)
        {
            char indexChar = (candidate.at(i));
            std::string stringChar(1, indexChar);
            newString.append(stringChar);
        }

        newString.append(replacement);
        
        return newString;
    }
}