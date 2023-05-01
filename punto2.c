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
void mostrarTareas(Nodo *start);
void cargarLista(Nodo);
void controlDeTareas(Nodo **tareasPendientes,Nodo **tareasRealizadas);
void mostrarTareasRealizadas(Nodo* tareasRealizadas);
void mostrarTareasPendientes(Nodo* tareasPendientes);
void BuscarTareaPorID(Nodo* tareasPendientes, Nodo* tareasRealizadas);
void BuscarTareaPorPalabra(Nodo* tareasPendientes, Nodo* tareasRealizadas);

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

    //Controles de tareas realizadas y pendientes
    controlDeTareas(&tareasPendientes,&tareasRealizadas);
    mostrarTareasRealizadas(tareasRealizadas);
    mostrarTareasPendientes(tareasPendientes);
    
    printf("\n======BUSQUEDA=====\n");
    int opcion;
    printf("\nBusqueda por: \n\r");
    printf("\n1. ID \n\r");
    printf("\n2. Palabra clave \n\n\r");
    printf("Ingrese la opcion deseada:");
    scanf("%d",&opcion);
    
    while (opcion!=2 && opcion!=1)
        {
            printf("\n\nBusqueda por: \n\r");
            printf("\n2. ID \n\r");
            printf("\n2. Palabra clave \n\n\r");
            printf("Ingrese la opcion deseada:");
            scanf("%d",&opcion);
        }
    printf("\n");

    if (opcion==1)
    {
        BuscarTareaPorID(tareasPendientes, tareasRealizadas);
    }
    else
    {
        BuscarTareaPorPalabra(tareasPendientes, tareasRealizadas);
    }

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

//MOSTRAR TAREAS 
void mostrarTareas(Nodo* start)
{
    Nodo* aux=start;
    printf("\n======Tareas=====\n");
    while (aux)
    {    
        printf("\n---Tarea %d\n",aux->T.TareaID);
        printf("Descripcion %s\n",aux->T.Descripcion);
        printf("Duracion: %d\n",aux->T.Duracion);
        aux=aux->Siguiente;
    }
}

//CONTROL DE TAREAS
void controlDeTareas(Nodo** tareasPendientes,Nodo** tareasRealizadas) 
{
    int completa;
    Nodo* aux=*tareasPendientes;
    Nodo* auxAnt=*tareasPendientes;

    printf("\n=====Control de tareas=====\n");

    while (aux)
    {
        printf("La tarea %d ya fue completada?\n 1-SI\t 2-NO\n\r",aux->T.TareaID);
        scanf("%d",&completa);
        fflush(stdin);
        while (completa!=2 && completa!=1)
        {
            puts("Valor incorrecto, intente nuevamente");
            printf("La tarea %d ya fue completada?\n 1-SI\t 2-NO\n\r",aux->T.TareaID);
            scanf("%d",&completa);
        }
        
        if (completa==1)
        {
            if (aux==*tareasPendientes)
            {
                //saco de las pendientes y redirijo el puntero
                *tareasPendientes=aux->Siguiente;
                auxAnt=aux->Siguiente;
                //pongo el nodo quitado en realizadas
                // auxAnt->Siguiente=aux->Siguiente;
                aux->Siguiente=*tareasRealizadas;
                *tareasRealizadas=aux;
                aux=auxAnt;
            }   
            else
            {
                auxAnt=aux;
                aux->Siguiente=*tareasRealizadas;
                *tareasRealizadas=aux;
                aux=aux->Siguiente;
                auxAnt->Siguiente=aux->Siguiente;
                
            }
        }
        else
        {
            auxAnt=aux;
            aux=aux->Siguiente;
        }
    }
}

void mostrarTareasRealizadas(Nodo* tareasRealizadas)
{
    Nodo *aux=tareasRealizadas;
    printf("\n======Tareas Realizadas=====\n");
    while(aux)
    {
        printf("\n---Tarea %d\n",aux->T.TareaID);
        printf("Descripcion %s\n",aux->T.Descripcion);
        printf("Duracion: %d\n",aux->T.Duracion);
        aux=aux->Siguiente;
    }
}

void mostrarTareasPendientes(Nodo* tareasPendientes)
{
    Nodo *aux=tareasPendientes;
    printf("\n======Tareas Pendientes=====\n");
    while(aux)
    {
        printf("\n---Tarea %d\n",aux->T.TareaID);
        printf("Descripcion %s\n",aux->T.Descripcion);
        printf("Duracion: %d\n",aux->T.Duracion);
        aux=aux->Siguiente;
    }
}

void BuscarTareaPorID(Nodo* tareasPendientes, Nodo* tareasRealizadas)
{
    int id;
    Nodo *auxP=tareasPendientes;
    Nodo *auxR=tareasRealizadas;
    printf("Numero de ID buscado: ");
    scanf("%d",&id);
    while(auxP && auxP->T.TareaID!=id)
    {
        auxP=auxP->Siguiente;
    }

    if (auxP)
    {
        printf("\n---Tarea %d: \n", auxP->T.TareaID);
        printf("Descripcion %s\n",auxP->T.Descripcion);
        printf("Duracion: %d\n",auxP->T.Duracion);
        printf("Estado: Pendiente\n");
    }
    else
    {
        while(auxR && auxR->T.TareaID!=id)
        {
            auxR=auxR->Siguiente;
        }
        if (auxR)
        {
            printf("\n---Tarea %d: \n", auxR->T.TareaID);
            printf("Descripcion %s\n",auxR->T.Descripcion);
            printf("Duracion: %d\n",auxR->T.Duracion);
            printf("Estado: Realizado\n");
        }
        else
        {
            printf("\nNo existe ninguna tarea asociada a ese id");  
        }
    }
}

void BuscarTareaPorPalabra(Nodo* tareasPendientes, Nodo* tareasRealizadas)
{
    int bandera=0;
    Nodo *auxP=tareasPendientes;
    Nodo *auxR=tareasRealizadas;
    char *palabra=(char*) malloc(sizeof(char)*50);

    printf("\n\t=======Busqueda por palabra clave=======\n");
    printf("Palabra clave buscada: ");
    scanf("%s",palabra);
    printf("\n");

    while(auxP && !strstr(auxP->T.Descripcion,palabra))
    {
        auxP=auxP->Siguiente;
    }

    while(auxR && !strstr(auxR->T.Descripcion,palabra))
    {
        auxR=auxR->Siguiente;
    }

    if (auxP)
    {
        printf("\n---Tarea %d: \n", auxP->T.TareaID);
        printf("Descripcion %s\n",auxP->T.Descripcion);
        printf("Duracion: %d\n",auxP->T.Duracion);
        printf("Estado: Pendiente\n");
        bandera=1;
    }
    else
    {
        bandera=0;
    }

    if (auxR)
    {
        printf("\n---Tarea %d: \n", auxR->T.TareaID);
        printf("Descripcion %s\n",auxR->T.Descripcion);
        printf("Duracion: %d\n",auxR->T.Duracion);
        printf("Estado: Realizado\n");
        bandera=1;
    }
    else
    {
        bandera=0;
    }

    if (bandera==0)
    {
            printf("\nNo existe ninguna tarea asociada a esa palabra");
    }
    
}

    // for (int i = 0; i < cantTareas; i++)
    // {
    //     if (tareasPendientes[i] && strstr(tareasPendientes[i]->Descripcion,palabra))
    //     {
    //         printf("---Tarea %d: \n",tareasPendientes[i]->TareaID);
    //         printf("Descripcion %s\n",tareasPendientes[i]->Descripcion);
    //         printf("Duracion: %d\n",tareasPendientes[i]->Duracion);
    //         printf("Estado: Pendiente\n");
    //         bandera=1;

    //     }
    //     else if (tareasRealizadas[i] && strstr(tareasRealizadas[i]->Descripcion,palabra))
    //     {
    //         printf("---Tarea %d: \n",tareasRealizadas[i]->TareaID);
    //         printf("Descripcion %s\n",tareasRealizadas[i]->Descripcion);
    //         printf("Duracion: %d\n",tareasRealizadas[i]->Duracion);
    //         printf("Estado: Realizada\n");
    //         bandera=1;
    //     }


    // }
    // if (bandera==0)
    // {
    //     printf("No existe ninguna tarea asociada a esa palabra\n");
    // }
