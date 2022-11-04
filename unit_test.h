#ifndef __UNIT_TEST_H
#define __UNIT_TEST_H

#include <cassert>
#include <iostream>

/*
 * BEGIN: Unit testing functions.
 */
template <typename T> bool __check_result(T expected, T result) {
  if (expected != result) {
    std::cout << "FAIL: " << expected << " does not equal " << result << "\n";
    return false;
  }
  std::cout << "PASS: " << expected << " does equal " << result << "\n";
  return true;
}

template <> bool __check_result(bool expected, bool result) {
  if (expected != result) {
    std::cout << std::boolalpha << "FAIL: " << expected << " does not equal "
              << result << std::noboolalpha << "\n";
    return false;            
  }
  std::cout << std::boolalpha << "PASS: " << expected << " does equal "
            << result << std::noboolalpha << "\n";
  return true;
}

#define check_result(expected, actual) \
  if (!__check_result(expected, actual)) { \
    std::cout << "at " << __FILE__ << ":" << __LINE__ << ".\n"; \
    assert(false); \
  }

/*
 * END: Unit testing functions.
 */

#endif
