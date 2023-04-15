#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea{
    int TareaID;
    char *Descripcion;
    int Duracion;
};

void cargarTarea(struct Tarea **tareasP, int num);
void mostrarTarea(struct Tarea **tareasP, int num);
void realizarTarea(struct Tarea **tareasP,struct Tarea **tareasR, int num, int num2);
struct Tarea* buscarTarea(struct Tarea **tareas, int num, int ID);

int main(){
    int cant, num, num2, estado, ID;
    struct Tarea *porID=NULL;
    struct Tarea **tareasP=NULL;
    struct Tarea **tareasR=NULL;
    printf("Entre la cantidad de tareas: ");
    scanf("%d",&cant);
    fflush(stdin);
    
    tareasP=(struct Tarea **)malloc(cant * sizeof(struct Tarea*));
    
    for (int i = 0; i < cant; i++){
        printf("Tarea #%d: \n",i+1);
        cargarTarea(tareasP,i);
    }
    printf("\n");

    printf("Tareas pendientes: \n");
    for (int i = 0; i < cant; i++){
        printf("Tarea #%d: \n",i+1);
        mostrarTarea(tareasP,i);
    }
    printf("\n");

    int j=0;
    for (int i = 0; i < cant; i++){
        printf("Tarea #%d:\n",i+1);
        printf("1-Realizada, 0-Pendiente: \n"),
        scanf("%d",&estado);
        if (estado==1){
            tareasR=(struct Tarea **)malloc((j+1) * sizeof(struct Tarea*));
            realizarTarea(tareasP,tareasR,i,j);
            j++;
        }
    }
    printf("\n");

    printf("Tareas realizadas: \n");
    for (int i = 0; i < j; i++){
        printf("Tarea #%d: \n",i+1);
        printf("ID: %d\n",tareasR[i]->TareaID);
        printf("Descripcion: ");
        puts(tareasR[i]->Descripcion);
        printf("Duracion: %d\n",tareasR[i]->Duracion);
    }
    printf("\n");

    printf("Tareas pendientesa actualizadas: \n");
    for (int i = 0; i < cant; i++){
        if (tareasP[i]!=NULL){
            printf("Tarea #%d: \n",i+1);
            mostrarTarea(tareasP,i);
        }
    }
    printf("\n");
    
    printf("Entre un ID a buscar: ");
    scanf("%d",&ID);
    fflush(stdin);
    //porID=(struct Tarea*)malloc(1*sizeof(struct Tarea));
    porID=buscarTarea(tareasP,cant,ID);
    if (porID!=NULL){
        printf("Tarea buscada: \n");
        printf("ID: %d\n",porID->TareaID);
        printf("Descripcion: ");
        puts(porID->Descripcion);
        printf("Duracion: %d\n",porID->Duracion);
    }else{
        printf("Tarea no encontrada\n");
    }
    
    
    

    free(porID);
    free(tareasP);
    free(tareasR);
    return(0);
}

void cargarTarea(struct Tarea **tareasP, int num){
    char *buff=NULL;
    tareasP[num]=NULL;
    tareasP[num]=(struct Tarea*)malloc(sizeof(struct Tarea));
        printf("Entre el ID: ");
        scanf("%d",&tareasP[num]->TareaID);
        fflush(stdin);
        printf("Entre la descripcion: ");
        buff=(char*)malloc(100*sizeof(char));
        gets(buff);
        tareasP[num]->Descripcion=(char*)malloc((strlen(buff)+1)*sizeof(char));
        strcpy((tareasP[num]->Descripcion),buff);
        printf("Entre la duracion entre (10 y 100): ");
        scanf("%d",&tareasP[num]->Duracion);
        fflush(stdin);
        free(buff);
}

void mostrarTarea(struct Tarea **tareasP, int num){
    printf("ID: %d\n",tareasP[num]->TareaID);
    printf("Descripcion: ");
    puts(tareasP[num]->Descripcion);
    printf("Duracion: %d\n",tareasP[num]->Duracion);
}

void realizarTarea(struct Tarea **tareasP, struct Tarea **tareasR, int num, int num2){
   tareasR[num2]=NULL;
   tareasR[num2]=(struct Tarea*)malloc(sizeof(struct Tarea));
   tareasR[num2]=tareasP[num];
   tareasP[num]=NULL;
}

struct Tarea* buscarTarea(struct Tarea **tareas, int num, int ID){
   for (int i = 0; i < num; i++){
    if (tareas[i]!=NULL){
        if (tareas[i]->TareaID==ID){
        return(tareas[i]);
        }
    }
   }
return NULL;
}