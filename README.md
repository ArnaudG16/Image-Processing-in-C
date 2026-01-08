# Projet PRIM : Traitement et Manipulation d'Images en C

Ce projet a été réalisé dans le cadre de ma formation à l'**ENSIIE** (Janvier 2025). Il s'agit d'un moteur de traitement d'images numériques conçu pour manipuler, transformer et analyser des fichiers aux formats **PGM** (niveaux de gris) et **PPM** (couleur).

## 📋 Description

L'objectif principal est d'implémenter des opérations bas niveau sur les pixels et des transformations géométriques sans utiliser de bibliothèques de traitement d'image externes. Le projet met l'accent sur la modularité du code et la gestion manuelle de la mémoire et des fichiers binaires.

## ✨ Fonctionnalités Principales

Le programme supporte les opérations suivantes :

* **Gestion des fichiers (I/O) :**
    * Lecture et écriture de fichiers binaires PGM (P5) et PPM (P6).
    * Gestion des entêtes et des commentaires (magic numbers).
* **Look-Up Tables (LUT) :**
    * Utilisation de tables de correspondance pour optimiser les calculs.
    * Fonctions de transfert : Inversion vidéo, normalisation dynamique, réduction de niveaux (discrétisation).
* **Arithmétique d'image :**
    * Multiplication, différence et mélange (blending) de deux images.
* **Ré-échantillonnage et Transformations :**
    * Redimensionnement d'images.
    * Algorithmes d'interpolation :
        * **Plus proche voisin** (Nearest Neighbor).
        * **Interpolation Bi-linéaire**.

## 🏗️ Architecture du Code

Le projet est structuré de manière modulaire pour séparer les responsabilités :

* `pictures.h/c` : Gestion de la structure `picture` (hauteur, largeur, canaux, données brutes), allocation mémoire et opérations directes sur les pixels.
* `lut.h/c` : Implémentation des structures et fonctions liées aux tables de correspondance (LUT).
* `filename.h/c` : Utilitaires pour la gestion et la génération automatique des noms de fichiers de sortie.

## 🛠️ Compétences Techniques

* **Langage :** C
* **Concepts :** Pointeurs, Structures, Allocation dynamique de mémoire (`malloc`), Manipulation de fichiers binaires.
* **Algorithmique :** Traitement du signal (interpolation), complexité algorithmique.

---
**Auteur :** Arnaud GRASSIAN
**École :** ENSIIE
