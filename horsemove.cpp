#include <iostream>
#include <thread>
using namespace std;

short route[64];
short currentMove = 0;
long long int variants = 0;
int a, b;//размеры доски
int max_moves;
bool correctMove(const int& x, const int& y);

void testMove(const int& x, const int& y) {
    if(currentMove==max_moves)
        return;
    correctMove(x + 2, y + 1);
    correctMove(x + 2, y - 1);
    correctMove(x - 2, y + 1);
    correctMove(x - 2, y - 1);
    correctMove(x + 1, y + 2);
    correctMove(x + 1, y - 2);
    correctMove(x - 1, y + 2);
    correctMove(x - 1, y - 2);
    if(currentMove!=max_moves)
        currentMove--;
    cout<<"Перебрано вариантов "<<variants<<" . Путь состоит из "<<currentMove<<"/"<<a*b<<" ходов. "<<endl;
}

bool correctMove(const int& x, const int& y) {
    variants++;
    if (currentMove == max_moves)
        return false;
    if (x<=a && x>=1 && y<=b && y>=1) { //клетка в пределах доски
        int t = x*10+y;                 //две координаты в одно число
        
        for (int i = 0; i < currentMove; i++)    //записываем число в массив
            if(route[i] == t)
                return false;
        
        route[currentMove]=t;
        currentMove++;

        testMove(x,y);
        return true;
    }
    return false;
}

int main()
{
    setlocale(LC_ALL,"Russian");
    
    int _x, _y;

    cout<<"Задача о ходе коня. \n\nВведите размеры доски AxB (прим. 8 8): ";   
    cin >> a >> b;
    max_moves = a*b;
    cout<<"Введите координаты начальной клетки в пределах шахматной доски цифрами через пробел (прим. 2 4): ";
    cin >> _x >> _y;

    if(!correctMove(_x,_y)) {
        cout<<"Такой клетки нет на шахматном поле "<<a<<" на "<<b<<endl;
        return -1;
    }
    if(currentMove!=max_moves) {
        cout<<"Решения нет."<<endl;
        return -2;
    }

    cout<<"Решение задачи: "<<endl;   
    
        for (int i = 0; i < max_moves; i++) {
            if (a <= 27)    
                cout << char(64 + route[i] / 10) << route[i] % 10 << ' ';
            else
                cout << route[i] / 10 << route[i] % 10 << ' ';
        }

    return 0;
}
