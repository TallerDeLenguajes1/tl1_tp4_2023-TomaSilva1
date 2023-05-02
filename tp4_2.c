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
void listar(struct Nodo **comienzo, struct Nodo **realizadas);
void mostraRea(struct Nodo *realizadas);
void mostrarPen(struct Nodo *comienzo);
void buscar1(struct Nodo *comienzo, struct Nodo *realizadas, int dato);
void buscar2(struct Nodo *comienzo, struct Nodo *realizadas, char *dato2);

int main(){
int cant=0,aux,stop,dato,aux2;
char dato2[35];

struct Nodo *comienzo = NULL;
struct Nodo *realizadas = NULL;

while (stop != 2)
{
    subir(&comienzo);
    cant++;
    printf("Agregar otra tarea(1), Parar(2): ");
    scanf("%d",&stop);
}


fflush(stdin);
listar(&comienzo,&realizadas);
fflush(stdin);
mostraRea(realizadas);
fflush(stdin);
mostrarPen(comienzo);

puts("===INTERFAZ DE USUARIO===");
printf("Buscar tarea por ID(1), \nBuscar tarea por palabra(2)\nParar(3)");
scanf("%d",&aux2);
switch (aux2)
{
case 1:
    printf("Ingrese el id de la tarea a buscar: ");
    scanf("%d",&dato);
    buscar1(comienzo,realizadas,dato);
    break;
    case 2:
    printf("Ingrese la palabra de la tarea a buscar: ");
    fflush(stdin);
    gets(dato2);
    buscar2(comienzo,realizadas,dato2);
    break;

default:
    break;
}
    

return 0;
}

void subir(struct Nodo **comienzo) {
    struct Nodo *nuevo = (struct Nodo*) malloc(sizeof(struct Nodo));

    char buffer[40];

    nuevo->tarea.Duracion = 10 + rand() % 101 - 10;
    nuevo->tarea.TareaID = 1 + rand() % 31 - 1;
    printf("Ingrese la descripcion del trabajo: ");
    fflush(stdin);
    gets(buffer);
    nuevo->tarea.Descripcion = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(nuevo->tarea.Descripcion, buffer);

    nuevo->Siguiente = NULL;

    if (*comienzo == NULL) {
        *comienzo = nuevo;
    } else {

        nuevo->Siguiente = *comienzo;
        *comienzo = nuevo;

        // struct Nodo *actual = *comienzo;
        // while (actual->Siguiente != NULL) {
        //     actual = actual->Siguiente;
        // }
        // actual->Siguiente = nuevo;
    }
}

void listar(struct Nodo **comienzo, struct Nodo **realizadas){
    int aux;
    struct Nodo *zap = *comienzo;
    struct Nodo *zapAnt= NULL;
    while (zap != NULL)
    {
        puts("-----------------");
        printf("ID de la tarea: %d\n", zap->tarea.TareaID);
        printf("Descripcion: %s\n", zap->tarea.Descripcion);
        printf("Duracion: %d\n", zap->tarea.Duracion);
        printf("Tarea realizada? 1(SI) , 2(NO) : ");
        fflush(stdin);
        scanf("%d",&aux);
        if (aux == 1)
        {
            struct Nodo *rea = (struct Nodo*) malloc(sizeof(struct Nodo));
            rea->tarea.TareaID = zap->tarea.TareaID;
            rea->tarea.Duracion = zap->tarea.Duracion;
            rea->tarea.Descripcion = (char*) malloc(sizeof(char)*(strlen(zap->tarea.Descripcion)+1));
            strcpy(rea->tarea.Descripcion,zap->tarea.Descripcion);
            rea->Siguiente = NULL;
            
            if(*realizadas == NULL){
                *realizadas = rea;
            }else{
                rea->Siguiente = *realizadas;
                *realizadas = rea;
            }

            if(zapAnt != NULL){
                zapAnt->Siguiente = zap->Siguiente;
            }else{
                *comienzo = zap->Siguiente;
            }
            
            struct Nodo *aux = zap;
            zap = zap->Siguiente;
            free(aux);
            continue;
        }
            zapAnt = zap;
            zap = zap->Siguiente;
    }
}

void mostraRea(struct Nodo *realizadas){
    struct Nodo *aux = realizadas;
        puts("=====REALIZADAS=====");
    while(aux){
        printf("Id tarea: %d\n", aux->tarea.TareaID);
        printf("Duracion: %d\n", aux->tarea.Duracion);
        printf("Descripcion: %s\n", aux->tarea.Descripcion);
        aux = aux->Siguiente;
    }
}

void mostrarPen(struct Nodo *comienzo){
    struct Nodo *pen = comienzo;
        puts("=====PENDIENTES=====");
    while(pen){
        printf("Id tarea : %d\n", pen->tarea.TareaID);
        printf("Duracion: %d\n", pen->tarea.Duracion);
        printf("Descripcion: %s\n", pen->tarea.Descripcion);
        pen = pen->Siguiente;
    }
}

void buscar1(struct Nodo *comienzo, struct Nodo *realizadas, int dato){
    struct Nodo *aux = comienzo;
    struct Nodo *aux2 = realizadas;

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
}

void buscar2(struct Nodo *comienzo, struct Nodo *realizadas, char *dato2){
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
            printf("No se encontro ninguna tarea.\n");
        }else
        {
            printf("ID tarea encontrada: %d\n",aux->tarea.TareaID);
            printf("Duracion: %d\n",aux->tarea.Duracion);
            printf("Descripcion: %s\n",aux->tarea.Descripcion);
            printf("Estado: REALIZADA\n");
        }
    }else {
            printf("ID tarea encontrada: %d\n",aux->tarea.TareaID);
            printf("Duracion: %d\n",aux->tarea.Duracion);
            printf("Descripcion: %s\n",aux->tarea.Descripcion);
            printf("Estado: PENDIENTE\n");
    }
}