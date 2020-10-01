# Archivos de Unai Lería
Para más información sobre los archivos en esta carpeta busque el archivo en [Archivos](#archivos).

# Archivos
- [Creador de librerias de lectura](leer%datos_creador%de%libreria/)
  - [input_reader_creator.py](#creador-de-librerias-de-lectura-de-datos)
- [Schrödinger: Pozo](#schrödinger-pozo-de-elías-mejorado)
- [Ejercicio 12 Schrödinger](#ejercicio-12-schrödinger)
- [foo](#qué-puñetas-es-foo-y-por-qué-está-en-todas-partes)



<!-- pagebreak -->

## Creador de librerias de lectura de datos
> Este script de Python solo soporta (actualmente) lectura de tipos int, double y char
> 
Pasos para crear una librería:
1) Ejecutar el código:
   ```bash
   $python input_reader_creator.py
   ```
2) Seguir los pasos:
   1) Escribir nombre de la nueva libreria.
   2) Escribir nombre del nuevo Struct con los datos que se leeran.
   3) Escribir cada una de las variables en el siguiente formato:
        ``` 
        tipo nombre_variable descripcion
        ```
        La descripción no es necesario. Pero se aconseja.

    4) Escribir el nombre de la función que se llamará desde otros códigos.

Para utilizar la librería creada deberá introducir en su código lo siguiente:
```c
#include "nombre_libreria_header.c"
nombre_struct foo;
nombre_funcion(&foo);
``` 
Así tendrás en la variable ```foo``` de tipo ```nombre_struct``` los valores leídos del fichero ```nombre_libreria_config.txt```.

<!-- pagebreak -->
## Schrödinger: Pozo de Elías mejorado
>Este código tiene de base el dado por Elías. Pero con las siguientes modificaciones:
>* Eliminar variables globales
>* Limpiar y reducir fichero principal
>* Renombrar variables a nombres significativos
>* Separar código en funciones coherentes
>* Reducir el código repetido:
>     * Añadir función ```super_print()```: (`printf()` + `fprintf()`)
>     * Añadir macros

En el estado actual hace exactamente lo mismo que el código de Elías.

### Modificar condiciones:
Puedes modificar las condiciones y variables del programa en el fichero: `input_reader_pozo_config.txt`
Es extríctamente necesario escribir todos, y del mismo tipo que se especifica.
### Para compilar y ejecutar con VSCode:
Es necesario abrir explícitamente la carpeta donde se encuentra el archivo `input_reader_pozo_config.txt`. De lo contrario no leerá los datos y finalizará la ejecución.
### Linux:
En ~/librerias/funciones.c `plot()`
Cambiar:
`system("Plot_Schr_pozo.plt");`
por
`system("gnuplot -p Plot_Schr_pozo.plt");`

<!-- pagebreak -->



## Ejercicio 12 Schrödinger
No está bien. Pero avanza en la dirección correcta. Aconsejo modificar al gusto
<!-- pagebreak -->
# Qué puñetas es foo y por qué está en todas partes?
> https://www.webopedia.com/TERM/F/foobar.html
De nada
    
