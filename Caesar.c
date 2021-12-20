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

void showKeyIntervalDecryption(char inputText[L][C], int caracterQuant, int firstKey, int lastKey){

        int i = 0;
        char cutText[L][C];
        int atualLenght = 0;


        while(i < L){
            
            strncpy(cutText[i], inputText[i], caracterQuant - atualLenght);
            atualLenght += strlen(cutText[i]);

            if(atualLenght >= caracterQuant){
                break;
            }
            
            i++;
        }

        char decrypted[L][C];

        for(i = firstKey; i < lastKey; i++){
        
            printf("chave %d: ", i);
            encryptText(cutText, decrypted, -i);
            shoWText(decrypted);

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
    char outputFileName[C];
    FILE *inputFile;
    char inputFileContent[L][C];
    char outputFileContent[L][C];
    int c0, c1, c2; //for choices

    
    int proceed = 1;

    clear();


    do{

        printf("O que deseja fazer?\n\n1- Criptografar;\n2- Descriptografar;\n0- Sair.\n\n-Sua escolha: ");
        scanf("%d", &c0);

        switch (c0)
        {
        case 1: //Criptografar
            
            clear();
            proceed = 1;
            do
            {

                printf("A partir de que tipo de entrada deseja criptografar?\n\n1- Arquivo de texto;\n2- Entrada do teclado;\n0- Voltar.\n\n-Sua escolha: ");
                scanf("%d", &c1);

                switch (c1)
                {
                case 1: //arquivo texto
                    clear();

                    do{
                        printf("Qual arquivo abrir? (0- Voltar)\n");
                        gets(inputFileName);

                        if(strcmp(inputFileName, "0") == 0){ 
                            proceed = 0; 
                            clear(); 
                            break;
                        }

                        inputFile = fopen(inputFileName, "r");

                        if(inputFile == NULL){
                            clear();
                            printf("*Arquivo não encontrado.\n\n");
                            continue;
                        }

                        readFromFile(inputFile, inputFileContent);
                        proceed = 1;
                        break;

                    }while(1);

                    break;

                case 2:
                    ///////////////ENTRADA DO TECLADO AQ//////////////
                    proceed = 1;
                    break;

                case 0:
                    clear();
                    break;

                default:
                    clear();
                    printf("*Opcao invalida.\n\n");
                    proceed = 0;
                    break;
                }

                if(c1 == 0){break;}
                if(proceed == 0){continue;}

                clear();
                printf("A partir de qual chave deseja criptografar? (1 - 26)\n");
                scanf("%d", &key);

                encryptText(inputFileContent, outputFileContent, key);
                clear();
                printf("Criptografado com sucesso.\n\n");
                do
                {
                    printf("O que deseja fazer?\n\n1- Mostrar saida; \n2- Escrever a saida em um arquivo;\n0- Voltar.\n\n - Sua escolha: ");
                    scanf("%d", &c2);

                    switch (c2)
                    {
                    case 1:
                        clear();
                        printf("A saida foi:\n\n");
                        shoWText(outputFileContent);
                        printf("\n\n");
                        break;

                    case 2:
                        clear();

                        printf("Com qual nome salvar o arquivo? (0- voltar)\n");
                        gets(outputFileName);

                        clear();

                        if(strcmp(outputFileName, "0") == 0){
                            break;
                        }

                        writeOnFile(outputFileContent, outputFileName);
                        
                        printf("* Arquivo salvo.\n\n");
                        break;

                    case 0:
                        clear();
                        break;

                    default:
                        clear();
                        printf("*Insira uma opcao valida\n\n");
                        proceed = 0;
                        break;
                    }
                } while (c2 != 0);
                
            } while (c1 != 0);
            break;

        case 2: //Descriptografar
            
            clear();
            proceed = 1;
            do
            {

                printf("A partir de que tipo de entrada deseja descriptografar?\n\n1- Arquivo de texto;\n2- Entrada do teclado;\n0- Voltar.\n\n-Sua escolha: ");
                scanf("%d", &c1);

                switch (c1)
                {
                case 1: //arquivo texto
                    clear();

                    do{
                        printf("Qual arquivo abrir? (0- Voltar)\n");
                        gets(inputFileName);

                        if(strcmp(inputFileName, "0") == 0){ 
                            proceed = 0; 
                            clear(); 
                            break;
                        }

                        inputFile = fopen(inputFileName, "r");

                        if(inputFile == NULL){
                            clear();
                            printf("*Arquivo não encontrado.\n\n");
                            continue;
                        }

                        readFromFile(inputFile, inputFileContent);
                        proceed = 1;
                        break;

                    }while(1);

                    break;

                case 2:
                    ///////////////ENTRADA DO TECLADO AQ//////////////
                    proceed = 1;
                    break;

                case 0:
                    clear();
                    proceed = 0;
                    break;

                default:
                    clear();
                    printf("*Opcao invalida.\n\n");
                    break;
                }

                
                if(proceed == 0){continue;}

                clear();
                
                
                do{

                    int firstKey = 1, lastKey = 26, caracterQuant;

                    printf("De qual forma deseja descriptografa?\n\n1- Inserir chave;\n2- Inserir intervalo de chaves;\n3- Exibir a partir de todas as chaves;\n0- Voltar.\n\n - Sua escolha: ");
                    scanf("%d", &c2);

                    proceed = 0;

                    switch (c2)
                    {
                    case 1:

                        clear();
                        proceed = 1;
                        break;
                    
                    case 2:
                        clear();

                        printf("A partir de qual chave iniciar? (1 - 26)\n");
                        scanf("%d", &firstKey);

                        printf("\nAté qual chave deseja executar? (%d - 26)\n", firstKey);
                        scanf("%d", &lastKey);

                        printf("\nCom quantos caracteres deseja exibir as saidas?\n");
                        scanf("%d", &caracterQuant);

                        clear();
                        showKeyIntervalDecryption(inputFileContent, caracterQuant, firstKey, lastKey);
                        printf("\n\n");
                        proceed = 1;

                        break;

                    case 3:
                        clear();
                        printf("\nCom quantos caracteres deseja exibir as saidas?\n");
                        scanf("%d", &caracterQuant);

                        clear();
                        showKeyIntervalDecryption(inputFileContent, caracterQuant, 1, 26);
                        printf("\n\n");
                        proceed = 1;
                        break;

                    case 0:
                        clear();
                        proceed = 0;
                        break;

                    default:
                        clear();
                        proceed = 0;
                        printf("*Insira uma opcao valida.\n\n");

                        break;
                    }

                    if(c2 == 0){break;}
                    if(proceed == 0){continue;}

                    int key;

                    printf("A partir de qual chave deseja descriptografar? (%d - %d)\n", firstKey, lastKey);
                    scanf("%d", &key);

                    encryptText(inputFileContent, outputFileContent, -key);

                    clear();
                    printf("* Descriptografado com sucesso.\n\n");
                    break;

                }while (c2 != 0);
                
                c2 = 1;
                
                do
                {
                    printf("O que deseja fazer?\n\n1- Mostrar saida; \n2- Escrever a saida em um arquivo;\n0- Voltar.\n\n - Sua escolha: ");
                    scanf("%d", &c2);

                    switch (c2)
                    {
                    case 1:
                        clear();
                        printf("A saida foi:\n\n");
                        shoWText(outputFileContent);
                        printf("\n\n");
                        break;

                    case 2:
                        clear();

                        printf("Com qual nome salvar o arquivo? (0- voltar)\n");
                        gets(outputFileName);

                        clear();

                        if(strcmp(outputFileName, "0") == 0){
                            break;
                        }

                        writeOnFile(outputFileContent, outputFileName);
                        
                        printf("* Arquivo salvo.\n\n");
                        break;

                    case 0:
                        clear();
                        break;

                    default:
                        clear();
                        printf("* Insira uma opcao valida\n\n");
                        break;
                    }
                } while (c2 != 0);
                
            } while (c1 != 0);
            break;

        }

    }while (c0 != 0);

    return 0;
}