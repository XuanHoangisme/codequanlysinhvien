#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include <iomanip>
#include <conio.h>
#include <cctype>

using namespace std;
// mục login******************************************
struct login{
	string user;
	string password;
};
typedef struct login LOGIN;

void Dangnhap (ifstream &f,LOGIN &sv){
	getline(f,sv.user,',');
	getline(f,sv.password,',');
}
string passwordInput(){
    string pw;
    for (char c; (c = getch()); ) {
        if (c == '\n' || c == '\r') { 
            cout << "\n";
            break;
        } else if (c == '\b') { 
            cout << "\b \b";
            if (!pw.empty()) pw.erase(pw.size()-1);
        } else if (c == -32) { 
            _getch(); 
        } else if (isprint(c)){ 
            cout << '*';
            pw += c;
        }
    }
    return pw;
}
// mục tùy chọn 1 **************************************
struct date{
	string ngay ;
	string thang;
	string nam ;
};
typedef struct date DATE;

struct thongtin{
	string TK;
	string hoten;
	string MSSV;
	DATE ngaysinh;
	string khoa;
	string lop;
};
typedef struct thongtin THONGTIN;

void Doc_ngay_thang(ifstream &file,DATE &date){
	getline(file,date.ngay,'/');
	getline(file,date.thang,'/');
	getline(file,date.nam,',');
}

struct node{
	THONGTIN data;
	node *next;
};
typedef struct node NODE;
struct list{
	NODE *head;
	NODE *tail;
};
typedef struct  list LIST;
void khoitaodanhsach( LIST &l){
	l.head=NULL;
	l.tail=NULL;
}
node *khoitaonode(THONGTIN x){
	NODE *p = new NODE;
	if(p==NULL){
		cout<<"/n Cap nhat that bai";
		return NULL;
	}
	p->data=x;
	p->next=NULL;
	return p;
}

void themcuoi(LIST &l,NODE *p){
	if(l.head==NULL) {
	l.head=p;
	l.tail=p;
}
    else{
    	l.tail->next=p;
    	l.tail=p;
	}
}
void xoanodedau(LIST &l){
	if(l.head==NULL) return;
	NODE *p=l.head;
	l.head=l.head->next;
	delete p;
}
void xoanodecuoi(LIST &l){
	if(l.head==NULL) return;
	for(NODE *k=l.head;k!=NULL;k=k->next){
		if(k->next==l.tail){
			delete l.tail;
			k->next=NULL;
			l.tail=k;
		}
	}
}
void xoanode(LIST &l,string tai_khoan){
	if(l.head->data.TK==tai_khoan){
		xoanodedau(l);
		return;
	}
	if (l.tail->data.TK==tai_khoan){
		xoanodecuoi(l);
		return;
	}
	for(NODE *k=l.head;k!=NULL;k=k->next){
		NODE *m;
		if(k->data.TK==tai_khoan){
		m->next=k->next;
		delete k;	
    }m=k;
}
}

void Doc_Thong_1_Sinh_Vien(ifstream &file,THONGTIN &sv){
	getline(file, sv.TK,',');
	getline(file, sv.hoten,',');
	getline(file, sv.MSSV,',');
	Doc_ngay_thang(file,sv.ngaysinh);
	getline(file, sv.khoa,',');
	getline(file, sv.lop);
}
void xuat(THONGTIN sv){
    cout<<"\n--------------------------------------------------------";
	cout<<"\n- Ho va ten:         "<<sv.hoten;
	cout<<"\n- Ma so sinh vien:   "<<sv.MSSV;
	cout<<"\n- Ngay sinh:         "<<sv.ngaysinh.ngay<<"/"<<sv.ngaysinh.thang<<"/"<<sv.ngaysinh.nam;
	cout<<"\n- Khoa:              "<<sv.khoa;
	cout<<"\n- Lop:               "<<sv.lop<<"\n";
	cout<<"--------------------------------------------------------\n";
}
void Doc_Danh_Sach_Sv(ifstream &file,LIST &l,string tai_khoan){
	while(!file.eof()){
		THONGTIN sv;
		Doc_Thong_1_Sinh_Vien(file,sv);
		NODE *p=khoitaonode(sv);
		themcuoi(l,p);}
	}
	

void	xem(ifstream &file,LIST &l,string tai_khoan){
	//Hiện thông tin sinh viên đang đăng nhập
		for(NODE *k=l.head;k!=NULL;k=k->next){
		if(k->data.TK==tai_khoan){
		cout<<"\n\n\t\tTHONG TIN SINH VIEN\n";
		xuat(k->data);
	    }
	}
	//thay đôir thông tin cá nhân 
	cout<<"bam 1 de thay doi thong tin ";
	int thaydoi;
	cin>>thaydoi;
	if (thaydoi==1){
		xoanode(l,tai_khoan);
	 cout<<"vui long cap nhat lai thong tin:\n";
	THONGTIN sv;
	NODE *g=khoitaonode(sv);
	g->data.TK=tai_khoan;
	string o;
	cout<<"- Ho va ten:         ";cin.ignore();getline(cin,o);
	g->data.hoten=o;
	cout<<"- Ma so sinh vien:   ";cin>>o;g->data.MSSV=o;
	cout<<"- Ngay sinh:         ";cin>>o;g->data.ngaysinh.ngay=o;
	cout<<"- Thang sinh:        ";cin>>o;g->data.ngaysinh.thang=o;
	cout<<"- Nam sinh:          ";cin>>o;g->data.ngaysinh.nam=o;
	cout<<"- Khoa:              ";cin>>o;g->data.khoa=o;
	cout<<"- Lop:               ";cin>>o;g->data.lop=o;
	themcuoi(l,g);
	cout<<"ban da sua thong tin thanh cong ^^";
	file.close();
	ofstream luu;
	luu.open("THONGTIN2.TXT",ios::trunc);
	for(NODE *k=l.head;k!=NULL;k=k->next){
		if(k->data.TK==tai_khoan) xuat(k->data);
		luu<<k->data.TK<<","<<k->data.hoten<<","<<k->data.MSSV<<",";
		luu<<k->data.ngaysinh.ngay<<"/"<<k->data.ngaysinh.thang<<"/";
		luu<<k->data.ngaysinh.nam<<","<<k->data.khoa<<","<<k->data.lop;
		if(k->next==NULL) break;luu<<"\n";
    } 
    cout<<"\n NEU THONG TIN SAI THI BAN CO THE AN LAI MUC 1 DE NHAP LAI ^^";
         luu.close();
        }
     }

//mục tùy chọn 2 va 3********************************************

struct thongtindiem{
    string taikhoan;
    int diemrenluyen;
    int somonhoc;
    string tenmon;
	int  diemgk;
	int diemck;
	float  heso;
	int sotin;
};
typedef struct thongtindiem THONGTINDIEM;

struct node2{
	THONGTINDIEM data2;
	node2 *next2;
	node2 *diem2;
};
typedef struct node2 NODE2;

struct list2{
	NODE2 *head2;
	NODE2 *tail2;
	NODE2 *DIEM;
};
typedef struct  list2 LIST2;
void khoitaodanhsachdiem( LIST2 &l2){
	l2.head2=NULL;
	l2.tail2=NULL;
	l2.DIEM=NULL;
}

node2 *khoitaonode2(THONGTINDIEM x){
	NODE2 *p = new NODE2;
	if(p==NULL){
		cout<<"/n Cap nhat that bai";
		return NULL;}
	p->data2=x;
	p->next2=NULL;
	p->diem2=NULL;	
	return p;
}


void themnnext2(LIST2 &l2,NODE2 *p){
	if(l2.head2==NULL) {
	l2.head2=p;
	l2.tail2=p;
	l2.DIEM=p;
}
    else{
    	l2.tail2->next2=p;
    	l2.DIEM=p;
    	l2.tail2=p;
	}
}
void themdiem2(LIST2 &l2,NODE2 *p){
	l2.DIEM->diem2=p;
	l2.DIEM=p;
}
void doc_1_thong_tin_diem(ifstream &file2,THONGTINDIEM &sv2){
	getline(file2,sv2.taikhoan,',');
	file2>>sv2.diemrenluyen;
	file2>>sv2.somonhoc;
}
void doc_1_diem(ifstream &file2,THONGTINDIEM &sv2){
	getline(file2,sv2.tenmon,'-');
	file2>>sv2.diemgk;
	file2>>sv2.diemck;
    file2>>sv2.heso;
    file2>>sv2.sotin;
}
void xuatdiem(THONGTINDIEM sv2){
	cout<<"\n monhoc:        "<<sv2.tenmon;
	cout<<"\n diem giua ky:  "<<sv2.diemgk;
	cout<<"\n diem cuoi ky:  "<<sv2.diemck;
	cout<<"\n he so:         "<<sv2.heso;
	cout<<"\n so tin mon hoc "<<sv2.sotin;
	cout<<"\n----------------------------\n";
}
void doc_danh_sach_diem(ifstream &file2,LIST2 &l2){
		while(!file2.eof()){
		THONGTINDIEM sv2;
		doc_1_thong_tin_diem(file2,sv2);
		NODE2 *p=khoitaonode2(sv2);
		themnnext2(l2,p);
		int n=sv2.somonhoc;
		for (int i=1;i<=n;i++){
			doc_1_diem(file2,sv2);
			NODE2 *p=khoitaonode2(sv2);
			themdiem2(l2,p);
		}
}
}
	
void diemcuahocsinh(ifstream &file2,LIST2 &l2,string tai_khoan,int chaymuc){
     if(chaymuc==2){
	for(NODE2 *k=l2.head2;k!=NULL;k=k->next2){	
	 if( k->data2.taikhoan==tai_khoan){
	   cout<<"\n\n   DIEM CUA SINH VIEN  \n";
	   cout<<"----------------------------";
	    for(NODE2 *h=k->diem2;h!=NULL;h=h->diem2){
	   	xuatdiem(h->data2);}
	   	break;
		}
       }
	}
	if(chaymuc==3){
		for(NODE2 *k=l2.head2;k!=NULL;k=k->next2){
			if( k->data2.taikhoan==tai_khoan){
		cout<<"\n\n  DIEM REN LUYEN CUA BAN LA: "<<k->data2.diemrenluyen<<"\n";
        }
	}
}
file2.close();
}
//chay muc 4******************************************
struct monhockisau{
    string tk4;
    int somonkisau;
    string monkisau;
};
typedef struct monhockisau  KISAU;

struct node4{
	KISAU data4;
	node4 *next4;
	node4 *mon4;
};
typedef struct node4 NODE4;

struct list4{
	NODE4 *head4;
	NODE4 *tail4;
	NODE4 *MON;
};
typedef struct  list4 LIST4;
void khoitaodanhsachmonhoc( LIST4 &l4){
	l4.head4=NULL;
	l4.tail4=NULL;
	l4.MON=NULL;
}

node4 *khoitaonode4(KISAU x){
	NODE4 *p = new NODE4;
	if(p==NULL){
		cout<<"/n Cap nhat that bai";
		return NULL;}
	p->data4=x;
	p->next4=NULL;
	p->mon4=NULL;	
	return p;
}

void themnnext4(LIST4 &l4,NODE4 *p){
	if(l4.head4==NULL) {
	l4.head4=p;
	l4.tail4=p;
	l4.MON=p;
}
    else{
    	l4.tail4->next4=p;
    	l4.MON=p;
    	l4.tail4=p;
	}
}
void themmon4(LIST4 &l4,NODE4 *p){
	l4.MON->mon4=p;
	l4.MON=p;
}

void doc_1_thong_tin_mon(ifstream &file4,KISAU &sv4){
	getline(file4,sv4.tk4,',');
	file4>>sv4.somonkisau;
}
void doc_1_mon(ifstream &file4,KISAU &sv4){
	getline(file4,sv4.monkisau,',');
}
void xuatdiem(KISAU sv4){	
	cout<<"\n mon hoc: "<<sv4.monkisau;
	cout<<"\n-------------------\n";
}
void doc_danh_sach_mon(ifstream &file4,LIST4 &l4){
		while(!file4.eof()){
		KISAU sv4;
		doc_1_thong_tin_mon(file4,sv4);
		NODE4 *p=khoitaonode4(sv4);
		themnnext4(l4,p);
		int n=sv4.somonkisau;
		for (int i=1;i<=n-1;i++){
			doc_1_mon(file4,sv4);
			NODE4 *p=khoitaonode4(sv4);
			themmon4(l4,p);
		}
		getline(file4,sv4.monkisau);
		NODE4 *pm=khoitaonode4(sv4);
			themmon4(l4,pm);
		}	
}
void xemmonhockisau(ifstream &file4,LIST4 &l4,string tai_khoan){
	 for(NODE4 *k=l4.head4;k!=NULL;k=k->next4)
		    if(k->data4.tk4==tai_khoan){
				for(NODE4 *h=k->mon4;h!=NULL;h=h->mon4){
					cout<<h->data4.monkisau<<"  ";
				}
		         cout<<"\n--------------------------------------------\n";
             }
}

void chinhmonhockisau(ifstream &file4,LIST4 &l4,string tai_khoan){
	cout<<"\n\n    Thong tin mon hoc sinh vien\n ";
	cout<<"\n--------------------------------------------\n";
	xemmonhockisau(file4,l4,tai_khoan); 

	//thay đôi thông tin mon hoc
	bool ketthuc=false;
	while(ketthuc=true){
    cout<<"\n bam so khac (1,2,3) neu muon sang muc khac";
	cout<<"\n bam (1/2/3) de (them/sua/xoa) mon hoc:"; 
	int thaydoi;
	cin>>thaydoi;
	if((thaydoi>3)||(thaydoi<1)) {ketthuc=true;break;}
	else{
	if(thaydoi==1){
		int dathem=0;
		for(NODE4 *k=l4.head4;k!=NULL;k=k->next4){
			if(k->data4.tk4==tai_khoan){
			  for(NODE4 *h=k->mon4;h!=NULL;h=h->mon4){
			  	if(h->mon4==NULL){
			  		cout<<"\n ban muon them mon:";
			  	    NODE4 *p=new NODE4;
			  	    	cin>>p->data4.monkisau;
                     	p->next4=NULL;
                    	p->mon4=NULL;
			        h->mon4=p;
			        k->data4.somonkisau++;
			        dathem=1;
			         cout<<" ban da them thanh cong ^^";
			         cout<<"\n--------------------------------------------\n";
			         if(dathem==1)break;
				  }
			  }
		    }
			   if(dathem==1) break;  
		}
	}
	if (thaydoi==2){
		string sua;int dasua=0;
		cout<<"\n ban muon sua mon: ";cin>>sua;
		for(NODE4 *k=l4.head4;k!=NULL;k=k->next4){
			if(k->data4.tk4==tai_khoan)
			  for(NODE4 *h=k->mon4;h!=NULL;h=h->mon4){
			  	if(h->data4.monkisau==sua){
			  		 dasua=1;
			  		cout<<" sua thanh: ";
			  		cin>>h->data4.monkisau;
			  		 cout<<" ban da sua thanh cong ^^";
			         cout<<"\n--------------------------------------------\n";
				  }
			  }	
        }
		if(dasua==0){
			cout<<"\n ! mon ban tim khong ton tai @@";
			cout<<"\n--------------------------------------------\n";
		}  
    }
    if(thaydoi==3){
    	string xoa;int daxoa=0;
    	cout<<"\n ban muon xoa mon: ";cin>>xoa;
    	for(NODE4 *k=l4.head4;k!=NULL;k=k->next4){
			if(k->data4.tk4==tai_khoan)
			  for(NODE4 *h=k->mon4;h!=NULL;h=h->mon4){
			  	if((h==k->mon4)&&(h->data4.monkisau==xoa)){
			  		k->mon4=h->mon4;delete h;daxoa=1;
				  }
				  NODE4 *temp=h->mon4;
				if(temp->data4.monkisau==xoa){
				   h->mon4=temp->mon4;
				   delete temp;daxoa=1;	
				  }    
				if(daxoa==1){
				   cout<<"\n ban da xoa thanh cong ^^"; 
				   k->data4.somonkisau--;
				   cout<<"\n--------------------------------------------\n";
    	           break;
    	           }
    	        }
    	    if(daxoa==1)break; 
	    }
	     if(daxoa==0){
		       cout<<"\n ! mon ban tim khong ton tai @@" ;
    	       cout<<"\n--------------------------------------------\n";
	    }
    }
    xemmonhockisau(file4,l4,tai_khoan);
    	ofstream luu4;
	luu4.open("MONHOC.TXT",ios::trunc);
		for(NODE4 *k=l4.head4;k!=NULL;k=k->next4){
		    luu4<<k->data4.tk4<<","<<k->data4.somonkisau;
			  for(NODE4 *h=k->mon4;h!=NULL;h=h->mon4){
			  	luu4<<h->data4.monkisau;
			  	if((k->next4==NULL)&&(h->mon4==NULL)) break;
			  	if(h->mon4==NULL) luu4<<"\n";
			  	else luu4<<",";
			    }
	     }
	     luu4.close();
      }
    }
}
//chay muc 5******************************************
void hocbong(ifstream &file2,LIST2 &l2,ifstream &file,LIST &l,string tai_khoan){
    float GPA=0,sumall=0,tin=0,diemrl=0;string khoa_tk;
  for(NODE2 *k=l2.head2;k!=NULL;k=k->next2){	
	 if( k->data2.taikhoan==tai_khoan){
	 	diemrl=k->data2.diemrenluyen;
	    for(NODE2 *h=k->diem2;h!=NULL;h=h->diem2){
	        float sum=0;
	   	    sum=sum+h->data2.diemgk*h->data2.heso;
	   	    sum=sum+h->data2.diemck*(1-h->data2.heso);
	   	    sum=roundf(sum*100)/100;
	   	    sumall=sumall+sum*h->data2.sotin;
	   	    tin=tin+h->data2.sotin;}
	   	break;    }
	   }
	   GPA=(sumall/tin)*4/10;GPA=roundf(GPA*100)/100;
	   cout<<"\n Diem GPA ki truoc cua ban:        "<<GPA;
	   cout<<"\n Diem ren luyen ki truoc cua ban:  "<<diemrl;
	  for(NODE *k=l.head;k!=NULL;k=k->next){
	  	if(k->data.TK==tai_khoan) khoa_tk=k->data.khoa;
	  }
	ifstream file5;
	file5.open("THONGTINHOCBONG.TXT",ios::in);
	string khoa_vien;float moc_tk;int moc_rl;
	while (!file5.eof()){
		getline(file5,khoa_vien,',');
		file5>>moc_tk;
		file5>>moc_rl;
	    if(khoa_vien==khoa_tk){
		  if((GPA>=moc_tk)&&(diemrl>=moc_rl))
		  	cout<<"\n Chuc mung ban dat duoc hoc bong {$~$}";
		  else cout<<"\n Hien tai chua co thong tin ban duoc hoc bong ^^";
        break;		  	  
		}	
	}
	file5.close();
}
//chay muc 6****************************************************

void lich_thi(LIST2 &l2,string tai_khoan){
	int cothi=0;
	cout<<"\n\tLICH THI CUA BAN: \n\n";
	cout<<"--------------------------------\n";
		ifstream file6;
	file6.open("LICHTHI.TXT",ios::in);
	for(NODE2 *k=l2.head2;k!=NULL;k=k->next2)
	   if(k->data2.taikhoan==tai_khoan){
	     	string thoigian,mh;
	while(!file6.eof()){
		getline(file6,mh,',');
		getline(file6,thoigian);
		for(NODE2 *h=k->diem2;h!=NULL;h=h->diem2){
	     	if(mh==h->data2.tenmon){
	     	cout<<mh<<":"<<setw(10-mh.length()+thoigian.length())<<thoigian<<"\n";
	     	cothi=1;
	        }
	    }
    }
}
    if(cothi==0) cout<<"HIEN TAI CHUA CO LICH THI CHO BAN ^^";
	file6.close();
}

void pressAnyKey() {
    cout << "\n\nBam phim bat ky de tiep tuc...\n";
    getchar();
    system("pause");
    system("cls");
}
//chay ham main************************************************
int main(){
	int key,d=0,a=0,chaymuc=0;string tai_khoan,mat_khau;
	while(a!=1){
	cout<<"=================================================\n";	
    cout<<"                   DANG NHAP                     \n";
    cout<<" TAI KHOAN: ";cin>>tai_khoan;
    cout<<" MAT KHAU:  ";mat_khau=passwordInput();
    cout<<"=================================================\n" ;
	ifstream f;
	f.open("input.txt",ios::in);
	LOGIN sv;
	while(!f.eof()){
	Dangnhap(f,sv);
	if(tai_khoan==sv.user){
	   d++; 
	   if(mat_khau==sv.password){
	   	cout<<"DANG NHAP THANH CONG\n";
	   	a++;
	   }	
	    else {
		cout<<"MAT KHAU SAI\n";
		     }
     	}
	}
	if (d==0) cout<<"TAI KHOAN KHONG TON TAI\n ";
	system("pause");
	system("cls");
	f.close();}
//tao danh sach lien ket *****************************
    ifstream file;
	file.open("THONGTIN2.TXT",ios::in);
	LIST l;
	khoitaodanhsach(l);
	Doc_Danh_Sach_Sv(file,l,tai_khoan);
	ifstream file2;
	file2.open("THONGTINDIEM.TXT",ios::in);
	LIST2 l2;
	khoitaodanhsachdiem(l2);
    doc_danh_sach_diem(file2,l2);
    ifstream file4;
	file4.open("MONHOC.TXT",ios::in);
	LIST4 l4;
	khoitaodanhsachmonhoc(l4);
	doc_danh_sach_mon(file4,l4);
	file4.close();
    
//bang thao tác****************************************************

    while(true) {
        cout << "*************************MENU**************************\n";
        cout << "**  1. Xem va chinh sua thong tin ca nhan.           **\n";
        cout << "**  2. Hien thi bang diem hoc tap.                   **\n";
        cout << "**  3. Hien thi bang diem ren luyen.                 **\n";
        cout << "**  4. Them/sua/xoa danh sach mon hoc theo ky.       **\n";
        cout << "**  5. Thong tin ve hoc bong duoc nhan.              **\n";
        cout << "**  6. Quan li va thong bao lich thi.                **\n";
        cout << "**  0. Dang xuat                                     **\n";
        cout << "*******************************************************\n";
        cout << "Nhap tuy chon: ";
        cin >> key;
        switch(key){
            case 1:
                cout << "\n1. Xem va chinh sua thong tin ca nhan.";
                xem(file,l,tai_khoan); 
				pressAnyKey(); 
                break;
            case 2:
                cout << "\n2. Hien thi bang diem hoc tap. ";
                chaymuc=2;
                diemcuahocsinh(file2,l2,tai_khoan,chaymuc);
                pressAnyKey();
                break;
            case 3:
                cout << "\n3. Hien thi bang diem ren luyen.";
                chaymuc=3;
                diemcuahocsinh(file2,l2,tai_khoan,chaymuc); 
                pressAnyKey();
                break;
            case 4:
                cout << "\n4. Them/sua/xoa danh sach mon hoc theo ky.";
                chinhmonhockisau(file4,l4,tai_khoan);   
                pressAnyKey();
                break;
            case 5:
                cout << "\n5. Thong tin ve hoc bong duoc nhan";
                chaymuc=5;
               hocbong(file2,l2,file,l,tai_khoan);
                pressAnyKey();
                break;
            case 6:
                cout << "\n6. Quan li va thong bao lich thi.";
                lich_thi(l2,tai_khoan);
                pressAnyKey();
                break;
           
            case 0:
                cout << "\nBan da dang xuat ^^ !";
                return 0;
            default:
                cout << "\nKhong co chuc nang nay!";
                cout << "\nHay chon chuc nang trong hop menu.";
                pressAnyKey();
                break;
        }
    }
}
