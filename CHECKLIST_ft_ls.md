# ft_ls — Checklist d'évaluation

Cocher `[x]` uniquement après validation. Comparer avec `/bin/ls` (hors ACL, attributs étendus et format en colonnes, réservés aux bonus).

## 1. OBLIGATOIRE

### Préliminaires — éliminatoires
- [ ] Dépôt Git correct (propriétaire, projet, aucun alias trompeur).
- [ ] `author` présent.
- [ ] Norme respectée.
- [ ] Aucune fonction interdite.
- [ ] Makefile présent : `all`, `clean`, `fclean`, `re` fonctionnels.
- [ ] Aucune fuite mémoire.

> Un seul échec ci-dessus : évaluation notée 0, arrêter la notation.

### Tests de base — /5
- [ ] `./ft_ls` identique à `ls` (+1).
- [ ] `./ft_ls -a` identique à `ls -a` (+1).
- [ ] `./ft_ls -l` : informations correctes (+2 ; padding différent accepté).
- [ ] Liens symboliques affichés correctement (+1).
- [ ] Pour les tests ci-dessus : essayer sans argument, avec un fichier, puis avec un dossier.

### Tests de base ++ — /5
- [ ] `./ft_ls -r` (+1).
- [ ] `./ft_ls -t` (+1).
- [ ] `./ft_ls -r fichier1 dossier1 fichier2` (+1).
- [ ] `./ft_ls -t fichier1 dossier1 fichier2` (+1).
- [ ] Bits setuid, setgid et sticky correctement affichés (+1).

### Tests intermédiaires — /5
- [ ] `./ft_ls -R` : parcours récursif correct (+2).
- [ ] Options séparées et groupées : `-l -t`, `-lt` (+2).
- [ ] Affichage correct avec plusieurs options combinées (+1).

### Gestion des erreurs — /5
- [ ] Fichier ou dossier inexistant : erreur correcte (+1).
- [ ] Fichier ou dossier inaccessible : erreur correcte (+1).
- [ ] Option inconnue ou non gérée : erreur correcte (+3).

### Bilan obligatoire
- [ ] Tous les préliminaires validés.
- [ ] Tous les tests obligatoires validés.
- [ ] Aucun défaut bloquant.

## 2. BONUS

> À évaluer uniquement si la partie obligatoire est complète et sans défaut.

### ACL / attributs
- [ ] Affichage des ACL implémenté.
- [ ] Affichage des attributs étendus implémenté.

### Affichage en colonnes
- [ ] Affichage en colonnes implémenté et correct.

### Vitesse — /5
- [ ] Comparer `time /bin/ls -lR /` et `time ./ft_ls -lR /` dans des conditions similaires.
- [ ] Note vitesse : ___ / 5 (0 = très lent ; 5 = aussi rapide).

### Options supplémentaires — /5
- [ ] Lister les options supplémentaires : ____________________
- [ ] Tester chaque option supplémentaire à 100 %.
- [ ] Note options : ___ / 5 (1 point par option totalement fonctionnelle).

## Résultat
- Tests de base : ___ / 5
- Tests de base ++ : ___ / 5
- Tests intermédiaires : ___ / 5
- Gestion des erreurs : ___ / 5
- Total obligatoire : ___ / 20
- Bonus vitesse : ___ / 5
- Bonus options : ___ / 5
