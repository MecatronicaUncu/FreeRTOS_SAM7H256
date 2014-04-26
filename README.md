FreeRTOS en SAM7-H256 (Olimex) con programador ARM-USB-TINY
============

El objetivo del proyecto fue migrar el sistema operativo FreeRTOS a la plataforma [SAM7-H256](https://www.olimex.com/Products/ARM/Atmel/SAM7-H256/) utilizando el programador  [ ARM-USB-TINY ](https://www.olimex.com/Products/ARM/JTAG/ARM-USB-TINY/).

Se obtiene un sistema operativo de tiempo real, que puede ser utilizado para aplicaciones de robótica, control, etc.

En este repositorio se incluyen:

- Los archivos del sistema operativo FreeRTOS para la plataforma (carpeta FreeRTOS).

- Los archivos de configuración del programador (carpeta OpenOCD).

- Documentación útil del proyecto (carpeta Doc).

- Archivos de configuración para Eclipse (carpeta Config).

## Sistema Operativo

El proyecto se probó con éxito en 
 - Arch Linux - openocd 0.8.0_rc1 - arm-none-eabi-gcc 4.9.0 - eclipse 4.3.2

Debería funcionar con modificaciones menores en otros sistemas linux (Ubuntu, Fedora).

Puede ser portado con un poco más de esfuerzo a sistemas Windows utilizando [Yagarto](http://www.yagarto.org/).

## Requerimientos
Los siguientes paquetes son necesarios:

- **arm-none-eabi:**
De ser posible, la suite completa (gcc + gdb + binutils).

- **OpenOCD:**
Para programar el uC y hacer debug en tiempo real.

- **Eclipse IDE for C/C++
Para un entorno de trabajo cómodo y para hacer debug en tiempo real.

## Compilación
Para verificar el correcto funcionamiento del compilador, debe ejecutarse:

    cd cd FreeRTOS/Demo/ARM7_AT91SAM7X256_Eclipse/RTOSDemo/
    make all
    
En caso de una compilación correcta, se obtiene un mensaje similar al siguiente al finalizar
    ....
    arm-none-eabi-objcopy RTOSDemo.elf -O ihex RTOSDemo.hex
    arm-none-eabi-objcopy RTOSDemo.elf -O binary RTOSDemo.bin

De obtenerse un mensaje de error, debe verificarse la correcta instalación de arm-none-eabi.

## Configuración Udev
Debido a que el programador se conecta por USB, debemos habilitar la regla Udev correspondiente en Linux.
Puede utilizarse el comando siguiente como root:

    echo 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="15ba", ATTRS{idProduct}=="0004", MODE="0666"' > /etc/udev/rules.d/99-olimex-arm.rules

## Flasheado

De obtener una compilación exitosa, puede flashearse el binario obtenido en la tarjeta de desarrollo.
Primero, nos conectamos al programador mediante OpenOCD

    cd OpenOCD
    openocd -f SAM7_JTAG_TINY.cfg
    
En otra terminal, debemos conectarnos por telnet a OpenOCD y proceder al flasheado

    telnet localhost 4444
    reset init
    at91sam_flash

Nota: una interfaz gráfica será desarrollada para facilitar este proceso

## Configuración del proyecto en Eclipse
Eclipse puede ser utilizado como entorno de desarrollo para el proyecto, como así también para debug en tiempo real

TODO: Para configurar Eclipse, buscar las instrucciones en Doc/ConfigurarEclipse.pdf
