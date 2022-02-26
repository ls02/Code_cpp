#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void reveser(vector<int>& v)
    {
        int left = 0;
        int right = v.size() - 1;

        while (left < right)
        {
            int temp = v[left];
            v[left] = v[right];
            v[right] = temp;

            left++;
            right--;
        }
    }

    vector<int> addToArrayForm(vector<int>& num, int k) {
        int n = 0;
        int i = 0;
        vector<int> v1;
        int flags = 0;

        for (i = num.size() - 1; i >= 0; i--)
        {
            n = k % 10;
            k /= 10;
            num[i] = (num[i] + n + flags);
            flags = 0;

            if (num[i] > 9)
            {
                num[i] %= 10;
                flags = 1;
            }

            v1.push_back(num[i]);
        }

        while (k)
        {
            int sum = k % 10 + flags;
            flags = 0;
            k /= 10;

            if (sum > 9)
            {
                sum %= 10;
                flags = 1;
            }

            v1.push_back(sum);
        }

        if (flags)
        {
            v1.push_back(flags);
        }

        reveser(v1);

        return v1;
    }
};