#include <stdio.h>
#include <stdlib.h>
#include <winbgim.h>
#include <time.h>
//declaracion de variables
int x_rand, y_rand; //son las coordenadas aleatorias y pocisiona la hormiga de busqueda en dicha posicion
int x_hor, y_hor; //posicion actual de la hormiga
int x_azucar, y_azucar; //posicion del monticulo de azucar
bool encontrado = false;
int x_mark[70], y_mark[70]; //marcas de referencia q deja la hormiga de busqueda
int i = 0, j = 0; //control de flujo
short interval = 0; //se usará como contador de repeticiones de generacion aleatoria (si supera los 500, se disminuira a un rango menor de aleatoriedad)
//declaracion de proptotipos
void hormiga_buscando();
void hormiga_quieta(int id);
void monticulo_azucar();
int main(){
   //Inicializamos modo gráfico
   initwindow(310,280);
   //Inicializacion de las matrices para las marcas
   for(;i<60;i++){
        x_mark[i]=0;
        y_mark[i]=0;
   }
   i=0;
   srand(time(NULL));//semilla para numeros aleatorios
   //Valores para la posicion de la azucar (aleatorio)
   x_azucar = rand()%171+50;
   y_azucar = rand()%151+50;
   x_hor = 30;
   y_hor = 30;
   monticulo_azucar(); //se dibuja donde esta el azucar y despues no se muestra mas
   //posiciones iniciales d ecada hormiga
   hormiga_quieta(1);
   hormiga_quieta(2);
   delay(1500);
   cleardevice();//para borrar pantalla
   //// busqueda del azucar ////
   while(1){
        setcolor(15);
        monticulo_azucar();
        hormiga_quieta(2); //para mostrar la hormiga que espera por su amiga :3
        srand(time(NULL)); //semilla para numeros aleatorios
        //Valores de x e y aleatorios para interval menor a 500
        if(interval <= 1000){
            x_rand = rand()%206+45; //valores random 45 hasta 290
            y_rand = rand()%211+45; //valorws random desde 45 hasta 256
        }
        //si interval es multiplo de 10, la hormiga dejará una marca
        if(interval%250 == 0){
            x_mark[i] = x_rand;
            y_mark[i] = y_rand;
            i++;
        }
        //Valores de x e y aleatorios por mas de una vez (si interval superior a 500)
        if(interval > 1000){
            //Cuanto mas este proximo al azucar, mas se restringe el intervalo para hacer la busqueda mas factible
            if((x_rand>(x_azucar-10) && x_rand < (x_azucar+15)) && (y_rand > (y_azucar-10) && y_rand < (y_azucar+15))){
                x_rand = x_azucar;
                y_rand = y_azucar;
                while(x_hor != x_rand || y_hor != y_rand){
                    setcolor(15);
                    monticulo_azucar();
                    hormiga_quieta(2);
                    if(x_hor < x_rand)
                        x_hor++;
                    else if(x_hor > x_rand)
                        x_hor--;
                    if(y_hor < y_rand)
                        y_hor++;
                    else if(y_hor > y_rand)
                        y_hor--;
                    setcolor(6);
                    hormiga_buscando();
                    delay(5);
                    cleardevice();
                }
                encontrado = true;
            }else if((x_rand>(x_azucar-10) && x_rand < (x_azucar-70)) && (y_rand > (y_azucar-70) && y_rand < (y_azucar+10))){
                x_rand = rand()%21+(x_azucar-10);
                y_rand = rand()%31+(y_azucar-20);
            }else if((x_rand > 50 && x_rand < 220) && (y_rand > 50 && 200)){
                x_rand = rand()%101+(x_azucar-50);
                y_rand = rand()%91+(y_azucar-40);
            }else{
                x_rand = rand()%121+(x_azucar-50);
                y_rand = rand()%111+(y_azucar-40);
            }
        }
        if(!encontrado){
            //movemos la hormiga pixel a pixel
            if(x_hor != x_rand){
                if(x_hor < x_rand)
                    x_hor++;
                if(x_hor > x_rand)
                    x_hor--;
            }
            if(y_hor != y_rand){
                if(y_hor <y_rand)
                    y_hor++;
                if(y_hor > y_rand)
                    y_hor--;
            }
        }
        //Si la hormiga encontró el azucar, avisará a su compañera
        if(x_rand == x_azucar && y_rand == y_azucar){
            setcolor(15);
            monticulo_azucar();
            hormiga_quieta(2);
            moveto(10,240);
            setcolor(2);
            hormiga_buscando();
            outtext("Has encontrado azucar");
            delay(1000);
            moveto(10,240);
            outtext("Presione una tecla para continuar");
            getch();
            break;
        }
        setcolor(6);
        hormiga_buscando(); //Dibujamos a la hormiga que sale a buscar :3
        delay(5);
        cleardevice();
        interval++;
   }
   j=i; //Se usará para una comprobacion mas adelante
   i--;
   //En esta parte la hormiga que encontro el azucar se devuelve a su posicion inicial y le dice a su compañera donde buscar azucar :P
   cleardevice();
   while(x_hor != 30 || y_hor!= 30){
        if(i != 0){
            while(x_hor != x_mark[i]|| y_hor != y_mark[i]){
                setcolor(15);
                monticulo_azucar();
                hormiga_quieta(2);
                if(x_hor < x_mark[i])
                    x_hor++;
                else if(x_hor > x_mark[i])
                    x_hor--;
                if(y_hor < y_mark[i])
                    y_hor++;
                else if(y_hor > y_mark[i])
                    y_hor--;
                setcolor(6);
                hormiga_buscando();
                delay(5);
                cleardevice();
            }
            i--;
        }else{
            setcolor(15);
            monticulo_azucar();
            hormiga_quieta(2);
            if(x_hor > 30)
                x_hor--;
            else if(x_hor < 30)
                x_hor++;
            if(y_hor > 30)
                y_hor--;
            else if(y_hor < 30)
                y_hor++;
            setcolor(6);
            hormiga_buscando();
            delay(5);
            cleardevice();
        }
    }
    setcolor(15);
    monticulo_azucar();
    hormiga_quieta(1);
    hormiga_quieta(2);
    delay(500);
    while(x_hor != x_azucar || y_hor != y_azucar){
        if(i != j){
            while(x_hor != x_mark[i]|| y_hor != y_mark[i]){
                setcolor(15);
                monticulo_azucar();
                hormiga_quieta(1);
                if(x_hor < x_mark[i])
                    x_hor++;
                else if(x_hor > x_mark[i])
                    x_hor--;
                if(y_hor < y_mark[i])
                    y_hor++;
                else if(y_hor > y_mark[i])
                    y_hor--;
                setcolor(4);
                hormiga_buscando();
                delay(5);
                cleardevice();
            }
            i++;
        }else{
            setcolor(15);
            monticulo_azucar();
            hormiga_quieta(1);
            if(x_hor < x_azucar)
                x_hor++;
            else if(x_hor > x_azucar)
                x_hor--;
            if(y_hor < y_azucar)
                y_hor++;
            else if(y_hor > y_azucar)
                y_hor--;
            setcolor(4);
            hormiga_buscando();
            delay(5);
            cleardevice();
        }
    }
    setcolor(15);
    monticulo_azucar();
    hormiga_quieta(1);
    setcolor(2);
    hormiga_buscando();
    moveto(10,240);
    setcolor(2);
    outtext("Estás lleno de determinación :3!!!"); // mensaje motivador para la hormiga que encontro el azucar :P
    delay(4000);
    closegraph();
}
//Dibuja las hormigas en su posicion iniciales
void hormiga_quieta(int id){
    if(id == 1){
        setcolor(6);
        ellipse(30,30,0,360,7,2);
        circle(30+8,30,3);
        line(30, 28, 30, 20);
        line(30, 31, 30, 39);
        line(33, 28, 37, 20);
        line(33, 31, 37, 39);
        line(27, 28, 23, 20);
        line(27, 31, 23, 39);
    }
    else if(id == 2){
        setcolor(4);
        ellipse(30,20,0,360,7,2);
        circle(30+8,20,3);
        line(30, 18, 30, 10);
        line(30, 21, 30, 29);
        line(33, 18, 37, 10);
        line(33, 21, 37, 29);
        line(27, 18, 23, 10);
        line(27, 21, 23, 29);
    }
}
//Dibuja la hormiga que sale a buscar azucar
void hormiga_buscando(){
    ellipse(x_hor,y_hor,0,360,7,2);
    circle(x_hor+8,y_hor,3);
    line(x_hor, y_hor-2, x_hor, y_hor-10);
    line(x_hor, y_hor+1, x_hor, y_hor+9);
    line(x_hor+3, y_hor-2, x_hor+7, y_hor-10);
    line(x_hor+3, y_hor+1, x_hor+7, y_hor+9);
    line(x_hor-3, y_hor-2, x_hor-7, y_hor-10);
    line(x_hor-3, y_hor+1, x_hor-7, y_hor+9);
}
//Dibuja un montículo de azucar en una coordenadas preestablecidas
void monticulo_azucar(){
    circle(x_azucar+8,y_azucar+8,4);
    circle(x_azucar+5,y_azucar+13,2);
    circle(x_azucar+11,y_azucar-3,2);
}
