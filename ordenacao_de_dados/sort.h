void printVet(int *V, int n){
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d  ", V[i]);
    }
    printf("\n");
}

void bubleSort(int *V, int n){
    int temp, i, run;
    // 0(falso) 1(true)
    do{
        run = 0;
        for (i = 0; i < n - 1; i++){//ultimo não tem vizinho a direita
            if (V[i] > V[i + 1]){
                temp = V[i + 1];
                V[i + 1] = V[i];
                V[i] = temp;
                run = 1;
            }
        }
        // ao fim do laço, se não cair nenhuma vez no if então não houve nenhuma troca, vetor ordenado
    } while (run == 1);
}

void selectSort(int *V, int n){
    int i=0, j, temp, i_low;
    //i_low aponta para onde esta o menor elemento naquela subarray
    while(i < n-1){
        i_low = i;
        for(j=i+1; j<n; j++){//j sempre a frente de i
            if(V[j] < V[i_low]){
                i_low=j;
            }
        }
        //achado a posição do menor elemento substituir em i e avancar 1 
        temp=V[i_low];
        V[i_low]=V[i];
        V[i]=temp;
        i++;
    }
}

void insertSort(int *v, int n){
    int i, j, temp;
    for(i=1; i<n; i++){
        j=i;
        while(j>0 && v[j]<v[j-1]){//v[i]posição errada
            temp=v[j];
            v[j]=v[j-1];
            v[j-1]=temp;
            j--;
        }
    }
}

void quickSort(int *v, int l, int r){
    int i=l, j=r, pivo=v[(l+r)/2], temp;
    if(l<r){
        while(i<=j){
            while(v[i]<pivo){//achar onde sera substituido no lado i
                i++;
            }
            while(v[j]>pivo){//achar onde sera substituido no lado j
                j--;
            }
            if(i<=j){//evita trocar valores na ordem errada
                temp=v[j];
                v[j]=v[i];
                v[i]=temp;
                i++;
                j--;
            }
        }
        quickSort(v, l, j);//j ficara antes do pivo e delimitara o fim do subvetor esquerdo
        quickSort(v, i, r);//i ficara depois do pivo e delimita o inicio so subvetor dirteito
    }
}

void seqVet(int *v, int size){//
    //gera um vetor  sequencial com elementos não repetidos e aleatorios, para testes
    int i, temp, x;
    for(i=0; i<size; i++){
        v[i]=i;
    }
    //embaralha o vetor
    for(i=0; i<size; i++){
        x=rand()%size;
        temp=v[x];
        v[x]=v[i];
        v[i]=temp;
    }
}