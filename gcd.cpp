#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

int gcd(vector<int> nums) {
  int ret = nums[0];

  for (int i = 1; i < nums.size(); i++) {
    ret = gcd(ret, nums[i]);
  }

  return ret;
}

int main() {
  assert(gcd(2, 8) == 2);

  vector<int> nums;
  nums.push_back(2);
  nums.push_back(6);
  nums.push_back(12);

  assert(gcd(nums) == 2);

  return 0;
}

