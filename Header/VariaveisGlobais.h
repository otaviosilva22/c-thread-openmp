/*--- Vari�veis Globais e Structs ---*/

/*Tamanho st�tico m�ximo de linhas do arquivo txt*/
#define tam 50

/*Tamanho st�tico m�ximo de caracteres em cada linha*/
#define tamLinha 300

//quantidade de linhas
int qtdLinhas = 0;

//contador comparilhado
int contador = 0;

//quantidade de nucleos
long nprocs;

//palavra a ser pesquisada
char palavra[] = "";

/*Typedef para posi��es da fila*/
typedef int TipoApontador;

//Struct de linha
struct Linha{
	char conteudo[tamLinha];
};

/*Struct referente a fila, onde cada posi��o existe uma linha*/
struct Fila {
	struct Linha linha[tam];
	TipoApontador frente, tras;
};

