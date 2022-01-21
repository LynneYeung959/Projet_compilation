#!/bin/sh

echo "Test du fichier add.c" 
./minicc -v Tests/Verif/OK/add.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier affect.c" 
./minicc -v Tests/Verif/OK/affect.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier and.c" 
./minicc -v Tests/Verif/OK/and.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier band.c" 
./minicc -v Tests/Verif/OK/band.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier bnot.c" 
./minicc -v Tests/Verif/OK/bnot.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier bor.c" 
./minicc -v Tests/Verif/OK/bor.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier decl_glob_local.c" 
./minicc -v Tests/Verif/OK/decl_glob_local.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du div.c" 
./minicc -v Tests/Verif/OK/div.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier eq.c" 
./minicc -v Tests/Verif/OK/eq.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier GE.c" 
./minicc -v Tests/Verif/OK/GE.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier GT.c" 
./minicc -v Tests/Verif/OK/GT.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier LE.c" 
./minicc -v Tests/Verif/OK/LE.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier LT.c" 
./minicc -v Tests/Verif/OK/LT.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier minus.c" 
./minicc -v Tests/Verif/OK/minus.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier modulo.c" 
./minicc -v Tests/Verif/OK/modulo.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier mult.c" 
./minicc -v Tests/Verif/OK/mult.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier NE.c" 
./minicc -v Tests/Verif/OK/NE.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier not.c" 
./minicc -v Tests/Verif/OK/not.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier or.c" 
./minicc -v Tests/Verif/OK/or.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier sll.c"
./minicc -v Tests/Verif/OK/sll.c 
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier sra.c" 
./minicc -v Tests/Verif/OK/sra.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier srl.c" 
./minicc -v Tests/Verif/OK/srl.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier testSujet.c" 
./minicc -v Tests/Verif/OK/testSujet.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier vardupli.c" 
./minicc -v Tests/Verif/OK/vardupli.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier vardupli2.c" 
./minicc -v Tests/Verif/OK/vardupli2.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier xor.c" 
./minicc -v Tests/Verif/OK/xor.c
echo "Sortie" $?
echo '------------------------------------------------'