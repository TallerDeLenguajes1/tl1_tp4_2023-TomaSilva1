#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef tarea;


void cargar(tarea **tareaCant, int cant);
void listar(tarea **tareaCant, int cant, tarea **tareaRealizada);
void mostrarRealizadas(tarea **tareaCant, int cant, tarea **tareaRealizada);
void mostrarPendientes(tarea **tareaCant, int cant, tarea **tareaRealizada);
void BuscaTareaPorId(tarea **tareaCant, int cant, tarea **tareaRealizada);
void BuscaTareaPorPalabra(tarea **tareaCant, int cant, tarea **tareaRealizada);

int main(){
int cant=0,aux;

printf("Ingrese el numero de tareas: ");
scanf("%d",&cant);
fflush(stdin);

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




cargar(tareaCant,cant);
listar(tareaCant,cant,tareaRealizada);
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



void cargar(tarea **tareaCant, int cant){
    srand(time(NULL));
    char* buffer = malloc(sizeof(tarea)*35);
    for (int i = 0; i < cant; i++)
    {
        tareaCant[i] = (tarea*) malloc(sizeof(tarea)*1);

        tareaCant[i]->TareaID = i+1;
        
        tareaCant[i]->Duracion = 10+rand()%101-10;

        printf("Ingrese la descripcion: ");
        gets(buffer);

        tareaCant[i]->Descripcion = (char*) malloc(strlen(buffer)+1);

        strcpy(tareaCant[i]->Descripcion, buffer);
    }
    
}

void listar(tarea **tareaCant, int cant, tarea **tareaRealizada){
    int aux;
    for (int i = 0; i < cant; i++)
    {
        printf("ID: %d\n", tareaCant[i]->TareaID);
        printf("Duracion: %d\n", tareaCant[i]->Duracion);
        printf("Descripcion: %s\n", tareaCant[i]->Descripcion);
        printf("Tarea Realizada? (1: SI , 2: NO): ");
        scanf("%d",&aux);
        if (aux == 1){
            tareaRealizada[i] = malloc(sizeof(tarea)*1);
            tareaRealizada[i]->TareaID = tareaCant[i]->TareaID;
            tareaRealizada[i]->Duracion = tareaCant[i]->Duracion;
            tareaRealizada[i]->Descripcion = malloc(sizeof(tarea)*30);
            tareaRealizada[i]->Descripcion = tareaCant[i]->Descripcion;
            tareaCant[i] = NULL;
        }
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