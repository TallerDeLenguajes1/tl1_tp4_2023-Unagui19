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

void cargarTareas(Tarea **nodo, int cantTareas);
void mostrarTareas(Tarea **nodo, int cantTareas);
void controlDeTareas(Tarea** tareasPendientes,Tarea** tareasRealizadas, int cantTareas);
void mostrarTareasRealizadas(Tarea** tareasRealizadas, int cantTareas);
void mostrarTareasPendientes(Tarea** tareasPendientes, int cantTareas);
void BuscarTarea(Tarea** tareasPendientes, Tarea** tareasRealizadas, int cantTareas);

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

    cargarTareas(tareasPendientes, cantTareas);

//MOSTRAR TAREAS
    mostrarTareas(tareasPendientes, cantTareas);

//CONTROL DE TAREAS
    controlDeTareas( tareasPendientes, tareasRealizadas, cantTareas);
    
//Mostrar resultado de control de tareas
    mostrarTareasRealizadas( tareasRealizadas, cantTareas);
    mostrarTareasPendientes( tareasPendientes, cantTareas);

//funcion buscar

    BuscarTarea( tareasPendientes, tareasRealizadas, cantTareas);
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



//CARGAR TAREAS
void cargarTareas(Tarea**nodo, int cantTareas){
    char* buff=(char*)malloc(sizeof(char)*500);
    for (int i = 0; i < cantTareas; i++)
    {
        
        nodo[i]=(Tarea*) malloc(sizeof(Tarea) * cantTareas);
        nodo[i]->TareaID=i+1;
        puts("Descripcion de la tarea a realizar: \t");
        gets(buff);
        nodo[i]->Descripcion=(char*)malloc(sizeof(char)*(strlen(buff)+1));
        strcpy(nodo[i]->Descripcion,buff);
        nodo[i]->Duracion=10+rand()%91;
    }
    free(buff);
}

//MOSTRAR TAREAS
void mostrarTareas(Tarea** tareasPendientes, int cantTareas)
{
    printf("\n======Tareas=====\n");
    for (int i = 0; i < cantTareas; i++)
    {
        printf("\n---Tarea %d\n",tareasPendientes[i]->TareaID);
        printf("Descripcion %s\n",tareasPendientes[i]->Descripcion);
        printf("Duracion: %d\n",tareasPendientes[i]->Duracion);
    }
}

//CONTROL DE TAREAS
void controlDeTareas(Tarea** tareasPendientes,Tarea** tareasRealizadas, int cantTareas)
{
    int completa;
    printf("\n=====Control de tareas=====\n");
    for (int i = 0; i < cantTareas; i++)
    {
        printf("La tarea %d ya fue completada?\n 1-SI\t 2-NO\n\r",tareasPendientes[i]->TareaID);
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
}

void mostrarTareasRealizadas(Tarea** tareasRealizadas, int cantTareas)
{
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
}
void mostrarTareasPendientes(Tarea** tareasPendientes, int cantTareas)
{
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
}

//Funcion buscar tarea

void BuscarTarea(Tarea** tareasPendientes, Tarea** tareasRealizadas, int cantTareas)
{
    int bandera=0;
    char *palabra=(char*) malloc(sizeof(char)*50);

    printf("\t=======Busqueda de tareas=======\n");
    printf("Palabra clave buscada: ");
    scanf("%s",palabra);
    printf("\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareasPendientes[i] && strstr(tareasPendientes[i]->Descripcion,palabra))
        {
            printf("---Tarea %d: \n",tareasPendientes[i]->TareaID);
            printf("Descripcion %s\n",tareasPendientes[i]->Descripcion);
            printf("Duracion: %d\n",tareasPendientes[i]->Duracion);
            printf("Estado: Pendiente\n");
            bandera=1;

        }
        else if (tareasRealizadas[i] && strstr(tareasRealizadas[i]->Descripcion,palabra))
        {
            printf("---Tarea %d: \n",tareasRealizadas[i]->TareaID);
            printf("Descripcion %s\n",tareasRealizadas[i]->Descripcion);
            printf("Duracion: %d\n",tareasRealizadas[i]->Duracion);
            printf("Estado: Realizada\n");
            bandera=1;
        }


    }
    if (bandera==0)
    {
        printf("No existe ninguna tarea asociada a esa palabra\n");
    }
}