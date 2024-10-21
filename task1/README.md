## Запуск проекта
1) Клонируйте репозиторий
```
git clone https://github.com/isshlyapin/MIPT-Cpp-2ndCourse.git
```
3) Перейдите в директорию проекта
```
cd MIPT-Cpp-2ndCourse/task1
```
4) Для управления зависимостями используется conan
```
conan install . --output-folder=build --build=missing
```
5) Для сборки используется cmake
```
cmake --preset conan-release
```
```
cmake --build --preset conan-release
```