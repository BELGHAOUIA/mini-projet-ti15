//code valide
#include<stdio.h>
#include <stdlib.h>

#define NB_LIGNES_JOUEURS 5
#define NB_COLONNES_JOUEURS 16

#define NB_LIGNES_HEROS 5
#define NB_COLONNES_HEROS 7

#define NB_LIGNES_UNITES 12
#define NB_COLONNES_UNITES 8

#define NB_LIGNES_HEROSJOUEURS 25
#define NB_COLONNES_HEROSJOUEURS 11

#define NB_LIGNES_UNITESJOUEURS 60
#define NB_COLONNES_UNITESJOUEURS 11

#define NB_LIGNES_CARTE 10
#define NB_COLONNES_CARTE 10

#define NB_EMPLACEMENT 6

#define NB_LIGNES_UNITESBATAILLE 12
#define NB_COLONNES_UNITESBATAILLE 13

#define NB_LIGNES_PLATEAUBATAILLE 12
#define NB_COLONNES_PLATEAUBATAILLE 12

#define JOUEUR_HUMAIN 0
#define LARGEUR_ECRAN_EN_CARACTERES 151
#define NB_EMPLACEMENTS_UNITES 6

typedef enum {NUM_JOUEUR_J, LIGNE_J, COLONNE_J, OR, BOIS, PIERRE, FER, SOUFFRE, SULFURE, GEMME_ROUGE, GEMME_BLEU, GEMME_JAUNE, NB_UNITES_TUEES, NB_BATAILLE_GAGNES, NB_UNITES_PERDUES, NB_BATAILLE_PERDUES} E_JOUEURS;
typedef enum { NUM_HERO_H, BONUS_ATTAQUE_H, BONUS_DEFENSE_H, CHANCE_CRITIQUE_H, MORAL_H, POINTS_ATTAQUE_SPECIALE_H, PRIX_H } E_HEROS;
typedef enum { NUM_UNITE_U, TYPE_U, SANTE_U, ATTAQUE_U, DEFENSE_U, DEGATS_U,MOUVEMENTS_U, PRIX_U } E_UNITES;
typedef enum { NUM_JOUEUR_HJ, NUM_HERO_HJ, HERO_PRINCIPAL, POINTS_EXPERIENCE, NIVEAU_HJ, POINTS_COMPETENCE_HJ, BONUS_ATTAQUE_HJ, BONUS_DEFENSE_HJ, CHANCE_CRITIQUE_HJ, MORAL_HJ, POINTS_ATTAQUE_SPECIALE_HJ } E_HEROSJOUEURS;
typedef enum { NUM_JOUEUR_UJ, NUM_UNITE_UJ, TYPE_UJ, SANTE_UJ, ATTAQUE_UJ, DEFENSE_UJ, DEGATS_UJ, MOUVEMENTS_UJ, NOMBRE_UJ, NIVEAU_UJ, UNITE_ACTIVE } E_UNITESJOUEURS;

typedef enum { NUM_JOUEUR_UB, NUM_UNITE_UB, TYPE_UB, SANTE_RESTANTE_UB, ATTAQUE_UB, DEFENSE_UB, DEGATS_UB, MOUVEMENTS_UB, NOMBRE_UNITES_UB, LIGNE_UB, COLONNE_UB, FINTOUR_UB, SANTE_UNITAIRE_UB} E_UNITESBATAILLE;

void chargerFichierVersTableau (int nb_lignes, int nb_colonnes, int tab[nb_lignes][nb_colonnes], char* nomFichier)
{
    int i,j;
    FILE *fic = fopen(nomFichier, "r");
    if(fic == NULL)
    {
        exit(1);
    }
    else
    {

        for(i=0; i<nb_lignes; i++)
        {
            for(j=0; j<nb_colonnes; j++)
            {
                fscanf(fic,"%d",&tab[i][j]);

            }
        }
    }
    fclose(fic);
}

void sauvegarderTableauDansFichier (int nb_lignes, int nb_colonnes, int tab[nb_lignes][nb_colonnes],char *nomFichier)
{

    int i,j;
    FILE *fic=fopen(nomFichier,"w");
    if(fic==NULL)
    {
        exit(1);
    }
    else
    {
        for(i=0; i<nb_lignes; i++)
        {
            for(j=0; j<nb_colonnes; j++)
            {
                fprintf(fic,"%d",tab[i][j]);

                if (j!=nb_colonnes-1)
                    fprintf(fic," ");
            }
            if(i!=nb_lignes-1)
                fprintf(fic,"\n");
        }
    }
    fclose(fic);
}



void afficherTableau (int nb_lignes, int nb_colonnes, int tab[nb_lignes][nb_colonnes], char* nomFichierEntete)
{
    int i,j,k,l;
    int max,larg_c,larg_i,nb_espace,larg_tab;
    max=150;
    larg_c=max/nb_colonnes;
    if(larg_c<=9)
    {
        larg_i=larg_c-1;
        nb_espace=0;
    }
    else
    {
        larg_i=7;
        nb_espace=(larg_c-larg_i-1)/2;
    }
    larg_c=larg_i+nb_espace*2+1;
    larg_tab=larg_c*nb_colonnes+1;

    for(i=0; i<larg_tab; i++)
    {
        printf("-");
        if(i==larg_tab-1)
        {
            printf("\n");
        }
    }
    FILE *fic=fopen(nomFichierEntete, "r");
    signed char entete[256];
    if(fic==NULL)
    {
        exit(1);
    }
    else
    {
        fgets(entete,255,fic);
        printf("%s\n",entete);
    }
    fclose(fic);

    for(i=0; i<larg_tab; i++)
    {
        printf("-");
    }
    printf("\n");
    for(l=0; l<nb_lignes; l++)
    {
        for(k=0; k<nb_colonnes; k++)
        {
            printf("|");

            for(i=1; i<=nb_espace; i++)
            {
                printf(" ");
            }
            printf("%*d",larg_i,tab[l][k]);
            for(i=1; i<=nb_espace; i++)
            {
                printf(" ");
            }
            if(k==nb_colonnes-1)
            {
                printf("|\n");
            }
        }
        for(i=0; i<larg_tab; i++)
        {
            printf("-");
            if(i==larg_tab-1)
            {
                printf("\n");
            }
        }
    }
}

void afficherTableauUneCondition (int colonne, int valeur, int nb_lignes, int nb_colonnes, int tab[nb_lignes][nb_colonnes], char* nomFichierEntete)
{
    int i,j,k,l;
    int max,larg_c,larg_i,nb_espace,larg_tab;
    max=150;
    larg_c=max/nb_colonnes;
    if(larg_c<=9)
    {
        larg_i=larg_c-1;
        nb_espace=0;
    }
    else
    {
        larg_i=7;
        nb_espace=(larg_c-larg_i-1)/2;
    }
    larg_c=larg_i+nb_espace*2+1;
    larg_tab=larg_c*nb_colonnes+1;

    printf("\n\n");

    for(i=0; i<larg_tab; i++)
    {
        printf("-");
        if(i==larg_tab-1)
        {
            printf("\n");
        }
    }
    FILE *fic=fopen(nomFichierEntete, "r");
    signed char entete[256];
    if(fic==NULL)
    {
        exit(1);
    }
    else
    {
        fgets(entete,255,fic);
        printf("%s\n",entete);
    }
    fclose(fic);

    for(i=0; i<larg_tab; i++)
    {
        printf("-");
    }
    printf("\n");
    for(l=0; l<nb_lignes; l++)
    {
        if(tab[l][colonne]==valeur)
        {
            for(k=0; k<nb_colonnes; k++)
            {
                printf("|");

                for(i=1; i<=nb_espace; i++)
                {
                    printf(" ");
                }
                printf("%*d",larg_i,tab[l][k]);
                for(i=1; i<=nb_espace; i++)
                {
                    printf(" ");
                }
                if(k==nb_colonnes-1)
                {
                    printf("|\n");
                }
            }
            for(i=0; i<larg_tab; i++)
            {
                printf("-");
                if(i==larg_tab-1)
                {
                    printf("\n");
                }
            }
        }
    }
}

void afficherTableauDeuxConditions (int colonne1, int valeur1, int colonne2, int valeur2, int nb_lignes, int nb_colonnes, int tab[nb_lignes][nb_colonnes], char* nomFichierEntete)
{
    int i,j,k,l;
    int max,larg_c,larg_i,nb_espace,larg_tab;
    max=150;
    larg_c=max/nb_colonnes;
    if(larg_c<=9)
    {
        larg_i=larg_c-1;
        nb_espace=0;
    }
    else
    {
        larg_i=7;
        nb_espace=(larg_c-larg_i-1)/2;
    }
    larg_c=larg_i+nb_espace*2+1;
    larg_tab=larg_c*nb_colonnes+1;

    printf("\n\n");

    for(i=0; i<larg_tab; i++)
    {
        printf("-");
        if(i==larg_tab-1)
        {
            printf("\n");
        }
    }
    FILE *fic=fopen(nomFichierEntete, "r");
    signed char entete[256];
    if(fic==NULL)
    {
        exit(1);
    }
    else
    {
        fgets(entete,255,fic);
        printf("%s\n",entete);
    }
    fclose(fic);

    for(i=0; i<larg_tab; i++)
    {
        printf("-");
    }
    printf("\n");
    for(l=0; l<nb_lignes; l++)
    {
        if(tab[l][colonne1]==valeur1 && tab[l][colonne2]==valeur2)
        {
            for(k=0; k<nb_colonnes; k++)
            {
                printf("|");

                for(i=1; i<=nb_espace; i++)
                {
                    printf(" ");
                }
                printf("%*d",larg_i,tab[l][k]);
                for(i=1; i<=nb_espace; i++)
                {
                    printf(" ");
                }
                if(k==nb_colonnes-1)
                {
                    printf("|\n");
                }
            }
            for(i=0; i<larg_tab; i++)
            {
                printf("-");
                if(i==larg_tab-1)
                {
                    printf("\n");
                }
            }
        }
    }
}


void afficherCarte(int carte[NB_LIGNES_CARTE][NB_COLONNES_CARTE] )
{
    int i,j,l,k;
    printf("CARTE DE JEU\n\n");

    printf("   ");
    for(i=0; i<10; i++)
    {
        printf("  %d  ", i);
    }
    printf("\n");
    printf("   ");
    for(i=0; i<49; i++)
    {
        printf("-");
    }
    printf("\n");

    for(l=0; l<NB_LIGNES_CARTE; l++)
    {
        printf(" %d",l);
        for(k=0; k<NB_COLONNES_CARTE; k++)
        {
            if(carte[l][k]==2)
            {
                printf("| J  ");
            }
            else if(carte[l][k]==1)
            {
                printf("| ?? ");
            }
            else if(carte[l][k]==0)
            {
                printf("|    ");
            }

            else if(carte[l][k]%10==1)
            {
                printf("| ?? ");
            }
            else if(carte[l][k]%10==0)
            {
                switch (carte[l][k]%100/10)
                {
                case 1:
                    switch (carte[l][k]/100)
                    {
                    case 1:
                        printf("| E1 ");
                        break;
                    case 2:
                        printf("| E2 ");
                        break;
                    case 3:
                        printf("| E3 ");
                        break;
                    case 4:
                        printf("| E4 ");
                        break;
                    }
                    break;
                case 2:
                    printf("| T  ");
                    break;
                case 3:
                    printf("| X  ");
                    break;
                }
            }
            else if(carte[l][k]%10==2)
            {
                switch(carte[l][k]%100/10)
                {
                case 1:
                    switch (carte[l][k]/100)
                    {
                    case 1:
                        printf("|JE1 ");
                        break;
                    case 2:
                        printf("|JE2 ");
                        break;
                    case 3:
                        printf("|JE3 ");
                        break;
                    case 4:
                        printf("|JE4 ");
                        break;
                    }
                    break;
                case 2:
                    printf("| JT ");
                    break;
                case 3:
                    printf("| JX ");
                    break;
                }
            }

            if(k==NB_COLONNES_CARTE-1)
            {
                printf("|\n");
            }
            if(k==NB_COLONNES_CARTE-1)
            {
                printf("   ");

                for(i=0; i<49; i++)
                {
                    printf("-");
                }
                printf("\n");
            }
        }
    }
}


void chargerJeuComplet(
    int carte[NB_LIGNES_CARTE][NB_COLONNES_CARTE],
    int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
    int heros[NB_LIGNES_HEROS][NB_COLONNES_HEROS],
    int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS],
    int unites[NB_LIGNES_UNITES][NB_COLONNES_UNITES],
    int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS] )
{

    chargerFichierVersTableau (NB_LIGNES_CARTE,NB_COLONNES_CARTE,carte,"carte_sauvegarde.txt");
    chargerFichierVersTableau (NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs,"joueurs_sauvegarde.txt");
    chargerFichierVersTableau (NB_LIGNES_HEROS,NB_COLONNES_HEROS,heros,"heros_sauvegarde.txt");
    chargerFichierVersTableau (NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs,"herosJoueurs_sauvegarde.txt");
    chargerFichierVersTableau (NB_LIGNES_UNITES,NB_COLONNES_UNITES,unites,"unites_sauvegarde.txt");
    chargerFichierVersTableau (NB_LIGNES_UNITESJOUEURS,NB_COLONNES_UNITESJOUEURS,unitesJoueurs,"unitesJoueurs_sauvegarde.txt");

}

void sauvegarderJeuComplet (int carte[NB_LIGNES_CARTE][NB_COLONNES_CARTE],
                            int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
                            int heros[NB_LIGNES_HEROS][NB_COLONNES_HEROS],
                            int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS],
                            int unites[NB_LIGNES_UNITES][NB_COLONNES_UNITES],
                            int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS])
{
    sauvegarderTableauDansFichier (NB_LIGNES_CARTE,NB_COLONNES_CARTE,carte,"carte_sauvegarde.txt");
    sauvegarderTableauDansFichier (NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS, joueurs,"joueurs_sauvegarde.txt");
    sauvegarderTableauDansFichier (NB_LIGNES_HEROS,NB_COLONNES_HEROS,heros,"heros_sauvegarde.txt");
    sauvegarderTableauDansFichier (NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS, herosJoueurs,"herosJoueurs_sauvegarde.txt");
    sauvegarderTableauDansFichier (NB_LIGNES_UNITES,NB_COLONNES_UNITES,unites,"unites_sauvegarde.txt");
    sauvegarderTableauDansFichier (NB_LIGNES_UNITESJOUEURS, NB_COLONNES_UNITESJOUEURS,unitesJoueurs,"unitesJoueurs_sauvegarde.txt");
}


void afficherTableauxJeu(
    int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
    int heros[NB_LIGNES_HEROS][NB_COLONNES_HEROS],
    int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS],
    int unites[NB_LIGNES_UNITES][NB_COLONNES_UNITES],
    int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS])
{
    printf("\nTableau Joueurs :\n");
    afficherTableau (NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs,"joueurs_entete.txt");
    printf("\nTableau Heros :\n");
    afficherTableau (NB_LIGNES_HEROS,NB_COLONNES_HEROS,heros,"heros_entete.txt");
    printf("\nTableau HerosJoueurs :\n");
    afficherTableau (NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs,"herosJoueurs_entete.txt");
    printf("\nTableau Unites :\n");
    afficherTableau (NB_LIGNES_UNITES,NB_COLONNES_UNITES,unites,"unites_entete.txt");
    printf("\nTableau UnitesJoueurs :\n");
    afficherTableau (NB_LIGNES_UNITESJOUEURS,NB_COLONNES_UNITESJOUEURS,unitesJoueurs,"unitesJoueurs_entete.txt");

}

void initialiserNouveauJeu (
    int carte[NB_LIGNES_CARTE][NB_COLONNES_CARTE],
    int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
    int heros[NB_LIGNES_HEROS][NB_COLONNES_HEROS],
    int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS],
    int unites[NB_LIGNES_UNITES][NB_COLONNES_UNITES],
    int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS])
{
    chargerFichierVersTableau (NB_LIGNES_CARTE,NB_COLONNES_CARTE,carte,"carte_original.txt");
    chargerFichierVersTableau (NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs,"joueurs_original.txt");
    chargerFichierVersTableau (NB_LIGNES_HEROS,NB_COLONNES_HEROS,heros,"heros_original.txt");
    chargerFichierVersTableau (NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs,"herosJoueurs_original.txt");
    chargerFichierVersTableau (NB_LIGNES_UNITES,NB_COLONNES_UNITES,unites,"unites_original.txt");
    chargerFichierVersTableau (NB_LIGNES_UNITESJOUEURS,NB_COLONNES_UNITESJOUEURS,unitesJoueurs,"unitesJoueurs_original.txt");

    sauvegarderJeuComplet (carte,joueurs,heros,herosJoueurs,unites,unitesJoueurs);
}


int chercherIndiceAvecUneCondition ( int colonneConcernee, int valeur, int nb_lignes, int nb_colonnes, int tab[nb_lignes][nb_colonnes] )
{
    int i,ok,rep;
    i=0;
    ok=0;
    rep=-1;
    while(ok==0 && i<nb_lignes)
    {
        if(tab[i][colonneConcernee]==valeur)
        {
            rep=i;
            ok=1;
        }
        else
        {
            i++;
        }
    }
    return rep;
}

int chercherIndiceAvecDeuxConditions ( int colonneConcernee1, int valeur1, int colonneConcernee2, int valeur2, int nb_lignes, int nb_colonnes, int tab[nb_lignes][nb_colonnes] )
{
    int i,ok,rep;
    i=0;
    ok=0;
    rep=-1;
    while(ok==0 && i<nb_lignes)
    {
        if((tab[i][colonneConcernee1]==valeur1) && (tab[i][colonneConcernee2]==valeur2))
        {
            rep=i;
            ok=1;
        }
        else
        {
            i++;
        }
    }
    return rep;
}


void afficherContenuCaseCarte ( int valeurCase,
                                int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS] )
{
    if(valeurCase%100/10==1)
    {
        afficherTableauDeuxConditions (NUM_JOUEUR_HJ,valeurCase/100,HERO_PRINCIPAL,1,NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs,"herosJoueurs_entete.txt");
    }
    else if(valeurCase%100/10==2)
    {
        printf(" ---------------------------------\n");
        printf("|  caisse a tresor = %d pieces !|\n", valeurCase/100);
        printf(" ---------------------------------\n");
    }
    else if(valeurCase%100/10==3)
    {
        printf(" ------------------------------------\n");
        printf("|  caisse d'experience = %d points !|\n", valeurCase/100);
        printf(" ------------------------------------\n");
    }

    else
    {
        printf(" --------------\n");
        printf("|  case vide ! |\n");
        printf(" --------------\n");
    }
}

void initialiserBataille ( int numJoueurHumain, int numJoueurEnnemi,
                           int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS],
                           int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS],
                           int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE],
                           int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE] )
{
    int i,j,l,index_humain,index_ennemi,col_humain=0,col_ennemi=0;


    for(i=0; i<NB_LIGNES_UNITESBATAILLE; i++)
    {
        for(j=0; j<NB_COLONNES_UNITESBATAILLE; j++)
        {
            unitesBataille[i][j]=-1;
        }
    }
    for(i=0; i<NB_LIGNES_PLATEAUBATAILLE; i++)
    {
        for(j=0; j<NB_COLONNES_PLATEAUBATAILLE; j++)
        {
            plateauBataille[i][j]=0;
        }
    }



    for(i=0; i<NB_LIGNES_UNITESJOUEURS; i++)
    {
        if(unitesJoueurs[i][NUM_JOUEUR_UJ]==numJoueurHumain && unitesJoueurs[i][UNITE_ACTIVE]==1)
        {
            index_humain=chercherIndiceAvecUneCondition(NUM_UNITE_UB,-1,NB_LIGNES_UNITESBATAILLE,NB_COLONNES_UNITESBATAILLE,unitesBataille);
            if(index_humain<6 && index_humain!=-1)
            {
                for( j=0; j<=NOMBRE_UJ; j++)
                {
                    unitesBataille[index_humain][j]=unitesJoueurs[i][j];
                }
                unitesBataille[index_humain][LIGNE_UB]=NB_LIGNES_PLATEAUBATAILLE-1;
                unitesBataille[index_humain][COLONNE_UB]=col_humain;
                unitesBataille[index_humain][FINTOUR_UB]=0;
                unitesBataille[index_humain][SANTE_UNITAIRE_UB]= unitesBataille[index_humain][SANTE_RESTANTE_UB];

                plateauBataille[NB_LIGNES_PLATEAUBATAILLE-1][col_humain]=unitesBataille[index_humain][NUM_UNITE_UB]*1000+numJoueurHumain*100+10;
                col_humain+=2;
            }
        }
        if(unitesJoueurs[i][NUM_JOUEUR_UJ]==numJoueurEnnemi && unitesJoueurs[i][UNITE_ACTIVE]==1)
        {
            l=NB_LIGNES_UNITESBATAILLE/2;
            while(l<NB_LIGNES_UNITESBATAILLE && unitesBataille[l][NUM_JOUEUR_UB]!=-1)
            {
                l++;
            }
            index_ennemi=l;

            if(index_ennemi<NB_LIGNES_UNITESBATAILLE)
            {
                for( j=0; j<=NOMBRE_UJ; j++)
                {
                    unitesBataille[index_ennemi][j]=unitesJoueurs[i][j];
                }
                unitesBataille[index_ennemi][LIGNE_UB]=0;
                unitesBataille[index_ennemi][COLONNE_UB]=col_ennemi;
                unitesBataille[index_ennemi][FINTOUR_UB]=0;
                unitesBataille[index_ennemi][SANTE_UNITAIRE_UB]= unitesBataille[index_ennemi][SANTE_RESTANTE_UB];

                plateauBataille[0][col_ennemi]=unitesBataille[index_ennemi][NUM_UNITE_UB]*1000+numJoueurEnnemi*100+10;
                col_ennemi+=2;

            }


        }

    }

}


void afficherPlateauBataille ( int numJoueur, int numJoueurEnnemi,
                               int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE],
                               int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE] )
{
    int i,j,l,k;


    afficherTableauUneCondition(NUM_JOUEUR_UB,numJoueurEnnemi,NB_LIGNES_UNITESBATAILLE,NB_COLONNES_UNITESBATAILLE,unitesBataille,"unitesBataille_entete.txt");
    printf("PLATEAU BATAILLE\n");

    printf("   ");
    for(i=0; i<NB_COLONNES_PLATEAUBATAILLE; i++)
    {
        printf("  %d   ", i);
    }
    printf("\n");
    printf("    ");
    for(i=0; i<NB_COLONNES_PLATEAUBATAILLE*6; i++)
    {
        printf("-");
    }
    printf("\n");

    for(l=0; l<NB_LIGNES_PLATEAUBATAILLE; l++)
    {
        if(l<10)
            printf(" ");
        printf("%d  ",l);
        for(k=0; k<NB_COLONNES_PLATEAUBATAILLE; k++)
        {
            if(plateauBataille[l][k]==0)
                printf("|     ");
            else if(plateauBataille[l][k]==1)
                printf("| +++ ");
            else if(plateauBataille[l][k]%100==10)
            {
                printf("|J%dU%-2d",plateauBataille[l][k]/100%10,plateauBataille[l][k]/1000);
            }

            if(k==NB_COLONNES_PLATEAUBATAILLE-1)
            {
                printf("|\n");
            }
            if(k==NB_LIGNES_PLATEAUBATAILLE-1)
            {
                printf("    ");

                for(i=0; i<NB_COLONNES_PLATEAUBATAILLE*6; i++)
                {
                    printf("-");
                }
                printf("\n");
            }
        }
    }

    afficherTableauUneCondition(NUM_JOUEUR_UB,numJoueur,NB_LIGNES_UNITESBATAILLE,NB_COLONNES_UNITESBATAILLE,unitesBataille,"unitesBataille_entete.txt");

}


void marquerDeplacementsPossibles (
    int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE],
    int ligneCourante, int colonneCourante, int mouvements )
{
    int i,j,min_lig,max_lig,min_col,max_col;

    if(ligneCourante+mouvements>NB_LIGNES_PLATEAUBATAILLE-1)
    {
        max_lig=NB_LIGNES_PLATEAUBATAILLE-1;
    }
    else
    {
        max_lig=ligneCourante+mouvements;
    }
    if(ligneCourante-mouvements<0)
    {
        min_lig=0;
    }
    else
    {
        min_lig=ligneCourante-mouvements;
    }

    if(colonneCourante+mouvements>NB_COLONNES_PLATEAUBATAILLE-1)
    {
        max_col=NB_COLONNES_PLATEAUBATAILLE-1;
    }
    else
    {
        max_col=colonneCourante+mouvements;
    }
    if(colonneCourante-mouvements<0)
    {
        min_col=0;
    }
    else
    {
        min_col=colonneCourante-mouvements;
    }


    for(i=min_lig; i<=max_lig; i++)
    {
        for(j=min_col; j<=max_col; j++)
        {

            if(plateauBataille[i][j]==0)
            {
                if(abs(ligneCourante-i)+abs(colonneCourante-j)<=mouvements)
                    plateauBataille[i][j]=1;
            }
        }
    }
}




void effacerDeplacementsPossibles (
    int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE] )
{
    int i,j;
    for(i=0; i<NB_LIGNES_PLATEAUBATAILLE; i++)
    {
        for(j=0; j<NB_COLONNES_PLATEAUBATAILLE; j++)
        {
            if(plateauBataille[i][j]==1)
            {
                plateauBataille[i][j]=0;
            }
        }

    }
}


void deplacerUnite ( int numJoueur, int indiceDansUniteEnBataille,
                     int numUnite, int ligne_courante, int colonne_courante, int nouvelle_ligne, int nouvelle_colonne,
                     int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE],
                     int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE] )
{
       plateauBataille[nouvelle_ligne][nouvelle_colonne]=plateauBataille[ligne_courante][colonne_courante];
       plateauBataille[ligne_courante][colonne_courante]=0;

       unitesBataille[indiceDansUniteEnBataille][LIGNE_UB]=nouvelle_ligne;
       unitesBataille[indiceDansUniteEnBataille][COLONNE_UB]=nouvelle_colonne;
}


int codeAttaqueSansDeplacement (
    int numJoueur, int typeUnite,
    int ligne_courante, int colonne_courante,
    int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE] )
{
    int i,premier_chiffre,deuxieme_chiffre,troisieme_chiffre,quaterieme_chiffre,cinquieme_chiffre;

    premier_chiffre = deuxieme_chiffre = troisieme_chiffre = quaterieme_chiffre = cinquieme_chiffre = 0;

    if(typeUnite == 1)
    {
        premier_chiffre = 1;
        return premier_chiffre;

    }
    else if(typeUnite == 0 || typeUnite == 2)
    {
        if(
            plateauBataille[ligne_courante-1][colonne_courante]%100 != 10 &&
            plateauBataille[ligne_courante+1][colonne_courante]%100 != 10 &&
            plateauBataille[ligne_courante][colonne_courante+1]%100 != 10 &&
            plateauBataille[ligne_courante][colonne_courante-1]%100 != 10
          )
            return premier_chiffre;
        else
        {
            premier_chiffre = 2;

            if(colonne_courante+1 < NB_COLONNES_PLATEAUBATAILLE)
            if(plateauBataille[ligne_courante][colonne_courante+1]%100 == 10 && (plateauBataille[ligne_courante][colonne_courante+1]/100)%10 != numJoueur)
                deuxieme_chiffre = 10;

            if(colonne_courante-1 >= 0)
            if(plateauBataille[ligne_courante][colonne_courante-1]%100 == 10 && (plateauBataille[ligne_courante][colonne_courante-1]/100)%10 != numJoueur)
                troisieme_chiffre = 100;

            if(ligne_courante+1 < NB_LIGNES_PLATEAUBATAILLE)
            if(plateauBataille[ligne_courante+1][colonne_courante]%100 == 10 && (plateauBataille[ligne_courante+1][colonne_courante]/100)%10 != numJoueur)
                quaterieme_chiffre = 1000;

            if(ligne_courante-1 >= 0)
            if(plateauBataille[ligne_courante-1][colonne_courante]%100 == 10 && (plateauBataille[ligne_courante-1][colonne_courante]/100)%10 != numJoueur)
                cinquieme_chiffre = 10000;

        }
        return premier_chiffre + deuxieme_chiffre + troisieme_chiffre + quaterieme_chiffre + cinquieme_chiffre;


    }
}


int uniteAttaquable ( int codeAttaque, int ligne_courante,
                      int colonne_courante, int ligne_ennemie,
                      int colonne_ennemie )
{
    int droit,gauche,bas,haut;

    droit = (codeAttaque%100)/10;
    gauche = (codeAttaque%1000)/100;
    bas = (codeAttaque%10000)/1000;
    haut = codeAttaque/10000;

    if(codeAttaque==1)
    {
        return 1;
    }

    else
    {
            if(droit == 1)
    {
        if(colonne_ennemie - colonne_courante == 1 && ligne_courante - ligne_ennemie == 0)
            return 1;
    }
    else if(gauche == 1)
    {
        if(colonne_courante - colonne_ennemie == 1 && ligne_courante - ligne_ennemie == 0)
            return 1;
    }

    else if(bas == 1)
    {
        if(ligne_ennemie - ligne_courante == 1 && colonne_courante - colonne_ennemie == 0)
            return 1;
    }

    else if(haut == 1)
    {
        if(ligne_courante - ligne_ennemie == 1 && colonne_courante - colonne_ennemie == 0)
            return 1;
    }

    else
    {
        return 0;
    }

    }

}


void attaque ( int indiceDansUniteEnBataille, int indiceEnnemiDansUnitesBataille,
               int numJoueur, int numEnnemi, int ligne, int colonne,
               int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE],
               int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE],
               int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS])
{
    float bonus,perte;
    int sante_totale_unite_attaque,sante_totale_restant,lig_humain,lig_ennemi,i,nb_unite;
    float op1,op2;

    bonus = (unitesBataille[indiceDansUniteEnBataille][DEGATS_UB] - unitesBataille[indiceEnnemiDansUnitesBataille][DEFENSE_UB])/200.0;
    perte = unitesBataille[indiceDansUniteEnBataille][NOMBRE_UNITES_UB] * (unitesBataille[indiceDansUniteEnBataille][DEGATS_UB] * (1 + bonus));

    if(unitesBataille[indiceEnnemiDansUnitesBataille][SANTE_RESTANTE_UB]!=unitesBataille[indiceEnnemiDansUnitesBataille][SANTE_UNITAIRE_UB])
    {
       sante_totale_unite_attaque=unitesBataille[indiceEnnemiDansUnitesBataille][SANTE_RESTANTE_UB]+(unitesBataille[indiceEnnemiDansUnitesBataille][SANTE_UNITAIRE_UB]*(unitesBataille[indiceEnnemiDansUnitesBataille][NOMBRE_UNITES_UB]-1));
    }
    else
    {
       sante_totale_unite_attaque=unitesBataille[indiceEnnemiDansUnitesBataille][SANTE_UNITAIRE_UB]*unitesBataille[indiceEnnemiDansUnitesBataille][NOMBRE_UNITES_UB];
    }

    sante_totale_restant=sante_totale_unite_attaque-perte;

    if(sante_totale_restant<=0)
    {
        lig_humain = chercherIndiceAvecUneCondition(NUM_JOUEUR_J,numJoueur,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs);
        lig_ennemi = chercherIndiceAvecUneCondition(NUM_JOUEUR_J,numEnnemi,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs);

        joueurs[lig_humain][NB_UNITES_TUEES]+=1;
        joueurs[lig_ennemi][NB_UNITES_PERDUES]+=1;
        plateauBataille[ligne][colonne]=0;

        for(i=NUM_JOUEUR_UB; i<=SANTE_UNITAIRE_UB; i++)
        {
            unitesBataille[indiceEnnemiDansUnitesBataille][i]=-1;

        }
    }
    else
    {
        op1=sante_totale_restant%unitesBataille[indiceEnnemiDansUnitesBataille][SANTE_UNITAIRE_UB];
        op2=sante_totale_restant/unitesBataille[indiceEnnemiDansUnitesBataille][SANTE_UNITAIRE_UB];
        unitesBataille[indiceEnnemiDansUnitesBataille][NOMBRE_UNITES_UB]=op2;

        if(op1!=0)
        {
            unitesBataille[indiceEnnemiDansUnitesBataille][NOMBRE_UNITES_UB]+=1;
            unitesBataille[indiceEnnemiDansUnitesBataille][SANTE_RESTANTE_UB]=op1;
        }
        else
        {
            unitesBataille[indiceEnnemiDansUnitesBataille][SANTE_RESTANTE_UB]=unitesBataille[indiceEnnemiDansUnitesBataille][SANTE_UNITAIRE_UB];
        }
    }
    printf("<< sante totale de l'unite attaquee %d - degats inflige %.0f = sante totale restante %d >> \n",sante_totale_unite_attaque,perte,sante_totale_restant);

}


void reinitialiserToursBataille (
    int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE] )
{
    int i;

    for(i=0; i<NB_LIGNES_UNITESBATAILLE; i++)
    {

        if(unitesBataille[i][FINTOUR_UB]==1)
        {
            unitesBataille[i][FINTOUR_UB]=0;
        }

    }
}

int verificationGagnant ( int numJoueur, int numJoueurEnnemi,
                          int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE] )
{
    int i,nb_joueur,nb_ennemie;
    nb_joueur=nb_ennemie=0;

    for(i=0; i<NB_LIGNES_UNITESBATAILLE; i++)
    {

        if(unitesBataille[i][NUM_JOUEUR_UB]==numJoueur)
        {
            nb_joueur++;
        }

        if(unitesBataille[i][NUM_JOUEUR_UB]==numJoueurEnnemi)
        {
            nb_ennemie++;
        }

    }

    if(nb_joueur!=0 && nb_ennemie!=0)
        return -1;

    if(nb_joueur!=0 && nb_ennemie==0)
        return numJoueur;
    return numJoueurEnnemi;
}




int verificationFinTours ( int numJoueur,
                           int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE] )
{
    int i,nb=0;

    for(i=0; i<NB_LIGNES_UNITESBATAILLE; i++)
    {

        if(unitesBataille[i][FINTOUR_UB]==0 && unitesBataille[i][NUM_JOUEUR_UB]==numJoueur)
        {
            nb++;
        }

    }
    if(nb==0)
        return 1; //le fin de tour
    return 0; //n'est pas le fin de tour
}



int jouerTourHumainBataille ( int numJoueur, int numJoueurEnnemi,
                              int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
                              int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS],
                              int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE],
                              int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE] )
{
       int choix_entree, lig_unite_selectionnee,lig_ub,col_ub,mouv_ub,ligne_case,colonne_case,num_unite,est_hero_principal,est_unite_principal;
       int code_attaque,choix,lig_ennemie,col_ennemie,lig_ennemie_selectionne,choix_deplacer;
       int lig, col, ligne;
       int verification_Fin_Tours,verification_Gagnant,fin_tour_forcee=0;
       verification_Fin_Tours = 0;

       ligne=chercherIndiceAvecUneCondition (NUM_JOUEUR_J,0,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs);
       lig=joueurs[ligne][LIGNE_J];
       col=joueurs[ligne][COLONNE_J];

         do{
                printf("--- Tour Joueur Humain ---\n");

            afficherPlateauBataille (numJoueur,numJoueurEnnemi,plateauBataille,unitesBataille);
           do{
                fin_tour_forcee = 0;
                lig_unite_selectionnee = 0;

            printf("donner le numero d'unite a jouer ou -1 si vous voulez forcer la fin du tour : ");
            scanf(" %d",&choix_entree);
            if(choix_entree==-1)
            {
                fin_tour_forcee = -1;
            }
            else if(choix_entree>=0)

            {
                num_unite=choix_entree;
               lig_unite_selectionnee=chercherIndiceAvecDeuxConditions(NUM_JOUEUR_UB,numJoueur,NUM_UNITE_UB,num_unite,NB_LIGNES_UNITESBATAILLE,NB_COLONNES_UNITESBATAILLE,unitesBataille);
            }
           }while(lig_unite_selectionnee==-1 || unitesBataille[lig_unite_selectionnee][FINTOUR_UB] == 1 || choix_entree<-1);


            if(choix_entree>-1)
            {
                lig_ub=unitesBataille[lig_unite_selectionnee][LIGNE_UB];
                col_ub=unitesBataille[lig_unite_selectionnee][COLONNE_UB];
                mouv_ub=unitesBataille[lig_unite_selectionnee][MOUVEMENTS_UB];
                marquerDeplacementsPossibles(plateauBataille,lig_ub,col_ub,mouv_ub);
                afficherPlateauBataille(numJoueur,numJoueurEnnemi,plateauBataille,unitesBataille);

                printf("les cases marquees de +++ sont les cases ou l'hero pourra s'y placer!\n");
             do{
                printf("voulez vous deplacer l'unite? (1:oui / 0:non)");
                scanf(" %d",&choix_deplacer);
               }while(choix_deplacer>1 || choix_deplacer<0);

                if(choix_deplacer==1)
                {
                    do{
                    do
                    {
                            printf("donner la ligne de la case a jouer (depuis les cases possibles marquees de + ) : ");
                            scanf("%d", &ligne_case);
                            printf("donner la colonne de la case a jouer (depuis les cases possibles marquees de + ) : ");
                            scanf("%d", &colonne_case);
                    }
                    while(((abs(ligne_case-lig_ub) + abs(colonne_case-col_ub))> mouv_ub));
                    }while(plateauBataille[ligne_case][colonne_case] != 1);

                    printf("--- deplacement de l'unite %d du joueur humain de la case (%d,%d) a la case (%d,%d) ---\n",num_unite,lig_ub,col_ub,ligne_case,colonne_case);
                    deplacerUnite(numJoueur,lig_unite_selectionnee,num_unite,lig_ub,col_ub,ligne_case,colonne_case,plateauBataille,unitesBataille);
                }
                    effacerDeplacementsPossibles(plateauBataille);
                    afficherPlateauBataille (numJoueur,numJoueurEnnemi,plateauBataille,unitesBataille);
                    //
                    code_attaque=codeAttaqueSansDeplacement(numJoueur,unitesBataille[lig_unite_selectionnee][TYPE_UB],unitesBataille[lig_unite_selectionnee][LIGNE_UB],unitesBataille[lig_unite_selectionnee][COLONNE_UB],plateauBataille);
                    if(code_attaque==1 || code_attaque>2)
                    {
                        printf("cette unite a la possibilites d'attaquer ! \n ");
                        do
                        {
                            printf("vous avez attaquer un enemie ? (1:oui /0:non) ");
                            scanf(" %d",&choix);
                        }
                        while(choix>1 || choix<0);
                        if(choix==1)
                        {
                            do{
                            printf("donner la ligne de la case de l'unite enemie adjacente a attaquer :");
                            scanf("%d",&lig_ennemie);
                            printf("donner la colonne de la case de l'unite enemie adjacente a attaquer :");
                            scanf("%d",&col_ennemie);
                            }while(uniteAttaquable(code_attaque,unitesBataille[lig_unite_selectionnee][LIGNE_UB],unitesBataille[lig_unite_selectionnee][COLONNE_UB],lig_ennemie,col_ennemie)!=1);
                            lig_ennemie_selectionne=chercherIndiceAvecDeuxConditions(NUM_UNITE_UB,plateauBataille[lig_ennemie][col_ennemie]/1000,NUM_JOUEUR_UB,numJoueurEnnemi,NB_LIGNES_UNITESBATAILLE,NB_COLONNES_UNITESBATAILLE,unitesBataille);
                            if(uniteAttaquable(code_attaque,ligne_case,colonne_case,lig_ennemie,col_ennemie))
                            {
                                printf("L'unite %d du joueur humain attaque l'unite %d d'ennemie %d ! \n",num_unite,plateauBataille[lig_ennemie][col_ennemie]/1000,numJoueurEnnemi);
                                attaque(lig_unite_selectionnee,lig_ennemie_selectionne,numJoueur,numJoueurEnnemi,lig_ennemie,col_ennemie,plateauBataille,unitesBataille,joueurs);
                                afficherPlateauBataille(numJoueur,numJoueurEnnemi,plateauBataille,unitesBataille);
                              if(unitesBataille[lig_unite_selectionnee][TYPE_UB]!=1)
                                {
                                   printf("L'unite %d du joueur ennemie contre attaque l'unite %d du joueur humain ! \n",plateauBataille[lig_ennemie][col_ennemie]/1000,num_unite);
                                   attaque(lig_ennemie_selectionne,lig_unite_selectionnee,numJoueurEnnemi,numJoueur,ligne_case,colonne_case,plateauBataille,unitesBataille,joueurs);
                                   afficherPlateauBataille(numJoueur,numJoueurEnnemi,plateauBataille,unitesBataille);

                                }

                            }
                        }
                    }
            }
           unitesBataille[lig_unite_selectionnee][FINTOUR_UB] = 1;

         verification_Fin_Tours = verificationFinTours(numJoueur,unitesBataille);

         verification_Gagnant = verificationGagnant(numJoueur,numJoueurEnnemi,unitesBataille);

           if(verification_Gagnant != -1 )
              return verification_Gagnant;
        }
        while(verification_Fin_Tours == 0 && fin_tour_forcee==0);


}


int choixAutomatiqueUniteEnnemie ( int numJoueurEnnemi, int codeAttaque,
                                   int ligne_courante, int colonne_courante,
                                   int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE],
                                   int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE] )
{
    int indice_unite_selectionne,num_unite_selectionne;
    int droit,gauche,bas,haut;


    if(codeAttaque==1)
    {
        indice_unite_selectionne = chercherIndiceAvecUneCondition(NUM_JOUEUR_UB,numJoueurEnnemi,NB_LIGNES_UNITESBATAILLE,NB_COLONNES_UNITESBATAILLE,unitesBataille);
        num_unite_selectionne = unitesBataille[indice_unite_selectionne][NUM_UNITE_UB];
        return num_unite_selectionne;
    }
    else if(codeAttaque>2)
    {
    droit = (codeAttaque%100)/10;
    gauche = (codeAttaque%1000)/100;
    bas = (codeAttaque%10000)/1000;
    haut = codeAttaque/10000;

            if(droit == 1)
    {
        num_unite_selectionne = plateauBataille[ligne_courante][colonne_courante+1]/1000;
            return num_unite_selectionne;
    }
    else if(gauche == 1)
    {
        num_unite_selectionne = plateauBataille[ligne_courante][colonne_courante-1]/1000;
            return num_unite_selectionne;
    }

    else if(bas == 1)
    {
        num_unite_selectionne = plateauBataille[ligne_courante+1][colonne_courante]/1000;
            return num_unite_selectionne;
    }

    else if(haut == 1)
    {
        num_unite_selectionne = plateauBataille[ligne_courante-1][colonne_courante]/1000;
            return num_unite_selectionne;
    }
    }

}


void deplacementAutomatiqueUnite( int numJoueur, int typeUnite,
                                  int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE],
                                  int ligne_courante, int colonne_courante,
                                  int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE],
                                  int indiceUnite )
{
    int found,i,j,nouvelle_ligne,nouvelle_colonne,code_attaque;

    found = 0;
    i = j = 0;
    nouvelle_ligne = ligne_courante;
    nouvelle_colonne = colonne_courante;
   while(found == 0 && i<NB_LIGNES_PLATEAUBATAILLE)
   {
   while(found == 0 && j<NB_COLONNES_PLATEAUBATAILLE)
   {
           if(plateauBataille[i][j]==1)
              {
            code_attaque = codeAttaqueSansDeplacement(numJoueur,typeUnite,nouvelle_ligne,nouvelle_colonne,plateauBataille);

                 if(code_attaque>2 || code_attaque==1)
               {
                found = 1;
               }

            else
                {   nouvelle_ligne = i;
                    nouvelle_colonne = j;
                }
               }
               j++;
    }
  i++;
  j = 0;
   }
   effacerDeplacementsPossibles(plateauBataille);
 if(nouvelle_ligne!=ligne_courante || nouvelle_colonne!=colonne_courante)
   deplacerUnite(numJoueur,indiceUnite,unitesBataille[indiceUnite][NUM_UNITE_UB],ligne_courante,colonne_courante,nouvelle_ligne,nouvelle_colonne,plateauBataille,unitesBataille);

 printf("--- deplacement de l'unite %d du joueur ennemie %d de la case (%d,%d) a la case (%d,%d) ---\n",unitesBataille[indiceUnite][NUM_UNITE_UB],numJoueur,ligne_courante,colonne_courante,nouvelle_ligne,nouvelle_colonne);
}


int jouerTourEnnemiBataille ( int numJoueur, int numJoueurEnnemi,
                              int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
                              int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS],
                              int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE],
                              int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE] )
{
       int choix_entree, lig_unite_selectionnee,lig_ub,col_ub,mouv_ub,ligne_case,colonne_case,num_unite,est_hero_principal,est_unite_principal;
       int code_attaque,choix,lig_ennemie,col_ennemie,lig_ennemie_selectionne;
       int num_unite_ennemi_auto;
       int verification_Fin_Tours,verification_Gagnant;
       verification_Fin_Tours = 0;

         do{
                printf("--- Tour Joueur Ennemie ---\n");

            afficherPlateauBataille (numJoueur,numJoueurEnnemi,plateauBataille,unitesBataille);
            lig_unite_selectionnee=chercherIndiceAvecDeuxConditions(NUM_JOUEUR_UB,numJoueur,FINTOUR_UB,0,NB_LIGNES_UNITESBATAILLE,NB_COLONNES_UNITESBATAILLE,unitesBataille);
               unitesBataille[lig_unite_selectionnee][FINTOUR_UB] = 1;

                lig_ub=unitesBataille[lig_unite_selectionnee][LIGNE_UB];
                col_ub=unitesBataille[lig_unite_selectionnee][COLONNE_UB];
                mouv_ub=unitesBataille[lig_unite_selectionnee][MOUVEMENTS_UB];
                if(unitesBataille[lig_unite_selectionnee][TYPE_UB]!=1)
                {
                marquerDeplacementsPossibles(plateauBataille,lig_ub,col_ub,mouv_ub);
                afficherPlateauBataille(numJoueur,numJoueurEnnemi,plateauBataille,unitesBataille);
                printf("les cases marquees de +++ sont les cases ou l'hero pourra s'y placer!\n");
                deplacementAutomatiqueUnite(numJoueur,unitesBataille[lig_unite_selectionnee][TYPE_UB],plateauBataille,lig_ub,col_ub,unitesBataille,lig_unite_selectionnee);

                    effacerDeplacementsPossibles(plateauBataille);
                    afficherPlateauBataille (numJoueur,numJoueurEnnemi,plateauBataille,unitesBataille);
                }
                //
                  ligne_case=unitesBataille[lig_unite_selectionnee][LIGNE_UB];
                  colonne_case=unitesBataille[lig_unite_selectionnee][COLONNE_UB];

                    code_attaque=codeAttaqueSansDeplacement(numJoueur,unitesBataille[lig_unite_selectionnee][TYPE_UB],ligne_case,colonne_case,plateauBataille);
                    if(code_attaque==1 || code_attaque>2)
                    {
                        printf("cette unite a la possibilites d'attaquer ! \n ");

                          num_unite_ennemi_auto = choixAutomatiqueUniteEnnemie(numJoueurEnnemi,code_attaque,ligne_case,colonne_case,plateauBataille,unitesBataille);

                            lig_ennemie_selectionne=chercherIndiceAvecDeuxConditions(NUM_UNITE_UB,num_unite_ennemi_auto,NUM_JOUEUR_UB,numJoueurEnnemi,NB_LIGNES_UNITESBATAILLE,NB_COLONNES_UNITESBATAILLE,unitesBataille);
                            lig_ennemie = unitesBataille[lig_ennemie_selectionne][LIGNE_UB];
                            col_ennemie = unitesBataille[lig_ennemie_selectionne][COLONNE_UB];

                            num_unite = unitesBataille[lig_unite_selectionnee][NUM_UNITE_UB];

                            if(uniteAttaquable(code_attaque,ligne_case,colonne_case,lig_ennemie,col_ennemie))
                            {
                                printf("L'unite %d du joueur ennemie %d attaque l'unite %d du joueur humain ! \n",num_unite,numJoueur,plateauBataille[lig_ennemie][col_ennemie]/1000);
                                attaque(lig_unite_selectionnee,lig_ennemie_selectionne,numJoueur,numJoueurEnnemi,lig_ennemie,col_ennemie,plateauBataille,unitesBataille,joueurs);
                                afficherPlateauBataille(numJoueur,numJoueurEnnemi,plateauBataille,unitesBataille);

                         if(unitesBataille[lig_unite_selectionnee][TYPE_UB]!=1)
                         {
                                printf("L'unite %d du joueur humain contre attaque l'unite %d du joueur ennemie ! \n",plateauBataille[lig_ennemie][col_ennemie]/1000,num_unite,numJoueur);
                                attaque(lig_ennemie_selectionne,lig_unite_selectionnee,numJoueurEnnemi,numJoueur,ligne_case,colonne_case,plateauBataille,unitesBataille,joueurs);
                                afficherPlateauBataille(numJoueur,numJoueurEnnemi,plateauBataille,unitesBataille);

                         }

                            }
                        }

         verification_Fin_Tours = verificationFinTours(numJoueur,unitesBataille);
         verification_Gagnant = verificationGagnant(numJoueur,numJoueurEnnemi,unitesBataille);
         if(verification_Gagnant != -1)
            return verification_Gagnant;
        }
        while(verification_Fin_Tours == 0);
}



void deroulerBataille ( int numJoueur, int numJoueurEnnemi,
                        int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
                        int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS],
                        int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS] )
{
        int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE];
        int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE];
        int nb_tour_de_bataille,tour_humain,tour_ennemie,i,indice_humain,indice_ennemie,loser,winner;
        nb_tour_de_bataille = 0;
        tour_ennemie = tour_humain = -1;

        initialiserBataille(numJoueur,numJoueurEnnemi,herosJoueurs,unitesJoueurs,plateauBataille,unitesBataille);

      do
      {
        printf("--- Tour %d ---\n",nb_tour_de_bataille);

        if(tour_humain==-1)
      {
        tour_humain = jouerTourHumainBataille(numJoueur,numJoueurEnnemi,joueurs,herosJoueurs,plateauBataille,unitesBataille);
                  reinitialiserToursBataille(unitesBataille);
      }

        if(tour_humain==-1 && tour_ennemie==-1)
        {
           tour_ennemie = jouerTourEnnemiBataille(numJoueurEnnemi,numJoueur,joueurs,herosJoueurs,plateauBataille,unitesBataille);
                     reinitialiserToursBataille(unitesBataille);
        }

          nb_tour_de_bataille++;

      }while(tour_humain==-1 && tour_ennemie==-1);

     indice_humain = chercherIndiceAvecUneCondition(NUM_JOUEUR_J,numJoueur,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs);
     indice_ennemie = chercherIndiceAvecUneCondition(NUM_JOUEUR_J,numJoueurEnnemi,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs);

     if(tour_humain== joueurs[indice_humain][NUM_JOUEUR_J] || tour_ennemie== joueurs[indice_humain][NUM_JOUEUR_J])
        {
            loser = indice_ennemie;
            winner = indice_humain;
        }
    else
        {
            loser = indice_humain;
            winner = indice_ennemie;
        }

     for(i=OR;i<GEMME_JAUNE;i++)
     {
         joueurs[winner][i] += joueurs[loser][i];
         joueurs[loser][i] = 0;
     }

     joueurs[winner][NB_BATAILLE_GAGNES] += 1;
     joueurs[loser][NB_BATAILLE_PERDUES] += 1;

     printf("--- la joueur %d a gagne la bataille !!! ---\n",joueurs[winner][NUM_JOUEUR_J]);
}


void lancerMenuAchatHeros ( int numJoueur,
                            int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
                            int heros[NB_LIGNES_HEROS][NB_COLONNES_HEROS],
                            int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS] )
{
    int nb_choix, num_hero, lig_joueur, lig_hero, lig_hero_j;
    int or,prix, lig_vide, ans,lig_hero_j_j;
    do
    {
        printf("\n\n\n");
        printf("<<<<<    Informations du Joueur Humain :    >>>>>\n");
        afficherTableauUneCondition(NUM_JOUEUR_J,numJoueur,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs,"joueurs_entete.txt");
        printf("\n");

        printf("liste des Heros disponible pour achat :\n");
        afficherTableau (NB_LIGNES_HEROS,NB_COLONNES_HEROS,heros,"heros_entete.txt");
        lig_hero_j_j=chercherIndiceAvecUneCondition(NUM_JOUEUR_HJ,numJoueur,NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs);

        if(lig_hero_j_j!=-1)
        {
            printf("\n");
            printf("Heros du joueur humain :");
            afficherTableauUneCondition(NUM_JOUEUR_HJ,numJoueur,NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs,"herosJoueurs_entete.txt");
        }


        printf("************************************\n");
        printf("**    Menu achat heros            **\n");
        printf("************************************\n");
        printf("* 1 - Acheter un nouveau hero     **\n");
        printf("* 0 - Revenir au menu precedent   **\n");
        printf("************************************\n");
        do
        {
            printf("Entrer votre choix (0-1) :\t");
            scanf("%d", &nb_choix);
        }
        while(nb_choix<0 || nb_choix>1);
        switch(nb_choix)
        {
        case 1:
        {
            do
            {
                printf("Entrez le numero du hero que vous voulez acheter :\t");
                scanf("%d", &num_hero);
            }
            while(num_hero<1 || num_hero>NB_LIGNES_HEROS);

            lig_vide=chercherIndiceAvecUneCondition (NUM_JOUEUR_HJ,-1,NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs);

            if(lig_vide==-1)
            {
                printf("on a atteint le nombre d'achat maximal !!!\n");
            }

            else
            {
                lig_hero_j=chercherIndiceAvecDeuxConditions(NUM_JOUEUR_HJ,numJoueur,NUM_HERO_HJ,num_hero,NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs);

                if(lig_hero_j!=-1)
                {
                    printf("Achat annule, on ne peut acheter une autre foix le heros %d !\n", num_hero);
                }
                else
                {
                    lig_joueur=chercherIndiceAvecUneCondition (NUM_JOUEUR_J,numJoueur,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs);
                    lig_hero=chercherIndiceAvecUneCondition (NUM_HERO_H,num_hero,NB_LIGNES_HEROS,NB_COLONNES_HEROS,heros);
                    or= joueurs[lig_joueur][OR];
                    prix= heros[lig_hero][PRIX_H];
                    if(or<prix)
                    {
                        printf("Achat annule, le joueur ne dispose pas du solde suffisant pour acheter ce heros !\n");
                    }
                    else
                    {
                        printf("Confiemez l'achat (non=0, oui=1) :\t");
                        scanf("%d", &ans);
                        if(ans==1)
                        {
                            herosJoueurs[lig_vide][NUM_JOUEUR_HJ]=numJoueur;
                            herosJoueurs[lig_vide][NUM_HERO_HJ]=num_hero;
                            herosJoueurs[lig_vide][HERO_PRINCIPAL]=0;
                            herosJoueurs[lig_vide][POINTS_EXPERIENCE]=0;
                            herosJoueurs[lig_vide][NIVEAU_HJ]=0;
                            herosJoueurs[lig_vide][POINTS_COMPETENCE_HJ]=0;
                            herosJoueurs[lig_vide][BONUS_ATTAQUE_HJ]=heros[lig_hero][BONUS_ATTAQUE_H];
                            herosJoueurs[lig_vide][BONUS_DEFENSE_HJ]=heros[lig_hero][BONUS_DEFENSE_H];
                            herosJoueurs[lig_vide][CHANCE_CRITIQUE_HJ]=heros[lig_hero][CHANCE_CRITIQUE_H];
                            herosJoueurs[lig_vide][MORAL_HJ]=heros[lig_hero][MORAL_H];
                            herosJoueurs[lig_vide][POINTS_ATTAQUE_SPECIALE_HJ]=heros[lig_hero][POINTS_ATTAQUE_SPECIALE_H];

                            joueurs[lig_joueur][OR]-=prix;
                            printf("Achat effectue avec succes !\n");
                        }
                    }
                }
            }
        }
        }
    }
    while(nb_choix!=0);

}


void lancerMenuAchatUnites ( int numJoueur,
                             int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
                             int unites[NB_LIGNES_UNITES][NB_COLONNES_UNITES],
                             int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS] )
{
    int nb_choix, num_unite, lig_joueur, lig_unite, lig_unite_j;
    int or,prix, lig_vide, ans, nb_soldat,lig_unite_j_j;
    do
    {
        printf("\n\n\n");
        printf("<<<<<    Informations du Joueur Humain :    >>>>>\n");
        afficherTableauUneCondition(NUM_JOUEUR_J,numJoueur,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs,"joueurs_entete.txt");
        printf("\n");

        printf("liste des unites disponible pour achat :\n");
        afficherTableau (NB_LIGNES_UNITES,NB_COLONNES_UNITES,unites,"unites_entete.txt");
        lig_unite_j_j=chercherIndiceAvecUneCondition(NUM_JOUEUR_UJ,numJoueur,NB_LIGNES_UNITESJOUEURS,NB_COLONNES_UNITESJOUEURS,unitesJoueurs);
        if(lig_unite_j_j!=-1)
        {
            printf("\n");
            printf("Informations des unites du joueur humain :");
            afficherTableauUneCondition(NUM_JOUEUR_UJ,numJoueur,NB_LIGNES_UNITESJOUEURS,NB_COLONNES_UNITESJOUEURS,unitesJoueurs,"unitesJoueurs_entete.txt");
        }


        printf("************************************\n");
        printf("**    Menu achat unites           **\n");
        printf("************************************\n");
        printf("* 1 - Acheter une nouvelle unite  **\n");
        printf("* 0 - Revenir au menu precedent   **\n");
        printf("************************************\n");
        do
        {
            printf("Entrer votre choix (0-1) :\t");
            scanf("%d", &nb_choix);
        }
        while(nb_choix<0 || nb_choix>1);
        switch(nb_choix)
        {
        case 1:
        {
            printf("Entrez le numero du unite que vous voulez acheter :\t");
            scanf("%d", &num_unite);

            lig_vide=chercherIndiceAvecUneCondition (NUM_JOUEUR_UJ,-1,NB_LIGNES_UNITESJOUEURS,NB_COLONNES_UNITESJOUEURS,unitesJoueurs);

            if(lig_vide==-1)
            {
                printf("on a atteint le nombre d'achat maximal !!!\n");
            }
            else
            {
                lig_unite=chercherIndiceAvecUneCondition (NUM_UNITE_U,num_unite,NB_LIGNES_UNITES,NB_COLONNES_UNITES,unites);
                if(lig_unite==-1)
                {
                    printf("Vous n'avez pas une unite avec ce numero !\n");
                }
                else
                {
                    lig_joueur=chercherIndiceAvecUneCondition (NUM_JOUEUR_J,numJoueur,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs);
                    or= joueurs[lig_joueur][OR];
                    prix= unites[lig_unite][PRIX_U];

                    printf("Entrez le nombre de soldats que vous voulez acheter de ce type d'unite :\t");
                    scanf("%d", &nb_soldat);
                    if(or<prix*nb_soldat)
                    {
                        printf("Achat annule, le joueur ne dispose pas du solde suffisant pour acheter cette unite!\n");
                    }
                    else
                    {
                        printf("Confiemez l'achat (non=0, oui=1) : \t");
                        scanf("%d", &ans);
                        if(ans==1)
                        {
                            lig_unite_j=chercherIndiceAvecDeuxConditions(NUM_JOUEUR_UJ,numJoueur,NUM_UNITE_UJ,num_unite,NB_LIGNES_UNITESJOUEURS,NB_COLONNES_UNITESJOUEURS,unitesJoueurs);

                            if(lig_unite_j!=-1)
                            {
                                unitesJoueurs[lig_unite_j][NOMBRE_UJ]+=nb_soldat;
                            }
                            else
                            {
                                unitesJoueurs[lig_vide][NUM_JOUEUR_UJ]=numJoueur;
                                unitesJoueurs[lig_vide][NUM_UNITE_UJ]=num_unite;
                                unitesJoueurs[lig_vide][TYPE_UJ]=unites[lig_unite][TYPE_U];
                                unitesJoueurs[lig_vide][SANTE_UJ]=unites[lig_unite][SANTE_U];
                                unitesJoueurs[lig_vide][ATTAQUE_UJ]=unites[lig_unite][ATTAQUE_U];
                                unitesJoueurs[lig_vide][DEFENSE_UJ]=unites[lig_unite][DEFENSE_U];
                                unitesJoueurs[lig_vide][DEGATS_UJ]=unites[lig_unite][DEGATS_U];
                                unitesJoueurs[lig_vide][MOUVEMENTS_UJ]=unites[lig_unite][MOUVEMENTS_U];
                                unitesJoueurs[lig_vide][NOMBRE_UJ]=nb_soldat;
                                unitesJoueurs[lig_vide][NIVEAU_UJ]=0;
                                unitesJoueurs[lig_vide][UNITE_ACTIVE]=0;
                            }
                            joueurs[lig_joueur][OR]-=prix*nb_soldat;
                            printf("Achat effectue avec succes !\n");
                        }
                    }
                }
            }
        }
        }

    }
    while(nb_choix!=0);
}


void lancerMenuConfigurationHeros ( int numJoueur,
                                    int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
                                    int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS] )
{
    int nb_choix, num_hero, lig_hero_j, hero_pr,lig_hero_j_existe;
    do
    {
        printf("Informations des Heros du Joueur Humain :\n");
        afficherTableauUneCondition(NUM_JOUEUR_HJ,numJoueur,NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs,"herosJoueurs_entete.txt");

        printf("************************************************\n");
        printf("**    Menu configuration hero                 **\n");
        printf("************************************************\n");
        printf("** 1 - Mettre un nouveau hero comme principal **\n");
        printf("** 0 - Revenir au menu precedent              **\n");
        printf("************************************************\n");
        do
        {
            printf("Entrer votre choix (0-1) :\t");
            scanf("%d", &nb_choix);
        }
        while(nb_choix<0 || nb_choix>1);
        switch(nb_choix)
        {
        case 1:
        {
            do
            {
                printf("Enterz le numero de votre nouveau hero principal :\t");
                scanf("%d", &num_hero);
            }
            while(num_hero<1 || num_hero>NB_LIGNES_HEROS);

            lig_hero_j=chercherIndiceAvecDeuxConditions(NUM_JOUEUR_HJ,numJoueur,NUM_HERO_HJ,num_hero,NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs);

            if(lig_hero_j==-1)
            {
                printf("Vous n'avez pas un hero avec ce numero !\n");
            }
            else
            {
                lig_hero_j_existe=chercherIndiceAvecDeuxConditions(NUM_JOUEUR_HJ,numJoueur,HERO_PRINCIPAL,1,NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs);
                if(lig_hero_j_existe==-1)
                {
                    herosJoueurs[lig_hero_j][HERO_PRINCIPAL]=1;
                    printf("Hero %d est l'hero principal !\n", num_hero);
                }
                else
                {
                    hero_pr=chercherIndiceAvecDeuxConditions(NUM_JOUEUR_HJ,numJoueur,HERO_PRINCIPAL,1,NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs);

                    herosJoueurs[hero_pr][HERO_PRINCIPAL]=0;
                    herosJoueurs[lig_hero_j][HERO_PRINCIPAL]=1;
                    printf("Hero %d est l'hero principal !\n", num_hero);

                }

            }
        }
        }

    }

    while(nb_choix!=0);
}


void lancerMenuConfigurationUnites ( int numJoueur,
                                     int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS] )
{
    int nb_choix, num_unite, lig_unite_j, unite_act, nb_emp, unite_reserve, i;


    do
    {
        printf("Informations des unites du Joueur Humain :\n");
        afficherTableauUneCondition(NUM_JOUEUR_UJ,numJoueur,NB_LIGNES_UNITESJOUEURS,NB_COLONNES_UNITESJOUEURS,unitesJoueurs,"unitesJoueurs_entete.txt");

        printf("******************************************\n");
        printf("**    Menu configuration unites         **\n");
        printf("******************************************\n");
        printf("** 1 - Mettre une unite comme principal **\n");
        printf("** 2 - Mettre une unite comme reserve   **\n");
        printf("** 0 - Revenir au menu precedent        **\n");
        printf("******************************************\n");
        do
        {
            printf("Entrer votre choix (0-2) :\t");
            scanf("%d", &nb_choix);
        }
        while(nb_choix<0 || nb_choix>2);
        switch(nb_choix)
        {
        case 1:
        {
            nb_emp=0;
            for(i=0; i<NB_LIGNES_UNITESJOUEURS; i++)
            {
                if(unitesJoueurs[i][NUM_JOUEUR_UJ]==0 && unitesJoueurs[i][UNITE_ACTIVE]==1)
                {
                    nb_emp++;
                }
            }
            if(nb_emp==NB_EMPLACEMENT)
            {
                printf("Le nombre maximum des unites actives est atteint !\n");

            }
            else
            {

                printf("Enterz le numero d'unite a rendre comme principal :\t");
                scanf("%d", &num_unite);

                lig_unite_j=chercherIndiceAvecDeuxConditions(NUM_JOUEUR_UJ,numJoueur,NUM_UNITE_UJ,num_unite,NB_LIGNES_UNITESJOUEURS,NB_COLONNES_UNITESJOUEURS,unitesJoueurs);

                if(lig_unite_j==-1)
                {
                    printf("Vous n'avez pas un unite avec ce numero !\n");
                }
                else
                {
                    unitesJoueurs[lig_unite_j][UNITE_ACTIVE]=1;
                    printf("Unite %d devenue principal !\n", num_unite);

                }
            }
        }

        break;

        case 2:
        {
            printf("Enterz le numero d'unite a rendre comme reserve :\t");
            scanf("%d", &num_unite);

            unite_reserve=chercherIndiceAvecDeuxConditions(NUM_JOUEUR_UJ,numJoueur,NUM_UNITE_UJ,num_unite,NB_LIGNES_UNITESJOUEURS,NB_COLONNES_UNITESJOUEURS,unitesJoueurs);
            if(unite_reserve==-1)
            {
                printf("Vous n'avez pas un unite avec ce numero !\n");
            }
            else
            {
                unitesJoueurs[unite_reserve][UNITE_ACTIVE]=0;
                printf("Unite %d devenue reserve !\n", num_unite);

            }
        }
        break;
        }
    }
    while(nb_choix!=0);
}


void executerAction (
    int carte[NB_LIGNES_CARTE][NB_COLONNES_CARTE],
    int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
    int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS],
    int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS],
    int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE],
    int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE] )
{
    int lig, col, ligne, nb_choix, ligne_hj, val1, val2,hero_j,ligne_hj_h;
    int est_hero_principal,est_unite_principal,bataille_gagne,bataille_perdu;
    ligne=chercherIndiceAvecUneCondition (NUM_JOUEUR_J,0,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs);

    lig=joueurs[ligne][LIGNE_J];
    col=joueurs[ligne][COLONNE_J];

    val1=carte[lig][col]%100/10;
    val2=carte[lig][col]/100;

    if(val1==1)
    {
        printf("confirmez vous l'entree en bataille avec l'enemie %d ?\t", val2);
        printf("(non=0, oui=1) :\t");
        do
        {
            scanf("%d", &nb_choix);
        }
        while(nb_choix!=0 && nb_choix!=1);
        switch(nb_choix)
        {
        case 0:
            break;
        case 1:
            bataille_gagne = chercherIndiceAvecDeuxConditions(NUM_JOUEUR_J,val2,NB_BATAILLE_GAGNES,1,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs);
            bataille_perdu = chercherIndiceAvecDeuxConditions(NUM_JOUEUR_J,val2,NB_BATAILLE_PERDUES,1,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs);

            if(bataille_gagne==-1 && bataille_perdu==-1)
            {
            est_hero_principal=chercherIndiceAvecDeuxConditions(NUM_JOUEUR_HJ,JOUEUR_HUMAIN,HERO_PRINCIPAL,1,NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs);
            est_unite_principal=chercherIndiceAvecDeuxConditions(NUM_JOUEUR_UJ,JOUEUR_HUMAIN,UNITE_ACTIVE,1,NB_LIGNES_UNITESJOUEURS,NB_COLONNES_UNITESJOUEURS,unitesJoueurs);
                 if(est_hero_principal!=-1 || est_unite_principal!=-1)
                {
                    deroulerBataille(JOUEUR_HUMAIN,carte[lig][col]/100,joueurs,herosJoueurs,unitesJoueurs);
                }
                 else
                {
                    printf("vous n'avez pas un unite active");
                }
            }
            else
            {
                printf("bataille deja faite");
            }
         break;
        }}

    else if(val1==2)
    {
        if(val2==0)
        {
            printf("Coffre de tresor deja ouvert !\n");
        }
        else
        {
            printf("confirmez vous l'ajout de %d pieces d'or a votre fortune personnelle ?\t",val2);
            printf("(non=0, oui=1) :\t");
            do
            {
                scanf("%d", &nb_choix);
            }
            while(nb_choix!=0 && nb_choix!=1);
            switch(nb_choix)
            {
            case 0:
                break;
            case 1:
                joueurs[ligne][OR]+=val2;
                printf("Un montant %d a ete ajoute a votre fortune !\n",val2);
                carte[lig][col]-=val2*100;

                break;
            }
        }
    }
    else if(val1==3)
    {
        if(val2==0)
        {
            printf("Coffre d'experience deja ouvert !\n");
        }
        else
        {
            ligne_hj_h=chercherIndiceAvecUneCondition (NUM_JOUEUR_HJ,0,NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs);

            if(ligne_hj_h==-1)
            {
                printf("vous n'avez pas un hero");
            }
            else
            {
                ligne_hj=chercherIndiceAvecDeuxConditions(NUM_JOUEUR_HJ,0,HERO_PRINCIPAL,1,NB_LIGNES_HEROSJOUEURS,NB_COLONNES_HEROSJOUEURS,herosJoueurs);
                if(ligne_hj==-1)
                {
                    printf("vous n'avez pas un hero principale");
                }
                else
                {
                    printf("confirmez vous l'ajout de %d points d'experience a votre hero principale ?\t",val2);
                    printf("(non=0, oui=1) :\t");
                    do
                    {
                        scanf("%d", &nb_choix);
                    }
                    while(nb_choix!=0 && nb_choix!=1);
                    switch(nb_choix)
                    {
                    case 0:
                        break;
                    case 1:
                    {
                        herosJoueurs[ligne_hj][POINTS_EXPERIENCE]+=val2;
                        printf("Un quantite %d a ete ajoute a l'experience de votre hero principale !\n",val2);
                        carte[lig][col]-=val2*100;
                        break;
                    }
                    }
                }
            }
        }
    }
}


void degagerNuages ( int lig, int col, int carte[NB_LIGNES_CARTE][NB_COLONNES_CARTE] )
{
    int i,j,min_lig,max_lig,min_col,max_col;

    if(lig+2>NB_LIGNES_CARTE-1)
    {
        max_lig=NB_LIGNES_CARTE-1;
    }
    else
    {
        max_lig=lig+2;
    }
    if(lig-2<0)
    {
        min_lig=0;
    }
    else
    {
        min_lig=lig-2;
    }

    if(col+2>NB_COLONNES_CARTE-1)
    {
        max_col=NB_COLONNES_CARTE-1;
    }
    else
    {
        max_col=col+2;
    }
    if(col-2<0)
    {
        min_col=0;
    }
    else
    {
        min_col=col-2;
    }


    for(i=min_lig; i<=max_lig; i++)
    {
        for(j=min_col; j<=max_col; j++)
        {
            if(carte[i][j]==1)
            {
                carte[i][j]-=1;
            }
            else if(carte[i][j]%10==1)
            {
                carte[i][j]-=1;
            }
        }
    }
}


void avancer ( char action,
               int carte[NB_LIGNES_CARTE][NB_COLONNES_CARTE],
               int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS] )
{
    int l,k;
    int old_LIGNE_J,old_COLONNE_J, LIG, COL, ligne;
    ligne=chercherIndiceAvecUneCondition (NUM_JOUEUR_J,0,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs);
    old_LIGNE_J=joueurs[ligne][LIGNE_J];
    old_COLONNE_J=joueurs[ligne][COLONNE_J];
    if (action=='h')
    {
        if(joueurs[ligne][LIGNE_J]-1<0)
        {
            joueurs[ligne][LIGNE_J]=joueurs[ligne][LIGNE_J];
        }
        else
        {
            joueurs[ligne][LIGNE_J]=joueurs[ligne][LIGNE_J]-1;
            carte[old_LIGNE_J][old_COLONNE_J]-=2;
        }
    }
    else if (action=='b')
    {
        if(joueurs[ligne][LIGNE_J]+1>NB_LIGNES_CARTE-1)
        {
            joueurs[ligne][LIGNE_J]=joueurs[ligne][LIGNE_J];
        }
        else
        {
            joueurs[ligne][LIGNE_J]=joueurs[ligne][LIGNE_J]+1;
            carte[old_LIGNE_J][old_COLONNE_J]-=2;
        }
    }

    else if (action=='g')
    {
        if(joueurs[ligne][COLONNE_J]-1<0)
        {
            joueurs[ligne][COLONNE_J]=joueurs[ligne][COLONNE_J];
        }
        else
        {
            joueurs[ligne][COLONNE_J]=joueurs[ligne][COLONNE_J]-1;
            carte[old_LIGNE_J][old_COLONNE_J]-=2;
        }
    }

    else if (action=='d')
    {
        if(joueurs[ligne][COLONNE_J]+1>NB_LIGNES_CARTE-1)
        {
            joueurs[ligne][COLONNE_J]=joueurs[ligne][COLONNE_J];
        }
        else
        {
            joueurs[ligne][COLONNE_J]=joueurs[ligne][COLONNE_J]+1;
            carte[old_LIGNE_J][old_COLONNE_J]-=2;
        }
    }
    LIG=joueurs[ligne][LIGNE_J];
    COL=joueurs[ligne][COLONNE_J];

    if (carte[LIG][COL]==0)
    {
        carte[LIG][COL]=carte[LIG][COL]+2;
    }
    else if (carte[LIG][COL]==1)
    {
        {
            carte[LIG][COL]=carte[LIG][COL]+1;
        }
    }
    else if(carte[LIG][COL]%10==0)
    {
        carte[LIG][COL]=carte[LIG][COL]+2;
    }
    else if(carte[LIG][COL]%10==1)
    {
        carte[LIG][COL]=carte[LIG][COL]+1;
    }
    degagerNuages (LIG,COL,carte);

}


void deroulerJeu (
    int carte[NB_LIGNES_CARTE][NB_COLONNES_CARTE],
    int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
    int heros[NB_LIGNES_HEROS][NB_COLONNES_HEROS],
    int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS],
    int unites[NB_LIGNES_UNITES][NB_COLONNES_UNITES],
    int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS],
    int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE],
    int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE])
{
    char nb_choix;
    int i,j, ValeurCase,lig_joueur;
    do
    {
        printf("\n\n\n");
        printf("<<<<<    JOUEUR HUMAIN    >>>>>\n");
        afficherTableauUneCondition(NUM_JOUEUR_J,0,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs,"joueurs_entete.txt");
        printf("\n");
        afficherCarte(carte);
        printf("\n");
        printf("<<<<<    CONTENU DE LA CASE DU JOUEUR    >>>>>\n");
        lig_joueur=chercherIndiceAvecUneCondition (NUM_JOUEUR_J,0,NB_LIGNES_JOUEURS,NB_COLONNES_JOUEURS,joueurs);

        ValeurCase=carte[joueurs[lig_joueur][LIGNE_J]][joueurs[lig_joueur][COLONNE_J]];

        afficherContenuCaseCarte (ValeurCase,herosJoueurs);
        do
        {
            printf("cliquer sur (h=haut , b=bas , g=gauche , d=droite , a=action , 0=menu principal) :");
            scanf(" %c", &nb_choix);
        }
        while(nb_choix!='h' && nb_choix!='b' && nb_choix!='g' && nb_choix!='d' && nb_choix!='a' && nb_choix!='0');
        if(nb_choix=='a')
        {
            executerAction (carte,joueurs,herosJoueurs,unitesJoueurs,plateauBataille,unitesBataille);
            sauvegarderJeuComplet (carte,joueurs,heros,herosJoueurs,unites,unitesJoueurs);
        }
        else
        {
            avancer(nb_choix,carte,joueurs);
            sauvegarderJeuComplet (carte,joueurs,heros,herosJoueurs,unites,unitesJoueurs);
        }
    }
    while(nb_choix!='0');
}


void lancerMenuCampement (
    int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
    int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS],
    int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS] )
{
    int nb_choix;
    do
    {
        printf("************************************\n");
        printf("**      Menu Campement            **\n");
        printf("************************************\n");
        printf("* 1 - Configuration heros         **\n");
        printf("* 2 - Configuration unites        **\n");
        printf("* 0 - Revenir au menu precedent   **\n");
        printf("************************************\n");
        do
        {
            printf("Entrer votre choix (0-2) :\t");
            scanf("%d", &nb_choix);
        }
        while(nb_choix<0 || nb_choix>2);
        switch(nb_choix)
        {
        case 1:
            lancerMenuConfigurationHeros(0,joueurs,herosJoueurs);
            break;
        case 2:
            lancerMenuConfigurationUnites(0,unitesJoueurs);
            break;
        }
    }
    while(nb_choix!=0);
}

void lancerMenuMagasin (
    int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
    int heros[NB_LIGNES_HEROS][NB_COLONNES_HEROS],
    int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS],
    int unites[NB_LIGNES_UNITES][NB_COLONNES_UNITES],
    int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS] )
{
    int nb_choix,i,valeur,colonne;
    sauvegarderTableauDansFichier (NB_LIGNES_UNITESJOUEURS,NB_COLONNES_UNITESJOUEURS, unitesJoueurs,"unitesJoueurs_sauvegarde.txt");

    do
    {
        printf("************************************\n");
        printf("**      Menu Magasin              **\n");
        printf("************************************\n");
        printf("* 1 - Acheter des heros           **\n");
        printf("* 2 - Acheter des unites          **\n");
        printf("* 0 - Revenir au menu precedent   **\n");
        printf("************************************\n");
        do
        {
            printf("Entrer votre choix (0-2) :\t");
            scanf("%d", &nb_choix);
        }
        while(nb_choix<0 || nb_choix>2);
        switch(nb_choix)
        {
        case 1:
            lancerMenuAchatHeros (0,joueurs,heros,herosJoueurs );
            break;
        case 2:
            lancerMenuAchatUnites (0,joueurs,unites,unitesJoueurs);
            break;
        }
    }
    while(nb_choix!=0);
}

void lancerMenuPrincipal (
    int carte[NB_LIGNES_CARTE][NB_COLONNES_CARTE],
    int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS],
    int heros[NB_LIGNES_HEROS][NB_COLONNES_HEROS],
    int herosJoueurs[NB_LIGNES_HEROSJOUEURS][NB_COLONNES_HEROSJOUEURS],
    int unites[NB_LIGNES_UNITES][NB_COLONNES_UNITES],
    int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS],
    int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE],
    int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE])
{
    int nb_choix;
    do
    {
        printf("************************************\n");
        printf("**      Menu principal            **\n");
        printf("************************************\n");
        printf("* 1 - Magasin                     **\n");
        printf("* 2 - Campement                   **\n");
        printf("* 3 - Reprendre le jeu en cours   **\n");
        printf("* 4 - Nouvelle partie             **\n");
        printf("* 5 - Quitter                     **\n");
        printf("************************************\n");
        do
        {
            printf("Entrer votre choix (1-5) :\t");
            scanf("%d", &nb_choix);
        }
        while(nb_choix<1 || nb_choix>5);

        switch(nb_choix)
        {
        case 1:
            lancerMenuMagasin(joueurs,heros,herosJoueurs,unites,unitesJoueurs);
            sauvegarderJeuComplet (carte,joueurs,heros,herosJoueurs,unites,unitesJoueurs);
            break;
        case 2:
            lancerMenuCampement(joueurs,herosJoueurs,unitesJoueurs);
            sauvegarderJeuComplet (carte,joueurs,heros,herosJoueurs,unites,unitesJoueurs);
            break;
        case 3:
            deroulerJeu(carte,joueurs,heros,herosJoueurs,unites,unitesJoueurs,plateauBataille,unitesBataille);
            break;
        case 4:
        {
            initialiserNouveauJeu (carte,joueurs,heros,herosJoueurs,unites,unitesJoueurs);
            sauvegarderJeuComplet (carte,joueurs,heros,herosJoueurs,unites,unitesJoueurs);
        }
        break;
        }
    }
    while(nb_choix!=5);
}


int main()
{
    int carte[NB_LIGNES_CARTE][NB_COLONNES_CARTE];
    int joueurs[NB_LIGNES_JOUEURS][NB_COLONNES_JOUEURS];
    int heros[NB_LIGNES_HEROS][NB_COLONNES_HEROS];
    int unites[NB_LIGNES_UNITES][NB_COLONNES_UNITES];
    int unitesJoueurs[NB_LIGNES_UNITESJOUEURS][NB_COLONNES_UNITESJOUEURS];
    int herosJoueurs[NB_LIGNES_HEROSJOUEURS ][NB_COLONNES_HEROSJOUEURS ];
    int plateauBataille[NB_LIGNES_PLATEAUBATAILLE][NB_COLONNES_PLATEAUBATAILLE];
    int unitesBataille[NB_LIGNES_UNITESBATAILLE][NB_COLONNES_UNITESBATAILLE];
    int nb_choix;
    printf("************************************\n");
    printf("*HEROES MAGIC WAR - CHARACTER MODE**\n");
    printf("************************************\n");
    printf("* 1 - Nouvele partie              **\n");
    printf("* 2 - charger partie              **\n");
    printf("************************************\n");
    do
    {
        printf("Entrer votre choix (1-2) :\t");
        scanf("%d",&nb_choix);

    }
    while(nb_choix!=1 && nb_choix!=2);

    switch(nb_choix)
    {
    case 1:
    {
        initialiserNouveauJeu (carte,joueurs,heros,herosJoueurs,unites,unitesJoueurs);
        sauvegarderJeuComplet (carte,joueurs,heros,herosJoueurs,unites,unitesJoueurs);

    }
    break;

    case 2:
    {
        chargerJeuComplet(carte,joueurs,heros,herosJoueurs,unites,unitesJoueurs);
    }
    break;
    }
    /*  afficherTableauxJeu(joueurs,heros,herosJoueurs,unites,unitesJoueurs);
      printf("\n");
      afficherCarte(carte);*/
    printf("\n");
    lancerMenuPrincipal (carte,joueurs,heros,herosJoueurs,unites,unitesJoueurs,plateauBataille,unitesBataille);
}


