
/* Restaurant Management System for Final Project */

#include<ctype.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<windows.h>


/* Constants */
#define F "\x1b[1;91m" // Red 
#define G "\x1b[1;32m" // Green
#define H "\x1b[3;37m" //  Italic 
#define R "\x1b[0m" // Reset  
#define O "\x1b[30;107m" // White Background 
#define S "\x1b[2m" // Faint
#define W "\x1b[1;37m" // W
#define CLR system("cls") // Clear screen 
#define SPASI printf("%s", spasi)
/*---------------------------------*/


/* Global Variables */

FILE *fp, *ft; // pointers 
int jmlh_menu = 5;
bool hides = FALSE; // set 
char data_user[100], order_user[100];

struct sort_f{
    int s_jumlah;
    int s_harga;
    char s_nama[16];
}linez[128];

/* -------------------------------------------------------------------------- */


/* Function prototypes */

void intro(); void lobby(); void credits(); void header();   void credits(); void exits(); 
void menu();  void art();   void chinese(); void japanese(); void western(); 

void login(); void pembayaran(); void signup(); 
void edit();  void edit_menu();  void list_ord(int y);

void hide(bool hides);
void post(int x, int y);
void gotoxy(int x, int y);
void p(int x, int y, const char *format, ...);

void cursor_control(int num_options, char options[][16], void (*fns[])(void), bool callob);
void lobby_control(void (*fns[])(void));
void intro_control(void (*fns[])(void));
void food_control(int jmlh_menu, char nama_makanan[][16], int harga[], int callf);

void shp_cart(bool lizt);
void food(int jmlh_menu, char nama[][16], int harga[], int callf);
void update_food(const char *file, const char *inp_nama, int inp_jumlah, int inp_harga, bool edit);

/* --------------------------------------------------------------------------- */


/* 14 Functions dibawah ini berfungsi sebagai display output dalam program ini */

void art(){

    p (22,6," _      __    __                     __     ");
    p (22,5,"| | /| / /__ / /______  __ _  ___   / /____ ");
    p (22,4,"| |/ |/ / -_) / __/ _ \\/  ' \\/ -_) / __/ _ \\ ");
    p (22,3,"|__/|__/\\__/_/\\__/\\___/_/_/_/\\__/  \\__/\\___/ ");
    p (35,2,"   ____          _ __     ___          __                          __");
    p (35,1,"  / __/_ _____  (_) /    / _ \\___ ___ / /____ ___ _________ ____  / /_");   
    p (35,0," _\\ \\/ // / _ \\/ / _ \\  / , _/ -_|_-</ __/ _ `/ // / __/ _ `/ _ \\/ __/");   
    p (35,-1,"/___/\\_,_/_//_/_/_.__/ /_/|_|\\__/___/\\__/\\_,_/\\_,_/_/  \\_,_/_//_/\\__/ ");  

}

void intro(){ CLR;
    
    art();
    p (23, -5, W"[Sign Up]"); 
    p (-15,-5, "[Login]");				 		 
    p (4,  -5, "[Credits]");				 		 
    p (3,  -8, "[Exit.]");				 		 
    
    void (*fns[4])(void) = {signup, login, credits, exits};
    intro_control(fns);

}

void lobby(){ CLR;
    
    p (5,   6, H"Lobby-Resto"R);
    p (25,  2, W"[Order Makanan]");
    p (-10, 2, "[List Orderan]");
    p (22, -2, "[Pembayaran]");
    p (-10,-2, "[Edit]");
    p (3,-  6, "[Exits]"R);

    void (*fns[4])(void) = {menu, pembayaran, edit_menu, exits};
    lobby_control(fns);

}

void menu(){ CLR; // Menu Option
    
    p (5,5 , H"List Menu"R);
    p (9,1 , W"[1] Chinese Food");
    p (9,-2, "[2] Japanese Food");
    p (9,-5, "[3] Western Food"R);
    char options[3][16] = {"Chinese Food", "Japanese Food", "Western Food"};
    void (*fns[3])(void) = {chinese, japanese, western};
    cursor_control(3, options, fns, true); // pergi ke plihan user 

}

void header(){

	p (6, 9 , H"Daftar Menu"R);
	p (18,-7, S"Tekan ESC untuk melihat list menu."R);

}

void chinese(){ // Chinese Menu

    char nama[5][16] = {"Capcay","Wonton", "Dimsum", "Kungpao-Chicken", "Hot-Pot"};
    int harga[5] = {20000, 25000, 30000, 30000, 40000};
    food(jmlh_menu, nama, harga, 1);

}

void japanese(){ // Japanese Menu

    char nama[5][16] = {"Onigiri","Udon", "Yakisoba", "Sushi", "Raw-Tuna"};
    int harga[5] = {20000, 25000, 30000, 40000, 50000};
    food(jmlh_menu, nama, harga, 2);

}

void western(){ // Western Menu

    char nama[5][16] = {"Mac-N-Cheese","Spaghetti", "Aglio-Olio", "Pizza", "Rendang"};
    int harga[5] = {20000, 25000, 30000, 40000, 99000};
    food(jmlh_menu, nama, harga, 3);

}

void food(int jmlh_menu, char nama[][16], int harga[], int callf){ CLR;
    
    header();
    
    for(int i=0 ;i<jmlh_menu; i++){
        p (18, 5-(2*i), "[%d] %s\n", (i+1), nama[i]);
        p (-8, 5-(2*i), "Rp%d\n", harga[i]);
    }

    food_control(jmlh_menu, nama, harga, callf);

}

char *format_duit(int duit, char *str){

    char temp[5];
    
    if(duit<1000.00){

        sprintf(str, "%d", duit);
        return str;
    
    }

    format_duit(duit/1000, str);
    sprintf(temp, ".%03d", duit%1000);
    strcat(str,temp);
    
    return str;

}

void waktu(int x, int y){

    char jam[10], buffer[80];
    
    time_t rawtime = time(NULL);
    struct tm *timeinfo = localtime(&rawtime);
    strftime(jam, sizeof(jam), "%H:%M", timeinfo);
    strftime(buffer, 80, "%d/%m/%Y", timeinfo);
    
    p (-13, x, "%s WIB  ", jam);
    p (-12, y, "%s  ", buffer);

}

void edit_menu(){ CLR;
    
    p (14,   3, "Pilih menu yang ingin di edit");
    p (24,  -1, "[Edit Data]");
    p (3,   -1, "[Lobby]");
    p (-14, -1, "[Edit Orderann]");
    
    int x=0;
    
    while(1){

        post(x,-2);
        putchar('^');
        int ch=getch();
        printf("\b \b");
        
        x += (ch==75) ? ((x==-21) ? 21 : (x==0) ? 19 : 0) :
             (ch==77) ? ((x==19) ? -19 : (x==0) ? -21 : 0) : 0;
        
        if(ch==13) break;
    
    }
    
    //if(x==21) edit_data();
    if(x==0) lobby();
    if(x==-21) shp_cart(FALSE);

}

void exits(){
    
	p (15,-11,"\033[1;21mTerima kasih sudah berkunjung %c\n\n\n\n\n\033[7m", 2);
    exit(0);

}

void credits(){ CLR; // Member group project
    
    fp = fopen("credits.txt", "r");
    
    if(fp==NULL){

        fp=fopen("credits.txt","w");
        
        fprintf(fp,
        "Project singkat yang bertemakan Aplikasi Restaurant ini ditujukan sebagai Tugas akhir Mata Kuliah Algoritma dan Pemograman\n\n\n"
        "Kami dari kelompok X yang beranggotakan\n\n"
        "# Christopher Seriwijaya   - 2602124644\n"
        "# Edbert Purwanto          - 2602063043\n"
        "# Efren Christofer         - 2602080320\n"
        "# Mhd. Fauzan Devinto      - 2602225201\n"
        "# Wan Mohamad Axel Rinaldi - 2602208750\n\n\n"
        " Kami ingin mengucapkan Terima kasih. ");
        
        fclose(fp);
    
    }

    fclose(fp);
    

    fp = fopen("credits.txt", "r");
    
    char credit[100];
    int stop=1, x=62, y=6;

    while(fgets(credit, 100, fp) != NULL){

        if(strstr(credit, "#") != NULL)
            stop = 0;
        
        if(strstr(credit, "kasih") != NULL)
            stop = 1;
        
        for(int i=0 ;i<strlen(credit); i++){
            
            if(credit[i] == '\n'){
                 y--;
                 if(y<=4) x=19;
            }
            
            else if(stop==1){
                p (x,y,"%c", credit[i]);
                fflush(stdout);
                usleep(45000); 
                x--;
            } 
            
            else if(stop==0){
                p (x,y,"%c", credit[i]);
                fflush(stdout); 
                x--;
            }

        }

    }

    fclose(fp);
    getch(); intro();
    
}


/* -------------------------------------------------------------------------- */


/*4 Functions dibawah ini digunakan untuk mengatur posisi cursor pada layar konsol, 
termasuk menyembunyikan/menampilkan cursor dan menempatkan cursor pada posisi tertentu di layar.*/
void hide(bool hides){

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 100;
    cursor.bVisible = hides;
    SetConsoleCursorInfo(consoleHandle, &cursor);

}

void gotoxy(int x, int y){
    
    COORD koordinat = {0, 0};
    koordinat.X=x; koordinat.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), koordinat);

}

void post(int x, int y){

	int kolom, baris;
    CONSOLE_SCREEN_BUFFER_INFO posisi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &posisi);
    kolom=posisi.srWindow.Right-posisi.srWindow.Left + 1;
    baris=posisi.srWindow.Bottom-posisi.srWindow.Top + 1;
	
    gotoxy(kolom/2-x,baris/2-y);

}

void p(int x, int y, const char* format, ...){

    int kolomp, barisp;
    char buffer[1024];

    CONSOLE_SCREEN_BUFFER_INFO posisi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &posisi);
    kolomp = posisi.srWindow.Right - posisi.srWindow.Left + 1;
    barisp = posisi.srWindow.Bottom - posisi.srWindow.Top + 1;
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    gotoxy(kolomp / 2 - x, barisp / 2 - y);
    printf("%s", buffer);

}
/* ------------------------------------------------------------------------- */


/* 4 Functions ini digunakan untuk mengontrol cursor dan membuat interaksi 
dengan user saat memilih menu yang ada dalam program. */
void cursor_control(int num_options, char options[][16], void (*fns[])(void), bool callob){
    
    int y = 1;
    
    while(1){
    
        post(-10, y);
        putchar('<');
        int ch = getch();
        printf("\b \b");

        y += (ch==72) ? (y==1) ? -6 : (y==-2) ? 3 : 3 : 
             (ch==80) ? (y==1) ? -3 : (y==-2) ? -3 : 6 : 0;
        
        if(ch==13) break;
        if(ch==27 &&callob) lobby();
    }

    int index = (y==1) ? 0 : (y==-2) ? 1 : 2;
    fns[index]();

}

void lobby_control(void (*fns[])(void)){
    int y = 2, x = 8, c = 0;

    while(1){
       
        char cursorz[4][2]={"<", ">", "v"};
        post(x, y);
        printf("%s",cursorz[c]);
        int ch = getch();
        printf("\b \b");
        
        (ch==72) ? ((x==8 && y==-2) ? (y+=4,  c=0) : (x==-8 && y==-2) ? (y+=4, c=1)  : (x==0 && y==-5) ? (x-=8, y+=3, c=1) : 0) :
        (ch==75) ? ((x==-8 && y==2) ? (x+=16, c=0) : (x==-8 && y==-2) ? (x+=16, c=0) : 0) :
        (ch==77) ? ((x==8 &&  y==2) ? (x-=16, c=1) : (x==8  && y==-2) ? (x-=16, c=1) : 0) :
        (ch==80) ? ((x==8 &&  y==2) ? (y-=4,  c=0) : (x==-8 && y== 2) ?    (y-=4)    : ((x==8 && y==-2) || (x==-8 && y==-2)) ? (x=0, y-=3, c=2) : 0) : 0;
        
        if(ch==13) break;
    
    }
    
    if(x==-8&&y==2) 
        shp_cart(TRUE);
    else{
        int index = (x==8&&y==2) ? 0 : (x==8&&y==-2) ? 1 : (x==-8&&y==-2) ? 2 : 3;
        fns[index]();
    }

}

void intro_control(void (*fns[])(void)){
    
    int y = -6, x = 0;
    
    while(1){

        post(x, y);
        putchar('^');
        int ch = getch();
        printf("\b \b");
        
        x = (ch==75 && y==-6) ? (x==0 ? x+19 : x==-18 ? x+18 : x) : x;
        x = (ch==77 && y==-6) ? (x==0 ? x-18 : x==19 ? x-19 : x) : x;
        y = (ch==72 && x==0 && y==-9) ? y+3 : y;
        y = (ch==80 && (x==0 || x==-18 || x==19) && y==-6) ? (x=0, y-3) : y;
        
        if(ch == 13) break;
    
    }
    
    int index = (x==19&&y==-6) ? 0 : (x==-18&&y==-6) ? 1 : (x==0&&y==-6) ? 2 : 3 ;
    fns[index]();

}

void food_control(int jmlh_menu, char nama_makanan[][16], int harga[], int callf){
    
    int i, y = 5;
    char jumlah[100], f_baris[128];
    
    while(1){
        
        post(-17, y);
        putchar('<');
        int ch = getch();
        printf("\b \b");
        
        y += (ch==72) ? (y>=-3 && y<5) ? 2 : -8 : 
             (ch==80) ? (y>-3 && y<=5) ? -2 : 8 : 0;
        i = (y==5) ? 0 : (y==3) ? 1 : (y==1) ? 2 : (y==-1) ? 3 : (y==-3) ? 4 : i;
        
        if(ch==13){
            
            p ((strlen(nama_makanan[i])+40)/2, -7, "Berapa banyak \x1b[1;37m%s\x1b[0m yang ingin kamu beli? ", nama_makanan[i]);
            scanf("%s", jumlah); getchar();

            for(int i=0; i<strlen(jumlah); i++){
                if(!isdigit(jumlah[i])){
                    p (7, -10, F"Invalid Input! "R);
                    getch(); 
                    callf == 1 ? chinese() : callf == 2 ? japanese() : callf == 3 ? western() : 0;
                }
            }

            update_food(order_user, nama_makanan[i], atoi(jumlah), harga[i]*atoi(jumlah), FALSE);
            p (8, -10, G"Order berhasil. "R); getch();
            
            callf==1 ? chinese() : callf==2 ? japanese() : callf==3 ? western() : 0;
        
        }
        else if(ch==27) menu();
    }
}
/* ------------------------------------------------------------------------ */


/* 5 Functions dibawah ini digunakan untuk mengecek informasi user saat proses login dan sign up, 
termasuk memvalidasi nomor telepon, email dan password user */

int check_hp(char *hp){ // Phone Number Check

	int valid=1;
	
    if(hp[0]=='0' && hp[1]=='8' && (strlen(hp)==11 || strlen(hp)==12)){ // di Indo no hp pasti depannya 0*
		for(int i=0 ;i<strlen(hp); i++)                                 // panjang no hp bisa 11 / 12
            if(!isdigit(hp[i])) valid = 0;
    }
	
    else valid = 0;
    return valid;

}

int check_mail(char *email){ // E-mail Check 

    int len = strlen(email), akeong = 0, username_len = 0, domain_len = 0, titik = 0, tld = 0;
    
    for(int i=0 ;i<len; i++){
        if(email[i] == '@'){
            akeong = 1;
            break;
        }
    }

    for(int i=0 ;i<len; i++){
        if(email[i] =='@') break;
        username_len++;
    }

    for(int i=len-1 ;i>=0; i--){
        if(email[i] == '@') break;
        domain_len++;
        if(email[i]=='.')
            titik=1;
        if(titik && isalpha(email[i])){
            tld = 1;
            break;
        }
    }

    if(len>100)
        return 0; 
    
    if(!akeong)
        return 0;
        
    if(username_len==0)
        return 0;
        
    if(domain_len<5 || !titik || !tld)  // Domain Lenght
        return 0;

    return 1;

}

int check_login(char *email, char* password) {

	int check=0;
	char line[200], curr_mail[100], curr_pass[100];
	
    fp=fopen("Data.txt", "r");

	while(fgets(line, 200, fp)!=NULL){
        sscanf(line,"%s %s", curr_mail, curr_pass);
        if(strcmp(email, curr_mail)==0&&strcmp(password,curr_pass)==0){ 
            check = 1;
            break; 
        }
    }

    fclose(fp);
    
    return check;

}

void signup(){ CLR; 
	
    while(1){ CLR;
        
        char nama[100], hp[13], email[100], password[100], validasi[100];

		p (6,11, H"Sign-Up"R);
		p (22,7, "Masukkan Nama");
        p (2, 7, ": "); 

		scanf("%[^\n]",nama); getchar(); 

        p (22,5, "Masukkan Nomor HP");
        p (2, 5, ": ");

		scanf("%[^\n]", hp); getchar();
		
        if(!check_hp(hp)){ // check sesuai kriteria 

			p (22, 2, F"Nomor HP yang kamu daftarkan tidak valid. "R);
			p (22,-2, S"Tekan ESC jika ingin kembali ke menu utama. "R);
			
            if(getch()==27) break; 
            
            continue;
		
        }

		p (22,3, "Daftarkan E-mail");
        p (2, 3, ": "); 
		scanf("%[^\n]", email); getchar();
		
        int check_email=0;

        if(!check_mail(email)){

            p (22 ,0, F"E-mail yang kamu daftarkan tidak valid !"R);
			p (22,-4, S"Tekan ESC jika ingin kembali ke menu utama. "R); 
            
            if(getch()==27) break; 
            
            continue;
        
        }

		fp=fopen("Data.txt", "r");

        char baris_f[200], check_maill[200];
        
        while (fgets(baris_f, 200, fp) != NULL){

            sscanf(baris_f,"%s", check_maill);
            
            if(!strcmp(email, check_maill)){
                check_email = 1;
                break;
            }

        }

		fclose(fp);

		if(check_email){
            
			Sleep(1000);
			p (22, 0, F"E-mail sudah digunakan, silahkan daftarkan e-mail yang lain. "R);
			p (22,-4, S"Tekan ESC jika ingin kembali ke menu utama. "R);
			
            if(getch()==27) break; 
            
            continue;

		}

		p (22,1, "Masukkan password");
        p (2,1 , ": "); 
		scanf("%[^\n]",password); getchar();
		
	    int len=0, lower=0, upper=0, number=0;
        
        for(int i=0 ;i<strlen(password); i++){

			if(islower(password[i])) lower=1;
			
            if(isupper(password[i])) upper=1;
			
            if(isdigit(password[i])) number=1;
		
        } 

		if(strlen(password)>7) len=1;
        // panjang harus lebih dari 8 
        // harus ada nomer 
        // harus ada uppercase
        // harus ada lowercase

		if(!len||!lower||!upper||!number){// keluarin pesan error 

            p (22,-2, F"Password tidak valid harap masukkan ulang."R);
            p (22,-4, "Password minimal harus terdiri atas :");
            p (22,-6, "1. Satu Huruf Besar.");
            p (22,-7, "2. Satu Huruf Kecil.");
            p (22,-8, "3. Satu Angka.");
            p (22,-9, "4. Memiliki panjang minimal 8 karakter.");
            p (22,-12, S"Tekan S jika ingin kembali ke menu utama. "R);
            
            if(getch()==27) break; 
            
            continue;
		
        }

		p (22,-1, "Konfirmasi password : ");
		scanf("%[^\n]",validasi); getchar();

		if(strcmp(password,validasi)){

			p (22,-4, F"Validasi gagal, password tidak sesuai. "R);
            p (22,-8, S"Tekan ESC jika ingin kembali ke menu utama. "R);
            
            if(getch()==27) break; 
            
            continue;

		}

		snprintf(data_user, sizeof(data_user), "data-%s.txt", email);
		snprintf(order_user, sizeof(order_user), "order-%s.txt", email);
		
        fp = fopen(data_user, "w");
		fprintf(fp,"Nama Customer : %s\nNo. HP   : %s\nE-mail   : %s\nPassword : %s\n\n",nama, hp, email, password);
		fclose(fp);
		
        fp = fopen(order_user, "w");
		fclose(fp);

		fp =fopen("Data.txt","a+");
		fprintf(fp,"%s %s\n",email ,password);
		fclose(fp);

		Sleep(1000);
		p (22,-4, G"Akun berhasil terdaftar. "R); getch(); 
        
        break;

	}

	intro();

}

void login(){ CLR;
	
    while(1){ CLR; 
        
        char login_password[100];
        char login_email[100];
        
        p (6,7, H"Log-In"R);
        p (22,3, W"Masukkan E-mail ");
        p (4, 3, ": "R);
		scanf("%s", login_email); getchar();
        p (22,0, W"Masukkan Password : "R);
		scanf("%[^\n]", login_password); getchar();
		
        if(!check_login(login_email, login_password)){

			Sleep(1000);
			p (22,-3, F"Invalid E-mail/ Password !"R);
			p (22,-7, S"Tekan ESC untuk kembali ke menu ke menu utama. "R);
			
            if(getch()==27) // asci 27 adalah esc
                break; continue;

		}

		Sleep(1500);
		snprintf(data_user, sizeof(data_user), "data-%s.txt", login_email);
		snprintf(order_user, sizeof(order_user), "order-%s.txt", login_email);
		p (22, -3, G"Login Berhasil. "R); getch();
		lobby();
	}
	intro();

}
/* ------------------------------------------------------------------------- */


/* 4 Functions dibawah ini berfungsi sebagai penyortiran dan peng-update-an file user selama program berlangsung */
int compare_lines(const void *a, const void *b){
    
    struct sort_f *line_a = (struct sort_f *)a;
    struct sort_f *line_b = (struct sort_f *)b;
    
    return line_a->s_harga - line_b->s_harga;

}

void sort_file(const char *file){
    
    fp = fopen(file, "r");
    
    int baris_f=0;

    rewind(fp);
    while(fscanf(fp, "%d %s %d", &linez[baris_f].s_jumlah, linez[baris_f].s_nama, &linez[baris_f].s_harga) == 3){

        baris_f++;
    
    }
    
    fclose(fp);


    qsort(linez, baris_f, sizeof(struct sort_f), compare_lines);
    

    fp = fopen(file, "w");

    for (int i=0 ;i<baris_f; i++) {

        fprintf(fp, "%d %-16s %d\n", linez[i].s_jumlah, linez[i].s_nama, linez[i].s_harga);
    
    }

    fclose(fp);

}

void update_food(const char *file, const char *inp_nama, int inp_jumlah, int inp_harga, bool edit){
    
    fp = fopen(file, "r+");
    
    bool dah_ada = false;
    int f_jumlah, f_harga;
    char f_nama[16];
    
    rewind(fp);
    while(fscanf(fp, "%d %s %d\n", &f_jumlah, f_nama, &f_harga)==3){

        if(strcmp(f_nama, inp_nama) == 0){
            
            if(edit==TRUE){
                f_jumlah = inp_jumlah;
                f_harga = inp_harga;
            }

            else{
                f_jumlah += inp_jumlah;
                f_harga += inp_harga;
            }

            dah_ada = true;
            break;
        }

    }

    char temp_file[]="temp.txt";
    char line[128];

    ft = fopen(temp_file, "w");
    
    rewind(fp);
    while(fgets(line, sizeof(line), fp) != NULL){

        if(strstr(line, inp_nama) == NULL)
            fputs(line, ft);
    
    }

    if(dah_ada)
        fprintf(ft, "%d %-16s %d\n", f_jumlah, inp_nama, f_harga);
    
    else
        fprintf(ft, "%d %-16s %d\n", inp_jumlah, inp_nama, inp_harga);
    
    _fcloseall();
    remove(file);
    rename(temp_file, file);
    sort_file(file);
}

void edit(char nama_edt[][100], int biaya_edt[100], int jumlah_edt[100], int top, int bot, int baris_ord){
    
    int idx=0, yy=top;
    char str[100], spasi[1000];
    
    memset(spasi, ' ', 53);
    
    p (20,bot-3,"Arahkan cursor ke menu yang ingin diedit");
    p (16,bot-7,S"Tekan ESC untuk kembali ke lobby"R);
    
    while(1){

        if(baris_ord>1){

            post(-18,yy);
            putchar('<');
            int ch = getch();
            printf("\b \b");
        
            yy = (ch==72) ? (yy>=bot&&yy<top) ? yy+1 : bot : 
                 (ch==80) ? (yy>bot&&yy<=top) ? yy-1 : top : yy;

            idx = (ch==72) ? (idx>=0&&idx<=baris_ord-1) ? idx-1 : baris_ord : 
                  (ch==80) ? (idx>=0&&idx<baris_ord-1) ? idx+1 : 0 : idx;
            
            if(ch==13) break;
            if(ch==27) lobby();
        
        }

        else{

            post(-18,yy);
            putchar('<');
            int ch = getch();
            if(ch==13) break;
            if(ch==27) lobby();
        
        }

    }

    post(20,bot-3); SPASI;
    p((strlen(nama_edt[idx])+26)/2,bot-3,"Masukkan jumlah %s yang baru", nama_edt[idx]);
    post(16,bot-7); SPASI;
    p (14,bot-7,S" Tekan ESC untuk membatalkan"R);
    post(16,yy);
    printf("   ");
    post(16,yy);
    
    char input[3];
    int i = 0, promptLength = 15, cursorPosition = promptLength; 
    while(1){
        
        char ch = _getch();
        if(ch == '\r')
            break;
        
        if (ch==27) 
            shp_cart(FALSE);
        
        if(ch=='\b'){
            if(i>0){
                i--;
                if(cursorPosition > promptLength){

                    printf("\b \b");
                    cursorPosition--;
                
                }
                continue;
            }
        }
        
        if(i<2){

            putchar(ch);
            input[i] = ch;
            i++;
            cursorPosition++;
        
        }
    
    }
    input[2] = '\0';
    
    if(strlen(input)==0){

        post(20,bot-3); SPASI;
        p (7, bot-3, F"Invalid Input! "R);
        getch(); shp_cart(FALSE);
    
    }

    for(int i=0; i<strlen(input); i++){
        
        if(!isdigit(input[i]) || input[0]=='0'){
            post(20,bot-3); SPASI;
            p (7, bot-3, F"Invalid Input! "R);
            getch(); shp_cart(FALSE);
        }

    }

    update_food(order_user, nama_edt[idx], atoi(input), (biaya_edt[idx]/jumlah_edt[idx])*atoi(input), TRUE);
    post(20,bot-3); SPASI;
    p(15,bot-3, G"Orderan kamu berhasil di update"R); getch(); shp_cart(FALSE);

}
/* ------------------------------------------------------------------------ */


/* 3 Functions dibwayah ini digunakan ketika user ingin melakukan pembayaran atau ketika user ingin melihat list orderan*/
void pembayaran(){ CLR;

    int chr;
    char c, str[30], baris_f[1024], cust[20], nama[20];

	srand(time(NULL));
    
    fp=fopen(data_user, "r");

    char hp[20];
    char nama_user[50];

    while(fgets(baris_f, sizeof(baris_f), fp)!=NULL){

        sscanf(baris_f, "Nama Customer : %s", nama_user);
    
    }

    fclose(fp);

    fp = fopen(order_user, "r");
    fseek(fp, 0, SEEK_END);

    if(ftell(fp)==0){

        post(15,0);
        puts("List Orderan kamu masih kosong. ");
        getch(); lobby();
    
    }

    int baris=0, top=1;

    rewind(fp);
    while((chr=fgetc(fp))!=EOF){

        if(chr=='\n'){
            baris++; if(baris%2==0) top++;
        }

    }
    int top_rcp=top;
    for(int y=((baris+25)/2) ;y>=((baris+26)/2)*-1; y--){

        for(int x=24 ;x>=-24; x--){
            printf(O);
            post(x, y);
            printf(" ");
        }
        
        printf("\n");
    
    }

    int jumlah, biaya;
    int subtotal=0;
    
    rewind(fp);
    while(fgets(baris_f, 200 ,fp)!=NULL){
		
        int n = (sscanf(baris_f,"%d %s %d", &jumlah, nama, &biaya));
        
        if(n==3){
            subtotal+=biaya;
            top-=1;
            p (24, top, "  - %d %s", jumlah, nama);
            p (strlen(format_duit(biaya,str))-20, top, "Rp%s", format_duit(biaya,str));
        }

	}

    int bot=top;
    
    fclose(fp); 


    char strip[1000];
    memset(strip, '-', 46);

    char spasi[1000];
    memset(spasi, ' ', 53);

    p (12, top_rcp+10 , "\xcd\xcd\xcd Sunib Restaurant \xcd\xcd\xcd");
    p (7 , top_rcp+8 , "(123) 456-7890");
    p (23, top_rcp+7  , "Paskal Hyper Square, Jl. Pasir Kaliki No.25-27");
    p (22, top_rcp+5  , "Customer  : %s", nama_user);
    p (22, top_rcp+3  , "No. Order : #%d", rand()%100000);
    p (23, top_rcp+1, " %s", strip);
    p (22, bot-2  , "Sub-Total : ");
    p (22, bot-3  , "Pajak :");
    p (22, bot-7  , "Total : ");
    

    int pajak = subtotal*0.05;
    int total = subtotal+pajak;

    p (strlen(format_duit((double)subtotal,str))-20, bot-2, "Rp%s  ", format_duit((double)subtotal, str));
    p (strlen(format_duit((double)pajak,str))-20, bot-3, "Rp%s  ", format_duit((double)pajak, str));
    p (strlen(format_duit((double)total,str))-20, bot-7,"Rp%s   ", format_duit((double)total, str));
    
    waktu(top_rcp+5,top_rcp+6);
    
    p (23, bot-5, "%s", strip);
    p (23, bot-9, "%s", strip);
    

    gotoxy(3,4);
    printf("\x1b[0mKonfirmasi pembayaran \x1b[1;97m[tidak bisa dicancel]\x1b[0m !");
    gotoxy(12,7);
    puts("Lanjutkan");
    gotoxy(32,7);
    puts("Batal");

    int x = 34;
    
    while(1){
        
        gotoxy(x,8);
        putchar('^');
        int ch = getch();
        printf("\b \b");
        x += (ch==75 && x>16 && x<=34) ? -18 : (ch==77 && x>=-16 && x<34) ? 18 : 0;
        if(ch==13) break;
    
    }
    if(x==34) lobby();

    
    hide(!hides);
    
    for(int i=3 ;i<48; i++){

        for(int j=4; j<8; j++){
            gotoxy(i,j);
            printf(" ");
        }
        
        puts("");

    }

    gotoxy(3,4);
    puts("Silahkan isi data berikut !");
    

    int d=0;
    
    char alamat[20];
    char metod[2][10]={"Delivery", "Take-Out"};
    
    while(1){

        gotoxy(3,6);
        puts("Delivery Methods : ");
        gotoxy(22,6);
        printf("%s", metod[d]);
        
        int ch = getch();
        
        if(ch==72 || ch==75 || ch==77 || ch==80){
            d = (d==0) ? d+1 : d-1;
        }
        
        if(ch==13) break;
    
    }

    (d==0) ? p (22,bot-10, O"Delivery Method : %s"R, metod[0]) : p (22,bot-10, O"Delivery Method : %s"R, metod[1]);


    int yx=6;
    int ongkir[5]={10000, 12000, 15000, 18000, 20000}, ongk=rand()%5;
    
    if(d==0){
        
        gotoxy(3,yx+=2);
        printf("Silahkan masukkan Alamat pengantaran : ");
        gotoxy(3,yx+=2);
        scanf("%[^\n]", alamat); getchar();
        
        p (22,bot-4,O"Ongkir: ");
        p (-14,bot-4,"Rp%s", format_duit(ongkir[ongk],str));
        p (22, bot-7,"Total : ");
        p (strlen(format_duit((total+ongkir[ongk]),str))-20,bot-7,"Rp%s "R, format_duit((total+ongkir[ongk]), str));
        
        total+=ongkir[ongk];        
    
    }
    
    gotoxy(3,yx+=2);
    puts("Metode Pembayaran : ");
    
    int i=0;
    char metode[2][10]={"Cash", "E-Wallet"};
    while(1){

        gotoxy(23, yx);
        printf("%s", metode[i]);
        
        int ch = getch();
        
        if(ch==72 || ch==75 || ch==77 || ch==80){
            i += (i==0) ? 1 : -1;
            gotoxy(23,yx);
            printf("        ");
        }
        
        if(ch==13) break;
    }

    (i==0) ? p (22,bot-11, O"Metode Pembayaran : %s"R, metode[0]) : p (22,bot-11, O"Metode Pembayaran : %s"R, metode[1]);
    
    gotoxy(3,yx+=2);
    printf("Total tagihan  : Rp%s",format_duit(total,str)); yx+=2;
    
    if(i==1){
        
        char total_str[100];
        int byr, total_len = snprintf(total_str, sizeof total_str, "%d", total + ongkir[ongk]);
        
        while (1) {
            
            gotoxy(3,yx);
            printf("Silahkan bayar : Rp");
            gotoxy(22,yx);
            
            if(scanf("%d", &byr) != 1){

                while (getchar() != '\n');
                gotoxy(3,yx); SPASI;
                gotoxy(3,yx);
                printf(F"Invalid input!"R);
                getch();
                gotoxy(3,yx); SPASI;
                continue;
            
            }

            if(byr<total){

                gotoxy(3,yx); SPASI;
                gotoxy(3,yx);
                printf(F"Input masih kurang!"R);
                getch();
                gotoxy(3,yx); SPASI;
                continue;

            }
            
            gotoxy(22,yx);
            printf("%s", format_duit(byr,str));
            gotoxy(3,yx+=2);
            printf(G"Pembayaran Berhasil!"R);
            break;
        
        }
    
    }
    
    if(d==0){

        int x=0,dr=rand()%5;
        char driver[5][7]={"Axel","Cio","Devin","Edbert","Efren"};
        
        while(x!=2){

            gotoxy(3,yx+2);
            printf("Sedang mencari driver");
            
            for(int i=0 ;i<3; i++){
                Sleep(1000);
                printf(".");
            }

            Sleep(1000);
            gotoxy(24,yx+2); puts("   ");
            x++;
        }

        gotoxy(3,yx+2);
        puts(G"Driver berhasil ditemukan!"R); Sleep(1500);
        gotoxy(3,yx+2); SPASI;
        gotoxy(3,yx+2);
        printf("Nama driver : %s",driver[dr]);
        p (22,bot-12, "\x1b[30;107mDriver : %s"R, driver[dr]);
        gotoxy(3,yx+4);
        printf("%s akan mengantarkan makananmu dalam %d menit.", driver[dr], rand()%(11)+15);
        
    }

    gotoxy(3,yx+=4);
    puts("Terima Kasih sudah berbelanja di Sunib Restaurant");
    gotoxy(24,yx+2);
    printf(" %c  %c  %c ", 2, 2, 2); 
    fp=fopen(order_user,"w");
    fclose(fp);
    gotoxy(0,0);
    getch();hide(hides);lobby();

}

void list_ord(int y){
    
    p ( 20, y, "[Bayar]");
    p (  3, y, "[Lobby]");
    p (-14, y, "[Edits]"); 
    
    int x=0;
    
    while(1){

        post(x,y-1);
        putchar('^');
        int ch = getch();
        printf("\b \b");
        x += (ch==75 && x>=-17 && x<17) ? 17 : (ch==77 && x>-17 && x<=17) ? -17 : 0;
        if(ch==13) break;

    }

    if(x==0) lobby();
    if(x==17) pembayaran();
    if(x==-17) shp_cart(FALSE);
    
}

void shp_cart(bool lizt){ CLR;
    
    fp=fopen(order_user, "r");
    fseek(fp, 0, SEEK_END);
    
    if(ftell(fp)==0){

        post(15,0);
        puts("List Orderan kamu masih kosong. ");
        getch(); lobby();
    
    }

    int chr, baris_ord=0, yl=1;
    
    rewind(fp);
    while((chr=fgetc(fp))!=EOF){

        if(chr=='\n'){
            baris_ord++;
            if(baris_ord%2==0) yl++;
        }
    
    }

    int top=yl;
    
    p (6 , yl+3,  "List Orderan");


    char str[30], baris_f[1024];
    char nama[26];
    char nama_edt[1][100]; 

    int index = 0; 
    int biaya, jumlah;
    int biaya_edt[100], jumlah_edt[100]; 
    
    rewind(fp);
    while(fgets(baris_f, 200 ,fp)!=NULL){

        int count = (sscanf(baris_f,"%d %s %d\n", &jumlah, nama, &biaya));
        
        if (count == 3){
            strcpy(nama_edt[index], nama);
            biaya_edt[index] = biaya;
            jumlah_edt[index] = jumlah;
            index++;
            p (16, yl--, "\x1b[1m%d  %s", jumlah, nama);
            p (strlen(format_duit(biaya, str))-14, yl+1, "Rp%s", format_duit(biaya, str));
        }

    }
    int bot=yl;

    fclose(fp);
    
    if(lizt==TRUE) list_ord(yl-=3);
    
    if(lizt==FALSE) edit(nama_edt, biaya_edt, jumlah_edt, top, bot+1, baris_ord);

}
/* ------------------------------------------------------------------------ */

int main(){
    
    hide(hides);
    intro();

}
