#include "libs/ed_base.h"
#include "libs/ed_mat.h"


#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm> //random_shuffle

using namespace std;

const char PAREDE = 'k';
const char ABERTO = 'w';
const char EMBUSCA = 'y';
const char CAMINHO = 'b';
const char ABATIDO = 'm';

void showMat(matchar& mat, vector<Par> pilha, Par inicio, Par fim){
    mat_draw(mat);
    for(Par par : pilha)
        mat_focus(par, 'c');
    if(pilha.size() > 0)
        mat_focus(pilha.back(), 'k');
    mat_focus(inicio, 'g');
    mat_focus(fim, 'r');
}


vector<Par> getNeib(Par par){
    vector<Par> vizinhos;
    vizinhos.push_back(Par(par.l + 1, par.c));
    vizinhos.push_back(Par(par.l - 1, par.c));
    vizinhos.push_back(Par(par.l, par.c + 1));
    vizinhos.push_back(Par(par.l, par.c - 1));
    return vizinhos;
}

int countOpen(matchar &mat, Par par){
    int cont = 0;
    for(auto vizinho : getNeib(par))
        if(!mat.is_inside(vizinho) || mat.get(vizinho) != PAREDE)
            cont++;
    return cont;
}

vector<Par> shuffle(vector<Par> vet){
    std::random_shuffle(vet.begin(), vet.end());
    return vet;
}

bool findPath(matchar& mat, Par inicio, Par final){
    vector<Par> pilha;
    pilha.push_back(inicio); //PRIMEIRO ELEMENTO NA PILHA É O INICIO
    mat.get(inicio) = EMBUSCA;//MARCA O INICIO

    while(pilha.size() != 0){//ENQUANTO TIVER ALGUEM NA PILHA FAÇA ISSO
        Par topo = pilha.back();//TOPO VAI SER O ULTIMO ELEMENTO NA PILHA
        if(topo == final){//SE FOR ACABOU, É FESTA
            showMat(mat, pilha, inicio, final);
            ed_show();
            return true;
        }
        //SE NAO FOR...
        vector<Par> viz_abertos;
        showMat(mat, pilha, inicio, final);
        for(Par par : getNeib(topo)){//PEGANDO TODOS OS VIZINHOS DO TOPO
            if(mat.get(par) == ABERTO){
                viz_abertos.push_back(par);//GUARDANDO OS VIZINHOS ABERTOS
                mat_focus(par, 'r');
            }
        }
        ed_show();
        if(viz_abertos.size() == 0){//SE NAO TIVER VIZINHO ABERTO
            pilha.pop_back();//DESIMPILHA DA PILHA
            showMat(mat, pilha, inicio, final);
            ed_show();
        }else{//SE TIVER
            Par escolhido = viz_abertos[rand() % viz_abertos.size()];//ESCOLHE UMA POSIÇÃO ALEATÓRIA
            mat.get(escolhido) = EMBUSCA;//E COMEÇA MARCANDO ELA
            pilha.push_back(escolhido);//E EMPILHANDO NA PILHA
            showMat(mat, pilha, inicio, final);
            ed_show();
        }
    }
    showMat(mat, pilha, inicio, final);
    ed_show();
    return false;
}

 void furar(matriz<char>& mat,Par inicio){
    vector<Par> pilha;
    pilha.push_back(inicio);//EMPILHANDO A PRIMEIRA COORDENADA NA PILHA
    mat.get(inicio)=ABERTO; //MARCAR O CAMINHO QUE PASSO

    while(pilha.size()!=0){
        vector<Par> podeSerFurado;
        Par topo = pilha.back(); //O TOPO VAI SER O ULTIMO VALOR DA PILHA
        for(auto vizinhos:getNeib(topo)) //PEGAR OS VIZINHOS DO TOPO
            if(countOpen(mat,vizinhos)<=1 && mat.equals(vizinhos,PAREDE)) //SABENDO QUEM SÃO OS VIZINHOS QUE PODEM SER ABERTOS
               podeSerFurado.push_back(vizinhos);//ADICIONANDO NUMA LISTA OS VIZINHOS Q PODEM SER FURADOS

        if(podeSerFurado.size()!=0){
            int vizinho = rand() % podeSerFurado.size(); //SORTEANDO ALGUMA PARA PEGAR OS VIZINHOS
            mat.get(podeSerFurado[vizinho]) = ABERTO;//MARCANDO O VIZINHO
            pilha.push_back(podeSerFurado[vizinho]);//EMPILHANDO ESSE VIZINHO NA PILHA
            mat_draw(mat);
            ed_show();
        }else{
            pilha.pop_back();//DESIMPILHA A PILHA
        }
    }
 }


int main(){
    srand(time(NULL));
    matchar mat(20, 15, PAREDE);
    furar(mat, Par(1,1));//chama a pilha
    Par inicio = mat_get_click(mat, "digite o local de inicio");
    Par final = mat_get_click(mat, "digite o local de fim");
    mat_draw(mat);
    ed_show();
    findPath(mat, inicio, final);
    ed_lock();//impede que termine abruptamente
    return 0;
}
