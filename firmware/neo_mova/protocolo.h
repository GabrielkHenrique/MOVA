#pragma once
#include <cstddef>
#include <cstring>
namespace neo {
// Schema fechado: objeto com exatamente uma chave e um valor textual conhecidos.
// Parser limitado ao schema; sem alocações. Escapes ASCII JSON são aceitos.
struct LeitorComando {
 const char* p;const char* fim;
 void espacos(){while(p<fim&&(*p==' '||*p=='\n'||*p=='\r'||*p=='\t'))p++;}
 bool consumir(char c){espacos();if(p==fim||*p!=c)return false;p++;return true;}
 static int hex(char c){if(c>='0'&&c<='9')return c-'0';if(c>='a'&&c<='f')return c-'a'+10;if(c>='A'&&c<='F')return c-'A'+10;return -1;}
 bool texto(char (&destino)[16]){
  if(!consumir('"'))return false;
  size_t n=0;
  while(p<fim){
   unsigned char c=*p++;
   if(c=='"'){destino[n]=0;return true;}
   if(c=='\\'){
    if(p==fim)return false;
    c=*p++;
    if(c=='u'){
     unsigned codigo=0;for(int i=0;i<4;i++){if(p==fim)return false;int h=hex(*p++);if(h<0)return false;codigo=codigo*16+h;}
     // Nenhum nome do schema contém controles ou caracteres não ASCII.
     if(codigo<32||codigo>126)return false;
     c=codigo;
    }else if(c!='"'&&c!='\\'&&c!='/')return false;
   }
   if(c<32||c>126||n>=15)return false;
   destino[n++]=c;
  }
  return false;
 }
};
inline bool lerComando(const char* corpo,size_t tamanho,const char* chave,char (&valor)[16]){
 if(tamanho>128)return false;
 LeitorComando l{corpo,corpo+tamanho};char encontrada[16]{};
 if(!l.consumir('{')||!l.texto(encontrada)||std::strcmp(encontrada,chave)||!l.consumir(':')||!l.texto(valor)||!l.consumir('}'))return false;
 l.espacos();if(l.p!=l.fim)return false;
 if(!std::strcmp(chave,"modo"))return !std::strcmp(valor,"ligar")||!std::strcmp(valor,"desligar")||!std::strcmp(valor,"automatico");
 if(!std::strcmp(chave,"acao"))return !std::strcmp(valor,"iniciar")||!std::strcmp(valor,"pausar")||!std::strcmp(valor,"retomar")||
  !std::strcmp(valor,"calmo")||!std::strcmp(valor,"normal")||!std::strcmp(valor,"forca")||!std::strcmp(valor,"treino")||
  !std::strcmp(valor,"menu")||!std::strcmp(valor,"proximo")||!std::strcmp(valor,"chapeu");
 return false;
}
}
