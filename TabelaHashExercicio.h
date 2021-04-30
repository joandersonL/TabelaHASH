#include <vector>
#include<iostream>
#include <functional>

using namespace std;

template <typename K, typename V>
class Tupla {
private:
	K chave;
	V valor;
	Tupla* prox;
public:
	Tupla(K c, V v) {
		chave = c;
		valor = v;
		prox = NULL;
	}

	K getChave() {
		return this->chave;
	}

	V getValor() {
		return this->valor;
	}

	Tupla* getProx() {
		return this->prox;
	}

	void setProx(Tupla* prox) {
		this->prox = prox;
	}
};

template <typename Chave, typename Valor>
class TabelaHash {

private:
	// Tupla<Chave, Valor>* tabela;
	vector <Tupla <int ,int >* > tabela;
	hash<Chave> minha_hash;
	//tamanho atual do array
	int qtde_buckets;
	//qtdade de elementos j� inseridos na tabela hash
	int tamanho;

	void inserir(Chave c, Valor v, vector <Tupla <Chave,Valor>* > &tabela) {
		if(!(this->qtde_buckets>=this->tamanho)){
			int codigo = abs(this-> minha_hash(c)) % this->qtde_buckets;
			if(this->tabela[codigo]==NULL){
				this->tabela[codigo]  = new Tupla <Chave ,Valor > (c,v);
				this->tamanho++;
			}else{
				inserir(c,v,this->tabela[codigo]->prox);
			}
		}else{
			aumentaArray();
			inserir(c,v,tabela);
		}

	}
	// void inserir(Chave c, Valor v, Tupla <Chave,Valor>*  t){
	// 	if(t == NULL){
	// 		t =  new Tupla <Chave ,Valor > (c,v);
	// 		this->tamanho++;
	// 	}else{
	// 		inserir(c,v,t->prox);
	// 	}
	// }


	void aumentaArray() {
		this->qtde_buckets = this->qtde_buckets *  8;
		//Criando nova tabela
		std::vector< Tupla <Chave,Valor> * >  TN ;
		for(int i=0;i<this->qtde_buckets;i++){
			for(int i=0;i<this->qtde_buckets;i++){
				this->TN.push_back(NULL);
			}
		}
		//Adicionando as tuplas a nova tabela
		for(int i = 0; i<(this->qtde_buckets/8);i++){
			addTupla(this->tabela[i],TN);
		}
		this->tabela.clear();
		this->tabela = TN;
	}

	void addTupla(Tupla <Chave,Valor>* t,vector <Tupla <Chave,Valor>* > &TN){

		if(t!=NULL){
			int codigo = abs(this-> minha_hash(t->getChave()) ) % this->qtde_buckets
			if(TN[codigo]==NULL){
				TN[codigo]  = new Tupla <Chave ,Valor > (t->getChave(),t->getValor());
			}else{
				addTupla(t,TN[codigo]->getProx());
			}
		}
	}
	addTupla(Tupla <Chave,Valor>*  t,Tupla <Chave,Valor>*  t2){
		if(t2==NULL){
			t2 = new Tupla <Chave ,Valor > (t->getChave(),t->getValor());
		}else{
			addTupla(t,t2->getProx());
		}
	}


public:

	//construtor
	TabelaHash() {
		this->qtde_buckets = 1;
		this->tamanho = 0;
		for(int i=0;i<this->qtde_buckets;i++){
			this->tabela.push_back(NULL);
		}
	}
	TabelaHash(int qtde_buckets) {
		this->qtde_buckets = qtde_buckets;
		this->tamanho = 0;
		for(int i=0;i<this->qtde_buckets;i++){
			this->tabela.push_back(NULL);
		}
	}

	void inserir(Chave c, Valor v,Tupla <Chave,Valor>*  t) {
		if(t==NULL){
			t = new Tupla <Chave ,Valor > (c,v);
		}else{
			addTupla(c,v,t->getProx());
		}
	}

	void inserir(Chave c, Valor v) {
		if(!(this->qtde_buckets>=this->tamanho)){
			int codigo = abs(this-> minha_hash(c)) % this->qtde_buckets;
			if(this->tabela[codigo]==NULL){
				this->tabela[codigo]  = new Tupla <Chave ,Valor > (c,v);
				this->tamanho++;
			}else{
				this->inserir(c,v,this->tabela[codigo]->getProx());
				this->tamanho++;
			}
		}else{
			this->aumentaArray();
			this->inserir(c,v);
		}
	}

	/**
	* Essa fun��o retorna o fator de carga da Tabela Hash.
	**/
	double load_factor() {
		//IMPLEMENTAR
		return this->qtde_buckets/double (this->tamanho);
	}

	/**
	* H� apenas um valor associado a uma chave.
	* Essa fun��o retorna esse valor, caso a chave exista.
	* Se a chave n�o existir a fun��o retorna NULL.
	* Lembre-se: em caso de colis�o, � preciso navegar
	* no bucket (lista ligada) para ter certeza se a chave
	* existe ou n�o.
	**/
	Valor getValor(Chave chave) {
		//IMPLEMENTAR
		int codigo = abs(this-> minha_hash(chave)) % this->qtde_buckets;
		Tupla <Chave,Valor>*  t  = this->tabela[codigo];
		while(1){
			if(t!=NULL){
				if(t->getChave()==chave){
					return  t->getValor();
				}
			}else{
				return NULL;
			}
			t = t->getProx();
		}

	}

	/**
	* Essa fun��o retorna true caso a chave exista,
	* false caso contr�rio.
	* Lembre-se: em caso de colis�o, � preciso navegar
	* no bucket (lista ligada) para ter certeza se a chave
	* existe ou n�o.
	**/
	bool contemChave(Chave chave) {
		//IMPLEMENTAR
		int codigo = abs(this-> minha_hash(chave)) % this->qtde_buckets;
		Tupla <Chave,Valor>*  t  = this->tabela[codigo];
		while(1){
			if(t!=NULL){
				if(t->getChave()==chave){
					return  true;
				}
			}else{
				return false;
			}
			t = t->getProx();
		}
	}

	/**
	* Essa fun��o retorna um vetor com todas as chaves
	* j� inseridas na tabela.
	**/
	vector<Chave> getChaves() {
		//IMPLEMENTAR
		std::vector<chave> v;
		for(int i=0;i<this->qtde_buckets;i++){
			addChave(this->tabela[i],v);
		}
		return v;
	}
	void addChave(Tupla <Chave,Valor>*  t,vector<Chave> &v){
		if(t!=NULL){
			v.push_back( t->getChave());
			addChave(t->getProx(),v);
		}
	}
	void clear() {
		//IMPLEMENTAR
	}

	void remover(Chave chave) {
		//IMPLEMENTAR
		int codigo = abs(this-> minha_hash(chave)) % this->qtde_buckets;
		Tupla <Chave,Valor>*  t  = this->tabela[codigo];
		remover(chave,t);
	}
	void remover(Chave chave,Tupla <Chave,Valor>*  t){
		if(t!=NULL){
			if(t->getChave()==chave){
				t = t->getProx();
			}else{
				remover(chave,t->getProx());
			}
		}
	}

	int size() {
		return tamanho;
	}

	/**
	* Essa fun��o retorna o tamanho atual do
	* array usado para armazenar a Tabela Hash.
	**/
	int bucket_count() {
		return qtde_buckets;
	}
};
