# ft_ls : problèmes repérés et tests à ajouter

Basé sur le sujet version 4.0 du dépôt et les vérifications du 2 novembre 2026.
Ce document complète les tests existants. Aucun code C ni script existant n'a
été modifié pour le créer. Les commandes de préparation ci-dessous ciblent
Linux avec Bash et les outils GNU.

Cette liste couvre les exigences et les principaux cas limites identifiés ;
aucune liste finie de tests ne garantit l'absence de tout bug.

## 1. Ce qui est faux ou incomplet dans le code actuel

### Bugs confirmés par comparaison avec le ls Linux

| Problème | Emplacement | Comportement actuel | Comportement attendu |
| --- | --- | --- | --- |
| `-t` sur plusieurs arguments | `srcs/sort_arguments.c`, `ft_arg_must_swap` | Trie uniquement par nom ; `-tr` est donc faux aussi | Trier les fichiers entre eux et les dossiers entre eux par date, puis inverser avec `-r` |
| Lien vers un dossier passé avec `-l` | `srcs/arguments_files.c`, `ft_is_dir` | `stat` suit le lien et le programme affiche le contenu du dossier | Afficher les métadonnées du lien et `-> cible` |
| Taille supérieure à INT_MAX | `srcs/output_long.c`, `ft_print_size` | `ft_putnbr_fd(int)` tronque `st_size` ; 3 Gio deviennent `-1073741824` | Afficher `3221225472` avec une conversion adaptée au type |
| Dossier lisible sans droit de traversée | `srcs/directory.c`, `ft_read_directory` | L'échec de `lstat` supprime toute la liste, sans diagnostic | Sans `-l`, garder les noms disponibles ; avec `-l`, signaler les erreurs et garder les informations disponibles comme `ls` |
| Dates futures proches | `srcs/output_long.c`, `ft_print_date` | Garde HH:MM jusqu'à une heure dans le futur | Le ls Linux testé affiche l'année pour une date dans 30 minutes |
| Limite des dates anciennes | Même fonction | Assimile six mois à 180 jours | Reproduire le seuil du ls de référence ; le test à 181 jours révèle une différence |
| Option après un chemin | `srcs/options.c`, `ft_parse_options` | `dossier -a` cherche un fichier nommé `-a` | GNU ls accepte cette position ; à comparer au système de l'évaluation |

Ne pas remplacer aveuglément tous les `stat` par `lstat` : les liens passés
en arguments sans `-l` peuvent légitimement conduire à afficher leur dossier cible.

### Défauts visibles dans le code, à tester par injection de panne

- `ft_print_files` ignore le retour de `ft_print_file` : un échec d'allocation
  ou de métadonnées peut laisser un code de sortie de succès.
- `ft_read_directory` ne distingue pas une fin normale de `readdir` d'une
  erreur de lecture. Il faut vérifier `errno` avec une gestion adaptée.
- Les erreurs de `ft_fill_entry` et certaines erreurs d'allocation n'ont pas
  de diagnostic ; une erreur sur une entrée fait abandonner tout le dossier.
- `ft_print_link` ignore silencieusement un échec de `readlink`.
- Le retour de `ctime` n'est pas vérifié avant d'utiliser le pointeur : tester
  les dates extrêmes si le système de fichiers les autorise.
- Les conversions vers `int` concernent aussi les UID/GID numériques, le nombre
  de liens et le total des blocs. Une valeur trop grande peut être tronquée.

Ces observations ne signifient pas qu'un crash ou une fuite a été reproduit
dans chacun de ces cas.

### Différences secondaires et limites

- Plusieurs fichiers en arguments sont imprimés séparément : les colonnes de
  `-l` ne partagent pas les mêmes largeurs. Le sujet tolère les petits écarts
  d'espacement, mais aucune information ne doit manquer.
- Le tri et les ajouts en fin de liste par parcours coûtent O(n²). À mesurer
  sur un gros dossier ; ce n'est pas une option obligatoire manquante.
- `sys/sysmacros.h` et `st_mtim` ciblent Linux : recompiler sur la machine
  d'évaluation si elle utilise un autre système.
- Le README parle encore d'un squelette : description à actualiser.

## 2. Préparation des tests manuels

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
    timeout 15s "$BIN" "$@" > "$T/results/actual.out" 2> "$T/results/actual.err"
    actual_status=$?
    /bin/ls "$@" > "$T/results/expected.out" 2> "$T/results/expected.err"
    expected_status=$?
    diff -u "$T/results/expected.out" "$T/results/actual.out"
    sed 's#^/bin/ls:#ls:#' "$T/results/expected.err" > "$T/results/expected.norm.err"
    sed 's#^ft_ls:#ls:#' "$T/results/actual.err" > "$T/results/actual.norm.err"
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
sock = socket.socket(socket.AF_UNIX)
sock.bind(sys.argv[1])
sock.close()
PY
compare -l "$T/tree/socket"
```

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

## 12. Comment compléter le script existant plus tard

Conserver sa fonction `check_case` et ses tests actuels. Ajouter les nouvelles
fixtures dans son dossier temporaire, puis les cas ci-dessus sous cette forme :

```bash
# Exemple : remplacer les chemins par ceux des nouvelles fixtures du script.
check_case "-t trie aussi les arguments fichiers" -t "$T/args/a_old" "$T/args/z_new"
check_case "-l affiche le lien vers un dossier" -l "$T/tree/link-dir"
check_case "taille au-dessus de INT_MAX" -l "$T/sizes/over-int"
check_case "date future proche" -l "$T/dates/future-30m"
check_case "limite de date a 181 jours" -l "$T/dates/old-181"
check_case "dossier lisible sans traversee" "$T/read-only"
```

Le script actuel est en `/bin/sh` : les tableaux Bash `flags=()` de ce guide
ne peuvent pas y être copiés tels quels. Pour les combinaisons, utiliser :

```sh
if [ -z "$opt" ]; then
    check_case "sans option" "$fixture/tree"
else
    check_case "combinaison -$opt" "-$opt" "$fixture/tree"
fi
```

Ajouter un délai pour les tests récursifs, conserver les sorties des échecs,
et distinguer les tests non exécutés faute de droits/outils des tests réussis.
Comparer stdout, stderr et le statut, comme le fait déjà le script.
Le test `-t` existant peut passer par hasard quand ordre alphabétique et ordre
chronologique coïncident : les noms `a_old` et `z_new` évitent ce faux positif.

## 13. Nettoyage des fixtures manuelles

Après les tests, restaurer les droits pour pouvoir supprimer le dossier créé.
Ne lancer ce bloc que dans le terminal où la préparation a défini `T`.

```bash
if [[ -n "${T:-}" && "$T" == /tmp/ft_ls-tests.* && -d "$T" ]]; then
    chmod -R u+rwx -- "$T"
    rm -rf -- "$T"
fi
```
