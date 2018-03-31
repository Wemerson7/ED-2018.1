#include <lib/pen.h>
//QUADRADO COM CIRCULO
void linha(Pen &p, int lado, int rotacao){
    if(lado < 1)
        return;
    //p.setColor(rand()%255, rand()%255, rand()%255);

    p.walk(lado);
    p.right(90 * rotacao);
    //linha(p, lado - 5, 1);

    p.setColor(rand()%255, rand()%255, rand()%255);
    linha(p, lado - 5, -1);
}
//EMBUÁ recursivo
void embua(Pen& p, int lado){
    if(lado < 20)
        return;
        p.setColor(sf::Color::Green);
        p.walk(lado);
        p.right(90);
        embua(p, lado - 20);
        p.left(90);
        p.setColor(sf::Color::Yellow);
        p.walk(- lado);

}
//TRIANGULO
void triangulo(Pen& p, int lado){
    if(lado < 10)
        return;
    for(int i=0;i<3;i++){
         p.walk(lado);
         p.left(120);
         triangulo(p, lado/2);
    }
}
//ESPIRAL AINDA ESTOU TENTANDO FAZER
void circulos(Pen& p,int lado, int rotacao){
    if(lado < 1)
           return;
    p.circle(100);

}
//FLOR
void flor(Pen& p, int lado){
    if(lado < 10){
        return;
    }
    for (int i=0;i<5;i++) {     //PARA TER 5 LINHAS
        p.walk(lado);
        flor(p,lado/3);         //FAZER A RECURSÃO ANDANDO 1/3 DO LADO
        p.walk(-lado);
        p.left(144);
    }


}
//QUADRADOS AINDA ESTOU TENTANDO FAZER
void quadrado(Pen& p,int lado){
    if(lado<10){
        return;
    }
    for(int i=0;i<4;i++){
        p.walk(lado*2);               //ANDAR A QTD QUE FOI PASSADA NO LADO
        p.right(90);
    }
    for(int i=0;i<4;i++){
        quadrado(p,lado/2);
        p.left(90);
    }

}
//TRIGO
void trigo(Pen&p, int lado){
    if(lado<=0){
        return;
    }
  for(int i=0;i<4;i++){
        p.walk(lado);       //ANDA A DISTANCIA LADO
        p.right(45);        //VIRA 45 PARA FAZER UMA FOLHA
        trigo(p,lado/3);    //FAZ A RECURSAO PARA FAZER AS FOLHAS DE CIMA
        p.left(90);         //VIRA 90 PARA A ESQUERDA PARA POSICAO INICIAL
        trigo(p,lado/3);
        p.right(45);
  }
    p.walk(-lado*4);        //VOLTA PARA A POSICAO INICIAL DO TRIGO
}
//ARVORE
void arvore(Pen& p, int lado){
    float ang= 30.0;
    float dec =17;
    lado -= (p.rand() % 4 - 3);     //PARA QUE CADA GALHO TENHA TAMANHOS DIFERENTES

    if(lado < 10)                   //QUANDO LADO FOR MENOR Q 10, RETORNA
        return;



    p.setColor( sf::Color::White);
    p.setThickness(7);          //MUDAR EXPESSURA DO DESENHO
    p.walk(lado);               //ANDAR A QTD QUE FOI PASSADA NO LADO
    p.right(ang);               //GIRAR DIRETA NO ANGULO PASSADO

    p.setThickness(3);          //MUDAR A EXPESSURA DO DESENHO
    arvore(p,lado-dec);         //RECURSAO
    p.left(ang);                //GIRAR PARA ESQUERDA NESSE ANGULO


    arvore(p,lado-dec);
    p.left(ang);

    arvore(p,lado-dec);
    p.right(ang);




    p.setColor(sf::Color::Green); //MUDAR DE COR
    p.walk(-lado);                //FAZER O CAMINHO REVERSO


}
//FRACTAL
void fractal(){
    Pen p(800, 600);
    //coloca o pincel na posicao x 300 y 500
    p.setXY(400, 450);

    //faz o pincel apontar pra direita
    p.setHeading(90);
    //se speed = 0 entao ele faz o mais rapido possivel
    //se foi a partir de 1 ele controla a velocidade
    p.setThickness(3);
    p.setSpeed(90);
//    p.circle(200);
    //espera clicar no botao de fechar


//    linha(p, 100,1);
//    embua(p,300);
//    p.clear();

//    p.setHeading(120);
//    triangulo(p,300);
//    p.setHeading(90);
//    p.clear();

//    arvore(p,100);
//    p.clear();

//    flor(p,80,60);
//    p.clear();

//    trigo(p,80);
//    circulos(p,100,5);
//    quadrado(p,100);

    p.wait();
}

int main(){
    fractal();
    return 0;
}
