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

int main(){
int cant=0;

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
    
    puts("====TAREAS PENDIENTES====");
    for (int j = 0; j < cant; j++)
    {
        printf("ID tarea pendiente: %d\n", tareaCant[j]->TareaID);
        printf("Duracion de tarea pendiente: %d\n", tareaCant[j]->Duracion);
        printf("Descripcion: %s\n", tareaCant[j]->Descripcion);
        puts("========================");
    }
    
    
}