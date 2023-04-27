    for (int i = 0; i < cantTareas; i++)
    {
        free(tareasRealizadas[i]);
        free(tareasPendientes[i]);

    }
    
    free(tareasRealizadas);
    free(tareasPendientes);