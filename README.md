# RedBlackTree
В данном проекте реализовано красно-черное.

![image](Images/rbt.jpeg)

# Уровень 1

## Условие задачи
Пусть на вход поступают ключи (каждый ключ это целое число, все ключи разные) и запросы (каждый запрос это пара из двух цулых чисел, второе больше первого). Нужно для каждого запроса подсчитать в дереве количество ключей, таких, что все они лежат строго между его левой и правой границами включительно.

## Установка и запуск проетка
Перед установкой проекта убедитесь, что у вас установлена библиотека [graphviz](https://graphviz.org).

Для установки
```
git clone git@github.com:Pelmeshka127/RedBlackTree.git

cd RedBlackTree
```

Для запуска дерева
```
cmake -B build

cd build/level1/src/

cmake --build .

./rbt1
```

Для запуска unit тестов
```
cmake -B build

cd build/level1/tests/unit

cmake --build .

./unit1
```

Для запуска end to end тестов на дерево и std::set
```
cmake -B build

cd build/level1/tests/ete

cmake --build .

./rbtreetest1 <test> (or) ./stdsettest1 <test>
```

Для генерации тестов нужен python3
```
cd level1/tests/ete

python3 testgen.py
```

Для сравнения скорости работы моего дерева с std::set
```
cd build

cd level1/compare

cmake --build .

./comp
```

Или для уже скомпилированного файла ./comp:
```
cd level1/compare

chmod +x compare.sh

./compare.sh
```

# Уровень 2

## Условие задачи
Со стандартного ввода приходят ключи (каждый ключ это целое число, все ключи разные) и запросы двух видов.
Запрос (m) на поиск k-го наименьшего элемента. Если запрашивается нулевой (минус первый и т.д.) наименьший выдавайте ошибку и возвращайте ненулевой код возврата. Если запрашивается наименьший элемент с номером больше чем вообще количество элементов в дереве, выдавайте просто последний наименьший (то есть наибольший). Запрос (n) на поиск количества элементов, меньших, чем заданный. Ключи могут быть как угодно перемешаны с запросами. Чтобы успешно пройти тесты, вы должны продумать такую балансировку дерева, чтобы оба вида запросов работали с логарифимической сложностью.

## Установка и запуск проетка

Для установки
```
git clone git@github.com:Pelmeshka127/RedBlackTree.git

cd RedBlackTree
```

Для запуска дерева
```
cmake -B build

cd build/level2/src/

cmake --build .

./rbt2
```

Для запуска unit тестов
```
cmake -B build

cd build/level2/tests/unit

cmake --build .

./unit2
```

Для запуска end to end тестов
```
cmake -B build

cd build/level2/tests/ete

cmake --build .

./ete2 <test> 
```

Для генерации тестов нужен python3
```
cd level2/tests/ete

python3 testgen.py
```