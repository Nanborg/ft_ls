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

Comparaison systématique avec `ls` (même locale) :

```sh
diff <(./ft_ls -l tests) <(LC_ALL=C ls -l tests)
```
