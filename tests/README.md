# tests — Environnement de test ft_ls

> Compagnon de `ft_ls_checklist.md` (§ 8). Ces dossiers ne font pas partie du rendu.

Chaque dossier prépare une famille de cas limites. À remplir petit à petit.

| Dossier | Cas à couvrir |
| --- | --- |
| `fichiers_simples/` | dossier vide, un seul fichier, beaucoup de fichiers |
| `caches/` | fichiers cachés, `.` et `..` |
| `sous_dossiers/` | plusieurs niveaux (`niveau2/`) pour `-R` |
| `liens/` | lien vers un fichier, un dossier, un lien cassé |
| `boucle_symbolique/` | boucle de liens symboliques (pas de récursion infinie) |
| `permissions/` | dossier sans droit de lecture |
| `dates/` | dates anciennes, récentes et identiques (pour `-t`) |
| `noms_speciaux/` | noms longs, noms avec espaces, tailles très différentes |

Le script `run.sh` suit les catégories de `CHECKLIST_ft_ls.md`. Il crée ses
fixtures dans un dossier temporaire, compare stdout, stderr et codes de sortie
avec `/bin/ls` en locale C (en normalisant seulement le nom du programme dans
les messages d'erreur), puis supprime les fixtures. Il couvre les options
obligatoires seules et combinées, les arguments fichiers/dossiers, les erreurs,
les liens, les permissions, les dates, les dossiers vides, les noms longs et
les fichiers nombreux.

```sh
sh tests/run.sh
```

Un échec indique une différence à examiner. Le test d'accès refusé est ignoré
si le script tourne en root, car root peut lire le dossier malgré ses droits.
