#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    void reverseString (vector<char>& s) {
        for (int i = 0, j = s.size() - 1; i < s.size() / 2; ++ i, -- j)
            swap(s[i], s[j]);
    }

    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += (2 * k)) {
            if (i + k <= s.size())
                reverse(s.begin() + i, s.begin() + i + k);
            else 
                reverse(s.begin() + i, s.end());
        }
        return s;
    }

    void Reverse(string& s, int start, int end){ //翻转，区间写法：左闭右闭 []
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }

    void removeExtraSpaces(string& s) {
        // This function processes a string to:
        // 1. Remove leading and trailing spaces
        // 2. Ensure exactly one space between words
        // 3. Handle the string in-place to be memory efficient
        
        int writePos = 0;         // Position where we'll write characters in the result
        bool isFirstWord = true;  // Flag to track if we're processing the first word
        
        // Iterate through each character in the input string
        for (int readPos = 0; readPos < s.size(); readPos++) {
            // If current character is not a space, we've found a word
            if (s[readPos] != ' ') {
                // If this is not the first word, add a single space as separator
                if (!isFirstWord) {
                    s[writePos++] = ' ';
                } else {
                    // Mark that we've processed the first word
                    isFirstWord = false;
                }
                
                // Copy all characters of the current word
                while (readPos < s.size() && s[readPos] != ' ') {
                    s[writePos++] = s[readPos++];
                }
                
                // Adjust readPos since the for loop will increment it again
                // This prevents skipping a character
                readPos--;
            }
            // If current character is a space, just skip it
            // This effectively removes consecutive spaces
        }
        
        // Resize the string to remove any unused characters at the end
        // This gives us the final string with proper spacing
        s.resize(writePos);
    }

    string reverseWords(string s) {
        removeExtraSpaces(s); //去除多余空格，保证单词之间之只有一个空格，且字符串首尾没空格。
        Reverse(s, 0, s.size() - 1);
        int start = 0; //removeExtraSpaces后保证第一个单词的开始下标一定是0。
        for (int i = 0; i <= s.size(); ++i) {
            if (i == s.size() || s[i] == ' ') { //到达空格或者串尾，说明一个单词结束。进行翻转。
                Reverse(s, start, i - 1); //翻转，注意是左闭右闭 []的翻转。
                start = i + 1; //更新下一个单词的开始下标start
            }
        }
        return s;
    }
};