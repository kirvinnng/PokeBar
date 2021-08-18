#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "dibujo.h"
#include "main.h"

int main() {

    system("mode 150,40");

    inicio();
    system("pause > nul");
    inicioSesion();

    return 0;
}

void inicio() {

    int x = 33;
    int y = 10;
    dibujoCopa();
    gengar(x, y);
    printf(" ... ");
}

/*____________[ ACUMULADOR DE DIAS DE TRABAJO ]_____________*/
int contandoLosDias() {
    system("cls");
    FILE *tempDias;
    tempDias = fopen(FILE_DIAS, "ab");

    Dias el;
    el.dia = 1;

    int acumulador = 0;

    if (tempDias != NULL) {
        fwrite(&el, sizeof(Mesa), 1, tempDias);
        el.dia++;

        fseek(tempDias, 0, SEEK_END);
        acumulador = ftell(tempDias) / sizeof(Mesa);

        fclose(tempDias);
    }
    gotoxy(5, 1);
    printf("  DIA  %d DE TRABAJO \n", acumulador);

    return acumulador;
}

/*_____________[ Inicio de Sesion Para Ingresar a un Puesto de Trabajo ]______________*/
void inicioSesion() {

    system("color 0E"); // AMARILLO
    system("cls");
    char matrizMesa[CANT_MESA][CANT_MESA] = {" "};

    Pila *pilaReserva;
    inicpila(pilaReserva);
    const int RESER = 15;
    Reserva reservas[RESER];

    Mesa unaMesa[TAM_MESA];
    for (int i = 0; i < TAM_MESA; i++) {
        unaMesa[i] = limpiarVariables();
    }

    int contrasenia = 0;
    int noPasanlosDias = 0;
    int flag = 0;
    int move = 0;
    do {
        menuTitulo();
        menuInicioSesion();

        gotoxy(2, 16);
        printf("____________________");
        gotoxy(2, 15);
        scanf("%d", &contrasenia);

        switch (contrasenia) {
        case 0:
            system("cls");
            system("color 0D "); // CELESTE
            JIGGlypuff();
            Sleep(800);
            exit(0);

        case KEY_MOZO:

            // system("color 0A"); VERDE
            trabajoMozo(matrizMesa, flag, unaMesa);
            flag = 1;
            charizard(20, 0);
            break;

        case KEY_CAJERO:

            trabajoCajero(pilaReserva, reservas);
            squirtle();
            break;

        case KEY_ENCARGADO:

            trabajoEncargado(matrizMesa, flag, unaMesa, pilaReserva, reservas);
            charmander();

            break;

        default:
            gotoxy(3, 20);
            printf("\n\n Contrase%ca incorrecta\n Vuelva a Ingresar\n", 164);
            Sleep(900);

            break;
        }

        system("pause > nul");
        system("color 0E"); // AMARILLO
        system("cls");

    } while (contrasenia != 0);
}

void menuInicioSesion() {
    printf(" \n  INTEGRANTES DEL GRUPO  %c\n\n", OKEY);
    simpleLineHori(0, 30, 0, 7);
    printf("\n   %c Kevin Reyna          \n", 5); //                    ( ͡❛ ͜ʖ ͡❛)
    printf("   %c Daniel Diaz            \n", 2);
    printf("   %c Ezequiel Morales       \n\n", 14);
    simpleLineHori(0, 30, 0, 11);
    printf("\n");

    gotoxy(2, 13);
    printf("Inicie Sesion ");
    gotoxy(1, 19);
    printf(" Finalizar Programa ( 0 )\n");
    int x = 57;
    int y = 10;
    pikachuChico(x, y);
}

void menuTitulo() {
    gotoxy(52, 2);
    printf("___  ____ _  _ ____    ___  ____ ____ \n");
    gotoxy(52, 3);
    printf("|__] |  | |_/  |___    |__] |__| |__/ \n");

    gotoxy(52, 4);
    printf("|    |__| | \\_ |___    |__] |  | |  \\ \n");
    gotoxy(55, 1);
    printf("Sistema de Gestion de Restaurant\n");
}
void elegirOpcion(int *opcion, int *var, char *texto1, char *texto2) {

    printf("\n 1. %s Mozo\n", texto1);
    printf(" 2. %s Cajero\n", texto1);
    printf("%c Opcion : ", FLECHA_DER);
    fflush(stdin);
    scanf("%d", opcion);
    printf("\n %s : ", texto2);
    fflush(stdin);
    scanf("%d", var);
}

/*_____________________[ TRABAJO DEL ENCARGADO ]__________________*/ // Debe tener las funciones
                                                                     // del mozo y cajero
void trabajoEncargado(char matrizMesa[CANT_MESA][CANT_MESA], int bandera, Mesa unaMesa[], Pila *pilaReserva, Reserva reservas[]) {
    system("cls");
    // system("color 0A"); //VERDE
    system("color 0D"); // VIOLETA
    int x = 95;
    int y = 1;

    int op = 0;
    int opcion = 0;
    int var = 0;

    int legajo = 0;

    do {
        legajo = cantLegajos();
        machamp(x, y);
        menuEncargado(); // Menu del Encargado

        fflush(stdin);
        scanf("%d", &op);

        switch (op) {
        case 1:
            cargarDatosEmpleado();
            Sleep(1000);
            break;
        case 2:
            printf("\n 1. Ver Mozos\n");
            printf(" 2. Ver Cajeros\n\n");
            printf(" %c \n", GUION);
            scanf("%d", &opcion);
            verDatosEmpleado(opcion);
            break;
        case 3:

            elegirOpcion(&opcion, &var, "Modificar un", "Legajo del Empleado");
            modificarEmpleado(opcion, var, x, y);

            break;
        case 4:
            elegirOpcion(&opcion, &var, "Buscar un", "Posicion del Registro");
            buscarEmpleado(opcion, var);

            Sleep(1000);

            break;
        case 5:

            resetearArchivos();
            break;
        case 6:
            trabajoMozo(matrizMesa, bandera, unaMesa);

            break;
        case 7:
            trabajoCajero(pilaReserva, reservas);
            break;
        default:
            if (op != 0) {
                printf(" INGRESE LA OPCION CORRECTA\n");
            }
            break;
        }
        system("color 0D"); // VIOLETA
        system("cls");
    } while (op != 0);
}

void menuEncargado() {
    menuTitulo();
    gotoxy(5, 3);
    printf(" E N C A R G A D O  \n");
    simpleLineHori(1, 25, 2, 4);

    gotoxy(3, 9);
    printf(" 1. Ingresar un Nuevo Empleado\n");
    gotoxy(3, 10);
    printf(" 2. Ver los Empleados\n");
    gotoxy(3, 11);
    printf(" 3. Modificar Empleado \n");
    gotoxy(3, 12);
    printf(" 4. Buscar Empleado \n");
    gotoxy(3, 13);
    printf(" 5. Borrar Historiales (Mesas - Dinero - Dias) \n");
    gotoxy(3, 14);
    printf(" 6. Acceder como Mozo \n");
    gotoxy(3, 15);
    printf(" 7. Acceder como Cajero \n\n");
    gotoxy(3, 17);
    printf(" 0. Volver \n\n");

    simpleLineHori(1, 20, 1, 20);
    gotoxy(3, 19);
    printf("%c Opcion : ", FLECHA_DER);
}

void resetearArchivos() {
    remove(FILE_HISTORIAL_MESAS);
    remove(FILE_DIAS);
    remove(F_HISTORIAL_DINERO);
}

void buscarEmpleado(int puesto, int posicion) {
    FILE *archivoCajero;
    FILE *archivoMozo;

    Empleados unEmpleado;

    int i = 0;
    if (puesto == 1) {
        if ((archivoMozo = fopen(FILE_MOZO, "rb")) != NULL) {
            while (fread(&unEmpleado, sizeof(Empleados), 1, archivoMozo) > 0) {
                i++;
                if (posicion == i) {
                    printf("\n  ( Registro N.%d ) ", posicion); // VALIDACION de registros mediante un contador EN EL CICLo
                    verMozo(unEmpleado);
                } else {
                    printf(" \n  ( Registro invalido ) \n");
                }
            }

            fclose(archivoMozo);
        }

    } else if (puesto == 2) {
        if ((archivoCajero = fopen(FILE_CAJERO, "rb")) != NULL) {
            while (fread(&unEmpleado, sizeof(Empleados), 1, archivoCajero) > 0) {
                i++;

                if (posicion == i) {
                    printf("\n  ( Registro N.%d ) ", posicion);
                    verCajero(unEmpleado);
                } else {
                    printf("  ( Registro Invalido ) \n");
                }
            }
            fclose(archivoCajero);
        }
    }
}

int validarArchivo(int legajoIngresado, int puesto) {
    FILE *archivoCajero;
    FILE *archivoMozo;

    Empleados unEmpleado;
    int flag = 0;

    if (puesto == 1) {
        if ((archivoMozo = fopen(FILE_MOZO, "rb")) != NULL) {
            while (fread(&unEmpleado, sizeof(Empleados), 1, archivoMozo) > 0) {
                if (unEmpleado.mozo.datos.legajo == legajoIngresado) {
                    flag = 1;
                }
            }
            fclose(archivoMozo);
        }

    } else if (puesto == 2) {
        if ((archivoCajero = fopen(FILE_CAJERO, "rb")) != NULL) {
            while (fread(&unEmpleado, sizeof(Empleados), 1, archivoCajero) > 0) {
                if (unEmpleado.cajero.datos.legajo == legajoIngresado) {
                    flag = 1;
                }
            }
            fclose(archivoCajero);
        }
    }

    return flag;
}

void modificarEmpleado(int puesto, int legajo, int x, int y) {
    system("cls");
    machamp(x, y);
    menuTitulo();
    gotoxy(5, 3);
    printf(" E N C A R G A D O  \n");
    simpleLineHori(1, 25, 2, 4);

    FILE *archivoCajero;
    FILE *archivoMozo;

    Empleados unEmpleado;
    Empleados nuevo;

    int flag = 0;
    int i = 0;
    char valid = 's';
    if (puesto == 1) {
        if ((archivoMozo = fopen(FILE_MOZO, "r+b")) != NULL) {
            flag = validarArchivo(legajo, puesto);
            while (fread(&unEmpleado, sizeof(Empleados), 1, archivoMozo) > 0) {
                i++;
                if (flag == 1 && legajo == unEmpleado.mozo.datos.legajo) {
                    printf("\n  Registro N.%d ", legajo);
                    verMozo(unEmpleado);

                    printf("\n %c Seguro que desea Modificarlo ? ( s / n ) \n   . ", PREGUNTA);
                    fflush(stdin);
                    scanf("%c", &valid);
                    valid = tolower(valid);

                    if (valid == 's') {
                        printf(" ( Ingresar Nuevo Empleado ) \n\n");
                        nuevo.mozo.datos = scanDatosEmpleado();
                        nuevo.mozo.datos.legajo = unEmpleado.mozo.datos.legajo;
                        fseek(archivoMozo, sizeof(Empleados) * (i - 1), SEEK_SET);
                        fwrite(&nuevo, sizeof(Empleados), 1, archivoMozo);
                        break;
                    } else {
                        break;
                    }
                }
            }
            fclose(archivoMozo);
        }

    } else if (puesto == 2) {
        if ((archivoCajero = fopen(FILE_CAJERO, "r+b")) != NULL) {
            flag = validarArchivo(legajo, puesto);

            while (fread(&unEmpleado, sizeof(Empleados), 1, archivoCajero) > 0) {
                i++;
                if (flag == 1 && legajo == unEmpleado.cajero.datos.legajo) {
                    printf("\n  Registro N.%d ", legajo);
                    verCajero(unEmpleado);

                    printf("\n %c Seguro que desea Modificarlo ? ( s / n ) \n   .  ", PREGUNTA);
                    fflush(stdin);
                    scanf("%c", &valid);
                    valid = tolower(valid);

                    if (valid == 's') {
                        printf(" Ingresar Nuevo Empleado \n");

                        nuevo.cajero.datos = scanDatosEmpleado();
                        nuevo.cajero.datos.legajo = unEmpleado.cajero.datos.legajo;
                        fseek(archivoCajero, sizeof(Empleados) * (i - 1), SEEK_SET);
                        fwrite(&nuevo, sizeof(Empleados), 1, archivoCajero);
                        break;
                    } else {
                        break;
                    }
                }
            }
            fclose(archivoCajero);
        }
    }
}

dataEmpleado scanDatosEmpleado() {
    dataEmpleado datos;

    printf(" Nombre del Empleado : ");
    fflush(stdin);
    gets(datos.nombre);
    printf(" DNI : ");
    scanf("%d", &datos.dni);
    printf(" Edad : ");
    scanf("%d", &datos.edad);
    printf(" Ingrese la Direccion del Empleado : ");
    fflush(stdin);
    gets(datos.calle);

    return datos;
}
/*           Funcion de Cargar los Datos de los EMPLEADOS        */
void cargarDatosEmpleado() {
    FILE *archivoCajero;
    FILE *archivoMozo;
    Empleados unEmpleado;

    int legajo = cantLegajos();

    int op = 0;

    printf("\n    1. Mozo\n");
    printf("    2. Cajero\n\n");
    printf(" %c Elegir el Puesto de Trabajo : ", GUION);
    scanf("%d", &op);
    printf("\n");

    if (op == 1) {
        archivoMozo = fopen(FILE_MOZO, "ab");

        if (archivoMozo != NULL) {
            unEmpleado.mozo.datos = scanDatosEmpleado();
            legajo++;
            unEmpleado.mozo.datos.legajo = legajo;
            printf("\n El Legajo del Empleado %s es ( %d )\n", unEmpleado.mozo.datos.nombre, legajo);
            fwrite(&unEmpleado, sizeof(Empleados), 1, archivoMozo);
            Sleep(800);
        }
        fclose(archivoMozo);
    } else if (op == 2) {
        archivoCajero = fopen(FILE_CAJERO, "ab");
        if (archivoCajero != NULL) {
            unEmpleado.cajero.datos = scanDatosEmpleado();
            legajo++;
            unEmpleado.cajero.datos.legajo = legajo;
            printf("\n El Legajo del Empleado %s es ( %d )\n", unEmpleado.cajero.datos.nombre, legajo);
            fwrite(&unEmpleado, sizeof(Empleados), 1, archivoCajero);
            Sleep(800);
        }
        fclose(archivoCajero);
    }
}
/*           Cantidad de LEGAJOS CARGADOS             */
int cantLegajos() {
    FILE *fileCajero;
    FILE *fileMozo;

    Empleados unEmpleado;

    int legajoCajero = 0;
    fileCajero = fopen(FILE_CAJERO, "rb");
    fileMozo = fopen(FILE_MOZO, "rb");

    if (fileCajero != NULL) {
        fseek(fileCajero, 0, SEEK_END); // Colocar el Cursor al Final del Archivo

        legajoCajero = ftell(fileCajero) / sizeof(Empleados);
        fclose(fileCajero);
    }
    int legajoMozo = 0;
    if (fileMozo != NULL) {
        fseek(fileMozo, 0, SEEK_END);
        legajoMozo = ftell(fileMozo) / sizeof(Empleados);
        fclose(fileMozo);
    }

    return legajoCajero + legajoMozo;
}
/*            Los Datos de los EMPLEADOS             */
void verDatosEmpleado(int puesto) {
    FILE *archivoCajero;
    FILE *archivoMozo;
    Empleados nuevoEmpleado;

    if (puesto == 1) {
        archivoMozo = fopen(FILE_MOZO, "rb");
        if (archivoMozo != NULL) {
            while (fread(&nuevoEmpleado, sizeof(Empleados), 1, archivoMozo) > 0) {
                printf("\n\t\t[MOZOS] ");
                verMozo(nuevoEmpleado);
                Sleep(300);
            }
            fclose(archivoMozo);
        } else {
            printf(" El Archivo no Existe\n");
        }

    } else if (puesto == 2) {
        archivoCajero = fopen(FILE_CAJERO, "rb");
        if (archivoCajero != NULL) {
            while (fread(&nuevoEmpleado, sizeof(Empleados), 1, archivoCajero) > 0) {
                printf("\n\t\t[CAJEROS] ");
                verCajero(nuevoEmpleado);
                Sleep(300);
            }
            fclose(archivoCajero);
        } else {
            printf(" El Archivo no Existe\n");
        }
    }
    printf(" ( FIN DE LA LISTA ) \n ... ");
    system(" pause > nul");
}
/*          VER DATOS DE LOS EMPLEADOS                 */
/*                 ( MOZO )                */
void verMozo(Empleados elEmpleado) {
    printf("\n\n");
    printf(" EMPLEADO : %s \n", elEmpleado.mozo.datos.nombre);
    printf(" DNI: %d\n", elEmpleado.mozo.datos.dni);
    printf(" Edad: %d \n", elEmpleado.mozo.datos.edad);
    printf(" Direccion: %s \n", elEmpleado.mozo.datos.calle);
    printf(" Legajo: %d \n", elEmpleado.mozo.datos.legajo);
    printf("________________________\n");
}
/*                 ( CAJERO )                */
void verCajero(Empleados elEmpleado) {
    printf("\n\n");
    printf(" EMPLEADO - %s \n", elEmpleado.cajero.datos.nombre);
    printf(" DNI: %d\n", elEmpleado.cajero.datos.dni);
    printf(" Edad: %d \n", elEmpleado.cajero.datos.edad);
    printf(" Direccion: %s \n", elEmpleado.cajero.datos.calle);
    printf(" Legajo: %d\n", elEmpleado.cajero.datos.legajo);
    printf("________________________\n");
}

/*____________________________[ EL TRABAJO DEL MOZO  ]__________________________*/

void trabajoMozo(char matrizMesa[CANT_MESA][CANT_MESA], int bandera, Mesa unaMesa[]) {
    system("cls");
    // system("color 0A"); // VERDE
    system("color 0B"); // CELESTE
    int x = 60;
    int y = 7;
    int mesaAccion = 0;

    if (bandera == 0) {
        cargarDibujoMesa(matrizMesa, CANT_MESA);
    }

    int op = 0;

    do {
        meowth(x, y);
        menuMOZO(matrizMesa);

        scanf("%d", &op);
        fflush(stdin);
        switch (op) {
        case 1:

            printf("\n Numero de Mesa a Abrir : ");
            fflush(stdin);
            scanf("%d", &mesaAccion);
            mesaParaABRIR(matrizMesa, mesaAccion, unaMesa);

            break;
        case 2:
            printf("\n Ingrese el NUMERO DE MESA :");
            scanf("%d", &mesaAccion);
            agregarNuevosPedidos(unaMesa, mesaAccion);

            break;
        case 3:
            system("cls");
            mostrarPedidosActuales(unaMesa, TAM_MESA);
            break;
        case 4:
            printf("\n 0. Atras \n");
            printf("\n Numero de Mesa a Cerrar : ");
            scanf("%d", &mesaAccion);

            if (1 == unaMesa[mesaAccion - 1].flag) {
                desocuparMesa(matrizMesa, CANT_MESA, mesaAccion);
                cerrarUnaMesa(mesaAccion, unaMesa);

            } else if (mesaAccion != 0) {
                printf("\n ( Esta mesa NO esta Ocupada, Debe abrirla antes de Cerrarla )\n");
                Sleep(1500);
            }

            break;
        case 5:
            mostrarHistorialMesasCerradas();
            break;
        }

        system("cls");
        system("color 0B"); // CELESTE
    } while (op != 0);
}

void menuMOZO(char matrizMesa[][CANT_MESA]) {
    menuTitulo();
    gotoxy(7, 1);
    printf(" M O Z O    \n");
    simpleLineHori(1, 20, 2, 2);
    dibujoMesa(matrizMesa, CANT_MESA);

    printf("\n\n 1. Abrir Mesa \n");
    printf(" 2. Agregar PEDIDOS a una Mesa\n");
    printf(" 3. Pedidos actuales\n");
    printf(" 4. Cerrar una Mesa\n");
    printf(" 5. Ver historial de Mesas Cerradas\n");
    printf("\n 0. Volver \n");

    simpleLineHori(1, 24, 0, 7);
    simpleLineVert(1, 11, 24, 8);
    simpleLineHori(1, 24, 0, 19); /*****   LINEAS DE LA MESA           */
    simpleLineHori(1, 20, 1, 31);

    gotoxy(2, 30);
    printf("%c ", GUION);
}

/*                   Abrir una MESA              */
void mesaParaABRIR(char matrizMesa[][CANT_MESA], int abrir, Mesa unaMesa[]) {
    if (abrir <= 0 ^ abrir > 9) {
        printf("Esta mesa no Existe \n");
    } else {
        if (unaMesa[abrir - 1].flag == 0) {
            unaMesa[abrir - 1] = limpiarVariables();

            hacerPedido(abrir, unaMesa);
            menuTitulo();
            ocuparMESA(matrizMesa, CANT_MESA, abrir);
        } else if (unaMesa[abrir - 1].flag == 1) {
            printf("\n\nLA MESA YA ESTA OCUPADA\n\n");
            Sleep(1500);
        }
    }
}

/*             EL  DIBUJO  DEL  SALON            */
void dibujoMesa(char arrMesa[][CANT_MESA], int cant) {
    printf("\n\n\n      ( S A L O N ) \n");

    for (int i = 0; i < cant; i++) {
        printf("\n\n");
        for (int j = 0; j < cant; j++) {
            printf(" | %c |\t", arrMesa[i][j]);
        }
        printf("\n\n\n");
    }
}

/*            PARA CARGAR EL DIBUJO DEL SALON AL PRINCIPIO        */
void cargarDibujoMesa(char arrMesa[][CANT_MESA], int cant) {
    int cantidad = 49;
    for (int i = 0; i < cant; i++) {
        for (int j = 0; j < cant; j++) {
            arrMesa[i][j] = (char)cantidad++; // Se cargan con numeros del 1 al 9
        }
    }
}

/*            PARA REMPLAZAR LOS NUMEROS CON LAS LETRAS           */
void ocuparMESA(char arrMesa[][CANT_MESA], int cant, int mesaElegida) {
    char arrBiAux[CANT_MESA][CANT_MESA];
    cargarMatrizLETRAS(CANT_MESA, arrBiAux);

    char eleccion = (char)mesaElegida + 48;

    for (int i = 0; i < cant; i++) {
        for (int j = 0; j < cant; j++) {
            if (eleccion == arrMesa[i][j]) {
                arrMesa[i][j] = arrBiAux[i][j]; // Se remplaza el numero por la letra
            }
        }
    }
}

/*        Cargar una matriz de LETRAS ( SE USO PARA HACER COMPARACIONES )*/
void cargarMatrizLETRAS(int cant, char arrAUX[][CANT_MESA]) {
    int letras = 65;
    for (int e = 0; e < cant; e++) {
        for (int f = 0; f < cant; f++) {
            arrAUX[e][f] = letras++; // Carga la Matriz de la "A HASTA I"
        }
    }
}

/*         REMPLAZAR LAS LETRAS  por el NUMERO  de la mesa       */
void desocuparMesa(char arrMesa[][CANT_MESA], int cant, int mesaElegida) {
    char arrAUX[CANT_MESA][CANT_MESA];
    cargarMatrizLETRAS(CANT_MESA, arrAUX); // Se carga la matriz para hacer comparaciones

    char eleccion = (char)mesaElegida + 64;
    for (int i = 0; i < cant; i++) {
        for (int j = 0; j < cant; j++) {
            if (eleccion == arrAUX[i][j]) {
                arrMesa[i][j] = (char)mesaElegida + 48; // Se remplaza la LETRA con el NUMERO
            }
        }
    }
}
/*              PARA CERRAR LA MESA              */
void cerrarUnaMesa(int cerrada, Mesa cerrarMesa[]) {
    FILE *historialMesas;
    historialMesas = fopen(FILE_HISTORIAL_MESAS, "ab");

    int i = 0;
    Mesa auxMesa;
    auxMesa = cerrarMesa[cerrada - 1];

    if (historialMesas != NULL) {
        fwrite(&auxMesa, sizeof(Mesa), 1, historialMesas);
    }
    cobrarMesa(cerrada, cerrarMesa[cerrada - 1]);

    fclose(historialMesas);
    cerrarMesa[cerrada - 1] = limpiarVariables(); // Limpiamos las variables de la estructura
}

void mostrarHistorialMesasCerradas() {
    FILE *historialMesa;
    historialMesa = fopen(FILE_HISTORIAL_MESAS, "rb");
    Mesa unaMesa;

    if (historialMesa != NULL) {
        while (fread(&unaMesa, sizeof(Mesa), 1, historialMesa) > 0) {
            pedidosMesa(unaMesa);
            Sleep(450);
        }
        fclose(historialMesa);
    } else {
        printf("\nTODAVIA NO HAY MESAS CERRADAS\n\n");
    }
    printf(" ...  ");
    system("pause > nul");
    system("cls");
}

void agregarNuevosPedidos(Mesa laMesa[], int agregar) {
    if (laMesa[agregar - 1].flag == 1) {
        hacerPedido(agregar, laMesa);
    } else {
        printf(" Esta mesa no esta Abierta\n");
        Sleep(900);
    }
}

/*__________________[  MOSTRAR LOS PEDIDOS CARGADOS EN LAS MESAS ]___________*/
void mostrarPedidosActuales(Mesa unaMesa[], int tam) {
    int banderita = 0;
    printf("\n\n");
    for (int i = 0; i < tam; i++) {
        if (unaMesa[i].flag == 1) {
            pedidosMesa(unaMesa[i]); //
            banderita = 1;
            Sleep(450);
        }
    }
    if (banderita == 1) {
        printf(" ESTAS SON TODAS LAS MESAS OCUPADAS\n");
        system("pause > nul");
    }
}
/*_________________[ Se muestra el HISTORIAL DE MESAS CERRADAS ]_______________*/

/*        MOSTRAMOS LOS PEDIDOS CARGADOS POR EL MOZO         */
void pedidosMesa(Mesa laMesa) {
    printf(" NUMERO DE MESA : %d\n\n", laMesa.numeroMesa);
    if (laMesa.consumos.cant_cubiertos > 0) {
        printf(" CANT CUBIERTOS : %d \n", laMesa.consumos.cant_cubiertos);
    }
    if (laMesa.consumos.cant_burger > 0) {
        printf(" CANT HAMBURGESAS : %d\n", laMesa.consumos.cant_burger);
    }
    if (laMesa.consumos.cant_pizza > 0) {
        printf(" CANT PIZZA : %d\n", laMesa.consumos.cant_pizza);
    }
    if (laMesa.consumos.cant_papas > 0) {
        printf(" CANT PAPAS : %d\n", laMesa.consumos.cant_papas);
    }
    if (laMesa.consumos.cant_agua > 0) {
        printf(" CANT AGUA : %d\n\n", laMesa.consumos.cant_agua);
    }
    if (laMesa.consumos.cant_soda > 0) {
        printf(" CANT AGUA CON GAS : %d\n", laMesa.consumos.cant_soda);
    }
    if (laMesa.consumos.cant_cerveza > 0) {
        printf(" CANT CERVEZA : %d\n", laMesa.consumos.cant_cerveza);
    }
    if (laMesa.consumos.cant_fernet > 0) {
        printf(" CANT FERNET : %d\n", laMesa.consumos.cant_fernet);
    }
    if (laMesa.consumos.cant_vino > 0) {
        printf(" CANT VINO : %d\n", laMesa.consumos.cant_vino);
    }
    if (laMesa.consumos.cant_cassata > 0) {
        printf(" CANT POSTRE CASSATA : %d\n", laMesa.consumos.cant_cassata);
    }

    if (laMesa.consumos.cant_mixFruta > 0) {
        printf(" CANT ENSALADA DE FRUTAS : %d\n", laMesa.consumos.cant_mixFruta);
    }

    if (laMesa.consumos.cant_donPedro > 0) {
        printf(" CANT POSTRE DON PEDRO : %d\n", laMesa.consumos.cant_donPedro);
    }
    printf("\n PRECIO TOTAL : $%.2f \n", laMesa.precioTotal);
    printf("______________________________________\n\n");
}

/*   Limpieza de las variables   */
Mesa limpiarVariables() {
    Mesa vaciarMesa;

    vaciarMesa.consumos.cant_cassata = 0;
    vaciarMesa.consumos.cant_donPedro = 0;
    vaciarMesa.consumos.cant_mixFruta = 0;
    vaciarMesa.consumos.cant_cerveza = 0;
    vaciarMesa.consumos.cant_vino = 0;
    vaciarMesa.consumos.cant_agua = 0;
    vaciarMesa.consumos.cant_soda = 0;
    vaciarMesa.consumos.cant_fernet = 0;
    vaciarMesa.consumos.cant_pizza = 0;
    vaciarMesa.consumos.cant_papas = 0;
    vaciarMesa.consumos.cant_burger = 0;
    vaciarMesa.consumos.cant_cubiertos = 0;
    vaciarMesa.precioTotal = 0;
    vaciarMesa.flag = 0;

    /*   SE INICIALIZA EL PRECIO DE LOS PRODUCTOS   */
    vaciarMesa.cubierto = 50;
    vaciarMesa.carta.comidas.burger = 380;
    vaciarMesa.carta.comidas.pizza = 210;
    vaciarMesa.carta.comidas.papas = 180;

    vaciarMesa.carta.bebidas.agua = 80;
    vaciarMesa.carta.bebidas.cerveza = 130;
    vaciarMesa.carta.bebidas.fernet = 130;
    vaciarMesa.carta.bebidas.vino = 150;
    vaciarMesa.carta.bebidas.soda = 80;

    vaciarMesa.carta.postres.cassata = 190;
    vaciarMesa.carta.postres.mixFruta = 140;
    vaciarMesa.carta.postres.donPedro = 190;

    return vaciarMesa;
}

/* _______________[ FUNCIONALIDAD DE LOS PEDIDOS ]_______________*/
void hacerPedido(int abrir, Mesa laMesa[]) {
    system("cls");

    laMesa[abrir - 1].numeroMesa = abrir;
    laMesa[abrir - 1].flag = 1;

    int op = 0;
    int cantidad = 0;
    int guardaPrecio;

    do {
        printf("\n");
        mostrarCarta();
        pedidosMesa(laMesa[abrir - 1]);

        printf(" %c  Opcion : ", FLECHA_DER);
        scanf("%d", &op);
        switch (op) {
        case 0:
            break;
        case 1:
            printf(" Cantidad de Cubiertos : ");
            scanf("%d", &cantidad);
            if (laMesa[abrir - 1].consumos.cant_cubiertos >= 8) {
                printf(" En la Mesa no entran mas Personas ");
                Sleep(3000);
            } else if (cantidad <= 8 && cantidad > 0) {
                laMesa[abrir - 1].precioTotal += laMesa[abrir - 1].cubierto * cantidad;
                laMesa[abrir - 1].consumos.cant_cubiertos += cantidad;

            } else if (cantidad > 8) {
                printf(" La mesa no es tan Grande :( ");
                Sleep(2300);
            } else if (cantidad < 1) {
                printf(" Pero ingresaste a la opcion de Cubiertos y \n  no me ingresas el numero "
                       "de personas :RAGE: ");
                Sleep(5000);
            }
            break;
        case 2:
            printf(" %c Ingrese la Cantidad de Pizzas: ", GUION);
            scanf("%d", &cantidad);
            if (cantidad > 0) {
                laMesa[abrir - 1].precioTotal += laMesa[abrir - 1].carta.comidas.pizza * cantidad;
                laMesa[abrir - 1].consumos.cant_pizza += cantidad;

            } else {
                printf(" Cantidad Invalida ");
                Sleep(300);
            }

            break;
        case 3:
            printf(" %c Ingrese la Cantidad de Hamburgesas: ", GUION);
            scanf("%d", &cantidad);
            if (cantidad > 0) {
                laMesa[abrir - 1].precioTotal += laMesa[abrir - 1].carta.comidas.burger * cantidad;
                laMesa[abrir - 1].consumos.cant_burger += cantidad;
            } else {
                printf(" Cantidad Invalida ");
                Sleep(300);
            }

            break;
        case 4:
            printf(" %c Ingrese la Cantidad de Papas: ", GUION);
            scanf("%d", &cantidad);
            if (cantidad > 0) {
                laMesa[abrir - 1].precioTotal += laMesa[abrir - 1].carta.comidas.papas * cantidad;
                laMesa[abrir - 1].consumos.cant_papas += cantidad;

            } else {
                printf(" Cantidad Invalida ");
                Sleep(300);
            }

            break;
        case 5:
            printf(" %c Ingrese la Cantidad de Botella de Agua: ", GUION);
            scanf("%d", &cantidad);
            if (cantidad > 0) {
                laMesa[abrir - 1].precioTotal += laMesa[abrir - 1].carta.bebidas.agua * cantidad;
                laMesa[abrir - 1].consumos.cant_agua += cantidad;
            } else {
                printf(" Cantidad Invalida ");
                Sleep(300);
            }
            break;
        case 6:
            printf(" %c Ingrese la Cantidad de Botella de Sodas: ", GUION);
            scanf("%d", &cantidad);
            if (cantidad > 0) {
                laMesa[abrir - 1].precioTotal += laMesa[abrir - 1].carta.bebidas.soda * cantidad;
                laMesa[abrir - 1].consumos.cant_soda += cantidad;
            } else {
                printf(" Cantidad Invalida ");
                Sleep(300);
            }
            break;
        case 7:
            printf(" %c Ingrese la Cantidad de Botella de Vinos: ", GUION);
            scanf("%d", &cantidad);
            if (cantidad > 0) {
                laMesa[abrir - 1].precioTotal += laMesa[abrir - 1].carta.bebidas.vino * cantidad;
                laMesa[abrir - 1].consumos.cant_vino += cantidad;
            } else {
                printf(" Cantidad Invalida ");
                Sleep(300);
            }
            break;
        case 8:
            printf(" %c Ingrese la Cantidad de Botella 1L Fernet: ", GUION);
            scanf("%d", &cantidad);
            if (cantidad > 0) {
                laMesa[abrir - 1].precioTotal += laMesa[abrir - 1].carta.bebidas.fernet * cantidad;
                laMesa[abrir - 1].consumos.cant_fernet += cantidad;
            } else {
                printf(" Cantidad Invalida ");
                Sleep(300);
            }
            break;
        case 9:
            printf(" %c Ingrese la Cantidad de Botella de Cerveza: ", GUION);
            scanf("%d", &cantidad);
            if (cantidad > 0) {
                laMesa[abrir - 1].precioTotal += laMesa[abrir - 1].carta.bebidas.cerveza * cantidad;
                laMesa[abrir - 1].consumos.cant_cerveza += cantidad;
            } else {
                printf(" Cantidad Invalida ");
                Sleep(300);
            }
            break;
        case 10:
            printf(" %c Ingrese la Cantidad de Postre Cassata: ", GUION);
            scanf("%d", &cantidad);
            if (cantidad > 0) {
                laMesa[abrir - 1].precioTotal += laMesa[abrir - 1].carta.postres.cassata * cantidad;
                laMesa[abrir - 1].consumos.cant_cassata += cantidad;
            } else {
                printf(" Cantidad Invalida ");
                Sleep(300);
            }
            break;
        case 11:
            printf(" %c Ingrese la Cantidad de Postre Don Pedro: ", GUION);
            scanf("%d", &cantidad);
            if (cantidad > 0) {
                laMesa[abrir - 1].precioTotal += laMesa[abrir - 1].carta.postres.donPedro * cantidad;
                laMesa[abrir - 1].consumos.cant_donPedro += cantidad;
            } else {
                printf(" Cantidad Invalida ");
                Sleep(300);
            }

            break;
        case 12:
            printf(" %c Ingrese la Cantidad de Ensalada de Fruta: ", GUION);
            scanf("%d", &cantidad);
            if (cantidad > 0) {
                laMesa[abrir - 1].precioTotal += laMesa[abrir - 1].carta.postres.mixFruta * cantidad;
                laMesa[abrir - 1].consumos.cant_mixFruta += cantidad;
            } else {
                printf(" Cantidad Invalida ");
                Sleep(300);
            }
            break;
        }

        system("cls");
    } while (op > 0);
}

void lineaHorizontalArriba(int tam) {
    for (int i = 0; i < tam; i++) {
        if (i == 0) {
            printf("\t\t\t\t\t\t\t%c", 218);
        }
        if (i == tam - 1) {
            printf("%c\n", 191);
        } else {
            printf("%c", HORI);
        }
    }
}

void lineaHorizontalAbajo(int tam) {
    for (int i = 0; i < tam; i++) {
        if (i == 0) {
            printf("\t\t\t\t\t\t\t%c", 192);
        }
        if (i == tam - 1) {
            printf("%c", 217);
        } else {
            printf("%c", HORI);
        }
    }
}

/*_______________________[  LA CARTA   ]_________________________*/
void mostrarCarta() {
    system("color 0A"); // VERDE
    /*   Precios   */
    Mesa laMesa;
    laMesa = limpiarVariables();
    int tam = 35;
    int x = 1;
    int y = 3;

    bulbasaur(x, y);
    gotoxy(61, 1);

    printf("[        POKE BAR        ]       \n");

    lineaHorizontalArriba(tam);
    printf("\t\t\t\t\t\t\t%c                                  %c\n", VERT, VERT);
    printf("\t\t\t\t\t\t\t%c 0. Salir de la Carta             %c\n", VERT, VERT);
    printf("\t\t\t\t\t\t\t%c 1. Cantidad de Cubiertos %d c/u  %c\n", VERT, laMesa.cubierto, VERT);
    printf("\t\t\t\t\t\t\t%c                                  %c\n", VERT, VERT);
    printf("\t\t\t\t\t\t\t%c ----------- Comidas ----------   %c\n", VERT, VERT);
    printf("\t\t\t\t\t\t\t%c 2. Pizza  $%d c/u               %c\n", VERT, laMesa.carta.comidas.pizza, VERT);
    printf("\t\t\t\t\t\t\t%c 3. Burger  $%d c/u              %c\n", VERT, laMesa.carta.comidas.burger, VERT);
    printf("\t\t\t\t\t\t\t%c 4. Papas   $%d c/u              %c\n", VERT, laMesa.carta.comidas.papas, VERT);

    printf("\t\t\t\t\t\t\t%c                                  %c\n", VERT, VERT);
    printf("\t\t\t\t\t\t\t%c ----------- Bebidas ----------   %c\n", VERT, VERT);
    printf("\t\t\t\t\t\t\t%c 5. Agua    $%d c/u               %c\n", VERT, laMesa.carta.bebidas.agua, VERT);
    printf("\t\t\t\t\t\t\t%c 6. Agua con Gas $%d c/u          %c\n", VERT, laMesa.carta.bebidas.soda, VERT);
    printf("\t\t\t\t\t\t\t%c 7. Vino $%d c/u                 %c\n", VERT, laMesa.carta.bebidas.vino, VERT);
    printf("\t\t\t\t\t\t\t%c 8. Fernet $%d c/u               %c\n", VERT, laMesa.carta.bebidas.fernet, VERT);
    printf("\t\t\t\t\t\t\t%c 9. Cervezas $%d c/u             %c\n", VERT, laMesa.carta.bebidas.cerveza, VERT);
    printf("\t\t\t\t\t\t\t%c                                  %c\n", VERT, VERT);
    printf("\t\t\t\t\t\t\t%c ----------- Postres ------------ %c\n", VERT, VERT);
    printf("\t\t\t\t\t\t\t%c 10. Cassata $%d c/u             %c\n", VERT, laMesa.carta.postres.cassata, VERT);
    printf("\t\t\t\t\t\t\t%c 11. Don Pedro $%d c/u           %c\n", VERT, laMesa.carta.postres.donPedro, VERT);
    printf("\t\t\t\t\t\t\t%c 12. Ensalada de Fruta $%d c/u   %c\n", VERT, laMesa.carta.postres.mixFruta, VERT);
    lineaHorizontalAbajo(tam);

    printf("\n");
}

void trabajoCajero(Pila *pilaReserva, Reserva reservas[]) {
    system("cls");
    system("color 0A"); // VERDE
    int x = 80;
    int y = 3;

    int posicionReserva = 0;
    int op = 0;
    int numRes = 0;
    int i = 0;
    int j = 0;
    int flag = 0;
    int dineroActual = 0;

    do {
        psyduck(x, y);
        menuCajero();

        fflush(stdin);
        scanf("%d", &op);

        switch (op) {
        case 1:
            reservas[i] = pedirDatosCliente(*pilaReserva, x, y); // Pedir Datos de la Reserva

            apilarReservas(reservas, pilaReserva, i);
            i++;

            break;
        case 2:
            ordenarReservas(pilaReserva);
            mostrar(pilaReserva);

            if (!pilavacia(pilaReserva)) {
                printf("\n Numero de RESERVA : "); // Ver UNA DETERMINA RESERVA
                scanf("%d", &numRes);
            }
            flag = verificarEntrada(*pilaReserva, numRes);

            if (flag == 1) {
                verLaReserva(reservas, numRes, i);
                system("pause > nul");

            } else if (flag == 0) {
                printf("\n No existe ese Numero de Reserva \n");
                Sleep(1000);
            }
            break;
        case 3:

            dineroActual = verGananciasActuales();
            printf("\n El dinero Guardado Hasta el momento : $%d ", dineroActual);
            Sleep(1000);

            break;
        }

        system("cls");
    } while (op != 0);
}

void menuCajero() {
    menuTitulo();
    gotoxy(5, 3);
    printf(" C A J E R O      \n\n\n");
    simpleLineHori(1, 20, 2, 4);

    printf("\n\n\n\n 1. Atender el Telefono (Reservar una Mesa)\n");
    printf(" 2. Ver Reserva\n");
    printf(" 3. Ver Ganancias Actuales \n\n");
    printf(" 0. Volver \n\n");

    simpleLineHori(1, 20, 1, 16);
    gotoxy(2, 15);
    printf(" > Opcion : ");
}

void cobrarMesa(int numMesa, Mesa cerrada) {
    system("cls");

    float total = cerrada.precioTotal;
    char aplicar = 's';
    float descuento = 0;
    int dineroRecibido = 0;
    int x = 70;
    int y = 2;
    diglett(x, y);
    gotoxy(5, 3);
    printf(" C A J E R O      \n\n\n");
    simpleLineHori(1, 20, 2, 4);
    printf("\n\n\n");
    pedidosMesa(cerrada);                                           // MUESTRO EL TICKET
    printf("%c Desea aplicar un descuento ? (s / n) \n", PREGUNTA); // Pregunto SI DESEA UN DESCUENTO
    printf("       . ");
    fflush(stdin);
    scanf("%c", &aplicar);
    aplicar = tolower(aplicar);

    if (aplicar == 's') {
        do {
            printf("\n Ingrese %% de descuento : ");
            fflush(stdin);
            scanf("%f", &descuento);
        } while (descuento < 0 || descuento > 100);

        descuento = total * (descuento / 100); // APLICO EL DESCUENTO
        total -= descuento;
    }

    printf("\n EL PRECIO TOTAL ES : $%.2f\n\n", total);

    do {
        printf(" Ingrese el Dinero Recibido del Cliente : ");
        fflush(stdin);
        scanf("%d", &dineroRecibido);
        if (dineroRecibido < total) {
            printf("\n El dinero Recibido es inferior al Precio Total \n");
        }
    } while (dineroRecibido < total);

    int vuelto = dineroRecibido - total;
    printf("\n El vuelto al Cliente es de : $%d \n", vuelto);

    guardarDinero(total);
    printf(" ...  ");
    system("pause > nul");
}

void guardarDinero(int total) {
    FILE *fileDinero;
    if ((fileDinero = fopen(F_HISTORIAL_DINERO, "ab")) != NULL) {
        fwrite(&total, sizeof(int), 1, fileDinero);
        fclose(fileDinero);
    } else {
        printf(" El dinero no se guardo, NOS ROBARON !!!!!!! \n");
    }
}

int verGananciasActuales() {
    FILE *dineroActual;
    int aux = 0;
    int dinero = 0;
    if ((dineroActual = fopen(F_HISTORIAL_DINERO, "rb")) != NULL) {
        while (fread(&aux, sizeof(int), 1, dineroActual) > 0) {
            dinero += aux;
        }
        fclose(dineroActual);
    }
    return dinero;
}
Reserva pedirDatosCliente(Pila a, int x, int y) {
    system("cls");
    psyduck(x, y);
    menuTitulo();
    gotoxy(5, 3);
    printf(" C A J E R O      \n\n\n");
    simpleLineHori(1, 20, 2, 4);

    printf("\n\n  (  Ingrese los Datos  )\n\n");

    Reserva persona;
    int flag = 0;
    persona.cantidadPersonas = 0;
    printf(" 1. Nombre : ");
    fflush(stdin);
    gets(persona.nombre);
    printf(" 2. Telefono : ");
    gets(persona.tel);

    for (int i = 0; i < strlen(persona.tel); i++) {
        if (persona.tel[i] == ' ') {
            persona.tel[i] = '-';
        }
    }

    do {
        printf(" 3. Cantidad de personas : ");
        scanf("%d", &persona.cantidadPersonas);
        if (persona.cantidadPersonas < 1 || persona.cantidadPersonas > 8) {
            printf(" Ingresaste una cantidad de personas no APTAS para el Tama%co de la Nuestras "
                   "Mesas \n",
                   164);
        }

    } while (persona.cantidadPersonas < 1 || persona.cantidadPersonas > 8);

    do {
        printf(" 4. Numero de Reserva :");
        scanf("%d", &persona.numeroReserva);
        if (persona.numeroReserva > 0) {
            flag = verificarEntrada(a, persona.numeroReserva);
            if (flag == 1) {
                flag = 1;
                printf(" Ese numero de Reserva ya esta Ocupado\n Ingrese otro. \n");
            }
        } else {
            printf(" Ingrese un Numero Positivo\n");
        }
    } while (flag != 0 || persona.numeroReserva <= 0);

    return persona;
}

void mostraUNAreserva(Reserva unaReserva) {
    printf("_________________________________\n\n");
    printf(" Nombre : %s \n", unaReserva.nombre);
    printf(" Telefono : %s \n", unaReserva.tel);
    printf(" Cantidad de Personas : %d \n", unaReserva.cantidadPersonas);
    printf(" Numero de Reserva : %d \n", unaReserva.numeroReserva);
    printf("_________________________________\n\n");
}
/*       Apilar en la Pila los NUMEROS DE RESERVAS */
void apilarReservas(Reserva persona[], Pila *reserva, int j) {
    int personaReserva = persona[j].numeroReserva;
    apilar(reserva, personaReserva);
}
/*              MOSTRAR UNA RESERVA DETERMINADA            */
void verLaReserva(Reserva persona[], int numReserva, int totalReser) {
    int i = 0;
    while (i < totalReser) {
        if (numReserva == persona[i].numeroReserva) {
            mostraUNAreserva(persona[i]);
        }
        i++;
    }
}
/*     Verificar si el Numero de Reserva ya esta ocupado o no */
int verificarEntrada(Pila a, int numReserva) {
    int flag = 0;
    while (!pilavacia(&a)) {
        if (tope(&a) == numReserva) { // Verificar si Esta el Numero de Reserva
            desapilar(&a);
            flag = 1;
        } else {
            desapilar(&a);
        }
    }
    return flag;
}
/* Ordenar los numeros de Reservas */
void ordenarReservas(Pila *ordenar) {
    Pila aux, mayor, local;
    inicpila(&aux);
    inicpila(&mayor);
    inicpila(&local);

    while (!pilavacia(ordenar)) {
        apilar(&mayor, desapilar(ordenar));

        while (!pilavacia(ordenar)) {
            if (tope(&mayor) > tope(ordenar)) {
                apilar(&aux, desapilar(ordenar));
            } else {
                apilar(&aux, desapilar(&mayor));
                apilar(&mayor, desapilar(ordenar));
            }
        }
        apilar(&local, desapilar(&mayor));

        while (!pilavacia(&aux)) {
            apilar(ordenar, desapilar(&aux));
        }
    }
    while (!pilavacia(&local)) {
        apilar(ordenar, desapilar(&local));
    }
}
