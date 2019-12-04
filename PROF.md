
EXOS
===========
1: OK

2: OK

3: OK

4: OK

5: OK

6: OK

Gestion des collisions. Très bien d'avoir généré le monde ! Gestion du brouillard, dommage qu'il ne cache pas l'apparition des blocs.

Dommage aussi que le pitch de caméra ne soit pas bloqué.

Présence de la lumière.

Par contre, les performances sont assez basses sur mon PC portable.

7: OK

8: OK

Joli rendu mais l'angle de la caméra ne le met pas en avant. Les réglages auraient pu être modifier pour rendre le jeu plus "amusant".

Le score est affiché.

Bien d'avoir subdivisé les blocs ! Comme dit dans les commentaires, il est vrai que la subdivision en Y pourrait être limité.

RÉSUMÉ
===========
Très bon travail. Vous êtes allé au delà des attentes du projet en terme de programmation. Par contre attention au résultat final, le stack manque de polish.

CODE REVIEW
===========

Beaucoup de fonctions dans les .h alors que ce n'est nécessaire.

Bonne idée d'avoir utilisé un tableau de bits pour l'affichage des digits.

Par contre pourquoi avoir fait :
```c++
digitLines.letter = 0b11101110 & 0b11111111;
// Au lieu de
digitLines.letter = 0b11101110;/
// ?
```

Vous êtes allé chercher des techniques (timeline, std::functions) par vous-même. C'est très bien.

DIVERS
===========
README présents.

