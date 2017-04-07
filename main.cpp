#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdio.h>

using namespace std;

struct item{
    int cpu,memoria;
};
struct peso{
    int cpu,memoria;
}P;

struct capacidade{
    int cpu,memoria;
}C;

vector< item > itens;
vector<item> bins;

void GerarItens(int num) {

	srand(time(0));
	for (int i = 0; i < num; ++i) {
          item it;

          it.cpu = (int) rand() % 10 + 1;
          it.memoria = (int) rand() % 10 + 1;


 		itens.push_back(it);
	}

}
bool ffdcomPesos(item &a, item &b){

        float valora = ((a.cpu * P.cpu) + (a.memoria * P.memoria));
        float valorb = ((b.cpu * P.cpu) + (b.memoria * P.memoria));

         return  valora > valorb;
}

bool ffdAVG(item &a, item &b){

        double valora = (a.cpu + a.memoria) / 2;
        double valorb = (b.cpu + b.memoria) / 2;

         return  valora > valorb;
}

bool ffdordenacaoAlan(item &a, item &b){

        float valora = abs(a.cpu - a.memoria);
        float valorb = abs(b.cpu - b.memoria);

         return  valora > valorb;
}


bool ordenaBin(item &a, item &b){
int capacidadea, capacidadeb;
        if(P.cpu >= P.memoria){
             capacidadea = (C.cpu - a.cpu);
             capacidadeb = (C.cpu - b.cpu);
        }else{
            capacidadea = (C.memoria - a.memoria);
            capacidadeb = (C.memoria - b.memoria);
        }
        //int capacidadea = (C.cpu - a.cpu) + (C.memoria - a.memoria);
        //int capacidadeb = (C.cpu - b.cpu) + (C.memoria - b.memoria);

        return capacidadea < capacidadeb;

}

bool compPor1nivel(item &a, item &b){
         return a.cpu > b.cpu;
}

bool ffdcomp(item &a, item &b){
         return a.cpu > b.cpu && a.memoria > b.memoria;
}

bool ffdprod(item &a, item &b){
         return a.cpu * a.memoria > b.cpu * b.memoria;
}

bool ffdsum(item &a, item &b){
         return a.cpu + a.memoria > b.cpu + b.memoria;
}

bool dotprod(item &a, item &b){
        int valora=0,valorb=0;

        for(int i=0; i < bins.size(); i++){
            int memr = C.memoria - bins[i].memoria;
            int cpur = C.cpu - bins[i].cpu;

            valora += (memr * a.memoria) + (cpur * a.cpu);
            valorb += (memr * b.memoria) + (cpur * b.cpu);
        }


         return valora > valorb;
}

int FirstFitBinDotProd() {
    bins.clear();
    cout << bins.size() << " ------------------" << endl;

    vector<item> itensc = itens;
    sort(itensc.begin(),itensc.end(),dotprod);
    bins.push_back(itensc[0]);
    itensc.erase(itensc.begin()+0,itensc.begin()+1);

    int i=0;
    //cout << endl;
    while( i < itensc.size()){
         sort(itensc.begin(),itensc.end(),dotprod);

        // cout << itensc[i].cpu << endl;
        for(int a=0;a<bins.size();a++){
            sort(bins.begin(),bins.end(),ordenaBin);
            if(itensc[i].cpu + bins[a].cpu <= C.cpu && itensc[i].memoria + bins[a].memoria <= C.memoria){
                //cout << i << " " << itens[i].cpu << " " << itens[i].memoria << endl;
                //cout << "Adicionou o elemento a o bin " << a <<endl;
                bins[a].cpu += itensc[i].cpu;
                bins[a].memoria += itens[i].memoria;
                itensc.erase(itensc.begin(),itensc.begin()+1);

                break;
            }else{
                if(a== bins.size() - 1){
                //cout << i << " " << itens[i].cpu << " " << itens[i].memoria << endl;
                //cout << "Criou um novo bin " << a + 1 << endl;
                    bins.push_back(itens[i]);
                    itensc.erase(itensc.begin(),itensc.begin()+1);
                break;
                }



            }

        }



    }

    cout << endl << "Quantidade de Bins: " << bins.size() << endl;
    int disperdiciom = 0, disperdicioc = 0;
	for(int i=0; i<bins.size(); i++){
        disperdicioc += C.cpu - bins[i].cpu;
        disperdiciom += C.memoria - bins[i].memoria;
	}
	cout << "Disperdicio de Espaco: \n Memoria:" << disperdiciom << "\n Cpu: " << disperdicioc << endl;



}

int FirstFitBinPacking1() {
   bins.clear();
    cout << bins.size() << " ------------------" << endl;
    bins.push_back(itens[0]);
    int i=1;
    //cout << endl;
    while( i < itens.size()){
         sort(bins.begin(),bins.end(),ordenaBin);
        for(int a=0;a<bins.size();a++){

            if(itens[i].cpu + bins[a].cpu <= C.cpu && itens[i].memoria + bins[a].memoria <= C.memoria){
                //cout << i << " " << itens[i].cpu << " " << itens[i].memoria << endl;
                //cout << "Adicionou o elemento a o bin " << a <<endl;
                bins[a].cpu += itens[i].cpu;
                bins[a].memoria += itens[i].memoria;

                break;
            }else{
                if(a== bins.size() - 1){
                //cout << i << " " << itens[i].cpu << " " << itens[i].memoria << endl;
                //cout << "Criou um novo bin " << a + 1 << endl;
                bins.push_back(itens[i]);

                break;
                }



            }

        }

      i++;

    }

    cout << endl << "Quantidade de Bins: " << bins.size() << endl;
    int disperdiciom = 0, disperdicioc = 0;
	for(int i=0; i<bins.size(); i++){
        disperdicioc += C.cpu - bins[i].cpu;
        disperdiciom += C.memoria - bins[i].memoria;
	}
	cout << "Disperdicio de Espaco: \n Memoria:" << disperdiciom << "\n Cpu: " << disperdicioc << endl;



}

int FirstFitBinPacking2() {


    bins.clear();
    cout << bins.size() << " ------------------" << endl;
    bins.push_back(itens[0]);
    int i=1;
    //cout << endl;
    while( i < itens.size()){
         //sort(itens.begin(),itens.end(),ordenaBin);
        for(int a=0;a<bins.size();a++){

            if(itens[i].cpu + bins[a].cpu <= C.cpu && itens[i].memoria + bins[a].memoria <= C.memoria){
                //cout << i << " " << itens[i].cpu << " " << itens[i].memoria << endl;
                //cout << "Adicionou o elemento a o bin " << a <<endl;
                bins[a].cpu += itens[i].cpu;
                bins[a].memoria += itens[i].memoria;

                break;
            }else{
                if(a== bins.size() - 1){
                //cout << i << " " << itens[i].cpu << " " << itens[i].memoria << endl;
                //cout << "Criou um novo bin " << a + 1 << endl;
                bins.push_back(itens[i]);

                break;
                }else{
                //cout << "Vai pro proximo Bin" << endl;
                }
            }

        }

      i++;

    }

    cout << endl << "Quantidade de Bins: " << bins.size() << endl;
    int disperdiciom = 0, disperdicioc = 0;
	for(int i=0; i<bins.size(); i++){
        disperdicioc += C.cpu - bins[i].cpu;
        disperdiciom += C.memoria - bins[i].memoria;
	}
	cout << "Disperdicio de Espaco: \n Memoria:" << disperdiciom << "\n Cpu: " << disperdicioc << endl;



}

int main()
{
    P.cpu = 2;
    P.memoria = 1;
    C.cpu = 200;
    C.memoria = 300;

    GerarItens(5000);


    clock_t tempo;

	tempo = clock();
    cout << "Desordenado: " <<endl;

   /*for(int c=0;c<itens.size();c++){
        cout << itens[c].cpu << "  " << itens[c].memoria << " | ";
    }*/
    FirstFitBinPacking2();
    printf("Tempo:%f \n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
    cout << "--------------------------------------" << endl;




    tempo = clock();
    cout << "FFD Ordenando sem os Bins e com Pesos: " <<endl;
    sort(itens.begin(),itens.end(),ffdcomPesos);
   /*for(int c=0;c<itens.size();c++){
        cout << itens[c].cpu << "  " << itens[c].memoria << " | ";
    }*/
    FirstFitBinPacking2();
     printf("Tempo:%f",(clock() - tempo) / (double)CLOCKS_PER_SEC);
    cout << "--------------------------------------" << endl;

    P.cpu = 5;
    P.memoria = 3;
     tempo = clock();
    cout << "FFD Ordenando sem os Bins e com Pesos Diferentes: " <<endl;
    sort(itens.begin(),itens.end(),ffdcomPesos);
   /*for(int c=0;c<itens.size();c++){
        cout << itens[c].cpu << "  " << itens[c].memoria << " | ";
    }*/
    FirstFitBinPacking2();
     printf("Tempo:%f",(clock() - tempo) / (double)CLOCKS_PER_SEC);
    cout << "--------------------------------------" << endl;

   /*  tempo = clock();
    cout << "FFD com Ordenacao pela Diferenca entre Coordenadas " <<endl;
    sort(itens.begin(),itens.end(),ffdordenacaoAlan);
   /*for(int c=0;c<itens.size();c++){
        cout << itens[c].cpu << "  " << itens[c].memoria << " | ";
    }*/
   /* FirstFitBinPacking2();
    printf("Tempo:%f \n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
    cout << "--------------------------------------" << endl;*/

     tempo = clock();
    cout << "FFD com uso de apenas um nivel de comparacao: " <<endl;
    sort(itens.begin(),itens.end(),compPor1nivel);
    /*for(int c=0;c<itens.size();c++){
        cout << itens[c].cpu << "  " << itens[c].memoria << " | ";
    }*/
    cout << endl << "Numeros de Bins:  ";
    FirstFitBinPacking2();
     printf("Tempo:%f \n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
    cout << "--------------------------------------" << endl;

    tempo = clock();
    cout << "FFD com uso de apenas dois niveis de comparacao mas sem pesos: " <<endl;
    sort(itens.begin(),itens.end(),ffdcomp);
    /*for(int c=0;c<itens.size();c++){
        cout << itens[c].cpu << "  " << itens[c].memoria << " | ";
    }*/
    cout << endl << "Numeros de Bins:  ";
    FirstFitBinPacking2();
    printf("Tempo:%f \n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
    cout << "--------------------------------------" << endl;


    tempo = clock();
    cout << "FFDAVG: " <<endl;
    sort(itens.begin(),itens.end(),ffdAVG);
    /*for(int c=0;c<itens.size();c++){
        cout << itens[c].cpu << "  " << itens[c].memoria << " | ";
    }*/
    cout << endl << "Numeros de Bins:  ";
    FirstFitBinPacking2();
    printf("Tempo:%f \n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
    cout << "--------------------------------------" << endl;

    tempo = clock();
    cout << "FFDprod: " <<endl;
    sort(itens.begin(),itens.end(),ffdprod);
    /*for(int c=0;c<itens.size();c++){
        cout << itens[c].cpu << "  " << itens[c].memoria << " | ";
    }*/
    cout << endl << "Numeros de Bins:  ";
    FirstFitBinPacking2();
    printf("Tempo:%f \n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
    cout << "--------------------------------------" << endl;



    tempo = clock();
    cout << "FFDSum: " <<endl;
    sort(itens.begin(),itens.end(),ffdsum);
    /*for(int c=0;c<itens.size();c++){
        cout << itens[c].cpu << "  " << itens[c].memoria << " | ";
    }*/
    cout << endl << "Numeros de Bins:  ";
    FirstFitBinPacking2();
    printf("Tempo:%f \n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
    cout << "--------------------------------------" << endl;


    /*tempo = clock();
    cout << "FFD Ordenando os Bins e com Pesos: " <<endl;
    sort(itens.begin(),itens.end(),ffdcomPesos);
   /*for(int c=0;c<itens.size();c++){
        cout << itens[c].cpu << "  " << itens[c].memoria << " | ";
    }*/
   /* FirstFitBinPacking1();
    printf("Tempo:%f \n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
    cout << "--------------------------------------" << endl;*/

    	tempo = clock();
    cout << "DotProd: " <<endl;

   /*for(int c=0;c<itens.size();c++){
        cout << itens[c].cpu << "  " << itens[c].memoria << " | ";
    }*/
    FirstFitBinDotProd();
    printf("Tempo:%f \n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
    cout << "--------------------------------------" << endl;


}
