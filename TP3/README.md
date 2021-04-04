# Compiling TP3 : Classes pour la gestion du temps

## a) Classe Chrono

arm-linux-g++ td3a.cpp Chrono.cpp ../TP1/timespec.cpp -o tp3a.out -Wall -Wextra -lrt -lpthread

## b) Classe Timer

arm-linux-g++ td3b.cpp Timer.cpp CountDown.cpp ../TP1/timespec.cpp -o tp3b.out -Wall -Wextra -lrt -lpthread

## c) Calibration en temps d’une boucle

arm-linux-g++ td3c.cpp Timer.cpp CpuLoop.cpp Calibrator.cpp Looper.cpp ../TP1/timespec.cpp Chrono.cpp -o tp3c.out -Wall -Wextra -lrt -lpthread