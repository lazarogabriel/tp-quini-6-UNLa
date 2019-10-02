#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <windows.h>

//CARGA DE DATOS "BOLETAS" PARA EL SORTEO Y BIENVENIDA POR SUPUESTO
void MensajeDeBienvenida();
int CantidadBoletas();
void MenuOpciones(int vector[][8], int l);
void CompraBoletaAutomatica(int m[][8],int c, int l);
void CompraBoletasManual(int m[][8], int c, int l);
void CompradaConExito(int contador);
//SORTEOS
void Tradicional(int m[][8], int l, int booleano);
void SegundaVuelta(int m[][8], int l);
void Revancha(int m[][8], int l);
void Bolillero(int v[6]);
int analizaboletas(int m[][8],int v[6], int l,int coinci, int f);
void imprimeBolillero(int v[6]);
void Ganancias(int m[][8],int l, int boolean);
//ASEGURADORES DE INGRESO DE DATOS
int verificador1(int v[][8],int i, int Nrand);
int verificador0(int v[], int Nrand);
void MenuFinal(int m[][8], int l);
void Resetea(int [][8], int l);
// LA MATRIZ CONSTA DE: FILAS PARA LA CANTIDAD DE BOLETAS A COMPRAR Y COLUMNAS DE LA 0 A LA 5 DE NUMEROS DE LAS BOLETAS, LA POSICION 6 CON NUMEROS DE DNI Y LA 7 CON LAS GANANCIAS PARA LOS SORTEOS
// Y LA ULTIMA POSICION O SEA LA 7 SIRVE COMO UN BOOLEANO PARA EL TRADICIONAL FINAL

int main(){
    int largo, booleano=1;//LARGO ES IGUAL A LA CANTIDAD DE BOLETAS Y BOOLEANO ES PARAR AVISARLE AL TRADICIONAL QUE CAMBIE A LA OPCION JUGAR HASTA QUE SE GANA SOLO

    srand(time(0));//PARA LOS NUMEROS RANDOM

    MensajeDeBienvenida();//PIDE LA CANTIDAD DE BOLETAS A COMPRAR

    largo=CantidadBoletas(); //GUARDA CANTIDAD DE BOLETAS A COMPRAR
    int boletas[largo][8]; //BASE DE DATOS DE LA BOLETAS

    Resetea(boletas,largo);//DEJA LA MATRIZ EN -1 PARA QUE SE GUARDE TODO BIEN
    MenuOpciones(boletas, largo); //MENU Y CARGADE DE MATRIZ "BOLETAS"
    Tradicional(boletas, largo, booleano);// SORTEO TRADICIONAL
    SegundaVuelta(boletas,largo);//SEGUNDA
    Revancha(boletas,largo);//REVANCHA
    Ganancias(boletas,largo,booleano);//MUESTRA LAS GANANCIAS DE LOS O LAS PARTICIPANTES
    MenuFinal(boletas, largo);//MUESTRA EL MENU FINAL
    Resetea(boletas,largo);//VUELVE A PONER LAS BOLETAS EN -1

    return 0;
}
void MensajeDeBienvenida(){
        printf(" ------------------- Bienvenidos\as a Quini 6 -------------------\n\n");
        printf(" Por favor ingrese la cantidad de boletas que desea comprar: ");
}
int CantidadBoletas(){
        int l;
        while(!scanf("%d", &l)){
              fflush(stdin);
              printf("¡No es un numero!\n\n");
              }
        return l;
}
void MenuOpciones(int vector[][8],int l){

    int opcion,num,contador=-1;

    printf("\nA continuacion por favor ingresar:\n\n");

    while(contador+1<l){

            printf("Boleta numero %d", contador+2);
            printf("\n\n1 (uno) para comprar boleta manual\n");
            printf("2 (dos) para comprar boleta automatica\n\n");
            printf("Opcion: ");

            while(!scanf("%d", &opcion)){
                fflush(stdin);
                printf("!No es un numero¡\n\n");
            }
            if(opcion==1){
                contador=contador+1;
                CompraBoletasManual(vector,contador,l);

            }else if(opcion=2){
                contador=contador+1;
                CompraBoletaAutomatica(vector,contador,l);

            }//CIERRE DEL ELSE IF
        }//CIERRE DEL WHILE
}// CIERRE TOTAL DEL PROCEDIMIENTO COMPRAR BOLETAS
void CompraBoletaAutomatica(int m[][8], int c, int l){

    int numRand,colum;

     printf("\n Compra de boleta automatica:");
            // ASEGURADOR... PARA QUE NO SE REPITAN LOS ALEATORIOS
            for(colum=0;colum<7;colum++){

                if(colum<6){

                    numRand=rand()%46;
                    while(verificador1(m,c,numRand)!=1){
                        numRand=rand()%46;
                    }
                    m[c][colum]=numRand;
              }else{
                  printf("\n\n Tu boleta es la N %d tus numeros son:\n\n", c+1);
                  for( colum=0; colum<6;colum++){
                        Sleep(100);
                     printf(" %2d ",m[c][colum]);
                  }
                printf("\n\nPara concretar tu compra por favor ingresa tu numero de DNI (sin puntos) para poder identificar tu boleta.\n\n");
                printf("DNI: ");
                fflush(stdin);
                scanf("%d", &m[c][6]);
                CompradaConExito(c);
                }//CIERRE DE ELSE
            }//cierra for 2
    }//CIERRA PROCEDIMIENTO COMPRAR BOLETAS AUTOMATICAS
void CompraBoletasManual(int m[][8], int c, int l){
    int num, colum;
    printf("Compra de boleta manual.\n\n");
    printf("A continuacion por favor ingresar numeros de 0(cero) a 45(cuarenta y cinco) sin repetirse.\n\n");

            for(int colum=0; colum<7;colum++){
                if(colum<6){
                    printf("  %d.  ",colum+1 );
                    int validar=1;

                    while(validar){
                        validar=0;
                        while(!scanf("%d", &num)){
                            fflush(stdin);
                            printf("\n¡No es un numero!\nIngrese otro: ");
                            printf("\n  %d.  ",colum+1 );
                        }
                         if(!(num>=0 && num<=45)){
                           validar=1;
                           printf("\n%d no es un numero entre 0 y 45", num);
                           printf("\n  %d.  ",colum+1 );
                           }
                        for(int i=0;i<7;i++){
                            if(m[c][i]==num){
                                validar=1;
                                printf("\nNumero repetido. Ingrese otro: ");
                                printf("\n  %d.  ",colum+1 );
                            }
                        }
                    }
                    m[c][colum]=num;
                }else{
                    printf("Tu boleta es la N %d con los numeros:\n\n ", c+1);
                    for(colum=0; colum<6;colum++){
                              printf("%2d ",m[c][colum]);
                    }
                        printf("\n\nPara concretar tu compra por favor ingresa tu numero de DNI (sin puntos) para poder identificar tu boleta.\n\n");
                        printf("DNI: ");
                        scanf("%d", &m[c][6]);

                        CompradaConExito(c);
                        }//cierre del else
                }
}
void CompradaConExito(int contador){
    system("cls");
    printf(" ---------------- ¡Boleta %d comprada con exito! ----------------\n\n\n\n\n", contador+1);
    system("pause");
    system("cls");
}
int verificador0(int v[], int Nrand){
    for(int i=0;i<6;i++){
        if(v[i]==Nrand){
            return 0;
        }
    }
    return 1;
}
int verificador1(int m[][8],int i, int Nrand){
    for(int columna=0;columna<6;columna++){
        if(m[i][columna]==Nrand){
            return 0;
        }
    }
    return 1;
}
void Tradicional(int m[][8], int l, int booleano){
    int NumsSorteados[6],coincidencias=0;

    Bolillero(NumsSorteados);

    printf("---------------------  Tradicional  ---------------------\n\n");
    printf("            -------------------------------------------\n          ");
    printf(" | Los numeros sorteados son los suiguientes |\n");
    printf("            -------------------------------------------\n\n          ");

    imprimeBolillero(NumsSorteados);

    for(int f=0;f<l;f++){
    if(booleano){
            if(analizaboletas(m,NumsSorteados,l,coincidencias, f)==6){
                m[f][7]=5000000;
            }else if(analizaboletas(m,NumsSorteados,l,coincidencias, f)==5){
                m[f][7]=2000000;
            }else if(analizaboletas(m,NumsSorteados,l,coincidencias, f)==4){
                m[f][7]=300000;
            }else if(coincidencias==0){
                m[f][7]=0;
            }

        }else{
            if(analizaboletas(m,NumsSorteados,l,coincidencias, f)==6){
                m[f][7]=1;
            }
        }
        coincidencias=0;
    }
}
void SegundaVuelta(int m[][8], int l){
    int NumsSorteados[6], coincidencias=0;

    Bolillero(NumsSorteados);

    printf("\n\n---------------------  Segunda Vuelta  ---------------------\n\n");
    printf("            -------------------------------------------\n          ");
    printf(" | Los numeros sorteados son los suiguientes |\n");
    printf("            -------------------------------------------\n\n          ");

    imprimeBolillero(NumsSorteados);

    printf("\n\n");


    for(int f=0;f<l;f++){
        analizaboletas(m,NumsSorteados,l,coincidencias, f);

        if(analizaboletas(m,NumsSorteados, l, coincidencias, f)==6){
            m[f][7]=2000000+m[f][7];
        }else if(analizaboletas(m,NumsSorteados, l, coincidencias, f)==5){
           m[f][7]=500000+m[f][7];
        }else if(analizaboletas(m,NumsSorteados, l, coincidencias, f)==4){
            m[f][7]=100000+m[f][7];
        }else{
            m[f][7]=0+m[f][7];
        }
        coincidencias=0;
    }

}
void Revancha(int m[][8], int l){
    int NumsSorteados[6],coincidencias=0;

    Bolillero(NumsSorteados);

    printf("---------------------  Sorteo Revancha  ---------------------\n\n");
    printf("            -------------------------------------------\n          ");
    printf(" | Los numeros sorteados son los suiguientes |\n");
    printf("            -------------------------------------------\n\n          ");

    imprimeBolillero(NumsSorteados);

    for(int f=0;f<l;f++){

        if(analizaboletas(m,NumsSorteados,l,coincidencias, f)==6){
            m[f][7]=4000000+m[f][7];
        }else{
            m[f][7]=0+m[f][7];
        }
        coincidencias=0;
    }
}
int analizaboletas(int m[][8],int v[6], int l,int coinci, int f){
    coinci=0;
        for(int columnas=0;columnas<6;columnas++){
            for(int i=0;i<6;i++){
                    if(m[f][columnas]==v[i]){
                        coinci=coinci+1;
                    }
            }
        }//CIERRE DEL FOR ANALIZA POR BOLETA
    return coinci;
}
void Bolillero(int v[6]){

    int Nrand;
    for(int i=0;i<6;i++){
        Nrand=rand()%46;
        while((verificador0(v, Nrand))!=1){
            Nrand=rand()%46;
        }
        v[i]=Nrand;
    }
}
void imprimeBolillero(int v[6]){
    for(int i=0;i<6;i++){

        printf("    %2d ", v[i]);
    }
}
void Ganancias(int m[][8],int l, int boolean){
if(boolean==0){
    printf("\n\n+++++++++++++++++ GANACIAS DE LOS SORTEOS +++++++++++++++++\n\n");
}else{
    printf("\n\n+++++++++++++++++ GANACIAS DE LOS SORTEOS +++++++++++++++++\n\n");
}

    for(int f=0;f<l;f++){
            if(boolean){
                Sleep(350);
                printf("\n   El\\la participante con DNI [%d] ha ganado $%d\n",m[f][6], m[f][7]);
            }else{
                if(m[f][7]==1){
                    printf(" ------------------------------\n");
                    printf("   EL DNI [%d] GANO $5.000.000 \n ", m[f][6]);
                    printf(" ------------------------------\n");
                }
            }
    }
    /*for(int f=0;f<l;f++){
        for(int c=0;c<8;c++){
            printf("%d ", m[f][c]);   // <<----- PARA DOCENTES : SI QUIERE VER COMO VA CAMBIANDO LA MATRIZ "DESCOMENTE"
        }
        printf("\n");
    }*/
    printf("\n\n");
 if(boolean){
    printf("    ");
    system("pause");
    system("cls");
    }
}
void MenuFinal(int m[][8], int l){

    int opcion, jugarHasta=0,ganador=0,cont=0;
    printf("\n  Sorteo finalizado.\n\n ");
    printf(" A continuacion ingrese: \n\n");
    printf("  1. Para mantener las boletas y jugar hasta que gane el sorteo Tradicional.\n");
    printf("  2. Jugar otra vez.\n");
    printf("  3. Salir\n\n");
    printf("  Opcion: ");
    while(!scanf("%d", &opcion)){
        fflush(stdin);
        printf("¡No es un numero!\n\n");
    }

    switch(opcion){
        case 1:// SE ELIJE JUGAR EL TRADICIONAL HASTA QUE GANE
           while(ganador!=1){

            Tradicional(m,l,jugarHasta);
            Ganancias(m,l,jugarHasta);
            for(int i=0;i<l;i++){
                if(m[i][7]==1){
                    ganador=1;
                }
           }
           cont=cont+1;
           printf("\n SORTEO NUMERO [%d]\n\n ", cont);
            if(ganador==0){
                system("cls");
            }

        }
        printf("\n\n  Cantidad de sorteos que hubo que jugar hasta que se ganara: %d\n\n ", cont);
        system("pause");
        system("cls");
        MenuFinal(m,l);
        break;
        case 2:// SI SE QUIERE JUGAR OTRA VEZ
        system("cls");
        jugarHasta=1;

        srand(time(0));// PARA NUMEROS RANDOM

        MensajeDeBienvenida();//PIDE LA CANTIDAD DE BOLETAS A COMPRAR

        l=CantidadBoletas(); //GUARDA CANTIDAD DE BOLETAS A COMPRAR

        int boletas[l][8]; //BASE DE DATOS DE LA BOLETAS
            Resetea(m,l); //DEJA EN -1 LAS BOLETAS PARA JUGAR OTRA VEZ
            MenuOpciones(m, l);//EL USUARIO ELIJE ENTRE COMPRA AUTOMATICO O MANUAL
            Tradicional(m,l,jugarHasta);//TRADICIONAL
            SegundaVuelta(m,l);//2DA VUELTA
            Revancha(m,l);//REVANCHA
            Ganancias(m,l, jugarHasta);//AL COMPARAR LAS BOLETAS CON LOS NUMEROS ALEATORIOS SI COINCIDEN RESPECTIVAMENTE LOS ACIERTOS SE HACE LA SUMATORIA DE LO GANADO
            MenuFinal(m, l);//MENU FINAL PARA QUE SE ELIJA ENTRE SALIR, JUGAR OTRA VEZ O TRADICINAL HASTA GANAR 6 ACIERTOS
        break;
    }
    printf("\n\nQUE TENGA UN BUEN DIA \n\n");
}
void Resetea(int m[][8], int l){
    for(int f=0;f<l;f++){
        for(int c=0;c<8;c++){
            if(c<7){
            m[f][c]=-1;
            }else{
                m[f][c]=0;
            }
            //printf("%d ", m[f][c]);// <<----- PARA DOCENTES : SI QUIERE VER COMO VA CAMBIANDO LA MATRIZ "DESCOMENTE"
        }
        //printf("\n");// <<----- PARA DOCENTES : SI QUIERE VER COMO VA CAMBIANDO LA MATRIZ "DESCOMENTE"
    }
}
