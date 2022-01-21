#!/bin/sh

echo "Test du fichier main.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/main.s
echo '------------------------------------------------'

echo "Test du fichier add.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/add.s
echo '------------------------------------------------'

echo "Test du fichier affect.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/affect.s
echo '------------------------------------------------'

echo "Test du fichier and.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/and.s
echo '------------------------------------------------'

echo "Test du fichier band.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/band.s
echo '------------------------------------------------'

echo "Test du fichier bnot.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/bnot.s
echo '------------------------------------------------'

echo "Test du fichier bor.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/bor.s
echo '------------------------------------------------'

echo "Test du div.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/div.s
echo '------------------------------------------------'

echo "Test du fichier eq.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/eq.s
echo '------------------------------------------------'

echo "Test du fichier GE.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/GE.s
echo '------------------------------------------------'

echo "Test du fichier GT.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/GT.s
echo '------------------------------------------------'

echo "Test du fichier LE.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/LE.s
echo '------------------------------------------------'

echo "Test du fichier LT.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/LT.s
echo '------------------------------------------------'

echo "Test du fichier minus.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/minus.s
echo '------------------------------------------------'

echo "Test du fichier modulo.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/modulo.s
echo '------------------------------------------------'

echo "Test du fichier mult.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/mult.s
echo '------------------------------------------------'

echo "Test du fichier NE.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/NE.s
echo '------------------------------------------------'

echo "Test du fichier not.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/not.s
echo '------------------------------------------------'

echo "Test du fichier or.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/or.s
echo '------------------------------------------------'

echo "Test du fichier sll.c"
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/sll.s
echo '------------------------------------------------'

echo "Test du fichier sra.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/sra.s
echo '------------------------------------------------'

echo "Test du fichier srl.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/srl.s
echo '------------------------------------------------'

echo "Test du fichier testSujet.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/testSujet.s
echo '------------------------------------------------'

echo "Test du fichier vardupli.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/vardupli.s
echo '------------------------------------------------'

echo "Test du fichier vardupli2.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/vardupli2.s
echo '------------------------------------------------'

echo "Test du fichier xor.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/xor.s
echo '------------------------------------------------'

echo "Test du fichier sujetAvecParan.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/sujetAvecParan.s
echo '------------------------------------------------'

echo "Test du fichier sujetSansParan.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/sujetSansParan.s
echo '------------------------------------------------'

echo "Test du fichier decl_glob_local.c" 
java -jar utils/Mars_4_2.jar Tests/Gencode/OK/MIPS/decl_glob_local.s
echo '------------------------------------------------'