#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct  Tarea
{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion;//entre 10-100
}typedef Tarea;


Tarea cargarTareas();

int main()
{
    srand(time(NULL));
    int cantTareas;


    printf("\t=====WENASSS=====\n\r");
    printf("Ingrese cantidad de tareas a realizar \t");
    scanf("%d",&cantTareas);
    fflush(stdin);
    Tarea **tareasPendientes, **tareasRealizadas;

    tareasPendientes=(Tarea**) malloc(sizeof(Tarea*) *cantTareas);
    tareasRealizadas=(Tarea**) malloc(sizeof(Tarea*) *cantTareas);
    
    //inicizlizo los punteros dentro del doble puntero
    for (int i = 0; i < cantTareas; i++)
    {
        tareasPendientes[i]=NULL;
    }

    //cargar las tareas
    char* buff=(char*)malloc(sizeof(char)*500);

    for (int i = 0; i < cantTareas; i++)
    {
        
        tareasPendientes[i]=(Tarea*) malloc(sizeof(Tarea) * cantTareas);
        tareasPendientes[i]->TareaID=i+1;
        puts("Descripcion de la tarea a realizar: \t");
        gets(buff);
        tareasPendientes[i]->Descripcion=(char*)malloc(sizeof(char)*(strlen(buff)+1));
        strcpy(tareasPendientes[i]->Descripcion,buff);
        tareasPendientes[i]->Duracion=10+rand()%91;
    }

    //MOSTRAR

    printf("======Tareas=====\n\n");
    for (int i = 0; i < cantTareas; i++)
    {
        printf("---Tarea %d\n",tareasPendientes[i]->TareaID);
        printf("Descripcion %s\n",tareasPendientes[i]->Descripcion);
        printf("Duracion: %d\n",tareasPendientes[i]->Duracion);

    }
    
        

    return 0;
}