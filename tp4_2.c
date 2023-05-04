#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef tarea;

struct Nodo {
    tarea tarea;
    struct Nodo *Siguiente;
};


void subir(struct Nodo **comienzo);
void mostrar(struct Nodo *comienzo, struct Nodo *realizadas, struct Nodo *proceso);
void buscar1(struct Nodo *comienzo, struct Nodo *realizadas,struct Nodo *proceso, int dato);
void buscar2(struct Nodo *comienzo, struct Nodo *realizadas,struct Nodo *proceso, char *dato2);
void eliminarId(struct Nodo **comienzo, struct Nodo **realizadas,int dato3);
void mostrarDatos(struct Nodo *comienzo, struct Nodo *realizadas,int dato4);
void cargar(struct Nodo **comienzo);
void mover(struct Nodo **comienzo, struct Nodo **realizadas, struct Nodo **proceso);
struct Nodo *extraerTarea(struct Nodo **lista, int id);

int main(){
int cant=0,aux,stop,dato,aux2,dato3,dato4;
char dato2[35];

struct Nodo *comienzo = NULL;
struct Nodo *realizadas = NULL;
struct Nodo *proceso = NULL;

while (stop != 2)
{
    cargar(&comienzo);
    cant++;
    printf("Agregar otra tarea(1), Parar(2): ");
    scanf("%d",&stop);
}


fflush(stdin);
fflush(stdin);
mover(&comienzo,&realizadas,&proceso);
mostrar(comienzo,realizadas,proceso);

puts("===INTERFAZ DE USUARIO===");
printf("Buscar tarea por ID(1), \nBuscar tarea por palabra(2)\nParar(3)");
scanf("%d",&aux2);
switch (aux2)
{
case 1:
    printf("Ingrese el id de la tarea a buscar: ");
    scanf("%d",&dato);
    buscar1(comienzo,realizadas,proceso,dato);
    break;
    case 2:
    printf("Ingrese la palabra de la tarea a buscar: ");
    fflush(stdin);
    gets(dato2);
    buscar2(comienzo,realizadas,proceso,dato2);
    break;

default:
    break;
}
    
    printf("Ingrese la id para eliminar: ");
    scanf("%d",&dato3);
    eliminarId(&comienzo,&realizadas,dato3);


    printf("---Mostrar listas---\n-1: Pendientes.\n-2: Realizadas.\n-: ");
    fflush(stdin);
    scanf("%d",&dato4);
    mostrarDatos(comienzo,realizadas,dato4);

return 0;
}



void mostrar(struct Nodo *comienzo, struct Nodo *realizadas, struct Nodo *proceso){
    struct Nodo *aux = comienzo;
    puts("=====PENDIENTES=====");
    while(aux != NULL){
        printf("Descripcion: %s\n", aux->tarea.Descripcion);
        printf("ID :%d\n", aux->tarea.TareaID);
        printf("Duracion: %d\n",aux->tarea.Duracion);
        aux=aux->Siguiente;
    }
    puts("=====EN PROCESO=====");
    aux = proceso;
    while(aux != NULL){
        printf("Descripcion: %s\n", aux->tarea.Descripcion);
        printf("ID :%d\n", aux->tarea.TareaID);
        printf("Duracion: %d\n",aux->tarea.Duracion);
        aux=aux->Siguiente;
    }
    puts("=====REALIZADAS=====");
    aux = realizadas;
    while (aux != NULL)
    {
        printf("Descripcion: %s\n", aux->tarea.Descripcion);
        printf("ID :%d\n", aux->tarea.TareaID);
        printf("Duracion: %d\n",aux->tarea.Duracion);
        aux=aux->Siguiente;
    } 
}

void buscar1(struct Nodo *comienzo, struct Nodo *realizadas,struct Nodo *proceso, int dato){
    struct Nodo *aux = comienzo;
    struct Nodo *aux2 = realizadas;
    struct Nodo *aux3 = proceso;

    while (aux != NULL)
    {
        if (aux->tarea.TareaID == dato)
        {
            printf("Id del nodo encontrado: %d\n", aux->tarea.TareaID);
            printf("Duracion: %d\n", aux->tarea.Duracion);
            printf("Descripcion: %s\n", aux->tarea.Descripcion);
            printf("PENDIENTE\n");
        }
        aux = aux->Siguiente;
    }

    while (aux2 != NULL)
    {
        if (aux2->tarea.TareaID == dato)
        {
            printf("Id del nodo encontrado: %d\n", aux2->tarea.TareaID);
            printf("Duracion: %d\n", aux2->tarea.Duracion);
            printf("Descripcion: %s\n", aux2->tarea.Descripcion);
            printf("REALIZADA\n");
        }
        aux2 = aux2->Siguiente;
    }

    while(aux3 != NULL){
        if(aux3->tarea.TareaID == dato){
            printf("Id del nodo encontrado: %d\n", aux3->tarea.TareaID);
            printf("Duracion: %d\n", aux3->tarea.Duracion);
            printf("Descripcion: %s\n", aux3->tarea.Descripcion);
            printf("EN PROCESO\n");
        }
        aux3 = aux3->Siguiente;
    }
}

void buscar2(struct Nodo *comienzo, struct Nodo *realizadas,struct Nodo *proceso, char *dato2){
    struct Nodo *aux = comienzo;

    while (aux && strstr(aux->tarea.Descripcion,dato2) == NULL)
    {
        aux = aux->Siguiente;
    }
    if (aux==NULL){
        aux = realizadas;
        while(aux && strstr(aux->tarea.Descripcion,dato2) == NULL){
            aux = aux->Siguiente;
        }
        if(aux == NULL){
            aux = proceso;
            while(aux && strstr(aux->tarea.Descripcion,dato2) == NULL){
                aux = aux->Siguiente;
            }
            if(aux == NULL){
                puts("NO se encontro ninguna tarea.");
            }else{
                printf("ID tarea encontrada: %d\n",aux->tarea.TareaID);
                printf("Duracion: %d\n",aux->tarea.Duracion);
                printf("Descripcion: %s\n",aux->tarea.Descripcion);
                printf("Estado: REALIZADA\n");
            }
        }else
        {
            printf("ID tarea encontrada: %d\n",aux->tarea.TareaID);
            printf("Duracion: %d\n",aux->tarea.Duracion);
            printf("Descripcion: %s\n",aux->tarea.Descripcion);
            printf("Estado: EN PROCESO\n");
        }
    }else {
            printf("ID tarea encontrada: %d\n",aux->tarea.TareaID);
            printf("Duracion: %d\n",aux->tarea.Duracion);
            printf("Descripcion: %s\n",aux->tarea.Descripcion);
            printf("Estado: PENDIENTE\n");
    }
}

void eliminarId(struct Nodo **comienzo, struct Nodo **realizadas,int dato3){
    struct Nodo *aux = *comienzo;
    struct Nodo *auxAnt = NULL;
    struct Nodo *aux2 = *realizadas;
    struct Nodo *auxAnt2 = NULL;
    while (aux != NULL )
    {
        if (aux->tarea.TareaID == dato3)
        {
            if (auxAnt==NULL)
            {
                *comienzo = aux->Siguiente;
                free(aux);
                printf("Se elimino la tarea con id: %d\n", dato3);
            }else{
                auxAnt->Siguiente = aux->Siguiente;
                free(aux);
                printf("Se elimino la tarea con id: %d\n", dato3);
            }
        }
        auxAnt = aux;
        aux  = aux->Siguiente;
    }
    while (aux2 != NULL )
    {
        if (aux2->tarea.TareaID == dato3)
        {
            if (auxAnt2==NULL)
            {
                *realizadas = aux2->Siguiente;
                free(aux2);
                printf("Se elimino la tarea con id: %d\n", dato3);
            }else{
                auxAnt2->Siguiente = aux2->Siguiente;
                free(aux2);
                printf("Se elimino la tarea con id: %d\n", dato3);
            }
        }
        auxAnt = aux2;
        aux2  = aux2->Siguiente;
    }
}

void mostrarDatos(struct Nodo *comienzo, struct Nodo *realizadas,int dato4){
    int total=0;
    if (dato4 == 1)
    {
        struct Nodo *aux = comienzo;
        printf("===TAREAS PENDIENTES===\n");
        while (aux != NULL)
        {
            puts("-----------------");
            printf("ID: %d\n", aux->tarea.TareaID);
            printf("Descripcion: %s\n",aux->tarea.Descripcion);
            printf("Duracion: %d\n",aux->tarea.Duracion);
            total += aux->tarea.Duracion;
            aux = aux->Siguiente;
        }
        puts("-----------------");
        printf("Total de duracion: %d\n", total);
    }else if (dato4 == 2)
    {
        struct Nodo *aux = realizadas;
        printf("===TAREAS REALIZADAS===\n");
        while (aux != NULL)
        {
            puts("-----------------");
            printf("ID: %d\n", aux->tarea.TareaID);
            printf("Descripcion: %s\n",aux->tarea.Descripcion);
            printf("Duracion: %d\n",aux->tarea.Duracion);
            total += aux->tarea.Duracion;
            aux = aux->Siguiente;
        }
        puts("-----------------");
        printf("Total de duracion: %d\n", total);
    }     
}

void cargar(struct Nodo **comienzo){
    int duracion;
    char buffer[45];
    printf("Ingrese la descripcion de la tarea:");
    fflush(stdin);
    gets(buffer);
    printf("Ingrese la duracion: ");
    fflush(stdin);
    scanf("%d",&duracion);
    puts("=========");


        struct Nodo *aux = (struct Nodo*) malloc(sizeof(struct Nodo));
        aux->tarea.TareaID = 1+rand()%(51-1);
        aux->tarea.Duracion = duracion;

        aux->tarea.Descripcion = malloc(sizeof(struct Nodo)*strlen(buffer)+1);
        strcpy(aux->tarea.Descripcion,buffer);

        aux->Siguiente = NULL;
        
        if(*comienzo == NULL){
            *comienzo = aux;
        }else{
            aux->Siguiente = *comienzo;
            *comienzo = aux;
        }
}

struct Nodo *extraerTarea(struct Nodo **lista, int id){
    struct Nodo *aux = *lista;
    struct Nodo *auxAnt = *lista;

    while (aux && aux->tarea.TareaID != id)
    {
        auxAnt = aux;
        aux = aux->Siguiente;
    }
    if (aux == *lista)
    {
        *lista = aux->Siguiente;
    }else{
        auxAnt->Siguiente = aux->Siguiente;
    }
    return aux;
}

void mover(struct Nodo **comienzo, struct Nodo **realizadas, struct Nodo **proceso){
    int dat;
    struct Nodo *aux = *comienzo;
    struct Nodo *auxAnt = NULL;
    while(aux != NULL){
        puts("---------");
        printf("ID :%d\n",aux->tarea.TareaID);
        printf("Descripcion: %s\n",aux->tarea.Descripcion);
        printf("Duracion: %d\n",aux->tarea.Duracion);

        printf("Desea mover esta tarea?\n1- En proceso\n2- Realizada\n3- NO\n : ");
        fflush(stdin);
        scanf("%d",&dat);

        if (dat == 2)
        {
            auxAnt = aux;
            aux = aux->Siguiente;
            auxAnt = extraerTarea(comienzo,auxAnt->tarea.TareaID);

            auxAnt->Siguiente = *realizadas;
            *realizadas = auxAnt;
        }else if (dat == 1)
        {
            auxAnt = aux;
            aux = aux->Siguiente;
            auxAnt = extraerTarea(comienzo,auxAnt->tarea.TareaID);

            auxAnt->Siguiente = *proceso;
            *proceso = auxAnt;
        }else{
            aux = aux->Siguiente;
        }
    }
}
