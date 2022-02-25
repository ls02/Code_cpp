#include <vector>
#include <iostream>

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        int i = 0;
        int j = 0;

        while (i < nums.size())
        {
            if (nums[i] == val)
            {
                i++;
            }
            else
            {
                nums[j++] = nums[i++];
            }
        }

        return j;
    }
};