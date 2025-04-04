# Entrega 2

## Argumentos que admite Nachos

La información referida a los argumentos de línea de comandos que admite Nachos pueden encontrarse en el archivo `threads/main.cc`. A continuación se muestra el modo de uso de los mismos:

```bash
nachos [-d <debugflags>] [-do <debugopts>] 
       [-rs <random seed #>] [-z] [-tt|-tN] 
       [-m <num phys pages>] [-i]
       [-s] [-x <nachos file>] [-tc <consoleIn> <consoleOut>] 
       [-f] [-cp <unix file> <nachos file>] [-pr <nachos file>]
       [-rm <nachos file>] [-ls] [-D] [-c] [-tf]
```

Estas opciones se pueden clasificar en distintos tipos:

- Generales (por ejemplo, para mostrar información del sistema o ciertos mensajes de debugging)

- Testeo de hilos

- Programa de usuario

- Sistema de archivos (tal como remover un archivo nachos del sistema de archivos o verificar la integridad del mismo)

Una bandera interesante a mencionar es '-rs'. Esta provoca que los yields (es decir, las renuncias de CPU que realizan los hilos) se produzcan en momentos aleatorios. De esta manera, se permite jugar un poco con el comportamiento concurrente de nuestro sistema.  

## List vs SynchList

La diferencia radica en que la clase SynchList permite la sincronización entre los múltiples hilos que utilicen la misma estructura de datos, mientras que la clase List no lo hace.
En particular, SynchList impone las siguientes restricciones:

- En cada momento, a lo sumo un hilo puede acceder a la estructura de datos.
- Los hilos que deseen remover un elemento de la lista esperarán hasta que la lista no este vacía para poder hacerlo.
