# Norme 42 - Règles de Code

## Règles Principales

### 1. Structure des Fichiers
- **Maximum 5 fonctions par fichier**
- Chaque fichier doit avoir un header avec les informations requises
- Pas de fichiers vides

### 2. Fonctions
- **Maximum 25 lignes par fonction**
  - Les accolades `{` et `}` comptent comme des lignes
  - Une ligne vide compte comme une ligne
- **Maximum 4 paramètres par fonction**
- Les fonctions doivent être séparées par une ligne vide
- Pas de fonction dans une fonction (nested functions interdites)

### 3. Variables
- **Maximum 4 variables par fonction**
  - Toutes les variables doivent être déclarées au début de la fonction
  - Une seule déclaration par ligne
- Noms de variables en snake_case (minuscules avec underscores)

### 4. Lignes et Colonnes
- **Maximum 80 colonnes par ligne**
- Pas de lignes vides multiples (max 1 ligne vide consécutive)
- Chaque fichier doit se terminer par un retour à la ligne

### 5. Structures de Contrôle
- Les accolades `{` doivent être sur la même ligne que la condition/boucle
- Exception: les fonctions où `{` est sur une nouvelle ligne

```c
// Correct
if (condition)
{
    // code
}

// Correct pour structures de contrôle
while (condition) {
    // code
}
```

### 6. Indentation et Espaces
- Indentation avec des **tabulations** uniquement
- Pas d'espaces pour l'indentation
- Un espace après les mots-clés (if, while, for, etc.)
- Pas d'espace après le nom de fonction avant les parenthèses

### 7. Déclarations
- Une déclaration par ligne
- Alignement des déclarations encouragé mais pas obligatoire

### 8. Opérateurs
- Espaces autour des opérateurs binaires: `a + b`, `a == b`
- Pas d'espace pour les opérateurs unaires: `!a`, `*ptr`, `&var`

### 9. Pointeurs
- L'astérisque `*` doit être attaché au nom de la variable: `int *ptr`

### 10. Structures et Types
- Structures, unions, enums en typedef
- Noms en snake_case avec suffix `_t`: `t_player`, `t_map`

### 11. Macros et Defines
- Noms en MAJUSCULES avec underscores: `MAX_VALUE`
- Pas de macros complexes (préférer les fonctions)

### 12. Headers
- Protection contre les inclusions multiples obligatoire:
```c
#ifndef HEADER_H
# define HEADER_H

// contenu

#endif
```

### 13. Fonctions Interdites
- Pas de variables globales (sauf cas très spécifiques autorisés)
- Pas de `for` dans certains projets (vérifier le sujet)
- Utiliser les fonctions autorisées uniquement

### 14. Includes
- Includes système en premier: `#include <stdio.h>`
- Puis includes locaux: `#include "header.h"`

### 15. Commentaires
- Commentaires en `/* */` uniquement
- Pas de commentaires `//` (C99)
- Pas de commentaires inutiles

## Checklist par Fichier

- [ ] Maximum 5 fonctions
- [ ] Chaque fonction ≤ 25 lignes
- [ ] Chaque fonction ≤ 4 paramètres
- [ ] Chaque fonction ≤ 4 variables
- [ ] Maximum 80 colonnes par ligne
- [ ] Indentation avec tabulations
- [ ] Header avec protection
- [ ] Pas de variables globales
- [ ] Noms en snake_case
- [ ] Fichier termine par newline

## Outils de Vérification

```bash
# Norminette (outil officiel 42)
norminette fichier.c
norminette *.c *.h

# Vérifier tout le projet
norminette src/ includes/
```

## Exemples Conformes

```c
/* Exemple de fonction conforme */
int	calculate_distance(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	distance;

	dx = x2 - x1;
	dy = y2 - y1;
	distance = dx * dx + dy * dy;
	return (distance);
}
```

## Sanctions
- Un seul warning/error = 0 au projet
- Vérifier avec norminette avant chaque push
