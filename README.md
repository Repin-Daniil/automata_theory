# Лабораторные работы по дисциплине «Теория автоматов и формальных языков»
- [Задачи](samples/)
- [Отчет](docs/report.pdf)

**Компиляция**
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target all        
```

**Установка опциональных зависимостей**
```bash
sudo apt install graphviz
```

**Генерация графа по dot-описанию**
```bash
 dot -Tpng nfa.dot -o nfa.png
```