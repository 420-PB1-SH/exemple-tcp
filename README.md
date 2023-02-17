# Exemple de programmation TCP avec SFML

Ce dépôt contient un exemple d'un client et un serveur s'échangeant des données
en TCP via le module réseau de SFML. Il s'agit d'un exemple de type "écho": tous
les messages envoyés par le client sont renvoyés par le serveur.

La solution Visual Studio 2022 comprend deux projets: un pour le client et un
pour le serveur.

## Pour démarrer les deux projets en même temps

1. Ouvrir les propriétés de la solution 
2. Aller dans l'onglet `Propriétés communes > Projet de démarrage` 
3. Sélectionner `Plusieurs projets de démarrage` 
4. Sélectionner l'action `Démarrer` pour `Client` et `Server` 
5. Cliquer sur `Appliquer` puis `OK` 
6. Cliquer sur le bouton `Démarrer` de la barre d'outils

## Références utiles

* [Tutoriel du module réseau de SFML](https://www.sfml-dev.org/tutorials/2.5/index-fr.php#module-rceseau)
* [Documentation des classes du module réseau de SFML](https://www.sfml-dev.org/documentation/2.5.1-fr/group__network.php)
