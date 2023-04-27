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
    struct Tarea tarea;
    struct Nodo *Siguiente;
};

void mostrarRealizadas(tarea **tareaCant, int cant, tarea **tareaRealizada);
void mostrarPendientes(tarea **tareaCant, int cant, tarea **tareaRealizada);
void BuscaTareaPorId(tarea **tareaCant, int cant, tarea **tareaRealizada);
void BuscaTareaPorPalabra(tarea **tareaCant, int cant, tarea **tareaRealizada);
void subir(struct Nodo **headRef);

int main(){
int cant=0,aux,stop;

printf("Ingrese el numero de tareas: ");
scanf("%d",&cant);
fflush(stdin);

struct Nodo *head = NULL;
tarea **tareaCant = malloc(sizeof(tarea*)*cant);
tarea **tareaRealizada = malloc(sizeof(tarea)*cant);

for (int j = 0; j < cant; j++)
{
    tareaRealizada[j] = NULL;

}

for (int i = 0; i < cant; i++)
{
    tareaCant[i] = NULL;
}




while (stop != 2)
{
    subir(&head);
    printf("Desea agregar otra tarea(1) o terminar(2) ?");
    fflush(stdin);
    scanf("%d",&stop);
}

mostrarRealizadas(tareaCant,cant,tareaRealizada);
mostrarPendientes(tareaCant,cant,tareaRealizada);

puts("-----Interfaz de usuario-----");
printf("Desea buscar una tarea por id(1) o palabra clabe(2)? :");
fflush(stdin);
scanf("%d",&aux);

if (aux == 1)
{
    BuscaTareaPorId(tareaCant,cant,tareaRealizada);
} else {
    BuscaTareaPorPalabra(tareaCant,cant,tareaRealizada);
}


return 0;
}

void subir(struct Nodo **comienzo) {
    struct Nodo *nuevo = (struct Nodo *) malloc(sizeof(struct Nodo));

    char buffer[40];

    nuevo->tarea.Duracion = 10 + rand() % 101 - 10;
    nuevo->tarea.TareaID = 1;
    printf("Ingrese la descripcion del trabajo: ");
    fflush(stdin);
    gets(buffer);
    nuevo->tarea.Descripcion = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(nuevo->tarea.Descripcion, buffer);

    nuevo->Siguiente = NULL;

    if (*comienzo == NULL) {
        *comienzo = nuevo;
    } else {
        struct Nodo *actual = *comienzo;
        while (actual->Siguiente != NULL) {
            actual = actual->Siguiente;
        }
        actual->Siguiente = nuevo;
    }
}

void mostrarRealizadas(tarea **tareaCant, int cant, tarea **tareaRealizada){
    
    puts("====TAREAS REALIZADAS====");
    for (int i = 0; i < cant; i++)
    {
        if (tareaRealizada[i] != NULL)
        {
            printf("ID tarea realizada: %d\n", tareaRealizada[i]->TareaID);
            printf("Duracion de tarea realizada: %d\n", tareaRealizada[i]->Duracion);
            printf("Descripcion: %s\n", tareaRealizada[i]->Descripcion);
            puts("========================");
        }
    }
    
}

void mostrarPendientes(tarea **tareaCant, int cant, tarea **tareaRealizada){
    
    puts("====TAREAS PENDIENTES====");
    for (int j = 0; j < cant; j++)
    {
        if (tareaCant[j] != NULL)
        {
            printf("ID tarea pendiente: %d\n", tareaCant[j]->TareaID);
            printf("Duracion de tarea pendiente: %d\n", tareaCant[j]->Duracion);
            printf("Descripcion: %s\n", tareaCant[j]->Descripcion);
            puts("========================");
        }  
    }
    fflush(stdin);
}

void BuscaTareaPorId(tarea **tareaCant, int cant, tarea **tareaRealizada){
    fflush(stdin);
    int aux;
    printf("Ingrese el id de la tarea a buscar: ");
    fflush(stdin);
    scanf("%d", &aux);

    int encont = 0;
    for (int i = 0; i < cant; i++) {
        if (tareaCant[i] != NULL)
        {
            if (aux == tareaCant[i]->TareaID) {
                encont = 1;
                printf("BUSQUEDA: \n");
                printf("Descripcion: %s\n", tareaCant[i]->Descripcion);
                printf("Duracion: %d\n", tareaCant[i]->Duracion);
                printf("Estado: PENDIENTE\n");
            }
        }
        if (tareaRealizada[i] != NULL)
        {
            if (aux == tareaRealizada[i]->TareaID) {
                encont = 1;
                printf("BUSQUEDA: \n");
                printf("Descripcion: %s\n", tareaRealizada[i]->Descripcion);
                printf("Duracion: %d\n", tareaRealizada[i]->Duracion);
                printf("Estado: REALIZADA\n");
            }
        }   
    }
    if (!encont) {
        printf("No se encontro ninguna tarea con esa id\n");
    }
}

void BuscaTareaPorPalabra(tarea **tareaCant, int cant, tarea **tareaRealizada){
    char aux[35],*resultado;
    
    printf("Ingrese la palabra clabe: ");
    fflush(stdin);
    gets(aux);

    for (int i = 0; i < cant; i++)
    {
        if (tareaCant[i] != NULL)
        {
            if (strstr(tareaCant[i]->Descripcion,aux))
            {
                puts("BUSQUEDA: ");
                printf("descripcion: %s\n", tareaCant[i]->Descripcion);
                printf("Duracion: %d\n", tareaCant[i]->Duracion);
                printf("Estado: PENDIENTE");
            }
        }
        
        if (tareaRealizada[i] != NULL)
        {
            if(strstr(tareaRealizada[i]->Descripcion,aux))
            {
                puts("BUSQUEDA: ");
                printf("descripcion: %s\n", tareaRealizada[i]->Descripcion);
                printf("Duracion: %d\n", tareaRealizada[i]->Duracion);
                printf("Estado: REALIZADA");
            }
        }
    }
}
