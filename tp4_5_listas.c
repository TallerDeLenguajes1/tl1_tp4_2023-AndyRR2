#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
};

struct Nodo{
    struct Tarea T;
    struct Nodo* Siguiente;
};
typedef struct Nodo* Lista;

void cargarTarea(struct Tarea *tarea,int num);
Lista insertarNodo(Lista ListaP, struct Tarea *tarea);
void mostrarLista(Lista lista);
Lista borrarNodo(Lista lista, int ID);
Lista buscarPorID(Lista lista,int ID);
Lista buscarPorPal(Lista lista,char *palabra);
void MostrarDatos(Lista lista);
int menu(int opcion);

int main(){
    int estado, opcion, i=0, donde, ID;
    char *palabra;
    Lista TareasEP=NULL, ListaP=NULL, ListaR=NULL, porID=NULL, porPal=NULL, aBorrar=NULL, selec=NULL;
    Lista aux;//nueva lista para recorrer ListaP
    struct Tarea *tarea;
    tarea=(struct Tarea *)malloc(sizeof(struct Tarea));

opcion=menu(opcion);
while (opcion!=11){
    switch (opcion)
    {
        case 1:
            printf("Tarea #%d: \n",i+1);
            cargarTarea(tarea,i);//crea una tarea individual de tipo struct Tarea
            ListaP=insertarNodo(ListaP,tarea);//inserta la tarea en la lista tipo Lista
            i++;
            printf("Tareas Cargadas: \n");
            mostrarLista(ListaP);//muestra la lista por conexiones entre nodos
            printf("\n");
        break;
        case 2:
            aux=ListaP;
            while (aux!=NULL){
                printf("Tarea #ID: %d:\n",aux->T.TareaID);
                printf("1-Realizar, 2-Procesar, 0-Pendiente: \n"),
                scanf("%d",&estado);
                fflush(stdin);
                if (estado==1){
                    *tarea=aux->T;//apunta a la tarea del nodo actual
                    ListaR=insertarNodo(ListaR,tarea);//inserta la tarea en la lista de realizadas
                    ListaP=borrarNodo(ListaP,aux->T.TareaID);//borra la tarea de la lista de pendientes
                }else if(estado==2){
                    *tarea=aux->T;
                    TareasEP=insertarNodo(TareasEP,tarea);
                    ListaP=borrarNodo(ListaP,aux->T.TareaID);
                }
                aux=aux->Siguiente;//pasa a la siguiente tarea
            } 
        break;
        case 3:
            printf("Entre el ID a buscar: ");
            scanf("%d",&ID);
            fflush(stdin);
            printf("Buscar en (1-Realizadas, 2-Pendientes, 3-Procesadas): ");
            scanf("%d",&donde);
            fflush(stdin);
            if (donde==1){
                porID=buscarPorID(ListaR,ID); 
                }else if (donde==2){
                    porID=buscarPorID(ListaP,ID);
                    }else if (donde==3){
                        porID=buscarPorID(TareasEP,ID);
                    }else{
                        printf("Opcion no valida\n");
                    }
            if (porID!=NULL){
                printf("Tarea Buscada por ID\n");
                printf("ID: %d\n",porID->T.TareaID);
                printf("Descripcion: ");
                puts(porID->T.Descripcion);
                printf("Duracion: %d\n",porID->T.Duracion);
            }else{
                printf("No se encontro la tarea\n");
            }
            printf("\n");
        break;
        case 4:
            printf("Entre la palabra a buscar: ");
            palabra=(char*)malloc(20*sizeof(char));
            gets(palabra);
            printf("Buscar en (1-Realizadas, 2-Pendientes, 3-Procesadas): ");
            scanf("%d",&donde);
            fflush(stdin);
            if (donde==1){
                porPal=buscarPorPal(ListaR,palabra); 
                }else if (donde==2){
                    porPal=buscarPorPal(ListaP,palabra);
                    }
                    else if (donde==3){
                        porPal=buscarPorPal(TareasEP,palabra);
                    }else{
                        printf("Opcion no valida\n");
                    }
            if (porPal!=NULL){
                printf("Tarea Buscada por Palabra\n");
                printf("ID: %d\n",porPal->T.TareaID);
                printf("Descripcion: ");
                puts(porPal->T.Descripcion);
                printf("Duracion: %d\n",porPal->T.Duracion);
            }else{
                printf("No se encontro la tarea\n");
            }
            printf("\n");
        break;
        case 5:
        printf("Tareas realizadas: \n");
        mostrarLista(ListaR);//muestra la lista por conexiones entre nodos
        printf("\n");
        break;
        case 6:
        printf("Tareas pendientes : \n");
        mostrarLista(ListaP);//muestra la lista por conexiones entre nodos
        printf("\n");
        break;
        case 7:
        printf("Tareas procesadas : \n");
        mostrarLista(TareasEP);//muestra la lista por conexiones entre nodos
        printf("\n");
        break;
        case 8:
        printf("Borrar en (1-Realizadas, 2-Pendientes, 3-Procesadas): ");
        scanf("%d",&donde);
        fflush(stdin);
        printf("Entre el Id de la tarea a borrar: ");
        scanf("%d",&ID);
            if (donde==1){
                ListaR=borrarNodo(ListaR,ID); 
                }else if (donde==2){
                    ListaP=borrarNodo(ListaP,ID);
                    }else if (donde==3){
                        TareasEP=borrarNodo(TareasEP,ID);
                        }else{
                            printf("Opcion no valida\n");
                        }
                        printf("\n");
        break;
        case 9:
        printf("Mostrar de (1-Realizadas, 2-Pendientes, 3-Procesadas): ");
        scanf("%d",&donde);
        fflush(stdin);
        if (donde==1){
            MostrarDatos(ListaR);
            }else if (donde==2){
                MostrarDatos(ListaP);
                }else if (donde==3){
                    MostrarDatos(TareasEP);
                    }else{
                        printf("Opcion no valida\n");
                    }
                    printf("\n");
        break;
        case 10:
        opcion=1;
        while (opcion==1&&opcion!=0)
        {
            printf("Realizadas:\n");
            mostrarLista(ListaR);
            printf("\n");
            printf("Pendientes:\n");
            mostrarLista(ListaP);
            printf("\n");
            printf("Procesadas:\n");
            mostrarLista(TareasEP);
            printf("\n");

            printf("Entre el ID de la tarea a mover: ");
            scanf("%d",&ID);
            fflush(stdin);
            printf("\n");

            selec=buscarPorID(ListaR,ID);
            if (selec!=NULL){
                *tarea=selec->T;
                ListaR=borrarNodo(ListaR,ID);
                }else{
                    selec=buscarPorID(ListaP,ID);
                    if (selec!=NULL){
                        *tarea=selec->T;                 
                        ListaP=borrarNodo(ListaP,ID);
                        }else{
                            selec=buscarPorID(TareasEP,ID);
                            }if (selec!=NULL){
                                *tarea=selec->T;
                                ListaP=borrarNodo(ListaP,ID);
                                }else{
                                    printf("No se encontro la tarea\n");
                                }       
                    }
            printf("\n");

            printf("Mover a (1-Realizadas, 2-Pendientes, 3-Procesadas): ");
            scanf("%d",&donde);
            fflush(stdin);
            if (donde==1){
                ListaR=insertarNodo(ListaR,tarea);
                }else if (donde==2){
                    ListaR=insertarNodo(ListaR,tarea);
                    }else if (donde==3){
                        TareasEP=insertarNodo(TareasEP,tarea);
                        }else{
                        printf("La opcion no es valida\n");
                        }
        printf("Mover otra tarea(1-Si, 0-No)\n");
        scanf("%d",&opcion);
        fflush(stdin);
        }
        printf("Realizadas:\n");
        mostrarLista(ListaR);
        MostrarDatos(ListaR);
        printf("\n");
        printf("Pendientes:\n");
        mostrarLista(ListaP);
        MostrarDatos(ListaP);
        printf("\n");
        printf("Procesadas:\n");
        mostrarLista(TareasEP);
        MostrarDatos(TareasEP);
        printf("\n");
        
        break;
    }
    opcion=menu(opcion);    
}

free(TareasEP);
free(porID);
free(porPal);
free(aBorrar);
free(selec);    
free(tarea);
free(ListaP);
free(ListaR);
    return(0);
}


 void cargarTarea(struct Tarea *tarea,int num){
    char *buff=NULL;
    tarea->TareaID=num+1;
    printf("Entre la descripcion: ");
    buff=(char*)malloc(100*sizeof(char));
    gets(buff);
    tarea->Descripcion=(char*)malloc((strlen(buff)+1)*sizeof(char));
    strcpy(tarea->Descripcion,buff);
    printf("Entre la duracion entre (10 y 100): ");
    scanf("%d",&tarea->Duracion);
    fflush(stdin);
    free(buff);
}

Lista insertarNodo(Lista ListaP, struct Tarea *tarea){
    Lista nuevo;
    nuevo=(Lista)malloc(sizeof(struct Nodo));
    nuevo->T=*tarea;
    nuevo->Siguiente=ListaP;
    ListaP=nuevo;
    return(ListaP);
}

void mostrarLista(Lista lista){
    while (lista!=NULL){
        printf("ID: %d\n",lista->T.TareaID);
        printf("Descripcion: ");
        puts(lista->T.Descripcion);
        printf("Duracion: %d\n",lista->T.Duracion);
        lista=lista->Siguiente;
    }
}

Lista borrarNodo(Lista lista, int ID){
    Lista anterior=NULL;
    Lista actual=lista;
    while (actual!=NULL && actual->T.TareaID!=ID){
        anterior=actual;
        actual=actual->Siguiente;
    }
    if (actual==NULL){//paso todo el while pero no encontro la coincidencia
        return (lista);//retorna la lista original sin borrar nada
    }
    if (anterior==NULL){//tiene un solo elemento
        lista=actual->Siguiente;//apunta a NULL, quitando el primer y unico elemento
        return(lista);
    }else{
        anterior->Siguiente=actual->Siguiente;
    }
    free(actual);
    return(lista);
}

Lista buscarPorID(Lista lista,int ID){
    Lista buscado=NULL;
    buscado=(Lista)malloc(sizeof(struct Nodo));
    while (lista!=NULL){
        if (lista->T.TareaID==ID){
            buscado->T=lista->T;
            buscado->Siguiente=NULL;
            return(buscado);
        }
        lista=lista->Siguiente;
    }
    return(NULL);
}

Lista buscarPorPal(Lista lista,char *palabra){
    Lista buscado=NULL;
    buscado=(Lista)malloc(sizeof(struct Nodo));
    while (lista!=NULL){
        if (strstr(lista->T.Descripcion,palabra)!=NULL){
            buscado->T=lista->T;
            buscado->Siguiente=NULL;
            return(buscado);
        }
        lista=lista->Siguiente;
    }
    return(NULL);
}

void MostrarDatos(Lista lista){
    int count=0, tiempo=0;
    while (lista!=NULL){
        count++;
        tiempo=tiempo+lista->T.Duracion;
        lista=lista->Siguiente;
    }   
    printf("Datos de la lista de tareas: \n");
    printf("Cantidad de tareas: %d\n",count);
    printf("Tiempo asociado: %d\n",tiempo);
    }

int menu(int opcion){
    printf("Seleccione una opcion:\n");
    printf("1-Entrar nueva tarea \n");
    printf("2-Realizar/Procesar tareas \n");
    printf("3-Buscar tarea por ID \n");
    printf("4-Buscar tarea por Palabra \n");
    printf("5-Mostrar tareas realizadas \n");
    printf("6-Mostrar tareas pendientes \n");
    printf("7-Mostrar tareas procesadas\n");
    printf("8-Borrar tarea\n");
    printf("9-Mostrar datos\n");
    printf("10-Mover tarea\n");
    printf("11-Cerrar \n");
    scanf("%d",&opcion);
    fflush(stdin);
    return(opcion);
}
