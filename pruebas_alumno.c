#include "lista.h"
#include "testing.h"
#include "pila.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                   FUNCIONES AUXILIARES ALUMNO
 * *****************************************************************/

bool insertar_muchos_elementos(lista_t* lista){
	bool insertar;
	for (int i=0; i<10000; i++){
		int* p = malloc(sizeof(int));
		*p = i;
		insertar = lista_insertar_ultimo(lista, p);
		if (insertar == false){
			return false;
		}
	}
	return insertar;
}

void* borrar_muchos_elementos(lista_t* lista){
	int* primero;
	void* borrar_primero;
	for(int i=0; i<10000; i++){
		primero = lista_ver_primero(lista);
		borrar_primero = lista_borrar_primero(lista);
		if (primero != borrar_primero){
			return NULL;
		}
		free(borrar_primero);
	}
	return borrar_primero; 
}



bool imprimir_un_item(void *elemento, void *extra)
{
    // Sabemos que �extra� es un entero, por tanto le podemos hacer un cast.
    int *contador = extra;
    printf("%d. %s\n", ++(*contador), (char*) elemento);

    return true; // seguir iterando
}

void imprimir_iter_interno(lista_t *lista)
{
    int num_items = 0;
    lista_iterar(lista, imprimir_un_item, &num_items);
    printf("Tengo que comprar %d �tems\n", num_items);
}


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_lista_vacia(){
	printf("INICIO DE PRUEBAS CON LISTA VACIA\n");
	/* Declaro las variables a utilizar*/
	lista_t* lista = lista_crear();

	/* Inicio de pruebas */
	print_test("Crear lista vacia", lista != NULL);
	print_test("Lista recien creada esta vacia", lista_esta_vacia(lista)==true);
	print_test("Lista vacia tiene largo 0", lista_largo(lista)==0);
	print_test("Al intentar ver primero de una lista vacia devuelve null", lista_ver_primero(lista)==NULL);
	print_test("Tampoco se puede ver el ultimo de una lista vacia", lista_ver_ultimo(lista)==NULL);
	print_test("Intentar borrar el primero en lista vacia devuelve null",lista_borrar_primero(lista)==NULL);

	/* Destruyo la lista*/
    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);

}

void pruebas_lista_algunos_elementos(){
	printf("INICIO DE PRUEBAS CON LISTA DE TAMANIO PEQUENIO\n");

	/* Declaro las variables a utilizar*/
	lista_t* lista = lista_crear();
	int valor = 5;
	int otro_valor = 12;

	/* Inicio de pruebas */
	printf("PRUEBAS INSERTANDO Y BORRANDO UN SOLO ELEMENTO\n");
    print_test("Insertar primero un elemento", lista_insertar_primero(lista, &valor) == true);
	print_test("Despues de insertar lista_esta_vacia devuelve false", lista_esta_vacia(lista) == false);
	print_test("Despues de insertar un elemento el largo de la lista es 1", lista_largo(lista) == 1);
	print_test("Borrar el unico elemento de la lista devuelve el valor correcto", lista_borrar_primero(lista) == &valor);
	print_test("Ahora la lista esta vacia nuevamente", lista_esta_vacia(lista) == true);
	print_test("El primero de la lista vacia es NULL", lista_ver_primero(lista) == NULL);
	print_test("Borrar el primero de la lista vacia devuelve NULL", lista_borrar_primero(lista) == NULL);
    print_test("Insertar primero NULL devuelve true", lista_insertar_primero(lista, NULL) == true);
	print_test("El primero de la lista ahora es NULL", lista_ver_primero(lista) == NULL);
	print_test("Borrar el elemento NULL de la lista devuelve NULL", lista_borrar_primero(lista) == NULL);
	print_test("Ahora la lista esta vacia nuevamente", lista_esta_vacia(lista) == true);

	printf("PRUEBAS INSERTANDO Y BORRANDO DOS ELEMENTOS\n");
	print_test("Insertar primero un elemento en la lista vacia", lista_insertar_primero(lista, &valor) == true);
	print_test("Insertar ultimo un segundo elemento", lista_insertar_ultimo(lista, &otro_valor) == true);
	print_test("El largo de la lista luego de insertar dos elementos es dos", lista_largo(lista)==2);
	print_test("El primero es 5", lista_ver_primero(lista)==&valor);
	print_test("El ultimo es 12", lista_ver_ultimo(lista)==&otro_valor);
	print_test("Borrar el primer elemento", lista_borrar_primero(lista) == &valor);
	print_test("Borrar el ultimo elemento", lista_borrar_primero(lista) == &otro_valor);
	print_test("Ahora la lista esta vacia nuevamente", lista_esta_vacia(lista) == true);

	/* Destruyo la lista*/
    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);
}

void pruebas_lista_grandes_volumenes(){
	/* Declaro las variables a utilizar*/
	lista_t* lista = lista_crear();

	printf("INICIO DE PRUEBAS CON LISTA DE TAMANIO GRANDE\n");
	print_test("Insertar muchos elementos devuelve true", insertar_muchos_elementos(lista) == true);
	print_test("Despues de insertar 10 mil elementos la lista tiene largo 10000", lista_largo(lista)==10000);
	print_test("Borrar muchos elementos", borrar_muchos_elementos(lista) != NULL);
	print_test("Ahora la lista esta vacia nuevamente", lista_esta_vacia(lista) == true);
	print_test("Despues de borrar los 10 mil elementos la lista tiene largo 0", lista_largo(lista)==0);
	
	/* Destruyo la lista*/
    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);
}

void pruebas_lista_insertando_pila(){
	printf("INICIO DE PRUEBAS INSERTANDO PILA \n");

	/* Declaro las variables a utilizar*/
	lista_t* lista = lista_crear();
	pila_t* pila = pila_crear();

	print_test("Insertar una pila devuelve true", lista_insertar_primero(lista, pila) == true);

	typedef void (*destructor_elemento)(void*);

	lista_destruir(lista, (destructor_elemento)pila_destruir);
	print_test("Destruir la lista pasando la funcion pila_destruir", true);
}

void pruebas_lista_insertando_puntero(){
	printf("INICIO DE PRUEBAS INSERTANDO PUNTERO \n");
	int* p = malloc(sizeof(int));
	lista_t* otra_lista = lista_crear();

	print_test("Insertar int* devuelve true", lista_insertar_primero(otra_lista, p) == true);

	lista_destruir(otra_lista, free);
	print_test("Destruir la lista pasando la funcion free", true);

}


void pruebas_iterador_externo(){
	printf("INICIO DE PRUEBAS CON ITERADOR EXTERNO\n");
	/* Declaro las variables a utilizar */
	lista_t* lista = lista_crear();
	int valor = 5;

	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("Inserto un elemento con el iterador recien creado", lista_iter_insertar(iter, &valor) == true);
	print_test("Al insertar un elemento con el iterador recien creado, se inserta al principio", lista_ver_primero(lista) == &valor);
	print_test("Me fijo en que posicion se encuentra el iterador ahora", lista_iter_ver_actual(iter)!=NULL);
	print_test("Avanzo un lugar en la lista", lista_iter_avanzar(iter) == true);
	print_test("No puedo avanzar porque llegue al final de la lista", lista_iter_avanzar(iter) == false);
	print_test("Chequeo que estoy al final", lista_iter_al_final(iter)==true);

	
	lista_destruir(lista, NULL);
	lista_iter_destruir(iter);
}


void pruebas_iterador_interno(){
	printf("INICIO DE PRUEBAS CON ITERADOR INTERNO\n");

	lista_t *super = lista_crear();

    lista_insertar_ultimo(super, "leche");
    lista_insertar_ultimo(super, "huevos");
    lista_insertar_ultimo(super, "pan");
    lista_insertar_ultimo(super, "mermelada");

	imprimir_iter_interno(super);

	lista_destruir(super, NULL);

}

void pruebas_lista_alumno() {
	pruebas_lista_vacia();
	pruebas_lista_algunos_elementos();
	pruebas_lista_grandes_volumenes();
	pruebas_lista_insertando_pila();
	pruebas_lista_insertando_puntero();
	pruebas_iterador_externo();
	pruebas_iterador_interno();
}
