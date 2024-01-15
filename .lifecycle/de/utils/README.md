
# CSV zu Notion

Exportieren Sie einfach Vertragsfunktionen und -variablen auf die ausgewählte Notion-Seite.

⚠WARNUNG: Experimentell, Änderungen vorbehalten.

## Wie man es benutzt

1. Erstellen Sie eine Integration auf `developer.notion.com` und erhalten Sie einen API-Schlüssel. Vergessen Sie nicht, die Projektseite mit dieser Integration zu teilen.
2. Erstellen Sie eine eigene Seite für ein Audit-Projekt und ermitteln Sie deren ID (eine UUID-ähnliche Zeichenkette, optional mit `-`).
3. Ein stabiler Proxy wird benötigt.

## Skript

Im Ordner "utils/csv2notion".

Linux:

```bash
npm install

export NOTION_KEY=secret_...
export PAGE_ID=<Ihre Seiten-ID>
npm run import
```

Windows:

```powershell
npm install

$env:NOTION_KEY = 'secret_...'
$env:PAGE_ID = '<Ihre Seiten-ID>'
Get-ChildItem -Path <Pfad zu den CSVs> -Filter *.csv -Recurse | %{$_.FullName} | %{node import.js $_}
```
