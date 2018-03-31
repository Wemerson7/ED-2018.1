#include "libs/ed_mat.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm> //random_shuffle

using namespace std;

int nlinhas = 20;
int ncolunas = 35;

const char PAREDE = 'k';
const char ABERTO = 'w';
const char CAMINHO = 'c';
const char EMBUSCA = 'r';


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
void furar(matchar &mat, Par par){
    if(!mat.equals(par, PAREDE) || countOpen(mat, par) > 1)
        return;
    mat.get(par) = FURADO;
    for(Par vizinho : shuffle(getNeib(par)))
        furar(mat, vizinho);
}


bool findPath(matchar& mat, Par atual, Par final){
       if(mat.get(atual) ==  final){
           mat.get(atual) = CAMINHO;
           return true;
       }
       if(mat.get(atual) != ABERTO){
           return false;
       }else{
           mat.get(atual) = EMBUSCA;


       }




}

#include <cstdlib>
#include <ctime>
int main(){
    srand(time(NULL));
    matchar mat(15, 20, PAREDE);
    furar(mat, Par(1, 1));//chama a função recursiva
    mat_draw(mat);
    ed_show();
    Par inicio = mat_get_click(mat, "digite o local de inicio");
    mat.get(inicio) = 'g';
    Par final = mat_get_click(mat, "digite o local de fim");
    mat.get(final) = 'r';
    mat_draw(mat);
    ed_show();
    ed_lock();//impede que termine abruptamente
    return 0;
}


