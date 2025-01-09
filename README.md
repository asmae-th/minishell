# Minishell

## Introduction

Minishell est un projet réalisé dans le cadre du cursus de l'école 42. Il s'agit d'implémenter un interpréteur de commandes minimaliste, inspiré des grands shell comme **bash** ou **zsh**. Ce projet nous permet de comprendre et de recréer les bases du fonctionnement d'un terminal interactif sous UNIX.

L'objectif est de développer un shell capable d'exécuter des commandes simples, de gérer les redirections et les pipelines, tout en respectant les principes fondamentaux des systèmes UNIX.

## Fonctionnalités

Voici les fonctionnalités que nous avons implémentées dans Minishell :

- **Prompt interactif** : affiche un prompt pour saisir des commandes.
- **Exécution des commandes système** : support des chemins relatifs et absolus.
- **Commandes intégrées (builtins)** :
  - `echo` : affiche du texte dans le terminal.
  - `cd` : change de répertoire.
  - `pwd` : affiche le répertoire courant.
  - `export` : ajoute ou modifie des variables d'environnement.
  - `unset` : supprime des variables d'environnement.
  - `env` : affiche toutes les variables d'environnement.
  - `exit` : ferme le shell.
- **Gestion des redirections** (`<`, `>`, `>>`) et des pipelines (`|`).
- **Gestion des variables d'environnement**.
- **Gestion des signaux** (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`).
- **Messages d'erreur clairs** pour une meilleure expérience utilisateur.

## Objectifs pédagogiques

Ce projet nous a permis de :

- Comprendre les appels système comme `fork`, `execve`, et `wait`.
- Implémenter un parsing robuste pour les commandes utilisateur.
- Gérer les processus et les redirections de manière efficace.
- Travailler sur un projet en équipe, avec une bonne structure de code.

## Installation

Pour essayer notre Minishell, suivez ces étapes :

1. Clonez le dépôt :
   ```bash
   git clone https://github.com/votre-repo/minishell.git

2. Compilez le projet avec make :
    ```bash
    cd minishell
    make
3. Lancez le shell :
    ```bash
    ./minishell

## Conclusion

Minishell est une opportunité d'explorer les bases des systèmes UNIX et de recréer un outil indispensable : un interpréteur de commandes. Ce projet nous a permis de consolider nos compétences techniques tout en relevant des défis complexes.

Si vous avez des questions, des suggestions ou souhaitez contribuer, n'hésitez pas à ouvrir une issue ou une pull request. Merci de votre intérêt pour notre projet !

