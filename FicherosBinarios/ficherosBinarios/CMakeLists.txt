cmake_minimum_required(VERSION 3.20)
project(FicherosBinarios C)

set(CMAKE_C_STANDARD 99)

# Target para ficherosBinarios
add_executable(ficherosBinarios ficherosBinarios/main.c)

# Target para ejemplo1Clase
add_executable(ejemplo1Clase ejemplo1Clase/main.c)

# Target para ejemplo2Clase
add_executable(ejemplo2Clase ejemplo2Clase/main.c)

# Target para ejercicio1
add_executable(ejercicio1 ejercicio1/main.c)

# Target para ejercicio2
add_executable(ejercicio2 ejercicio2/main.c)
