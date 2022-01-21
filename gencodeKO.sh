#!/bin/sh

echo "Test du fichier div0.c" 
./minicc -v Tests/Gencode/KO/div0.c
echo "Sortie" $?
echo '------------------------------------------------'


echo "Test du fichier modulo0.c" 
./minicc -v Tests/Gencode/KO/modulo0.c
echo "Sortie" $?
echo '------------------------------------------------'