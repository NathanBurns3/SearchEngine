#include <cassert>
#include <ios>
#include <iostream>

#include "helpers.h"

#include "unit_test.h"

#include "stemmer.h"

/*
 * stem
 *
 * Stem _base_ according to the Porter Stemming Algorithm using helper
 * functions defined in stemmer.h.
 *
 * input: A string, _base_, to stem.
 * output: A stemmed version of _base_.
 */
std::string stem(std::string base) {
  std::string result{""};

  result = step_1a(base);
  result = step_1b(result);
  result = step_1c(result);
  result = step_2(result);
  result = step_3(result);
  result = step_4(result);
  result = step_5(result);
  return result;
}

int main() {

  /*
   * Start of unit tests for is_vowel()
   */
  check_result(true, is_vowel('a'));
  check_result(true, is_vowel('e'));
  check_result(true, is_vowel('i'));
  check_result(true, is_vowel('o'));
  check_result(true, is_vowel('u'));

  /*
   * Start of unit tests for is_consonant()
   */
  check_result(true, is_consonant('b'));
  check_result(true, is_consonant('c'));
  check_result(true, is_consonant('d'));
  check_result(true, is_consonant('f'));
  check_result(true, is_consonant('g'));
  check_result(true, is_consonant('h'));
  check_result(true, is_consonant('j'));
  check_result(true, is_consonant('k'));
  check_result(true, is_consonant('l'));
  check_result(true, is_consonant('m'));
  check_result(true, is_consonant('n'));
  check_result(true, is_consonant('p'));
  check_result(true, is_consonant('q'));
  check_result(true, is_consonant('r'));
  check_result(true, is_consonant('s'));
  check_result(true, is_consonant('t'));
  check_result(true, is_consonant('v'));
  check_result(true, is_consonant('w'));
  check_result(true, is_consonant('x'));
  check_result(true, is_consonant('y'));
  check_result(true, is_consonant('z'));

  /*
   * Start of unit tests for ends_with_double_consonant()
   */
  check_result(false, ends_with_double_consonant(std::string{""}));
  check_result(false, ends_with_double_consonant(std::string{"a"}));
  check_result(false, ends_with_double_consonant(std::string{"aa"}));
  check_result(false, ends_with_double_consonant(std::string{"ra"}));
  check_result(true, ends_with_double_consonant(std::string{"rr"}));
  check_result(false, ends_with_double_consonant(std::string{"rd"}));

  /*
   * Start of unit tests for count_consonants_at_front()
   */
  check_result(21, count_consonants_at_front(std::string{"bcdfghjklmnpqrstvwxyzaeiou"}));
  check_result(2, count_consonants_at_front(std::string{"tree"}));
  check_result(0, count_consonants_at_front(std::string{""}));

  /*
   * Start of unit tests for count_vowels_at_back()
   */
  check_result(5, count_vowels_at_back(std::string{"bcdfghjklmnpqrstvwxyzaeiou"}));
  check_result(2, count_vowels_at_back(std::string{"tree"}));
  check_result(0, count_vowels_at_back(std::string{""}));

  /*
   * Start of unit tests for ends_with_cvc()
   */
  check_result(false, ends_with_cvc(std::string{""}));
  check_result(false, ends_with_cvc(std::string{"a"}));
  check_result(false, ends_with_cvc(std::string{"aa"}));
  check_result(false, ends_with_cvc(std::string{"aaa"}));
  check_result(false, ends_with_cvc(std::string{"straaa"}));
  check_result(false, ends_with_cvc(std::string{"rrr"}));
  check_result(false, ends_with_cvc(std::string{"fiverrr"}));
  check_result(true, ends_with_cvc(std::string{"car"}));
  check_result(true, ends_with_cvc(std::string{"racecar"}));

  /*
   * Start of unit tests for contains_vowel()
   */
  check_result(false, contains_vowel(std::string{""}));
  check_result(false, contains_vowel(std::string{"b"}));
  check_result(true, contains_vowel(std::string{"a"}));
  check_result(false, contains_vowel(std::string{"rr"}));
  check_result(true, contains_vowel(std::string{"rar"}));

  /*
   * Start of unit tests for new_ending()
   */
  check_result(std::string{""}, new_ending(std::string{"end"}, 3, std::string{""}));
  check_result(std::string{"ing"}, new_ending(std::string{"end"}, 3, std::string{"ing"}));
  check_result(std::string{"extr"}, new_ending(std::string{"extra"}, 1, std::string{""}));
  check_result(std::string{"extro"}, new_ending(std::string{"extra"}, 1, std::string{"o"}));
  check_result(std::string{"extern"}, new_ending(std::string{"extra"}, 2, std::string{"ern"}));

  /*
   * Start of unit tests for ends_with()
   */
  check_result(false, ends_with(std::string{""}, std::string{"esse"}));
  check_result(true, ends_with(std::string{""}, std::string{""}));
  check_result(true, ends_with(std::string{"anything"}, std::string{""}));
  check_result(true, ends_with(std::string{"finesse"}, std::string{"esse"}));
  check_result(true, ends_with(std::string{"retest"}, std::string{"test"}));
  check_result(false, ends_with(std::string{"test"}, std::string{"detest"}));


  /*
   * Start of unit tests for calculate_m()
   */
  check_result(0, calculate_m(std::string{"tr"}));
  check_result(0, calculate_m(std::string{"ee"}));
  check_result(0, calculate_m(std::string{"by"}));
  check_result(1, calculate_m(std::string{"trouble"}));
  check_result(2, calculate_m(std::string{"oaten"}));
  check_result(2, calculate_m(std::string{"orrery"}));

  /*
   * Start of unit tests for stem()
   */
  check_result(std::string{"caress"}, stem(std::string{"caresses"}));
  check_result(std::string{"poni"}, stem(std::string{"ponies"}));
  check_result(std::string{"ti"}, stem(std::string{"ties"}));
  check_result(std::string{"caress"}, stem(std::string{"caress"}));
  check_result(std::string{"cat"}, stem(std::string{"cats"}));
  check_result(std::string{"feed"}, stem(std::string{"feed"}));
  check_result(std::string{"agre"}, stem(std::string{"agreed"}));
  check_result(std::string{"plaster"}, stem(std::string{"plastered"}));
  check_result(std::string{"bled"}, stem(std::string{"bled"}));
  check_result(std::string{"motor"}, stem(std::string{"motoring"}));
  check_result(std::string{"sing"}, stem(std::string{"sing"}));
  check_result(std::string{"conflat"}, stem(std::string{"conflated"}));
  check_result(std::string{"troubl"}, stem(std::string{"troubled"}));
  check_result(std::string{"size"}, stem(std::string{"sized"}));
  check_result(std::string{"hop"}, stem(std::string{"hopping"}));
  check_result(std::string{"tan"}, stem(std::string{"tanned"}));
  check_result(std::string{"fall"}, stem(std::string{"falling"}));
  check_result(std::string{"hiss"}, stem(std::string{"hissing"}));
  check_result(std::string{"fizz"}, stem(std::string{"fizzed"}));
  check_result(std::string{"fail"}, stem(std::string{"failing"}));
  check_result(std::string{"file"}, stem(std::string{"filing"}));
  check_result(std::string{"happi"}, stem(std::string{"happy"}));
  check_result(std::string{"sky"}, stem(std::string{"sky"}));
  check_result(std::string{"relat"}, stem(std::string{"relational"}));
  check_result(std::string{"condit"}, stem(std::string{"conditional"}));
  check_result(std::string{"ration"}, stem(std::string{"rational"}));
  check_result(std::string{"valenc"}, stem(std::string{"valenci"}));
  check_result(std::string{"hesit"}, stem(std::string{"hesitanci"}));
  check_result(std::string{"digit"}, stem(std::string{"digitizer"}));
  check_result(std::string{"conform"}, stem(std::string{"conformabli"}));
  check_result(std::string{"differ"}, stem(std::string{"differentli"}));
  check_result(std::string{"vile"}, stem(std::string{"vileli"}));
  check_result(std::string{"analog"}, stem(std::string{"analogousli"}));
  check_result(std::string{"vietnam"}, stem(std::string{"vietnamization"}));
  check_result(std::string{"predic"}, stem(std::string{"predicate"}));
  check_result(std::string{"oper"}, stem(std::string{"operator"}));
  check_result(std::string{"feudal"}, stem(std::string{"feudalism"}));
  check_result(std::string{"decis"}, stem(std::string{"decisiveness"}));
  check_result(std::string{"hope"}, stem(std::string{"hopefulness"}));
  check_result(std::string{"callous"}, stem(std::string{"callousness"}));
  check_result(std::string{"formal"}, stem(std::string{"formaliti"}));
  check_result(std::string{"sensit"}, stem(std::string{"sensitiviti"}));
  check_result(std::string{"sensibl"}, stem(std::string{"sensibiliti"}));
  check_result(std::string{"triplic"}, stem(std::string{"triplicate"}));
  check_result(std::string{"form"}, stem(std::string{"formative"}));
  check_result(std::string{"formal"}, stem(std::string{"formalize"}));
  check_result(std::string{"electr"}, stem(std::string{"electriciti"}));
  check_result(std::string{"electr"}, stem(std::string{"electrical"}));
  check_result(std::string{"hope"}, stem(std::string{"hopeful"}));
  check_result(std::string{"good"}, stem(std::string{"goodness"}));
  check_result(std::string{"reviv"}, stem(std::string{"revival"}));
  check_result(std::string{"allow"}, stem(std::string{"allowance"}));
  check_result(std::string{"infer"}, stem(std::string{"inference"}));
  check_result(std::string{"airlin"}, stem(std::string{"airliner"}));
  check_result(std::string{"gyroscop"}, stem(std::string{"gyroscopic"}));
  check_result(std::string{"adjust"}, stem(std::string{"adjustable"}));
  check_result(std::string{"defens"}, stem(std::string{"defensible"}));
  check_result(std::string{"irrit"}, stem(std::string{"irritant"}));
  check_result(std::string{"replac"}, stem(std::string{"replacement"}));
  check_result(std::string{"adjust"}, stem(std::string{"adjustment"}));
  check_result(std::string{"depend"}, stem(std::string{"dependent"}));
  check_result(std::string{"adopt"}, stem(std::string{"adoption"}));
  check_result(std::string{"homolog"}, stem(std::string{"homologou"}));
  check_result(std::string{"homolog"}, stem(std::string{"homologous"}));
  check_result(std::string{"commun"}, stem(std::string{"communism"}));
  check_result(std::string{"activ"}, stem(std::string{"activate"}));
  check_result(std::string{"angular"}, stem(std::string{"angulariti"}));
  check_result(std::string{"effect"}, stem(std::string{"effective"}));
  check_result(std::string{"bowdler"}, stem(std::string{"bowdlerize"}));
  check_result(std::string{"probat"}, stem(std::string{"probate"}));
  check_result(std::string{"rate"}, stem(std::string{"rate"}));
  check_result(std::string{"ceas"}, stem(std::string{"cease"}));
  check_result(std::string{"control"}, stem(std::string{"controlling"}));
  check_result(std::string{"roll"}, stem(std::string{"roll"}));
  check_result(std::string{"roll"}, stem(std::string{"rolling"}));

  return 0;
}
