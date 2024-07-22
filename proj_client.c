#include<stdio.h>
#include<stdlib.h>


int nbr[]={1000,200,100,50}; // Quantité en stock
float argentcumule[]={0,0,0,0}; // Argent selon le produit
float prix[]={1.2,2,2,80}; //Prix de chacun produit

struct achat
{
	int baguette;
	int croissant;
	int millefeuilles;
	int tarte;
};
typedef struct achat achat;

typedef struct client client;
struct client
{
	int numeroclient;
	achat choixclient;
	client *suivant;
};


typedef struct File File;
struct File
{
	client *premier;
};


client *ajou() 
{
	client *nouveau=NULL;
	nouveau=malloc(sizeof(client));
	return nouveau;
}

achat choisir()
{
	int T[]={0,0,0,0}; // tableau qui repr�sente le panier du client
	int i;
	int choix,nombre;
	achat choixclient;
	do
	{
		printf("\tCombien voulez-vous de produits (entre 1 et 4) : ");
		scanf("%d",&nombre);
	}
	while(nombre<1 || nombre>4);
	
	for(i=0;i<nombre;i++)
	{
		do
		{
			printf("\t\t1-baguette \n\t\t2-croissant \n\t\t3-millefeuilles \n\t\t4-tarte \n \tNumero du produit que vous voulez :");
			scanf("%d",&choix);
			
		}while(choix<1 || choix>4);
		
		do
		{
			printf("\tLa quantite que vous voulez acheter :");
			scanf("%d",&T[choix-1]);
			if(T[choix-1]>nbr[choix-1])
			{
				printf("il nous reste juste %d dans le stock \n",nbr[choix-1]);
			}
		}while(T[choix-1]>nbr[choix-1] || T[choix-1]<0);
		
		nbr[choix-1]-=T[choix-1]; // mise � jour du stock
		argentcumule[choix-1]+=prix[choix-1]*T[choix-1]; // mise � jour e la caisse
	}
	
	choixclient.baguette=T[0];
	choixclient.croissant=T[1];
	choixclient.millefeuilles=T[2];
	choixclient.tarte=T[3];
	
	return choixclient;
}

void ajouterclient(File *f,int n)
{
	client *nouveau=ajou(); // Allocation de l'espace memoire pour un nouveau client
	
	//noeud contient des infos du client
	nouveau->numeroclient = n;
	nouveau->choixclient=choisir();	 
	nouveau->suivant=NULL;
	
	// construction de la file
	if(f->premier==NULL)
	{
		f->premier=nouveau;
	}
	else
	{
		client *tmp=f->premier;
		while(tmp->suivant!=NULL)
		{
			tmp=tmp->suivant;
		}
		tmp->suivant=nouveau;
	}

	affichageFile(f);
}

void affichageFile (File *f)
{
	printf("Ma file est comme suit :\n");
	client *c=f->premier; // c est un pointeur courant
	if(c==NULL)
		printf("Vide !!!\n");
	while(c!=NULL)
	{
		printf("[%d] : (%d)+(%d)+(%d)+(%d) -->\n",c->numeroclient,c->choixclient.baguette,c->choixclient.croissant,c->choixclient.millefeuilles,c->choixclient.tarte);
		c=c->suivant;
	}
	printf("Fin de la file !\n\n");
}

void modifierachat(File *f)
{
	int num,clientTrouve=0;
		
	client *parcourus;
	printf("\tEntrez le nombre du client :");
	scanf("%d",&num);
	parcourus=f->premier;
	while(parcourus !=NULL)
	{
		if(parcourus->numeroclient==num)
		{	
			nbr[0]+=parcourus->choixclient.baguette;
			nbr[1]+=parcourus->choixclient.croissant;
			nbr[2]+=parcourus->choixclient.millefeuilles;
			nbr[3]+=parcourus->choixclient.tarte;
			
			argentcumule[0]-=prix[0]*(parcourus->choixclient.baguette);
			argentcumule[1]-=prix[1]*(parcourus->choixclient.croissant);
			argentcumule[2]-=prix[2]*(parcourus->choixclient.millefeuilles);
			argentcumule[3]-=prix[3]*(parcourus->choixclient.tarte);
			
			printf("\tChoisissez a nouveau ce que vous voulez \n");
			parcourus->choixclient=choisir();
			clientTrouve=1; //Le client a �t� trouv�
		}
		parcourus=parcourus->suivant;
	}
	if (clientTrouve==0)
	{
		printf("Le client qui porte le num %d ne se trouve pas dans la liste !! \n",num);
	
	}
		
	
	affichageFile(f);
}

void supprimerclient(File *f)
{
	int num,clientTrouve=0;
		
	client *parcourus, *precedent;
	printf("\tEntrez le numero du client a supprimer :");
	scanf("%d",&num);
	parcourus=f->premier;
	precedent=parcourus;	
	
	while(parcourus !=NULL && clientTrouve==0)
	{
		printf("\tje suis ici :");
		if(parcourus->numeroclient==num)
		{				
			if(parcourus==f->premier)//Client au d�but de la file
				f->premier=parcourus->suivant;
			else if(parcourus->suivant!=NULL)//Client au milieu
				precedent->suivant=parcourus->suivant;
			else //Client � la fin 
			{
				precedent->suivant=NULL;
			}
			clientTrouve=1; //Le client a �t� trouv�
			break;
		}		
		precedent=parcourus;
		parcourus=parcourus->suivant;
	}
	if (clientTrouve==0)
	{
		printf("Le client qui porte le num %d ne se trouve pas dans la liste !! \n",num);
	
	}
	else
	{
		nbr[0]+=parcourus->choixclient.baguette;
		nbr[1]+=parcourus->choixclient.croissant;
		nbr[2]+=parcourus->choixclient.millefeuilles;
		nbr[3]+=parcourus->choixclient.tarte;
		
		argentcumule[0]-=prix[0]*(parcourus->choixclient.baguette);
		argentcumule[1]-=prix[1]*(parcourus->choixclient.croissant);
		argentcumule[2]-=prix[2]*(parcourus->choixclient.millefeuilles);
		argentcumule[3]-=prix[3]*(parcourus->choixclient.tarte);
		
		free(parcourus); // lib�rer la memoire du client supprim�
	}
		

	affichageFile(f);
}

void insererenfichier(File *f)
{
	FILE *fp=fopen("clients.txt","a+");
	if (fp==NULL)
		printf("Erreur!");
	else
	{

		client *c=f->premier; // c est un pointeur courant
		if(c==NULL)
			fprintf(fp,"\t-->Pas de client !!!\n");
		while(c!=NULL)
		{
			fprintf(fp,"\t-->Client Num %d  a achete %d baguettes + %d croissants + %d millefeuilles + %d tartes.\n",c->numeroclient,c->choixclient.baguette,c->choixclient.croissant,c->choixclient.millefeuilles,c->choixclient.tarte);
			c=c->suivant;
		}
		float argentgagne=argentcumule[0]+argentcumule[1]+argentcumule[2]+argentcumule[3];
		fprintf(fp,"\t-->Total en DH = %.2f\n",argentgagne);
		fprintf(fp,"Fin !\n\n");
	}
	fclose(fp);

}

void situationPatisserie()
{
	printf("\t-->Total d'argent gagne en DH = %.2f\n",argentcumule[0]+argentcumule[1]+argentcumule[2]+argentcumule[3]);
	printf("Dans le stock, il reste :\n");
	printf("\t-->%d baguette(s), %d croissant(s), %d millefeuile(s) et %d tarte(s).",nbr[0],nbr[1],nbr[2],nbr[3]);
	
}

int main()
{
	int n=1;
	int ope;
	File *f;
	f=malloc(sizeof(File));
	f->premier=NULL;
	
	do
	{
		printf("\n***** MENU *****\n");
		printf("\t1 : Ajouter un client \n");
		printf("\t2 : Supprimer un client \n");
		printf("\t3 : Modifier un client \n ");
		printf("\t4 : Sauvegarder vers fichier txt \n ");
		printf("\t5 : Situation patisserie \n ");
		printf("\t6 : Quitter \nVotre choix : ");
		scanf("%d",&ope);
		switch(ope)
		{
			case 1:
				ajouterclient(f,n);
				n++;
				break;
			case 2:
				supprimerclient(f);
				break;
			case 3:
				modifierachat(f);
				break;
			case 4:
				insererenfichier(f);
				break;
			case 5:
				situationPatisserie();
				break;
			case 6:
				exit(-1); // quitter le programme
			default:
				break;
		}
	}while(nbr[0]!=0 || nbr[1]!=0 || nbr[2]!=0 || nbr[3]!=0);
	
	
	return 0;
}
