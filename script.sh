echo "a) y c)"
sed 's/\./.\n/g' breve_historia.txt | sed 's/^ //g' > breve_historia_2.txt
cat breve_historia_2.txt
## s marca sustitución
## g sirve para que siga ejecutándose y encuentre todos los puntos a pesar de haber encontrado el primero
## Además, borro los espacios de adelante sobrantes

echo ""
echo "b) y c)"
sed -i '/^$/d' breve_historia_2.txt && cat breve_historia_2.txt
## d marca eliminación

echo ""
echo "d)"
grep -i 'guerra' breve_historia.txt

echo ""
echo "e)"
egrep -o '^La\b.*(s.|s$)' breve_historia.txt

echo ""
echo "f)"
echo "La palabra peronismo aparece $(sed 's/\./.\n/g' breve_historia.txt | sed 's/^ //g' | grep -c 'peronismo') veces"

echo ""
echo "g)"
echo "La cantidad de veces de oraciones con las palabras Sarmiento y Rosas es: $(sed 's/\./.\n/g' breve_historia.txt | sed 's/^ //g' | grep -c 'Sarmiento.*Rosas\|Rosas.*Sarmiento')"
echo "La cantidad de veces de oraciones con las palabras Sarmiento y/o Rosas es: $(sed 's/\./.\n/g' breve_historia.txt | sed 's/^ //g' | grep -c 'Sarmiento.*Rosas\|Rosas.*Sarmiento\|Sarmiento\|Rosas')"


echo ""
echo "h)"