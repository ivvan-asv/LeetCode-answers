#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    long long findKthSmallest(std::vector<int>& coins, int k) {
        int n = coins.size();

        auto count = [&](long long M) -> long long {
            long long total = 0;
            int total_subsets = 1 << n; 

            for (int mask = 1; mask < total_subsets; ++mask) {
                int bits_set = 0;
                long long current_lcm = 1; 
                bool overflow = false;

                for (int i = 0; i < n; ++i) {
                    if ((mask >> i) & 1) {
                        bits_set++;
                        current_lcm = std::lcm(current_lcm, (long long)coins[i]);
                        
                        
                        if (current_lcm > M) {
                            overflow = true;
                            break;
                        }
                    }
                }

                if (!overflow) {
                    
                    if (bits_set % 2 == 1) {
                        total += M / current_lcm;
                    } else {
                        total -= M / current_lcm;
                    }
                }
            }
            return total;
        };

        
        long long min_coin = *std::min_element(coins.begin(), coins.end());
        long long low = 1;
        long long high = min_coin * k; 
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (count(mid) >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1
            }
        }

        return ans;
    }
};