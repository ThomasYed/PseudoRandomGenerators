#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include "mygenerators.h"

/** \brief Устанавливает количество выборок, которые мы будем генерировать
 */
#define SIZE 20


/** \brief Перегрузка оператора << для последовательного вывода вектора
 *
 * @param os - адрес буфера, в которой необходимо записывать данные
 * @param vector - вектор, который необходимо вывести
 *
 * \return адрес буфера
 */
template<typename S>
std::ostream &operator<<(std::ostream &os, const std::vector<S> &vector) {
    for (auto element: vector)
        os << element << " ";
    return os;
}

/**
 * \brief Основная функция в программе
 * \return ноль, если программа завершилась успешно
 */
int main() {
    /**В начале программы создаётся массив sample_sizez, в котором описаны все размеры, которые будут генерироваться.
     * \code
     * int sample_sizes[SIZE];
     * \endcode
     */
    int sample_sizes[SIZE] = {100,  600,  1100, 1600, 2200, 2700, 3300, 3700, 4200, 4700,
                              5300, 5800, 6300, 6900, 7400, 7900, 8400, 8990, 9600, 10000};


    /**Проходим два цикла (так как два метода генерации) по всем размерам и генерируем данные по заданным размерам
     * Создание объекта первого генератора
     * \code
     * LXRandomGenerator generator(n)
     * \endcode
     *
     * Создание объекта второго генератора
     * \code
     * RandomGenerator generator(n)
     * \endcode
     */
    std::ofstream gen1_s;
    gen1_s.open("gen1.txt");
    for (int sample_size: sample_sizes) {
        LXRandomGenerator generator(sample_size);
        std::vector<unsigned> temp;
        temp.reserve(sample_size);

        for (int j = 0; j < sample_size; j++)
            temp.emplace_back(generator.generate());
        gen1_s << temp << std::endl;
    }
    gen1_s.close();

    std::ofstream gen2_s;
    gen2_s.open("gen2.txt");
    for (int sample_size: sample_sizes) {
        RandomGenerator generator(sample_size);
        std::vector<unsigned> temp;
        temp.reserve(sample_size);

        for (int j = 0; j < sample_size; j++)
            temp.emplace_back(generator.generate());
        gen2_s << temp << std::endl;
    }
    gen2_s.close();


    /**Проходим цикл по всем размерам от 1e3 до 1e7 и замеряем время генерации каждого типа (два собственной реализации
     * и один встроенный) Создание объекта первого генератора \code LXRandomGenerator generator(n) \endcode
     *
     * Создание объекта второго генератора
     * \code
     * RandomGenerator generator(n)
     * \endcode
     *
     * Использование третьего (встроенного) генератора
     * \code
     * std::rand()
     * \endcode
     */
    std::ofstream t_gen1, t_gen2, t_ingen;
    unsigned int time_samples[10] = {10000, 30000, 50000, 100000, 300000, 500000, 1000000, 3000000, 5000000, 10000000};

    t_gen1.open("gen1_time.txt");
    t_gen2.open("gen2_time.txt");
    t_ingen.open("genin_time.txt");
    LXRandomGenerator gen1(123456);
    RandomGenerator gen2(123456);

    for (unsigned int size: time_samples) {
        clock_t start = clock();
        for (int i = 0; i < size; i++)
            gen1.generate();
        clock_t end = clock();
        double seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        t_gen1 << seconds << " ";

        start = clock();
        for (int i = 0; i < size; i++)
            gen2.generate();
        end = clock();
        seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        t_gen2 << seconds << " ";

        start = clock();
        for (int i = 0; i < size; i++)
            std::rand();
        end = clock();
        seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        t_ingen << seconds << " ";
    }
    t_gen1.close();
    t_gen2.close();
    t_ingen.close();

    return 0;
}
