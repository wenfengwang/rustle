
## 分岐条件におけるトートロジーの使用

### Configuration

* detector id: `tautology`
* severity: low

### Description

条件に`true`または`false`が含まれることで分岐が決定論的になる、単純なトートロジーを検出します。

### サンプルコード

```rust
let ok: bool = check_state();
if true || ok {
    // ...
} else {
    // ...
}
```

このデモでは、`else`ブランチ内のコードは決して実行されません。これは`true || ok`がトートロジーであるためです。
