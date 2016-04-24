#ifndef E_FENETRETYPE_H_INCLUDED
#define E_FENETRETYPE_H_INCLUDED

typedef enum{fenetreQuitter=-1,fenetreTitre,fenetreSelecNbJoueur,fenetreConfigJoueur,fenetreDureePartie,fenetreDifficulte,fenetreJeu,fenetreCarteEvenement,fenetreRegles, fenetreSauvegarde} E_fenetre;

#define chrono_Action 600                           //definit le temps entre 2 action
#define chrono_AnimationCourte 250                  //celui des animationCourte
#define chrono_AnimationLongue 750                 //celui des animation Longue
#define chrono_FinPartie 5000                       //temps ou on affiche le vainqueur
#define chrono_AnimationTraitre 100                //celui des animationTraitre


#endif // E_FENETRETYPE_H_INCLUDED
