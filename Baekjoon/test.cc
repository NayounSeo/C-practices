/* 11004 */
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int N;
    scanf("%d", &N);
    long long arr[1000001] = {0, };

    for (int i = 0; i < N; i++) {
        scanf("%lld", arr + i);
    }

    sort(arr, arr + N);

    long long answer = 0;
    int max_count = 0;
    int temp_count = 0;
    for (int i = 0; i < N; i++) {
        temp_count += 1;
        if (arr[i] != arr[i + 1]) {
            if (max_count < temp_count) {
                answer = arr[i];
                max_count = temp_count;
            }
            temp_count = 0;
        }
    }

    printf("%lld\n", answer);

    return 0;
}

/*
5
1
2
1
2
1
*/
/*
6
1
2
1
2
1
2
*/
    /*
    내가 고민해야 하는 게 뭐지? 
    해당 수가 들어온 횟수는 카운트 하면서도 어떤 수인지 나중에도 알 수 있도록 하는 것?
    아니야ㅜㅠㅜ "정렬 한 이후에는 같은 수가 인접"이라고 했으니까 배열로 그대로 저장이 맞을거야!
    아래는 위 방식에 맞게 원래 썼던 코드..
    
    int i = 0;
    int temp = 0;
    while (1) {
        if (arr[i] == arr[i + 1]) {
            temp = i + 1
        }
        i += 1;
    }
    */