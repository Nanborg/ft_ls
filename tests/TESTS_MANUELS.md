# Tests manuels

Depuis la racine du projet, lancer les deux commandes de chaque bloc.
Utiliser la même locale et le même fuseau horaire :

```sh
export LC_ALL=C TZ=UTC
unset BLOCK_SIZE BLOCKSIZE LS_BLOCK_SIZE TIME_STYLE QUOTING_STYLE POSIXLY_CORRECT
```

Les comparaisons utilisent `ls -1` pour ne pas confondre les colonnes du terminal
avec une fonctionnalité obligatoire. Le script automatique redirige ses sorties :
il n'a pas besoin de cette option. Les compléments ci-dessous ciblent Bash sur
GNU/Linux ; Python 3 est facultatif pour les sockets et les nanosecondes.

Le script conserve les tests existants et ajoute les cas manquants :

```sh
sh tests/script.sh
```

`PASS` = stdout, diagnostics et statut identiques à la référence ; `FAIL` =
une différence à examiner ; `SKIP` = cas non exécuté faute de droits/outils.
Les diagnostics indépendants sont comparés sans imposer leur ordre.
La comparaison de stdout est stricte : un écart de padding peut être toléré par
le sujet, contrairement à une taille fausse, un mauvais tri ou un nom absent.
Un échec n'est donc pas automatiquement un échec à l'évaluation.

Chaque appel à ft_ls a un délai de 15 secondes, configurable avec
`FT_LS_TIMEOUT=30 sh tests/script.sh`. Ce délai protège les tests d'une boucle ;
ce n'est pas une limite de temps imposée par le sujet. Les résultats des échecs
sont sauvegardés dans le dossier `/tmp/ft_ls-failures.*` indiqué en fin de test,
avec stdout, stderr, diffs, arguments, dossier courant et codes de retour.
Les fixtures temporaires sont nettoyées : pour reproduire un cas ensuite,
utiliser la préparation manuelle ci-dessous.

Le script peut aussi être contrôlé contre la référence elle-même avec
`FT_LS_BIN=/bin/ls sh tests/script.sh` : tous les cas exécutés doivent passer.

## Base

### Dossier courant
```sh
./ft_ls
/bin/ls -1
```

### Fichier
```sh
./ft_ls Makefile
/bin/ls -1 Makefile
```

### Dossier
```sh
./ft_ls srcs
/bin/ls -1 srcs
```

## Options seules

### `-a` — fichiers caches
```sh
./ft_ls -a
/bin/ls -1 -a
```

### `-l` — format long
```sh
./ft_ls -l
/bin/ls -1 -l
```

### `-r` — ordre inverse
```sh
./ft_ls -r srcs
/bin/ls -1 -r srcs
```

### `-t` — tri par date
```sh
./ft_ls -t srcs
/bin/ls -1 -t srcs
```

### `-R` — récursivité
```sh
./ft_ls -R .
/bin/ls -1 -R .
```

## Combinaisons de deux options

### `-la`
```sh
./ft_ls -la
/bin/ls -1 -la
```

### `-lr`
```sh
./ft_ls -lr srcs
/bin/ls -1 -lr srcs
```

### `-lt`
```sh
./ft_ls -lt srcs
/bin/ls -1 -lt srcs
```

### `-lR`
```sh
./ft_ls -lR .
/bin/ls -1 -lR .
```

### `-ar`
```sh
./ft_ls -ar
/bin/ls -1 -ar
```

### `-at`
```sh
./ft_ls -at
/bin/ls -1 -at
```

### `-aR`
```sh
./ft_ls -aR .
/bin/ls -1 -aR .
```

### `-rt`
```sh
./ft_ls -rt srcs
/bin/ls -1 -rt srcs
```

### `-rR`
```sh
./ft_ls -rR .
/bin/ls -1 -rR .
```

### `-tR`
```sh
./ft_ls -tR .
/bin/ls -1 -tR .
```

## Combinaisons de trois options

### `-lar`
```sh
./ft_ls -lar
/bin/ls -1 -lar
```

### `-lat`
```sh
./ft_ls -lat
/bin/ls -1 -lat
```

### `-laR`
```sh
./ft_ls -laR .
/bin/ls -1 -laR .
```

### `-lrt`
```sh
./ft_ls -lrt srcs
/bin/ls -1 -lrt srcs
```

### `-lrR`
```sh
./ft_ls -lrR .
/bin/ls -1 -lrR .
```

### `-ltR`
```sh
./ft_ls -ltR .
/bin/ls -1 -ltR .
```

### `-art`
```sh
./ft_ls -art
/bin/ls -1 -art
```

### `-arR`
```sh
./ft_ls -arR .
/bin/ls -1 -arR .
```

### `-atR`
```sh
./ft_ls -atR .
/bin/ls -1 -atR .
```

### `-rtR`
```sh
./ft_ls -rtR .
/bin/ls -1 -rtR .
```

## Combinaisons de quatre et cinq options

### `-lart`
```sh
./ft_ls -lart
/bin/ls -1 -lart
```

### `-larR`
```sh
./ft_ls -larR .
/bin/ls -1 -larR .
```

### `-latR`
```sh
./ft_ls -latR .
/bin/ls -1 -latR .
```

### `-lrtR`
```sh
./ft_ls -lrtR .
/bin/ls -1 -lrtR .
```

### `-artR`
```sh
./ft_ls -artR .
/bin/ls -1 -artR .
```

### `-lartR`
```sh
./ft_ls -lartR .
/bin/ls -1 -lartR .
```

## Options séparées

### `-l -t`
```sh
./ft_ls -l -t srcs
/bin/ls -1 -l -t srcs
```

## Arguments multiples

### Plusieurs fichiers
```sh
./ft_ls srcs/main.c srcs/options.c
/bin/ls -1 srcs/main.c srcs/options.c
```

### Plusieurs dossiers
```sh
./ft_ls srcs includes
/bin/ls -1 srcs includes
```

### Fichiers et dossiers mélangés
```sh
./ft_ls srcs/main.c includes srcs/options.c
/bin/ls -1 srcs/main.c includes srcs/options.c
```

### Fichier, dossier, fichier avec `-r`
```sh
./ft_ls -r srcs/main.c includes srcs/options.c
/bin/ls -1 -r srcs/main.c includes srcs/options.c
```

### Fichier, dossier, fichier avec `-t`
```sh
./ft_ls -t srcs/main.c includes srcs/options.c
/bin/ls -1 -t srcs/main.c includes srcs/options.c
```

## Erreurs

### Chemin inexistant
```sh
./ft_ls chemin-inexistant
/bin/ls -1 chemin-inexistant
```

### Chemin inexistant et chemin valide
```sh
./ft_ls chemin-inexistant Makefile
/bin/ls -1 chemin-inexistant Makefile
```

### Option inconnue
```sh
./ft_ls -z
/bin/ls -1 -z
```

## Liens, permissions et appareils

### Liens, permissions spéciales et appareils
```sh
./ft_ls -l /dev
/bin/ls -1 -l /dev
```

### Appareil caractère — major/minor
```sh
./ft_ls -l /dev/null
/bin/ls -1 -l /dev/null
```


## Compléments — préparation des cas limites

Depuis la racine du projet, dans Bash, exécuter ce bloc une fois.
Les fichiers de test sont créés dans un nouveau dossier temporaire.

```bash
make
BIN="$PWD/ft_ls"
T=$(mktemp -d /tmp/ft_ls-tests.XXXXXX)
export LC_ALL=C TZ=UTC
unset BLOCK_SIZE BLOCKSIZE LS_BLOCK_SIZE TIME_STYLE QUOTING_STYLE POSIXLY_CORRECT
mkdir -p "$T/results" "$T/tree/sub/deep" "$T/tree/.hidden-dir"
mkdir -p "$T/empty" "$T/args/a_dir_old" "$T/args/z_dir_new"
mkdir -p "$T/permissions" "$T/dates" "$T/sizes" "$T/names"
mkdir -p "$T/read-only" "$T/no-read" "$T/blocked"

printf 'hello\n' > "$T/tree/alpha"
touch "$T/tree/zeta" "$T/tree/.hidden" "$T/tree/A" "$T/tree/a"
touch "$T/tree/sub/deep/child" "$T/tree/.hidden-dir/inside"
touch "$T/tree/file with spaces"
ln -s alpha "$T/tree/link-file"
ln -s sub "$T/tree/link-dir"
ln -s absent "$T/tree/broken-link"
ln -s link-file "$T/tree/link-chain"
ln -s self-link "$T/tree/self-link"
ln -s ../.. "$T/tree/sub/deep/link-parent"
ln -s cycle-b "$T/tree/cycle-a"
ln -s cycle-a "$T/tree/cycle-b"
ln "$T/tree/alpha" "$T/tree/hard-link"
mkfifo "$T/tree/fifo"

touch -t 202001010000 "$T/args/a_old"
touch -t 202101010000 "$T/args/z_new"
touch -t 202001010000 "$T/args/a_dir_old"
touch -t 202101010000 "$T/args/z_dir_new"

touch "$T/sizes/zero"
printf x > "$T/sizes/one"
truncate -s 2147483647 "$T/sizes/int-max"
truncate -s 2147483648 "$T/sizes/over-int"
truncate -s 3221225472 "$T/sizes/three-gib"
truncate -s 5368709120 "$T/sizes/five-gib"

for mode in 000 001 002 004 010 020 040 100 200 400 644 755 777 \
            4755 4644 2755 2644 1755 1644 7777; do
    touch "$T/permissions/mode-$mode"
    chmod "$mode" "$T/permissions/mode-$mode"
done
touch "$T/read-only/one" "$T/read-only/two"
touch "$T/no-read/inside" "$T/blocked/inside"
chmod 400 "$T/read-only"
chmod 100 "$T/no-read"
chmod 000 "$T/blocked"

for name in recent future-30m future-2h old-179 old-180 old-181 old-184 ancient; do
    touch "$T/dates/$name"
done
touch -d '1 hour ago' "$T/dates/recent"
touch -d '30 minutes' "$T/dates/future-30m"
touch -d '2 hours' "$T/dates/future-2h"
touch -d '179 days ago' "$T/dates/old-179"
touch -d '180 days ago' "$T/dates/old-180"
touch -d '181 days ago' "$T/dates/old-181"
touch -d '184 days ago' "$T/dates/old-184"
touch -t 197001020304 "$T/dates/ancient"

touch "$T/names/-" "$T/names/-a" "$T/names/--"
touch "$T/names/A" "$T/names/a" "$T/names/Z" "$T/names/z"
touch "$T/names/.hidden" "$T/names/..not-parent" "$T/names/_under"
touch "$T/names/with spaces" "$T/names/ leading" "$T/names/trailing "
touch "$T/names/quote'file" "$T/names/quote\"file"
touch "$T/names/"$'tab\tfile' "$T/names/"$'line\nfile'
long_name=$(printf '%0255d' 0)
touch "$T/names/$long_name"
printf 'Dossier de test : %s\n' "$T"
```

Les grands fichiers sont creux : leur taille logique est grande, sans écrire
plusieurs Gio de données. Les droits doivent être testés sans être root.

### Fonction de comparaison

Elle compare stdout, stderr et les codes de sortie, en conservant les dernières
sorties dans `$T/results`. Elle ne modifie aucun fichier du projet.

```bash
compare() {
    printf '\nTest :'
    printf ' <%s>' "$@"
    printf '\n'
    timeout -k 2 15s "$BIN" "$@" > "$T/results/actual.out" 2> "$T/results/actual.err"
    actual_status=$?
    /bin/ls "$@" > "$T/results/expected.out" 2> "$T/results/expected.err"
    expected_status=$?
    diff -u "$T/results/expected.out" "$T/results/actual.out"
    sed 's#/bin/ls#ls#g' "$T/results/expected.err" | sort > "$T/results/expected.norm.err"
    sed 's#/bin/ls#ls#g; s/^ft_ls:/ls:/' "$T/results/actual.err" | sort > "$T/results/actual.norm.err"
    diff -u "$T/results/expected.norm.err" "$T/results/actual.norm.err"
    printf 'Codes : ft_ls=%s ; ls=%s\n' "$actual_status" "$expected_status"
}
```

Pas de différence dans les `diff` et mêmes codes : le cas correspond à la
référence. Un code 124 côté ft_ls signifie que le délai de 15 secondes a expiré.
Un simple écart d'espacement n'a pas la même gravité qu'une entrée manquante.
Les préfixes dans une éventuelle ligne `Try ... --help` peuvent aussi différer.

## 3. Toutes les combinaisons des cinq options

Tester les 32 combinaisons sur un dossier rempli, un dossier vide, plusieurs
fichiers, plusieurs dossiers et un mélange. Cela vérifie aussi les interactions
entre options et les en-têtes/sauts de ligne.

```bash
for opt in '' l R a r t lR la lr lt Ra Rr Rt ar at rt \
           lRa lRr lRt lar lat lrt Rar Rat Rrt art \
           lRar lRat lRrt lart Rart lRart; do
    flags=()
    [ -z "$opt" ] || flags=("-$opt")
    compare "${flags[@]}" "$T/tree"
    compare "${flags[@]}" "$T/empty"
    compare "${flags[@]}" "$T/args/a_old" "$T/args/z_new"
    compare "${flags[@]}" "$T/args/a_dir_old" "$T/args/z_dir_new"
    compare "${flags[@]}" "$T/args/z_dir_new" "$T/args/a_old" \
        "$T/args/a_dir_old" "$T/args/z_new"
done
```

Attendu : `-t` donne les plus récents en premier ; `-tr` les plus anciens.
`-a` inclut `.` et `..` dans l'affichage, mais `-R` ne doit jamais y descendre.
Les dossiers cachés sont parcourus avec `-Ra`, pas avec `-R` seul.
Les liens rencontrés dans l'arborescence ne doivent pas provoquer de boucle.

## 4. Parsing et arguments

```bash
compare
compare -l -R -a -r -t "$T/tree"
compare -tarlR "$T/tree"
compare -llaaRRrrtt "$T/tree"
compare -- "$T/tree"
compare -l -- "$T/tree"
compare --
compare -z
compare -laz
compare -z "$T/absent"
compare ''
compare "$T/absent"
compare "$T/z-absent" "$T/a-absent"
compare "$T/absent" "$T/tree/alpha" "$T/tree"
compare "$T/tree/alpha/not-a-directory"
compare "$T/tree/alpha/"
compare "$T/tree/" "$T/tree/sub/../sub"
compare "$T/tree" "$T/tree"
compare "$T/tree/alpha" "$T/tree/alpha"
compare "$T/tree" -a
compare "$T/tree" -l -t
(cd "$T/names" && compare -- - -a --)
(cd "$T/names" && compare -l -- -a)
(cd "$T/names" && compare ./-a)
```

Vérifier que `--` arrête le parsing, que les doublons ne disparaissent pas,
que les chemins valides restent traités malgré les erreurs, et que les erreurs
sont écrites sur stderr. Les options après les chemins suivent ici GNU ls.
`--help`, `--version` et les autres options non demandées ne sont pas requis.

## 5. Liens symboliques et liens physiques

```bash
for opt in '' l R lR; do
    flags=()
    [ -z "$opt" ] || flags=("-$opt")
    for name in link-file link-dir broken-link link-chain self-link cycle-a; do
        compare "${flags[@]}" "$T/tree/$name"
    done
done
compare -l "$T/tree/link-dir/"
compare -l "$T/tree/link-file" "$T/tree/link-dir" "$T/tree/sub"
compare -l "$T/tree/alpha" "$T/tree/hard-link"
compare -laR "$T/tree"
```

Attendu : `-l link-dir` décrit le lien ; la barre finale peut imposer la
résolution vers un dossier, à comparer au ls système. Les liens cassés existent
en tant que liens. Les deux liens physiques partagent le nombre de liens de
l'inode ; ils ne s'affichent pas avec une flèche.

## 6. Droits et erreurs de permissions

```bash
compare -l "$T/permissions"
compare "$T/read-only"
compare -l "$T/read-only"
compare "$T/no-read"
compare "$T/no-read/inside"
compare "$T/blocked"
compare -l "$T/blocked"
compare "$T/blocked/inside"
compare "$T/blocked" "$T/tree/alpha" "$T/tree"
mkdir -p "$T/recurse/accessible" "$T/recurse/refuse"
touch "$T/recurse/accessible/child" "$T/recurse/refuse/child"
chmod 000 "$T/recurse/refuse"
compare -R "$T/recurse"
compare -laR "$T/recurse"
```

Vérifier les neuf bits rwx, `s/S` pour setuid et setgid, `t/T` pour sticky.
Un fichier mode 000 peut être listé : on lit ses métadonnées, pas son contenu.
Une erreur dans un sous-dossier ne doit pas empêcher de traiter les autres.
Les tests de permissions sont non significatifs avec les privilèges root.

## 7. Tailles, blocs, types et alignement

```bash
compare -l "$T/sizes"
compare -l "$T/sizes/three-gib"
compare -l "$T/sizes/zero" "$T/sizes/five-gib"
compare -la "$T/empty"
compare -l "$T/empty"
compare -l "$T/tree/fifo"
compare -l /dev/null /dev/zero
compare -l /dev
```

Vérifier : taille exacte, total basé sur les blocs alloués plutôt que la taille
logique, `total 0` dans un dossier vide en `-l`, lettre de type et major/minor
pour les périphériques. Aucun total de dossier ne doit apparaître pour de
simples arguments fichiers. Les fichiers creux ne doivent pas gonfler le total
comme si tous leurs octets étaient réellement alloués.

Socket Unix, si Python 3 est disponible :

```bash
python3 - "$T/tree/socket" <<'PY'
import socket, sys
try:
    with socket.socket(socket.AF_UNIX) as sock:
        sock.bind(sys.argv[1])
except OSError as error:
    print(f"Socket indisponible : {error}", file=sys.stderr)
    sys.exit(1)
PY
[ ! -S "$T/tree/socket" ] || compare -l "$T/tree/socket"
```

Si la création de socket échoue, ce cas est non exécuté, pas réussi.

Pour un périphérique bloc, utiliser un fichier bloc existant accessible sur
la machine. Ne pas créer de périphérique ni changer les droits de `/dev`.
Les tests de UID/GID sans nom ou supérieurs à INT_MAX nécessitent des fichiers
appropriés ou un environnement isolé avec droits suffisants : vérifier leur
affichage numérique sans modifier les propriétaires du projet.

## 8. Dates, égalités et nanosecondes

```bash
compare -l "$T/dates"
compare -lt "$T/dates"
compare -ltr "$T/dates"
touch -t 202001010000 "$T/args/same-a" "$T/args/same-z"
compare -t "$T/args/same-z" "$T/args/same-a"
compare -tr "$T/args/same-z" "$T/args/same-a"
```

Attendu : à date strictement identique, départager par nom en locale C ; `-r`
inverse aussi ce départage. Les seuils de dates doivent reproduire le ls local.
Les dates relatives évitent qu'un test « récent » devienne ancien avec le temps.

Pour tester les nanosecondes et ne pas confondre mtime et atime :

```bash
mkdir -p "$T/nano"
python3 - "$T/nano" <<'PY'
import os, pathlib, sys
p = pathlib.Path(sys.argv[1])
for name, atime, mtime in [
    ('a_old', 1700000000900000000, 1700000000100000000),
    ('z_new', 1700000000100000000, 1700000000900000000),
]:
    (p / name).touch()
    os.utime(p / name, ns=(atime, mtime))
for item in sorted(p.iterdir()):
    print(item.name, item.stat().st_mtime_ns)
PY
compare -t "$T/nano"
compare -tr "$T/nano"
compare -t "$T/nano/a_old" "$T/nano/z_new"
```

Vérifier que le système de fichiers a conservé les nanosecondes affichées.
`z_new` doit précéder `a_old` avec `-t`, même si leurs secondes sont identiques
et si leurs dates d'accès donnent l'ordre contraire.

## 9. Noms et chemins limites

```bash
compare "$T/names"
compare -la "$T/names"
compare -r "$T/names"
compare -laR "$T/names"
compare -l "$T/names/with spaces" "$T/names/ leading" "$T/names/trailing "
long_path="$T/long-path"
component=$(printf '%0120d' 0)
for i in 1 2 3 4 5 6 7 8; do
    long_path="$long_path/$component"
    mkdir -p "$long_path"
done
touch "$long_path/leaf"
compare -l "$long_path"
compare -R "$T/long-path"
```

Vérifier qu'aucun nom n'est tronqué, que les espaces appartiennent au nom, et
que `..not-parent` n'est pas exclu comme `..`. Les noms avec tabulations ou
retours à la ligne rendent l'affichage ambigu : inspecter les sorties avec
`cat -vet "$T/results/actual.out"`. Comparer les sorties redirigées comme ici,
car le ls système peut afficher différemment dans un terminal.

## 10. Robustesse et mémoire : vérifications complémentaires

Ces contrôles complètent les comparaisons déterministes ; ils ne sont pas
tous automatisables avec un simple diff.

- Exécuter `valgrind --leak-check=full --show-leak-kinds=all "$BIN" -laR "$T/tree"`.
- Refaire Valgrind avec un chemin absent, un lien cassé et un dossier interdit.
- Distinguer les allocations du projet des bibliothèques système. Pendant
  l'audit, `/bin/ls` présentait les mêmes quantités perdues dans NSS/SASL ; cela
  ne dispense pas de contrôler les allocations propres au projet.
- Tester les échecs successifs de malloc/calloc/strdup avec un injecteur de
  pannes : absence de crash, double free et fuite ; statut d'erreur cohérent.
- Injecter un échec de `readdir`, `lstat` et `readlink` : vérifier diagnostics,
  nettoyage, conservation des autres entrées et propagation des erreurs.
- Supprimer une entrée pendant une lecture : pas de crash ; les erreurs doivent
  être traitées. Un diff exact n'est pas fiable sur une arborescence qui change.
- Tester une date extrême si le système de fichiers l'accepte : aucun accès à
  un pointeur NULL si la conversion de date échoue.
- Tester un dossier de plusieurs milliers d'entrées et une arborescence profonde,
  en imposant un délai. Mesurer le temps ; ne pas assimiler une limite arbitraire
  de 15 secondes à un seuil officiel de l'école.
- Vérifier que `-R` n'accumule pas les descripteurs de dossiers ouverts.

## 11. Compilation et rendu

Depuis la racine du projet, sans avoir besoin de toucher aux sources :

```bash
make
make
norminette includes srcs libft
git status --short
```

- Le deuxième `make` ne doit ni recompiler ni relinker inutilement.
- Vérifier aussi `make clean`, `make fclean`, `make re` et une compilation
  parallèle `make -j4` ; ces commandes retirent/recréent les artefacts de build.
- Dans une copie temporaire du projet, vérifier qu'une modification d'un `.c`,
  d'un header et d'un fichier de libft reconstruit ce qui dépend du changement.
- Vérifier que le dépôt rendu contient bien tous les `.c`, headers, Makefiles
  et la libft nécessaires : les fichiers présents seulement chez toi ne suffisent pas.
- Savoir expliquer chaque partie du code et indiquer honnêtement l'aide de l'IA,
  comme le demande le sujet.

Le sujet autorise les fonctions libc. Il n'impose pas `ft_printf`. Les colonnes
sans `-l`, couleurs, ACL, attributs étendus et options supplémentaires sont
hors partie obligatoire. Les petits écarts de padding sont tolérés ; les
tailles fausses, noms manquants ou mauvais tris ne sont pas du padding.


## Nettoyage des fixtures manuelles

Après les tests, restaurer les droits pour pouvoir supprimer le dossier créé.
Ne lancer ce bloc que dans le terminal où la préparation a défini `T`.

```bash
if [[ -n "${T:-}" && "$T" == /tmp/ft_ls-tests.* && -d "$T" ]]; then
    chmod -R u+rwx -- "$T"
    rm -rf -- "$T"
fi
```
