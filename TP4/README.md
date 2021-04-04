# Compiling TP4 Classes de base pour la programmation multitâches

## a) Classe Thread

arm-linux-g++ td4a.cpp ../TP1/timespec.cpp PosixThread.cpp ../TP3/Chrono.cpp -o td4a.out -Wall -Wextra -lrt -lpthread

## b) Classes Mutex et Mutex::Lock

arm-linux-g++ td4b.cpp ../TP1/timespec.cpp PosixThread.cpp Mutex.cpp ../TP3/Chrono.cpp -o td4b.out -Wall -Wextra -lrt -lpthread

## c) Classe Semaphore

arm-linux-g++ td4c.cpp ../TP1/timespec.cpp PosixThread.cpp Mutex.cpp ../TP3/Chrono.cpp Semaphore.cpp -o td4c.out -Wall -Wextra -lrt -lpthread

## d) Classe Fifo multitâches
