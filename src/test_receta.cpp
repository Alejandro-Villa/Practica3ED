#include "receta.h"
#include "recetas.h"
#include <fstream>
using namespace std;
int main(int argc,char *argv[]){
  if (argc!=2){
    cout<<"Dime el fichero con las recetas"<<endl;
    return 0;
  
  }
  ifstream f(argv[1]);
  if (!f){
	  cout<<"No existe el fichero "<<argv[1]<<endl;
  }
  /***********************************************************************/
  
  //SECTION 1: Test sobre TDA receta. Operadores de entrada y salida
  receta r;
  f>>r;
  cout<<"La receta leida es "<<r<<endl;
  cout<<"Pulse una tecla para continuar"<<endl;
  cin.get();
  /***********************************************************************/

  //Section 2: Comprueba el iterador de receta
  receta::iterator it;
  cout<<"Los ingredientes de la receta "<<r.getNombre()<<" son:"<<endl;
  for (it=r.begin();it!=r.end();++it){
	  cout<<(*it).first<<"\t"<<(*it).second<<"\t";
   }	  
   cout<<endl;
   cout<<"Total de ingredientes son "<<r.ningredientes()<<endl;
  cout<<"Pulse una tecla para continuar"<<endl;
  cin.get(); 
  
  f.seekg(0);
  /***********************************************************************/
  
  //SECTION 3: Test sobre TDA recetas. Operadores de lectura y escritura
  
  recetas rall;
  f>>rall;
  cout<<"Todas las recetas: "<<endl<<rall<<endl;
  cout<<"Numero de recetas "<<rall.size()<<endl;
  cout<<"Pulse una tecla para continuar"<<endl;
  cin.get(); 
  /***********************************************************************/
  
  //SECTION 4: Consultar una receta por codigo
  cout<<"Dime el codigo de una receta:";
  string c;
  cin>>c;
  if (rall[c].getNombre()!="Undefined"){
	  cout<<"La receta es "<<rall[c]<<endl;
  }
  else{
	  cout<<"La receta con codigo "<<c<<" no existe"<<endl;
  }
  /***********************************************************************/
  
  //SECTION 5: Borramos la receta con un código. Comprobamos el 
  //funcionamiento del iterador de recetas
  rall.borrar(c);
  cout<<"Tras el borrado "<<endl;
  recetas::iterator its;
  for (its=rall.begin();its!=rall.end();++its){
	cout<<*its<<endl;  
	  
  }
  cout<<endl;
  cout<<"Numero de recetas "<<rall.size()<<endl;
  

}
