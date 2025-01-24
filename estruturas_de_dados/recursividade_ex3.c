#include <stdio.h>
int NinNUM(int num, int n){
	int cont=0;
	if(num>10){
		cont+=NinNUM(num/10, n);
		cont=(num%10==n)?cont+1:cont+0;
		return cont;
	}
	cont= (num%10==n)?cont+1:cont+0;
	return cont;
}

int somatorio(int x){
	int som=x;
	if(x!=1){
		som+=somatorio(x-1);
		return som;
	}
	return x;
}

int pot(int b, int e){
	int r = (e==0)? 1: b;
	if(e>1){
		r=pot(b,e-1)*b;
		return r;
	}
	return r;
}

int inv(int N){
	int q=N, x, cont=0;
	if(N>10){
		while(q>10){
			q=q/10;
			cont++;
		}
		x=(N%10)*pot(10,cont);
		x+=inv(N/10);
		return x;
	}
	return N;
}

int main(){
	//printf("%d\n", NinNUM(6228, 2));
	//printf("%d\n", pot(2, 10);
	//printf("%d\n", inv(5678));
	return 0;
}

