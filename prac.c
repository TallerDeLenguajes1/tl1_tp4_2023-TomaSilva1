#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct persona
{
    char *nombre;
    int edad;
}typedef persona;

struct Nodo
{
    persona persona;
    struct Nodo *siguiente;
}typedef nodo;

void cargar(nodo **nuevo);
void listar(nodo **nuevo, nodo **varon, nodo **mujer);
nodo *extraer(nodo **lista, int edad);
void mostrarV(nodo *varon);
void mostarM(nodo *mujer);
void eliminarID(nodo **varon, nodo **mujer);

int main(){

nodo *nuevo = NULL;
nodo *varon = NULL;
nodo *mujer = NULL;

int stop;

 do
 {
    cargar(&nuevo);
    printf("Cargar otra pesona? \n1-(SI)\n2-(NO)\n : ");
    fflush(stdin);
    scanf("%d",&stop);
 } while (stop != 2);
    fflush(stdin);
    listar(&nuevo,&varon,&mujer);
    puts("paso");
    mostrarV(varon);
    mostarM(mujer);
    eliminarID(&varon,&mujer);
    mostrarV(varon);
    mostarM(mujer);

return 0;
}

void cargar(nodo **nuevo){
    char buffer[45];
    nodo *aux = malloc(sizeof(nodo)*1);
    srand(time(NULL));

    printf("Ingrese el nombre: ");
    fflush(stdin);
    gets(buffer);

    aux->persona.nombre = malloc(sizeof(nodo)*strlen(buffer)+1);
    strcpy(aux->persona.nombre,buffer);

    printf("Ingrese la edad: ");
    fflush(stdin);
    scanf("%d",&aux->persona.edad);

    aux->siguiente = NULL;

    if (*nuevo == NULL)
    {
        *nuevo = aux;
    }else{
        aux->siguiente = *nuevo;
        *nuevo = aux;
    }

}

nodo *extraer(nodo **lista, int edad){
    nodo *aux = *lista;
    nodo *auxAnt = *lista;
    while (aux && aux->persona.edad != edad)
    {
        auxAnt = aux;
        aux = aux->siguiente;
    }
    if (aux == *lista)
    {
        *lista = aux->siguiente;
    }else{
        auxAnt->siguiente = aux->siguiente;
    }
    return aux;
}

void listar(nodo **nuevo, nodo **varon, nodo **mujer){
    nodo *aux = *nuevo;
    nodo *aux2 = NULL;
    int auxN;
    while(aux != NULL){
        printf("Nombre: %s\n",aux->persona.nombre);
        printf("Edad: %d\n",aux->persona.edad);
        printf("Sexo\n1-Varon\n2-Mujer\n : ");
        scanf("%d",&auxN);
        
        if (auxN == 1)
        {
            aux2 = aux;
            aux = aux->siguiente;

            aux2 = extraer(nuevo,aux2->persona.edad);

            aux2->siguiente = *varon;
            *varon = aux2;

        }else if(auxN == 2){
            aux2 = aux;
            aux = aux->siguiente;

            aux2 = extraer(nuevo,aux2->persona.edad);

            aux2->siguiente = *mujer;
            *mujer = aux2;
        }else{
            aux = aux->siguiente;
        }
    }
}

void mostrarV(nodo *varon){
    nodo *aux = varon;
    printf("======VARONES======\n");
    while(aux != NULL){
        printf("Nombre: %s\n",aux->persona.nombre);
        printf("Edad: %d\n",aux->persona.edad);
        printf("Sexo: VARON\n");
        aux = aux->siguiente;
        puts("=================");
    }
}

void mostarM(nodo *mujer){
    nodo *aux = mujer;
    printf("======MUJERES======\n");
    while (aux != NULL)
    {
        printf("Nombre: %s\n",aux->persona.nombre);
        printf("Edad: %d\n",aux->persona.edad);
        printf("Sexo: MUJER\n");
        aux = aux->siguiente;
        puts("=================");
    }
}

void eliminarID(nodo **varon, nodo **mujer){
    nodo *aux = *varon;
    nodo *auxAnt = NULL;
    char nom[45];
    printf("Ingrese el nombre a eliminar: \n");
    fflush(stdin);
    gets(nom);
    while(aux && strstr(aux->persona.nombre,nom) == NULL){
        auxAnt = aux;
        aux = aux->siguiente;
    }
    if(aux == NULL){
        aux = *mujer;
        auxAnt = NULL;
        while (aux && strstr(aux->persona.nombre,nom) == NULL)
        {
            auxAnt = aux;
            aux = aux->siguiente;
        }
        if (aux == NULL)
        {
            puts("No se econtro ninguna persona.\n");
        }else if(aux == *mujer){
                *mujer = aux->siguiente;
                free(aux);
                printf("Se elimino el nombre %s\n", nom);
            }else {
                auxAnt->siguiente = aux->siguiente;
                free(aux);
                printf("Se elimino el nombre %s\n", nom);
        }
    }else if(aux == *varon){
        *varon = aux->siguiente;
        free(aux);
        printf("Se elimino el nombre %s\n", nom);
    }else{
        auxAnt->siguiente = aux->siguiente;
        free(aux);
        printf("Se elimino el nombre %s\n", nom);
    }
}