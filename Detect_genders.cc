#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <time.h>
#include <sys/resource.h>
#include <bits/stdc++.h>


using namespace std;

/*****************************************************
Nombre funcion: tiempo(void)
Proposito: Calcular el tiempo de CPU de este proceso
(y sólo de este proceso)
Parametros de entrada: nada
Devuelve: El tiempo empleado en segundos
******************************************************/
long double
tiempoCPU(void){
 struct rusage usage;
 getrusage(RUSAGE_SELF,&usage);
 return( (long double) usage.ru_utime.tv_sec +
	 (long double) usage.ru_utime.tv_usec/1e6
	 /* + (long double) usage.ru_stime.tv_sec +
         (long double) usage.ru_stime.tv_usec/1e6 */
       );
}

void removeCharsFromString( string &str, char* charsToRemove ) {
   for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
      str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
   }
}

int main() {
	vector<int> times;
	vector<string> words;
	string word;
	ifstream file;
	system("pdftotext 360pgs.pdf");
  	file.open("360pgs.txt");
	long double init = tiempoCPU();
	if (file.is_open())
	{
		while (file >> word) 
		{
			bool in = false;
			if(word.length() > 2) 
			{
				for (int i = 0; i < word.length(); ++i)
				{
					//Cambia a minúscula
					if (word[i] <= 90 && word[i] >= 65)
					{
						word[i] += 32;
					} else if (word[i] == 144)
					{
						word[i] = 130;
					}
					if ((word[i] <= 96 && word[i] >= 33) || (word[i] >= 123 && word[i] <= 126) || (word[i] == 128) || (word[i] >= 131 && word[i] <= 143) || (word[i] >= 145 && word[i] <= 159/*Por aquiiii*/) || (word[i] >= 168 && word[i] <= 180) || (word[i] >= 184 && word[i] <= 223) || (word[i] > 224 && word[i] < 233) || (word[i] > 233 && word[i] < 255) )
					{
						word.erase(word.begin() + i);
					}
				}
				if (word.length() != 0)
				{	
					//Si words está vacío, empieza a llenarlo
					if(words.size() == 0) 
					{
						words.push_back(word);
						times.push_back(1);
					} else 
					{
						//Busca en el vector si está
						for (int i = 0; i < words.size(); i++) 
						{
							if (word == words[i]) 
							{
								times[i]++;
								in = true;
							}
						}
						//Si no está en los vectores lo añade como nuevo
						if (!in) 
						{
							words.push_back(word);
							times.push_back(1);
						}
					}
				}
			}
	    word.clear();
		}
	}
	for (int i = 0; i < words.size(); i++) 
	{
		cout<<words[i]<<" - "<<times[i]<<endl;
	}
	long double finish = tiempoCPU();

	cout<<endl<<endl<<"El programa ha tardado: "<<finish-init<<endl;
}
