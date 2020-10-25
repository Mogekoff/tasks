/*
Дано число N. Определите, сколькими способами можно расставить на доске N×N N ферзей, не бьющих друг друга.
Формат входных данных
Задано единственное число N. (N ≤ 10)
Формат выходных данных
Выведите ответ на задачу.
Sample Input:
8
Sample Output:
92
*/

#include <iostream>

unsigned Count = 0;
int** Positions;

void Move(const unsigned N, unsigned Queens = 0) {
    if (Queens == N) {
        Count++;
        return;
    }
    int i = 0;
    int j = 0;
    while (i < N) {
        while (j < N) {
            for (int k = 0; k <= Queens; k++) {
                if(k==Queens) {
                    Positions[k][0] = i;
                    Positions[k][1] = j++;
                    Move(N, Queens + 1);
                }
                else if (Positions[k][0] == i) {
                    i++; j = 0; break;
                }
                else if (Positions[k][1] == j || abs(Positions[k][0] - i) == abs(Positions[k][1] - j)) {
                    j++; break;
                }
            }
        }
        i++;
    }
}

int main() {
    unsigned N;
    std::cin >> N;
    
    Positions = new int* [N];
    for (int i = 0; i < N; i++)
        Positions[i] = new int[2];
    
    Move(N);
    std::cout << Count;
    return 0;
}
