# RedBlackTree
В данном проекте реализовано красно-черное дерево для решения задачи range queries.

![image](Images/rbt.jpeg)

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

cd build/src/

cmake --build .

./rbt
```

Для запуска unit тестов
```
cmake -B build

cd build/tests/unit

cmake --build .

./unit
```

Для запуска end to end тестов на дерево и std::set
```
cmake -B build

cd build/tests/ete

cmake --build .

./rbtreetest <test> (or) ./stdsettest <test>
```

Для генерации тестов нужен python3
```
cd tests/ete

python3 testgen.py
```

Для сравнения скорости работы моего дерева с std::set
```
cd build

cd compare

cmake --build .

./comp
```

Или для уже скомпилированного файла ./comp:
```
cd compare

chmod +x compare.sh

./compare.sh
```