# Entrega 2

## List vs SynchList

La diferencia radica en que la clase SynchList permite la sincronización entre los múltiples hilos que utilicen la misma estructura de datos, mientras que la clase List no lo hace.
En particular, SynchList impone las siguientes restricciones:

- En cada momento, a lo sumo un hilo puede acceder a la estructura de datos.
- Los hilos que deseen remover un elemento de la lista esperarán hasta que la lista no este vacía para poder hacerlo.
