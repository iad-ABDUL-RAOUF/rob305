# Compile the TP2 : Familiarisation avec l’API multitâches pthread

## a) Exécution sur plusieurs tâches sans mutex

arm-linux-g++  td2a.cpp ../TP1/timespec.cpp -o td2a.raspi -Wall -Wextra -lrt - lpthread

## b) Mesure de temps d’exécution

arm-linux-g++  td2b.cpp ../TP1/timespec.cpp -o td2b.raspi -Wall -Wextra -lrt - lpthread

## c) Exécution sur plusieurs tâches avec mutex

arm-linux-g++  td2c.cpp ../TP1/timespec.cpp -o td2c.raspi -Wall -Wextra -lrt - lpthread