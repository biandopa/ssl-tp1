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
egrep -o '^La.*(s.|s$)' breve_historia.txt
