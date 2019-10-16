#include <iostream>
#include <ctime>
#include <vector>
#include <string>
using namespace std;
typedef vector<vector<int>> MATRIX;
void print(MATRIX matrix, MATRIX checkmatrix);
void create(MATRIX &matrix, bool is_random);
void check(MATRIX &matrix, MATRIX &checkmatrix,bool &verificar );
void change(MATRIX &matrix,MATRIX &checkmatrix, int f1, int c1,int n_new);
int count_rows(MATRIX &matrix, int n, int i);
int count_cols(MATRIX &matrix, int n, int j);
int count_square(MATRIX &matrix, int n, int i, int j);

int main() {
    vector<vector<int>> matrix;
    vector<vector<int>> checkmatrix;
    create(matrix, true);
    create(checkmatrix, false);
    bool verificar=false;
    check(matrix, checkmatrix, verificar);
    print(matrix, checkmatrix);
    do{
      int f1,c1,n_new;
      cout<<"Ingrese fila a cambiar:";
      cin>>f1;
      cout<<"Ingrese columna a cambiar:";
      cin>>c1;
      cout<<"Ingrese nuevo valor:";
      cin>>n_new;
      change(matrix, checkmatrix, f1, c1,n_new);
      check(matrix, checkmatrix, verificar);
      print(matrix, checkmatrix);
    }while (verificar==false);
    cout<<"Adios!!";
}
void change(MATRIX &matrix,MATRIX &checkmatrix, int f1, int c1,int n_new){
    matrix[f1][c1]=n_new;
    for(int i=0; i<matrix.size(); i++){
        for(int j=0; j< matrix[i].size(); j++ ){
    checkmatrix[i][j]=0;}}
}

void check(MATRIX &matrix,MATRIX &checkmatrix, bool &verificar ){
    int verify=0;
    for(int i=0; i<matrix.size(); i++){
        for(int j=0; j< matrix[i].size(); j++ ){
            if(count_rows(matrix, matrix[i][j], i) > 1){
                checkmatrix[i][j] = 1;
                verify++;
            }
            if(count_cols(matrix, matrix[i][j], j) > 1){
                checkmatrix[i][j] = 2;
                verify++;
            }
            bool no_es_borde=i<matrix.size()-1 && j<=matrix[0].size()-1;
            if( no_es_borde && count_square(matrix, matrix[i][j],i,j) > 1){
                checkmatrix[i][j] = 3;
                verify++;
            }
        }
    }
    if (verify==0){
      verificar=true;
    }
}

//Cuenta cuantas veces se repite el numero n en la fila i
int count_rows(MATRIX &matrix, int n, int i){
    int n_rows=0;
    for(int j=0; j<matrix.size(); j++){
        if (matrix[i][j]==n){
            n_rows++;
        }
    }
    return n_rows;
}
//Cuenta cuantas veces se repite el numero n en region (i-1, j-1) a (i+1, j+1)
int count_square(MATRIX &matrix, int n, int i, int j){
    int n_rows=0;
    for(int k=i/3*3; k<(i/3*3)+3; k++){
        for (int l=j/3*3;l<(j/3*3)+3; l++){
            if (matrix[k][l]==n){
                n_rows++;
            }
        }
    }
    return n_rows;
}

//Cuenta cuantas veces se repite el numero n en la columna j
int count_cols(MATRIX &matrix, int n, int j){
    int n_columns=0;
    for(int i=0; i<matrix.size(); i++){
        if (matrix[i][j]==n){
            n_columns++;
        }
    }
    return n_columns;
}

//Crea una matrix de 9 filas y 9 columnas.
// Si rand es true los valores de la matriz serán aleatorios
// Si rand es false los valores de la matriz serán cero.
void create(MATRIX &matrix, bool is_random){
    srand(time(nullptr));
    int filas=9, columnas =9;
    for(int i=0;i<filas;i++){
        vector<int> fil = vector<int>(columnas,0);
        if (is_random == true){
            for(int j=0;j<columnas; j++){
                fil[j] = 1+rand()%9;
            }
        }
        matrix.push_back(fil);
    }
}

//Muestra la matriz en pantalla.  El elemento será
// rojo si se repite en la fila
// azul si se repite en la columna
// verde si se repite en la región de 3x3.
void print(MATRIX matrix, MATRIX checkmatrix){
    for(int i=0;i<matrix.size();i++){
        if (i==0){
            cout<<"\t";
            for(int i=0;i<matrix.size();i++){
              cout<<i<<"\t";
              if ((i+1)%3==0 && i!=0 ){
                  cout<<"\t";
              }
            }
            cout<<endl;
        }
        if (i%3==0 ){
            cout<<"  -------------------------------------------"<<endl;
        }
        for(int j=0; j<matrix[i].size(); j++){
            if (j==0  ){
                cout<<i;
            }
            if (j%3==0 ){
                cout<<"|   ";
            }
            if(checkmatrix[i][j] == 1){
                cout << "\033[1;41m" <<matrix[i][j]<<"\033[0;0m"<<"\t";
            }else if(checkmatrix[i][j] == 2){
                cout << "\033[1;44m"<<matrix[i][j]<<"\033[0;0m"<<"\t";
            }else if(checkmatrix[i][j] == 3){
                cout <<"\033[1;42m"<<matrix[i][j]<<"\033[0;0m"<<"\t";
            }else{
                cout<<matrix[i][j]<<"\t";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}
