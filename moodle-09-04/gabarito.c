#include <stdio.h>
#include <stdlib.h>

typedef struct s_noArv * noArv;
struct s_noArv{
	int ra;
	int nota;
	noArv esq;
	noArv dir;
};

noArv novoNoArv(int ra, int nota){
	noArv tmp = (noArv) malloc (sizeof(struct s_noArv));

	if(!tmp){
		return NULL;
	}

	tmp->ra = ra;
	tmp->nota = nota;
	tmp->esq = NULL;
	tmp->dir = NULL;

	return tmp;
}

void teste(noArv *raiz){
	if (*raiz == NULL){
		//printf("Árvore vazia\n");
		return;
	}

	if ((*raiz)->esq){
		printf("(%d, %d) <--", (*raiz)->esq->ra, (*raiz)->esq->nota);
	}else{
		printf("(null) <--");
	}
	printf(" (%d, %d) ", (*raiz)->ra, (*raiz)->nota);
	if ((*raiz)->dir){
		printf("--> (%d, %d)\n", (*raiz)->dir->ra, (*raiz)->dir->nota);	
	}else{
		printf("--> (null)\n");	
	}

	teste(&(*raiz)->esq);
	teste(&(*raiz)->dir);
}

//rotação simples a direita
void rotacaoSD(noArv *raiz){
	if (*raiz == NULL) return;
	noArv pai = *raiz;
	noArv filhoEsq = pai->esq;
	noArv netoDir = filhoEsq->dir;

	filhoEsq->dir = pai;
	pai->esq = netoDir;

	*raiz = filhoEsq;
}

//rotaçao simples a esquerda
void rotacaoSE(noArv *raiz){
	if (*raiz == NULL) return;

	noArv pai = *raiz;
	noArv filhoDir = pai->dir;
	noArv netoEsq = filhoDir->esq;

	filhoDir->esq = pai;
	pai->dir = netoEsq;

	*raiz = filhoDir;
}

//rotação dupla a direita
void rotacaoDD(noArv *raiz){
	if (*raiz == NULL) return;

	noArv pai = *raiz;
	noArv filhoEsq = pai->esq;
	noArv netoDir = filhoEsq->dir;

	pai->esq = netoDir;
	filhoEsq->dir = netoDir->esq;
	netoDir->esq = filhoEsq;

	rotacaoSD(raiz);
}

//rotação dupla a esquerda
void rotacaoDE(noArv *raiz){
	if (*raiz == NULL) return;

	noArv pai = *raiz;
	noArv filhoDir = pai->dir;
	noArv netoEsq = filhoDir->esq;

	pai->dir = netoEsq;
	filhoDir->esq = netoEsq->dir;
	netoEsq->dir = filhoDir;

	rotacaoSE(raiz);
}


//retorna o maior de 2 números
int max(int a, int b){
	return a > b ? a : b;
}

//mostra a altura de uma árvore
int alturaArv(noArv raiz){
	if (raiz == NULL){
		return -1;
	}
	int alturaEsq, alturaDir;
	alturaEsq = alturaArv(raiz->esq);
	alturaDir = alturaArv(raiz->dir);

	return max(alturaDir, alturaEsq) + 1;
}

//retorna o fator de balanceamento do nó
int fatorBalancNo(noArv raiz){
	if (raiz == NULL){
		return 0;
	}

	int alturaEsq, alturaDir;
	alturaEsq = alturaArv(raiz->esq);
	alturaDir = alturaArv(raiz->dir);

	return alturaEsq - alturaDir;
}

//escolhe a rotação
void rotacao(noArv *raiz){
	int fb;
	fb = fatorBalancNo(*raiz);

	if (fb > 1){ //rotação a direita

		printf("[No desbalanceado: %d]\n", (*raiz)->ra);		
		fb = fatorBalancNo((*raiz)->esq);

		if (fb  < 0){ 	//rotação dupla
			printf("[Rotacao: DD]\n");
			printf("[x=%d y=%d z=%d]\n", (*raiz)->esq->ra, (*raiz)->esq->dir->ra, (*raiz)->ra);
			rotacaoDD(raiz);

		}else{ //rotacao simples
			printf("[Rotacao: SD]\n");
			printf("[x=%d y=%d z=%d]\n", (*raiz)->esq->esq->ra, (*raiz)->esq->ra, (*raiz)->ra);
			rotacaoSD(raiz);
		}

	}else if (fb < -1){	//rotação a esquerda
		printf("[No desbalanceado: %d]\n", (*raiz)->ra);		
		fb = fatorBalancNo((*raiz)->dir);

		if (fb > 0){ //rotação dupla
			printf("[Rotacao: DE]\n");
			printf("[x=%d y=%d z=%d]\n", (*raiz)->ra, (*raiz)->dir->esq->ra, (*raiz)->dir->ra);
			rotacaoDE(raiz);

		}else{	//rotação simples
			printf("[Rotacao: SE]\n");
			printf("[x=%d y=%d z=%d]\n", (*raiz)->ra, (*raiz)->dir->ra, (*raiz)->dir->dir->ra);
			rotacaoSE(raiz);
		}
	}
}


//insere nó x na árvore
int flag = 0;
int flag2 = 0; //pra primeira inserção
void insereNoArv(noArv * raiz, noArv x){
	int fb;

	if ((*raiz) == NULL){
		*raiz = x;
	}
	//vai para direita
	if (x->ra > (*raiz)->ra){
		insereNoArv(&(*raiz)->dir, x);
	//vai para esquerda
	}else if (x->ra < (*raiz)->ra){
		insereNoArv(&(*raiz)->esq, x);
	//RA igual
	}else{
		(*raiz)->nota = x->nota;
	}

	//verifica se está balanceado
	fb = fatorBalancNo(*raiz);
	if (fb < -1 || fb > 1){ //desbalanceado
		flag = 1;
		rotacao(raiz);
	}
}

//Verifica se não houve rotação na op. de inserção ou remoção
void verificaBalanco(){
	if (flag == 0){
		printf("[Ja esta balanceado]\n");
	}
}

//remove nó com ra informado
noArv x = NULL; 
void removeNoArv(noArv *raiz, int ra){
	if (*raiz == NULL) return;

	//acha o nó a ser removido
	if (ra > (*raiz)->ra){ 	//vai pra sub arvore da direita
		removeNoArv(&(*raiz)->dir, ra);	
	}else if (ra < (*raiz)->ra){	//vai pra sub arvore da esquerda
		removeNoArv(&(*raiz)->esq, ra);
	}else{	//achei o nó

		noArv aux = *raiz;	//auxiliar
		if((*raiz)->dir && (*raiz)->esq){	//tem os dois filhos 

			//achar o menor à direita
			noArv prev = NULL;
			noArv tmp = (*raiz)->dir;
			while(tmp){
				prev = tmp;
				tmp = tmp->esq;
			}
			//copia os valores
			(*raiz)->ra = prev->ra;
			(*raiz)->nota = prev->nota;

			//remover o menor nó a direita
			removeNoArv(&(*raiz)->dir, prev->ra);

		}else{	//tem no máx um filho
			if ((*raiz)->dir){	//tem o filho da direita
				(*raiz) = (*raiz)->dir;
				free(aux); 

			}else if ((*raiz)->esq){	//tem o filho da esquerda
				(*raiz) = (*raiz)->esq;
				free(aux);
			}else{		//não tem filho
				free(aux);
				(*raiz) = NULL;
			}	
		}
	}

	//verifica se está balanceado
	int fb;
	fb = fatorBalancNo(*raiz);
	if (fb < -1 || fb > 1){ //desbalanceado
		flag = 1;
		rotacao(raiz);
	}
}

//busca um ra na arvore, imprime a nota e número de comparações
void buscaNoArv(noArv *raiz, int ra){	
	int numInteracoes = 0;
	noArv atual = *raiz;
	while(atual){
		if (ra > atual->ra){
			atual = atual->dir;
			numInteracoes++;
		}else if (ra < atual->ra){
			atual = atual->esq;
			numInteracoes++;
		}else{
			numInteracoes++;
			break;
		}
	}
	if (atual){
		printf("C=%d Nota=%d\n", numInteracoes, atual->nota);
	}else{
		printf("C=%d Nota=-1\n", numInteracoes);
	}
}

//imprime árvore em pós-ordem
void imprimePosOrdem(noArv *raiz){
	if (*raiz == NULL) return;
	imprimePosOrdem(&(*raiz)->esq);
	imprimePosOrdem(&(*raiz)->dir);
	printf("%d ", (*raiz)->ra);
}

int main(int argc, char const *argv[])
{
	char operation;
	int ra, nota, altura, fatorBalanc;
	noArv raiz = NULL;

	while(1){
		scanf("%c", &operation);
		switch(operation){
			case('I'):
				scanf("%d %d", &ra, &nota);
				flag = 0;
				insereNoArv(&raiz, novoNoArv(ra, nota));
				verificaBalanco();
				break;
			case('R'):
				scanf("%d", &ra);
				flag = 0;
				removeNoArv(&raiz, ra);
				verificaBalanco();
				break;
			case('B'):
				scanf("%d", &ra);
				buscaNoArv(&raiz, ra);
				break;
			case('A'):
				altura = alturaArv(raiz);
				printf("A=%d\n", altura);
				fatorBalanc = fatorBalancNo(raiz);
				break;
			case('T'):
				teste(&raiz);
				break;
			case('P'):
				printf("[");
				imprimePosOrdem(&raiz);
				printf("]\n");
				return 0;
		}
	}
}