#include <stdio.h>
#include <string.h>//bibilhoteca para trabalhar com strings
#include <time.h>//bibilhhoteca para trabalhar com a rolagem dos dados

typedef struct dados{//struct para jogadores
    char nome[50];//nome do jogador
    char cor[50];//cor das peças do jogador
    int peao[4];//vetor de 4 posiçoes, representando cada peao de cada jogador
    int saiu;


}dados;

int rolagem_de_dado(dados* jogador);//declaração da existencia das funçoes
void primeiraJogada(dados* jogador);
int verificar_casas_iguais_jogador1(dados* jogador1, dados* jogador2, int posicao);
int verificar_casas_iguais_jogador2(dados* jogador2, dados* jogador1, int posicao);
int casas_finais(dados* jogador, int posicao, int dado);
int final(dados* jogador, int posicao, int jog);
void print_peoes(dados* jogador, int valor);
void dado_seis(dados* jogador, int jog, dados jogador1, dados jogador2);
void inicio(char* nome1, char* nome2, dados* jogador1, dados* jogador2);
void Cor_jogador(dados* jogador);

int contagem_final[2] = {0,0};//variaveis de contagem final para cada jogador
int retorno_casas_finais;//variaveis globais que sao usadas para trafegar entre funçoes
int op;
int colisao;
int main() {

    //////////////////////// aqui sao as atribuições iniciais do jogo////////////////////////////////



    dados jogador1, jogador2;//criaçao da variavel do tipo struct dados
    jogador1.saiu = 0;//atribuindo valor ao campo saiu dos dois jogadores
    jogador2.saiu = 0;
    int valor;
    int colisao;
    int retorno_final;
    char nome1[50];
    char nome2[50];
    int play;

    memset(jogador1.peao, 0, sizeof(jogador1.peao));//atribuição dos valores 0 a todas as posiçoes dos vetores peoes dos jogadores 1 e 2
    memset(jogador2.peao, 0, sizeof(jogador2.peao));

    printf("****Bem-vindo ao jogo ludo****\n");
    printf("Digite qualquer tecla para iniciar o jogo\n");
    scanf("%d",&play);
    printf("Digite o nome do jogador 1: ");//imput dos nomes dos jogadores
    setbuf(stdin, NULL);
    fgets(nome1, 50, stdin);
    nome1[strcspn(nome1, "\n")] = '\0';//a função strcspn tira o \n do nome
    printf("Digite o nome do jogador 2: ");
    setbuf(stdin, NULL);
    fgets(nome2, 50, stdin);
    nome2[strcspn(nome2, "\n")] = '\0';//a função strcspn tira o \n do nome

    inicio(nome1, nome2, &jogador1, &jogador2);//chamada da função inicio que determina a ordem dos jogadores

    printf("Digite a cor do jogador %s:\n", jogador1.nome);//imput das cores dos jogadores
    setbuf(stdin, NULL);
    fgets(jogador1.cor, 50, stdin);
    jogador1.cor[strcspn(jogador1.cor, "\n")] = '\0';//a função strcspn tira o \n do char "cor"
    Cor_jogador(&jogador1);//uso da função cor para atribuir cor aos caracteres correspondentes a cada jogador

    printf("Digite a cor do jogador %s:\n", jogador2.nome);
    setbuf(stdin, NULL);
    fgets(jogador2.cor, 50, stdin);
    jogador2.cor[strcspn(jogador2.cor, "\n")] = '\0';//a função strcspn tira o \n do char "cor"
    Cor_jogador(&jogador2);//uso da função cor para atribuir cor aos caracteres correspondentes a cada jogador



    ////////////////////////////////aqui tem um for para os jogadores que ainda nao sairam da jogada inicial ////////////////////////////


    while (jogador1.saiu == 0 || jogador2.saiu == 0) {//verificação se os dois jogadores ja tirarm seus peoes
    
        if (jogador1.saiu == 0) {//quando o jogador nao tirou nenhum dado da parte inicial
            primeiraJogada(&jogador1);//uso da função primeira jogada
        }else{                        //passagem a estrutura jogador 1 como parametro por referencia

         valor=rolagem_de_dado(&jogador1);//uso da função rolagem de dados
         printf("Dado: %d\n", valor);
         if(valor!=6){
           print_peoes(&jogador1, valor);//uso da função para printar os peoes
                scanf("%d",&op);
                op=op-1;//op - 1 para atrinuir corretamente ao peao selecionado
                retorno_casas_finais=casas_finais(&jogador1, op, valor);//chamada da função 
                if(jogador1.peao[op]==58||retorno_casas_finais==1){//se o jogador selecionar um peao que nao pode ser movido a vez é passada e o peao nao recebe o valor do dado
                    printf("Jogada invalida\nA vez foi passada\n");
                }else{
                    jogador1.peao[op]+=valor;//caso o peao selecionado possa ser movido é incrementado o valor do dado 
                    retorno_final= final(&jogador1, op, 1);
                if(retorno_final==1){//se a função final retornar 1 significa que os 4 peoes chegaram a casa final e o jogo acabou
                    break;
                }
                }    
               
         }else{
             dado_seis(&jogador1, 1, jogador1, jogador2);//se o jogador tirar 6 no dado é chamada a função dado seis pois tem regras especificas
         }
        }

        if (jogador2.saiu == 0) {//quando o jjogador nao tirou nenhum dado da parte inicial
            primeiraJogada(&jogador2);//uso da função primeira jogada
        }else{

         valor=rolagem_de_dado(&jogador2);//uso da função rolagem de dados
         printf("Dado: %d\n", valor);
         if(valor!=6){
             print_peoes(&jogador2, valor);//uso da função para printar os peoes
                scanf("%d",&op);
                op=op-1;//op - 1 para atrinuir corretamente ao peao selecionado
                retorno_casas_finais=casas_finais(&jogador2, op, valor);//chamada da função 
                if(jogador2.peao[op]==58||retorno_casas_finais==1){//se o jogador selecionar um peao que nao pode ser movido a vez é passada e o peao nao recebe o valor do dado
                    printf("Jogada invalida\nA vez foi passada\n");
                }else{
                    jogador2.peao[op]+=valor;//caso o peao selecionado possa ser movido é incrementado o valor do dado 
                    retorno_final= final(&jogador2, op, 1);
                if(retorno_final==1){//se a função final retornar 1 significa que os 4 peoes chegaram a casa final e o jogo acabou
                    break;
                }
                }
         }else{
            dado_seis(&jogador2, 2, jogador1, jogador2);//se o jogador tirar 6 no dado é chamada a função dado seis pois tem regras especificas
         }

      }
    }


//////////aqui foi feita a parte principal do jogo////////////////////////////////


/////////////////////jogador 1 ////////////////////////

while(1){
printf("%s", jogador1.cor);//cor do jogador correspodente
    printf("Jogada jogador %s\n", jogador1.nome);
    valor=rolagem_de_dado(&jogador1);//uso da função rolagem de dados
    printf("Dado: %d\n", valor);
    if(valor!=6){
        print_peoes(&jogador1, valor);//uso da função para printar os peoes
                scanf("%d",&op);
                op=op-1;//op - 1 para atrinuir corretamente ao peao selecionado
                retorno_casas_finais=casas_finais(&jogador1, op, valor);//chamada da função 
                if(jogador1.peao[op]==58||retorno_casas_finais==1){//se o jogador selecionar um peao que nao pode ser movido a vez é passada e o peao nao recebe o valor do dado
                    printf("Jogada invalida\nA vez foi passada\n");
                }else{
                    jogador1.peao[op]+=valor;//caso o peao selecionado possa ser movido é incrementado o valor do dado 
                    colisao = verificar_casas_iguais_jogador1(&jogador1, &jogador2, op);//variavel colisao recebe 1 ou 0
                    if(colisao==1){//se a função retornar 1 significa que existem dois peoes na mesma casa e o peao adversario recebe valor 0
                        printf("Seu peao ocupou o lugar do peao adversario\n");
                    }

                      retorno_final= final(&jogador1, op,1);
                    if(retorno_final==1){//se a função final retornar 1 significa que os 4 peoes chegaram a casa final e o jogo acabou
                         break;
                }
                }
               


    }else{//se o numero tirado no dado for 6 ele pode mover qualquer peao
     dado_seis(&jogador1, 1, jogador1, jogador2);
    }

    /////////////////////jogador2//////////////////////////

printf("%s", jogador2.cor);//cor do jogador correspodente
 printf("Jogada jogador %s\n", jogador2.nome);
    valor=rolagem_de_dado(&jogador2);//uso da função rolagem de dados
    printf("Dado: %d\n", valor);
    if(valor!=6){
        print_peoes(&jogador2, valor);//uso da função para printar os peoes
                scanf("%d",&op);
                op=op-1;//op - 1 para atrinuir corretamente ao peao selecionado
                retorno_casas_finais=casas_finais(&jogador2, op, valor);//chamada da função 
                if(jogador2.peao[op]==58||retorno_casas_finais==1){//se o jogador selecionar um peao que nao pode ser movido a vez é passada e o peao nao recebe o valor do dado
                    printf("Jogada invalida\nA vez foi passada\n");
                }else{
                    jogador2.peao[op]+=valor;//caso o peao selecionado possa ser movido é incrementado o valor do dado 
                    colisao = verificar_casas_iguais_jogador2(&jogador2, &jogador1, op);//variavel colisao recebe 1 ou 0
                    if(colisao==1){//se a função retornar 1 significa que existem dois peoes na mesma casa e o peao adversario recebe valor 0
                        printf("Seu peao ocupou o lugar do peao adversario\n");
                    }
                    retorno_final= final(&jogador2, op,2);
                    if(retorno_final==1){//se a função final retornar 1 significa que os 4 peoes chegaram a casa final e o jogo acabou
                       break;
                }
                }
                colisao = verificar_casas_iguais_jogador2(&jogador2, &jogador1, op);//variavel colisao recebe 1 ou 0
                    if(colisao==1){//se a função retornar 1 significa que existem dois peoes na mesma casa e o peao adversario recebe valor 0
                        printf("Seu peao ocupou o lugar do peao adversario\n");
                    }


    }else{//se o numero tirado no dado for 6 ele pode mover qualquer peao
     dado_seis(&jogador2, 2, jogador1, jogador2);
    }


}
printf("\nObrigado por jogar");//se sair do loop infinito significa que o jogo acabou, o programa se incerra
return 0;

}


///////funçoes///////////////////////////
  




void Cor_jogador(dados* jogador) {//essa função muda a cor dos caracteres de cada jogador de acordo com a escolha do mesmo
    if (strcmp(jogador->cor, "verde") == 0) {//verificação do campo 'cor' da struct dados jogador
    strcpy(jogador->cor, "\033[0;32m"); // Código de escape ANSI para a cor verde eh atribuida ao jogador correspondente
    } else if (strcmp(jogador->cor, "vermelho") == 0) {//verificação do campo 'cor' da struct dados jogador
    strcpy(jogador->cor, "\033[0;31m"); // Código de escape ANSI para a cor vermelha eh atribuida ao jogador correspondente
    } else if (strcmp(jogador->cor, "azul") == 0) {//verificação do campo 'cor' da struct dados jogador
     strcpy(jogador->cor,"\033[0;34m"); // Código de escape ANSI para a cor azul eh atribuida ao jogador correspondente
    } else if (strcmp(jogador->cor, "amarelo") == 0) {//verificação do campo 'cor' da struct dados jogador
     strcpy(jogador->cor,"\033[0;33m"); // Código de escape ANSI para a cor amarela eh atribuida ao jogador correspondente
   
}
}


void inicio(char* nome1, char* nome2, dados* jogador1, dados* jogador2){//função para decidir qual jogador irá jogar primeiro
    int dado_1;//variavel que recebe o primeiro dado
    int dado_2;//variavel que recebe o segundo dado
    printf("Decisao da ordem dos jogadores: Cada jogador deve jogar o dado e o jogador que obtiver o maior valor no dado inicia o jogo\n");
    printf("jogada jogador %s\n", nome1);
    dado_1 = rolagem_de_dado(&jogador1);//jogada de dados do primeiro jogador usando a função de rolagem de peoes
    printf("Dado: %d\n", dado_1);
    printf("jogada jogador %s\n", nome2);
    dado_2 = rolagem_de_dado(&jogador2);//jogada de dados do segundo jogador usando a função de rolagem de peoes
    printf("Dado %d\n", dado_2);
    while(1){
        if(dado_1 == dado_2){//se os dados forem iguais é feita uma nova jogada
            printf("Dados iguais, jogue novamente\n");
            printf("jogada %s\n", nome1);
            dado_1 = rolagem_de_dado(&jogador1);//jogada de dados do primeiro jogador usando a função de rolagem de peoes
            printf("Dado: %d\n", dado_1);
            printf("jogada %s\n", nome2);
            dado_2 = rolagem_de_dado(&jogador2);//jogada de dados do segundo jogador usando a função de rolagem de peoes
            printf("Dado %d\n", dado_2);
        }
        else if(dado_1 > dado_2){//se o primeiro dado foi maior o jogador 1 começa e de fato a struct jogador 1 recebe seu nome
            printf("%s inicia o jogo\n", nome1);
            strcpy(jogador1->nome, nome1);//e o segundo jogador sera o jogador que sobrou
            strcpy(jogador2->nome, nome2);
            break;
        }
        else{//se o segundo dado foi maior o jogador 2 começa e a struct jogador 1 recebe seu nome
            printf("%s inicia o jogo\n", nome2);
            strcpy(jogador1->nome, nome2);//e o segundo jogador sera o jogador que sobrou
            strcpy(jogador2->nome, nome1);
            break;
        }
    }
}



int rolagem_de_dado(dados*jogador){//função para gerar numero aleatorio entre 1 e 6
    int play;
    printf("%s", jogador->cor);
    printf("Digite qualquer numero para rodar o dado: ");
    scanf("%d", &play);
    srand(time(NULL));
    return (rand() % 6) + 1;//geração de numero aleatorio de 1 a 6
}



void print_peoes(dados* jogador, int valor){//função para printar os peoes disponiveis
    int retorno_casas_seguras;//criação de variavl para receber o retorno da função casas seguras
    int peao_disponivel=0;//variavel de contagem para cada peao movido
    printf("Qual peao sera movido\n");
    if(valor!=6){
                for(int i=0; i<4; i++){//loop para printar os peoes
                    if(jogador->peao[i]<= 58 && jogador->peao[i] > 0){//peoes que nao iniciaram nao serão mostrados
                        if(jogador->peao[i]<52){//se o peao nao estiver nas casas finais
                            retorno_casas_seguras=casas_seguras(jogador, i);//para exibir a mensagem se o peao esta ou nao em uma casa segura, é feita a verificação usando a propria função casa segura
                            if(retorno_casas_seguras==0){//a função retorna 0 se estiver em casa segura
                            printf("peao %d ->> %d(casa segura) Movimento- %d\n", i+1, jogador->peao[i], jogador->peao[i]+valor);//mostra a mensagem com o (casa segura)
                            peao_disponivel++;//peao disponivel é incrementado caso algum peao seja mostrado  
                            }else{//se nao estiver, o peao é printado normalmente
                                printf("peao %d ->> %d Movimento- %d\n", i+1, jogador->peao[i], jogador->peao[i]+valor);
                                peao_disponivel++;//para cada print de peoes eh incrementada a a variavel de controle de peoes mostrados
                            }
                        }else if(jogador->peao[i]==58){
                            printf("peao %d ->> %d(peao concluiu o jogo)\n", i+1, jogador->peao[i]);//quando o peao esta na casa final ele é mostrado juntamente com a mensagem

                        }else{
                            retorno_casas_finais=casas_finais(jogador, i, valor);//peoes que estao na parte final podem nao ser possivel executar o movimento
                            if(retorno_casas_finais==1){
                                printf("Peao %d ->> %d(movimento nao permitido)\n", i+1, jogador->peao[i]);//se o peao nao puder ser movido ele eh mostrado junto a mensagem de advertencia
                            }else{
                                printf("Peao %d ->> %d Movimento- %d\n", i+1, jogador->peao[i], jogador->peao[i]+valor);
                                peao_disponivel++;//para cada print de peoes eh incrementada a a variavel de controle de peoes mostrados
                            }
                        }
                    }
                }
    }else{
        for(int i=0; i<4; i++){//loop para printar os peoes
                    if(jogador->peao[i]<= 58 && jogador->peao[i]!= 0){//peoes que chegaram ao final nao serão mostrados
                        if(jogador->peao[i]<52){
                            retorno_casas_seguras=casas_seguras(jogador, i);//para exibir a mensagem se o peao esta ou nao em uma casa segura, é feita a verificação usando a propria função casa segura
                            if(retorno_casas_seguras==0){//a função restorna 0 se estiver
                            printf("peao %d ->> %d(casa segura) Movimento- %d\n", i+1, jogador->peao[i], jogador->peao[i]+valor);//mostra a mensagem com o (casa segura)
                            peao_disponivel++;
                            }else{//se nao estiver, o peao é printado normalmente
                                printf("peao %d ->> %d Movimento- %d\n", i+1, jogador->peao[i], jogador->peao[i]+valor);
                                peao_disponivel++;
                            }
                        }else if(jogador->peao[i]==58){//peoes que concluiram o jogo irao mostra o aviso
                            printf("peao %d ->> %d(Peao concluiu o jogo)\n", i+1, jogador->peao[i]);
                        }else{
                            retorno_casas_finais=casas_finais(jogador, i, valor);//peoes que estao na parte final podem nao ser possivel executar movimento
                            if(retorno_casas_finais==1){
                                printf("Peao %d ->> %d(movimento nao permitido)\n", i+1, jogador->peao[i]);//se o peao nao puder ser movido ele eh mostrado a mensagem de aviso
                            }else{
                                printf("Peao %d ->> %d Movimento- %d\n", i+1, jogador->peao[i], jogador->peao[i]+valor);
                                peao_disponivel++;//para cada print de peoes eh incrementada a a variavel de controle de peoes mostrados
                            }
                        }
                    }else if(jogador->peao[i]== 0){
                        printf("Peao %d - %d Movimento- %d\n", i+1, jogador->peao[i], jogador->peao[i]+1);//caso o peao nao foi iniciado ele so pode ser movido para a casa 1
                        peao_disponivel++;
                    }
                }
    }
    if(peao_disponivel==0){//caso a variavel peao disponivel nao seja incrementada(valor 0) eh mostrado a mensagem de nenhum peao disponivel para jogo
        printf("\nNenhum peao disponivel para movimentar\nA vez sera passada\n");
        return;
    }

}




void primeiraJogada(dados* jogador){//função primeira jogada recebendo a estrutura jogador 1 e 2
printf("%s", jogador->cor);//cor para cada jogador correspondente
    printf("Jogada jogador %s\n", jogador->nome);
    int contadorSeis = 0;//variavel para contar a quantidade de vezes que o numero 6 eh tirado no dado
    
    while (contadorSeis < 3) {//controlar quantas vezes o jogador tirou 6
        int dado = rolagem_de_dado(jogador);//uso da função rolagem de dado
        jogador->dados[jogador->saiu] = dado;
        printf("Dado: %d\n", dado);

        if (dado == 6) {//verificação se o valor do dado eh 6
            jogador->saiu++;//incremento do campo jogador saiu para ele iniciar o jogo no campo principal do tabuleiro
            contadorSeis++;//variavel de controle para cada vez que o jogador tirar 6 no dado
            if(contadorSeis == 1){
                printf("O peao 1 foi iniciado no jogo\n");
                jogador->peao[0] = 1;//atribuição do valor 1 ao peao para ir para a primeira casa
                printf("O jogador tem direito a nova jogada\n");
            }else if(contadorSeis == 2){
                printf("O peao 2 foi iniciado no jogo\n");
                jogador->peao[1] = 1;//atribuição do valor 1 ao peao para ir para a primeira casa
                printf("O jogador tem direito a nova jogada\n");
            }

            if (contadorSeis == 3) {//se o jogador tirar 3 6 consecutivos ele passa a vez
                printf("A vez foi passada (tres 6 consecutivos)\n");
                break;
            }
        } else {
            printf("A vez foi passada\n");//apos a jogada da rolagem de dados sai do loop
            break;
        }
    }
}


void dado_seis(dados* jogador, int jog, dados jogador1, dados jogador2){//função para quando o jogador tirar 6 no dado, passando jog referente ao jogador que chama a função
    int valor;//nova variavel para receber valor do dado
    printf("Voce tem direiro a uma nova jogada\n");//toda vez que um jogador tirar 6 no dado ele tem direito a uma nova jogada
    valor = rolagem_de_dado(jogador);//uso da função rolagem de dado
    printf("Dado: %d\n", valor);
    if(valor==6){
        printf("Voce tem direiro a uma nova jogada\n");//se tiirar 6 novamente ele tem direito a outra jogada
        valor = rolagem_de_dado(jogador);//uso da função rolagem de dado
        printf("Dado: %d\n", valor);
        if(valor==6){
            printf("A vez foi passada (três seis consecutivos)\n");//se tirar 3 seis consecutivos a vez eh passada
        }else{//se o jogador tirar um numero diferente de 6 ele tem 2 jogadas para o dado 6, isso foi feiro em um loop 
            for(int i=0; i<2; i++){
                print_peoes(jogador, 6);//uso da função para printar peoes
                printf("(Dado 6)\n");
                scanf("%d", &op);
                jogador->peao[op-1]+=6;//atribuição obrigatoria do 6 ao dado
                if(jog==1){//verificação de qual jogador esta chamando a função para usar de forma correta a função "verificar casas iguais"
                    colisao = verificar_casas_iguais_jogador1(&jogador1, &jogador2, op);//variavel colisao recebe 1 ou 0
                    if(colisao==1){//se a função retornar 1 significa que existem dois peoes na mesma casa e o peao adversario recebe valor 0
                        printf("Seu peao ocupou o lugar do peao adversario\n");
                    }
                }else{//verificação de qual jogador esta chamando a função para usar de forma correta a função "verificar casas iguais"
                    colisao = verificar_casas_iguais_jogador2(&jogador2, &jogador1, op);//variavel colisao recebe 1 ou 0
                    if(colisao==1){//se a função retornar 1 significa que existem dois peoes na mesma casa e o peao adversario recebe valor 0
                        printf("Seu peao ocupou o lugar do peao adversario\n");
                    }
                }
            }//se o jogador tirar 6 duas vezes ele joga duas vezes para o valor 6 e uma para o ultimo valor tirado
            print_peoes(jogador, valor);
            printf("(Dado: %d)\n", valor);
            scanf("%d", &op);
            jogador->peao[op-1]+=valor;//atribuição do ultimo valor tirado
        }
    }else{//se o jogador nao tirar 6  duas vezes consecutivas ele faz uma jogada para o valor 6 e outra para o ultimo valor tirado 
        print_peoes(jogador, 6);
        printf("(Dado 6)\n");
        scanf("%d",&op);
        jogador->peao[op-1]+=6;//atribuição obrigatoria do valor 6
        if(jog==1){
                    colisao = verificar_casas_iguais_jogador1(&jogador1, &jogador2, op);//variavel colisao recebe 1 ou 0
                    if(colisao==1){//se a função retornar 1 significa que existem dois peoes na mesma casa e o peao adversario recebe valor 0
                        printf("Seu peao ocupou o lugar do peao adversario\n");
                    }
                }else{
                    colisao = verificar_casas_iguais_jogador2(&jogador2, &jogador1, op);//variavel colisao recebe 1 ou 0
                    if(colisao==1){//se a função retornar 1 significa que existem dois peoes na mesma casa e o peao adversario recebe valor 0
                        printf("Seu peao ocupou o lugar do peao adversario\n");
                    }
                }
        print_peoes(jogador, valor);
        printf("(Dado %d)\n", valor);
        scanf("%d",&op);
        jogador->peao[op-1]+=valor;//atribuição do ultimo valor tirado
        if(jog==1){//verificação de qual jogador esta chamando a função para usar de forma correta a função "verificar casas iguais"
                    colisao = verificar_casas_iguais_jogador1(&jogador1, &jogador2, op);//variavel colisao recebe 1 ou 0
                    if(colisao==1){//se a função retornar 1 significa que existem dois peoes na mesma casa e o peao adversario recebe valor 0
                        printf("Seu peao ocupou o lugar do peao adversario\n");
                    }
                }else{//verificação de qual jogador esta chamando a função para usar de forma correta a função "verificar casas iguais"
                    colisao = verificar_casas_iguais_jogador2(&jogador2, &jogador1, op);//variavel colisao recebe 1 ou 0
                    if(colisao==1){//se a função retornar 1 significa que existem dois peoes na mesma casa e o peao adversario recebe valor 0
                        printf("Seu peao ocupou o lugar do peao adversario\n");
                    }
                }
        
    }
}


int verificar_casas_iguais_jogador1(dados* jogador1, dados* jogador2, int posicao) {//função para verificar se dois peoes ocupam a mesma posição no tabuleiro
    int valor_peao_atual = jogador1->peao[posicao]+27;//+27 pois pela logica do tabuleiro, os peoes 1 estao 27 posiçoes atras do jogador 2
    int verificacao_casas_seguras;//variavel para receber o retorno da funçao de casas seguras


    for (int i = 0; i < 4; i++) {
        if (jogador2->peao[i] == valor_peao_atual) {
            verificacao_casas_seguras = casas_seguras(jogador1, i); //função verificar casas seguras
            if(verificacao_casas_seguras==1){
                jogador2->peao[i] = 0;//peao que esta na casa volat a posição original
            return 1; // Retorna 1 se há um peão do adversário com o mesmo valor na mesma posição
        }
    }
  }
    
    return 0; // Retorna 0 se não há colisão com peões do adversário
}


int verificar_casas_iguais_jogador2(dados* jogador2, dados* jogador1, int posicao) {//função para verificar se dois peoes ocupam a mesma posição no tabuleiro
    int valor_peao_atual = jogador2->peao[posicao]-27;//-27 pois pela logica do tabuleiro, os peoes 2 estao 27 posiçoes afrente do jogador 1
    int verificacao_casas_seguras;//variavel para receber o retorno da funçao de casas seguras


    for (int i = 0; i < 4; i++) {//jogador1 é o peao adversario
        if (jogador1->peao[i] == valor_peao_atual) {
            verificacao_casas_seguras = casas_seguras(jogador2, i); //função verificar casas seguras
            if(verificacao_casas_seguras==1){
                jogador1->peao[i] = 0;//peao que esta em casa igual volta a posição original
                return 1;// Retorna 1 se há um peão do adversário com o mesmo valor na mesma posição e nao estiver em uma casa segura
            }
        }
    }
    
    return 0; // Retorna 0 se não há colisão com peões do adversário
}

int casas_seguras(dados* jogador, int posicao){//função para verificar casas seguras
    if(jogador->peao[posicao]== 1 || jogador->peao[posicao]== 9 || jogador->peao[posicao]== 22 || jogador->peao[posicao]== 33 || jogador->peao[posicao]== 48 || jogador->peao[posicao]== 14 || jogador->peao[posicao]== 27 || jogador->peao[posicao]== 40){//verificação nas posiçoes
        return 0;//retorna 0 se estiver em uma casa segura
    }else{
        return 1;//retorna 1 se a casa ocupada nao for uma casa segura
    }
}          



int casas_finais(dados* jogador, int posicao, int dado){//função para verificar as ultimas 6 casas do jogador
    

    if(jogador->peao[posicao] + dado <= 58){// é calculada por uma simulação da proxima posição do jogador, baseada em sua posição atual e no valor tirado no dado
        return 0;                          //a função retorna 1 caso o peao nao possa ser movido
    }else{                                 //a função retorna 0 caso o peao possa ser movido,
        return 1;
    }
}



int final(dados* jogador, int posicao, int jog){//função para verificar casa final 

    if(jogador->peao[posicao]==58){//verificação se o peao esta na casa final
        contagem_final[jog]++;//contagem peoes que finalizaram o jogo
        printf("\n***Seu peao chegou a casa final!***\n");
        printf("Voce tem %d peao/peoes na casa final!\n",contagem_final[jog]);
        if(contagem_final[jog]==4){//quando 4 peoes finalizrem o jogo retorna 1 
            printf("***Jogo finalizado!***\n");
            printf("vencedor:\n %s\n%s", jogador->nome, jogador->cor);//mostra o nome e a cor do jogador campeao
            return 1;//retorna 1 se o jogador venceu o jogo
        }else{
        return 0;//retorna 0 se o jogador nao esta com todos ps peoes na finalizados
    }
    }
}
