# SNAKE GAME 

## Description

Ce projet est une version du jeu Snake en utilisant SDL2.
Le joueur est le serpent qui doit manger des fruits pour grandir.

## Fonctionnalités: 

Il y a 2 modes de jeu pour le snake :

### Premier mode : 

- Le **mode normal** classique avec un seul fruit qui le fait grandir à chaque fois qu'il le mange.

### Deuxième mode : 

- Le **mode avec 4 types fruits** qui ont chacun leurs particularités quand il est mangé.

### Les Types de Fruits dans le Snake :

- La **Pomme** (fruit classique) fait grandir le serpent + 1.
- La **Banane** fait grandir le serpent de + 1 et change sa direction aléatoirement.
- La **Coco** fait grandir le serpent de + 1 et téléporte le serpent à une position aléaoire.
- Le **Mauvais** fruit fait rétrécir le serpent de - 1.

### Prérequis

Avant de compiler et exécuter le projet, assurez-vous que les bibliothèques suivantes sont installées sur votre système :

- **SDL2**
- **SDL2_TTF**

 ### Installation des dépendances sous Linux :
 
 `sudo apt-get install libsdl2-dev libsdl2-ttf-dev`
 
 ### Installation des dépendances sous Windows et Mac :
 
 Pour les deux, vous pouvez télécharger et installer les bibliothèques SDL2 et SDL2_TTF à partir des sites officiels.
 
### Méthode de Compilation 

Le projet utilise un **Makefile** pour simplifier la compilation. Pour compiler le jeu, exécuter simplement avec la commande suivante dans votre terminal.
`make`
Si, compilation réussite alors un fichier exécutable nommé snake sera crée dans le répetoire courant.

### Exécution

Pour lancer le jeu après compilation, utilisez la commande suivante :
`./snake`

Un menu va s'ouvrir est vous permettra de choisir le mode de jeu avec 0 ou 1.

### Controles du Serpent

- **Flèche Haut** : Diriger le serpent vers le  haut.
- **Flèche Bas** : Diriger le serpent vers le bas.
- **Flèche Gauche** : Diriger le serpent vers la gauche.
- **Flèche Droite** : Diriger le serpent vers la droite.

### Condition de Victoire

Pour gagner, votre serpent doit remplir toutes les cases du terrain de jeu.

### Objectif du Jeu

Le but est de manger autant de fruits que possible pour faire grandir le serpent sans heurter les murs ou se mordre la queue. Certains fruits ont des facultés qui sera plus compliqué de gagné.

### Auteurs

- Mthloow - Développeur à CODA


