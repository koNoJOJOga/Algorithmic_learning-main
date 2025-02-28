#include <iostream>
#include <vector>
using namespace std;

// 计算前缀表（Partial Match Table）
vector<int> computeLPSArray(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0); // 初始化 lps 数组

    int len = 0; // 当前已匹配的前缀长度
    int i = 1;   // 从第二个字符开始计算

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;               // 匹配成功，延长前缀长度
            lps[i] = len;        // 更新 lps 数组
            i++;                 // 移动到下一个字符
        } else {
            if (len != 0) {
                len = lps[len - 1]; // 回退到之前匹配的位置
                // 优化点：如果回退后仍然不匹配，则继续回退，直到找到匹配或回到起点
                while (len > 0 && pattern[i] != pattern[len]) {
                    len = lps[len - 1];
                }
                if (pattern[i] == pattern[len]) {
                    len++;
                }
                lps[i] = len;
                i++;
            } else {
                lps[i] = 0;       // 没有匹配，lps[i] 为 0
                i++;              // 移动到下一个字符
            }
        }
    }

    return lps;
}

// KMP 匹配算法
vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> result; // 存储匹配位置
    int n = text.size();
    int m = pattern.size();

    if (m == 0) return result; // 如果模式串为空，返回空结果

    vector<int> lps = computeLPSArray(pattern); // 计算前缀表

    int i = 0; // 主串指针
    int j = 0; // 模式串指针

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++; // 主串指针前进
            j++; // 模式串指针前进
        }

        if (j == m) {
            result.push_back(i - j); // 找到匹配位置
            j = lps[j - 1];          // 继续查找下一个匹配
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1]; // 根据前缀表回退模式串指针
            } else {
                i++; // 主串指针前进
            }
        }
    }

    return result;
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    vector<int> result = kmpSearch(text, pattern);

    if (result.empty()) {
        cout << "Pattern not found." << endl;
    } else {
        cout << "Pattern found at index(es): ";
        for (int pos : result) {
            cout << pos << " ";
        }
        cout << endl;
    }

    return 0;
}