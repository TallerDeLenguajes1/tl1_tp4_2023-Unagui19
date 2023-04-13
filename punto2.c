#include <stdio.h>
#include <stdlib.h>

struct  Tarea
{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion;//entre 10-100
}typedef Tarea;


int main()
{

    int cantTareas;


    printf("\t=====WENASSS=====\n\r");
    printf("Ingrese cantidad de tareas a realizar \t");
    scanf("%d",&cantTareas);

    Tarea **tareas=NULL;

        tareas=(Tarea**) malloc(sizeof(Tarea*) *cantTareas);


    return 0;
}