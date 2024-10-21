##Запуск проекта
1) ```git clone https://github.com/isshlyapin/MIPT-Cpp-2ndCourse.git```
2) ```cd MIPT-Cpp-2ndCourse/task1```
3) ```conan install . --output-folder=build --build=missing```
4) ```cmake --preset conan-release```
5) ```cmake --build --preset conan-release```