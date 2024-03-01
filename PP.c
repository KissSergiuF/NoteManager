#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
typedef struct notes {
    char data[21];
    char ora[11];
    char continut[1001];
} notes;

void sageata(int pozitiedorita,int pozitieactuala) {
    if(pozitiedorita==pozitieactuala)
        printf(">> ");
    else printf("   ");
}

void loopsageata(int *pozsageata,int min,int max) {
    if(*pozsageata>max) *pozsageata=min;
    if(*pozsageata<min) *pozsageata=max;
}

void optiuni(int *pozsageata,int *inainte,int *iesire,int *inapoi,int meniuprincipal) {
    int alegere=getch();
    if(alegere==72)
        (*pozsageata)--;
    if(alegere==80)
        (*pozsageata)++;
    if(alegere==77)
        *inainte=1;
    if(alegere==27 && meniuprincipal==1)
        *iesire=1;
    if(alegere==75)
        *inapoi=1;
}
void remove_newline(char *s) {
    int len=strlen(s);
    if (len>0 && s[len-1]=='\n')
        s[len-1]='\0';
}
void citeste_notite_din_fisier_in_memorie(notes notite[],int *nrNotite) {
    FILE *fp=fopen("notite.txt","r");
    char linii[100][100];
    int nrLinii=0;
    char linie[100];
    while(fgets(linie,100,fp)!=NULL) {
        strcpy(linii[nrLinii],linie);
        nrLinii++;
    }
    fclose(fp);
    *nrNotite=0;
    for(int i=0;i<nrLinii-2;i++)
        if(i%3==0) {
            strcpy(notite[*nrNotite].data,linii[i]);
            strcpy(notite[*nrNotite].ora, linii[i+1]);
            strcpy(notite[*nrNotite].continut,linii[i+2]);
            remove_newline(notite[*nrNotite].data);
            remove_newline(notite[*nrNotite].ora);
            remove_newline(notite[*nrNotite].continut);
            (*nrNotite)++;
        }
}

void creeaza_notita_in_fisier() {
    char data[21],ora[11],continut[1001];
    printf("Introduceti data: ");
    scanf("%s",&data);
    getchar();
    printf("Introduceti ora: ");
    scanf("%s",&ora);
    getchar();
    printf("Introduceti continut: ");
    scanf("%99[^\n]",&continut);
    getchar();
    FILE *fp=fopen("notite.txt","a+");
    fprintf(fp,"%s\n%s\n%s\n",data,ora,continut);
    fclose(fp);
}
void print_notita(notes notita,int nrNotita) {
    printf("Notita (%d)\n", nrNotita);
    printf("Data: %s\n", notita.data);
    printf("Ora: %s\n", notita.ora);
    printf("Continut: %s\n", notita.continut);
    printf("\n");
}
void sterge_notita_din_memorie_si_fisier(notes notite[],int numarAles,int *nrNotite) {
    for(int i=numarAles;i<(*nrNotite-1);i++) // aici sterg din vector notita aleasa
        notite[i]=notite[i+1];
    (*nrNotite)--;
    FILE *fp=fopen("notite.txt","w");
    for(int i=0;i<(*nrNotite);i++)
        fprintf(fp,"%s\n%s\n%s\n",notite[i].data,notite[i].ora,notite[i].continut);
    fclose(fp);
}
void editeaza_notita_din_fisier_si_memorie(notes notite[],int numarAles,int nrNotite) {
    char data[21],ora[11],continut[1001];
    printf("Introduceti noua data: ");
    scanf("%s",&data);
    getchar();
    printf("Introduceti noua ora: ");
    scanf("%s",&ora);
    getchar();
    printf("Introduceti noul continut: ");
    scanf("%99[^\n]",&continut);
    getchar();
    strcpy(notite[numarAles].data,data);
    strcpy(notite[numarAles].ora,ora);
    strcpy(notite[numarAles].continut,continut);
    FILE *fp=fopen("notite.txt","w");
    for(int i=0;i<nrNotite;i++)
        fprintf(fp,"%s\n%s\n%s\n",notite[i].data,notite[i].ora,notite[i].continut);
    fclose(fp);
}

int main()
{
    int iesire=0,pozsageata=1,inainte=0,inapoi;
    int nrNotite;
    notes notite[101];
    citeste_notite_din_fisier_in_memorie(notite,&nrNotite);

    while (iesire==0)
    {
        system("cls");
        printf("-= MENIU PRINCIPAL =-\n");
        sageata(pozsageata,1);
        printf("1. Creare notita\n");
        sageata(pozsageata,2);
        printf("2. Vizualizare notite\n");
        sageata(pozsageata,3);
        printf("3. Editare notita\n");
        sageata(pozsageata,4);
        printf("4. Stergere notita\n\n");
        printf("Apasa ESC pentru a iesi");
        loopsageata(&pozsageata,1,4);
        optiuni(&pozsageata,&inainte,&iesire,&inapoi,1);
        if(inainte==1)
        {
            inainte=0;
            if(pozsageata==1)
            {
                /// Creare notite
                pozsageata=0;
                system("cls");
                creeaza_notita_in_fisier();
                citeste_notite_din_fisier_in_memorie(notite,&nrNotite);
            }
            if(pozsageata==2)
            {
                /// Vizualizare notite
                int inapoi=0;
                int sageatameniu=1;
                while(inapoi==0)
                {
                    inainte=0;
                    system("cls");
                    sageata(sageatameniu,1);
                    printf("1. Toate notitele\n");
                    sageata(sageatameniu,2);
                    printf("2. Notite dupa data");
                    optiuni(&sageatameniu, &inainte,&iesire,&inapoi,0);
                    loopsageata(&sageatameniu,1,2);
                    if(inainte==1) {
                        /// Vizualizare toate notitele
                        if(sageatameniu==1) {
                            int inapoimeniu=0,a,b;
                            while(inapoimeniu==0) {
                                system("cls");
                                for(int i=0;i<nrNotite;i++)
                                    print_notita(notite[i],i+1);
                                optiuni(&a,&b,&iesire,&inapoimeniu, 0);
                            }
                        }
                        else {
                            /// Vizualizare dupa data
                            int inapoimeniu=0,a,b;
                            system("cls");

                            char dataAnume[21];
                            printf("Introduceti data: ");
                            scanf("%s", &dataAnume);
                            while(inapoimeniu == 0) {
                                system("cls");
                                int existaNotite = 0;
                                for(int i = 0; i<nrNotite;i++) {
                                    if(strcmp(notite[i].data,dataAnume) == 0) {
                                        print_notita(notite[i],i+1);
                                        existaNotite=1;
                                    }
                                }
                                if(existaNotite==0)
                                    printf("Nu exista notite din data respectiva\n");

                                optiuni(&a,&b,&iesire,&inapoimeniu,0);
                            }
                        }
                    }
                }
            }
            if(pozsageata==3)
            {
                /// Editare notite
                int inapoimeniu=0,a,b;
                while(inapoimeniu==0)
                {
                    system("cls");
                    for(int i=0;i<nrNotite;i++)
                        print_notita(notite[i], i+1);
                    printf("Introduceti numarul notitei pe care doriti sa o editati (sau 0 ca sa anulati): ");
                    int numarAles;
                    scanf("%d",&numarAles);
                    if(numarAles==0)
                        inapoimeniu=1;
                    else {
                        numarAles--;
                        if(numarAles>= 0 && numarAles<nrNotite)
                            editeaza_notita_din_fisier_si_memorie(notite, numarAles, nrNotite);
                        else
                            printf("Nu exista notita cu numarul %d\n", numarAles+1);
                    }
                }
            }
            if(pozsageata==4)
            {
                /// Stergere notite
                int inapoimeniu=0,a,b;
                while(inapoimeniu==0)
                {
                    system("cls");
                    for(int i = 0; i<nrNotite;i++)
                        print_notita(notite[i],i+1);
                    printf("Introduceti numarul notitei pe care doriti sa o stergeti (sau 0 ca sa anulati): ");
                    int numarAles;
                    scanf("%d",&numarAles);
                    getchar();
                    if(numarAles==0)
                        inapoimeniu=1;
                    else {
                        numarAles--;
                        if(numarAles>=0 && numarAles<nrNotite)
                            sterge_notita_din_memorie_si_fisier(notite,numarAles,&nrNotite);
                        else
                            printf("Nu exista notita cu numarul respectiv\n");
                    }
                }
            }
        }
    }

    return 0;
}
