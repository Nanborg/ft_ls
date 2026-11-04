# Tests manuels

Lancer les deux commandes de chaque bloc et comparer les sorties.

## Base

### Dossier courant
```sh
./ft_ls
ls
```

### Fichier
```sh
./ft_ls Makefile
ls Makefile
```

### Dossier
```sh
./ft_ls srcs
ls srcs
```

## Options seules

### `-a` — fichiers caches
```sh
./ft_ls -a
ls -a
```

### `-l` — format long
```sh
./ft_ls -l
ls -l
```

### `-r` — ordre inverse
```sh
./ft_ls -r srcs
ls -r srcs
```

### `-t` — tri par date
```sh
./ft_ls -t srcs
ls -t srcs
```

### `-R` — récursivité
```sh
./ft_ls -R .
ls -R .
```

## Combinaisons de deux options

### `-la`
```sh
./ft_ls -la
ls -la
```

### `-lr`
```sh
./ft_ls -lr srcs
ls -lr srcs
```

### `-lt`
```sh
./ft_ls -lt srcs
ls -lt srcs
```

### `-lR`
```sh
./ft_ls -lR .
ls -lR .
```

### `-ar`
```sh
./ft_ls -ar
ls -ar
```

### `-at`
```sh
./ft_ls -at
ls -at
```

### `-aR`
```sh
./ft_ls -aR .
ls -aR .
```

### `-rt`
```sh
./ft_ls -rt srcs
ls -rt srcs
```

### `-rR`
```sh
./ft_ls -rR .
ls -rR .
```

### `-tR`
```sh
./ft_ls -tR .
ls -tR .
```

## Combinaisons de trois options

### `-lar`
```sh
./ft_ls -lar
ls -lar
```

### `-lat`
```sh
./ft_ls -lat
ls -lat
```

### `-laR`
```sh
./ft_ls -laR .
ls -laR .
```

### `-lrt`
```sh
./ft_ls -lrt srcs
ls -lrt srcs
```

### `-lrR`
```sh
./ft_ls -lrR .
ls -lrR .
```

### `-ltR`
```sh
./ft_ls -ltR .
ls -ltR .
```

### `-art`
```sh
./ft_ls -art
ls -art
```

### `-arR`
```sh
./ft_ls -arR .
ls -arR .
```

### `-atR`
```sh
./ft_ls -atR .
ls -atR .
```

### `-rtR`
```sh
./ft_ls -rtR .
ls -rtR .
```

## Combinaisons de quatre et cinq options

### `-lart`
```sh
./ft_ls -lart
ls -lart
```

### `-larR`
```sh
./ft_ls -larR .
ls -larR .
```

### `-latR`
```sh
./ft_ls -latR .
ls -latR .
```

### `-lrtR`
```sh
./ft_ls -lrtR .
ls -lrtR .
```

### `-artR`
```sh
./ft_ls -artR .
ls -artR .
```

### `-lartR`
```sh
./ft_ls -lartR .
ls -lartR .
```

## Options séparées

### `-l -t`
```sh
./ft_ls -l -t srcs
ls -l -t srcs
```

## Arguments multiples

### Plusieurs fichiers
```sh
./ft_ls srcs/main.c srcs/options.c
ls srcs/main.c srcs/options.c
```

### Plusieurs dossiers
```sh
./ft_ls srcs includes
ls srcs includes
```

### Fichiers et dossiers mélangés
```sh
./ft_ls srcs/main.c includes srcs/options.c
ls srcs/main.c includes srcs/options.c
```

### Fichier, dossier, fichier avec `-r`
```sh
./ft_ls -r srcs/main.c includes srcs/options.c
ls -r srcs/main.c includes srcs/options.c
```

### Fichier, dossier, fichier avec `-t`
```sh
./ft_ls -t srcs/main.c includes srcs/options.c
ls -t srcs/main.c includes srcs/options.c
```

## Erreurs

### Chemin inexistant
```sh
./ft_ls chemin-inexistant
ls chemin-inexistant
```

### Chemin inexistant et chemin valide
```sh
./ft_ls chemin-inexistant Makefile
ls chemin-inexistant Makefile
```

### Option inconnue
```sh
./ft_ls -z
ls -z
```

## Liens, permissions et appareils

### Liens, permissions spéciales et appareils
```sh
./ft_ls -l /dev
ls -l /dev
```

### Appareil caractère — major/minor
```sh
./ft_ls -l /dev/null
ls -l /dev/null
```

## Options et arguments particuliers

### Toutes les options séparées
```sh
./ft_ls -l -a -r -t -R srcs
ls -l -a -r -t -R srcs
```

### Options répétées
```sh
./ft_ls -llaa srcs
ls -llaa srcs
```

### Fin des options avec `--`
```sh
./ft_ls -- Makefile
ls -- Makefile
```

### Même fichier deux fois
```sh
./ft_ls Makefile Makefile
ls Makefile Makefile
```

### Même dossier deux fois
```sh
./ft_ls srcs srcs
ls srcs srcs
```

### Argument vide
```sh
./ft_ls ''
ls ''
```

### Chemin traversant un fichier
```sh
./ft_ls Makefile/abc
ls Makefile/abc
```

### Plusieurs chemins inexistants et un fichier valide
```sh
./ft_ls absent1 Makefile absent2
ls absent1 Makefile absent2
```

### Tri par date de plusieurs fichiers
```sh
./ft_ls -t Makefile srcs/main.c srcs/options.c
ls -t Makefile srcs/main.c srcs/options.c
```

### Tri inverse par date de plusieurs fichiers
```sh
./ft_ls -tr Makefile srcs/main.c srcs/options.c
ls -tr Makefile srcs/main.c srcs/options.c
```

### Tri par date de plusieurs dossiers
```sh
./ft_ls -t srcs includes libft
ls -t srcs includes libft
```

### Format long de plusieurs fichiers
```sh
./ft_ls -l Makefile srcs/main.c srcs/options.c
ls -l Makefile srcs/main.c srcs/options.c
```

### Chemin avec une barre finale
```sh
./ft_ls -l srcs/
ls -l srcs/
```

## Préparation des tests supplémentaires

À exécuter une fois depuis la racine du projet.

```sh
mkdir test_vide test_interdit
touch 'test avec espaces' test_sans_droits
ln -s Makefile test_lien_fichier
ln -s srcs test_lien_dossier
ln -s cible_absente test_lien_casse
chmod 000 test_interdit test_sans_droits
```

## Tests supplémentaires

### Dossier vide
```sh
./ft_ls -l test_vide
ls -l test_vide
```

### Lien vers un fichier
```sh
./ft_ls -l test_lien_fichier
ls -l test_lien_fichier
```

### Lien vers un dossier avec `-l`
```sh
./ft_ls -l test_lien_dossier
ls -l test_lien_dossier
```

### Lien vers un dossier sans `-l`
```sh
./ft_ls test_lien_dossier
ls test_lien_dossier
```

### Lien cassé
```sh
./ft_ls -l test_lien_casse
ls -l test_lien_casse
```

### Dossier sans permission
```sh
./ft_ls test_interdit
ls test_interdit
```

### Nom avec des espaces
```sh
./ft_ls -l 'test avec espaces'
ls -l 'test avec espaces'
```

### Fichier sans permission
```sh
./ft_ls -l test_sans_droits
ls -l test_sans_droits
```

## Nettoyage des tests supplémentaires

À exécuter après les tests.

```sh
chmod 755 test_interdit
chmod 644 test_sans_droits
rmdir test_vide test_interdit
rm test_lien_fichier test_lien_dossier test_lien_casse
rm 'test avec espaces' test_sans_droits
```
