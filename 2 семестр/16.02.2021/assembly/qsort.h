// Начнем с директив препроцессора. ADD_H – это произвольное уникальное имя (обычно используется имя заголовочного файла)
#ifndef QSORT_H
#define QSORT_H
#include <vector>
 
// А это уже содержимое заголовочного файла
void quicksort(std::vector<int> &value, long long left, long long right); // прототип функции qsort()
 
// Заканчиваем директивой препроцессора
#endif