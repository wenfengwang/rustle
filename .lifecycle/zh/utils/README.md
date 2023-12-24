# CSV 转 Notion

只需将合约函数和变量导出到选定的 Notion 页面。

⚠警告：实验性的，可能会有所更改。

## 如何使用

1. 在 `developer.notion.com` 创建一个集成并获取 API 密钥。记得将项目页面分享给该集成。
2. 创建一个专门用于审计项目的页面，并获取其 ID（类似 UUID 的字符串，可选择包含“-”）。
3. 需要一个稳定的代理。

## 脚本

位于 "utils/csv2notion" 文件夹下。

Linux：

```bash
npm install

export NOTION_KEY=secret_...
export PAGE_ID=<your page id>
npm run import
```

Windows：

```powershell
npm install

$env:NOTION_KEY = 'secret_...'
$env:PAGE_ID = '...'
Get-ChildItem -Path <path to csvs> -Filter *.csv -Recurse | %{$_.FullName} | %{node import.js $_}
```