#!/bin/sh

echo "Test du fichier addTypeDiff.c" 
./minicc -v Tests/Verif/KO/addTypeDiff.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier and.c" 
./minicc -v Tests/Verif/KO/and.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier band.c" 
./minicc -v Tests/Verif/KO/band.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier bnot.c" 
./minicc -v Tests/Verif/KO/bnot.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier bor.c" 
./minicc -v Tests/Verif/KO/bor.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier break.c" 
./minicc -v Tests/Verif/KO/break.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier continue.c" 
./minicc -v Tests/Verif/KO/continue.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du divTypeDiff.c" 
./minicc -v Tests/Verif/KO/divTypeDiff.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du divBool.c" 
./minicc -v Tests/Verif/KO/divTypeDiff.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier eq2.c" 
./minicc -v Tests/Verif/KO/eq2.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier EQ.c" 
./minicc -v Tests/Verif/KO/EQ.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier GE.c" 
./minicc -v Tests/Verif/KO/GE.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier global1.c" 
./minicc -v Tests/Verif/KO/global1.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier GT.c" 
./minicc -v Tests/Verif/KO/GT.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier LE.c" 
./minicc -v Tests/Verif/KO/LE.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier LT.c" 
./minicc -v Tests/Verif/KO/LT.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier modTypeDiff.c" 
./minicc -v Tests/Verif/KO/modTypeDiff.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier moinsTypeDiff.c" 
./minicc -v Tests/Verif/KO/moinsTypeDiff.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier mulTypeDiff.c" 
./minicc -v Tests/Verif/KO/mulTypeDiff.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier NE.c" 
./minicc -v Tests/Verif/KO/NE.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier not.c" 
./minicc -v Tests/Verif/KO/not.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier or.c" 
./minicc -v Tests/Verif/KO/or.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier sll.c"
./minicc -v Tests/Verif/KO/sll.c 
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier sra.c" 
./minicc -v Tests/Verif/KO/sra.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier srl.c" 
./minicc -v Tests/Verif/KO/srl.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier utilnondecl.c" 
./minicc -v Tests/Verif/KO/utilnondecl.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier varfauxdecl.c" 
./minicc -v Tests/Verif/KO/varfauxdecl.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier varLocaleDupli.c" 
./minicc -v Tests/Verif/KO/varLocaleDupli.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier varLocaleDupli2.c" 
./minicc -v Tests/Verif/KO/varLocaleDupli2.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier varnondecl.c" 
./minicc -v Tests/Verif/KO/varnondecl.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier xor.c" 
./minicc -v Tests/Verif/KO/xor.c
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier div0.c" 
./minicc -v Tests/Verif/KO/div0.c
echo "Sortie" $?
echo '------------------------------------------------'


echo "Test du fichier modulo0.c" 
./minicc -v Tests/Verif/KO/modulo0.c
echo "Sortie" $?
echo '------------------------------------------------'