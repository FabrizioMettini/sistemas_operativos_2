# Entrega 1

- [Entrega 1](#entrega-1)
  - [Descargar Código Fuente de Nachos](#descargar-código-fuente-de-nachos)
  - [1. Emulación de la CPU](#1-emulación-de-la-cpu)
  - [2. Configuración de Memoria](#2-configuración-de-memoria)
  - [3. Aumentar la Memoria](#3-aumentar-la-memoria)
  - [4. Configuración del Disco](#4-configuración-del-disco)
  - [5. Simulación de Operaciones MIPS](#5-simulación-de-operaciones-mips)
  - [6. Búsqueda de la Función main](#6-búsqueda-de-la-función-main)
  - [7. Secuencia de Ejecución en main](#7-secuencia-de-ejecución-en-main)
  - [8. Funcionalidad de DEBUG y ASSERT](#8-funcionalidad-de-debug-y-assert)
  - [9. Banderas de Depuración](#9-banderas-de-depuración)
  - [10. Constantes en los Makefiles](#10-constantes-en-los-makefiles)

## Descargar Código Fuente de Nachos

Para descargar el código fuente, ejecuta lo siguiente:

```bash
svn co https://svn.dcc.fceia.unr.edu.ar/svn/lcc/R-412/Public/nachos/2025/nachos-unr25a/code/
```

## 1. Emulación de la CPU

Se prefiere emular una CPU en vez de utilizar directamente la CPU existente por las siguientes razones:

- **Entorno seguro:**  
  Permite aislar el entorno de ejecución del sistema operativo (SO) en desarrollo o estudio. Así, errores en el código del SO no afectan al sistema anfitrión, evitando posibles fallos graves o pérdida de datos.

- **Entorno controlado:**  
  Un emulador brinda herramientas de depuración y control que no están disponibles en hardware real. Por ejemplo, es posible pausar la ejecución, inspeccionar el estado de la CPU y la memoria, o ejecutar instrucciones paso a paso.

- **Entorno flexible:**  
  Los emuladores pueden configurarse para simular diferentes tipos de hardware, lo que facilita experimentar con distintas configuraciones y observar cómo afectan al rendimiento y comportamiento del SO.

## 2. Configuración de Memoria

En el archivo `machine/mmu` se define:

```text
MEMORY_SIZE = NUM_PHYS_PAGES *PAGE_SIZE
            = 32* 128 = 4096 bytes = 4KB
```

## 3. Aumentar la Memoria

Para aumentar la cantidad de memoria, basta con modificar el tamaño de la memoria por página, es decir, aumentar la variable `PAGE_SIZE` en el archivo ubicado en `machine/mmu`.

## 4. Configuración del Disco

Extraído de los archivos `machine/disk.hh` y `machine/disk.cc`:

```C
const unsigned SECTOR_SIZE = 128;         ///< Número de bytes por sector de disco.
const unsigned SECTORS_PER_TRACK = 32;    ///< Número de sectores por pista.
const unsigned NUM_TRACKS = 32;           ///< Número de pistas por disco.
const unsigned NUM_SECTORS = SECTORS_PER_TRACK * NUM_TRACKS;
```

Por lo tanto, se calcula el tamaño del disco como:

```text
DISK_SIZE = MAGIC_SIZE + NUM_SECTORS *SECTOR_SIZE
          = sizeof(int) + 32* 32 * 128 bytes ≈ 128KB
```

## 5. Simulación de Operaciones MIPS

Según lo extraído de `machine/mips_sim.cc`:

- La máquina Nachos simula **59 operaciones MIPS**, aunque teóricamente simula **60 instrucciones MIPS**.  
- Las instrucciones se pueden ver en `machine/instruction.cc` y `machine/encoding.hh`.

## 6. Búsqueda de la Función main

Para localizar archivos que contienen la función `main()`, se puede usar el siguiente comando:

```bash
grep -rl "main("
```

La salida típica es:

```bash
threads/main.cc
userland/matmult.c
userland/halt.c
userland/shell.c
userland/touch.c
userland/sort.c
userland/tinyshell.c
userland/filetest.c
userland/echo.c
bin/coff2flat.c
bin/disasm.c
bin/out.c
bin/readnoff.c
bin/coff2noff.c
bin/fuse/nachosfuse.c
bin/main.c
```

Si no existe el ejecutable, primero debes compilar:

```bash
cd userprog
make depend
make
```

Luego, para debugear `userprog/nachos`:

```bash
gdb ./userprog/nachos  
```

Dentro de GDB, establece un breakpoint en `main`:

```bash
>>> b main
file ../threads/main.cc, line 112.
```

## 7. Secuencia de Ejecución en main

La secuencia de funciones y llamadas es la siguiente:

```text
main > Initialize > ASSERT
main > DEBUG > Print
main > SysInfo
main > PrintVersion > printf
main > currentThread>Finish > interrupt->SetLevel
```

## 8. Funcionalidad de DEBUG y ASSERT

- **DEBUG:**  
  Imprime la ubicación de la línea donde se invoca la función `DEBUG` y notifica si alguna variable dentro de esta función no se utiliza.

- **ASSERT:**  
  Recibe una condición booleana.  
  - Si la condición es verdadera, no ocurre nada.  
  - Si es falsa, se notifica que el assert falló, mostrando por consola la expresión evaluada, la ubicación en el archivo y la línea correspondiente.

## 9. Banderas de Depuración

Las banderas y sus respectivas funcionalidades son:

- `+` : Activa todos los mensajes de depuración.
- `t` : Sistema de hilos (threads).
- `s` : Semáforos, locks y condiciones.
- `i` : Emulación de interrupciones.
- `m` : Emulación de la máquina (requiere *USER_PROGRAM*).
- `d` : Emulación del disco (requiere *FILESYS*).
- `f` : Sistema de archivos (requiere *FILESYS*).
- `a` : Espacios de direcciones (requiere *USER_PROGRAM*).
- `e` : Manejo de excepciones (requiere *USER_PROGRAM*).

## 10. Constantes en los Makefiles

Las constantes `USER_PROGRAM`, `FILESYS_NEEDED` y `FILESYS_STUB` se definen en los siguientes Makefiles:

```bash
userprog/Makefile
vmem/Makefile
filesys/Makefile
```

Para encontrarlas, se puede utilizar el siguiente comando de búsqueda:

```bash
$ grep -Er "USER_PROGRAM|FILESYS_NEEDED|FILESYS_STUB"
threads/sys_info.cc:#ifdef USER_PROGRAM
threads/sys_info.cc:      "USER_PROGRAM "
threads/sys_info.cc:#ifdef FILESYS_STUB
threads/sys_info.cc:      "FILESYS_STUB "
threads/sys_info.cc:#ifdef FILESYS_NEEDED
threads/sys_info.cc:      "FILESYS_NEEDED "
threads/thread.hh:#ifdef USER_PROGRAM
threads/thread.hh:#ifdef USER_PROGRAM
threads/system.cc:#ifdef USER_PROGRAM
threads/system.cc:#ifdef FILESYS_NEEDED
threads/system.cc:#ifdef USER_PROGRAM  // Requires either *FILESYS* or *FILESYS_STUB*.
threads/system.cc:#ifdef USER_PROGRAM
threads/system.cc:#ifdef FILESYS_NEEDED
threads/system.cc:#ifdef USER_PROGRAM
threads/system.cc:#ifdef FILESYS_NEEDED
threads/system.cc:#ifdef USER_PROGRAM
threads/system.cc:#ifdef FILESYS_NEEDED
threads/system.cc:#ifdef USER_PROGRAM
threads/system.cc:#ifdef FILESYS_NEEDED
threads/thread.cc:#ifdef USER_PROGRAM
threads/thread.cc:#ifdef USER_PROGRAM
threads/system.hh:#ifdef USER_PROGRAM
threads/system.hh:#ifdef FILESYS_NEEDED  // *FILESYS* or *FILESYS_STUB*.
threads/scheduler.cc:#ifdef USER_PROGRAM  // Ignore until running user programs.
threads/scheduler.cc:#ifdef USER_PROGRAM
threads/main.cc:/// *USER_PROGRAM* options
threads/main.cc:#ifdef USER_PROGRAM
lib/debug.hh:/// * `m` -- machine emulation (requires *USER_PROGRAM*).
lib/debug.hh:/// * `a` -- address spaces (requires *USER_PROGRAM*).
lib/debug.hh:/// * `e` -- exception handling (requires *USER_PROGRAM*).
userprog/Makefile:DEFINES      = -DUSER_PROGRAM -DFILESYS_NEEDED -DFILESYS_STUB \
userprog/Makefile:#DEFINES      = -DUSER_PROGRAM -DFILESYS_NEEDED -DFILESYS
vmem/Makefile:DEFINES      = -DUSER_PROGRAM  -DFILESYS_NEEDED -DFILESYS_STUB -DVMEM \
vmem/Makefile:#DEFINES      = -DUSER_PROGRAM -DFILESYS_NEEDED -DFILESYS -DVMEM -DUSE_TLB
Makefile.common:#    before (as in this distribution), then it must define `FILESYS_STUB`.
filesys/Makefile:DEFINES      = -DUSER_PROGRAM -DVMEM -DFILESYS_NEEDED -DFILESYS -DDFS_TICKS_FIX
filesys/Makefile:#DEFINES      = -DTHREADS -DFILESYS_NEEDED -DFILESYS
filesys/file_system.hh:#ifdef FILESYS_STUB  // Temporarily implement file system calls as calls to
filesys/open_file.hh:#ifdef FILESYS_STUB  // Temporarily implement calls to Nachos file system as
machine/interrupt.cc:    } else {  // USER_PROGRAM
machine/interrupt.cc:#ifdef USER_PROGRAM
```

**Importante:** La constante `NETWORK` no se encuentra definida, ya que el código correspondiente fue eliminado en esta versión de la práctica.

