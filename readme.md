## **INFORME TP 1**

**Alumno:** Andrés Fernández

**Padrón:** 102220

**Link al repositorio:** https://github.com/andres912/Taller_TP1

### **DESCRIPCIÓN**

El siguiente diagrama muestra de forma muy general el funcionamiento del código:

![Captura](capturas/MessageDiagram.png)

Con un poco más de detalle, el funcionamiento del código es el siguiente:

* TDA Client / TDA Server:

    Son los TDAs que se encargan de llevar a cabo el envío y la recepción del mensaje de forma general. Ambos cuentan con los siguientes atributos:

        - TDA Cipher: para codificar/decodificar el mensaje.
        - TDA Socket: para enviar/recibir el mensaje. El Server tiene dos sockets, uno de conexión y otro de aceptación.
        - Buffer: el buffer utilizado para transportar cada chunk del mensaje desde que se lee de STDIN hasta que se escribe en STDOUT.


* Primero, el TDA Server establece a través de su TDA Socket la conexión necesaria para eventualmente recibir el mensaje. Si la conexión falla, el programa del Server se cierra. Esta paso no se incluyó en el diagrama porque el diagrama muestra otro tipo de secuencia, y agregar este paso lo volvía confuso.

* Si la conexión fue exitosa, el Server se quedará esperando a que el Client haga su conexión correspondiente.

* Por su lado, el TDA Client establecerá la conexión necesaria para el envío del mensaje. De no poder conectarse, el programa del Client se cierra. De lo contrario, se iniciará el ciclo de envío del mensaje. A partir de aquí, la secuencia contada seguirá el mismo esquema que el diagrama mostrado.

* El Cliente lee el mensaje de STDIN. Este mensaje es tomado como una cadena de bytes, y no como un string de caracteres (se transforma a unsigned char y no se usa strlen para conocer su largo). Este mensaje se lee de forma cíclica, en trozos de 64 bytes. El fin del ciclo se da cuando la función **feof** devuelve verdadero. La función **fread** marca la cantidad de bytes leídos, que puede ser como máximo 64. Esta cantidad de bytes leídos se utiliza a lo largo del ciclo de envío del mensaje.


* El Cliente envía el trozo del mensaje leído al TDA Cipher que tiene instanciado, que se encargará de codificarlo de acuerdo a los argumentos recibidos por parámetro.

* TDA Cipher:

	Es el TDA que se "encarga" de codificar o decodificar un mensaje (utiliza internamente un TDA Encoder de acuerdo al tipo de traducción requerido).

	    - callback_t init_function: puntero a función de inicio. Hay una función de inicio por tipo de traducción.
        - callback_t init_function: puntero a función de traducción. Hay una función de traducción por tipo de traducción.
        - callback_t init_function: puntero a función de cierre. Hay una función de cierre por tipo de traducción.
        - void* encoder: un puntero genérico al encoder que finalmente terminará realizando la traducción. Se pasa por parámetro en las tres funciones anteriormente mencionadas. Hay 3 tipos de encoders:

* TDA CesarEncoder:

        - int offset: el offset usado en la traducción.
        - int op_type: 0 para codificar, 1 para decodificar.

* TDA VigenereEncoder:

        - char* key_string: la clave de cifrado utilizada.
        - int op_type: 0 para codificar, 1 para decodificar.
        - int key_length: el largo de la clave de cifrado.
        - int last_pos: la última posición visitada en el mensaje (valor necesario para guardar el estado entre chunks del mensaje).

* TDA Rc4Encoder:

        - char* key_string: la clave de cifrado utilizada.
        - int pos_1: la posición 1 utilizada en el cifrado RC4 (valor necesario para guardar el estado entre chunks del mensaje)
        - int pos_1: la posición 2 utilizada en el cifrado RC4 (valor necesario para guardar el estado entre chunks del mensaje). 
        - unsigned char arreglo[256]: el arreglo random utilizado en el cifrado RC4 (es necesario guardar el mismo para todo el mensaje).         


* El cipher codifica el trozo de 64 Bytes del mensaje en un buffer correspondiente al Cliente. El Cliente le indica a su Socket que reenvíe este buffer al socket servidor. El envío del mensaje se hace mediante un ciclo, ya que no necesariamente los 64 Bytes (o el largo del trozo de mensaje) son enviados en una única operación.

* TDA Socket:

	Es el TDA que se encarga de conectarse a los sockets "reales" (los provistos por la librería correspondiente) y de enviar y/o recibir un mensaje a/desde otro socket. Tiene los siguientes atributos:

		- struct addrinfo* addr_info: es una estructura propia de la librería de sockets, necesaria para la conexión entre los mismos.
    	- int connection_socket_fd: guarda el fd correspondiente al socket de conexión (en el caso del socket cliente, es el único socket necesario).
    	- int acceptance_socket_fd: guarda el fd correspondiente al socket de aceptación, que es el que termina recibiendo el mensaje (sólo necesario para el servidor).

    En un primer momento, había hecho dos tipos de socket distintos: un TDA transmissionSocket y otro TDA receptorSocket, cada uno con sus propios métodos y alguna diferencia en su estructura (el transmissionSocket no tenía acceptance_socket_fd). Sin embargo, como en clase se hizo hincapié a que ambos sockets pueden enviar y recibir información, me pareció más correcto terminar haciendo un único TDA socket que agrupara a todos los métodos.

* El socket servidor recibe el mensaje del socket cliente. Al igual que en el envío, la recepción del total de los bytes se realiza en un ciclo. A diferencia de la operación de envío, en la recepción no se conoce la cantidad de bytes a recibir del cliente, por lo que el ciclo se corta cuando en una de las operaciones se recibieron 0 bytes.

* El trozo de mensaje se envía a un nuevo cipher, que esta vez se encargará de decodificarlo. Para Cesar y Vigenere, se realizará la operación matemática inversa a la realizada durante la codificación. Para RC4, la operación será exactamente la misma que en su codificación.

* Se envía el trozo de mensaje para ser impreso por salida estándar, y se vuelve a iniciar el ciclo. Recién en este momento, se vuelve a tomar la cadena de bytes como un string, por lo que se hace un printf con "%c" como formato.

### **COMENTARIOS**

* El uso de las líneas **// cppcheck-suppress unusedStructMember** está relacionado a que se utilizan punteros a funciones a la hora de inicializar, traducir y cerrar los encoders. Por lo tanto, cppcheck asume que no se están utilizando los atributos de los encoders cuando en realidad sí están siendo utilizados.

* Además de las dificultades mencionadas, también surgió una a la hora de enviar y recibir el mensaje entre los sockets. Tardé bastante en darme cuenta de ir actualizando la posición inicial del envío del buffer en cada **send** y en cada **receive**. Es decir, si en la primera operación de envío se enviaron n bytes, en la próxima operación el envío del mensaje debía comenzar desde la posición buffer[n], y la cantidad de bytes a enviar debería ser de k-n bytes (con k el largo del trozo de mensaje). De forma análoga debía hacerse con la recepción del mensaje.

* Intenté usar el heap lo menos posible, pero en algunos casos tuve que decidir entre el uso del heap y un código más prolijo. Por ejemplo, pude hacer un único tipo callback_t para las funciones de decodificación, pero para eso fue necesario un vector de punteros genéricos para cuya utilización tuve que usar malloc.

* En un primer momento, había intentado leer el stdin de a 64 bytes, pero pasando todo a un buffer que contuviera la totalidad del mensaje. A partir de ahí, sólo se tenía un buffer a codificar y enviar al servidor. El problema es que eso implicaba poner un límite a la cantidad de bytes que podía contener el mensaje, porque el buffer estaba en memoria estática y necesitaba darle un tamaño antes de leer stdin. Cuando entendí mejor lo que se pedía en el enunciado, tuve que cambiar el funcionamiento del código.




