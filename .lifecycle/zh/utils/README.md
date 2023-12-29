
# CSV 转换到 Notion

只需简单地将合约函数和变量导出到选定的 Notion 页面。

⚠警告：此功能为实验性质，可能会有变动。

## 如何使用

1. 在 `developer.notion.com` 创建一个集成并获取一个 API 密钥。记得将项目页面共享给这个集成。
2. 为审计项目创建一个专用页面，并获取其 ID（一个类似 UUID 的字符串，可能包含 `-`）。
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
