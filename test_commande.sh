#!/bin/sh

echo "Test de la commande ./minicc -h" 
./minicc -h
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc -b" 
./minicc -b
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc main.c" 
./minicc main.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc main.c -o fichier.s" 
./minicc main.c -o fichier.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc -o fichier.s main.c" 
./minicc -o fichier.s main.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc -o fichier.s -t 0 main.c -r 6" 
./minicc -o fichier.s -t 0 main.c -r 6
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc -o fichier.s -v main.c" 
./minicc -o fichier.s -v main.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc -s testSujet.c" 
./minicc -s testSujet.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc -b main.c" 
./minicc -b main.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc main.c testSujet.c" 
./minicc main.c testSujet.c 
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc -h -t 10 main.c"
./minicc -h -t 10 main.c 
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc -s -v main.c" 
./minicc -s -v main.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc -t -r 4 main.c" 
./minicc -t -r 4 main.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc main.c -o fichier.s testSujet.c" 
./minicc main.c -o fichier.s testSujet.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc -r 2 main.c" 
./minicc -r 2 main.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc -t 6 main.c" 
./minicc -t 6 main.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc -t 0 -r 8 -o fichier.s" 
./minicc -t 0 -r 8 -o fichier.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test de la commande ./minicc fichier.c" 
./minicc fichier.c
echo "Sortie" $?
echo '------------------------------------------------'
