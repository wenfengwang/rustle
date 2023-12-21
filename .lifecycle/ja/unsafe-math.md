
## オーバーフローチェックなしの安全でない数学演算

### 設定

* detector id: `unsafe-math`
* 重大度: 高

### 説明

すべての算術演算でオーバーフローチェックを有効にします。そうでない場合、オーバーフローが発生し、結果が不正確になる可能性があります。

NEARコントラクトでのオーバーフローチェックは、以下の2つの異なる方法で実装できます。

1. \[推奨\] Cargoマニフェストで`overflow-checks`を有効にします。この場合、算術演算に`+`、`-`、`*`を使用しても構いません。
2. 安全な数学関数（例：`checked_xxx()`）を使用して算術演算を行います。

### サンプルコード

この例では、Cargoマニフェストで`overflow-checks`フラグがオフになっているため、`+`を使用するとオーバーフローが発生する可能性があります。

```toml
[profile.xxx]  # `xxx`は`dev`または`release`に等しい
overflow-checks = false
```

```rust
let a = b + c;
```

`overflow-checks=false`で加算演算を行う場合、以下のコードが推奨されます。

```rust
let a = b.checked_add(c).expect("Overflow occurred");
```
