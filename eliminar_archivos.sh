directorio_actual="$PWD"
directorio_usr="$directorio_actual/user"

find "$directorio_actual" -maxdepth 1 -type f -name "*.txt" -delete

find "$directorio_usr/data/esquemas" "$directorio_usr/data/relaciones" -type f -name "*.txt" -delete

rm -rf "$directorio_usr/data/esquemas" "$directorio_usr/data/relaciones"

rm -rf "$directorio_usr/data"

rm -rf "$directorio_usr"

echo "Archivos .txt eliminados en el directorio actual y en $directorio_usr, y la carpeta user y todos sus contenidos han sido eliminados."