#include <iostream>
#include <string>
#include <cassert>

#include "stemmer.h"

LetterType get_letter_type(char c) {
  if (is_vowel(c)) {
    return LetterType::vowel;
  }
  return LetterType::consonant;
}

int calculate_m(const std::string &str) {
  int begin = count_consonants_at_front(str);
  int end = str.length() - count_vowels_at_back(str);

  if (begin > end) {
    std::cout << "Oops: begin > end in calculate_m. Be sure to check that"
                 "count_consonants_at_front and count_vowels_at_back are "
                 "implemented correctly.";
    assert(false);
  }

  std::string calculable = str.substr(begin, end - begin);

  if (calculable.length() == 0) {
    return 0;
  }

  LetterType last_letter_type = LetterType::vowel;

  int m{0};
  for (int i = 1; i < calculable.length(); i++) {
    if (last_letter_type != get_letter_type(calculable.at(i))) {
      last_letter_type = get_letter_type(calculable.at(i));
      m++;
    }
  }

  /*
   * The loop above calculates the number of flip/flops between vowel and
   * consonant runs -- but m is the number of flip/flops between
   * vowel/consonant-run pairs. Therefore, we divide m by 2!
   */
  return (m + 1) / 2;
}
std::string maybe_remove_suffix(std::string candidate, std::string suffix) {
  if (ends_with(candidate, suffix)) {
    return new_ending(candidate, suffix.length(), std::string{""});
  }
  return candidate;
}

bool apply_rule(std::string candidate, std::string suffix,
                std::string replacement, std::string &result) {
  if (ends_with(candidate, suffix)) {
    result = new_ending(candidate, suffix.length(), replacement);
    return true;
  }
  result = candidate;
  return false;
}

std::string step_1a(std::string base) {
  std::string result{base};
  bool s1a =
      (apply_rule(base, std::string{"sses"}, std::string{"ss"}, result) ||
       apply_rule(base, std::string{"ies"}, std::string{"i"}, result) ||
       apply_rule(base, std::string{"ss"}, std::string{"ss"}, result) ||
       apply_rule(base, std::string{"s"}, std::string{""}, result));
  return result;
}

std::string step_1b(std::string base) {
  std::string result{base};

  if (ends_with(base, std::string{"eed"})) {
    if (calculate_m(maybe_remove_suffix(base, std::string{"eed"})) > 0) {
      apply_rule(base, std::string{"eed"}, std::string{"ee"}, result);
    }
    return result;
  }
  bool s1b1_or_2 =
      contains_vowel(maybe_remove_suffix(base, std::string{"ed"})) &&
      apply_rule(base, std::string{"ed"}, std::string{""}, result);
  s1b1_or_2 = s1b1_or_2 ||
              (contains_vowel(maybe_remove_suffix(base, std::string{"ing"})) &&
               apply_rule(base, std::string{"ing"}, std::string{""}, result));

  if (s1b1_or_2) {
    apply_rule(result, std::string{"at"}, std::string{"ate"}, result) ||
    apply_rule(result, std::string{"bl"}, std::string{"ble"}, result) ||
    apply_rule(result, std::string{"iz"}, std::string{"ize"}, result) ||
    (
      (ends_with_double_consonant(result) &&
       !(result.at(result.length() - 1) == 'l' ||
         result.at(result.length() - 1) == 's' ||
         result.at(result.length() - 1) == 'z')
      ) &&
      apply_rule(result, std::string{result.at(result.length() - 1)}, std::string{""}, result)
    ) ||
    (
      (calculate_m(result) == 1 && ends_with_cvc(result)) && std::string{""} != (result = result + std::string{"e"})
    );
  }
  return result;
}

std::string step_1c(std::string base) {
  std::string result{base};
  if (contains_vowel(maybe_remove_suffix(base, std::string{"y"}))) {
    apply_rule(base, std::string{"y"}, std::string{"i"}, result);
  }
  return result;
}

std::string step_2(std::string base) {
  std::string result{base};
  bool did_step = 
    ((calculate_m(maybe_remove_suffix(base, std::string{"ational"})) > 0) && apply_rule(base, std::string{"ational"}, std::string{"ate"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"tional"})) > 0) && apply_rule(base, std::string{"tional"}, std::string{"tion"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"enci"})) > 0) && apply_rule(base, std::string{"enci"}, std::string{"ence"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"anci"})) > 0) && apply_rule(base, std::string{"anci"}, std::string{"ance"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"izer"})) > 0) && apply_rule(base, std::string{"izer"}, std::string{"ize"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"abli"})) > 0) && apply_rule(base, std::string{"abli"}, std::string{"able"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"alli"})) > 0) && apply_rule(base, std::string{"alli"}, std::string{"al"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"entli"})) > 0) && apply_rule(base, std::string{"entli"}, std::string{"ent"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"eli"})) > 0) && apply_rule(base, std::string{"eli"}, std::string{"e"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ousli"})) > 0) && apply_rule(base, std::string{"ousli"}, std::string{"ous"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ization"})) > 0) && apply_rule(base, std::string{"ization"}, std::string{"ize"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ation"})) > 0) && apply_rule(base, std::string{"ation"}, std::string{"ate"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ator"})) > 0) && apply_rule(base, std::string{"ator"}, std::string{"ate"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"alism"})) > 0) && apply_rule(base, std::string{"alism"}, std::string{"al"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"iveness"})) > 0) && apply_rule(base, std::string{"iveness"}, std::string{"ive"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"fulness"})) > 0) && apply_rule(base, std::string{"fulness"}, std::string{"ful"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ousness"})) > 0) && apply_rule(base, std::string{"ousness"}, std::string{"ous"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"aliti"})) > 0) && apply_rule(base, std::string{"aliti"}, std::string{"al"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"iviti"})) > 0) && apply_rule(base, std::string{"iviti"}, std::string{"ive"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"biliti"})) > 0) && apply_rule(base, std::string{"biliti"}, std::string{"ble"}, result));
  return result;
}

std::string step_3(std::string base) {
  std::string result{base};
  bool did_step = 
    ((calculate_m(maybe_remove_suffix(base, std::string{"icate"})) > 0) && apply_rule(base, std::string{"icate"}, std::string{"ic"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ative"})) > 0) && apply_rule(base, std::string{"ative"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"alize"})) > 0) && apply_rule(base, std::string{"alize"}, std::string{"al"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"iciti"})) > 0) && apply_rule(base, std::string{"iciti"}, std::string{"ic"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ical"})) > 0) && apply_rule(base, std::string{"ical"}, std::string{"ic"}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ful"})) > 0) && apply_rule(base, std::string{"ful"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ness"})) > 0) && apply_rule(base, std::string{"ness"}, std::string{""}, result));
  return result;
}

std::string step_4(std::string base) {
  std::string result{base};
  bool did_step = 
    ((calculate_m(maybe_remove_suffix(base, std::string{"al"})) > 1) && apply_rule(base, std::string{"al"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ance"})) > 1) && apply_rule(base, std::string{"ance"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ence"})) > 1) && apply_rule(base, std::string{"ence"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"er"})) > 1) && apply_rule(base, std::string{"er"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ic"})) > 1) && apply_rule(base, std::string{"ic"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"able"})) > 1) && apply_rule(base, std::string{"able"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ible"})) > 1) && apply_rule(base, std::string{"ible"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ant"})) > 1) && apply_rule(base, std::string{"ant"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ement"})) > 1) && apply_rule(base, std::string{"ement"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ment"})) > 1) && apply_rule(base, std::string{"ment"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ent"})) > 1) && apply_rule(base, std::string{"ent"}, std::string{""}, result)) ||
    (
      (calculate_m(maybe_remove_suffix(base, std::string{"ion"})) > 1 && (ends_with(maybe_remove_suffix(base, std::string{"ion"}),std::string{"s"}) || ends_with(maybe_remove_suffix(base, std::string{"ion"}), std::string{"t"}))) &&
      (apply_rule(base, std::string{"ion"}, std::string{""}, result))
    ) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ou"})) > 1) && apply_rule(base, std::string{"ou"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ism"})) > 1) && apply_rule(base, std::string{"ism"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ate"})) > 1) && apply_rule(base, std::string{"ate"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"iti"})) > 1) && apply_rule(base, std::string{"iti"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ous"})) > 1) && apply_rule(base, std::string{"ous"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ive"})) > 1) && apply_rule(base, std::string{"ive"}, std::string{""}, result)) ||
    ((calculate_m(maybe_remove_suffix(base, std::string{"ize"})) > 1) && apply_rule(base, std::string{"ize"}, std::string{""}, result));
  return result;
}

std::string step_5(std::string base) {
  std::string result{base};
  bool did_step_5a = 
    ((calculate_m(maybe_remove_suffix(base, std::string{"e"})) > 1) && apply_rule(base, std::string{"e"}, std::string{""}, result)) ||
    (
      ( calculate_m(maybe_remove_suffix(base, std::string{"e"})) == 1 && !ends_with_cvc(maybe_remove_suffix(base, std::string{"e"}))) && 
      apply_rule(base, std::string{"e"}, std::string{""}, result)
    );

  bool did_step_5b = (
      ( calculate_m(result) > 1 && ends_with_double_consonant(result) && result.at(result.length()-1) == 'l') && 
      apply_rule(result, std::string{"l"}, std::string{""}, result)
    );
  return result;
}

