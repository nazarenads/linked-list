#ifndef LISTA_H
#define LISTA_H
#include <stddef.h>
#include <stdbool.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct lista;
typedef struct lista lista_t;
struct lista_iter;
typedef struct lista_iter lista_iter_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vac�a, si falla la creacion devuelve NULL.
lista_t* lista_crear(void);

// Devuelve verdadero si la lista no tiene elementos, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t* lista);

// Devuelve verdadero si el elemento se pudo insertar primero, false en caso contrario.
// Pre: la lista fue creada.
// Post: se agreg� un nuevo elemento al principio de la lista.
bool lista_insertar_primero(lista_t* lista, void* dato);

// Devuelve verdadero si el elemento se pudo insertar ultimo, false en caso contrario.
// Pre: la lista fue creada.
// Post: se agreg� un nuevo elemento al final de la lista.
bool lista_insertar_ultimo(lista_t* lista, void* dato);

// Devuelve el valor del primer elemento de la lista luego de borrarlo, 
// si la lista esta vac�a devuelve NULL.
// Pre: la lista fue creada.
// Post: se borr� el primer elemento de la lista. 
void* lista_borrar_primero(lista_t* lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si est� vac�a devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvi� el primer elemento de la lista, cuando no est� vac�a.
void* lista_ver_primero(const lista_t* lista);

// Obtiene el valor del �ltimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del �ltimo, si est� vac�a devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvi� el �ltimo elemento de la lista, cuando no est� vac�a.
void* lista_ver_ultimo(const lista_t* lista);

// Devuelve el largo de la lista.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t* lista);

// Destruye la lista. Si se recibe la funci�n destruir_dato por par�metro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una funci�n capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t* lista, void (*destruir_dato)(void*));

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea un iterador.
// Post: devuelve un iterador, si falla la creacion devuelve NULL.
lista_iter_t* lista_iter_crear(lista_t* lista);

// Avanza una posicion sobre la lista, si ya llego al ultimo devuelve NULL.
// Pre: el iterador se encuentra sobre el elemento actual.
// Post: el iterador se movio hacia el elemento siguiente
bool lista_iter_avanzar(lista_iter_t* iter);

// Devuelve el elemento sobre el cual se encuentra el iterador.
// Pre: el iterador fue creado.
// Post: se devolvi� el elemento actual de la lista.
void* lista_iter_ver_actual(const lista_iter_t* iter);

// Devuelve true si el iterador llego al final de la lista, es decir cuando el actual es NULL,
// false en caso contrario.
// Pre: el iterador fue creado y llego al final de la lista.
bool lista_iter_al_final(const lista_iter_t* iter);

// Destruye el iterador. 
// Pre: el iterador fue creado.
// Post: se eliminaron todos los elementos del iterador.
void lista_iter_destruir(lista_iter_t* iter);

// Inserta un dato en alguno de los nodos de la lista.
// Pre: el iterador fue creado.
// Post: uno de los nodos de la lista tiene almacenado el dato.
bool lista_iter_insertar(lista_iter_t* iter, void* dato);

// Borra el nodo en el que se encuentre el iterador y devuelve el dato.
// Pre: el iterador fue creado.
// Post: la lista tiene un nodo menos. 
void* lista_iter_borrar(lista_iter_t* iter);

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

//
//
//
void lista_iterar(lista_t* lista, bool visitar(void* dato, void* extra), void* extra);


/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementaci�n del alumno.
//
//
// Para la implementaci�n de las pruebas se debe emplear la funci�n
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_alumno(void);

#endif // LISTA_H