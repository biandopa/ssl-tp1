echo "a) y c)"
sed 's/\./.\n/g' breve_historia.txt | sed 's/^ //g' > breve_historia_2.txt
cat breve_historia_2.txt
## Borro los espacios de adelante sobrantes

echo ""
echo "b) y c)"
sed -i '/^$/d' breve_historia_2.txt && cat breve_historia_2.txt
## d marca eliminación

echo ""
echo "d)"
grep --color -i 'guerra' breve_historia.txt

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
echo "$(sed 's/\./.\n/g' breve_historia.txt | sed 's/^ //g' | egrep '18[0-9]{2}|1900')"

echo ""
echo "i)"
echo "$(sed 's/^[a-zA-Z]*\b//g' breve_historia.txt)" 

echo ""
echo "j)"
echo "Cantidad de archivos .txt en el directorio actual: $(ls | grep -c .txt)"
echo "Si desea ver la cantidad de otro directorio, ingreselo: "
read directorio
echo "Cantidad de archivos .txt en el directorio $directorio es: $(ls $directorio | grep -c .txt)"