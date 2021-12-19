//O código ignora pontuações, e converte caracteres maiúsculos para minúsculos

#include <stdio.h>
#include <string.h>

#define L 3000
#define C 50

void clear(){
    system("cls");
    fflush(stdin);
}

void readFromFile(FILE *file, char content[L][C]){

    int l = 0;

    while(fgets(content[l], C, file) != EOF && l <= L){
        strlwr(content[l++]); //todo o conteúdo é guardado com letras minúsculas minúsculas
    }

    content[l][0] = NULL;

    fclose(file);

}

void writeOnFile(char content[L][C], char fileName[C]){

    FILE *file = fopen(fileName, "w");
    int l = 0;

    while (content[l][0] != NULL)
    {
        fputs(content[l++], file);
    }
    
    fclose(file);
    
}

//para descriptografar, basta passar a chave com um valor negativo
void encryptText(char inputText[L][C], char outputText[L][C], int key){

    int i, j;

    for(i = 0; i < L; i++){

        if(inputText[i][0] == NULL){
            outputText[i][0] == NULL;
            break;
        }

        for(j = 0; j <= strlen(inputText[i]); j++){

            int ci = (int)inputText[i][j]; //guarda a posição do caractere da tabela ASCII

            //tabela ascii de a - z : 97 - 122
            if(ci > 122 || ci < 97){
                outputText[i][j] = inputText[i][j];

                if(inputText[i][j] == '\n'){
                    break;
                }

                continue;
            }

            int cf = (int)(inputText[i][j] + key); //guarda a posição do caractere da tabela ASCII somada à chave

            //Corrige para caso o novo valor esteja em um intervalo fora de a-z (minúsculo)
            if(cf < 97){
                cf += 26;
            }else{
                if(cf > 122){
                    cf -= 26;
                }
            }

            outputText[i][j] = (char)cf;
        }
    }

}

void shoWText(char text[L][C]){
    
    int i;

    for(i = 0; i < L; i++){
        printf("%s", text[i]);
    }

    printf("\n");

}

int main(){

    int key;

    char inputFileName[C];
    FILE *inputFile;
    char inputFileContent[L][C];
    char outputFileContent[L][C];
    int c0, c1, c2; //for choices

    clear();

    do
    {
        printf("O que deseja fazer?\n1- Criptografar;\n2- Descriptografar;\n0- Sair.\n-Sua escolha: ");
        scanf("%d", &c0);
        
        switch (c0)
        {
        case 1:
            clear();
            do{
                printf("A partir de que tipo de entrada deseja criptografar?\n1- Arquivo de texto;\n2- Entrada do teclado;\n0- Voltar.\n-Sua escolha: ");
                scanf("%d", &c1);

                switch (c1)
                {
                case 1:
                    clear();
                    printf("Qual o nome do que arquivo deseja criptografar?\n");
                    gets(inputFileName);

                    inputFile = fopen(inputFileName, "r");

                    if(inputFile == NULL){
                        printf("Nao foi possivel abrir o arquivo.\n");
                        break;
                    }

                    readFromFile(inputFile, inputFileContent);

                    printf("A partir de qual chave deseja criptografar? (1 - 26)\n");
                    scanf("%d", &key);

                    encryptText(inputFileContent, outputFileContent, key);

                    clear();

                    do{
                        printf("\nCriptografado com sucesso. O que deseja fazer com o novo texto?\n1- Mostrar;\n2- Escrever em arquivo;\n0- Voltar.");
                        scanf("%d", &c2);

                        switch (c2)
                        {
                        case 1:
                            shoWText(outputFileContent);
                            break;

                        case 2:
                            clear();
                            printf("com qual nome deseja salvar o arquivo?\n");
                            
                            char fileName[C];
                            gets(fileName);

                            writeOnFile(outputFileContent, fileName);
                            
                            clear();
                            printf("Arquivo salvo com sucesso.\n");
                            break;

                        case 0:
                            clear();
                            break;
                        
                        default:
                            clear();
                            printf("Insira uma escolha valida.\n\n");
                        }
                    }while (c2 != 0);

                    break;
                
                case 2:
                    ///////ENTRADA DE TECLADO AQUI//////////////
                    break;

                case 0:
                    clear();
                    break;
                
                default:
                    clear();
                    printf("Insira uma escolha valida.\n\n");
                    break;
                }

            }while(c1 != 0);

            break;
        case 2:
            clear();

            do{
                printf("A partir de que tipo de entrada deseja descriptografar?\n1- Arquivo de texto;\n2- Entrada do teclado;\n0- Voltar.\n-Sua escolha: ");
                scanf("%d", &c1);

                switch (c1)
                {
                case 1:
                    clear();
                    printf("Qual o nome do que arquivo deseja descriptografar?\n");
                    gets(inputFileName);

                    inputFile = fopen(inputFileName, "r");

                    if(inputFile == NULL){
                        printf("Nao foi possivel abrir o arquivo.");
                    }

                    readFromFile(inputFile, inputFileContent);

                    printf("A partir de qual chave deseja descriptografar? (1 - 26)");
                    scanf("%d", &key);

                    encryptText(inputFileContent, outputFileContent, -key);

                    clear();
                    do{
                        printf("Descriptografado com sucesso. O que deseja fazer com o novo texto?\n1- Mostrar;\n2- Escrever em arquivo;\n0-Voltar.\n");
                        scanf("%d", &c2);

                        switch (c2)
                        {
                        case 1:
                            shoWText(outputFileContent);
                            break;

                        case 2:
                            clear();
                            printf("com qual nome deseja salvar o arquivo?\n");
                            
                            char fileName[C];
                            gets(fileName);

                            writeOnFile(outputFileContent, fileName);
                            
                            clear();
                            printf("Arquivo salvo com sucesso.\n");
                            break;

                        case 0:
                            clear();
                            break;
                        
                        default:
                            clear();
                            printf("Insira uma escolha valida.\n\n");
                            break;
                        }
                    }while(c2 != 0);

                    break;

                case 2:
                    /////////////entrada do teclado para descriptografar//////////////////
                    break;
                }
            }while (c1 != 0);
            
            break;
        
        case 0:
            printf("Encerrando o programa...\n");
            break;

        default:
            clear();
            printf("Insira uma escolha valida.\n\n");
            break;
        }

    }while (c0 != 0);
    
    return 0;
}