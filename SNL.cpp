// De tai Hoang Tuan Nhan + Vu Ngoc Son
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

#define max 2015
typedef char string[50];

struct element{			//dslk voi data luu gia tri tu 0-9, next luu dia chi tiep theo
	int data;
	element *next;
};

typedef element *SNL;

void InsertF(SNL &F, int x){		//chen 1 phan tu vao dau dslk
	SNL p=new element;
	p->data=x;
	p->next=F;
	F=p;
}

void conv(SNL &F, char *s){			//chuyen xau s thanh dslk
	for(int i=0;i<strlen(s);i++) InsertF(F,s[i]-48);
}

bool isFail(char *s){				//kiem tra xau s bi loi khong
	for(int i=1;s[i]!='\0';i++){
		if(s[i]>'9'||s[i]<'0') return 1;
	}
	if(s[0]=='-'&&s[1]=='\0') return 1;
	if(s[0]!='-'&&(s[0]>'9'||s[0]<'0')) return 1;
	return 0;
}

void dao(SNL &F){					//dao nguoc dslk
	if(F->next==NULL) return;
	SNL p_after,p_befor=F,p=F->next;
	F->next=NULL;
	while(p!=NULL){
		p_after=p->next;
		p->next=p_befor;
		p_befor=p;
		p=p_after;
	}
	F=p_befor;
}

void rutgon(SNL &F,bool &am){		//rut gon SNL
	dao(F);
	SNL p;
	while(F->data==0&&F->next!=NULL){
		p=F;
		F=F->next;
		delete p;
	}
	if(F->data==0) am=0;
	dao(F);
}

bool KhongBeHon(const SNL &F1,const SNL &F2){	//so sanh 2 SNL F1>=F2?
	SNL p=F1,q=F2;
	int nho=0;
	while(p!=NULL&&q!=NULL){
		nho=(p->data-q->data-nho<0);
		p=p->next;
		q=q->next;
	}
	while(p!=NULL){
		nho=(p->data-nho<0);
		p=p->next;
	}
	while(q!=NULL){
		nho=(-q->data-nho<0);
		q=q->next;
	}
	return (nho<1);
}

void Nhap(SNL &F,bool &am){					//nhap 1 SNL
	am=0;
	char *s=new char[max];
	fflush(stdin);
	gets(s);
	while(isFail(s)){
		printf("%cNhap lai: ",16);
		fflush(stdin);
		gets(s);
	}
	if(s[0]=='-'){
		int l=strlen(s);
		for(int i=0;i<l-1;i++) s[i]=s[i+1];
		s[l-1]='\0';
		am=1;
	}
	conv(F,s);
	delete s;
	rutgon(F,am);
}

void Xuat(SNL &F,int am){ //in ra SNL
	dao(F);				//SNL luu theo thu tu nguoc nen phai dao truoc khi in ra
	if(am) printf("-");
	SNL p=F;
	while(p!=NULL){
		printf("%d",p->data);
		p=p->next;
	}
	dao(F);
}

void INC(SNL &F,bool &am){		//tang SNL 1 don vi
	SNL p=F;
	int a,nho=1;
	if(!am){			//neu khong am
		while(p!=NULL){
			a=p->data+nho;
			nho=a>9;
			p->data=a%10;
			p=p->next;
		}
		if(nho){
			dao(F);
			InsertF(F,nho);
			dao(F);
		}
	}
	else{				//neu so am
		while(p!=NULL){
			a=p->data-nho;
			nho=a<0;
			p->data=(a+10)%10;
			p=p->next;
		}
		rutgon(F,am);
	}
}

void DEC(SNL &F,bool &am){	//giam SNL 1 don vi
	if(F->data==0){			//neu bang 0
		F->data=1;
		am=1;
		return;
	}
	SNL p=F;
	int a,nho=1;
	if(am){					//neu am
		while(p!=NULL){
			a=p->data+nho;
			nho=a>9;
			p->data=a%10;
			p=p->next;
		}
		if(nho){
			dao(F);
			InsertF(F,nho);
			dao(F);
		}
	}
	else{					//neu duong
		while(p!=NULL){
			a=p->data-nho;
			nho=a<0;
			p->data=(a+10)%10;
			p=p->next;
		}
		rutgon(F,am);
	}
}

void Delete(SNL &F){				//xoa dslk
	SNL p;
	while(F!=NULL){
		p=F;
		F=F->next;
		delete p;
	}
}

void Cong(const SNL &F1,const bool &am1,const SNL &F2,const bool &am2,SNL &F,bool &am){			//tinh tong 2 SNL
	SNL p=F1,q=F2;
	int a,nho=0;
	Delete(F);
	if (am1+am2!=1){			//neu cung dau
		if(am1+am2==0) am=0;
		else am=1;
		while(p!=NULL&&q!=NULL){
			a=p->data+q->data+nho;
			nho=a/10;
			a%=10;
			InsertF(F,a);
			p=p->next;
			q=q->next;
		}
		while(p!=NULL){
			a=p->data+nho;
			nho=a/10;
			a%=10;
			InsertF(F,a);
			p=p->next;
		}
		while(q!=NULL){
			a=q->data+nho;
			nho=a/10;
			a%=10;
			InsertF(F,a);
			q=q->next;
		}
		if(nho) InsertF(F,nho);
	}
	else{					//truong hop trai dau
		if(KhongBeHon(F1,F2)){
			p=F1; q=F2;
			if(am1) am=1;
			else am=0;
		}
		else{
			p=F2; q=F1;
			if(am1) am=0;
			else am=1;
		}
		while(q!=NULL){
			a=p->data-q->data-nho;
			nho=(a<0);
			a=(a+10)%10;
			InsertF(F,a);
			p=p->next;
			q=q->next;
		}
		while(p!=NULL){
			a=p->data-nho;
			nho=(a<0);
			a=(a+10)%10;
			InsertF(F,a);
			p=p->next;
		}
	}
	dao(F);
	rutgon(F,am);
}

void Tru(const SNL &F1,const bool &am1,const SNL &F2,const bool &am2,SNL &F,bool &am){		//tru 2 so nguyen lon
	Cong(F1,am1,F2,1-am2,F,am);
	rutgon(F,am);
}

void Nhan(const SNL &F1,const bool &am1,const SNL &F2,const bool &am2,SNL &F,bool &am){		//nhan 2 so nguyen lon
	if(am1+am2!=1) am=0;
	else am=1;
	Delete(F);
	SNL p=F1,q=F2,t,tem;
	while(p!=NULL){
		InsertF(F,0);
		p=p->next;
	}
	while(q!=NULL){
		InsertF(F,0);
		q=q->next;
	}
	q=F2;
	t=F;
	int a,b,nho=0;
	while(q!=NULL){
		tem=t;
		b=q->data;
		p=F1;
		while(p!=NULL){
			a=p->data*b+nho+tem->data;
			nho=a/10;
			tem->data=a%10;
			p=p->next;
			tem=tem->next;
		}
		while(nho){
			a=nho+tem->data;
			nho=a/10;
			tem->data=a%10;
			tem=tem->next;
		}
		q=q->next;
		t=t->next;
	}
	rutgon(F,am);
}

void Chia(const SNL &F1,const bool &am1,const SNL &F2,const bool &am2,SNL &F,bool &am){		//chia 2 so nguyen lon
	Delete(F);
	if(!KhongBeHon(F1,F2)){
		Delete(F);
		am=0;
		InsertF(F,0);
		return;
	}
	SNL SBC=NULL,SoChia=NULL;
	SNL p=F1,q=F2;
	while(p!=NULL){
		InsertF(SBC,p->data);
		p=p->next;
	}
	while(q!=NULL){
		InsertF(SoChia,q->data);
		q=q->next;
	}
	q=SBC;
	SNL t=SoChia;
	while(t!=NULL){
		q=q->next;
		t=t->next;
	}
	InsertF(SBC,0); 
	p=SBC;
	SNL SBT=NULL,SoTru=NULL;
	t=SoChia;
	while(t!=NULL){
		InsertF(SoTru,t->data);
		t=t->next;
	}
	t=SBC;
	while(t!=q){
		InsertF(SBT,0);
		t=t->next;
	}
	int x,a,nho;
	SNL tem;
	while(1){
		t=p;
		tem=SBT;
		while(t!=q){
			tem->data=t->data;
			t=t->next;
			tem=tem->next;
		}
		dao(SBT);
		x=0;
		while(KhongBeHon(SBT,SoTru)){
			nho=0;
			t=SBT; tem=SoTru;
			while(tem!=NULL){
				a=t->data-tem->data-nho;
				nho=a<0;
				t->data=(a+10)%10;
				t=t->next;
				tem=tem->next;
			}
			t->data-=nho;
			x++;
		}
		InsertF(F,x);
		dao(SBT);
		t=SBT;
		tem=p;
		while(tem!=q){
			tem->data=t->data;
			tem=tem->next;
			t=t->next;
		}
		if(q==NULL) break;
		p=p->next;
		q=q->next;
	}
	if(am1+am2!=1) am=0;
	else am=1;
	rutgon(F,am);
}

void Fibo(SNL &F,const long &n){		//tim so fibonaci thu n, bat dau tu n=0
	SNL F1=NULL,p,q,tem;
	InsertF(F1,1);
	Delete(F);
	InsertF(F,1);
	int a,nho;
	if(n>1){
		for(int i=2;i<=n;i++){
			p=F1;
			q=F;
			nho=0;
			while(p!=NULL){
				a=p->data+q->data+nho;
				nho=(a>9);
				p->data=a%10;
				p=p->next;
				q=q->next;
			}
			dao(F1);
			while(q!=NULL){
				a=q->data+nho;
				nho=(a>9);
				a%=10;
				InsertF(F1,a);
				q=q->next;
			}
			if(nho) InsertF(F1,nho);
			dao(F1);
			tem=F;
			F=F1;
			F1=tem;
 		}
	}
	delete(F1);
}

void giaithua(SNL &F,const long &n){
	Delete(F);
	InsertF(F,1);
	if(n<2) return;
	SNL SoNhan=NULL,Tich=NULL;
	bool SoNhan_sign=0,Tich_sign=0;
	InsertF(SoNhan,1);
	for(long i=2;i<=n;i++){
		INC(SoNhan,SoNhan_sign);
		Nhan(F,0,SoNhan,SoNhan_sign,Tich,Tich_sign);
		Delete(F);
		F=Tich;
		Tich=NULL;
	}
	Delete(SoNhan);
}

main(){
	SNL F=NULL,F1=NULL,F2=NULL;	//khoi tao dslk
	bool am,am1,am2;	//luu dau SNL
	long n;
	int cv;
	string s[9];
	strcpy(s[0],"TANG 1 SO NGUYEN LON THEM 1 DON VI");
	strcpy(s[1],"GIAM 1 SO NGUYEN LON DI 1 DON VI");
	strcpy(s[2],"TINH TONG 2 SO NGUYEN LON");
	strcpy(s[3],"TINH HIEU 2 SO NGUYEN LON");
	strcpy(s[4],"NHAN 2 SO NGUYEN LON");
	strcpy(s[5],"CHIA 2 SO NGUYEN LON");
	strcpy(s[6],"TIM SO THU N TRONG DAY FIBONACCI (BAT DAU TU N=0)");
	strcpy(s[7],"TINH N!");
	strcpy(s[8],"THOAT");
	char c0=176,c1=16,c2=26;
	unsigned char c3=254;
	do{
		system("cls");
		for(int i=0;i<104;i++) printf("%c",c0);
		printf("CHUONG TRINH XU LI SO NGUYEN LON");
		for(int i=0;i<114;i++) printf("%c",c0);
		for(int i=0;i<9;i++){
			printf("[%d]%c%-56s",i+1,16,s[i]);
			for(int i=0;i<20;i++) printf("%c",c0);
		}
		for(int i=0;i<70;i++) printf("%c",c0);
		printf("	  %cLuu y so nguyen lon nhap vao co dang 1234.. va -1234..",26);
		printf("\n%cNhap lua chon: ",c3);
		fflush(stdin); scanf("%d",&cv);
	switch(cv){
		case 1:
			printf("\n%cNhap so nguyen lon: ",c1);
			Nhap(F,am);
			printf("\n%cSo vua nhap F= ",c2);
			Xuat(F,am);
			INC(F,am);
			printf("\n%cSau khi tang 1 don vi, F= ",c3);
			Xuat(F,am);
			getch();
			Delete(F);
			break;
		case 2:
			printf("\n%cNhap so nguyen lon: ",c1);
			Nhap(F,am);
			printf("\n%cSo vua nhap F= ",c2);
			Xuat(F,am);
			DEC(F,am);
			printf("\n%cSau khi giam 1 don vi, F= ",c3);
			Xuat(F,am);
			getch();
			Delete(F);
			break;
		case 3:
			printf("\n%cNhap so nguyen lon thu nhat: ",c1);
			Nhap(F1,am1);
			printf("\n%cNhap so nguyen lon thu hai: ",c1);
			Nhap(F2,am2);
			Cong(F1,am1,F2,am2,F,am);
			printf("\n%c2 so vua nhap:",c2);
			printf("\n%cSo thu nhat F1= ",c2);
			Xuat(F1,am1);
			printf("\n%cSo thu hai F2= ",c2);
			Xuat(F2,am2);
			printf("\n%cTong 2 so: F1+F2= ",c3);
			Xuat(F,am);
			getch();
			Delete(F);
			Delete(F1);
			Delete(F2);
			break;
		case 4:
			printf("\n%cNhap so nguyen lon thu nhat: ",c1);
			Nhap(F1,am1);
			printf("\n%cNhap so nguyen lon thu hai: ",c1);
			Nhap(F2,am2);
			Tru(F1,am1,F2,am2,F,am);
			printf("\n%c2 so vua nhap:",c2);
			printf("\n%cSo thu nhat F1= ",c2);
			Xuat(F1,am1);
			printf("\n%cSo thu hai F2= ",c2);
			Xuat(F2,am2);
			printf("\n%cHieu 2 so: F1-F2= ",c3);
			Xuat(F,am);
			getch();
			Delete(F);
			Delete(F1);
			Delete(F2);
			break;
		case 5:
			printf("\n%cNhap so nguyen lon thu nhat: ",c1);
			Nhap(F1,am1);
			printf("\n%cNhap so nguyen lon thu hai: ",c1);
			Nhap(F2,am2);
			Nhan(F1,am1,F2,am2,F,am);
			printf("\n%c2 so vua nhap:",c2);
			printf("\n%cSo thu nhat F1= ",c2);
			Xuat(F1,am1);
			printf("\n%cSo thu hai F2= ",c2);
			Xuat(F2,am2);
			printf("\n%cTich 2 so: F1*F2= ",c3);
			Xuat(F,am);
			getch();
			Delete(F);
			Delete(F1);
			Delete(F2);
			break;
		case 6:
			printf("\n%cNhap so nguyen lon thu nhat: ",c1);
			Nhap(F1,am1);
			printf("\n%cNhap so nguyen lon thu hai: ",c1);
			Nhap(F2,am2);
			printf("\n%c2 so vua nhap:",c2);
			printf("\n%cSo thu nhat F1= ",c2);
			Xuat(F1,am1);
			printf("\n%cSo thu hai F2= ",c2);
			Xuat(F2,am2);
			if(F2->data==0&&F2->next==NULL){
				printf("\n%cKhong the chia cho 0",c3);
				getch();
				break;
			}
			Chia(F1,am1,F2,am2,F,am);
			printf("\n%cThuong 2 so: F1/F2= ",c3);
			Xuat(F,am);
			getch();
			Delete(F);
			Delete(F1);
			Delete(F2);
			break;
		case 7:
			printf("\n%cDay so Fibonacci 1,1,2,3,5,8,13,21... \n%ctuong ung voi N= 0,1,2,3,4,5,6 ,7 ... ",c1,c1);
			printf("\n%cNhap N= ",c1); fflush(stdin); scanf("%d",&n);
			while(n<0){
				printf("\n%cNhap lai N= ",c1); fflush(stdin); scanf("%d",&n);
			}
			Fibo(F,n);
			printf("\n%cSo Fibonacci ung voi N= %d la: Fibo(%d)= ",c3,n,n);
			Xuat(F,0);
			getch();
			Delete(F);
			break;
		case 8:
			printf("\n%cNhap N=",c1); fflush(stdin); scanf("%d",&n);
			while(n<0){
				printf("\n%cNhap lai N= ",c1); fflush(stdin); scanf("%d",&n);
			}
			giaithua(F,n);
			printf("\n%c%5d!= ",c3,n);
			Xuat(F,0);
			getch();
			Delete(F);
			break;
	}
	}while (cv!=9);
}
