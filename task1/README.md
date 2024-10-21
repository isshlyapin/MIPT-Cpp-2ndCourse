## Запуск проекта
1) 
```
git clone https://github.com/isshlyapin/MIPT-Cpp-2ndCourse.git
```
3) 
```
cd MIPT-Cpp-2ndCourse/task1
```
4) 
```
conan install . --output-folder=build --build=missing
```
5) 
```
cmake --preset conan-release
```
6) 
```
cmake --build --preset conan-release
```