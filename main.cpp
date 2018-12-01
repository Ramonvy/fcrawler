#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <Wininet.h>


struct string {
  char *ptr;
  size_t len;
};

FILE *mainsite;
struct string s;
char code[10000000];
char cback[10000];
CURL *curl;
CURLcode res;
int code_size = 0;



size_t myfunc(void *ptr, size_t size, size_t nmemb, char *c){
	size_t x = size*nmemb;
	//printf((char *)ptr);
	//strcpy(c, (char *)ptr);
	sprintf(c, "%s%s", c, (char*)ptr);
	//memcpy(c + code_size, ptr, size);
	code_size += x;
  	return  x;
}





int getscripthttps(char *url){
	//printf("\n\nTentando se conectar a %s\n\n", url);
	//system("pause");
	code_size = 0;
  	curl = curl_easy_init();
  	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, myfunc);
   	curl_easy_setopt(curl, CURLOPT_WRITEDATA, code);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(curl, CURLOPT_HEADER, false);
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
	curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.2; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1667.0 Safari/537.36");
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
  	curl_easy_setopt(curl, CURLOPT_POST, false);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
	curl_easy_setopt(curl, CURLOPT_COOKIESESSION, true);
	//curl_easy_setopt(curl, CURLOPT_REFERER, "https://www.facebook.com/login.php");
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1500);
	//curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
	
	code[0] = 0;
	curl_easy_setopt(curl, CURLOPT_URL, url);
	res = curl_easy_perform(curl);
	
	struct curl_slist *cookies = NULL;
	curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
	
	struct curl_slist *each = cookies;
      while(each) {
        printf("%s", each->data);
        each = each->next;
      }
	
	
	curl_easy_cleanup(curl);
    //strcpy(code, s.ptr);
    return strlen(code);
}





static size_t read_callback(void *ptr, size_t size, size_t nmemb, char *c)
{
  size_t x = size*nmemb;
	//strcpy(c, (char *)ptr);
	sprintf(c, "%s%s", c, (char*)ptr);
  	return  x;
}


int facelog(char *login, char *senha){
	
    
	printf("\n\nfacelog iniciado.\n\n");
	
	char logpass[3000];
	sprintf(logpass, "email=%s&pass=%s", login, senha);

	
	printf(logpass);
  	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, myfunc);
   	curl_easy_setopt(curl, CURLOPT_WRITEDATA, code);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(curl, CURLOPT_HEADER, false);
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
	curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.2; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1667.0 Safari/537.36");
    curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
	curl_easy_setopt(curl, CURLOPT_COOKIESESSION, true);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1500);	
	
	
	code[0] = 0;
	printf("\n\nCarregando facebook.com \n\n");
	curl_easy_setopt(curl, CURLOPT_URL, "https://www.facebook.com/");
	res = curl_easy_perform(curl);
	printf("\n\nfacebook carregado\n\n");
	//system("pause");
	
	/*FILE *f = fopen("test.html", "w");
	fprintf(f, code);
	fclose(f);*/
	//system("pause");
	
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, logpass);
	//curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback); 
    //curl_easy_setopt(curl, CURLOPT_READDATA, cback);
    curl_easy_setopt(curl, CURLOPT_REFERER, "http://www.facebook.com/");
	curl_easy_setopt(curl, CURLOPT_POST, true);
	
	
	
	
	code[0] = 0;
	curl_easy_setopt(curl, CURLOPT_URL, "https://www.facebook.com/login.php");
	printf("1\n");
	//system("pause");
	res = curl_easy_perform(curl);
	//system("pause");
	printf("\n\nRequisicao finalizada\n");
	
	//system("pause");
	
	printf("code leng >> %d\n\n", strlen(code));
	/*f = fopen("test.html", "w");
	fputs(code, f);
	fclose(f);*/
	
	printf("POST feito\n");
	//system("pause");
	
	struct curl_slist *cookies = NULL;
	curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
	
	struct curl_slist *each = cookies;
      while(each) {
        printf("%s", each->data);
        each = each->next;
      }
	
	
	curl_easy_cleanup(curl);
	
	
	
	
	/*FILE *f = fopen("fb.html", "w");
	fprintf(f, code);
	fclose(f);*/
	
	printf("\n\nfacelog finalizado\n\n");
}




int vrfpoint(char *word, int point, FILE *f){
	int x = 0;
	fseek(f, point, SEEK_SET);
	char c;
	while(word[x] != 0){
		c = getc(f);
		if(c != word[x]){
			return 1;
		}
		++x;
	}
	return 0;
}


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
char lbase[3000];
int getbaselnk(){
	//printf("1");
	char classe[100];
	strcpy(classe, "class=\"_2s25 _606w\"");
	
	int x = 0;
	
	
	//int codesize = strlen(code);
	while(x < code_size && vrfpoint(classe, x, mainsite) != 0){
		++x;
	}
	
	if(x < code_size){
		//printf("Ponto rastreado\n");
		//x += strlen(classe);
		/*while(code[x] != '='){
			++x;
		}
		while(code[x] != '\"'){
			++x;
		}*/
		while(code[x] != '\"'){
			--x;
		}
		++x;
		while(code[x] != 'k'){
			++x;
		}
		while(code[x] != '/'){
			++x;
		}
		int y = 0;
		while(code[x] != '\"'){
			lbase[y] = code[x];
			++y;
			++x;
		}
		lbase[y] = 0;
	}
	else{
		printf("code_size >> %d\n", code_size);
		printf("Ponto nao rastreado :(\n");
	}
}


char nextpagef[3000];	
int getnextpagef(int lvl){
	char link_out[3000];
	char classe[100];
	if(lvl == 1){
		strcpy(classe, "id=\"u_0_0");
	}
	else{
		strcpy(classe, "m_more_friends");
	}
	
	
	int x = 0;
	//int codesize = strlen(code);
	mainsite = fopen("site.html", "r");
	fseek(mainsite, 0, SEEK_END);
	int codesize = ftell(mainsite);
	fseek(mainsite, 0, SEEK_SET);
	
	while(x < codesize && vrfpoint(classe, x, mainsite) != 0){		//loop buscando a string de "classe" dentro de site.html
		++x;
		//printf("%d/%d\n", x, codesize);
	}
	strcpy(classe, "href=\"");
	while(x < codesize && vrfpoint(classe, x, mainsite) != 0){
		++x;
		//printf("%d/%d\n", x, codesize);
	}
	
	
	
	if(x < codesize){
		x = ftell(mainsite) - 5;
		
		//printf("Ponto rastreado\n");
		//x += strlen(classe);
		int y = 0;
		while(code[x] != '\"'){
			--x;
		}
		++x;
		while(code[x] != '\"'){
			if(code[x] != '\n'){
				link_out[y] = code[x];
				++y;
			}
			++x;
		}
		link_out[y] = 0;
		
		sprintf(nextpagef, "https://mbasic.facebook.com%s", link_out);
		printf("%s\n", nextpagef);
		//system("pause");
		fclose(mainsite);
		return 0;
	}
	else{
		printf("Ponto nao rastreado\n");
		fclose(mainsite);
		//system("pause");
		return 1;
	}
}



int searchonlines(char *str, char *road){
	FILE *f = fopen(road, "r");
	char str2[3000];
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	
	int pos = 0;
	
	int x;
	char c = 0;
	while(pos < size){
		x = 0;
		str2[0] = 0;
		
		while(c != '\n'){
			if(c != 0){
				str2[x] = c;
				++x;
			}
			c = fgetc(f);
			++pos;
		}
		c = fgetc(f);
		str2[x] = 0;
		if(strcmp(str, str2) == 0){
			return 1;
		}
		
	}
	
	return 0;
	
}


int qb(char *str){
	int x = 0;
	int y = 0;
	while(str[x] != 0){
		if(str[x] == '/'){
			++y;
		}
		++x;
	}
	return y;
}


int fgetsmv(char *str, FILE *f){
	int x = 0;
	char c = getc(f);
	while(c != '\n'){
		str[x] = c;
		c = getc(f);
		++x;
	}
	str[x] = 0;
	
}

int norep(char *str, FILE *f){
	fseek(f, 0, SEEK_END);
	int fs = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	int z = 0;
	
	char res[3000];
	while(ftell(f) < fs){
		fgetsmv(res, f);
		if(strcmp(res, str) == 0){
			++z;
		}
	}
	
	
	return z;
	
}



int loadfriendsinfile(int lvl){
	printf("p1\n");
	
	
	char fname[20];
	sprintf(fname, "fl%d.txt", lvl);
	FILE *f = fopen(fname, "r");
	if(f == NULL){
		f = fopen(fname, "w");
		fclose(f);
	}
	
	
	
	char link[3000];
	
	printf("p2\n");
	
	mainsite = fopen("site.html", "r");
	
	fseek(mainsite, 0, SEEK_END);
	unsigned long int codesize = ftell(mainsite);
	fseek(mainsite, 0, SEEK_SET);
	fclose(mainsite);
		
	unsigned long int x;
	
		
	
		
	//printf("\n\nx >> %d\ncodeside >> %d\nv >> %d\n", x, codesize, v);
		
	//while(x < codesize){
		//system("pause");
		
		mainsite = fopen("site.html", "r");
		//printf("x >> %d\n", x);
		
			
		x = 0;
		
		
		if(lvl == 1){
			while(x < codesize && vrfpoint("<body", x, mainsite) != 0){
				++x;
				//printf("x >> %d || codesize >> %d\n", x, codesize);
				//printf("%d/%d\n", x, codesize);
			}
			
			
			int divx = 0;
			
			while(divx < 7){
				while(x < codesize && vrfpoint("<div", x, mainsite) != 0){
					++x;
					//printf("x >> %d || codesize >> %d\n", x, codesize);
					//printf("%d/%d\n", x, codesize);
				}
				++divx;
			}
			while(x < codesize && vrfpoint("/table>", x, mainsite) != 0){
				++x;
				//printf("x >> %d || codesize >> %d\n", x, codesize);
				//printf("%d/%d\n", x, codesize);
			}	
		}
		else{
			int tablex = 0;
			printf("codesize >> %d\n", codesize);
			if(codesize == -1){
				return 1;
			}
			
			while(tablex < 4){
				while(x < codesize && vrfpoint("<table", x, mainsite) != 0){
					++x;
					//printf("x >> %d || codesize >> %d\n", x, codesize);
					//printf("%d/%d\n", x, codesize);
					
					
				}
				++x;
				++tablex;
				printf("tablex >> %d / 4\n", tablex);
			}
		}
		
		
		
		printf("p22\n");
		
		char user[3000];
		int y;
		char id[100];
		strcpy(id, "1");
		while(x < codesize && atoi(id) != 0){
			++x;
			while(x < codesize && vrfpoint("<table", x, mainsite) != 0 && vrfpoint("m_more_friends", x, mainsite) != 0){
				++x;
			}
			while(x < codesize && vrfpoint("href=\"", x, mainsite) != 0 && vrfpoint("m_more_friends", x, mainsite) != 0){
				++x;
			}
			
			x += strlen("href=\"");
			
			printf("p23\n");
			
			y = 0;
			char c = getc(mainsite);
			while(c != '\"' && ftell(mainsite) < codesize){
				user[y] = c;
				c = getc(mainsite);
				++y;
			}
			user[y] = 0;
			printf("user >>> %s\n", user);
			int fp = strlen(user);
			
			printf("p231\n");
			
			int y2;
			char user2[3000];
			strcpy(user2, user);
			user2[strlen("/profile.php")] = 0;
			
			if(lvl == 1 || strcmp(user2, "/profile.php") == 0){
				y = 0;
				while(user[y] != '='){
					++y;
				}
				++y;
				y2 = 0;
				while(user[y] != '&'){
					id[y2] = user[y];
					++y2;
					++y;
				}
				id[y2] = 0;
				sprintf(user, "/profile.php?v=friends&id=%s", id);
			}
			else{
				y = 0;
				while(user[y] != '?'){
					++y;
				}
				user[y] = 0;
				sprintf(user, "%s/friends", user);
				printf("p25\n");
			}
			
			int rep = 0;
			int lvlx = 1;
			char nrc[1000];
					
			if(user[y - 1] == '/'){
				++rep;	
			}
					
			if(lvl == 1){
				f = fopen("fl1.txt", "r");
				if(f == NULL){
					f = fopen("fl1.txt", "w");
					fprintf(f, "%s\n", user);
					fclose(f);
				}
				else{
					rep += norep(user, f);
					fclose(f);
				}
			}
			else{
				while(lvlx <= lvl && rep == 0){
					sprintf(nrc, "fl%d.txt", lvlx);
					f = fopen(nrc, "r");
					rep += norep(user, f);
					fclose(f);
					++lvlx;
				}
			}
			
			printf("k1\n");
			
						
			if(rep == 0 && atoi(id) != 0 && fp > 0){
				
				char flname[100];
				sprintf(flname, "fl%d.txt", lvl);
				f = fopen(flname, "a");
				fprintf(f, "%s\n", user);
				fclose(f);
				printf("%s\n\n", user);
			}
			
			++x;	
			
			if(fp == 0){
				x = codesize;
			}
			
		}
		
		
		
		
	//}
 	
		
	printf("p6\n");
	return 0;
}




int loadfriendlist(int level){
	int lvl = 1;
	int rtn;
	
	FILE *db;
	
	
	while(lvl <= level){
		printf("Linha 624\n");
		if(lvl == 1){
			printf("Linha 626\n");
			system("title nivel 1");
			//char llnk[3000];
			//strcpy(llnk, "https://www.facebook.com/home.php");
			//getscripthttps(llnk);
			//printf("\n\nPagina inicial carregada\n\nAnalizando codigo html\n\n");
			
			
			/*
			FILE *f = fopen("face.html", "w");
			//fputs(code, f);
			fwrite(code, code_size, 1, f);
			fclose(f);
			
			//system("pause");
			
			mainsite = fopen("face.html", "r");
			//getbaselnk();
			//printf("%s\n", lbase);
			//printf("Codigo html analizado\n\n");*/
			char mlink[3000];
			strcpy(mlink, "https://mbasic.facebook.com/friends/center/friends");
			printf("link face mine >> %s\n\nCarregando pagina de amigos\n\n", mlink);
			//system("pause");
			getscripthttps(mlink);
			
			printf("strlen(code) >> %d\n", strlen(code));
			//system("pause");
			
			
			mainsite = fopen("site.html", "w");
			fputs(code, mainsite);
			fclose(mainsite);
			
			
			printf("fl loaded\n");
			//system("pause");
			
			//printf("Pagina inicial de amigos carregada\n\n");
			loadfriendsinfile(lvl);
			printf("Html de pagina verificado\n\n");
			
			printf("gnx1\n");
			
			while(getnextpagef(1) == 0){
				printf("Linha 671\n");
				
				printf("gnx2\n");
				
				printf("Carregando nextpagef\n\n");
				printf("%s\n\n", nextpagef);
				//system("pause");
				getscripthttps(nextpagef);
				
				FILE *f = fopen("site.html", "w");
				fputs(code, f);
				fclose(f);
				printf("Carregado em arquivo");
				//system("pause");
				
				printf("Verificando html\n\n");
				loadfriendsinfile(lvl);
				nextpagef[0] = 0;
			}
		}
		else{
			printf("Linha 692\n");
			system("title nivel 2");
			char nome[3000];
			sprintf(nome, "fl%d.txt", lvl - 1);
			char mlink[3000];
			
			
			db = fopen(nome, "r");
			fseek(db, 0, SEEK_END);
			int dbs = ftell(db);
			fseek(db, 0, SEEK_SET);
			
			int dbpoison;
			rtn = 0;
			
			while(ftell(db) < dbs && rtn == 0){
				printf("Linha 708\n");
				fgetsmv(lbase, db);
				printf("lbase >> %s\n", lbase);
				//system("pause");
				
				
				sprintf(mlink, "https://mbasic.facebook.com%s", lbase);
				printf("link face mine >> %s\n\nCarregando pagina de amigos\n\n", mlink);
				//system("pause");
				getscripthttps(mlink);
				
				printf("strlen(code) >> %d\n", strlen(code));
				//system("pause");
				
				
				FILE *f = fopen("site.html", "w");
				fputs(code, f);
				fclose(f);
				
				
				//printf("Pagina inicial de amigos carregada\n\n");
				dbpoison = ftell(db);
				fclose(db);
				
				rtn = loadfriendsinfile(lvl);
				db = fopen(nome, "r");
				fseek(db, dbpoison, SEEK_SET);
				//printf("Html de pagina verificado\n\n");
				
				while(getnextpagef(lvl) == 0 && rtn == 0){
					printf("Linha 738\n");
					printf("nextpagef >>>>>  %s\n", nextpagef);
					printf("Carregando nextpagef\n\n");
					//printf("%s\n\n", nextpagef);
					//system("pause");
					getscripthttps(nextpagef);
					
					f = fopen("site.html", "w");
					fputs(code, f);
					fclose(f);
					//printf("Carregado em arquivo");
					///system("pause");
					
					//printf("Verificando html\n\n");
					rtn = loadfriendsinfile(lvl);
					nextpagef[0] = 0;
				}
				
				printf("Linha 756\n");
					
			}
			
			printf("Linha 760\n");
			
		}
		
		rtn = 0;
		++lvl;
		printf("Linha 766\n");
		
	}
	
}


int main(int argc, char** argv) {
	
	if(fopen("in.txt", "r") == 0){
		remove("cookies.txt");
		FILE *ini = fopen("cookies.txt", "w");
		fclose(ini);
		
		printf("Email:");
		char email[3000];
		char senha[3000];
		gets(email);
		printf("Senha:");
		gets(senha);
		
		
		facelog(email, senha);
		ini = fopen("in.txt", "w");
		fclose(ini);
		//system("start crawler.exe");
		//exit(0);
	}
	
	
	curl_global_init(CURL_GLOBAL_DEFAULT);
	

	
	
	loadfriendlist(5);
	
	//system("pause");
	return 0;
}
