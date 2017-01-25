#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#define HOP 3

using namespace std;

int maximizeRatings(vector<int> ratings) {
  int temp[4] = {0, };
  int num_minus = 0;
  int result = 0;
  int i, j; // i : position

  for (i = 0; i < ratings.size();) {
    if (ratings[i] >= 0) {
      result += ratings[i];
      i += 1;
    } else {
      if (i + 1 >= ratings.size - 1) {
        break;

      for (j = i; j < ratings.size(); j++) { // 연속된 음수의 갯수
        if (ratings[j] < 0) {
          num_minus += 1;
        } else {
          break;
        }
      }

      if (num_minus > 4) {
        sum = sum + ratings[i + 1] + ratings[i + 3];
        i += 5;
      } else {
        temp[0] = ratings[i] + ratings[i + 1];
        temp[1] = ratings[i] + ratings[i + 2];
        temp[2] = ratings[i + 1] + ratings[i + 2];
        temp[3] = ratings[i + 1];

        int max_index = 0;

        for (j = 1; j <= 3; j++) {
          if (temp[max_index] < temp[j]) 
            max_index = j;
        }

        result += temp[max_index];

        switch (max_index) {
          case 0: 
          case 3: {
            i += 2;
            break;
          }
          case 1:
          case 2: {
            i += 3;
            break;
          }
        }
        
      }  // else 종료 

    }
  }

  return result;

}
