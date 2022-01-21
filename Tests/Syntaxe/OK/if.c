void main(){
	int a=1; 
	int b = 0;
	if(a){
		print("a different de 0\n");
	}
	if(a == b){
		print("a different de 0\n");
	}
	else{
		print("default print \n");
	}
	if(a<1){
		print("a inférieur à 1\n");
	}
	if(a>1){
		print("a supérieur à 1\n");
	}
	if(a<=1){
		print("a inférieur à 1\n");
	}
	if(a>=1){
		print("a supérieur à 1\n");
	}
	if(!a){
		print("a vaut 0\n");
	}
	if(a!=0){
		print("a different de 0\n");
	}
	if((a==1)||(b==0)){
		print("a ou b\n");		
	}
	if((a==1)&&(b==0)){
		print("a et b\n");		
	}
}
