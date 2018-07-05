#include <iostream>
#include "miniwin.h"
#include <stdlib.h>

using namespace std;
using namespace miniwin;

/***************COSA IMPORTANTE A REALIZAR****************/
/* crear una constante para 2*radio, 4*radio y 6*radio, ya que queda feo el codigo así tal como está

**********************************************************/

static const int LADO = 12;
static const Color vector[6] = {AZUL, MAGENTA, ROJO, VERDE, AMARILLO, BLANCO};

class Particula {
  private:

    float x;
    float y;
    Color c;
    bool fija;

  public:

  Particula (){
    x = 50;
    y = 50;
    c = BLANCO;
    fija = false;
  }

  Particula(int POSX, int POSY, Color k){
    x = POSX;
    y = POSY;
    c = k;
    fija = false;
  }

void SetPosicionX( float posicionX){

x = posicionX;

}

void SetPosicionY(float posicionY){

y = posicionY;

}

void SetPosicion(float posicionX, float posicionY){

x = posicionX;
y = posicionY;

}


void SetColor(Color col){

c = col;

}

void SetEstado(bool estado){

  fija = estado;
}

float GetPosicionX ()const{

	return x;
}

float GetPosicionY ()const{

	return y;

}

bool GetEstado () const{

  return fija;

}

Color GetColor()const{

	return c;
}


  void MueveParticula(int ancho, int alto, int t){ //Función que mueve la particula según la tecla pulsada ysegún el alto y ancho

    if(fija == false){

      switch (t) {

        case IZQUIERDA :
          if(x > LADO)
            x-=2*LADO;

            break;

        case DERECHA :
          if(x < ancho - LADO)
            x+=2*LADO;

          break;

        case ARRIBA :

          if(y > LADO)
            y-=2*LADO;

            break;

        case ABAJO :
          if(y < alto - LADO)
            y+=2*LADO;

            break;

        case 89 :

            break;
      }

      if(y >= alto -LADO) //Así bloqueamos la pieza una vez toque el suelo
        fija = true;
      }




  }

 //Colision entre dos particulas
 /*
DESCRIPCIÓN DEL METODO COLISION ENTRE DOS PARTICULAS: Simplemente se le pasa como argumento una particula y comparan sus posiciones. devuelve un booleano
 */

 bool ColisionEntreParticulas(Particula particula1){

    bool hay_colision = false;

   if( (GetPosicionX() == particula1.GetPosicionX() ) && ( GetPosicionY() == particula1.GetPosicionY() - 2*LADO) && (particula1.GetEstado() == true) )
    hay_colision = true;


    return hay_colision;


 }

  void PintaParticula(){

  color(c);
  rectangulo_lleno(x-LADO, y-LADO, x+LADO, y+LADO);
  color(NEGRO);
  rectangulo(x-LADO, y-LADO, x+LADO, y+LADO);

  }



};


class Pieza {
  private:

    int ID; //identificador de la pieza
    int utiles; //numero de cuadraditos pequeños que contiene
    bool piezafija; // indica si la pieza está fija
    Particula *pieza; //vector dinamico de piezas
    int estado; //Estado de la pieza, usado para la rotación. Estados 0,1,2,3

    void LiberaMemoria(){
      if(pieza !=0)
        delete[] pieza;

    }

    void ReservaMemoria(){
      pieza = new Particula[utiles];

    }

    void Copiar (const Pieza &pieza1){ //Método privado copiar objetos clase Pieza

      ID = pieza1.GetID();
      utiles = pieza1.GetUtiles();
      piezafija = pieza1.GetEstadoPieza();
      estado = pieza1.GetEstadoPosicion();

      ReservaMemoria();
      Particula p;

      for(int i = 0; i< utiles; i++){
        p = pieza1.ObtieneParticula(i);
        pieza[i] = p;
      }

    }

  public:

  Pieza (){ //Constructor por defecto. Pieza vacía

    int num;
    do{
    num = rand()%7;
    }while(num == 0);

    ID = num;
    utiles = 4;
    piezafija = false;
    estado = 0;
    ReservaMemoria();

  }

  Pieza(int identificador){ //Constructor con parámetros
    ID = identificador;
    utiles = 4;
    piezafija = false;
    estado = 0;
    ReservaMemoria();

  }


  Pieza (const Pieza &pieza1){ //Constructor de copia

  Copiar(pieza1);

  }

  ~Pieza (){ //Destructor

    LiberaMemoria();


  }



int GetUtiles() const{
  return utiles;
}

bool GetEstadoPieza()const{
  return piezafija;
}

int GetID() const{
  return ID;

}

bool GetEstadoPosicion()const{
  return estado;

}

void SetID(int identificador){

    ID = identificador;
}

Pieza &operator=(const Pieza &pieza1){ //Sobrecarga operador =

  if(&pieza1 != this){

  				delete [] this->pieza;
  				Copiar(pieza1);
  			}

  			return *this;
}



void SetEstadoPieza(bool estafija){
  piezafija =  estafija;
}

void BajaTodo(int limit){

  borra();

  for(int i = 0; i< utiles; i++){

  if(pieza[i].GetEstado() == true && pieza[i].GetPosicionY() <= limit){
  //cout<<pieza[i].GetPosicionY()<<"\t";
  pieza[i].SetPosicion(pieza[i].GetPosicionX(), pieza[i].GetPosicionY() + 2*LADO);
  //cout<<pieza[i].GetPosicionY()<<"\n";
  }
    }

    refresca();

}




void OrdenaPieza (){
  static const int XINI = LADO*17; //CONDICIONES INCIALES DE LA PIEZA. SIEMPRE SALDRÁ DESDE ARRIBA Y MAS O MENOS EL CENTRO
  static const int YINI = LADO;

  switch (ID) {
    case 1 :
      pieza[0].SetPosicion(XINI,YINI); //figura cuadrado
      pieza[1].SetPosicion(XINI + 2*LADO, YINI);
      pieza[2].SetPosicion(XINI, YINI + 2*LADO);
      pieza[3].SetPosicion(XINI + 2*LADO, YINI + 2*LADO);

      for(int i =0; i< utiles; i++)
        pieza[i].SetColor(ROJO);

      break;

    case 2 :
      pieza[0].SetPosicion(XINI, YINI + 4*LADO);//figura L
      pieza[1].SetPosicion(XINI,YINI);
      pieza[2].SetPosicion(XINI, YINI + 2*LADO);
      pieza[3].SetPosicion(XINI + 2*LADO, YINI + 4*LADO);

      for(int i=0; i<utiles; i++)
        pieza[i].SetColor(VERDE);

      break;


    case 3 :
      pieza[0].SetPosicion(XINI + 2*LADO,YINI + 2*LADO); // fijura _|_
      pieza[1].SetPosicion(XINI, YINI + 2*LADO);
      pieza[2].SetPosicion(XINI + 2*LADO, YINI);
      pieza[3].SetPosicion(XINI + 4*LADO, YINI + 2*LADO);

      for(int i=0; i<utiles; i++)
        pieza[i].SetColor(CYAN);

      break;


    case 4 :
    pieza[0].SetPosicion(XINI +2*LADO, YINI + 4*LADO); //figura L inversa
    pieza[1].SetPosicion(XINI +2*LADO,YINI);
    pieza[2].SetPosicion(XINI +2*LADO, YINI + 2*LADO);
    pieza[3].SetPosicion(XINI, YINI + 4*LADO);

    for(int i=0; i<utiles; i++)
      pieza[i].SetColor(VERDE);

      break;

    case 5 :

    pieza[0].SetPosicion(XINI +2*LADO, YINI + 2*LADO); //figura Z
    pieza[1].SetPosicion(XINI,YINI);
    pieza[2].SetPosicion(XINI +2*LADO, YINI);
    pieza[3].SetPosicion(XINI +4*LADO, YINI + 2*LADO);

    for(int i=0; i<utiles; i++)
      pieza[i].SetColor(AMARILLO);

      break;

    case 6 :
    pieza[0].SetPosicion(XINI +2*LADO, YINI +2*LADO); //figura Z inversa
    pieza[1].SetPosicion(XINI,YINI+ 2*LADO);
    pieza[2].SetPosicion(XINI +2*LADO, YINI);
    pieza[3].SetPosicion(XINI +4*LADO, YINI);

    for(int i=0; i<utiles; i++)
      pieza[i].SetColor(MAGENTA);

      break;

    case 7 :

    pieza[0].SetPosicion(XINI,YINI); //figura Z inversa
    pieza[1].SetPosicion(XINI +2*LADO, YINI);
    pieza[2].SetPosicion(XINI +4*LADO, YINI);
    pieza[3].SetPosicion(XINI +6*LADO, YINI);

    for(int i=0; i<utiles; i++)
      pieza[i].SetColor(AZUL);

      break;


  }


}

void RotarPieza(){

  switch (ID) {
    case 2 :
          switch (estado) {
          case 0 :
            pieza[1].SetPosicion(pieza[1].GetPosicionX() + 4*LADO, pieza[1].GetPosicionY() + 4*LADO);
            pieza[2].SetPosicion(pieza[2].GetPosicionX() + 2*LADO, pieza[2].GetPosicionY() + 2*LADO);
            pieza[3].SetPosicion(pieza[3].GetPosicionX() - 2*LADO, pieza[3].GetPosicionY() + 2*LADO);

              estado = 1;
          break;

          case 1 :
            pieza[1].SetPosicion(pieza[1].GetPosicionX() - 4*LADO, pieza[1].GetPosicionY() + 4*LADO);
            pieza[2].SetPosicion(pieza[2].GetPosicionX() - 2*LADO, pieza[2].GetPosicionY() + 2*LADO);
            pieza[3].SetPosicion(pieza[3].GetPosicionX() - 2*LADO, pieza[3].GetPosicionY() - 2*LADO);


            estado = 2;
          break;

          case 2 :
            pieza[1].SetPosicion(pieza[1].GetPosicionX() - 4*LADO, pieza[1].GetPosicionY() - 4*LADO);
            pieza[2].SetPosicion(pieza[2].GetPosicionX() - 2*LADO, pieza[2].GetPosicionY() - 2*LADO);
            pieza[3].SetPosicion(pieza[3].GetPosicionX() + 2*LADO, pieza[3].GetPosicionY() - 2*LADO);

            estado = 3;
          break;

          case 3 :

            pieza[1].SetPosicion(pieza[1].GetPosicionX() + 4*LADO, pieza[1].GetPosicionY() - 4*LADO);
            pieza[2].SetPosicion(pieza[2].GetPosicionX() + 2*LADO, pieza[2].GetPosicionY() - 2*LADO);
            pieza[3].SetPosicion(pieza[3].GetPosicionX() + 2*LADO, pieza[3].GetPosicionY() + 2*LADO);


            estado = 0;
          break;
          }

    break;

    case 3 :
      switch (estado) {
      case 0 :
        pieza[1].SetPosicion(pieza[1].GetPosicionX() + 2*LADO, pieza[1].GetPosicionY() - 2*LADO);
        pieza[2].SetPosicion(pieza[2].GetPosicionX() + 2*LADO, pieza[2].GetPosicionY() + 2*LADO);
        pieza[3].SetPosicion(pieza[3].GetPosicionX() - 2*LADO, pieza[3].GetPosicionY() + 2*LADO);

          estado = 1;
          break;

      case 1 :
        pieza[1].SetPosicion(pieza[1].GetPosicionX() + 2*LADO, pieza[1].GetPosicionY() + 2*LADO);
        pieza[2].SetPosicion(pieza[2].GetPosicionX() - 2*LADO, pieza[2].GetPosicionY() + 2*LADO);
        pieza[3].SetPosicion(pieza[3].GetPosicionX() - 2*LADO, pieza[3].GetPosicionY() - 2*LADO);


        estado = 2;
        break;

      case 2 :
        pieza[1].SetPosicion(pieza[1].GetPosicionX() - 2*LADO, pieza[1].GetPosicionY() + 2*LADO);
        pieza[2].SetPosicion(pieza[2].GetPosicionX() - 2*LADO, pieza[2].GetPosicionY() - 2*LADO);
        pieza[3].SetPosicion(pieza[3].GetPosicionX() + 2*LADO, pieza[3].GetPosicionY() - 2*LADO);

        estado = 3;
        break;

      case 3 :

        pieza[1].SetPosicion(pieza[1].GetPosicionX() - 2*LADO, pieza[1].GetPosicionY() - 2*LADO);
        pieza[2].SetPosicion(pieza[2].GetPosicionX() + 2*LADO, pieza[2].GetPosicionY() - 2*LADO);
        pieza[3].SetPosicion(pieza[3].GetPosicionX() + 2*LADO, pieza[3].GetPosicionY() + 2*LADO);


        estado = 0;

        break;
    }
    break;

    case 4 :
          switch (estado) {
              case 0 :
                pieza[1].SetPosicion(pieza[1].GetPosicionX() + 4*LADO, pieza[1].GetPosicionY() + 4*LADO);
                pieza[2].SetPosicion(pieza[2].GetPosicionX() + 2*LADO, pieza[2].GetPosicionY() + 2*LADO);
                pieza[3].SetPosicion(pieza[3].GetPosicionX() + 2*LADO, pieza[3].GetPosicionY() - 2*LADO);

                estado = 1;
                break;

              case 1 :
                pieza[1].SetPosicion(pieza[1].GetPosicionX() - 4*LADO, pieza[1].GetPosicionY() + 4*LADO);
                pieza[2].SetPosicion(pieza[2].GetPosicionX() - 2*LADO, pieza[2].GetPosicionY() + 2*LADO);
                pieza[3].SetPosicion(pieza[3].GetPosicionX() + 2*LADO, pieza[3].GetPosicionY() + 2*LADO);


                estado = 2;
                break;

              case 2 :
                pieza[1].SetPosicion(pieza[1].GetPosicionX() - 4*LADO, pieza[1].GetPosicionY() - 4*LADO);
                pieza[2].SetPosicion(pieza[2].GetPosicionX() - 2*LADO, pieza[2].GetPosicionY() - 2*LADO);
                pieza[3].SetPosicion(pieza[3].GetPosicionX() - 2*LADO, pieza[3].GetPosicionY() + 2*LADO);

                estado = 3;
                break;

              case 3 :

                pieza[1].SetPosicion(pieza[1].GetPosicionX() + 4*LADO, pieza[1].GetPosicionY() - 4*LADO);
                pieza[2].SetPosicion(pieza[2].GetPosicionX() + 2*LADO, pieza[2].GetPosicionY() - 2*LADO);
                pieza[3].SetPosicion(pieza[3].GetPosicionX() - 2*LADO, pieza[3].GetPosicionY() - 2*LADO);


                estado = 0;
                break;
                }
        break;

        case 5:
            switch (estado) {
              case 0 :
                pieza[1].SetPosicion(pieza[1].GetPosicionX() + 4*LADO, pieza[1].GetPosicionY());
                pieza[2].SetPosicion(pieza[2].GetPosicionX() + 2*LADO, pieza[2].GetPosicionY() + 2*LADO);
                pieza[3].SetPosicion(pieza[3].GetPosicionX() - 2*LADO, pieza[3].GetPosicionY() + 2*LADO);

                estado = 1;
                break;

              case 1 :
                pieza[1].SetPosicion(pieza[1].GetPosicionX() - 4*LADO, pieza[1].GetPosicionY());
                pieza[2].SetPosicion(pieza[2].GetPosicionX() - 2*LADO, pieza[2].GetPosicionY() - 2*LADO);
                pieza[3].SetPosicion(pieza[3].GetPosicionX() + 2*LADO, pieza[3].GetPosicionY() - 2*LADO);


                estado = 0;
                break;

                }

        break;

        case 6:
                switch (estado) {
                  case 0 :
                    pieza[1].SetPosicion(pieza[1].GetPosicionX() + 2*LADO, pieza[1].GetPosicionY() - 2*LADO);
                    pieza[2].SetPosicion(pieza[2].GetPosicionX() + 2*LADO, pieza[2].GetPosicionY() + 2*LADO);
                    pieza[3].SetPosicion(pieza[3].GetPosicionX() , pieza[3].GetPosicionY() + 4*LADO);

                    estado = 1;
                    break;

                  case 1 :
                    pieza[1].SetPosicion(pieza[1].GetPosicionX() - 2*LADO, pieza[1].GetPosicionY() + 2*LADO);
                    pieza[2].SetPosicion(pieza[2].GetPosicionX() - 2*LADO, pieza[2].GetPosicionY() - 2*LADO);
                    pieza[3].SetPosicion(pieza[3].GetPosicionX(), pieza[3].GetPosicionY() - 4*LADO);


                    estado = 0;
                    break;

                    }
          break;

        case 7:
            switch (estado) {
              case 0 :
                pieza[1].SetPosicion(pieza[1].GetPosicionX() - 2*LADO, pieza[1].GetPosicionY() + 2*LADO);
                pieza[2].SetPosicion(pieza[2].GetPosicionX() - 4*LADO, pieza[2].GetPosicionY() + 4*LADO);
                pieza[3].SetPosicion(pieza[3].GetPosicionX() - 6*LADO, pieza[3].GetPosicionY() + 6*LADO);

                estado = 1;
                break;

                case 1 :
                pieza[1].SetPosicion(pieza[1].GetPosicionX() + 2*LADO, pieza[1].GetPosicionY() - 2*LADO);
                pieza[2].SetPosicion(pieza[2].GetPosicionX() + 4*LADO, pieza[2].GetPosicionY() - 4*LADO);
                pieza[3].SetPosicion(pieza[3].GetPosicionX() + 6*LADO, pieza[3].GetPosicionY() - 6*LADO);


                estado = 0;
                break;

              }

      break;

  }

}

/*
DESCRIPCIÓN DEL METODO COLISIONENTREPIEZAS: Recibe una pieza, como no tenemos sobrecargado el operador [] para pieza, no podemos hacer pieza1[], por tanto
usamos p = ObtieneParticula(i). Comparamos cada una de las particulas de la pieza instanciada con la pieza que le pasamos. Si hay colisión, ponemos el Estado
de todas las particulas a true, así las fijamos para que en el Mueve de Particula haga el filtro y no se muevan.
*/

bool ColisionEntrePiezas(Pieza pieza1){
  bool hay_colision =  false;

  Particula p;


  for(int i = 0; i< utiles; i++){ //4 porque solo hay cuatro particulas en cada pieza

    for(int j = 0; j< pieza1.GetUtiles(); j++){
        p = pieza1.ObtieneParticula(j);

        if(pieza[i].ColisionEntreParticulas(p)){
          hay_colision =  true;

          for(int k = 0; k < utiles; k++)
          pieza[k].SetEstado(hay_colision);

        }
    }
  }

  return hay_colision;

}


Particula ObtieneParticula(int posicion)const{

  return pieza[posicion];

}

void BorraParticula(int posicion){

pieza[posicion].SetColor(NEGRO);
pieza[posicion].SetPosicion(1500,1500);





}



  void MuevePieza(int ancho, int alto, int t){

    bool estafija = false;
    int cont = 0;
    bool limiteIZQ = false;
    bool limiteDECH = false;

    if(piezafija == false){

            for(int i =0; i< utiles; i++){
                if(pieza[i].GetPosicionX() <= LADO)
                  limiteIZQ = true;

                if(pieza[i].GetPosicionX() >= ancho - LADO)
                  limiteDECH = true;
                }
                    if( (limiteIZQ == true && (t == IZQUIERDA || t == ESPACIO)) || (limiteDECH == true && (t == DERECHA || t == ESPACIO)))
                      for(int i = 0; i<utiles; i++)
                        pieza[i].MueveParticula(ancho,alto, 89);

                      else
                        for(int i = 0; i< utiles; i++)
                          pieza[i].MueveParticula(ancho,alto,t);

                      if(t ==  ESPACIO && limiteIZQ == false && limiteDECH == false)
                        RotarPieza();
                }





        for(int j =0; j< utiles; j++){

        if(pieza[j].GetEstado() == true){
            estafija =  true;

            for(int j = 0; j< utiles; j++)
                pieza[j].SetEstado(estafija);

                SetEstadoPieza(estafija);
        }

    }
}


  void PintaPieza(){

    for(int i = 0; i < utiles; i++)
      pieza[i].PintaParticula();



  }


};


class Tetris {
private:
  int utilestetris;
  Pieza *tetris;
  int puntuacion;
  bool hay_megalinea;
  bool game_over;

  void ReservaMemoriaTetris(){
    tetris = new Pieza[utilestetris];
  }
  void LiberaMemoriaTetris(){
    if(tetris!=0)
      delete[] tetris;
  }

  void CopiarTetris(const Tetris &tetris1){

    utilestetris = tetris1.GetUtilesTetris();
    puntuacion = tetris1.GetPuntuacion();
    hay_megalinea = false;
    game_over = false;
      ReservaMemoriaTetris();
      Pieza p;

        for(int i = 0; i< utilestetris; i++){
          p = tetris1.ObtienePieza(i);
          tetris[i] = p;

        }

}

public:
  Tetris (){//Constructor por defecto
    utilestetris = 1;
    puntuacion = 0;
    tetris = 0;
    hay_megalinea = false;
    game_over = false;
    ReservaMemoriaTetris();
  }

  Tetris (int numero_piezas){ //Constructor con parámetros
    utilestetris = numero_piezas;
    puntuacion = 0;
    tetris = NULL;
    hay_megalinea = false;
    game_over = false;

  }


Tetris(const Tetris &tetris1){ //Constructor de copia

CopiarTetris(tetris1);


}

 ~Tetris (){ //Destrutor
   LiberaMemoriaTetris();
   vcierra();
 }


Tetris &operator=(const Tetris &tetris1){

  if(&tetris1 != this){

  				delete [] this->tetris;
  				CopiarTetris(tetris1);
  			}

  			return *this;


}


int GetUtilesTetris()const{

  return utilestetris;

}

int GetPuntuacion()const{

  return puntuacion;

}

 void SetUtilesTetris(int utils){

    utilestetris = utils;
 }

 bool GetGameOver(){

   return game_over;

 }

 void RedimensionaTetris(){
   int tam = utilestetris + 1;

   Pieza *auxiliar = new Pieza[tam];

     for(int i=0;i<utilestetris;i++)
       auxiliar[i] = tetris[i];


     if(tetris!=0)
       delete [] tetris;

     tetris = auxiliar;
    SetUtilesTetris(tam);

 }

 Pieza ObtienePieza(int posicion)const {

   return tetris[posicion];

 }



 void AgregaPieza(){

static int contador = 0;

   		RedimensionaTetris();


   		Pieza nueva_pieza;
      if( nueva_pieza.GetID() == tetris[contador].GetID() && nueva_pieza.GetID() != 7)
        nueva_pieza.SetID(7);

      nueva_pieza.OrdenaPieza();
   		tetris[utilestetris-1] = nueva_pieza; //¿Faltará el operador de asignación?
      //Sí, faltaba el operador de asignación


 }

 bool GetEstadoPiezaTetris(int posicion)const{

   bool estado;
    estado = tetris[posicion].GetEstadoPieza();

    return estado;

 }

void BajaTodoTetris(int limite){

  for(int i = 0; i < utilestetris; i++){

    tetris[i].BajaTodo(limite);

  }

}




void OrdenaPiezaTetris(){

  for(int i = 0; i< utilestetris; i++)
    tetris[i].OrdenaPieza();

}


//Métodos de gestión de colisiones

/*
DESCRIPCION METODO COLISION TETRIS: Este metodo engloba a los otros metodos de colisiones, tanto para particula como para pieza. Compara pieza con pieza
del tablero para ver si hay colisión. Si hay colision, fija esa pieza al estado true;

*/

void ColisionTetris(){ //Método modifica y aplica colisiones

  bool hay_colision;

  if(utilestetris >= 2){
    for(int i = 0 ; i < utilestetris -1 ; i++){
      //  if(tetris[utilestetris - 1].GetEstadoPieza() == false && tetris[i].GetEstadoPieza() == true )
            hay_colision = false;
              if(tetris[utilestetris -1].ColisionEntrePiezas(tetris[i])){
                hay_colision = true;
                tetris[utilestetris -1].SetEstadoPieza(hay_colision);
              }
      }

  }

}

/*
  DESCRIPCION METODO HAYLINEA :  Sabemos que el máximo de particulas que caben en el ancho es 18. Esto lo podríamos modificar y ajustar para distintos
  anchos etc, pero de momento lo voy a hacer así, ya que es complicado ajustar los cuadrados para que no parezcan que se salen del ancho. La cosa es
  hacer un contador y que si llega a 18, devuelve true. Hemos de almacenar la pieza tetris[i] en algún vector, así como la partícula[j] en otro, PARA
  después eliminar dichas particulas
*/



void HayLinea(int ancho, int alto){

int contador = 0;
int limiteY = 0;
int piezasafectadas[15] = {0};
int indicepieza = 0;
int vector[15]={0};
int indiceparticula = 0;
int megalinea = 0;


   //4 porque solo hay 4 particulas en cada pieza. Podría ser tetris[i].GetUtiles() etc
int count = 0;

  for(int i = 0; i<utilestetris; i++){ //Para cada pieza

    for(int k= 0; k<tetris[i].GetUtiles(); k++){ //Para cada particula de la pieza
        contador = 0;
        indicepieza = 0;
        indiceparticula = 0;

        if(megalinea >= 2){

          hay_megalinea = true;


        }

      for(int j = i; j<utilestetris; j++){ // Compara con todas las piezas

          for(int z = 0; z< tetris[j].GetUtiles(); z++){ //Compara con todas las particulas
              //Ahora solo compara segun las condiciones. Una de las más importantes es que las particulas que comparen esten dentro del ancho y alto, ya que las que desechemos van a ir fuera de la pantalla, y no queremos comparar con esas, ya que estariamos usando recursos tontamente


              if(tetris[i].ObtieneParticula(k).GetPosicionY() == tetris[j].ObtieneParticula(z).GetPosicionY() && tetris[i].GetEstadoPieza() == true && tetris[j].GetEstadoPieza()== true && (tetris[i].ObtieneParticula(k).GetPosicionX()<=ancho) && (tetris[j].ObtieneParticula(z).GetPosicionX() <= ancho)){


                  contador ++;
                  piezasafectadas[indicepieza] = j;
                  vector[indiceparticula] = z;

                  indicepieza++;
                  indiceparticula++;

                  if(contador == 15){

                    megalinea++;
                    limiteY = tetris[i].ObtieneParticula(k).GetPosicionY();
                    tetris[i].ObtieneParticula(k).SetPosicionY(0);
                    for(int i = 0; i< contador; i++){

                      tetris[piezasafectadas[i]].BorraParticula(vector[i]);

                      }
                      //cout << limiteY<<"\n";

                      BajaTodoTetris(limiteY);

                        puntuacion+=10;
                      }

                        }
                    }
                  }

                  }
              }


            }








void MueveTetris(int ancho, int alto, int t){

static int contador = 0;
  HayLinea(ancho, alto);
  ColisionTetris();
  for(int i = 0; i< utilestetris; i++){
    tetris[i].MuevePieza(ancho,alto,t);


     if(GetEstadoPiezaTetris(contador) == true){
        AgregaPieza();
        contador++;

      }
    }

    for(int j = 0; j< utilestetris; j++)
      for(int k = 0; k<tetris[j].GetUtiles(); k++)
        if(tetris[j].ObtieneParticula(k).GetPosicionY() <= LADO && tetris[j].ObtieneParticula(k).GetEstado() == true)
          game_over = true;


}



void PintaTetris(int anchoju,int ancho, int alto){
  for(int i = 0; i< utilestetris; i++)
    tetris[i].PintaPieza();

    color(VERDE);
		linea(anchoju,0,anchoju,alto);
    color(BLANCO);
    texto((ancho-(anchoju/3)),alto/2,"  SCORE : "+to_string(puntuacion));

    if(hay_megalinea == true){

      puntuacion *=2;

      for(int i = 0; i <= alto-200; i++){
			texto(ancho/2, i, "MEGALINEA");
      texto(ancho/2, i+30, "SORE*2");
			refresca();
			espera(4);
			borra();
		}
    hay_megalinea = false;


    }
}

void LetsPlay(int ancho,int alto){
		int m=tecla();
		refresca();
		while(m!=ESPACIO){

			color(BLANCO);
			texto(ancho/3 +50,alto/3,"Pulsa ESPACIO para Jugar");
      texto(ancho/3 +50,alto/3 + 50,"INSTRUCCIONES");
      texto(ancho/3 +50,alto/3 + 70,"Pulsa ESPACIO para rotar la pieza");
      texto(ancho/3 +50,alto/3 + 90,"Mueve las piezas con las flechas de dirección");
			refresca();
			espera(25);
			m=tecla();


    }

}


void TextoGameOver(int ancho, int alto){

  color(BLANCO);

  texto(ancho/3 +50,alto/3,"GAME OVER");
  texto(ancho/3 +50,alto/3 +30,"SOCRE: " +to_string(puntuacion));
  texto(ancho/3 +50,alto/3 + 60,"Pulsa ESCAPE para salir");


}



};



int main(){

  int ancho, alto, anchojuego;
  anchojuego = 360;
  ancho = 520;
  alto = 600;

  srand(time(0));

  vredimensiona(ancho,alto);

  Tetris principio;
  principio.OrdenaPiezaTetris();



  principio.LetsPlay(anchojuego,alto);
	int t = tecla();
	refresca();


    int contador = 0; //numero de veces que ha recorrido el while del main
    //int t = tecla();

  	while(t != ESCAPE && principio.GetGameOver() != true){

    borra();


    if(t == NINGUNA && contador > 15){
      contador = 0;
      principio.MueveTetris(anchojuego,alto,ABAJO);
      principio.PintaTetris(anchojuego,ancho,alto);
      }
    else{
    principio.MueveTetris(anchojuego,alto,t);
    principio.PintaTetris(anchojuego,ancho,alto);
    }


    refresca();
 	  espera(25);
    contador++;
    t = tecla();



  }

  borra();
  refresca();
  t = tecla();

  while(t!= ESCAPE){

    principio.TextoGameOver(ancho,alto);

    t = tecla();


  }






  return 0;

}
