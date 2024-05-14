#ifndef MYGENERATORS_H
#define MYGENERATORS_H

/** \brief Устанавливает параметр А для линейно-конгруентного метода
 */
#define A 214013
/** \brief Устанавливает параметр С для линейно-конгруентного метода
 */
#define C 2531011


/**
 * @brief Класс генератора случайных чисел
 *
 * Класс основан на использовании Xor-шифта с модификациями
 *

 * Класс имеет приватное поле:
 * \tparam state - состояние генератора. Из этого числа расчитывается каждое следующее число
 */
class RandomGenerator {
private:
    unsigned int state;

    /** \brief Приватная функция генерации одного числа по state
     *
     * @return новое значение state
     */
    unsigned int xorshift() {
        state += C ^ state;
        state ^= (state << 13);
        state ^= (state >> 17);
        state ^= (state << 5);
        state *= 0x2545F4914F6CDD1D;
        return state;
    }

public:
    /** \brief Стандартный конструктор класса
     *
     * Инициализирует поле state, как seed, подаваемый при первоначальной инициализации пользователем
     */
    explicit RandomGenerator(unsigned int seed) : state(seed) {}

    /** \brief Открытая функция, позволяющая пользователю получить новое число из генератора
     *
     * @return число, полученное после выполнения приватной функции xorshift()
     */
    unsigned int generate() { return xorshift(); }
};


/** @brief Второй класс генератора случайных чисел
 *
 * Класс основан на конкатенации Xor-шифта и лиейно-конгурентного метода
 *
 * Класс имеет приватное поле:
 * \tparam state - состояние генератора. Из этого числа расчитывается каждое следующее число
 */
class LXRandomGenerator {
private:
    unsigned int state;

    /** \brief Приватная функция генерации одного числа по полю state
     *
     * @return новое значение state
     */
    unsigned int lcg() {
        state = A * state + C;
        return state;
    }

    /** \brief Приватная функция генерации одного числа по полю state
     *
     * @return новое значение state
     */
    unsigned int xorshift() {
        state ^= (state << 13);
        state ^= (state >> 17);
        state ^= (state << 5);
        return state;
    }

public:
    /** \brief Стандартный конструктор класса
     *
     * Инициализирует поле state, как seed, подаваемый при первоначальной инициализации пользователем
     */
    explicit LXRandomGenerator(const unsigned int seed) : state(seed) {}

    /** \brief Открытая функция, позволяющая пользователю получить новое число из генератора
     *
     * @return число, полученное после конкатенации результатов приватных функций xorshift() и lcg()
     */
    unsigned int generate() { return lcg() ^ xorshift(); }
};

#endif // MYGENERATORS_H
