#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int N;
    double t_end, L, lamda, ro, c, T0, Tl, Tr;

    // Ввод параметров
    cout << "Введите количество пространственных узлов, N: ";
    cin >> N;
    cout << "Введите окончание по времени, t_end: ";
    cin >> t_end;
    cout << "Введите толщину пластины, L: ";
    cin >> L;
    cout << "Введите коэффициент теплопроводности материала пластины, lamda: ";
    cin >> lamda;
    cout << "Введите плотность материала пластины, ro: ";
    cin >> ro;
    cout << "Введите теплоемкость материала пластины, c: ";
    cin >> c;
    cout << "Введите начальную температуру, T0: ";
    cin >> T0;
    cout << "Введите температуру на границе x=0, Tl: ";
    cin >> Tl;
    cout << "Введите температуру на границе x=L, Tr: ";
    cin >> Tr;


    // Расчет шагов
    double h = L / (N - 1);
    double tau = t_end / 100.0;

    // Вектор температуры
    vector<double> T(N);
    for (int i = 0; i < N; ++i) {
        T[i] = T0;
    }

    // Прогоночные коэффициенты
    vector<double> alfa(N), beta(N);

    // Интегрирование
    double time = 0;
    while (time < t_end) {
        time += tau;

        alfa[0] = 0.0;
        beta[0] = Tl;

        for (int i = 1; i < N - 1; ++i) {
            double ai = lamda / (h * h);
            double bi = 2.0 * lamda / (h * h) + ro * c / tau;
            double ci = lamda / (h * h);
            double fi = -ro * c * T[i] / tau;

            alfa[i] = ai / (bi - ci * alfa[i - 1]);
            beta[i] = (ci * beta[i - 1] - fi) / (bi - ci * alfa[i - 1]);
        }

        T[N - 1] = Tr;

        for (int i = N - 2; i >= 0; --i) {
            T[i] = alfa[i] * T[i + 1] + beta[i];
        }
    }

    // Вывод результатов в файл
    ofstream f("res.txt");
    f << "Толщина пластины L = " << L << endl;
    f << "Число узлов по координате N = " << N << endl;
    f << "Коэффициент теплопроводности материала пластины lamda = " << lamda << endl;
    f << "Плотность материала пластины ro = " << ro << endl;
    f << "Теплоемкость материала пластины c = " << c << endl;
    f << "Начальная температура T0 = " << T0 << endl;
    f << "Температура на границе x = 0, Tl = " << Tl << endl;
    f << "Температура на границе x = L, Tr = " << Tr << endl;
    f << "Результат получен с шагом по координате h = " << h << endl;
    f << "Результат получен с шагом по времени tau = " << tau << endl;
    f << "Температурное поле в момент времени t = " << t_end << endl;
    f.close();

    ofstream g("tempr.txt");
    for (int i = 0; i < N; ++i) {
        g << " " << h * i << " " << T[i] << endl;
    }
    g.close();

    cout << "Результаты сохранены в файлы res.txt и tempr.txt" << endl;

    return 0;
}