class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() < 2)
        {
            return nums.size();
        }

        int src = 0;
        int fast = 1;
        int slow = 0;

        while (fast < nums.size())
        {
            if (nums[fast] == nums[slow])
            {
                fast++;
                slow++;
            }
            else
            {
                src++;
                nums[src] = nums[fast];
                fast++;
                slow++;
            }
        }

        return src + 1;

    }
};