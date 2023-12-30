
# CSVからNotionへ

契約機能と変数を選択したNotionページに簡単にエクスポートします。

⚠警告: 実験的な機能で、変更される可能性があります。

## 使い方

1. `developer.notion.com`でインテグレーションを作成し、APIキーを取得してください。プロジェクトページをこのインテグレーションと共有することを忘れないでください。
2. 監査プロジェクト用の専用ページを作成し、そのID（オプションの`-`を含むUUID形式の文字列）を取得します。
3. 安定したプロキシが必要です。

## スクリプト

「utils/csv2notion」フォルダ内。

Linux:

```bash
npm install

export NOTION_KEY=secret_...
export PAGE_ID=<your page id>
npm run import
```

Windows:

```powershell
npm install

$env:NOTION_KEY = 'secret_...'
$env:PAGE_ID = '...'
Get-ChildItem -Path <path to csvs> -Filter *.csv -Recurse | %{$_.FullName} | %{node import.js $_}
```
