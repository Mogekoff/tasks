#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <chrono>
using namespace std;

long long unsigned variants = 0;
int a, b;//размеры доски
int max_moves;
std::mutex locker;
void correctMove(const int& x, const int& y, short* route, short currentMove);

void testMove(const int& x, const int& y, short* route, short currentMove) {
    if (currentMove == max_moves)
        return;
    correctMove(x + 2, y + 1, route, currentMove);
    correctMove(x + 2, y - 1, route, currentMove);
    correctMove(x - 2, y + 1, route, currentMove);
    correctMove(x - 2, y - 1, route, currentMove);
    correctMove(x + 1, y + 2, route, currentMove);
    correctMove(x + 1, y - 2, route, currentMove);
    correctMove(x - 1, y + 2, route, currentMove);
    correctMove(x - 1, y - 2, route, currentMove);
    if (currentMove != max_moves)
        currentMove--;
    
    if (variants % 100000000 == 0) {
        locker.lock();
        std::cout << "Перебрано вариантов " << variants << ". Путь состоит из " << currentMove << "/" << a * b << " ходов. " << endl;
        locker.unlock();
    }
    
}

void correctMove(const int& x, const int& y, short* route, short currentMove) {
    variants++;   

    if (x <= a && x >= 1 && y <= b && y >= 1) { //клетка в пределах доски
        int t = x * 10 + y;                 //две координаты в одно число
        if (!(route[0]==t && currentMove==63))
            for (int i = 0; i < currentMove; i++)    //записываем число в массив
                if (route[i] == t)
                    return;

        route[currentMove] = t;
        currentMove++;

        if (currentMove == max_moves) {
            string output = "Решение задачи: ";
            
            for (int i = 0; i < max_moves; i++) {
                if (a <= 27) {
                    output += char(64 + route[i] / 10);
                    output += to_string(route[i] % 10);
                }
                else {
                    output += to_string(route[i] / 10);
                    output += to_string(route[i] % 10);
                }
                output += ' ';
            }
            locker.lock();
            std::cout << output << endl;
            locker.unlock();
            return;
        }

        testMove(x, y, route, currentMove);
    }
    return;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int _x, _y;

    std::cout << "Задача о ходе коня. \n\nВведите размеры доски AxB (прим. 8 8): ";
    cin >> a >> b;
    max_moves = a * b;
    std::cout << "Введите координаты начальной клетки в пределах шахматной доски цифрами через пробел (прим. 2 4): ";
    cin >> _x >> _y;

    short* route1 = new short[64]; route1[0] = _x * 10 + _y;
    short* route2 = new short[64]; route2[0] = _x * 10 + _y;
    short* route3 = new short[64]; route3[0] = _x * 10 + _y;
    short* route4 = new short[64]; route4[0] = _x * 10 + _y;
    short* route5 = new short[64]; route5[0] = _x * 10 + _y;
    short* route6 = new short[64]; route6[0] = _x * 10 + _y;
    short* route7 = new short[64]; route7[0] = _x * 10 + _y;
    short* route8 = new short[64]; route8[0] = _x * 10 + _y;

    std::thread thr1(correctMove, _x + 2, _y + 1, route1, 1);
    std::thread thr2(correctMove, _x + 2, _y - 1, route2, 1);
    std::thread thr3(correctMove, _x - 2, _y + 1, route3, 1);
    std::thread thr4(correctMove, _x - 2, _y - 1, route4, 1);
    std::thread thr5(correctMove, _x + 1, _y + 2, route5, 1);
    std::thread thr6(correctMove, _x + 1, _y - 2, route6, 1);
    std::thread thr7(correctMove, _x - 1, _y + 2, route7, 1);
    std::thread thr8(correctMove, _x - 1, _y - 2, route8, 1);

    auto lastVar = variants;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        long double minus = variants - lastVar;
        locker.lock();
        cout<<"Скорость перебора: "<<minus/5000000<<"M вариантов в секунду"<<endl;
        locker.unlock();
        lastVar = variants;
    }

    thr1.join();
    thr2.join();
    thr3.join();
    thr4.join();
    thr5.join();
    thr6.join();
    thr7.join();
    thr8.join();

    return 0;
}
