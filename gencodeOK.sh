#!/bin/sh

echo "Test du fichier main.c" 
./minicc Tests/Gencode/OK/main.c -o Tests/Gencode/OK/MIPS/main.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier add.c" 
./minicc Tests/Gencode/OK/add.c -o Tests/Gencode/OK/MIPS/add.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier affect.c" 
./minicc Tests/Gencode/OK/affect.c -o Tests/Gencode/OK/MIPS/affect.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier and.c" 
./minicc Tests/Gencode/OK/and.c -o Tests/Gencode/OK/MIPS/and.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier band.c" 
./minicc Tests/Gencode/OK/band.c -o Tests/Gencode/OK/MIPS/band.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier bnot.c" 
./minicc Tests/Gencode/OK/bnot.c -o Tests/Gencode/OK/MIPS/bnot.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier bor.c" 
./minicc Tests/Gencode/OK/bor.c -o Tests/Gencode/OK/MIPS/bor.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier decl_glob_local.c" 
./minicc Tests/Gencode/OK/decl_glob_local.c -o Tests/Gencode/OK/MIPS/decl_glob_local.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du div.c" 
./minicc Tests/Gencode/OK/div.c -o Tests/Gencode/OK/MIPS/div.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier eq.c" 
./minicc Tests/Gencode/OK/eq.c -o Tests/Gencode/OK/MIPS/eq.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier GE.c" 
./minicc Tests/Gencode/OK/GE.c -o Tests/Gencode/OK/MIPS/GE.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier GT.c" 
./minicc Tests/Gencode/OK/GT.c -o Tests/Gencode/OK/MIPS/GT.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier LE.c" 
./minicc Tests/Gencode/OK/LE.c -o Tests/Gencode/OK/MIPS/LE.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier LT.c" 
./minicc Tests/Gencode/OK/LT.c -o Tests/Gencode/OK/MIPS/LT.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier minus.c" 
./minicc Tests/Gencode/OK/minus.c -o Tests/Gencode/OK/MIPS/minus.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier modulo.c" 
./minicc Tests/Gencode/OK/modulo.c -o Tests/Gencode/OK/MIPS/modulo.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier mult.c" 
./minicc Tests/Gencode/OK/mult.c -o Tests/Gencode/OK/MIPS/mult.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier NE.c" 
./minicc Tests/Gencode/OK/NE.c -o Tests/Gencode/OK/MIPS/NE.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier not.c" 
./minicc Tests/Gencode/OK/not.c -o Tests/Gencode/OK/MIPS/not.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier or.c" 
./minicc Tests/Gencode/OK/or.c -o Tests/Gencode/OK/MIPS/or.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier sll.c"
./minicc Tests/Gencode/OK/sll.c -o Tests/Gencode/OK/MIPS/sll.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier sra.c" 
./minicc Tests/Gencode/OK/sra.c -o Tests/Gencode/OK/MIPS/sra.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier srl.c" 
./minicc Tests/Gencode/OK/srl.c -o Tests/Gencode/OK/MIPS/srl.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier testSujet.c" 
./minicc Tests/Gencode/OK/testSujet.c -o Tests/Gencode/OK/MIPS/testSujet.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier vardupli.c" 
./minicc Tests/Gencode/OK/vardupli.c -o Tests/Gencode/OK/MIPS/vardupli.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier vardupli2.c" 
./minicc Tests/Gencode/OK/vardupli2.c -o Tests/Gencode/OK/MIPS/vardupli2.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier xor.c" 
./minicc Tests/Gencode/OK/xor.c -o Tests/Gencode/OK/MIPS/xor.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier sujetAvecParan.c" 
./minicc Tests/Gencode/OK/sujetAvecParan.c -o Tests/Gencode/OK/MIPS/sujetAvecParan.s
echo "Sortie" $?
echo '------------------------------------------------'

echo "Test du fichier sujetSansParan.c" 
./minicc Tests/Gencode/OK/sujetSansParan.c -o Tests/Gencode/OK/MIPS/sujetSansParan.s
echo "Sortie" $?
echo '------------------------------------------------'