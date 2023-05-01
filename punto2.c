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


struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} typedef Nodo;

Nodo* crearListaVacia();
Nodo* crearTareas(int id);
void insertarTareas(Nodo **start,int id);
void *mostrarTareas(Nodo *start);
void cargarLista(Nodo);
// void controlDeTareas(Tarea** tareasPendientes,Tarea** tareasRealizadas);
// void mostrarTareasRealizadas(Tarea** tareasRealizadas);
// void mostrarTareasPendientes(Tarea** tareasPendientes);
// void BuscarTareaPorID(Tarea** tareasPendientes, Tarea** tareasRealizadas);
// void BuscarTareaPorPalabra(Tarea** tareasPendientes, Tarea** tareasRealizadas);

int main()
{
    srand(time(NULL));
    int seguir,id=0;
    Nodo  *tareasPendientes,*tareasRealizadas; //serian  las cabeceras
    tareasPendientes=crearListaVacia();
    tareasRealizadas=crearListaVacia();

    printf("\t=====WENASSS=====\n\r");

    printf("\nDesea ingresar una nueva tarea?( 1: SI    2:NO) \t");
    scanf("%d",&seguir);
    fflush(stdin);   
    while (seguir!=1 && seguir!=2)
    {
        puts("Valor incorrecto, intente nuevamente");
        printf("Desea ingresar una nueva tarea?( 1: SI    2:NO) \t");
        scanf("%d",&seguir);
        fflush(stdin);
    }

    while (seguir==1)
    {
        id++;
        insertarTareas(&tareasPendientes, id);
        printf("\nDesea ingresar una nueva tarea?( 1: SI    2:NO) \t");
        scanf("%d",&seguir);
        fflush(stdin);
        while (seguir!=1 && seguir!=2)
        {
            puts("Valor incorrecto, intente nuevamente");
            printf("Desea ingresar una nueva tarea?( 1: SI    2:NO) \t");
            scanf("%d",&seguir);
            fflush(stdin);
        }
    }

    //MOSTRAR TAREAS
    mostrarTareas(tareasPendientes);

    
    free(tareasRealizadas);
    free(tareasPendientes);

    return 0;
}

//CREAR LA CABECERA
Nodo* crearListaVacia()
{
    return NULL;
}

//CARGAR TAREAS

Nodo* crearTareas(int id)
{
    Nodo *NuevoNodo = (Nodo*) malloc(sizeof(Nodo));
    Tarea *tareas= (Tarea*) malloc (sizeof(Tarea));
    char* buff=(char*)malloc(sizeof(char)*500);
    NuevoNodo->T.TareaID=id;
    puts("Descripcion de la tarea a realizar: \t");
    gets(buff);
    NuevoNodo->T.Descripcion=(char*)malloc(sizeof(char)*(strlen(buff)+1));
    strcpy(NuevoNodo->T.Descripcion,buff);
    NuevoNodo->T.Duracion=10+rand()%91;
    NuevoNodo->Siguiente=NULL;
    free(buff);
    return(NuevoNodo);  
}

void insertarTareas(Nodo**start, int id)
{
    Nodo *nuevoNodo=crearTareas(id);
    nuevoNodo->Siguiente=*start;
    *start=nuevoNodo;
}

//MOSTRAR TAREAS ORDENADAS ASCENDENTEMENTE SEGUN SU NUMERO DE ID
void *mostrarTareas(Nodo* start)
{
    int i=0;
    Tarea **direcciones=(Tarea**) malloc (sizeof(Tarea*));
    Nodo* Aux=start;
    printf("\n======Tareas=====\n");
    while (Aux)
    {    
        direcciones[i]=(Tarea*) malloc(sizeof(Tarea));
        direcciones[i]->TareaID=Aux->T.TareaID;
        direcciones[i]->Duracion= Aux->T.Duracion;
        direcciones[i]->Descripcion=(char*) malloc(sizeof(Aux->T.Descripcion));
        strcpy(direcciones[i]->Descripcion,Aux->T.Descripcion);
        Aux=Aux->Siguiente;
        i++;
    }
    for (int j = i-1; j >= 0 ; j--)
    {
        printf("\n---Tarea %d\n",direcciones[j]->TareaID);
        printf("Descripcion %s\n",direcciones[j]->Descripcion);
        printf("Duracion: %d\n",direcciones[j]->Duracion);
    }

    for (int j = 0; j < i; j++)
    {
        free(direcciones[j]->Descripcion);
    }
    
    free(direcciones);
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
void BuscarTareaPorID(Tarea** tareasPendientes, Tarea** tareasRealizadas, int cantTareas)
{
    int id, bandera=0;
    printf("\t=======Busqueda de tareas=======\n");
    printf("Numero de ID buscado: ");
    scanf("%d",&id);
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareasPendientes[i] && tareasPendientes[i]->TareaID==id)
        {
            printf("---Tarea %d: \n",id);
            printf("Descripcion %s\n",tareasPendientes[i]->Descripcion);
            printf("Duracion: %d\n",tareasPendientes[i]->Duracion);
            printf("Estado: Pendiente\n");
            bandera=1;

        }
        else if (tareasRealizadas[i] && tareasRealizadas[i]->TareaID==id)
        {
            printf("---Tarea %d: \n",id);
            printf("Descripcion %s\n",tareasRealizadas[i]->Descripcion);
            printf("Duracion: %d\n",tareasRealizadas[i]->Duracion);
            printf("Estado: Realizada\n");
            bandera=1;
        }
        
    }
    if (bandera==0)
    {
        printf("No existe ninguna tarea asociada a ese id");
    }
    
}

void BuscarTareaPorPalabra(Tarea** tareasPendientes, Tarea** tareasRealizadas, int cantTareas)
{
    int bandera=0;
    char *palabra=(char*) malloc(sizeof(char)*50);

    printf("\n\t=======Busqueda de tareas=======\n");
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