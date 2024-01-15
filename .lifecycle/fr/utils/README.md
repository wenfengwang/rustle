
# CSV vers Notion

Exportez simplement les fonctions et les variables de contrat vers la page Notion sélectionnée.

⚠ATTENTION : expérimental, susceptible de subir des modifications.

## Comment utiliser

1. Créez une intégration sur `developer.notion.com` et obtenez une clé API. Assurez-vous de partager la page du projet avec cette intégration.
2. Créez une page dédiée pour un projet d'audit et récupérez son ID (une chaîne de caractères semblable à un UUID, avec des `-` en option).
3. Nécessite un proxy stable.

## Script

Dans le dossier "utils/csv2notion".

Linux :

```bash
npm install

export NOTION_KEY=secret_...
export PAGE_ID=<votre ID de page>
npm run import
```

Windows :

```powershell
npm install

$env:NOTION_KEY = 'secret_...'
$env:PAGE_ID = '<votre ID de page>'
Get-ChildItem -Path <chemin vers les csv> -Filter *.csv -Recurse | %{$_.FullName} | %{node import.js $_}
```
