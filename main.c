#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

///Aluno Maximiliano Meyer

int BinGlobal[9], verif = 0;
char msg[10];

int main(){
    setlocale(LC_ALL, "Portuguese");
    menu();
    return 0;
}

int menu(void){ ///menu geral - Pronto
    int op;
    verif = 0;

    printf("\n\n");
    printf("Com qual ferramenta voc� quer trabalhar?\n");
    printf("\t1. Converter ASCII para bin�rio\n");
    printf("\t2. Converter bin�rio para ASCII\n");
    printf("\t3. Hamming\n");
    printf("\t4. Checksum\n");
    printf("\t5. CRC\n");
    printf("\t6. Sair\n\n");
    do{
        opcoes:
        printf("\t\nDigite sua op��o: ");
        scanf("%d", &op);
        switch(op){
                case 1:
                                AscToBin();
                                break;
                case 2:
                                BinToAsc();
                                break;
                case 3:
                                Hamming();
                                break;
                case 4:
                                Checksum();
                                break;
                case 5:
                                CRC();
                                break;
                case 6:
                                exit(0);
                default:
                                printf("Opcao Inv�lida\n");
                                goto opcoes;
        }
    }while(1);
}

int AscToBin(void){ ///passar ascii to bin - pronto
int i, x = 0, tamanho;
int bin[8];

    printf("\nDigite a mensagem a transmitir: ");
    scanf("%s", &msg);

    tamanho = strlen(msg);

    printf("\nMensagem em bin�rio: ");
    while (x < tamanho) {
        char letra = msg[x];
        for(i=0;i<8;i++)
            bin[i]=0;
            BinGlobal[i]=0;
        for(i=0;letra!=0;i++){
            bin[i]=letra%2;
            BinGlobal[i]=letra%2;
            letra=(letra - bin[i])/2;
    }
    for(i=7;i>=0;i--)
        printf("%d", bin[i]);
    x++;
    }
    getch();

    if (verif == 0)
        menu();
    else
        BinToHam();
}

int BinToAsc(void){ ///passar binpario para ascii - pronto
int  x, binario, decimal = 0, base = 1, rem;
char valor;

    printf("\nDigite os 8 bits do valor bin�rio: ");
    scanf("%d", &x);
    binario = x;
    while (x > 0) {
        rem = x % 10;
        decimal = decimal + rem * base;
        x = x / 10 ;
        base = base * 2;
    }

    valor = decimal;

    printf("\nO bin�rio inserido foi %d ", binario);
    printf("\nO caractere correspondente � '%c' \n", valor);

    getch();
    menu();
}

int Hamming(void){ ///Implementa o m�todo de hamming - pronto
int op, i;
    printf("\n\nO que voc� deseja fazer?\n");
    printf("\t1. Codificar algum caractere\n");
    printf("\t2. Checar alguma mensagem codificada em busca de erros\n");
    printf("\t3. voltar\n\n");

    do{
        opcoes:
        printf("\tDigite sua op��o: ");
        scanf("%d", &op);
        switch(op){
                case 1:
                                verif = 1;
                                AscToBin();
                                BinToHam();
                                break;
                case 2:
                                VerificarHam();
                                break;
                case 3:
                                menu();
                default:
                                printf("Opcao Invalida\n");
                                goto opcoes;
        }
    }while(1);
}

int BinToHam(void){ ///Codifica um bin�rio atrav�s do m�todo de Hamming - pronto

int x =0,i,  data[11];
int dataatrec[11],c,c1,c2,c3;

    data[2] = BinGlobal[7];
    data[4] = BinGlobal[6];
    data[5] = BinGlobal[5];
    data[6] = BinGlobal[4];
    data[8] = BinGlobal[3];
    data[9] = BinGlobal[2];
    data[10] = BinGlobal[1];
    data[11] = BinGlobal[0];

    data[0]=data[2]^data[4]^data[6]^data[8]^data[10];
    data[1]=data[2]^data[5]^data[6]^data[9]^data[10];
    data[3]=data[4]^data[5]^data[6]^data[11];
    data[7]=data[8]^data[9]^data[10]^data[11];

    printf("\n\nO caracter '%c' ap�s passar pelo algoritmo de Hamming resulta em: ", msg[0]);
    for(i=0;i<=11;i++){
        printf("%d", data[i]);
    }

    getch();
    menu();
}

int VerificarHam(void){ ///Verifica se o c�digo de hamming inserido est� correto - pronto
int i,x=0,v=0, verif[11], v1, v2, v3 ,v4;

    printf("\nDigite os bits, 1 a 1: ");

    for(i=0;i<=11;i++){
        scanf("%d", &verif[x]);
        x++;
    }

    v1=verif[0]^verif[2]^verif[4]^verif[6]^verif[8]^verif[10];
    v2=verif[1]^verif[2]^verif[5]^verif[6]^verif[9]^verif[10];
    v3=verif[3]^verif[4]^verif[5]^verif[6]^verif[11];
    v4=verif[7]^verif[8]^verif[9]^verif[10]^verif[11];

    v=v4*8+v3*4+v2*2+v1;

    if(v==0) {
        printf("\n\nA mensagem ");

        x=0;
        for(i=0;i<=11;i++){
        printf("%d", verif[i]);
        x++;
        }

        printf(" n�o cont�m erros, de acordo com o c�digo de Hamming\n");
    }
        else {
        printf("\nC�digo Recebido: ");
        for(i=0;i<=11;i++)
            printf("%d",verif[i]);

        printf("\nErro na posi��o: %d",v);
        printf("\n\nA mensagem correta �: ");

        if(verif[11-v]==0)
            verif[11-v]=1;
        else
            verif[11-v]=0;

        for (i=0;i<=11;i++) {
            printf("%d",verif[i]);
        }
    }
    getch();
    menu();
}

int Checksum(void){ ///Menu de op��es do checksum - pronto
int op, i;
    printf("\n\nO que voc� deseja fazer?\n");
    printf("\t1. Aplicar o checksum a alguma mensagem\n");
    printf("\t2. Checar alguma mensagem codificada em busca de erros\n");
    printf("\t3. voltar\n\n");

    do{
        opcoes:
        printf("\tDigite sua op��o: ");
        scanf("%d", &op);
        switch(op){
                case 1:
                                BinToCheck();
                                break;
                case 2:
                                VerificarCheck();
                                break;
                case 3:
                                menu();
                default:
                                printf("Opcao Invalida\n");
                                goto opcoes;
        }
    }while(1);
}

int BinToCheck(void){ ///Gera o checksum para o bin�rio inserido - pronto
char a[50], b[50], soma[50],complemento[20];
int i,tamanho;

    printf("\nEntre com a primeira sequ�ncia de bin�rios: ");
    scanf("%s",&a);
    printf("Entre com a segunda sequ�ncia de bin�rios: ");
    scanf("%s",&b);

    if(strlen(a)==strlen(b)){
        tamanho = strlen(a);
        char resto ='0';

        for(i=tamanho-1;i>=0;i--)
        {
            if(a[i]=='0' && b[i]=='0' && resto=='0'){
                soma[i]='0';
                resto='0';
            }
            else if(a[i]=='0' && b[i]=='0' && resto=='1'){
                soma[i]='1';
                resto='0';
            }
            else if(a[i]=='0' && b[i]=='1' && resto=='0'){
                soma[i]='1';
                resto='0';
            }
            else if(a[i]=='0' && b[i]=='1' && resto=='1'){
                soma[i]='0';
                resto='1';
            }
            else if(a[i]=='1' && b[i]=='0' && resto=='0'){
                soma[i]='1';
                resto='0';
            }
            else if(a[i]=='1' && b[i]=='0' && resto=='1'){
                soma[i]='0';
                resto='1';
            }
            else if(a[i]=='1' && b[i]=='1' && resto=='0'){
                soma[i]='0';
                resto='1';
            }
            else if(a[i]=='1' && b[i]=='1' && resto=='1'){
                soma[i]='1';
                resto='1';
            }
            else
                break;
        }

        printf("\nSoma= %c%s\n",resto,soma);
        for(i=0;i<tamanho;i++){
            if(soma[i]=='0')
                complemento[i]='1';
            else
                complemento[i]='0';
        }

        if(resto=='1')
            resto='0';
        else
            resto='1';
        printf("\nChecksum= %c%s\n",resto,complemento);
    }
    else {
        printf("\nDados de tamanhos diferentes inseridos. Tente novamente");
    }
    getch();
    menu();
}

int VerificarCheck(void){ ///Confere se a mensagem recebida est� correta de acordo com o checksum - pronto
int receb, check, i = 0, resultado = 0, sum[20], erro = 0;

    printf("\nInforme o valor recebido em bin�rio: ");
    scanf("%d", &receb);
    printf("Informe o checksum fornecido: ");
    scanf("%d", &check);
    while (receb != 0 || check != 0){
        sum[i++] = (receb % 10 + check % 10 + resultado) % 2;
        resultado = (receb % 10 + check % 10 + resultado) / 2;
        receb = receb / 10;
        check = check / 10;
    }
    if (resultado != 0)
        sum[i++] = resultado;
        --i;
    printf("\nValor conferido: ");
    for(;i>=0;i--){
        printf("%d", sum[i]);
        if (sum[i] == 0)
            erro = i;
        else;
    }
    if (erro != 0)
        printf("\nTemos um erro na posi��o %d", erro+1);
    else
        printf("\n\nMensagem recebida sem erros");

    getch();
    menu();
}

int CRC (void){ ///Menu de op��es do CRC - pronto
int op, i;
    printf("\n\nO que voc� deseja fazer?\n");
    printf("\t1. Codificar algum caractere\n");
    printf("\t2. Checar alguma mensagem codificada em busca de erros\n");
    printf("\t3. voltar\n\n");

    do{
        opcoes:
        printf("\tDigite sua op��o: ");
        scanf("%d", &op);
        switch(op){
                case 1:
                                BinToCRC();
                                break;
                case 2:
                                VerificarCRC();
                                break;
                case 3:
                                menu();
                default:
                                printf("Opcao Invalida\n");
                                goto opcoes;
        }
    }while(1);
}

int BinToCRC(){
    printf("\n\nOp��o n�o implementada ainda\n");
    getch();
    menu();
}

int VerificarCRC(){
    printf("\n\nOp��o n�o implementada ainda\n");
    getch();
    menu();
}
