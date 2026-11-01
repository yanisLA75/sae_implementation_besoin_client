#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_NOM  30
#define MAX_PARTICIPANT 100
#define NB_CONCOURS_MAX 20

typedef struct {
	char nom[MAX_NOM + 1]; // + 1 pour le \0
	char prenom[MAX_NOM + 1];
	int score[NB_CONCOURS_MAX];
	int rang_davant[NB_CONCOURS_MAX];
}Participant;

typedef struct {
	char nomconcours[MAX_NOM + 1];
}Concours;

// je dois faire 10 fonctions pour les dix commandes ou plus meme
typedef struct {
	Participant participants[MAX_PARTICIPANT];
	int nb_participants;
	Concours liste_concours[NB_CONCOURS_MAX];
	int nb_concours;
}donnee;

// je cree une fonction pour verifier qu'il n'y ai pas deux fois le meme participant
int nom_connu(const donnee* d, const char* prenom, const char* nom) {
	for (int i = 0; i < d->nb_participants; i++) {
		if (strcmp(d->participants[i].prenom, prenom) == 0 && strcmp(d->participants[i].nom, nom) == 0) {
			return 1; // double
		}
	}
	return 0; // pas double
}
int creer_connu(donnee* d, const char* monconcours){
	for (int i = 0; i < d->nb_concours; ++i) {
		if (strcmp(d->liste_concours[i].nomconcours, monconcours) == 0)
			return 1;
	}
	return 0;
}

int Participant_inconnu(donnee* d, const int id) {
		if (id < 1 || id > d->nb_participants)
			return 1;
	return 0; 
}

int Concours_inconnu(donnee* d, const int concours) {
		if (concours < 1 || concours > d->nb_concours)
			return 1;
	return 0;
}
int Point_strict_pos(donnee* d, int nb_point) {
	if (nb_point < 1) {
		return 1;
	}
	return 0;
}



// je cree une fonction pour inscrire les participants
void inscrire(donnee* d, const char* prenom, const char* nom) {
	if (nom_connu(d, prenom, nom)) {
		printf("Nom incorrect\n");
		return;
	}
	/*if (d->nb_participants >= MAX_PARTICIPANT) {
		printf("Inscription impossible\n");
	}*/
	else{
		strcpy(d->participants[d->nb_participants].prenom, prenom);
		strcpy(d->participants[d->nb_participants].nom, nom);
		for (int i = 0; i < NB_CONCOURS_MAX; i++) {
			d->participants[d->nb_participants].score[i] = 0;
			d->participants[d->nb_participants].rang_davant[i] = 0;
		}
		printf("Inscription enregistree (%d)\n", ++d->nb_participants);
	}
}
//je cree une fonction pour voir les nombre de participant.e.s
void participants(donnee* d) {
	assert(d != NULL); // je verifie qu'y-il y a au moins un participant
	if (d->nb_participants == 0) {
		printf("Aucun participant inscrit\n");
		return;
	} 
	else {
		for (int i = 0; i < d->nb_participants; ++i) {
			int nb_concours_actif = 0;

			for (int j = 0; j < NB_CONCOURS_MAX; ++j)
				if (d->participants[i].score[j] > 0) //si score est positive on add un concours le lien entre ? score[NB_CONCOURS_MAX];
					++nb_concours_actif;

		printf("(%d) %s %s : %d concours\n", i + 1,
			d->participants[i].prenom,
			d->participants[i].nom,
			nb_concours_actif);
		}
	}
}

void creer(donnee* d, const char* nomconcours) {
	if (creer_connu(d, nomconcours)) {
		printf("Nom incorrect\n");
		return;
	}
	/*if (d->nb_concours >= NB_CONCOURS_MAX) {
		printf("Creation impossible\n");
		return;
	}*/
	else{
		strcpy(d->liste_concours[d->nb_concours].nomconcours, nomconcours);
		printf("Creation enregistree (%d)\n", ++d->nb_concours);
	}
}

void concours(donnee* d) {
	if (d->nb_concours == 0) {
		printf("Aucun concours cree\n");
		return;
	}
	else {
		for (int i = 0; i < d->nb_concours; ++i) {
			int nb_participant_actif = 0;

			for (int j = 0; j < d->nb_participants; ++j) {
				if (d->participants[j].score[i] > 0)
					++nb_participant_actif;
			}
			printf("(%d) %s : %d participant%s\n",
				i + 1,
				d->liste_concours[i].nomconcours,
				nb_participant_actif, nb_participant_actif > 1? "s": "");
		}
	}
}
void gain(donnee* d, const int id, const int concours, int point) {
	if (Participant_inconnu(d, id)) {
		printf("Participant incorrect\n");
		return;
	}
	if (Concours_inconnu(d, concours)) {
		printf("Concours incorrect\n");
		return;
	}
	if (Point_strict_pos(&d, point)) {
		printf("Points incorrects\n");
		return;
	}
	else {
		d->participants[id - 1].score[concours - 1] += point;
		printf("Gain enregistre\n");
	}
}

void scores(donnee* d, const int id) {
	if (Participant_inconnu(d, id)) {
		printf("Identifiant incorrect\n");
		return;
	}
	int index = id - 1;
	printf("%s %s\n", d->participants[index].prenom, d->participants[index].nom);

	int nb_gain = 0;
	for (int i = 0; i < d->nb_concours; ++i) {
		if (d->participants[index].score[i] > 0)
			++nb_gain;
	}
	if (nb_gain == 0) {
		printf("Aucun gain\n");
		return;
	}
	else {
		for (int i = 0; i < d->nb_concours; ++i) {
			if (d->participants[index].score[i] > 0) {
				printf("(%d) %s : %d point%s\n", i + 1,
					d->liste_concours[i].nomconcours,
					d->participants[index].score[i],
					d->participants[index].score[i] > 1 ? "s" : "");
			}
		}
	}
}

void classement(donnee* d, int id_concours) {
	if(creer_connu(d, id_concours)){
		printf("Identifiant incorrect\n");
		return;
	}
	int nb_participant = 0;

}

int main() {

	donnee d;
	d.nb_participants = 0;
	d.nb_concours = 0;

	char cmd[30];
	// dedans je fais la boucle dans laquelle je met tout les if et else etc
	while (1) {
		scanf("%s", cmd);
		if (strcmp(cmd, "EXIT") == 0) break;
		else if (strcmp(cmd, "INSCRIRE") == 0) {
			char prenom[MAX_NOM + 1], nom[MAX_NOM + 1];
			scanf("%s %s", prenom, nom);
			inscrire(&d, prenom, nom);
		}
		else if (strcmp(cmd, "PARTICIPANTS") == 0) {
			participants(&d);
		}
		else if (strcmp(cmd, "CREER") == 0) {
			char nomcrea[MAX_NOM + 1];
			scanf("%s", nomcrea);
			creer(&d, nomcrea);
		}
		else if (strcmp(cmd, "CONCOURS") == 0) {
			concours(&d);
		}
		else if (strcmp(cmd, "GAIN") == 0) {
			int id;
			int concours;
			int nb_point;
			scanf("%d %d %d",&id, &concours, &nb_point);
			gain(&d, id, concours, nb_point);
		}
		else if (strcmp(cmd, "SCORES") == 0) {
			int id;
			scanf("%d", &id);
			scores(&d, id);
		}
		else if (strcmp(cmd, "CLASSEMENT") == 0) {
			int id_concours;
			scanf("%d", &id_concours);
			classement(&d, id_concours);
		}
		else if (strcmp(cmd, "COMPARAISON") == 0) {

		}
		else if (strcmp(cmd, "BILAN") == 0) {

		}
		/*else if jusqua la fin */
	}

	return 0;
}