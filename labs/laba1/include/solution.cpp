#include "solution.h"

int countVowels(const std::string& str) {
    int count = 0;
    for (char ch : str) {
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y') {
            count++;
        }
    }
    return count;
}
