#pragma once

#include "pila.h"

#define FLECHA_DER 26
#define OKEY 251
#define PREGUNTA 168
#define VERT 179
#define HORI 196
#define GUION 175
#define KEY_MOZO 54321
#define KEY_CAJERO 12345
#define KEY_ENCARGADO 98765

#define FILE_MOZO "database/fileMozo.bin"
#define FILE_CAJERO "database/fileCajero.bin"
#define F_HISTORIAL_DINERO "database/dineroMesas.bin"
#define FILE_HISTORIAL_MESAS "database/historialMesas.bin"
#define FILE_DIAS "database/historialDias.bin"

#define CANT_MESA 3
#define TAM_MESA CANT_MESA *CANT_MESA // EL TAMAÑO DE LA ESTRUCTURA ( CALCULO :  CANT_MESA 3 =  3x3  = 9 : TAM_MESA ) :)

/*________[ Struct Alimentos y Bebidas ]____________*/

/* Cantidades    */
typedef struct {
    int cant_cassata;
    int cant_donPedro;
    int cant_mixFruta;
    int cant_cerveza;
    int cant_vino;
    int cant_agua;
    int cant_soda;
    int cant_fernet;
    int cant_pizza;
    int cant_papas;
    int cant_burger;
    int cant_cubiertos;
} CantConsumos;
/*    Alimentos   */
typedef struct {
    int cassata;
    int donPedro;
    int mixFruta;
} Postres;
typedef struct {
    int cerveza;
    int vino;
    int agua;
    int soda;
    int fernet;
} Bebidas;
typedef struct {
    int pizza;
    int papas;
    int burger;
} Comidas;
typedef struct {
    Bebidas bebidas;
    Postres postres;
    Comidas comidas;
} Carta;
/*_____________[ CONTANDO LOS DIAS ]____________*/
typedef struct {
    int dia;
    int meses;
} Dias;
/*_____________[ Struct Reservar Mesa ]____________*/
typedef struct {
    char nombre[60];
    char tel[30];
    int cantidadPersonas;
    int numeroReserva;

} Reserva;
/*-____________[ Struct MESA ]______________*/
typedef struct {
    Carta carta;

    int cubierto; // Precio
    float precioTotal;
    int numeroMesa;
    int flag;
    CantConsumos consumos;

} Mesa;
/*________[   Struct Datos Empleado ]__________*/
typedef struct {
    char nombre[50];
    int edad;
    int dni;
    char calle[30];
    int legajo;

} dataEmpleado;
/*    Cajero    */
typedef struct {
    dataEmpleado datos;
    float sueldo;

} Cajero;
/*     Mozo      */
typedef struct {
    dataEmpleado datos;
    float sueldo;

} Mozo;
typedef struct {
    Cajero cajero;
    Mozo mozo;

} Empleados;
/*----------------------  FIN DE LAS ESTRUCTURAS   --------------------*/

/*------------ (  PROTOTIPADO  )------------*/
void inicioSesion();
int contandoLosDias();

/* ________[   MENUS  ]_______*/
void menuTitulo();
void menuEncargado();
void menuMOZO(char matrizMesa[][CANT_MESA]);
void menuCajero();
void menuInicioSesion();
/*      LAS FUNCIONES DEL ENCARGADO     */
void trabajoEncargado(char matrizMesa[CANT_MESA][CANT_MESA], int bandera, Mesa unaMesa[], Pila *pilaReserva, Reserva reservas[]);
dataEmpleado scanDatosEmpleado();
void cargarDatosEmpleado();
void verDatosEmpleado(int puesto);
void verCajero(Empleados elEmpleado);
void verMozo(Empleados elEmpleado);
int cantLegajos();
void resetearArchivos();
void mostrarDeterminadoEmpleado(int puesto, int pos);
void modificarEmpleado(int puesto, int pos, int x, int y);
void buscarEmpleado(int puesto, int pos);
void elegirOpcion(int *opcion, int *var, char *texto1, char *texto2);
int validarArchivo(int legajoIngresado, int puesto);

/*      LAS FUNCIONES DEL MOZO     */
void trabajoMozo(char matrizMesa[CANT_MESA][CANT_MESA], int bandera, Mesa unaMesa[]);
void mostrarCarta();
void hacerPedido(int abrir, Mesa laMesa[]);

/*        Dibujos del SALON         */
void dibujoMesa(char arrMesa[][CANT_MESA], int cant);
void cargarMatrizLETRAS(int cant, char arrAUX[][CANT_MESA]);
void ocuparMESA(char arrMesa[][CANT_MESA], int cant, int mesaElegida);
void cargarDibujoMesa(char arrMesa[][CANT_MESA], int cant);
void mesaParaABRIR(char matrizMesa[][CANT_MESA], int abrir, Mesa unaMesa[]);
void desocuparMesa(char arrMesa[][CANT_MESA], int cant, int mesaElegida);
void lineaHorizontalArriba(int tam);
void lineaHorizontalAbajo(int tam);

/*   Funciones de las MESAS    */
Mesa limpiarVariables();

void mostrarPedidosActuales(Mesa unaMesa[], int tam);
void cerrarUnaMesa(int pos, Mesa cerrarMesa[]);
void mostrarHistorialMesasCerradas();
void pedidosMesa(Mesa laMesa);
void agregarNuevosPedidos(Mesa laMesa[], int agregar);

/*________________[ FUNCIONES DEL CAJERO]________*/
void trabajoCajero(Pila *pilaReserva, Reserva reservas[]);
void guardarDinero(int total);
void cobrarMesa(int numMesa, Mesa cerrada);
int verGananciasActuales();

/*       funciones de reservas    */

Reserva pedirDatosCliente(Pila pilaReserva, int x, int y);
void verLaReserva(Reserva persona[], int numReserva, int totalReser);
void mostraUNAreserva(Reserva unaReserva);
void apilarReservas(Reserva persona[], Pila *reserva, int j);
int verificarEntrada(Pila a, int numReserva);
void ordenarReservas(Pila *ordenar);
void inicio();
