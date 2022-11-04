#ifndef __STEMMER_H
#define __STEMMER_H

#include <iostream>
#include <string>
#include <cassert>

/*
 * Forward declare functions that are defined in stemmer.cpp
 * but that we use here.
 */
bool apply_rule(std::string candidate, std::string suffix,
                std::string replacement, std::string &result);
int count_consonants_at_front(std::string str);
int count_vowels_at_back(std::string str);
bool ends_with_cvc(std::string str);
bool contains_vowel(std::string str);
bool ends_with_double_consonant(std::string str);
std::string maybe_remove_suffix(std::string candidate, std::string suffix);
bool is_vowel(char c);
bool ends_with(std::string candidate, std::string suffix);
std::string new_ending(std::string candidate, int suffix, std::string);

/*
 * Declare an enumerated type so that we can easily
 * create a variable that will tell us whether a letter
 * is a vowel or a consonant.
 */
enum class LetterType { vowel, consonant };

LetterType get_letter_type(char c);

/*
 * calculate_m
 *
 * Use the algorithm at https://tartarus.org/martin/PorterStemmer/def.txt
 * to calculate m for _str_.
 *
 * input: The string on which to calculate m.
 * output: m for the string argument.
 */
int calculate_m(const std::string &str);

/*
 * maybe_remove_suffix
 *
 * If _candidate_ ends in _suffix_, this function will return
 * a string identical to _candidate_ but without _suffix_.
 *
 * input: a candidate string and a suffix string.
 * output: a (possibly) _suffix_-free copy of _candidate_.
 */
std::string maybe_remove_suffix(std::string candidate, std::string suffix);

/*
 * apply_rule
 *
 * If _candidate_ ends in _suffix_, then this function will 1) output
 * (via output parameter _result_) a copy of _candidate_ where _suffix_ is
 * replaced with _replacement_ and 2) return true.
 * Otherwise, this function will not alter _result_ and return false.
 *
 * input: a candidate string, a suffix string and a replacement string.
 * output: whether the rule applies (return value) and the (possibly)
 * altered version of candidate (via _result_).
 */
bool apply_rule(std::string candidate, std::string suffix,
                std::string replacement, std::string &result);

/*
 * step_1a
 *
 * This function will return an updated copy of _base_ according to the
 * specification of Step 1a of the Porter Stemming Algorithm.
 *
 * input: a string to manipulate
 * output: an updated version of the input string transformed according
 * to Step 1a of the Porter Stemming Algorithm.
 */
std::string step_1a(std::string base);

/*
 * step_1b
 *
 * This function will return an updated copy of _base_ according to the
 * specification of Step 1b of the Porter Stemming Algorithm.
 *
 * input: a string to manipulate
 * output: an updated version of the input string transformed according
 * to Step 1b of the Porter Stemming Algorithm.
 */
std::string step_1b(std::string base);

/*
 * step_1c
 *
 * This function will return an updated copy of _base_ according to the
 * specification of Step 1c of the Porter Stemming Algorithm.
 *
 * input: a string to manipulate
 * output: an updated version of the input string transformed according
 * to Step 1c of the Porter Stemming Algorithm.
 */
std::string step_1c(std::string base);

/*
 * step_2
 *
 * This function will return an updated copy of _base_ according to the
 * specification of Step 2 of the Porter Stemming Algorithm.
 *
 * input: a string to manipulate
 * output: an updated version of the input string transformed according
 * to Step 2 of the Porter Stemming Algorithm.
 */
std::string step_2(std::string base);

/*
 * step_3
 *
 * This function will return an updated copy of _base_ according to the
 * specification of Step 3 of the Porter Stemming Algorithm.
 *
 * input: a string to manipulate
 * output: an updated version of the input string transformed according
 * to Step 3 of the Porter Stemming Algorithm.
 */
std::string step_3(std::string base);

/*
 * step_4
 *
 * This function will return an updated copy of _base_ according to the
 * specification of Step 4 of the Porter Stemming Algorithm.
 *
 * input: a string to manipulate
 * output: an updated version of the input string transformed according
 * to Step 4 of the Porter Stemming Algorithm.
 */
std::string step_4(std::string base);

/*
 * step_5
 *
 * This function will return an updated copy of _base_ according to the
 * specification of Step 5 of the Porter Stemming Algorithm.
 *
 * input: a string to manipulate
 * output: an updated version of the input string transformed according
 * to Step 5 of the Porter Stemming Algorithm.
 */
std::string step_5(std::string base);

#endif
