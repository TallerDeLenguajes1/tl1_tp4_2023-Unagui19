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


void cargarTareas(Tarea **nodo, int cantTareas, char* buff);
// void cargarTareas(Tarea **nodo, int cantTareas);

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
    free(buff);

    //MOSTRAR TAREAS
    int completa,cont=0,cont2=0;

    printf("\n======Tareas=====\n");
    for (int i = 0; i < cantTareas; i++)
    {
        printf("\n---Tarea %d\n",tareasPendientes[i]->TareaID);
        printf("Descripcion %s\n",tareasPendientes[i]->Descripcion);
        printf("Duracion: %d\n",tareasPendientes[i]->Duracion);

        printf("La tarea ya fue completada?\n 1-SI\t 2-NO\n\r");
        scanf("%d",&completa);
        while (completa!=2 && completa!=1)
        {
            puts("Valor incorrecto, intente nuevamente");
            printf("\nLa tarea ya fue completada?\n 1-SI\t 2-NO\n\r");
            scanf("%d",&completa);
        }
        
        if (completa==1)
        {
            tareasRealizadas[i]= (Tarea*) malloc (sizeof(Tarea));
            tareasRealizadas[i]=tareasPendientes[i];
            tareasPendientes[i]=NULL;
        }
        else
        {
            tareasRealizadas[i]=NULL;
        }

    }

    printf("\n======Tareas Realizadas=====\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareasRealizadas[i])
        {
            printf("\n---Tarea %d\n",tareasRealizadas[i]->TareaID);
            printf("Descripcion %s\n",tareasRealizadas[i]->Descripcion);
            printf("Duracion: %d\n",tareasRealizadas[i]->Duracion);
        }
    }

    printf("\n======Tareas Pendientes=====\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareasPendientes[i])
        {
            printf("\n---Tarea %d\n",tareasPendientes[i]->TareaID);
            printf("Descripcion %s\n",tareasPendientes[i]->Descripcion);
            printf("Duracion: %d\n",tareasPendientes[i]->Duracion);
        }        
    }

//liberar memoria
    for (int i = 0; i < cantTareas; i++)
    {
        free(tareasPendientes[i]->Descripcion);
        free(tareasRealizadas[i]);
        free(tareasPendientes[i]);
    }
    
    free(tareasRealizadas);
    free(tareasPendientes);

    return 0;
}


// tareaRealiz(Tarea *nodo,int i)
// {
//     int i;
//     char* buff=(char*)malloc(sizeof(char)*500);


// }
// void cargarTareas(Tarea**nodo, int cantTareas,char* buff){
//     char* buff=(char*)malloc(sizeof(char)*500);
//     for (int i = 0; i < cantTareas; i++)
//     {
        
//         nodo[i]=(Tarea*) malloc(sizeof(Tarea) * cantTareas);
//         nodo[i]->TareaID=i+1;
//         puts("Descripcion de la tarea a realizar: \t");
//         gets(buff);
//         nodo[i]->Descripcion=(char*)malloc(sizeof(char)*(strlen(buff)+1));
//         strcpy(nodo[i]->Descripcion,buff);
//         nodo[i]->Duracion=10+rand()%91;
//     }
//     free(buff);
// }

