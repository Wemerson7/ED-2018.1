#include <iostream>
#include <list>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "sftext.h"

using namespace std;

struct Ambiente{
    list<char> texto;
    list<char>::iterator cursor;
    Ambiente(){
        cursor = texto.end();
    }

    string toString(){
        stringstream ss;
        for(auto it = texto.begin(); it != texto.end(); it++){
            if(it == cursor)
                ss << "|";
            ss << (*it);
        }
        if(cursor == texto.end())
            ss << "|";
        return ss.str();
    }
};

int main()
{
    Ambiente amb;
    amb.texto.push_back('a');
    amb.texto.push_back('m');
    amb.texto.push_back('o');
    amb.texto.push_back('r');

    sf::RenderWindow janela(sf::VideoMode(800, 600), "Janela");

    vector<Ambiente> pilha1;
    vector<Ambiente> pilha2;

    while(janela.isOpen()){

        sf::Event event;
        while(janela.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                janela.close();
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Z){
                    if(event.key.control){
                        if(pilha1.size()!= 0){
                        cout << "control z" << endl;
                        amb = pilha1.back(); //
                        pilha1.pop_back();
                        pilha2.push_back(amb);
                        }
                      //e uma pilha que guarda as acoes do ctrl z
                    //fazer uma pilha que guarda as acoes pra depois só voltar
                    }
                 }
                else if(event.key.control && (event.key.code == sf::Keyboard::R)){
                    cout << "control r" << endl;
                    if(pilha2.size()!= 0){
                        amb = pilha2.back();
                        pilha2.pop_back();
                    }
                }
                else if((event.key.code >= sf::Keyboard::A) &&
                   (event.key.code <= sf::Keyboard::Z)){
                    char tecla = (event.key.code - sf::Keyboard::A) + 'a';
                    cout << tecla << endl;
                    pilha1.push_back(amb); //
                    amb.texto.insert(amb.cursor,tecla);
                }
                else if((event.key.code == sf::Keyboard::Space)){
                    cout << "espaco" << endl;
                     amb.texto.insert(amb.cursor,' ');
                }
                else if(event.key.code == sf::Keyboard::BackSpace){
                    cout << "backspace" << endl;

                    if(amb.texto.begin()!= amb.cursor){

                    amb.texto.erase(amb.cursor++,amb.cursor--);

                   //arrumar isso
                    }

                }
                else if(event.key.code == sf::Keyboard::Return){
                    amb.texto.insert(amb.cursor, '\n');
                }
                else if(event.key.code == sf::Keyboard::Delete){
                    cout << "delete" << endl;
                    if(amb.cursor!=amb.texto.end()){
                        amb.texto.erase(amb.cursor++);
                    }
                }
                else if(event.key.code == sf::Keyboard::Left){
                    if(amb.cursor != amb.texto.begin()){
                        amb.cursor--;
                    }
                }
                else if(event.key.code == sf::Keyboard::Right){
                    if(amb.cursor != amb.texto.end())
                        amb.cursor++;
                }

            }
        }

        auto pos = sf::Vector2f(30, 50);
        janela.clear();
        janela.draw(sfText(pos, amb.toString(), sf::Color::White, 30));
        janela.display();
    }
    return 0;
}




